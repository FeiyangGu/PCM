#include "ConMethod.h"

struct Node
{
	int u, v;
	double value;
	Node(int a = 0, int b = 0, double c = 0)
	{
		u = a; v = b; value = c;
	}
	friend bool operator <(Node A, Node B)
	{
		return A.value > B.value;
	}
};

const double M_SQRT1_2 = sqrt(0.5);

void Padjust(MatrixXd& pmat, MatrixXd &p_mat);
double normalCFD(double value);
double FisherNormal(double value, int n, int q);
double p12_3(double p12, double p13, double p23);
double p12_34(double p12_3, double p14_3, double p24_3);

void LOPC(char* inputfile, char *outputfile)
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

	MatrixXd CV(m, m);
	CV = Covar(data.transpose());

	MatrixXd PAB(m, m);
	MatrixXd PABC(m, m);
	MatrixXd PABCD(m, m);

	MatrixXd pab(m, m);
	MatrixXd p_ab(m, m);
	MatrixXd pabc(m, m);
	MatrixXd p_abc(m, m);
	MatrixXd pabcd(m, m);
	MatrixXd p_abcd(m, m);

	MatrixXd temp(2, 2);
	for (int i = 0; i < m; i++)
	{
		for (int j = i+1; j < m; j++)
		{
			temp(0, 0) = CV(i, i);
			temp(0, 1) = CV(i, j);
			temp(1, 0) = CV(j, i);
			temp(1, 1) = CV(j, j);
			MatrixXd temp_inv(2, 2); temp_inv = temp.inverse();
			PAB(i, j) = -1.0*temp_inv(0, 1) / sqrt(temp_inv(0, 0)*temp_inv(1, 1));
			PAB(j, i) = PAB(i, j);
			pab(i, j) = pab(j, i) =FisherNormal(PAB(i,j), m, 0);
		}
	}
	Padjust(pab, p_ab);
	for (int i = 0; i < m; i++)
	{
		for (int j = i+1; j < m; j++)
		{
			double tempij = 0;
			for (int k = 0; k < m; k++)
			{
				if (k == i || k == j) continue;
				double temp = p12_3( PAB(i, j) , PAB(i, k) ,PAB(j, k) );
				tempij = max(temp, tempij);
			}
			PABC(i, j) = PABC(j, i) = tempij;
			pabc(i, j) = pabc(j, i) = FisherNormal(tempij, m, 1);
		}
	}
	Padjust(pabc, p_abc);
	for (int i = 0; i < m; i++)
	{
		for (int j = i+1; j < m; j++)
		{
			if (p_ab(i, j) < 0.05 && p_abc(i,j)<0.05)
			{
				double tempij = 0;
				for (int k = 0; k < m; k++)
				{
					if (k == i || k == j) continue;
					for (int w = 0; w < m; w++)
					{
						if (w == k || w == j || w == i) continue;
						double v12_3 = p12_3(PAB(i, j), PAB(i, k), PAB(j, k) );
						double v14_3 = p12_3(PAB(i, w), PAB(i, k), PAB(w, k) );
						double v24_3 = p12_3(PAB(j, w), PAB(j, k), PAB(w, k) );
						double temp = p12_34(v12_3, v14_3, v24_3);
						tempij = max(tempij, temp);
					}
				}
				PABCD(i, j) = PABCD(j, i) = tempij;
				pabcd(i, j) = pabcd(j, i) = FisherNormal(tempij, m, 2);
			}
			else
			{
				pabcd(i, j) = pabcd(j, i) = 2.0;
				p_abcd(i, j) = p_abcd(j, i) = 2.0;
			}
		}
	}
	Padjust(pabcd, p_abcd);
	ofstream fout(outputfile);
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if (p_abcd(i, j) < 0.05)
			{
				fout << i + 1 << " " << j + 1 << " " << p_abcd(i, j) << endl;
			}
		}
	}
	fout.close();
}

void Padjust(MatrixXd& pmat, MatrixXd &p_mat)
{
	int m = pmat.rows();
	int num = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if (pmat(i, j) <= 1.0)
				num++;
		}
	}
	Node *p = new Node[num];
	num = 0;
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			if (pmat(i,j) <= 1.0)
				p[num++] = Node(i, j, pmat(i, j) );
		}
	}
	sort(p, p + num);
	int u = 0, v = 0;
	double value = 0;
	double ret = 1;
	for (int i = 0; i < num; i++)
	{
		u = p[i].u;   
		v = p[i].v;
		value = p[i].value;
		ret = min(ret, value *num / (i + 1) );
		p_mat(u, v) = p_mat(v, u) = ret;
	}
	delete []p;
}

double normalCFD(double value)
{
	return 0.5 * erfc(-value * M_SQRT1_2);
}
double FisherNormal(double value, int n, int q)
{
	double z = 0.5*log((1 + value) / (1 - value));
	double key = sqrt(n - q - 3)*value;
	return  2.0*(1.0 - normalCFD(key));
}
double p12_3(double p12, double p13, double p23)
{
	return (p12 - p13*p23) / sqrt( (1-p13*p13)*(1-p23*p23) );
}
double p12_34(double p12_3, double p14_3, double p24_3)
{
	return (p12_3 - p14_3*p24_3) / sqrt( (1-p14_3*p14_3)*(1-p24_3*p24_3) );
}
