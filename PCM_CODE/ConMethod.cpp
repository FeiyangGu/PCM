#include "ConMethod.h"
void Con(char* inputfile, char* outputfile, double threshold, double(*method) (vector<double>& var1, vector<double>& var2))
{
	vector< vector<double> > Element = ReadConData(inputfile);
	/// row->varable, column -> sample
	int m = Element.size(); // the number of variables
	vector<int> pu;
	vector<int> pv;
	vector<double> value;
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			double result = method(Element[i], Element[j]);
			if (result >= threshold)
			{
				pu.push_back(i + 1);
				pv.push_back(j + 1);
				value.push_back(result);
			}
		}
	}
	ofstream fout(outputfile);
	for (int i = 0; i < pu.size(); i++)
	{
		fout << pu[i] << " " << pv[i] << " " << value[i] << endl;
	}
	fout.close();
	return;
}

void Con(char* inputfile, char* outputfile, double threshold, double(*method) (vector<double>& var1, vector<double>& var2), bool isrank)
{
	vector< vector<double> > Element = ReadConData(inputfile);
	/// row->varable, column -> sample
	int m = Element.size(); // the number of variables
	if (isrank)
	{
		for (int i = 0; i < m; i++)
		{
			vector<double> temp = Element[i];
			sort(temp.begin(), temp.end());
			map<double, int>mp;
			for (int j = 0; j < temp.size(); j++)
				mp[temp[j]] = j;
			for (int j = 0; j < temp.size(); j++)
				Element[i][j] = mp[Element[i][j]];
		}
	}
	vector<int> pu;
	vector<int> pv;
	vector<double> value;
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			double result = method(Element[i], Element[j]);
			if (result >= threshold)
			{
				pu.push_back(i + 1);
				pv.push_back(j + 1);
				value.push_back(result);
			}
		}
	}
	ofstream fout(outputfile);
	for (int i = 0; i < pu.size(); i++)
	{
		fout << pu[i] << " " << pv[i] << " " << value[i] << endl;
	}
	fout.close();
	return;
}