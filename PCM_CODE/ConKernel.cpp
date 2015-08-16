#include "ConMethod.h"

struct Node
{
	double element1, element2;
	Node(double a = 0, double b = 0)
	{
		element1 = a;
		element2 = b;
	}
	friend bool operator <(Node A, Node B)
	{
		return A.element1 < B.element1;
	}
};
double CK_Jaccard(vector<double>& var1, vector<double>& var2)
{
	int n = var1.size();
	double result = 0;
	double sq1 = 0, sq2 = 0;
	for (int i = 0; i < n; i++)
	{
		result += var1[i] * var2[i];
		sq1 += var1[i] * var1[i];
		sq2 += var2[i] * var2[i];
	}
	sq1 = sqrt(sq1);
	sq2 = sqrt(sq2);
	if (fabs(sq1 + sq2-result) < 1e-7) return 0;
	result = result / (sq1 + sq2 - result);
	return result;
}
double CK_Dice(vector<double>& var1, vector<double>& var2)
{
	int n = var1.size();
	double result = 0;
	double sq1 = 0, sq2 = 0;
	for (int i = 0; i < n; i++)
	{
		result += var1[i] * var2[i];
		sq1 += var1[i] * var1[i];
		sq2 += var2[i] * var2[i];
	}
	if (fabs(sqrt(sq1) + sqrt(sq2)) < 1e-7 ) return 0;
	result = 2*result / (sqrt(sq1) + sqrt(sq2));
	return result;
}
double CK_Overlap(vector<double>& var1, vector<double>& var2)
{
	int n = var1.size();
	double result = 0;
	double sq1 = 0, sq2 = 0;
	for (int i = 0; i < n; i++)
	{
		result += var1[i] * var2[i];
		sq1 += var1[i] * var1[i];
		sq2 += var2[i] * var2[i];
	}
	if (fabs( min(sqrt(sq1) , sqrt(sq2)) ) < 1e-7) return 0;
	result = result / min(sqrt(sq1), sqrt(sq2));
	return result;
}
double CK_Cosin(vector<double>& var1, vector<double>& var2)
{
	int n = var1.size();
	double result = 0;
	double sq1 = 0, sq2 = 0;
	for (int i = 0; i < n; i++)
	{
		result += var1[i] * var2[i];
		sq1 += var1[i] * var1[i];
		sq2 += var2[i] * var2[i];
	}
	if (fabs(sqrt(sq1*sq2) ) < 1e-7) return 0;
	result = result / sqrt(sq1*sq2);
	return result;
}

double CK_Pearson(vector<double>& var1, vector<double>& var2)
{
	int n = var1.size();
	double v1_sum = 0, v2_sum=0;
	double sq1_sum = 0, sq2_sum = 0;
	double mul_sum = 0;
	for (int i = 0; i < n; i++)
	{
		mul_sum += var1[i] * var2[i];
		v1_sum += var1[i];
		v2_sum += var2[i];
		sq1_sum += var1[i] * var1[i];
		sq2_sum += var2[i] * var2[i];
	}
	double a = mul_sum - v1_sum*v2_sum / n;
	double b = sqrt( (sq1_sum-v1_sum*v1_sum/n) * (sq2_sum-v2_sum*v2_sum/n) ) ;
	if (fabs(b) < 1e-7) return 0;
	return a / b;
}

double CK_DotProduct(vector<double>& var1, vector<double>& var2)
{
	double result = 0;
	int n = var1.size();
	for (int i = 0; i < n; i++)
		result += var1[i] * var2[i];
	return result;
}

double CK_Spearman(vector<double>& var1, vector<double>& var2)
{
	int n = var1.size();
	double result = 0;
	for (int i = 0; i < n; i++)
	{
		result += (var1[i] - var2[i])*(var1[i] - var2[i]);
	}
	return 1.0 - 6 * result / n / (n - 1) / (n + 1);
}

double CK_Kendall(vector<double>& var1, vector<double>& var2)
{
	int n = var1.size();
	double C = 0, D = 0, N3=0, N2=0, N1=0;
	map<double, int>mp1, mp2;
	for (int i = 0; i < n; i++)
	{
		if (mp1.count(var1[i]) == 0) mp1[var1[i]] = 1;
		else mp1[var1[i]] += 1;

		if (mp2.count(var2[i]) == 0) mp2[var2[i]] = 1;
		else mp2[var2[i]] += 1;

		for (int j = i+1; j < n; j++)
		{
			if (var1[i] == var1[j] || var2[i] == var2[j]) continue;
			if (var1[j] < var1[i] && var2[j] < var2[i])
				C += 1;
			else if (var1[j] > var1[i] && var2[j] > var2[i])
				C += 1;
			else D += 1;
		}
	}
	N3 = 0.5*n*(n - 1);
	for (map<double, int>::iterator it = mp1.begin(); it != mp1.end(); it++)
	{
		N1 += it->second*(it->second - 1);
	}
	N1 *= 0.5;
	for (map<double, int>::iterator it = mp2.begin(); it != mp2.end(); it++)
	{
		N2 += it->second*(it->second - 1);
	}
	N2 *= 0.5;
	double b = sqrt((N3 - N1)*(N3 - N2));
	if (fabs(b) < 1e-7) return 0;
	return (C - D) / b;
}

double CK_Distance(vector<double>& var1, vector<double>& var2)
{
	int n = var1.size();
	double ret = 0;
	for (int i = 0; i < n; i++)
	{
		ret += (var1[i] - var2[i]) * (var1[i] - var2[i]);
	}
	return sqrt(ret);
}

double CK_HoeffdingD(vector<double>& var1, vector<double>& var2)
{
	int n = var1.size();
	if (n <= 4)
	{
		printf("The number of elements is too small!!!");
		exit(1);
	}
	vector<int>R, S, Q;
	for (int i = 0; i < n; i++)
	{
		int temp = 0;
		for (int j = 0; j < n; j++)
		{
			if (var1[j] < var1[i] && var2[j] < var2[i])
			{
				temp += 1;
			}
		}
		Q.push_back(temp);
	}
	vector<double> v1 = var1, v2 = var2;
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	map<double, int>mp1, mp2;
	for (int i = 0; i < v1.size(); i++)
	{
		mp1[v1[i]] = i;
		mp2[v2[i]] = i;
	}
	for (int i = 0; i < n; i++)
	{
		R.push_back(mp1[var1[i]]);
		S.push_back(mp2[var2[i]]);
	}
	double D1 = 0, D2 = 0, D3 = 0;
	for (int i = 0; i < n; i++)
	{
		D1 += Q[i] * (Q[i] - 1);
		D2 += (R[i] - 1)*(R[i] - 2)*(S[i] - 1)*(S[i] - 2);
		D3 += (R[i] - 2)*(S[i] - 2)*Q[i];
	}
	double a = (n - 2)*(n - 3)*D1 + D2 - 2 * (n - 2)*D3;
	double b = n*(n - 1)*(n - 2)*(n - 3)*(n - 4);
	return a / b;
}