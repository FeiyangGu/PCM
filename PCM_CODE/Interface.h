#pragma once

#include "BinMethod.h"
#include "ConMethod.h"


void CMI2NIC(char* inputfile, char *outputfile, double threshold, int order0 = 2);
void LOPCC(char* inputfile, char *outputfile);
void JaccardC(char* inputfile, char *outputfile, double threshold, int kind=0, int k=5);
void DiceC(char* inputfile, char *outputfile ,double threshold,  int kind=0, int k=5);
void OverlapC(char* inputfile, char *outputfile ,double threshold,  int kind=0, int k=5);
void CosineC(char* inputfile, char *outputfile ,double threshold,  int kind=0, int k=5);
void PearsonC(char* inputfile, char *outputfile ,double threshold,  int kind=0, int k=5);
void SpearmanC(char* inputfile, char *outputfile ,double threshold,  int kind=0, int k=5);
void DotProductC(char* inputfile, char *outputfile ,double threshold,  int kind=0, int k=5);
void KendallC(char* inputfile, char *outputfile ,double threshold,  int kind=0, int k=5);
void HoeffdingDC(char* inputfile, char *outputfile ,double threshold,  int kind=0, int k=5);

void CMI2NIB(char* inputfile, char *outputfile, double threshold, int order0 = 1);
void MIB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void SupportB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void JaccardB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void InterestB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void Piatetsky_ShapirosB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void CosineB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void ConfidenceB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void YulesQB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void YulesYB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void KappaB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void J_MeasureB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void OddsRatioB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void GiniIndexB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void LaplaceB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void ConvictionB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void CertaintyFactorB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void AddedValueB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void CollectiveStrengthB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void KlosgenB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void Phi_CoefficientB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void ProbabilityRatioB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void LikelihoodRatioB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void BCPNNB(char* inputfile, char *outputfile, double threshold, double cc, int kind = 0, double r = 2);
void SCWCCB(char* inputfile, char *outputfile, double threshold, double cc, int kind = 0, double r = 2);
void TwoWaySupportB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void SCWSB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);
void SimplifiedXstatisticB(char* inputfile, char *outputfile, double threshold, int kind = 0, double r = 2);


