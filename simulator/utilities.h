//utilities.h

#ifndef UTILITIES_HEADER	
#define UTILITIES_HEADER	

#include "residue.h"

#define PRINT_DEBUG		0
#define PRINT_DEBUG2	0

#define ABS(X)	((double)((X) > 0 ? (X) : (-(X))))
#define ABS_INT(X)	(((X) > 0 ? (X) : (-(X))))

#define SIZE_OF_NUM_STATISTICS_BUFFER	16384
#define MAX_STRUCTURES					25


double getAverageMCS2NativeStructureFromFile(char *fnameStruct, char *fnameMCS, 
									point *structure, char *seqMode);
double getAverageRMSD2NativeStructureFromFile(char *fnameStruct, point *structure, char*seqMode);
double getPearsonCorrelation(double N, double *dataX, double *dataY);
int findFileInDir(char* name, char* fileFounded, char* substr);
double getFractionOfFolded2Native(char *fnameStruct, char *fnameMCS, 
									point *structure, char *dstfname, char *seqMode);

int getRMSD2NativeStructureFromFile(char *fnameStruct, char *fnameMCS, 
									point *structure, char *dstfname, 
									char *seqMode = 0);
int grabNativeStructureFromSimulationsFile(char *fname, double threshold, char *seqMode = 0);
double getStrongInteractionLocalityIndex(int sizeOfResidueArray, 
										 point *structure, 
										 char *hp, 
										 int segmentWidth = 0);

double getLocalityIndex(int size, point *structure, char*hp);
int writeStructure2output(int sizeOfResidueArray, 
						  point *structure, 
						  char *confRes);
int getMatrixBounds(int **matrix, int sizeOfResidueArray, int *Xmin, int *Xmax, int *Ymin, int
		*Ymax);
int getStructFromDB(int idx, point *structure, int sizeOfResidueArray, int sideStructDBsize);
int getConfigurationIndexFromFile(char *fname, int index);
double CO(int N, point *pArr);
/*
Pair Wise Distance
*/
class PWD
{
public:
		/*int*/double* pairDistanceArray;
	    long length;
		int N;//begins from 1 to N+1
		
		PWD(int chainLength);
		~PWD();
		
		unsigned long countPairCombinations();
		virtual double compute(residueArray *resArr);
		double compute(point *pArr);
		
};			

/*
Pair Wise Distance Average
*/
class PWDA: public PWD
{
public:
		PWDA(int chainLength);
		
		
		double compute(residueArray *resArr);

};

class RMSD
{
public:
		PWD src;
		int N;//=chainLength + 1
		
		int pairsDiffCtr;

		int maxStructures;
		point **structures;
		double **rmsdResults;
		
		RMSD(residueArray* resArr, int chainLength, int maxStructures = MAX_STRUCTURES);
		RMSD(point* pArr, int chainLength, int maxStructures = MAX_STRUCTURES);
		~RMSD();
		
		int update(residueArray* resArr);
		int update(point* pArr);
		
		double computeNativePairDiff(residueArray& resArr);
		double compute(residueArray& resArr);
		double compute(point* pArr);
		
		double dimer_compute(point* pArr, int from1, int to1, int from2, int to2);
		double dimer_compute(residueArray& resArr, int from1, int to1, int from2, int to2);
		double dimer_compute(point* pArr, int from1, int to1, int from2, int to2, double *ddd);
		double dimer_compute(residueArray& resArr, int from1, int to1, int from2, int to2, double *ddd);
		
		void pairwiseCompute(int size, double *results, double *pairdiffs = 0);
		void pairwiseCompute(char *name, int *structureDBindexs, int size, double *results);

		double getPairErrorPercent();	
};


/*
Same as PWD but computes each axe 
alone for the benefit of 2D plots.
*/
class PWD_XY
{
public:
		int* pairDistanceArrayX;
		int* pairDistanceArrayY;
		unsigned long length;
		int N;//begins from 1 to N+1
		
		PWD_XY(int chainLength);
		~PWD_XY();
		
		unsigned long countPairCombinations();
		void compute(residueArray *resArr);
		
		
};			


/*
Same as RMSD but computes each axe 
alone for the benefit of 2D plots.
*/
class RMSD_XY
{
public:
		PWD_XY src;
		int N;//=chainLength + 1
		
		RMSD_XY(residueArray* resArr, int chainLength);
		~RMSD_XY(){} 
		
		bool compute(residueArray& resArr, double& accX, double& accY);	
};
/*
class statistics
{
public:
		
	double mean, variance;
	FILE* fp;
	int compute4dir(char* name, char* dstFilePrefix, char* substr);
	int compute4file(char* name, FILE* dfp0, FILE* dfp1);
	int compute4file(char* name, double *statisticX, double *statisticY);
	int compute4file(int index, char* dirname, char *substr, 
			double *statisticX, double *statisticY);
	
};
*/
class sortedStack
{
public:
	double *items;
	int *dataIndex;
	int currentSize, maxSize;
	
	sortedStack(int sizeOfStack);
	~sortedStack()
	{
		delete []items;	
		delete []dataIndex;
	}
	
	int insert(double value, int dataIndexValue);
	int getLowestItemIndex();
	int isUnique(int itemIdx = -1);
	void print();	
		
};

#endif
