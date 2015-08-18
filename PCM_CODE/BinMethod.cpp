#include "BinMethod.h"
#include <cmath>
#include <map>
#include <set>
#include <cstdlib>
using namespace std;
const int INF = 1 << 29;

vector<int> ClustB(vector<RecordB>& Element, double r);
vector<RetRec> Bin_Get_Pair(vector<RecordB>& Element, double threshold, double(*method) (vector<int>& var1, vector<int>& var2));
vector<RetRec> Bin_Get_Pair(vector<RecordB>& Element, double threshold, double(*method) (vector<int>& var1, vector<int>& var2, double), double cc);


void Bin(char* inputfile, char* outputfile, double threshold, double(*method) (vector<int>& var1, vector<int>& var2), int kind, double r)
{
	vector< RecordB > Element = ReadBinData(inputfile);
	/// row->varable, column -> sample
	int m = Element.size();
	int n = Element[0].attribute.size();
	vector < vector<RecordB> > data;
	int k = 0;
	if (kind == 0)
	{
		k = 1;
		data.push_back(Element);
	}
	else if (kind == 1)
	{
		vector<int> belong_clust = ClustB(Element, r);											/// utilize CLOPE to cluster the data
		set<int>Set;
		for (int i = 0; i < belong_clust.size(); i++)
		{
			if (Set.count(belong_clust[i]) == 0)
				Set.insert(belong_clust[i]);
		}
		k = Set.size();
		data.resize(k);
		for (int i = 0; i < m; i++)
		{
			int temp = belong_clust[i];
			data[temp].push_back(Element[i]);
		}
	}
	ofstream fout(outputfile);
	for (int i = 0; i < k; i++)
	{
		vector<RetRec> ret = Bin_Get_Pair(data[i], threshold, method);                        ///  calculate the correlations between the pairs which are in the same cluster. 
		for (int j = 0; j < ret.size(); j++)
		{
			fout << ret[j].pu << " " << ret[j].pv << " " << ret[j].value << endl;
		}
	}
	fout.close();
	return;
}

void Bin(char* inputfile, char* outputfile, double threshold, double(*method) (vector<int>& var1, vector<int>& var2, double), double cc, int kind, double r)
{
	vector< RecordB > Element = ReadBinData(inputfile);
	/// row->varable, column -> sample
	int m = Element.size();
	int n = Element[0].attribute.size();
	vector < vector<RecordB> > data;
	int k = 0;
	if (kind == 0)
	{
		k = 1;
		data.push_back(Element);
	}
	else if (kind == 1)
	{
		vector<int> belong_clust = ClustB(Element, r);	                                  /// utilize CLOPE to cluster the data
		set<int>Set;
		for (int i = 0; i < belong_clust.size(); i++)
		{
			if (Set.count(belong_clust[i]) == 0)
				Set.insert(belong_clust[i]);
		}
		k = Set.size();
		data.resize(k);
		for (int i = 0; i < m; i++)
		{
			int temp = belong_clust[i];
			data[temp].push_back(Element[i]);
		}
	}
	ofstream fout(outputfile);
	for (int i = 0; i < k; i++)
	{
		vector<RetRec> ret = Bin_Get_Pair(data[i], threshold, method, cc);              ///  calculate the correlations between the pairs which are in the same cluster. 
		for (int j = 0; j < ret.size(); j++)
		{
			fout << ret[j].pu << " " << ret[j].pv << " " << ret[j].value << endl;
		}
	}
	fout.close();
	return;
}

vector<int> ClustB(vector<RecordB>& Element, double r)                                 /// CLOPE
{
	int m = Element.size();
	int n = Element[0].attribute.size();
	/// Clusting begins
	vector< vector<int>> data(m);
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (Element[i].attribute[j] == 1)
				data[i].push_back(j);
		}
	}
	int k = 0;
	vector<int>belong_clust(m, -1);
	vector<int>C;
	bool cluster_changed = true;
	vector<int> S;
	vector< map<int, int> > W;
	int cnt = 0;
	while (cluster_changed)
	{   
		cnt++;
		cluster_changed = false;
		for (int i = 0; i < m; i++)
		{
			double max_value = 0;
			int max_index = belong_clust[i];
			int old_clust = belong_clust[i];
			double v_min = 0;
			if (old_clust != -1)
			{
				int s_min = S[old_clust] - data[i].size();
				int w_min = W[old_clust].size();
				int c_min = C[old_clust] - 1;
				for (int q = 0; q < data[i].size(); q++)
				{
					if (W[old_clust].count(data[i][q]) > 0 && W[old_clust][data[i][q]] == 1)
						w_min--;
				}
				double a = 0, b = 0;
				if (w_min == 0) a = 0;
				else a = 1.0*s_min*c_min / pow(w_min, r);
				if (W[old_clust].size() == 0) b = 0;
				else b = 1.0 * S[old_clust] * C[old_clust] / pow(W[old_clust].size(), r);
				v_min = a - b;
			}
			for (int j = 0; j < k; j++)
			{
				double v_add = 0;
				
				int s_add = S[j] + data[i].size();
				int w_add = W[j].size();
				int c_add = C[j] + 1;
				for (int q = 0; q < data[i].size(); q++)
				{
					if (W[j].count(data[i][q]) == 0 || W[j][data[i][q]] == 0)
						w_add++;
				}
				double a = 0, b = 0;
				if (w_add == 0) a = 0;
				else a = 1.0*s_add*c_add /pow( w_add,r);
				if (W[j].size() == 0) b = 0;
				else b = 1.0 * S[j] * C[j] /pow( W[j].size(), r);
				v_add = a - b;
				if (v_add + v_min > max_value)
				{
					max_value = v_add + v_min;
					max_index = j;
				}
			}

			double v_add = 1.0 * data[i].size() * 1 / pow(data[i].size(), r);
			if (v_add + v_min > max_value)
			{
				S.push_back(data[i].size());
				C.push_back(1);
				map<int, int > temp;
				W.push_back(temp);
				for (int j = 0; j < data[i].size(); j++)
				{
					W[k][data[i][j]] = 1;
				}
				belong_clust[i] = k++;
				cluster_changed = true;
				continue;
			}
			if (max_index != belong_clust[i])
			{
				int old_clust = belong_clust[i];
				S[max_index] += data[i].size();
				C[max_index] += 1;
				if (old_clust != -1)
				{
					C[old_clust] -= 1;
					S[old_clust] -= data[i].size();
				}
				for (int q = 0; q < data[i].size(); q++)
				{
					if (W[max_index].count(data[i][q]) == 0)
						W[max_index][data[i][q]] = 1;
					else W[max_index][data[i][q]]++;
					if (old_clust != -1)
					{
						W[old_clust][data[i][q]]--;
					}
				}
				belong_clust[i] = max_index;
				cluster_changed = true;
			}
		}
	}

	/// Clusting ends
	return belong_clust;
}

vector<RetRec> Bin_Get_Pair(vector<RecordB>& Element, double threshold, double(*method) (vector<int>& var1, vector<int>& var2))
{
	int m = Element.size(); // the number of variables
	vector<RetRec> ret;
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			double result = method(Element[i].attribute, Element[j].attribute);
			if (result >= threshold)
			{
				ret.push_back(RetRec(Element[i].id, Element[j].id, result));
			}
		}
	}
	return ret;
}

vector<RetRec> Bin_Get_Pair(vector<RecordB>& Element, double threshold, double(*method) (vector<int>& var1, vector<int>& var2, double), double cc)
{
	int m = Element.size(); // the number of variables
	vector<RetRec> ret;
	for (int i = 0; i < m; i++)
	{
		for (int j = i + 1; j < m; j++)
		{
			double result = method(Element[i].attribute, Element[j].attribute, cc);
			if (result >= threshold)
			{
				ret.push_back(RetRec(Element[i].id, Element[j].id, result));
			}
		}
	}
	return ret;
}