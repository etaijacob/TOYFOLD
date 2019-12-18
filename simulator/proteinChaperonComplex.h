//proteinChaperonComplex.h
#ifndef PROTEINCHAPERONCOMPLEX_H
#define PROTEINCHAPERONCOMPLEX_H


#include "protchap.h"
#include "smartChaperone.h"
#include "chaperon.h"

#define USE_CHAPERON_WITH_POTENTIAL	1

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

											
#define UPDATE_INPUT_FILES(R)\
				{\
				double error = rmsd.compute(*this);\
				fprintf(rmsd_mcs, "%d %f\n", (R), error);\
				fprintf(rmsd_energy, "%d %f\n", (R), energy);\
				}		
													
#define CREATE_FILE(FN)		sprintf(tmpstr, "%s%s-%d-%d.data",\
									outputDatafileName,\
									datafn,\
									sizeOfResidueArray,\
									configfileIndex);\
							cout<<"Open file: "<<tmpstr<<"\n";\
							(FN) = fopen(tmpstr, "wb");\
							if(!(FN))\
							{\
								cout<<"ERROR - file opening (CREATE_FILE)\n";\
								exit(0);\
							}

#define UPDATE_PROTEIN_STRUCTURE \
							for(int i = 1; i <= sizeOfResidueArray; i++)\
							{\
								res[i].position.x = structure[i].x;\
								res[i].position.y = structure[i].y;\
								occupyPosition(i);\
							}
							
		
			
class proteinChaperonComplex: public foldingComplex
{
public:
	chaperon *chap;
	bool useZeroPotential;
	//bool firstPassageTime;
	proteinChaperonComplex(int length, char* confFileName, int findex, char *cname = 0, int isSmart = 0);
	proteinChaperonComplex(char *name, char* confFileName, int findex, char *cname = 0, int isSmart = 0);
	proteinChaperonComplex(int length, char *name, char* confFileName, int findex, char *cname = 0, int isSmart = 0);

	int cageProteinInChaperon();
	int cageProteinInChaperon(double energyThreshold);
		
	double getEnergyValue(int x, int y, int i);	
	void occupyChaperonPosition(int residueArrayIndex);
	int transformProtein(int dx, int dy);
	//int modifyBestFoldingArray();
	int foldInChaperon(double times, 
			int numOfSimulations, 
			int configfileIndex, 
			bool inChaperon,
			bool dynamic);
	
	int foldInChaperonWithBindReleaseMechanism
					   (double times, 
						int numOfSimulations, 
						int configfileIndex, 
						bool inChaperon,
						bool dynamic,
						int bindInterval,
		                int releaseinterval,
		                double energyThreshold);

	int unFoldInChaperonWithBindReleaseMechanism
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   bool inChaperon,
										   bool dynamic,
										   int bindInterval,
		                                   int releaseInterval,
		                                   double energyThreshold,
								    	   int sampleRate);

int unFoldThreshInChaperonWithBindReleaseMechanism
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   bool inChaperon,
										   bool dynamic,
										   int bindInterval,
		                                   int releaseInterval,
		                                   double energyThreshold,
								    	   int sampleRate,
										   double threshold);
#if 0 										   
int dimer_foldInChaperonWithBindReleaseMechanism
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   int *fromto,
										   bool inChaperon,
										   bool dynamic,
										   int bindInterval,
		                                   int releaseInterval,
		                                   double energyThreshold);
#endif
	int writeStructures2output();
	
	double calculateEnergyWithoutChaperon();
	double getEnergyValueWithoutChaperon(int x, int y, int i);
	int releaseProteinFromChaperon();
	
};

#endif
