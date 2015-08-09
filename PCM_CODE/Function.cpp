#include "Function.h"

/*
input: rows represent samples and  colums represent attributes
output: rows represent attributes and colums represent samples
*/
vector < vector<int> >  ReadBinData(char * inputfile)
{
	vector< vector<int> > Element;
	ifstream fin(inputfile);
	string str;
	int n = 0; //sample
	int m = 0; //variable
	vector<int>temp;
	int pre = -1;
	while (getline(fin, str))
	{
		stringstream ss(str);
		int value;
		m = 0;
		while (ss >> value)
		{
			if (value!=0 && value!=1)
			{
				printf("The input data shoud be a 0 1 matrix!!!");
				exit(1);
			}
			if (Element.size() <= m) Element.push_back(temp);
			Element[m].push_back(value);
			m++;
		}
		if (n != 0 && m != pre)
		{
			printf("The number of the elements in line %d are not the same as before\n", n + 1);
			exit(1);
		}
		n++;
		pre = m;
	}
	fin.close();
	cout << n << " row(s)  " << m << " column(s)" << endl;
	if (n <= 2)
	{
		printf("The number of sample is too little\n");
		exit(1);
	}
	return Element;
}

vector < vector<double> > ReadConData(char * inputfile)
{
	vector< vector<double> > Element;
	ifstream fin(inputfile);
	string str;
	int n = 0; //sample
	int m = 0; //variable
	vector<double>temp;
	int pre = -1;
	while (getline(fin, str))
	{
		stringstream ss(str);
		double value;
		m = 0;
		while (ss >> value)
		{
			if (Element.size() <= m) Element.push_back(temp);
			Element[m].push_back(value);
			m++;
		}
		if (n != 0 && m != pre)
		{
			printf("The number of the elements in line %d are not the same as before\n", n + 1);
			exit(1);
		}
		n++;
		pre = m;
	}
	fin.close();
	cout << n << " row(s)  " << m << " column(s)" << endl;
	if (n <= 2)
	{
		printf("The number of sample is too little\n");
		exit(1);
	}
	return Element;
}

MatrixXd Covar(const MatrixXd &mat)
{
	MatrixXd centered = mat.rowwise() - mat.colwise().mean();
	MatrixXd cov = (centered.adjoint() * centered) / double(mat.rows() - 1);
	return cov;
}

double Support(vector<int>& var1, int var1v)
{
	int n = var1.size();
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (var1[i] == var1v)
			cnt++;
	}
	return 1.0*cnt / n;
}

double Support(vector<int>& var1, int var1v, vector<int>& var2, int var2v)
{
	int n = var1.size();
	int cnt = 0;
	for (int i = 0; i < n; i++)
	{
		if (var1[i] == var1v && var2[i] == var2v)
			cnt++;
	}
	return 1.0*cnt / n;
}
double SupCond(vector<int>& var1, int var1v, vector<int>& var2, int var2v)
{
	int n = var1.size();
	int cnt = 0;
	int cnt_cond = 0;
	for (int i = 0; i < n; i++)
	{
		if (var2[i] == var2v)
		{
			cnt_cond++;
			if (var1[i] == var1v)
			{
				cnt++;
			}
		}
	}
	if (cnt_cond == 0) return 0;
	return 1.0 * cnt / cnt_cond;
}