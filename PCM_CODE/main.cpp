#include <iostream>
#include <fstream>
#include <sstream>
#include "Interface.h"
using namespace std;
const int INF = 1 << 29;

int main(int argc, char **argv) /// exe  funcion input output thresod   (cc/order)
{
	if (argc == 4)
	{
		string function = argv[1];
		char *inputfile = argv[2];
		char *outputfile = argv[3];
	    if (function == "LOPCC")			LOPCC(inputfile, outputfile);
		else
		{
			cout << "There is no this funcion!!!" << endl;
			return 0;
		}
	}
	else if (argc == 5)
	{
		string function = argv[1]; 		
		char *inputfile = argv[2];
		char *outputfile = argv[3];
		double threshold = 0;
		stringstream ss(argv[4]);
		ss >> threshold;
		ss.clear();
		if (function == "MID")					MID(inputfile, outputfile, threshold);
		else if (function == "DiceC")			DiceC(inputfile, outputfile, threshold);
		else if (function == "JaccardC")		JaccardC(inputfile, outputfile, threshold);
		else if (function == "OverlapC")		OverlapC(inputfile, outputfile, threshold);
		else if (function == "CosineC")			CosineC(inputfile, outputfile, threshold);
		else if (function == "PearsonC")		PearsonC(inputfile, outputfile, threshold);
		else if (function == "SpearmanC")		SpearmanC(inputfile, outputfile, threshold);
		else if (function == "DotProductC")		DotProductC(inputfile, outputfile, threshold);
		else if (function == "KendallC")		KendallC(inputfile, outputfile, threshold);
		else if (function == "HoeffdingDC")	HoeffdingDC(inputfile, outputfile, threshold);
		else if (function == "SupportB")		SupportB(inputfile, outputfile, threshold);
		else if (function == "JaccardB")		JaccardB(inputfile, outputfile, threshold);
		else if (function == "InterestB")		InterestB(inputfile, outputfile, threshold);
		else if (function == "Piatetsky_ShapirosB")Piatetsky_ShapirosB(inputfile, outputfile, threshold);
		else if (function == "CosineB")			CosineB(inputfile, outputfile, threshold);
		else if (function == "ConfidenceB")		ConfidenceB(inputfile, outputfile, threshold);
		else if (function == "YulesQB")			YulesQB(inputfile, outputfile, threshold);
		else if (function == "YulesYB")			YulesYB(inputfile, outputfile, threshold);
		else if (function == "KappaB")			KappaB(inputfile, outputfile, threshold);
		else if (function == "J_MeasureB")		J_MeasureB(inputfile, outputfile, threshold);
		else if (function == "OddsRatioB")		OddsRatioB(inputfile, outputfile, threshold);
		else if (function == "GiniIndexB")		GiniIndexB(inputfile, outputfile, threshold);
		else if (function == "LaplaceB")		LaplaceB(inputfile, outputfile, threshold);
		else if (function == "ConvictionB")		ConvictionB(inputfile, outputfile, threshold);
		else if (function == "CertaintyFactorB")CertaintyFactorB(inputfile, outputfile, threshold);
		else if (function == "AddedValueB")		AddedValueB(inputfile, outputfile, threshold);
		else if (function == "CollectiveStrengthB")CollectiveStrengthB(inputfile, outputfile, threshold);
		else if (function == "KlosgenB")		KlosgenB(inputfile, outputfile, threshold);
		else if (function == "CoefficientB")	Phi_CoefficientB(inputfile, outputfile, threshold);
		else if (function == "ProbabilityRatioB")ProbabilityRatioB(inputfile, outputfile, threshold);
		else if (function == "LikelihoodRatioB")LikelihoodRatioB(inputfile, outputfile, threshold);
		else if (function == "TwoWaySupportB")	TwoWaySupportB(inputfile, outputfile, threshold);
		else if (function == "SCWSB")			SCWSB(inputfile, outputfile, threshold);
		else if (function == "SimplifiedXstatisticB")SimplifiedXstatisticB(inputfile, outputfile, threshold);
		else if (function == "BCPNNB")			BCPNNB(inputfile, outputfile, threshold, -1);
		else if (function == "SCWCCB")			SCWCCB(inputfile, outputfile, threshold, -1);
		else if (function == "CMI2NIC")			CMI2NIC(inputfile, outputfile, threshold, INF);
		else if (function == "CMI2NIB")			CMI2NIB(inputfile, outputfile, threshold, 1);
		else
		{
			cout << "There is no this funcion!!!" << endl;
			return 0;
		}
	}
	else if (argc == 6)
	{
		string function = argv[1];
		char *inputfile = argv[2];
		char *outputfile = argv[3];
		double threshold = 0;
		stringstream ss(argv[4]);
		ss >> threshold;
		ss.clear();
		if (function == "CMI2NIC" || function == "CMI2NIB")
		{
			int order = 0;
			stringstream ss(argv[5]);
			ss >> order;
			ss.clear();
			if (function == "CMI2NIC")			CMI2NIC(inputfile, outputfile, threshold, order);
			else if (function == "CMI2NIB")		CMI2NIB(inputfile, outputfile, threshold, order);
		}
		else if(function == "BCPNNB" || function == "SCWCCB")
		{
			double cc = 0;
			stringstream ss(argv[4]);
			ss >> cc;
			ss.clear();
			if (function == "BCPNNB")			BCPNNB(inputfile, outputfile, threshold, cc);
			else if (function == "SCWCCB")		SCWCCB(inputfile, outputfile, threshold, cc);
		}
		else
		{
			cout << "There is no this funcion!!!" << endl;
			return 0;
		}
	}
	else
	{
		cout << "There is no this funcion!!!" << endl;
		return 0;
	}
	return 0;
}



