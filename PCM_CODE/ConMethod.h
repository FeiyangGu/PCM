#pragma once

#include "Function.h"

///  Continuous Variable
void CMI2NI(char* inputfile, char *outputfile, double threshold, int order0 = 1);
void LOPC(char* inputfile, char *outputfile);

void Con(char* inputfile, char* outputfile, double threshold, double(*method) (vector<double>& var1, vector<double>& var2), int kind=0, int k=5);

/// This is funcion is for the measures that need to rank the elements of variables. 
void Con(char* inputfile, char* outputfile, double threshold, double(*method) (vector<double>& var1, vector<double>& var2), bool isrank, int kind=0, int k=5);

double CK_Dice(vector<double>& var1, vector<double>& var2);
double CK_Jaccard(vector<double>& var1, vector<double>& var2);
double CK_Overlap(vector<double>& var1, vector<double>& var2);
double CK_Cosin(vector<double>& var1, vector<double>& var2);
double CK_Pearson(vector<double>& var1, vector<double>& var2);
double CK_Spearman(vector<double>& var1, vector<double>& var2);
double CK_DotProduct(vector<double>& var1, vector<double>& var2);
double CK_Kendall(vector<double>& var1, vector<double>& var2);
double CK_Distance(vector<double>& var1, vector<double>& var2);
double CK_HoeffdingD(vector<double>& var1, vector<double>& var2);
