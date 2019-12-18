//dimersChaperonComplex.h

#ifndef DIMERSCHAPERONCOMPLEX_H
#define DIMERSCHAPERONCOMPLEX_H

#include "proteinChaperonComplex.h"


#define ERROR_FPT_THRESHOLD 0.0
#define ENERGY_BACK_GAP 2.5

class dimersChaperonComplex: public proteinChaperonComplex
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
	int modifyBestFoldingArray();
	
	dimersChaperonComplex(int length, char* confFileName,
			      int findex, char *cname, int isSmart = 0);
	~dimersChaperonComplex();
	
	int foldOneDomainInDimer
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   int *fromtoIn);
	int foldDimer
		(double times, 
		 int numOfSimulations, 
		 int configfileIndex, 
		 int *fromtoIn);
										   
	int foldInChaperonWithBindReleaseMechanism
		(double times, 
		 int numOfSimulations, 
		 int configfileIndex, 
		 int *fromto,
		 bool inChaperon,
		 bool dynamic,
		 int bindInterval,
		 int releaseInterval,
		 double energyThreshold,
		 int addedX = 3,
		 int addedY = 3);

	double calculateMonomersEnergy(char which, double*);
	int initFoldingComplex();
	double getEnergyValue(int x, int y, int i);
};

#endif
