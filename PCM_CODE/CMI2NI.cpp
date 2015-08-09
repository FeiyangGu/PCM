#include "ConMethod.h"
#include <iostream>
#include <fstream>
using namespace std;
const int INF = 1 << 29;

bool EdgeReduce(MatrixXd & data, MatrixXi &G, MatrixXd &Gval, int &order, double lamda);
double cmi(const MatrixXd & v1, const MatrixXd &v2);
void dfs_combntnslist(int n, int k, vector<int> & element, vector< vector<int> > & combntnslist);
double MI2(const MatrixXd & v1, const MatrixXd &v2, const MatrixXd & vcs);
double cas(const MatrixXd & x, const MatrixXd &y, const MatrixXd & z);


void CMI2NI(char* inputfile, char *outputfile, double threshold, int order0)
{
	vector< vector<double> > Element = ReadConData(inputfile);
	int m = Element.size();
	int n = Element[0].size();
	MatrixXd data(m, n);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			data(i, j) = Element[i][j];
		}
	}

	MatrixXi G(m, m);
	G = MatrixXi::Ones(m, m);
	for (int i = 0; i < G.rows(); i++)
		G(i, i) = 0;

	MatrixXd Gval(m, m);
	Gval = MatrixXd::Ones(m, m);
	for (int i = 0; i < Gval.rows(); i++)
	{
		Gval(i, i) = 0;
	}

	int order = -1;
	bool isReduced = true;
	while (isReduced)
	{
		order = order + 1;
		if (order0 != INF && order > order0)
		{
			break;
		}
		isReduced = EdgeReduce(data, G, Gval, order, threshold);
	}
	order = order - 1;
	ofstream fout(outputfile);
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if (Gval(i, j) >= threshold)
			{
				fout << i + 1 << " " << j + 1 << " " << Gval(i, j) << endl;
			}
		}
	}
	fout.close();
}

bool EdgeReduce(MatrixXd & data, MatrixXi &G, MatrixXd &Gval, int &order, double lamda)
{
	bool flag = false;
	for (int i = 0; i < G.rows(); i++)
	{
		for (int j = 0; j < G.cols(); j++)
		{
			if (G(i, j) != 0)
			{
				if (order == 0)
				{
					double cmiv = cmi(data.row(i), data.row(j));
					Gval(i, j) = Gval(j, i) = cmiv;
					if (cmiv < lamda)
					{
						G(i, j) = G(j, i) = 0;
						flag = true;
					}
				}
				else
				{
					vector<int> adj;
					for (int k = 0; k < G.rows(); k++)
					{
						if (G(i, k) != 0 && G(j, k) != 0)
						{
							adj.push_back(k);
						}
					}
					if (adj.size() >= order)
					{
						double cmiv = 0;
						vector<int>pos;
						vector< vector<int>> combntnslist;
						dfs_combntnslist(adj.size() - 1, order - 1, pos, combntnslist);
						MatrixXd v1 = data.row(i);
						MatrixXd v2 = data.row(j);
						MatrixXd vcs(order, v1.cols());

						for (int k = 0; k < combntnslist.size(); k++)
						{
							for (int w = 0; w <order; w++)
							{
								vcs.row(order - 1 - w) = data.row(adj[combntnslist[k][w]]);
							}
							double a = MI2(v1, v2, vcs);
							cmiv = max(cmiv, a);
						}
						Gval(i, j) = Gval(j, i) = cmiv;
						if (cmiv < lamda)
						{
							G(i, j) = G(j, i) = 0;
						}
						flag = true;
					}
				}
			}
		}
	}
	return flag;
}

void dfs_combntnslist(int n, int k, vector<int> & element, vector< vector<int> > & combntnslist)
{
	if (k == -1)
	{
		combntnslist.push_back(element);
		return;
	}
	if (n == -1) return;
	element.push_back(n);
	dfs_combntnslist(n - 1, k - 1, element, combntnslist);
	element.pop_back();
	dfs_combntnslist(n - 1, k, element, combntnslist);
	return;
}

double MI2(const MatrixXd & x, const MatrixXd &y, const MatrixXd & z)
{
	return (cas(x, y, z) + cas(y, x, z)) / 2;
}

double cas(const MatrixXd & x, const MatrixXd &y, const MatrixXd & z)
{
	int n1 = z.rows();
	int n = n1 + 2;
	MatrixXd xz(x.rows() + z.rows(), x.cols());
	xz << x, z;
	MatrixXd xyz(x.rows() + y.rows() + z.rows(), x.cols());
	xyz << x, y, z;

	MatrixXd Cov = Covar(x.transpose());
	MatrixXd Covm = Covar(xyz.transpose());
	MatrixXd Covm1 = Covar(xz.transpose());
	MatrixXd InvCov = Cov.inverse();
	MatrixXd InvCovm = Covm.inverse();
	MatrixXd InvCovm1 = Covm1.inverse();

	MatrixXd C11(1, 1); C11(0, 0) = InvCovm1(0, 0);
	MatrixXd C12(1, 1); C12 = MatrixXd::Zero(1, 1);
	MatrixXd C13 = InvCovm1.block(0, 1, 1, n1);
	MatrixXd C23 = InvCovm.block(1, 2, 1, n1) -
		InvCovm(0, 1) * (1.0 / (InvCovm(0, 0) - InvCovm1(0, 0) + InvCov(0, 0)))*(InvCovm.block(0, 2, 1, n1) - InvCovm1.block(0, 1, 1, n1));
	MatrixXd C22(1, 1);
	C22(0, 0) = InvCovm(1, 1) - InvCovm(0, 1)*InvCovm(0, 1)*(1.0 / (InvCovm(0, 0) - InvCovm1(0, 0) + InvCov(0, 0)));
	MatrixXd C33 = InvCovm.block(2, 2, n1, n1) - (1.0 / (InvCovm(0, 0) - InvCovm1(0, 0) + InvCov(0, 0)))*
		((InvCovm.block(0, 2, 1, n1) - InvCovm1.block(0, 1, 1, n1)).transpose() *  (InvCovm.block(0, 2, 1, n1) - InvCovm1.block(0, 1, 1, n1)));

	MatrixXd C1(1, n); C1 << C11, C12, C13;
	MatrixXd C2(1, n); C2 << C12, C22, C23;
	MatrixXd C3(n1, n); C3 << C13.transpose(), C23.transpose(), C33;

	MatrixXd InvC(n, n); InvC << C1, C2, C3;

	double C0 = Cov(0, 0) * (InvCovm(0, 0) - InvCovm1(0, 0) + InvCov(0, 0));
	double CS = 0.5 * ((InvC*Covm).trace() + log(C0) - n);
	return CS;
}

double cmi(const MatrixXd & v1, const MatrixXd &v2)
{
	double c1 = Covar(v1.transpose()).determinant();
	double c2 = Covar(v2.transpose()).determinant();
	MatrixXd m(v1.rows() + v2.rows(), v1.cols());
	m << v1,
		v2;
	double c3 = Covar(m.transpose()).determinant();
	if (fabs(c3) < 1e-8) return 1e10;
	double ret = 0.5*log(c1*c2 / c3);
	if (ret > 1e10) return 1e10;
	else return ret;
}
