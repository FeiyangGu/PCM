#pragma once

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <assert.h>
#include <map>
#include <Eigen/Dense> 
#include "DataStruct.h"
using namespace std;
using namespace Eigen;
using namespace Eigen::internal;
using namespace Eigen::Architecture;

vector <RecordB>  ReadBinData(char * inputfile);
vector <RecordB>  ReadDisData(char * inputfile);
vector <RecordC>  ReadConData(char * inputfile);
double Support(vector<int>& var1, int var1v);
double Support(vector<int>& var1, int var1v, vector<int>& var2, int var2v);
double SupCond(vector<int>& var1, int var1v, vector<int>& var2, int var2v);
MatrixXd Covar(const MatrixXd &mat);