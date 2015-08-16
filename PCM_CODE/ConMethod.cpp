#include "ConMethod.h"
const double INF = 1e32;

vector<int> ClustC(vector<RecordC>& Element, int k);

vector<RetRec> Con_Get_Pair(vector<RecordC>& Element, double threshold, double(*method) (vector<double>& var1, vector<double>& var2))
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

vector<RetRec> Con_Get_Pair(vector<RecordC>& Element, double threshold, double(*method) (vector<double>& var1, vector<double>& var2), bool isrank)
{
	int m = Element.size(); // the number of variables
	if (isrank)
	{
		for (int i = 0; i < m; i++)
		{
			vector<double> temp = Element[i].attribute;
			sort(temp.begin(), temp.end());
			map<double, int>mp;
			for (int j = 0; j < temp.size(); j++)
				mp[temp[j]] = j;
			for (int j = 0; j < temp.size(); j++)
				Element[i].attribute[j] = mp[Element[i].attribute[j]];
		}
	}
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

void Con(char* inputfile, char* outputfile, double threshold, double(*method) (vector<double>& var1, vector<double>& var2), int kind, int k)
{
	vector<RecordC> Element = ReadConData(inputfile);
	/// row->varable, column -> sample
	int m = Element.size();
	int n = Element[0].attribute.size();
	vector < vector<RecordC> > data;
	if (kind == 0)
	{
		k = 1;
		data.push_back(Element);
	}
	else if (kind == 1)
	{
		vector<int> belong_clust = ClustC(Element, k);
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
		vector<RetRec> ret = Con_Get_Pair(data[i], threshold, method);
		for (int j = 0; j < ret.size(); j++)
		{
			fout << ret[j].pu << " " << ret[j].pv << " " << ret[j].value << endl;
		}
	}
	fout.close();
	return;
}

void Con(char* inputfile, char* outputfile, double threshold, double(*method) (vector<double>& var1, vector<double>& var2), bool isrank, int kind, int k)
{
	vector<RecordC> Element = ReadConData(inputfile);
	/// row->varable, column -> sample
	int m = Element.size();
	int n = Element[0].attribute.size();
	vector < vector<RecordC> > data;
	if (kind == 0)
	{
		k = 1;
		data.push_back(Element);
	}
	else if (kind == 1)
	{
		vector<int> belong_clust = ClustC(Element, k);
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
		vector<RetRec> ret = Con_Get_Pair(Element, threshold, method, isrank);
		for (int j = 0; j < ret.size(); j++)
		{
			fout << ret[j].pu << " " << ret[j].pv << " " << ret[j].value << endl;
		}
	}
	fout.close();
	return;
}


vector<int> ClustC(vector<RecordC>& Element, int k)
{
	int m = Element.size();
	int n = Element[0].attribute.size();
	/// Clusting begins
	vector<RecordC> centroids;
	vector<bool> used(m, false);
	for (int i = 0; i < k; i++)
	{
		int tp = 0;
		do{
			tp = rand() % m;
		} while (used[tp]);
		centroids.push_back(RecordC(Element[tp].attribute, i));
	}
	vector<int>belong_clust(m, -1);
	vector<int>clust_num(k, 0);
	bool cluster_changed = true;
	int cnt = 0;
	while (cluster_changed)
	{
		cluster_changed = false;
		for (int i = 0; i<Element.size(); i++)
		{
			double min_dis = INF;
			double min_index = -1;
			for (int j = 0; j<k; j++)
			{
				double dis_j = CK_Distance(Element[i].attribute, centroids[j].attribute);

				if (dis_j < min_dis)
				{
					min_dis = dis_j;
					min_index = j;
				}
			}
			if (belong_clust[i] != min_index)
			{
				belong_clust[i] = min_index;
				cluster_changed = true;
			}
		}
		// 更新质点。这个时候用num统计了数目
		for (int i = 0; i<k; i++)
		{
			for (int j = 0; j<centroids[i].attribute.size(); j++)
			{
				centroids[i].attribute[j] = 0;
			}
			clust_num[i] = 0;
		}

		int temp = 0;
		for (int i = 0; i<Element.size(); i++)
		{
			temp = belong_clust[i];
			clust_num[temp]++;
			for (int j = 0; j<Element[i].attribute.size(); j++)
			{
				centroids[temp].attribute[j] += Element[i].attribute[j];
			}
		}


		for (int i = 0; i<k; i++)
		{
			for (int j = 0; j<centroids[i].attribute.size(); j++)
			{
				if (clust_num[i] != 0)
					centroids[i].attribute[j] = 1.0*centroids[i].attribute[j] / clust_num[i];
			}
		}
	}
	/// Clusting ends
	return belong_clust;
}
