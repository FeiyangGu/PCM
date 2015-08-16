
#include "BinMethod.h"
#include <fstream>
#include <iostream>
using namespace std;
const double eps = 1e-8;


double BK_Support(vector<int>& var1, vector<int>& var2)
{
	double pij = Support(var1, 1, var2, 1);
	return pij;
}

double BK_Jaccard(vector<int>& var1, vector<int>& var2)
{
	double pi = Support(var1, 1);
	double pj = Support(var2, 1);
	if (pi == 0 || pj == 0) return 0;
	double pij = Support(var1, 1, var2, 1);
	return  pij / (pi + pj - pij);
}

double BK_Interest(vector<int>& var1, vector<int>& var2)
{
	double pi = Support(var1, 1);
	double pj = Support(var2, 1);
	if (pi == 0 || pj == 0) return 0;
	double pij = Support(var1, 1, var2, 1);
	return pij / (pi * pj);
}

double BK_Piatetsky_Shapiros(vector<int>& var1, vector<int>& var2)
{
	double pi = Support(var1, 1);
	double pj = Support(var2, 1);
	double pij = Support(var1, 1, var2, 1);
	return pij - (pi * pj);
}

double BK_Cosine(vector<int>& var1, vector<int>& var2)
{
	double pi = Support(var1, 1);
	double pj = Support(var2, 1);
	if (pi == 0 || pj == 0) return 0;
	double pij = Support(var1, 1, var2, 1);
	return pij / sqrt(pi * pj);
}

double BK_Confidence(vector<int>& var1, vector<int>& var2)
{
	return max(SupCond(var1, 1, var2, 1), SupCond(var2, 1, var1, 1));
}

double BK_YulesQ(vector<int>& var1, vector<int>& var2)
{
	double pij = Support(var1, 1, var2, 1);
	double pi0j0 = Support(var1, 0, var2, 0);
	double temp = Support(var1, 1, var2, 0)*Support(var1, 0, var2, 1);
	double a = pij*pi0j0 - temp;
	double b = pij*pi0j0 + temp;;
	if (b == 0) return 0;
	return a / b;
}

double BK_YulesY(vector<int>& var1, vector<int>& var2)
{
	double pij = Support(var1, 1, var2, 1);
	double pi0j0 = Support(var1, 0, var2, 0);
	double temp = Support(var1, 1, var2, 0)*Support(var1, 0, var2, 1);
	double a = sqrt(pij*pi0j0) - sqrt(temp);
	double b = sqrt(pij*pi0j0) + sqrt(temp);
	if (b == 0) return 0;
	return a / b;
}

double BK_Kappa(vector<int>& var1, vector<int>& var2)
{
	double pi0 = Support(var1, 0);
	double pi = Support(var1, 1);
	double pj0 = Support(var2, 0);
	double pj = Support(var2, 1);
	double a = Support(var1, 1, var2, 1) + Support(var1, 0, var2, 0) - pi*pj - pi0*pj0;
	double b = 1 - pi*pj - pi0*pj0;
	if (b == 0) return 0;
	return a / b;
}

double BK_J_Measure(vector<int>& var1, vector<int>& var2)
{
	double pij = Support(var1, 1, var2, 1);
	double a = 0, b=0;
	if (fabs(pij) > eps)
	{
		a += pij*log(SupCond(var2, 1, var1, 1) / Support(var2, 1));
		b += pij*log(SupCond(var1, 1, var2, 1) / Support(var1, 1));
	}
	if (fabs(Support(var1, 1, var2, 0)) > eps)
		a += Support(var1, 1, var2, 0)*log(SupCond(var2, 0, var1, 1) / Support(var2, 0));
	if (fabs(Support(var1, 0, var2, 1)))
		b += Support(var1, 0, var2, 1)*log(SupCond(var1, 0, var2, 1) / Support(var1, 0));
	return max(a, b);
}

double BK_OddsRatio(vector<int>& var1, vector<int>& var2)
{
	double a = Support(var1, 1, var2, 1)*Support(var1, 0, var2, 0);
	double b = Support(var1, 1, var2, 0)*Support(var1, 0, var2, 1);
	if (b == 0) return 0;
	return a/b;
}

double BK_Phi_Coefficient(vector<int>& var1, vector<int>& var2)
{
	double pij = Support(var1, 1, var2, 1);
	double pi = Support(var1, 1);
	double pj = Support(var2, 1);
	double a = pij - pi*pj;
	double b = sqrt(pi*pj*(1 - pi)*(1 - pj));
	if (b == 0) return 0;
	return a / b;
}

double BK_GiniIndex(vector<int>& var1, vector<int>& var2)
{
	double pi = Support(var1, 1);
	double pj = Support(var2, 1);
	double condji[4] = {
		SupCond(var2, 1, var1, 1),
		SupCond(var2, 0, var1, 1),
		SupCond(var2, 1, var1, 0),
		SupCond(var2, 0, var1, 0)
	};
	double a = pi*(condji[0] * condji[0] + condji[1] * condji[1]) +
		(1 - pi)*(condji[2] * condji[2] + condji[3] * condji[3]) - pj*pj-(1-pj)*(1-pj);
	double condij[4] = {
		SupCond(var1, 1, var2, 1),
		SupCond(var1, 0, var2, 1),
		SupCond(var1, 1, var2, 0),
		SupCond(var1, 0, var2, 0)
	};
	double b = pj*(condij[0] * condij[0] + condij[1] * condij[1]) +
		(1 - pj)*(condij[2] * condij[2] + condij[3] * condij[3])-pi*pi-(1-pi)*(1-pi);
	return max(a, b);
}

double BK_Laplace(vector<int>& var1, vector<int>& var2)
{
	double pi = Support(var1, 1);
	double pj = Support(var2, 1);
	double pij = Support(var1, 1, var2, 1);
	int n = var1.size();
	return max((n*pij + 1) / (n*pi + 2), (n*pij + 1) / (n*pj + 2));
}

double BK_Conviction(vector<int>& var1, vector<int>& var2)
{
	double a = 0, b = 0;
	double pi0j = Support(var1, 0, var2, 1);
	double pij0 = Support(var1, 1, var2, 0);
	if (pij0 == 0) a = 0;
	else a = Support(var1, 1)*Support(var2, 0) / pij0;
	if (pi0j == 0) b = 0;
	else b = Support(var1, 0)*Support(var2, 1) / pi0j;
	return max(a, b);
}

double BK_CertaintyFactor(vector<int>& var1, vector<int>& var2)
{
	double a = 0, b = 0;
	double pi = Support(var1, 1);
	double pj = Support(var2, 1);
	if (1 - pi == 0) a = 0;
	else a = (SupCond(var2, 1, var1, 1) - Support(var2, 1)) / (1 - pj);
	if (1 - pj == 0) b = 0;
	else b = (SupCond(var1, 1, var2, 1) - Support(var1, 1)) / (1 - pi);
	return max(a, b);
}

double BK_AddedValue(vector<int>& var1, vector<int>& var2)
{
	double a = SupCond(var2, 1, var1, 1) - Support(var2, 1);
	double b = SupCond(var1, 1, var2, 1) - Support(var1, 1);
	return max(a, b);
}

double BK_CollectiveStrength(vector<int>& var1, vector<int>& var2)
{
	double pi = Support(var1, 1);
	double pj = Support(var2, 1);
	double pij = Support(var1, 1, var2, 1);
	double pi0j0 = Support(var1, 0, var2, 0);
	if (pi*pj + (1 - pi)*(1 - pj) == 0 || 1 - pij - pi0j0 == 0) return 0;
	double a = (pij + pi0j0) / (pi*pj + (1 - pi)*(1 - pj));
	double b = (1 - pi*pj - (1 - pi)*(1 - pj)) / (1 - pij - pi0j0);
	return a*b;
}

double BK_Klosgen(vector<int>& var1, vector<int>& var2)
{
	return sqrt(Support(var1, 1, var2, 1)) *
		max(SupCond(var2, 1, var1, 1) - Support(var2, 1), SupCond(var1, 1, var2, 1) - Support(var1, 1));
}

double BK_ProbabilityRatio(vector<int>& var1, vector<int>& var2)
{
	double result = BK_Interest(var1, var2);
	if (result == 0) return 0;
	else return log(result);
}

double BK_LikelihoodRatio(vector<int>& var1, vector<int>& var2)
{
	int n = var1.size();
	double tp = Support(var1, 1, var2, 1);
	double ep = Support(var1, 1)*Support(var2, 1);
	if (fabs(tp) < eps)  return n*log(1.0/(1-ep));
	if (fabs(tp - 1) < eps) return 0;
	if (fabs(ep) < eps) return 0;
	if (fabs(ep - 1) < eps) return 0 ;
	return n*(tp*log(tp / ep) + (1 - tp)*log(1 - tp) / (1 - ep));
}

double BK_BCPNN(vector<int>& var1, vector<int>& var2, double cc)
{
	int n = var1.size();
	if (cc <= 0) cc = 0.5 / n;
	double tp = Support(var1, 1, var2, 1);
	double ep = Support(var1, 1) * Support(var2, 1);
	return log((tp + cc) / (ep + cc));
}

double BK_SCWCC(vector<int>& var1, vector<int>& var2, double cc)
{
	int n = var1.size();
	if (cc <= 0) cc = 0.5 / n;
	double tp = Support(var1, 1, var2, 1);
	double ep = Support(var1, 1) * Support(var2, 1);
	return n * (tp - ep)*(tp - ep) / (ep + cc);
}

double BK_TwoWaySupport(vector<int>& var1, vector<int>& var2)
{
	double tp = Support(var1, 1, var2, 1);
	double ep = Support(var1, 1) * Support(var2, 1);
	if (ep == 0) return 0;
	else return tp*log(tp / ep);
}

double BK_SCWS(vector<int>& var1, vector<int>& var2)
{
	int n = var1.size();
	double tp = Support(var1, 1, var2, 1);
	double ep = Support(var1, 1) * Support(var2, 1);
	if (ep == 0) return 0;
	else return n*tp*(tp - ep)*(tp - ep) / ep;
}

double BK_SimplifiedXstatistic(vector<int>& var1, vector<int>& var2)
{
	int n = var1.size();
	double tp = Support(var1, 1, var2, 1);
	double ep = Support(var1, 1) * Support(var2, 1);
	if (ep == 0) return 0;
	else return n*(tp - ep)*(tp - ep) / ep;
}

int BK_Distance(vector<int>& var1, vector<int>& var2)
{
	int ret = 0;
	int n = var1.size();
	for (int i = 0; i < n; i++)
	{
		if (var1[i] != var2[i])
			ret++;
	}
	return ret;
}

double BK_MI(vector<int>& var1, vector<int>& var2)
{
	map<int, int> var1_kind, var2_kind;

	int n = var1.size();
	for (int i = 0; i < n; i++)
	{
		if (var1_kind.count(var1[i]) == 0)
			var1_kind[var1[i]] = var1_kind.size();
		if (var2_kind.count(var2[i]) == 0)
			var2_kind[var2[i]] = var2_kind.size();
	}

	vector<int> var1_kind_num(var1_kind.size(), 0), var2_kind_num(var2_kind.size(), 0);
	for (int i = 0; i < var1.size(); i++)
	{
		int tp = var1_kind[var1[i]];
		var1_kind_num[tp] ++;
		tp = var2_kind[var2[i]];
		var2_kind_num[tp] ++;
	}

	double H1 = 0, H2 = 0;
	for (int i = 0; i < var1_kind.size(); i++)
	{
		double value = 1.0*var1_kind_num[i] / n;
		H1 -= value*log(value);
	}

	for (int i = 0; i < var2_kind.size(); i++)
	{
		double value = 1.0*var2_kind_num[i] / n;
		H2 -= value*log(value);
	}

	vector<int> temp(var2_kind.size(), 0);
	vector< vector<int> > join_count(var1_kind.size(), temp);
	for (int i = 0; i<n; i++)
	{
		int iv = var1_kind[var1[i]];
		int jv = var2_kind[var2[i]];
		join_count[iv][jv]++;
	}

	double result = 0;
	for (int k = 0; k<var1_kind.size(); k++)
	{
		for (int w = 0; w<var2_kind.size(); w++)
		{
			if (join_count[k][w] == 0) continue;
			double value = 1.0*join_count[k][w] / n;
			result += value*log(1.0*n*join_count[k][w] / var1_kind_num[k] / var2_kind_num[w]);
		}
	}
	if (H1 != 0 && H2 != 0)
	{
		return result /= min(H1, H2);
	}
	else return 0;
}