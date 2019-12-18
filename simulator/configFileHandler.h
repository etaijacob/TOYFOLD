//configFileHandler.h

#ifndef CONFIG_FILE_HANDLER_HEADER
#define CONFIG_FILE_HANDLER_HEADER

#define LENGTH_OF_FILE_BUFFER	262144//131072//65536

#include "point.h"
#include <stdio.h>
#include "residue.h"
#include <fstream>

using namespace std;

//void computeRMSD2NativeStructureForDirectory(int argc, char **argv);
//void grabNativeStructuresFromDirectory(int argc, char **argv);
int getIntegerFromFile(char *sname, int idx);
int createDimer(int argc, char**argv);
int printStructureFromFile(int argc, char **argv);
bool recursiveIsExternalEdge(point p, int **matrix, int size);

class configFileHandler
{
public:
	char *buffer;//[LENGTH_OF_FILE_BUFFER];
	int currentArrayPosition;
	
	char fileName[100];
	int lengthOfText;
	configFileHandler(char *name, int sizeOfResidueArray, int index = 0);
	int init(char *name);
	configFileHandler(){};
	~configFileHandler();
	
	char* getHPconfiguration();
	char* getConfiguration(int sizeOfResidueArray, int index);
	int getStructureDBIndex(int sizeOfResidueArray, int index);
	int writeStructure2output(int sizeOfResidueArray, point *structure, char *confRes = 0);
	
	int writeContactMap2Output(int sizeOfResidueArray, point *structure, char *confRes = 0);

	int generateDimerTextStructure(int index1, int index2, 
												  int originalSize,
												  int linkerSize);

	char* readTextStructure(int sizeOfResidueArray, 
				  	      point *structure, 
				  		  int index);
	char* readTextStructureGivenSequence(int sizeOfResidueArray, 
				  						 point *structure, 
				  						 char *sequence, int minStructIdx);
	char* readDoubleDomainTextStructureGivenSequence(int sizeOfResidueArray, int domainSize, int linkerLength,
				  						 point *struct1, point *struct2, 
				  						 char *inseq, char *seq1, char *seq2, 
				  						 int minStructIdx);
	char* readTextStructureGivenSequenceAndThermoData(int sizeOfResidueArray, 
				  						 point *structure, 
				  						 char *sequence, char *addData, int minStructIdx);
	char* readTextStructureandNextDataLine(int sizeOfResidueArray, 
				  						 point *structure, char *addData,
				  						 int index);
	char* dimer_readTextStructure(int sizeOfResidueArray, 
				  						 		 point *structure, 
												 int linkerLength,
				  						 		 int index);
	int generateDimerTextStructureFromTwoFiles(int index1, int index2, 
												  int originalSize,
												  int linkerSize,
												  char *fn2);

	char* readUnknownLengthTextStructure(int maxSizeOfResidueArray, 
				  						 point *structure, 
				  						 int index, 
										 int *sizeOfCurrentArray);

	char* getChaperonData(int maxSizeOfResidueArray, 
				  		  point *structure, 
				  		  int index, 
				          int *sizeOfCurrentArray,
						  int **&modes,
						  int &numberOfModes,
						  char *&dynamics);

	char* getSmartChaperonData(int maxSizeOfResidueArray, 
				  		 	 point *structure, 
				  			 int index, 
							 int *sizeOfCurrentArray,
							 int **&modes,
							 int &numberOfModes,
							 char *&dynamics,
							 int **&sides,
			  				 char *&sideDynamics,		 
							 int &numberOfSides);

	int writeStructure2output(int sizeOfResidueArray, 
				  residueArray *structure); 

	int writeStructure2file(int sizeOfResidueArray, 
				point *structure, 
				char *confRes,
				ofstream &fo); 
				
	int writeStructure2file(int sizeOfResidueArray, 
			 										residueArray *structure, 
											 	  ofstream &of);
											 	  
	int readBinStructure(char *fn, point *structure, int idx);

	int getDataName(char *tmpstr, int &i);
	int getStructure(int &i, int *&sizeOfCurrentArray, point *&structure);

	int getModes(int &i, 
		     int sizeOfCurrentArray, 
		     int **&modes,		 
		     int &numberOfModes);	
	
	int getDynamics(int &i, char *&dynamics);
	
	int getSmart (int &i, 
		      int **&sides,
	     	      char *&dynamics,		 
		      int &numberOfSides);


};

#endif// CONFIG_FILE_HANDLER_HEADER
