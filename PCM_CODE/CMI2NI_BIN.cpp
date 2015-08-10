#include "BinMethod.h"
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;
const int MAX_ORDER = 5;
const int INF = 1 << 29;

bool EdgeReduce_BIN(MatrixXi & data, MatrixXi &G, MatrixXd &Gval, int &order, double lamda);
double cmi_BIN(const MatrixXi & v1, const MatrixXi &v2);
void dfs_combntnslist_BIN(int n, int k, vector<int> & element, vector< vector<int> > & combntnslist);
double MI2_BIN(const MatrixXi & v1, const MatrixXi &v2, const MatrixXi & vcs);
double cas_BIN(const MatrixXi & x, const MatrixXi &y, const MatrixXi & z);

void CMI2NI_BIN(char* inputfile, char *outputfile, double threshold, int order0)
{
	vector< vector<int> > Element = ReadBinData(inputfile);
	int m = Element.size();
	int n = Element[0].size();
	MatrixXi data(m, n);
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
		if (order > MAX_ORDER) break;
		if (order0 != INF && order > order0)
		{
			break;
		}
		isReduced = EdgeReduce_BIN(data, G, Gval, order, threshold);
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

bool EdgeReduce_BIN(MatrixXi & data, MatrixXi &G, MatrixXd &Gval, int &order, double lamda)
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
					double cmiv = cmi_BIN(data.row(i), data.row(j));
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
						dfs_combntnslist_BIN(adj.size() - 1, order - 1, pos, combntnslist);
						MatrixXi v1 = data.row(i);
						MatrixXi v2 = data.row(j);
						MatrixXi vcs(order, v1.cols());

						for (int k = 0; k < combntnslist.size(); k++)
						{
							for (int w = 0; w <order; w++)
							{
								vcs.row(order - 1 - w) = data.row(adj[combntnslist[k][w]]);
							}
							double a = MI2_BIN(v1, v2, vcs);
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

double cmi_BIN(const MatrixXi & v1, const MatrixXi &v2)
{
	double p[2][2] = { 0 };
	int n = v1.cols();
	for (int i = 0; i <n; i++)
	{
		int a = v1(0, i);
		int b = v2(0, i);
		if ((a == 0 || a == 1) && (b == 0 || b == 1))
		{
			p[a][b] += 1;
		}
		else
		{
			cout << "There exits some non-binary elements!!!" << endl;
			exit(1);
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
			p[i][j] /= n;
	}
	double H[2] = { 0 };
	H[0] = p[0][0] * log(p[0][0]) + p[0][1] * log(p[0][1]);
	H[1] = p[1][0] * log(p[1][0]) + p[1][1] * log(p[1][1]);
	double result = 0;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result += p[i][j] * log(p[i][j] / (p[i][0] + p[i][1]) / (p[0][j] + p[1][j]));
		}
	}
	if (H[0] != 0 && H[1] != 0)
	{
		result /= min(H[0], H[0]);
		return result;
	}
	else return 0;
}

void dfs_combntnslist_BIN(int n, int k, vector<int> & element, vector< vector<int> > & combntnslist)
{
	if (k == -1)
	{
		combntnslist.push_back(element);
		return;
	}
	if (n == -1) return;
	element.push_back(n);
	dfs_combntnslist_BIN(n - 1, k - 1, element, combntnslist);
	element.pop_back();
	dfs_combntnslist_BIN(n - 1, k, element, combntnslist);
	return;
}
double MI2_BIN(const MatrixXi & x, const MatrixXi &y, const MatrixXi & z)
{
	return (cas_BIN(x, y, z) + cas_BIN(y, x, z)) / 2;
}

double cas_BIN(const MatrixXi & x, const MatrixXi &y, const MatrixXi & z)
{
	int  n1 = z.rows();
	int n = n1 + 2;
	int m = z.cols();
	vector<double>pxyz(1 << n, 0);
	vector<double>pxz(1 << (n - 1), 0);
	vector<double>pyz(1 << (n - 1), 0);
	vector<double>px(2, 0);
	vector<double>py(2, 0);
	for (int i = 0; i < x.cols(); i++)
	{
		int sx = x(0, i);
		int sy = y(0, i);
		int sz = 0;
		for (int j = 0; j < z.rows(); j++)
		{
			sz = sz << 1;
			sz += z(j, i);
		}
		px[sx] += 1;
		py[sy] += 1;
		pxyz[sx + (sy << 1) + (sz << 2)] += 1;
		pxz[sx + (sz << 1)] += 1;
		pyz[sy + (sz << 1)] += 1;
	}
	for (int i = 0; i < (1 << n); i++)
	{
		if (i < pxyz.size()) pxyz[i] /= m;
		if (i < pxz.size()) pxz[i] /= m;
		if (i < pyz.size()) pyz[i] /= m;
		if (i < px.size()) px[i] /= m;
		if (i < py.size()) py[i] /= m;
	}
	double result = 0;
	for (int i = 0; i < (1 << n); i++)
	{
		int sxyz = i;
		int sx = i & 1;
		int sy = (i&(1 << 1)) >> 1;
		int sxz = ((i >> 2) << 1) + sx;
		int syz = ((i >> 2) << 1) + sy;
		double temp = 0;
		for (int j = 0; j < 2; j++)
		{
			int jsx = j;
			int jsxyz = (syz << 1) + jsx;
			int jsxz = ((i >> 2) << 1) + jsx;
			temp += pxz[sxz] * pxyz[jsxyz] / pxz[jsxz] * px[jsx];
			int jsy = j;
			int jsyz = ((i >> 2) << 1) + jsy;
			jsxyz = (i & 1) + (jsyz << 1);
			temp += pxz[sxz] * pxyz[jsxyz] / pyz[jsyz] * py[jsy];
		}
		if (pxyz[sxyz] > 1e-8)
		{
			result += pxyz[sxyz] * log(pxyz[sxyz] / temp);
		}
	}
	return result;
}
