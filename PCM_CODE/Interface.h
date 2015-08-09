#pragma once

#include "BinMethod.h"
#include "ConMethod.h"
#include "DisMethod.h"

void MID(char* inputfile, char* outputfile, double threshold);

void CMI2NIC(char* inputfile, char *outputfile, double threshold, int order0 = 2);
void LOPCC(char* inputfile, char *outputfile);
void JaccardC(char* inputfile, char *outputfile, double threshold);
void DiceC(char* inputfile, char *outputfile, double threshold);
void OverlapC(char* inputfile, char *outputfile, double threshold);
void CosineC(char* inputfile, char *outputfile, double threshold);
void PearsonC(char* inputfile, char *outputfile, double threshold);
void SpearmanC(char* inputfile, char *outputfile, double threshold);
void DotProductC(char* inputfile, char *outputfile, double threshold);
void KendallC(char* inputfile, char *outputfile, double threshold);
void HoeffdingDC(char* inputfile, char *outputfile, double threshold);

void CMI2NIB(char* inputfile, char *outputfile, double threshold, int order0 = 1);
void SupportB(char* inputfile, char *outputfile, double threshold);
void JaccardB(char* inputfile, char *outputfile, double threshold);
void InterestB(char* inputfile, char *outputfile, double threshold);
void Piatetsky_ShapirosB(char* inputfile, char *outputfile, double threshold);
void CosineB(char* inputfile, char *outputfile, double threshold);
void ConfidenceB(char* inputfile, char *outputfile, double threshold);
void YulesQB(char* inputfile, char *outputfile, double threshold);
void YulesYB(char* inputfile, char *outputfile, double threshold);
void KappaB(char* inputfile, char *outputfile, double threshold);
void J_MeasureB(char* inputfile, char *outputfile, double threshold);
void OddsRatioB(char* inputfile, char *outputfile, double threshold);
void GiniIndexB(char* inputfile, char *outputfile, double threshold);
void LaplaceB(char* inputfile, char *outputfile, double threshold);
void ConvictionB(char* inputfile, char *outputfile, double threshold);
void CertaintyFactorB(char* inputfile, char *outputfile, double threshold);
void AddedValueB(char* inputfile, char *outputfile, double threshold);
void CollectiveStrengthB(char* inputfile, char *outputfile, double threshold);
void KlosgenB(char* inputfile, char *outputfile, double threshold);
void Phi_CoefficientB(char* inputfile, char *outputfile, double threshold);
void ProbabilityRatioB(char* inputfile, char *outputfile, double threshold);
void LikelihoodRatioB(char* inputfile, char *outputfile, double threshold);
void BCPNNB(char* inputfile, char *outputfile, double threshold, double cc);
void SCWCCB(char* inputfile, char *outputfile, double threshold, double cc);
void TwoWaySupportB(char* inputfile, char *outputfile, double threshold);
void SCWSB(char* inputfile, char *outputfile, double threshold);
void SimplifiedXstatisticB(char* inputfile, char *outputfile, double threshold);

