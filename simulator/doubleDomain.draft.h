//doubleDomain.h

//dimersChaperonComplex.h

#ifndef DOUBLEDOMAIN_H
#define DOUBLEDOMAIN_H

#include "protchap.h"


#define ERROR_FPT_THRESHOLD 0.0
#define ENERGY_BACK_GAP 2.5

class doubleDomain: public foldingComplex
{
public:
	
	// 0 - dimer, 1 - monomer A, 2 - monomer B
	foldingArray *BFA[3];
	double BFAerror[6];//0-RMSD, 1-pairdiff
	double BFAenergy[3];//energy without chaperone
	
	foldingArray *MINENERGY_BFA[3];
	double MINENERGY_BFAerror[6];//0-RMSD, 1-pairdiff
	double MINENERGY_BFAenergy[3];//energy without chaperone
	
	int fromto[4]; 
	
	int PIVOT;
	// The higher the temperature the higher the acceptence rate of movements
	// The lower the temperature the lower the acceptance rate of any movement
	double A_temperature;
	double B_temperature;
	double Linker_temperature;
	
	int modifyBestFoldingArray();
	
	doubleDomain(int length, char* confFileName,
			      int findex, char *cname);
	~doubleDomain();
	
	int foldDimer
		(double times, 
		 int numOfSimulations, 
		 int configfileIndex, 
		 int *fromtoIn);
										   
	double calculateMonomersEnergy(char which, double*);
	int initDoubleDomain();
	double getEnergyValue(int x, int y, int i);
	
	inline double doubleDomain::getLinkerTemperature()
	{
		return A_temperature + (PIVOT - from[2])*((B_temperature - A_temperature)/(from[3] - from[2])) 
	}
};

#endif
