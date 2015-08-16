#pragma once
#include <vector>
using namespace std;

/// RetRec: the pair of result
struct RetRec
{
	int pu, pv;
	double value;
	RetRec(int u = 0, int v = 0, double c = 0)
	{
		pu = u;
		pv = v;
		value = c;
	}
};

struct RecordB
{
	vector<int>  attribute;
	int id;
	RecordB(vector<int> temp, int ID=0)
	{
		attribute = temp;
		id = ID;
	}
};

struct RecordC
{
	vector<double> attribute;
	int id;
	RecordC(vector<double> temp, int ID = 0)
	{
		attribute = temp;
		id = ID;
	}
};