#include "Interface.h"


//Continuous
void CMI2NIC(char* inputfile, char *outputfile, double threshold, int order0)
{
	CMI2NI(inputfile, outputfile, threshold, order0);
}

void LOPCC(char* inputfile, char *outputfile)
{
	LOPC(inputfile, outputfile);
}

void JaccardC(char* inputfile, char *outputfile, double threshold, int kind, int k)
{
	Con(inputfile, outputfile, threshold, CK_Jaccard, kind, k);
}
void DiceC(char* inputfile, char *outputfile, double threshold, int kind, int k)
{
	Con(inputfile, outputfile, threshold, CK_Dice, kind, k);
}
void OverlapC(char* inputfile, char *outputfile, double threshold, int kind, int k)
{
	Con(inputfile, outputfile, threshold, CK_Overlap, kind, k);
}
void CosineC(char* inputfile, char *outputfile, double threshold, int kind, int k)
{
	Con(inputfile, outputfile, threshold, CK_Cosin, kind, k);
}
void PearsonC(char* inputfile, char *outputfile, double threshold, int kind, int k)
{
	Con(inputfile, outputfile, threshold, CK_Pearson, kind, k);
}
void SpearmanC(char* inputfile, char *outputfile, double threshold, int kind, int k)
{
	Con(inputfile, outputfile, threshold, CK_Spearman, kind, k);
}
void DotProductC(char* inputfile, char *outputfile, double threshold, int kind, int k)
{
	Con(inputfile, outputfile, threshold, CK_DotProduct, kind, k);
}
void KendallC(char* inputfile, char *outputfile, double threshold, int kind, int k)
{
	Con(inputfile, outputfile, threshold, CK_Kendall, kind, k);
}
void HoeffdingDC(char* inputfile, char *outputfile, double threshold, int kind, int k)
{
	Con(inputfile, outputfile, threshold, CK_HoeffdingD, kind, k);
}


/// Binary

void CMI2NIB(char* inputfile, char *outputfile, double threshold, int order0)
{
	CMI2NI_BIN(inputfile, outputfile, threshold);
}



void MIB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_MI, kind, r);
}
void SupportB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Support, kind, r);
}
void JaccardB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Jaccard, kind, r);
}
void InterestB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Interest, kind, r);
}
void Piatetsky_ShapirosB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Piatetsky_Shapiros, kind, r);
}
void CosineB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Cosine, kind, r);
}
void ConfidenceB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Confidence, kind, r);
}
void YulesQB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_YulesQ, kind, r);
}
void YulesYB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_YulesY, kind, r);
}
void KappaB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Kappa, kind, r);
}
void J_MeasureB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_J_Measure, kind, r);
}
void OddsRatioB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_OddsRatio, kind, r);
}
void GiniIndexB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_GiniIndex, kind, r);
}
void LaplaceB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Laplace, kind, r);
}
void ConvictionB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Conviction, kind, r);
}
void CertaintyFactorB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_CertaintyFactor, kind, r);
}
void AddedValueB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_AddedValue, kind, r);
}
void CollectiveStrengthB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_CollectiveStrength, kind, r);
}
void KlosgenB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Klosgen, kind, r);
}
void Phi_CoefficientB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_Phi_Coefficient, kind, r);
}
void ProbabilityRatioB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_ProbabilityRatio, kind, r);
}
void LikelihoodRatioB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_LikelihoodRatio, kind, r);
}
void BCPNNB(char* inputfile, char *outputfile, double threshold, double cc, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_BCPNN ,cc, kind, r);
}
void SCWCCB(char* inputfile, char *outputfile, double threshold, double cc, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_SCWCC, cc, kind, r);
}
void TwoWaySupportB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_TwoWaySupport, kind, r);
}
void SCWSB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_SCWS, kind, r);
}
void SimplifiedXstatisticB(char* inputfile, char *outputfile, double threshold, int kind, double r)
{
	Bin(inputfile, outputfile, threshold, BK_SimplifiedXstatistic, kind, r);
}

