#pragma once

#include "Function.h"

///  Binary Variable
void CMI2NI_BIN(char* inputfile, char *outputfile, double threshold, int order0 = 1);
void Bin(char* inputfile, char* outputfile, double threshold, double(*method) (vector<int>& var1, vector<int>& var2), int kind=0, double r = 2);
void Bin(char* inputfile, char* outputfile, double threshold, double(*method) (vector<int>& var1, vector<int>& var2, double cc), double cc, int kind=0, double r = 2);


double BK_MI(vector<int>& var1, vector<int>& var2);
double BK_Support(vector<int>& var1, vector<int>& var2);
double BK_Jaccard(vector<int>& var1, vector<int>& var2);
double BK_Interest(vector<int>& var1, vector<int>& var2);
double BK_Piatetsky_Shapiros(vector<int>& var1, vector<int>& var2);
double BK_Cosine(vector<int>& var1, vector<int>& var2);
double BK_Confidence(vector<int>& var1, vector<int>& var2);
double BK_YulesQ(vector<int>& var1, vector<int>& var2);
double BK_YulesY(vector<int>& var1, vector<int>& var2);
double BK_Kappa(vector<int>& var1, vector<int>& var2);
double BK_J_Measure(vector<int>& var1, vector<int>& var2);
double BK_OddsRatio(vector<int>& var1, vector<int>& var2);
double BK_GiniIndex(vector<int>& var1, vector<int>& var2);
double BK_Laplace(vector<int>& var1, vector<int>& var2);
double BK_Conviction(vector<int>& var1, vector<int>& var2);
double BK_CertaintyFactor(vector<int>& var1, vector<int>& var2);
double BK_AddedValue(vector<int>& var1, vector<int>& var2);
double BK_CollectiveStrength(vector<int>& var1, vector<int>& var2);
double BK_Klosgen(vector<int>& var1, vector<int>& var2);
double BK_Phi_Coefficient(vector<int>& var1, vector<int>& var2);
double BK_ProbabilityRatio(vector<int>& var1, vector<int>& var2);
double BK_LikelihoodRatio(vector<int>& var1, vector<int>& var2);
double BK_BCPNN(vector<int>& var1, vector<int>& var2, double cc);
double BK_SCWCC(vector<int>& var1, vector<int>& var2, double cc);
double BK_TwoWaySupport(vector<int>& var1, vector<int>& var2);
double BK_SCWS(vector<int>& var1, vector<int>& var2);
double BK_SimplifiedXstatistic(vector<int>& var1, vector<int>& var2);
int BK_Distance(vector<int>& var1, vector<int>& var2);