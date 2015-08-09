#include "BinMethod.h"
#include <cmath>
#include <map>
#include <cstdlib>
using namespace std;

void Bin(char* inputfile, char* outputfile, double threshold, double(*method) (vector<int>& var1, vector<int>& var2))
{
	vector< vector<int> > Element = ReadBinData(inputfile);
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

void Bin(char* inputfile, char* outputfile, double threshold, double(*method) (vector<int>& var1, vector<int>& var2, double), double cc)
{
	vector< vector<int> > Element = ReadBinData(inputfile);
	/// row->varable, column -> sample
	int m = Element.size(); // the number of variables
	vector<int> pu;
	vector<int> pv;
	vector<double> value;
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			double result = method(Element[i], Element[j], cc);
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
		fout << pu[i] << " " << pv[i] << " " << value[i]<<endl;
	}
	fout.close();
	return;
}