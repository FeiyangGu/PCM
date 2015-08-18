#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include "Interface.h"
using namespace std;
const int INF = 1 << 29;

void warning();

int main(int argc, char **argv) /// exe  funcion input output (thresod)   (cc/order)  (kind)  (k/r)
{
	srand(0);
	string function = argv[1];
	char *inputfile = argv[2];
	char *outputfile = argv[3];
	double threshold = 0;
	if (function == "LOPCC")
	{
		if (argc == 4) LOPCC(inputfile, outputfile);
		else
		{
			warning();
			return 0;
		}
	}
	else
	{
		if (argc < 5) 
		{
			warning(); return 0; 
		}
		stringstream ss(argv[4]);
		ss >> threshold;
		ss.clear();
		if (function == "CMI2NIC")
		{
			if (argc == 5) CMI2NIC(inputfile, outputfile, threshold);
			else if (argc == 6)
			{
				/* The default parameter is INF */
				int order = INF;
				ss.str(argv[5]);
				ss >> order; 
				ss.clear();
				CMI2NIC(inputfile, outputfile, threshold, order);
			}
			else
			{
				warning();
				return 0;
			}
		}
		else if (function == "CMI2NIB")
		{
			if (argc == 5) CMI2NIB(inputfile, outputfile, threshold);
			else if (argc == 6)
			{
				/* The default parameter is 1 */
				int order = 1;
				ss.str(argv[5]);
				ss >> order;
				ss.clear();
				CMI2NIB(inputfile, outputfile, threshold, order);
			}
			else
			{
				warning();
				return 0;
			}
		}
		else
		{
			if (function == "BCPNNB" || function == "SCWCCB")
			{
				double cc = -1;
				int kind = 0;
				double r = 2;
				if (argc == 6)
				{
					ss.str(argv[5]); ss >> cc;  ss.clear();
				}
				else if (argc == 7)
				{
					ss.str(argv[5]); ss >> kind; ss.clear();
					ss.str(argv[6]); ss >> r; ss.clear();
				}
				else if (argc == 8)
				{
					ss.str(argv[5]); ss >> cc;  ss.clear();
					ss.str(argv[6]); ss >> kind; ss.clear();
					ss.str(argv[7]); ss >> r; ss.clear();
				}
				else if (argc > 8)
				{
					warning(); return 0;
				}
				if (function == "BCPNNB")				    BCPNNB(inputfile, outputfile, threshold, cc, kind, r);
				else if (function == "SCWCCB")				SCWCCB(inputfile, outputfile, threshold, cc, kind, r);
				else
				{
					warning(); return 0;
				}
			}
			else
			{
				int kind = 0;
				int k = 5;
				double r = 2;
				int len = function.length();
				if (argc >= 6)
				{
					ss.str(argv[5]);
					ss >> kind; ss.clear();
				}
				if (argc == 7)
				{
					if (function[len - 1] == 'B')
					{
						ss.str(argv[6]);
						ss >> r; ss.clear();
					}
					else if(function[len - 1] == 'C')
					{
						ss.str(argv[6]);
						ss >> k; ss.clear();
					}
				}
				if (argc > 7 || (kind != 0 && kind != 1))
				{
					warning(); return 0;
				}
				if (function == "DiceC")			    DiceC(inputfile, outputfile, threshold, kind, k);
				else if (function == "JaccardC")		JaccardC(inputfile, outputfile, threshold, kind, k);
				else if (function == "OverlapC")		OverlapC(inputfile, outputfile, threshold, kind, k);
				else if (function == "CosineC")			CosineC(inputfile, outputfile, threshold, kind, k);
				else if (function == "PearsonC")		PearsonC(inputfile, outputfile, threshold, kind, k);
				else if (function == "SpearmanC")		SpearmanC(inputfile, outputfile, threshold, kind, k);
				else if (function == "DotProductC")		DotProductC(inputfile, outputfile, threshold, kind, k);
				else if (function == "KendallC")		KendallC(inputfile, outputfile, threshold, kind, k);
				else if (function == "HoeffdingDC")		HoeffdingDC(inputfile, outputfile, threshold, kind, k);

				else if (function == "MIB")					MIB(inputfile, outputfile, threshold, kind, r);
				else if (function == "SupportB")			SupportB(inputfile, outputfile, threshold, kind, r);
				else if (function == "JaccardB")			JaccardB(inputfile, outputfile, threshold, kind, r);
				else if (function == "InterestB")			InterestB(inputfile, outputfile, threshold, kind, r);
				else if (function == "Piatetsky_ShapirosB")	Piatetsky_ShapirosB(inputfile, outputfile, threshold, kind, r);
				else if (function == "CosineB")				CosineB(inputfile, outputfile, threshold, kind, r);
				else if (function == "ConfidenceB")			ConfidenceB(inputfile, outputfile, threshold, kind, r);
				else if (function == "YulesQB")				YulesQB(inputfile, outputfile, threshold, kind, r);
				else if (function == "YulesYB")				YulesYB(inputfile, outputfile, threshold, kind, r);
				else if (function == "KappaB")				KappaB(inputfile, outputfile, threshold, kind, r);
				else if (function == "J_MeasureB")			J_MeasureB(inputfile, outputfile, threshold, kind, r);
				else if (function == "OddsRatioB")			OddsRatioB(inputfile, outputfile, threshold, kind, r);
				else if (function == "GiniIndexB")			GiniIndexB(inputfile, outputfile, threshold, kind, r);
				else if (function == "LaplaceB")			LaplaceB(inputfile, outputfile, threshold, kind, r);
				else if (function == "ConvictionB")			ConvictionB(inputfile, outputfile, threshold, kind, r);
				else if (function == "CertaintyFactorB")	CertaintyFactorB(inputfile, outputfile, threshold, kind, r);
				else if (function == "AddedValueB")			AddedValueB(inputfile, outputfile, threshold, kind, r);
				else if (function == "CollectiveStrengthB")	CollectiveStrengthB(inputfile, outputfile, threshold, kind, r);
				else if (function == "KlosgenB")			KlosgenB(inputfile, outputfile, threshold, kind, r);
				else if (function == "Phi_CoefficientB")	Phi_CoefficientB(inputfile, outputfile, threshold, kind, r);
				else if (function == "ProbabilityRatioB")	ProbabilityRatioB(inputfile, outputfile, threshold, kind, r);
				else if (function == "LikelihoodRatioB")	LikelihoodRatioB(inputfile, outputfile, threshold, kind, r);
				else if (function == "TwoWaySupportB")		TwoWaySupportB(inputfile, outputfile, threshold, kind, r);
				else if (function == "SCWSB")				SCWSB(inputfile, outputfile, threshold, kind, r);
				else if (function == "SimplifiedXstatisticB")SimplifiedXstatisticB(inputfile, outputfile, threshold, kind, r);
				else
				{
					warning(); 
					return 0;
				}
			}
		}
	}
	return  0;
}



void warning()
{
	cout << "The parameters you input is not right!!!\n";
	return;
}