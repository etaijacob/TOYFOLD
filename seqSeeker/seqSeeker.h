//seqSeeker.h
#ifndef SEQ_SEEKER_HEADER
#define SEQ_SEEKER_HEADER

#include "seqPermutation.h"
#include "../simulator/point.h"
#include "../simulator/residue.h"
//#include "../sharedLibs/configFileHandler.h"

class seqStatistics
{
public:
	double expectation;
	double variance;
	double max, min;
	int maxStructIndex, minStructIndex;
	int numInLowRange;
	void print();

};
	
	

class seqSeeker
{
public:
	seqPermutation sp;
	seqStatistics currStatistics;
	int seqLength;	

	residueArray** bestSeqs;
	seqStatistics* bestSeqsStatistics;
	int maxBestSeqs;
	
	point** structureDB;
	int sizeOfDB;
	int currentStructIdx;
	
	int** matrix;
	int lowRangeCounterTres;
	double* eng;
	
	seqSeeker(int length, int maxBest, int lrc = 5);
	seqSeeker(int length, int maxBest, int sideadd, char*name, int lrc = 5);
	seqSeeker(int length, int maxBest, int sideadd, int lrc = 5);
	seqSeeker(int length, int maxBest, char *inf);
	~seqSeeker();
	
	double calculateEnergy();
	double getEnergyValue(int x, int y, int i);
	int computeSeqThroughDB();
	int computeSeqThroughDB(char* confFileName, int configfileIndex);
	int computeAllSeqThroughDB(char* fileName, int sizeOfResidueArray);
	int computeIndexedSeqThroughDB(char* fileName, int sizeOfResidueArray, char *indexFileName);
	int computeAllSeqThroughDBdeviations(char* fileName, int sizeOfResidueArray);
	int computeIndexedSeqThroughDBdeviations(char* fileName, int sizeOfResidueArray, char *indexFileName);
	int computeEnergyLandscape(char* fileName, int sizeOfResidueArray, int configFileIndex);
	int getLowestEnergyStructures(int numOfLowEnergyStruct);
	void printCurrent(int structIdx);
	int countExternalEdges4AllresiduesPro(point *structure, int originalSize, double *edgeCnt);
	bool recursiveIsExternalEdge(point p, int **matrix, int size);


	
	void countDB4externalEdges();
	int countExternalEdges(point *structure1, double &edgeCnt1, double &edgeCnt2);
	void countDB4AllexternalEdges();
	int countExternalEdges4Allresidues(point *structure1, double *edgeCnt);
	void printDBasText(char *fileName);


};
	

#endif//SEQ_SEEKER_HEADER
