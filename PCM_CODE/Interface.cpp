#include "Interface.h"

//Disperse
void MID(char* inputfile, char* outputfile, double threshold)
{
	MI(inputfile, outputfile, threshold);
}

//Continuous
void CMI2NIC(char* inputfile, char *outputfile, double threshold, int order0)
{
	CMI2NI(inputfile, outputfile, threshold, order0);
}

void LOPCC(char* inputfile, char *outputfile)
{
	LOPC(inputfile, outputfile);
}

void CosineC(char* inputfile, char *outputfile, double threshold)
{
	Con(inputfile, outputfile, threshold, CK_Cosin);
}

void DiceC(char* inputfile, char *outputfile, double threshold)
{
	Con(inputfile, outputfile, threshold, CK_Dice);
}

void JaccardC(char* inputfile, char *outputfile, double threshold)
{
	Con(inputfile, outputfile, threshold, CK_Jaccard);
}

void OverlapC(char* inputfile, char *outputfile, double threshold)
{
	Con(inputfile, outputfile, threshold, CK_Overlap);
}

void PearsonC(char* inputfile, char *outputfile, double threshold)
{
	Con(inputfile, outputfile, threshold, CK_Pearson);
}

void SpearmanC(char* inputfile, char *outputfile, double threshold)
{ 
	Con(inputfile, outputfile, threshold, CK_Spearman,true);
}

void DotProductC(char* inputfile, char *outputfile, double threshold)
{
	Con(inputfile, outputfile, threshold, CK_DotProduct);
}

void KendallC(char* inputfile, char *outputfile, double threshold)
{
	Con(inputfile, outputfile, threshold, CK_Kendall);
}

void HoeffdingDC(char* inputfile, char *outputfile, double threshold)
{
	Con(inputfile, outputfile, threshold, CK_HoeffdingD);
}


/// Binary
void CMI2NIB(char* inputfile, char *outputfile, double threshold, int order0)
{
	CMI2NI_BIN(inputfile, outputfile, threshold);
}

void SupportB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Support);
}

void JaccardB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Jaccard);
}

void InterestB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Interest);
}

void Piatetsky_ShapirosB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Piatetsky_Shapiros);
}

void CosineB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Cosine);
}

void ConfidenceB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Confidence);
}

void YulesQB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_YulesQ);
}

void YulesYB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_YulesY);
}

void KappaB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Kappa);
}

void J_MeasureB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_J_Measure);
}

void OddsRatioB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_OddsRatio);
}

void GiniIndexB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_GiniIndex);
}

void LaplaceB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Laplace);
}

void ConvictionB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Conviction);
}

void CertaintyFactorB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_CertaintyFactor);
}

void AddedValueB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_AddedValue);
}

void CollectiveStrengthB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_CollectiveStrength);
}

void KlosgenB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Klosgen);
}

void Phi_CoefficientB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_Phi_Coefficient);
}

void ProbabilityRatioB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_ProbabilityRatio);
}

void LikelihoodRatioB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_LikelihoodRatio);
}

void BCPNNB(char* inputfile, char *outputfile, double threshold, double cc)
{
	Bin(inputfile, outputfile, threshold, BK_BCPNN, cc);
}
void SCWCCB(char* inputfile, char *outputfile, double threshold, double cc)
{
	Bin(inputfile, outputfile, threshold, BK_SCWCC, cc);
}
void TwoWaySupportB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_TwoWaySupport);
}

void SCWSB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_SCWS);
}
void SimplifiedXstatisticB(char* inputfile, char *outputfile, double threshold)
{
	Bin(inputfile, outputfile, threshold, BK_SimplifiedXstatistic);
}

