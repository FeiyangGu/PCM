#include "Function.h"

void MI(char* inputfile, char* outputfile, double threshold)
{
	vector< vector<int> > Element;
	vector< map<int, int> > var_kind;
	vector< vector<int> > var_kind_num;
	vector<double> H;

	ifstream fin(inputfile);
	string str;
	int n = 0, m = 0;
	while (getline(fin, str))
	{ 
		stringstream ss(str);
		vector<int>temp;
		int value;
		m = 0;
		while (ss >> value)
		{
			map<int, int> mp_temp;
			if (n == 0) var_kind.push_back(mp_temp);
			if (var_kind[m].count(value) == 0)
			{
				var_kind[m][value] = var_kind[m].size();
			}
			value = var_kind[m][value];
			temp.push_back(value);
			m++;
		}
		ss.clear();
		Element.push_back(temp);
		if (n != 0 && Element[n].size() != Element[n - 1].size())
		{
			printf("The number of the elements in line %d are not the same as before\n", n + 1);
			exit(1);
		}
		n++;
	}
	fin.close();
	cout << n << " row(s)  " << m << " column(s)" << endl;
	if (n <= 2)
	{
		printf("The number of sample is too little\n");
		exit(1);
	}
	m = Element[0].size();
	for (int i = 0; i<m; i++)
	{
		vector<int> cnt(var_kind[i].size(), 0);
		for (int j = 0; j<n; j++)
		{
			int value = Element[j][i];
			cnt[value]++;
		}
		var_kind_num.push_back(cnt);
		H.push_back(0);
		for (int j = 0; j<var_kind_num[i].size(); j++)
		{
			double value = 1.0*var_kind_num[i][j] / n;
			H[i] -= value*log(value);
		}
	}
	ofstream fout(outputfile);

	for (int i = 0; i<m; i++)
	{
		for (int j = i + 1; j<m; j++)
		{
			vector<int> temp(var_kind[j].size(), 0);
			vector< vector<int> > join_count(var_kind[i].size(), temp);

			for (int k = 0; k<n; k++)
			{
				int iv = Element[k][i];
				int jv = Element[k][j];
				join_count[iv][jv]++;
			}
			double result = 0;
			for (int k = 0; k<var_kind[i].size(); k++)
			{
				for (int w = 0; w<var_kind[j].size(); w++)
				{
					if (join_count[k][w] == 0) continue;
					double value = 1.0*join_count[k][w] / n;
					result += value*log(1.0*n*join_count[k][w] / var_kind_num[i][k] / var_kind_num[j][w]);
				}
			}
			if (H[i] != 0 && H[j] != 0)
			{
				result /= min(H[i], H[j]);
				if (result >= threshold)
				{
					fout << i + 1 << " " << j + 1 << " " << result << endl;
				}
			}
		}
	}
	fout.close();
}