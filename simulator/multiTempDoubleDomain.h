//multiTempDoubleDomain.h

#ifndef MULTITEMPDOUBLEDOMAIN_H
#define MULTITEMPDOUBLEDOMAIN_H

#include "doubleDomain.h"

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

class multiTempDoubleDomain: public doubleDomain
{
public:
		
	int currentSimulationPivot; // 1 indexing
	int currentMoveSize; // 1 indexing
	int domainInFocus; // 0 - NA, 1 - A, 2 - B, 3 - AB
	int fromFocus;
	int toFocus;
	int fromNotInFocus;
	int toNotInFocus;
	int domainInFocusItr;
	int domainInFocusMCS;
	bool enableInteractionsBetweenDomains;
	int anyInterDomainInteractions;
	int successfulInterDomainInteractions;
	int collisionsWithDomainNotInFocus;
	
	double energyA;
	double energyB;
	
	int intraContacts1[4][4], intraContacts2[4][4], interContacts[4][4], linkerContacts1[4][4], linkerContacts2[4][4];
	int saltBridgeInteractions;
	
	bool confine;
	int confineXsize;
	int confineYsize;
	bool wasOutOfConfinedRegion;
	int collisionsWithConfinment;
	bool preConfinement;
	
	double *sequenceTemperature;//size of residueArray + 1;
	double *perturbationFactor;
	double domain_A_temp;
	double domain_B_temp;
	double domain_A_perturbation;
	double domain_B_perturbation;
	point *domain_A_struct;
	point *domain_B_struct;
	char whichDomainToAssign;
	
	multiTempDoubleDomain(int length, int* fromtoIn, double domain_A_tempIn, double domain_B_tempIn, double Aperturb, double Bperturb, 
												int domainInFocus, bool enableInteractionsBetweenDomains, bool confineIn, int confineXsizeIn, int confineYsizeIn);
	multiTempDoubleDomain(int length, int* fromtoIn, double domain_A_tempIn, double domain_B_tempIn, double Aperturb, double Bperturb, 
												point *domain_struct, char whichDomain, int domainInFocus, bool enableInteractionsBetweenDomains,
												bool confineIn, int confineXsizeIn, int confineYsizeIn);
	multiTempDoubleDomain(int length, int* fromtoIn, double domain_A_tempIn, double domain_B_tempIn, double Aperturb, double Bperturb, 
												point *domain_struct1, point *domain_struct2, char whichDomain, int domainInFocusIn, 
												bool enableInteractionsBetweenDomainsIn, bool confineIn, int confineXsizeIn, int confineYsizeIn);

	~multiTempDoubleDomain();
	
	void countSingleInteraction(int x, int y, int i, int state1);
	void calculateMoveContactStatistics();
	
	int modifyBestFoldingArray();
	int initParameters();
	int initFoldingComplex();	
	int foldOnce();
	void updateEnergiesByDomains();
	bool MonteCarloAnnealingByDomain(bool wasInFocus);
	bool MontaCarloAnnealing(double newE, double oldE, bool wasInFocus);
	int assignDomainStructs(char whichDomain);
	void getDomainInFocusStruct(point *mystruct);
	
	int FoldAndPrintDwellTime(double times, 
										   			int numOfSimulations, 
										   			char *hp,
										   			double rmsdDwell,
										   			bool breaking);
										   
	int foldToMinimumEnergy(double times, 
										   		int numOfSimulations, 
										   		char *hp);

	int randLocalMod(int pivot);
	
	//modifies only the edge = tail of the array
	int tailRotateLeft(int pivot);//0
	int tailRotateRight(int pivot);//1
	int tailRotate180(int pivot);//2
	
private:
	
	bool haveInteractionWithDomainInFocus();
	bool movementIncludesDomainInFocus();
	bool hasCollisionWithDomainNotInFocus(point p);
	bool movementIncludesLinker();
	
	point getMaxDistInMovement();
	point getMaxDist();
	bool recursiveOccupyPositions(int from, int to, point p);
	bool reverseRecursiveOccupyPositions(int from, int to, point p);
	int initTemperature(double Atemp, double Btemp, double Aperturb, double Bperturb);
					
	inline bool dismissPositionAndResidueArray(point p, int residueArrayIndex) 
	{
		boolMatrix[p.y][p.x] &= 0;
		return true;
	}
	
	inline bool occupyAndAssignIfVacant(int x, int y, int residueArrayIndex)
	{
// 		cout<<x<<", "<<y<<" "<<residueArrayIndex<<endl;
		if( (x < left_x) || (x >= right_x) )
		{
// 			cout<<"out of limits\n";
			return false;
		}
		if( (y < buttom_y) || (y >= top_y) )
		{
// 			cout<<"out of limits\n";
			return false;
		}
		
		if(!boolMatrix[y][x]) {
// 			cout<<"not bool??? "<<boolMatrix[y+1][x]<<endl;
// 			if(y < top_y - 1 && boolMatrix[y + 1][x] > 0 && (boolMatrix[y + 1][x] - residueArrayIndex > 2 || boolMatrix[y + 1][x] - residueArrayIndex < -2))
// 				return false;
// 				cout<<"not bool??? "<<boolMatrix[y-1][x]<<endl;
// 			if(y > buttom_y && boolMatrix[y - 1][x] > 0 && (boolMatrix[y - 1][x] - residueArrayIndex > 2 || boolMatrix[y - 1][x] - residueArrayIndex < -2))
// 				return false;
// 				cout<<"not bool??? "<<boolMatrix[y][x+1]<<endl;
// 			if(x < right_x -1 && boolMatrix[y][x + 1] > 0 && (boolMatrix[y][x + 1] - residueArrayIndex > 2 || boolMatrix[y][x + 1] - residueArrayIndex < -2))
// 				return false;
// 				cout<<"not bool??? "<<boolMatrix[y][x-1]<<endl;
// 			if(x > left_x && boolMatrix[y][x - 1] > 0 && (boolMatrix[y][x - 1] - residueArrayIndex > 2 || boolMatrix[y][x - 1] - residueArrayIndex < -2))
// 				return false;
			
			res[residueArrayIndex].position.x = x;
			res[residueArrayIndex].position.y = y;
			occupyPosition(residueArrayIndex);
			return true;
		}
		return false;
	}
	
	inline bool dismissPositionIfRelevant(point p, int index) 
	{
		if(boolMatrix[p.y][p.x] == index)
			boolMatrix[p.y][p.x] &= 0;
		return true;
	}
};

#endif
