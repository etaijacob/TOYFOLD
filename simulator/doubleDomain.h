//doubleDomain.h

#ifndef DOUBLEDOMAIN_H
#define DOUBLEDOMAIN_H

#include "protchap.h"

#define ERROR_FPT_THRESHOLD 0.0
#define ENERGY_BACK_GAP 2.5

#define UPDATE_PROTEIN_MODES(RES) 	for(int i = 1; i <= sizeOfResidueArray; i++)\
								{\
									switch(hp[i-1])\
									{\
										case 'H':\
											(RES)[i].mode = HYDROPHOBIC; break;\
 										case 'P':\
											(RES)[i].mode = POLAR_NEUTRAL; break;\
 										case '+':\
											(RES)[i].mode = POSITIVE_CHARGE; break;\
										case '-':\
											(RES)[i].mode = NEGATIVE_CHARGE; break;\
									}		\
								}

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
	
	int fromto[4]; //1 indexing
	
	doubleDomain(int length, int* fromtoIn);
	~doubleDomain();
	
	int initFoldingComplex();
	double getSingleDomainEnergyValue(int x, int y, int i, int from, int to);
	double calculateMonomersEnergy(char which, double*);
	double getEnergyValue(int x, int y, int i);
	int modifyBestFoldingArray();//TODO: RMSD analysis
	
	
	virtual int foldToMinimumEnergy(double times, 
													int numOfSimulations, 
													char *hp);
					
};

#endif
