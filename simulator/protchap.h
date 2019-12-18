//File name: protchap.h
#ifndef PROTCHAP_HEADER
#define PROTCHAP_HEADER

#include "point.h"
#include "randomNumberGenerator.h"
#include "localConformations.h"
#include "definitions.h"
#include "residue.h"
#include "configFileHandler.h"	
#include "utilities.h"			
	


class foldingArray: public residueArray
{
public:
	double energy;
	unsigned long stepNumber;
	
	foldingArray(int length):energy(0), stepNumber(0), residueArray(length) {}
	foldingArray(char *name):energy(0), stepNumber(0), residueArray(name) {}
	foldingArray(int length, char *name):energy(0), stepNumber(0), residueArray(length, name){}
	~foldingArray(){}	

};
class foldingComplex: public residueArray
{

public:
	
	static double energyMatrix[4][4];
	RMSD *rmsd;
	bool firstPassageTime;	
	randomNumberGenerator RNG;
	
	configFileHandler CfileHdlr;
	foldingArray bestFoldingArray;
	localConformations lc;
	int maxRangeOfLocalConf;
	int sideStructDBsize;
	
	char outputDatafileName[512];
	int structureDBIndex;
	int generalCounter;
	int added_confinedX, added_confinedY;
	bool isOnConfinedFold;
	double alphaE;
	int edgesProbability;
	
	foldingComplex(int length, char* confFileName, int useRMSD = 1);
	foldingComplex(char *name, char* confFileName);
	foldingComplex(int length, char *name, char* confFileName);
	foldingComplex(int length);
	
	~foldingComplex();
	
//Functions and Data structures to use for controling new folds 
//so no run down will occur:

//Assuming that on the average more run downs will occure,
//it is preferable to save new fold cordinates on additonal
//tmp array and if after all the process no rundowns occure than
//the additunal array is copied to the residue array.

	point* tmpArr;//[sizeOfResidueArray + 1];
	
//The boolean matrix is updated with occupied and non occupied (1, 0)
//cordinates of the folding Complex residue Array on the planner
 
	int** boolMatrix;//[top_y][right_x];
	
	double energy;
	
	//double bestEnergy;
	//residueArray bestResidueArray;
	
	
	double Ck;
	double simulationFactor;
	unsigned long successCtr;
	unsigned long enteringMCAnneal;
	unsigned long successLocalConf, enterLocalConf;
	
	void printBoolMatrix();
	void printHPMatrix();
	point getMin_dx_dy();
	point getMin_dx_dy(int pivot);
	point getMin_dx_dy(int pivot, int range);
	virtual int initFoldingComplex();
	
	inline bool isVacant(int residueArrayIndex)
	{
		return(!boolMatrix[res[residueArrayIndex].position.y][res[residueArrayIndex].position.x]);
	}
	
	
	inline bool isVacant(point p)
	{
		if( (p.x < left_x) || (p.x >= right_x) )
		{
			//cout<<"out of limits\n";
			return false;
		}
		if( (p.y < buttom_y) || (p.y >= top_y) )
		{
			//cout<<"out of limits\n";
			return false;
		}

		return (!boolMatrix[p.y][p.x]);
	}

	inline bool isVacant(int x, int y)
	{
		if( (x < left_x) || (x >= right_x) )
		{
			//cout<<"out of limits\n";
			return false;
		}
		if( (y < buttom_y) || (y >= top_y) )
		{
			//cout<<"out of limits\n";
			return false;
		}

		return (!boolMatrix[y][x]);
	}
	

	inline void occupyPosition(int residueArrayIndex)
	{
		boolMatrix[res[residueArrayIndex].position.y][res[residueArrayIndex].position.x]
			= residueArrayIndex;
	}
	
	inline void occupyPositionByTmpArr(int tmpArrIndex)
	{
		boolMatrix[tmpArr[tmpArrIndex].y][tmpArr[tmpArrIndex].x] = tmpArrIndex;
	}
	
	inline void dismissPosition(int residueArrayIndex)
	{
		boolMatrix[res[residueArrayIndex].position.y][res[residueArrayIndex].position.x]
			&= 0;
	}
	 
	inline bool dismissPosition(point p) 
	{
		boolMatrix[p.y][p.x] &= 0;
		return true;
	}
		
	
	virtual double getEnergyValue(int x, int y, int i);
	
	
	
//application functions: 


	virtual int randLocalMod(int pivot);
	
	//modifies only the edge = tail of the array
	virtual int tailRotateLeft(int pivot);//0
	virtual int tailRotateRight(int pivot);//1
	virtual int tailRotate180(int pivot);//2
	
	//rotate from the residue after the pivot until the edge
	int fixedRotateLeft(int pivot);//3
	int fixedRotateRight(int pivot);//4
	int fixedRotate180(int pivot);//5
	
	int flipflopCorner(int pivot);//6	//cannot be a tail or a strait line, must be a corner
	
	bool outOfBorders(int pivot, int range);
	bool outOfBorders(int pivot);
	bool outOfBorders();
	
	int nonEdgeSegmentFold(int pivot, int segmentLen);
	
	
	

//user functions:
	int foldInBox();
	virtual int foldOnce();
	int fold(long times);
	int fold2RMSD(double times, int configfileIndex = 0);
	int fold2BestEngergyStruct(double times, 
							   int numOfSimulations, 
							   int configfileIndex);
	int fold2BestEngergyStructWithPairwiseRMSD(double times, 
										   	   int numOfSimulations, 
										   	   int configfileIndex);

	int foldOverStructures(double times, 
						   int numOfSimulations, 
						   int configfileIndex,
						   char* nameOfStructFile);
	
	
	virtual double calculateEnergy();
	virtual double calculateEnergy(int pivot);
	virtual double calculateEnergy(int pivot, int range);
	virtual bool MontaCarloAnnealing(double newE, double oldE);
	virtual int modifyBestFoldingArray();
	void printBestEnergyArray();
	int getStructFromDB(int idx);
	void DEBUG_lostRes();
	void DEBUG_outOfLimitRes();
	int foldAndAggregateParamsEachNStep(double times, int configfileIndex, int NStep);
	int foldAndPrintParamsEachNStep(double times, int NStep, int configfileIndex);
	int dwellTimeFold(double times, int configfileIndex, double rmsdDwell, int NStep);
	virtual int foldToMinimumEnergy(double times, 
				int numOfSimulations, 
				int configfileIndex);
	virtual int foldToMinimumEnergy(double times, 
					int numOfSimulations, 
					char *hp);
	
	

};
#endif //PROTCHAP_HEADER
