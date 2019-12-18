//main.cpp

#include "protchap.h"
#include "doubleDomain.h"
/*#include "multiTempDoubleDomain.h"*/

#include "point.h"
#include "configFileHandler.h"
#include "utilities.h"

#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std; 

void getCOsOfSingleDomains(int argc, char**argv);
int foldAndAggregate(int argc, char**argv);
int dwellTimeFold(int argc, char**argv);
int foldAndPrint(int argc, char**argv);
int freeFoldSingleDomain(int argc, char**argv);
void getRMSDs2nativeSingleDomains(int argc, char **argv);
int generateDoubleDomainStructure(int argc, char**argv);
int freeFoldDoubleDomain(int argc, char**argv);
void getRMSDs2nativeDoubleDomains(int argc, char **argv);
int freeFoldMultiTempDoubleDomain(int argc, char**argv);
void getSingleDomainContactMapAndThermoData(int argc, char **argv);
int dwellTimeFoldMultiTempDoubleDomain(int argc, char **argv);

int main(int argc, char **argv)
{
  if(argc < 2) {
    cout<<"programs available:\n-foldAndAggregate\n-dwellTimeFold\n-foldAndPrint\n-freeFold\n-RMSDsingle\n-RMSDdouble\n-generateDouble\n-freeFoldDouble\n-getSingleDomainContactMap\n-getCOsOfSingleDomains\n\n";
    exit(0);
  }
  /*
	if(argc < 2) {
		cout<<"programs available:\n-foldAndAggregate\n-dwellTimeFold\n-foldAndPrint\n-freeFold\n-RMSDsingle\n-RMSDdouble\n-generateDouble\n-freeFoldDouble\n-freeFoldMultiTempDouble\n-getSingleDomainContactMap\n-getCOsOfSingleDomains\n-dwellTimeFoldMultiTempDoubleDomain\n";
		exit(0);
	}*/ /*
	if(strcmp(argv[1], "-dwellTimeFoldMultiTempDoubleDomain") == 0) {
		dwellTimeFoldMultiTempDoubleDomain(argc, argv);
	}
	else */if(strcmp(argv[1], "-dwellTimeFold") == 0) {
		dwellTimeFold(argc, argv);
	}
	else if(strcmp(argv[1], "-foldAndPrint") == 0) {
		foldAndPrint(argc, argv);
	}
	else if(strcmp(argv[1], "-foldAndAggregate") == 0) {
		foldAndAggregate(argc, argv);
	}
	else if(strcmp(argv[1], "-freeFold") == 0) {
		freeFoldSingleDomain(argc, argv);
	}
	else if(strcmp(argv[1], "-RMSDsingle") == 0) {
		getRMSDs2nativeSingleDomains(argc, argv);
	}
	else if(strcmp(argv[1], "-generateDoubleDomain") == 0) {
		generateDoubleDomainStructure(argc, argv);
	}
	else if(strcmp(argv[1], "-freeFoldDouble") == 0) {
		freeFoldDoubleDomain(argc, argv);
	}
	else if(strcmp(argv[1], "-RMSDdouble") == 0) {
		getRMSDs2nativeDoubleDomains(argc, argv);
	}/*
	else if(strcmp(argv[1], "-freeFoldMultiTempDouble") == 0) {
		freeFoldMultiTempDoubleDomain(argc, argv);
	}*/
	else if(strcmp(argv[1], "-getSingleDomainContactMap") == 0) {
		getSingleDomainContactMapAndThermoData(argc, argv);
	}
	else if(strcmp(argv[1], "-getCOsOfSingleDomains") == 0) {
		getCOsOfSingleDomains(argc, argv);
	}
	else
	{
		cout<<"No valid program as input\n";
		exit(0);
	}
	return 0;
}

/*
int dwellTimeFoldMultiTempDoubleDomain(int argc, char**argv)
{
	cout<<"Version 23-09-13, V21 dwellTimeFoldMultiTempDoubleDomain"<<endl;
	
	if(argc != 25 && argc != 26)
	{
		cout<<"Vxx -dwellTimeFoldMultiTempDoubleDomain 1. sizeOfResidueArray 2. iterations 3. maxRangeOfLocalConf"<<endl;
		cout<<"4. numOfTimesEach 5. file_output_prefix 6. sequence 7. from1 8. to1 9. from2 10. to2"<<endl;
		cout<<"11. temp1 12. perturb1 13. temp2 14. perturb2 15. domainInFocus (1,2,3) 16. enableInteractionsBetweenDomains"<<endl;
		cout<<"17. confine 18. confineXsize 19. confineYsize"<<endl;
		cout<<"20. whichDomainToAssign (A, B, C) 21. nativeStructFileName 22. nativeStructIndex (in case of multiple native structures) 23. rmsdDwell [24. breaking (1,0)]"<<endl; 
		exit(0);
	}

	//1. sizeOfResidueArray:
	int size = atoi(argv[2]);

	//2. iterations
	int iterations = atoi(argv[3]);
	
	//4. numOfTimesEach	
	int numOfTimesEach = atoi(argv[5]);
		
	//7. index_fileName
	char *hp = argv[7];
	int fromto[4];
	
	//8.9.10.11. from/to
	fromto[0] = atoi(argv[8]);
	fromto[1] = atoi(argv[9]);
	fromto[2] = atoi(argv[10]);
	fromto[3] = atoi(argv[11]);
	int domainSize = fromto[1] - fromto[0] + 1;
	int linkerLength = fromto[2] - fromto[1] - 1;
	
	point *nativeStruct = new point[size + 1];
	point *nativeDomain1 = new point[domainSize + 1];
	point *nativeDomain2 = new point[domainSize + 1];
	char *domainSeq2 = new char[domainSize+1];
	char *domainSeq1 = new char[domainSize+1];

	char whichDomainToAssign = 0;
	char *nativeStructFileName;
	int nativeStructIndex = 0;
	
	double temp1 = atof(argv[12]);
	double perturb1 = atof(argv[13]);
	double temp2 = atof(argv[14]);
	double perturb2 = atof(argv[15]);
	int domainInFocus = atoi(argv[16]);
	bool enableInteractionsBetweenDomains = atoi(argv[17]);
	cout<<"enableInteractionsBetweenDomains: "<<enableInteractionsBetweenDomains<<endl;
	
	bool confine = atoi(argv[18]);
	int confineXsize = atoi(argv[19]); 
	int confineYsize = atoi(argv[20]);
	
	
	whichDomainToAssign = *argv[21];//A or B
	nativeStructFileName = argv[22];
	
	nativeStructIndex = atoi(argv[23]);
	double rmsdDwell = atof(argv[24]);
	bool breaking = false;
	if(argc == 26)
		breaking = atoi(argv[25]);
// 	cout<<"Got here!\n";
	
	multiTempDoubleDomain *MTDD;
	char *tmpstr;

	if(whichDomainToAssign && nativeStructFileName) {
		configFileHandler nativeCfh(nativeStructFileName, size);
		if( (tmpstr = nativeCfh.readDoubleDomainTextStructureGivenSequence(size, domainSize, linkerLength, nativeDomain1, nativeDomain2, hp, 			                                                                   domainSeq1, domainSeq2, nativeStructIndex)) != 0) {
				nativeCfh.writeStructure2output(domainSize, nativeDomain1, domainSeq1);
				nativeCfh.writeStructure2output(domainSize, nativeDomain2, domainSeq2);
				MTDD = new multiTempDoubleDomain(size, fromto, temp1, temp2, perturb1, perturb2, nativeDomain1, nativeDomain2, whichDomainToAssign, domainInFocus, enableInteractionsBetweenDomains, confine, confineXsize, confineYsize);
		}
	}
	else {
		cout<<"Error - no domain to assign or native struct file name is missing\n";
		exit(1);
	}
	int line;

//3. maxRangeOfLocalConf
	MTDD->maxRangeOfLocalConf = atoi(argv[4]);

	//8. outputdir	
	sprintf(MTDD->outputDatafileName, "%s", argv[6]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<MTDD->maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"outputdir: "<<MTDD->outputDatafileName<<endl;
	cout<<"edgesProbability: "<<MTDD->edgesProbability<<endl;
	cout<<"from1: "<<fromto[0]<<" to1: "<<fromto[1]<<" from2: "<<fromto[2]<<" to2: "<<fromto[3]<<endl;
	if(whichDomainToAssign && nativeStructFileName)
		cout<<"nativeStructFileName: "<<nativeStructFileName<<endl<<"whichDomainToAssign: "<<whichDomainToAssign<<endl;
	cout<<"sequence: "<<hp<<endl;
	
	MTDD->FoldAndPrintDwellTime(iterations, numOfTimesEach, hp, rmsdDwell, breaking); 
										  
	return 1;
}
*/

void getSingleDomainContactMapAndThermoData(int argc, char **argv)
{	
	cout<<"Version 19-09-11, V21 getsingleDomainContactMapAndThermoData"<<endl<<endl;
	if(argc < 6)
	{
		cout<<"Vxx -getSingleDomainContactMap 1.sizeOfResidueArray 2.nativeStructFileName(fdb) 3.maxNumberOfNativeStructs 4.sequence\n";
		exit(1);
	}
	int sizeOfResidueArray = atoi(argv[2]);
	char *nativeStructFname = argv[3];
	
	int maxNumberOfNativeStructs = atoi(argv[4]);
	
	char *sequence = argv[5];
	char *tmpstr;
		
	configFileHandler nativeCfh(nativeStructFname, sizeOfResidueArray);
	
	char *hp = new char[sizeOfResidueArray+1];
	point *nativeStruct = new point[sizeOfResidueArray + 1];
	
	if(!nativeStruct)
	{
		cout<<"ERROR - mem alloc getsingleDomainContactMapAndThermoData\n";
		exit(1);
	}
	int structIndex = 0;
	
	for(int structIndex = 0; structIndex < maxNumberOfNativeStructs; structIndex++) {
		cout<<"#STRUCT_ID\t"<<structIndex<<endl;
		char thermoData[50960];
		if( (tmpstr = nativeCfh.readTextStructureGivenSequenceAndThermoData(sizeOfResidueArray, nativeStruct, sequence, thermoData, structIndex)) != 0) {
			nativeCfh.writeStructure2output(sizeOfResidueArray, nativeStruct, sequence);
			cout<<"#THRMO DATA\n\n"<<thermoData<<endl;
			cout<<"#CONTACT MAP\n\n"<<endl;
			nativeCfh.writeContactMap2Output(sizeOfResidueArray, nativeStruct, sequence);
		}
		else {
			cout<<"Didn't find anything for structIndex\n";
			break;
		}
	}
	delete []nativeStruct;	
}

/*
int freeFoldMultiTempDoubleDomain(int argc, char**argv)
{
	cout<<"Version 22-08-13, V21 freeFoldMultiTempDoubleDomain"<<endl;
	
	if(argc < 21 || argc > 24)
	{
		cout<<"Vxx -freeFoldMultiTempDouble 1. sizeOfResidueArray 2. iterations 3. maxRangeOfLocalConf"<<endl;
		cout<<"4. numOfTimesEach 5. file_output_prefix 6. sequence 7. from1 8. to1 9. from2 10. to2"<<endl;
		cout<<"11. temp1 12. perturb1 13. temp2 14. perturb2 15. domainInFocus 16. enableInteractionsBetweenDomains"<<endl;
		cout<<"17. confine 18. confineXsize 19. confineYsize"<<endl;
		cout<<"[20. whichDomainToAssign 21. nativeStructFileName 22. nativeStructIndex (in case of multiple native structures)]"<<endl; 
		exit(0);
	}

	//1. sizeOfResidueArray:
	int size = atoi(argv[2]);

	//2. iterations
	int iterations = atoi(argv[3]);
	
	//4. numOfTimesEach	
	int numOfTimesEach = atoi(argv[5]);
		
	//7. index_fileName
	char *hp = argv[7];
	int fromto[4];
	
	//8.9.10.11. from/to
	fromto[0] = atoi(argv[8]);
	fromto[1] = atoi(argv[9]);
	fromto[2] = atoi(argv[10]);
	fromto[3] = atoi(argv[11]);
	int domainSize = fromto[1] - fromto[0] + 1;
	int linkerLength = fromto[2] - fromto[1] - 1;
	
	point *nativeStruct = new point[size + 1];
	point *nativeDomain1 = new point[domainSize + 1];
	point *nativeDomain2 = new point[domainSize + 1];
	char *domainSeq2 = new char[domainSize+1];
	char *domainSeq1 = new char[domainSize+1];

	char whichDomainToAssign = 0;
	char *nativeStructFileName;
	int nativeStructIndex = 0;
	
	double temp1 = atof(argv[12]);
	double perturb1 = atof(argv[13]);
	double temp2 = atof(argv[14]);
	double perturb2 = atof(argv[15]);
	int domainInFocus = atoi(argv[16]);
	bool enableInteractionsBetweenDomains = atoi(argv[17]);
	cout<<"enableInteractionsBetweenDomains: "<<enableInteractionsBetweenDomains<<endl;
	
	bool confine = atoi(argv[18]);
	int confineXsize = atoi(argv[19]); 
	int confineYsize = atoi(argv[20]);
	
	if(argc > 21) {
		whichDomainToAssign = *argv[21];//A or B
		nativeStructFileName = argv[22];
	if(argc == 24)
			nativeStructIndex = atoi(argv[23]);
	}
	cout<<"Got here!\n";
	
	multiTempDoubleDomain *MTDD;
	char *tmpstr;
	
	if(whichDomainToAssign && nativeStructFileName) {
		configFileHandler nativeCfh(nativeStructFileName, size);
		if( (tmpstr = nativeCfh.readDoubleDomainTextStructureGivenSequence(size, domainSize, linkerLength, nativeDomain1, nativeDomain2, hp, domainSeq1, domainSeq2, nativeStructIndex)) != 0) {
			if(whichDomainToAssign == 'A') {
				cout<<"Domain A to assign:\n";
				nativeCfh.writeStructure2output(domainSize, nativeDomain1, domainSeq1);
				MTDD = new multiTempDoubleDomain(size, fromto, temp1, temp2, perturb1, perturb2, nativeDomain1, whichDomainToAssign, domainInFocus, enableInteractionsBetweenDomains, confine, confineXsize, confineYsize);
			}
			else if(whichDomainToAssign == 'B') {
				cout<<"Domain B to assign:\n";
				nativeCfh.writeStructure2output(domainSize, nativeDomain2, domainSeq2);
				MTDD = new multiTempDoubleDomain(size, fromto, temp1, temp2, perturb1, perturb2, nativeDomain2, whichDomainToAssign, domainInFocus, enableInteractionsBetweenDomains, confine, confineXsize, confineYsize);
			}
			else {
				cout<<"Wrong character in whichDomainToAssign. Should be A or B\n";
				exit(1);
			}
		}
	}
	else {
		cout<<"Executing simulation as free fold with temperature of "<<temp1<<" for domain A and "<<temp2<<" for domain B\n";
		MTDD = new multiTempDoubleDomain(size, fromto, temp1, temp2, perturb1, perturb2, domainInFocus, enableInteractionsBetweenDomains, confine, confineXsize, confineYsize);
	}
	int line;

//3. maxRangeOfLocalConf
	MTDD->maxRangeOfLocalConf = atoi(argv[4]);

	//8. outputdir	
	sprintf(MTDD->outputDatafileName, "%s", argv[6]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<MTDD->maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"outputdir: "<<MTDD->outputDatafileName<<endl;
	cout<<"edgesProbability: "<<MTDD->edgesProbability<<endl;
	cout<<"from1: "<<fromto[0]<<" to1: "<<fromto[1]<<" from2: "<<fromto[2]<<" to2: "<<fromto[3]<<endl;
	if(whichDomainToAssign && nativeStructFileName)
		cout<<"nativeStructFileName: "<<nativeStructFileName<<endl<<"whichDomainToAssign: "<<whichDomainToAssign<<endl;
	cout<<"sequence: "<<hp<<endl;
	
	MTDD->foldToMinimumEnergy(iterations, numOfTimesEach, hp);
	
	return 1;
}
*/
void getCOsOfSingleDomains(int argc, char **argv)
{	
	if(argc < 6)
	{
		cout<<"Version 02-09-13, V21 getCOsOfSingleDomains"<<endl<<endl;
		cout<<"Vxx -getCOsOfSingleDomains 1.sizeOfResidueArray 2.nativeStructFileName(fdb) 4.from_index 5. to_index (0 indexing)\n";
		exit(1);
	}
	int sizeOfResidueArray = atoi(argv[2]);
	char *nativeStructFname = argv[3];
	int from_index = atoi(argv[4]);
	int to_index = atoi(argv[5]);
	char *tmpstr;
	
	configFileHandler nativeCfh(nativeStructFname, sizeOfResidueArray);
	point *nativeStruct = new point[sizeOfResidueArray + 1];
	char *sequence = new char[sizeOfResidueArray+1];
// 	cout<<"to_index: "<<to_index<<endl;
	for(int i = from_index; i <= to_index; i++) {
// 		cout<<"- "<<i<<" -"<<endl;
		if(tmpstr = nativeCfh.getConfiguration(sizeOfResidueArray, i)) {
			strncpy(sequence, tmpstr, sizeOfResidueArray);
			sequence[sizeOfResidueArray] = '\0';
// 			cout<<"#SEQ\t"<<sequence<<":\n";
			char dataLine[256];
			if(nativeCfh.readTextStructureandNextDataLine(sizeOfResidueArray, nativeStruct, dataLine, i) != 0) {
// 				nativeCfh.writeStructure2output(sizeOfResidueArray, nativeStruct, sequence);
				double co = CO(sizeOfResidueArray, nativeStruct);
				cout<<i<<"\t"<<co<<endl;
			}
		}
	}
}

void getRMSDs2nativeDoubleDomains(int argc, char **argv)
{	
	cout<<"Version 31-08-11, V21 getRMSDs2nativeDoubleDomains"<<endl<<endl;
	if(argc < 8)
	{
		cout<<"Vxx -RMSDdouble 1.sizeOfResidueArray 2.kineticOutputFilename(data) 3.nativeStructFileName(fdb) 4.maxNumberOfNativeStructs 5.domainSize 6. linkerLength\n";
		exit(1);
	}
	int sizeOfResidueArray = atoi(argv[2]);
	char *kineticFileFname = argv[3];
	char *nativeStructFname = argv[4];
	
	int maxNumberOfNativeStructs = atoi(argv[5]);
	int domainSize = atoi(argv[6]);
	int linkerLength = atoi(argv[7]);
	
	configFileHandler kineticCfh(kineticFileFname, sizeOfResidueArray);
	
	char *sequence = new char[sizeOfResidueArray+1];
	char *domainSeq2 = new char[domainSize+1];
	char *domainSeq1 = new char[domainSize+1];
	char *tmpstr;
	// we assume all file kineticFileFname has the same sequence
	if( (tmpstr = kineticCfh.getConfiguration(sizeOfResidueArray, 0)) == 0) {
		cout<<"ERROR - getRMSDs2nativeDoubleDomains - cannot find sequence in "<<kineticFileFname<<endl;
		exit(1);
	}
	strncpy(sequence, tmpstr, sizeOfResidueArray);
	sequence[sizeOfResidueArray] = '\0';
	cout<<"#SEQ\t"<<sequence<<":\n";
		
	configFileHandler nativeCfh(nativeStructFname, sizeOfResidueArray);
	
	char *hp = new char[sizeOfResidueArray+1];
	point *nativeStruct = new point[sizeOfResidueArray + 1];
	point *nativeDomain1 = new point[domainSize + 1];
	point *nativeDomain2 = new point[domainSize + 1];
	
	point *kineticStruct = new point[sizeOfResidueArray + 1];
	point *kineticDomain1 = new point[domainSize + 1];
	point *kineticDomain2 = new point[domainSize + 1];
	if(!nativeStruct || !kineticStruct)
	{
		cout<<"ERROR - mem alloc getRMSDs2nativeDoubleDomains\n";
		exit(1);
	}
	int structIndex = 0;
	
	for(int structIndex = 0; structIndex < maxNumberOfNativeStructs; structIndex++) {
		if( (tmpstr = nativeCfh.readDoubleDomainTextStructureGivenSequence(sizeOfResidueArray, domainSize, linkerLength,
				  																									 nativeDomain1, nativeDomain2, sequence, domainSeq1, domainSeq2, structIndex)) != 0) {
			cout<<"#NAS\t"<<structIndex<<endl;
			RMSD rmsd1(nativeDomain1, domainSize, 0);
			RMSD rmsd2(nativeDomain2, domainSize, 0);
			nativeCfh.writeStructure2output(domainSize, nativeDomain1, domainSeq1);
			nativeCfh.writeStructure2output(domainSize, nativeDomain2, domainSeq2);
			char dataLine[3][128];
			
			int kineticDomainIndex = 0;
			int kineticIndex = 0;
			while(kineticCfh.readTextStructureandNextDataLine(sizeOfResidueArray, kineticStruct, dataLine[0], kineticIndex++) != 0) {
				kineticCfh.readTextStructureandNextDataLine(domainSize, nativeDomain1, dataLine[1], kineticDomainIndex++);
				kineticCfh.readTextStructureandNextDataLine(domainSize, nativeDomain2, dataLine[2], kineticDomainIndex++);
				cout<<"#KRUN\t"<<kineticIndex<<endl;
				kineticCfh.writeStructure2output(sizeOfResidueArray, kineticStruct, sequence);
				cout<<"#DATA\tDOMAIN_DOUBLE\t"<<dataLine[0]<<endl;
				kineticCfh.writeStructure2output(domainSize, nativeDomain1, domainSeq1);
				double error1 = rmsd1.compute(nativeDomain1);
				cout<<"#DATA\tDOMAIN_1\tRMSD: "<<error1<<", pairwise error percent: "<<rmsd1.getPairErrorPercent()<<", "<<dataLine[1]<<endl;
				kineticCfh.writeStructure2output(domainSize, nativeDomain2, domainSeq2);
				double error2 = rmsd2.compute(nativeDomain2);
				cout<<"#DATA\tDOMAIN_2\tRMSD: "<<error2<<", pairwise error percent: "<<rmsd2.getPairErrorPercent()<<", "<<dataLine[2]<<endl;
			}
		}
		else {
			cout<<"Didn't find anything for structIndex\n";
			break;
		}
	}
	delete []nativeStruct;	
}

int freeFoldDoubleDomain(int argc, char**argv)
{
	cout<<"Version 28-08-11, V21 freeFoldDoubleDomain"<<endl;
	
	if(argc < 13)
	{
		cout<<"Vxx -freeFoldDouble 1. sizeOfResidueArray 2. iterations 3. maxRangeOfLocalConf"<<endl;
		cout<<"4. numOfTimesEach 5. simulationFactor 6. file_output_prefix 7. sequence 8. from1 9. to1 10. from2 11. to2"<<endl;
		exit(0);
	}
	cout<<"Executing protein grouping simulation.V1\n";

	//1. sizeOfResidueArray:
	int size = atoi(argv[2]);

	//2. iterations
	int iterations = atoi(argv[3]);
	
	//4. numOfTimesEach	
	int numOfTimesEach = atoi(argv[5]);
		
	//7. index_fileName
	char *hp = argv[8];
	int fromto[4];
	
	//8.9.10.11. from/to
	fromto[0] = atoi(argv[9]);
	fromto[1] = atoi(argv[10]);
	fromto[2] = atoi(argv[11]);
	fromto[3] = atoi(argv[12]);
	
	doubleDomain DD(size, fromto);
	int line;

//3. maxRangeOfLocalConf
	DD.maxRangeOfLocalConf = atoi(argv[4]);

//5. simulationFactor
	DD.simulationFactor = strtod(argv[6], NULL);

	//8. outputdir	
	sprintf(DD.outputDatafileName, "%s", argv[7]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<DD.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"simulationFactor: "<<DD.simulationFactor<<endl;
	cout<<"outputdir: "<<DD.outputDatafileName<<endl;
	cout<<"edgesProbability: "<<DD.edgesProbability<<endl;
	cout<<"from1: "<<fromto[0]<<"to1: "<<fromto[1]<<"from2: "<<fromto[2]<<"to2: "<<fromto[3]<<endl;
	
	cout<<"sequence: "<<hp<<endl;
	DD.foldToMinimumEnergy(iterations, numOfTimesEach, hp);
	
	return 1;
}


int generateDoubleDomainStructure(int argc, char**argv) {
	cout<<"Version 15-08-13, V21 generateDoubleDomainStructure"<<endl;
	if(argc < 8) {
		cout<<"Vxx -generateDoubleDomain 1.size of residue array 2.filename (fdb) of first domain 3.filename (fdb) of second domain 4.linker Length\n";
		cout<<"5.index of first domain in filename 6.index of second domain in filename\n"; 
		exit(0);  
	}
	int sizeOfResidueArray = atoi(argv[2]);
	char *fname1 = argv[3];
	char *fname2 = argv[4];
	int linkerLength = atoi(argv[5]);
	int index1 = atoi(argv[6]);
	int index2 = atoi(argv[7]);
	
	configFileHandler cfh(fname1, sizeOfResidueArray, 0);
			
	cfh.generateDimerTextStructureFromTwoFiles(index1, index2, sizeOfResidueArray, linkerLength, fname2);
	return 0;
}

int foldAndPrint(int argc, char**argv)
{
// 	cout<<"Version 04-07-13, V21 foldAndPrint"<<endl;
	
	if(argc < 10)
	{
		cout<<"Vxx -freeFold 1. sizeOfResidueArray 2. iterations 3. maxRangeOfLocalConf"<<endl;
		cout<<"4. numOfTimesEach 5. simulationFactor 6. configFileName 7.configfileIndex 8. NStep"<<endl;
		exit(0);
	}
// 	cout<<"Executing protein grouping simulation.V1\n";

	//1. sizeOfResidueArray:
	int size = atoi(argv[2]);
	
	//2. iterations
	int iterations = atoi(argv[3]);
	
	//4. numOfTimesEach	
	int numOfTimesEach = atoi(argv[5]);
	
	//6. configFileName:
	char *configFileName = argv[7];
	
	//7. configfileIndex:
	int configfileIndex = atoi(argv[8]);
	
	//8. Nstep:
	int NStep = atoi(argv[9]);
	int line;

	foldingComplex FC(size, configFileName);
	
	//3. maxRangeOfLocalConf
	FC.maxRangeOfLocalConf = atoi(argv[4]);
	
	//5. simulationFactor
	FC.simulationFactor = strtod(argv[6], NULL);
	
// 	cout<<"Session Details:\n";
// 	cout<<"----------------\n";
// 	cout<<"residueSize: "<<size<<endl;
// 	cout<<"iterations: "<<iterations<<endl;
// 	cout<<"maxRangeOfLocalConf: "<<FC.maxRangeOfLocalConf<<endl;
// 	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
// 	cout<<"simulationFactor: "<<FC.simulationFactor<<endl;
// // 	cout<<"outputdir: "<<FC.outputDatafileName<<endl;
// 	cout<<"edgesProbability: "<<FC.edgesProbability<<endl;
// 	cout<<"config file name: "<<configFileName<<endl;

	
// 	cout<<"sequence: "<<hp<<endl;
	FC.foldAndPrintParamsEachNStep(iterations, configfileIndex, NStep);
	
	return 1;
}

int foldAndAggregate(int argc, char**argv)
{
// 	cout<<"Version 04-08-13, V21 foldAndAggregate"<<endl;
	
	if(argc < 10)
	{
		cout<<"Version 04-08-13, V21 foldAndAggregate"<<endl;
		cout<<"Vxx -foldAndAggregate 1. sizeOfResidueArray 2. iterations 3. maxRangeOfLocalConf"<<endl;
		cout<<"4. numOfTimesEach 5. simulationFactor 6. configFileName 7.configfileIndex 8. NStep"<<endl;
		exit(0);
	}
// 	cout<<"Executing protein grouping simulation.V1\n";

	//1. sizeOfResidueArray:
	int size = atoi(argv[2]);
	
	//2. iterations
	int iterations = atoi(argv[3]);
	
	//4. numOfTimesEach	
	int numOfTimesEach = atoi(argv[5]);
	
	//6. configFileName:
	char *configFileName = argv[7];
	
	//7. configfileIndex:
	int configfileIndex = atoi(argv[8]);
	
	//8. Nstep:
	int NStep = atoi(argv[9]);
	int line;

	foldingComplex FC(size, configFileName);
	
	//3. maxRangeOfLocalConf
	FC.maxRangeOfLocalConf = atoi(argv[4]);
	
	//5. simulationFactor
	FC.simulationFactor = strtod(argv[6], NULL);
	
	FC.foldAndAggregateParamsEachNStep(iterations, configfileIndex, NStep);
	
	return 1;
}



int dwellTimeFold(int argc, char**argv)
{
// 	cout<<"Version 04-07-13, V21 foldAndPrint"<<endl;
	
	if(argc < 11)
	{
		cout<<"Vxx -freeFold 1. sizeOfResidueArray 2. iterations 3. maxRangeOfLocalConf"<<endl;
		cout<<"4. numOfTimesEach 5. simulationFactor 6. configFileName 7.configfileIndex 8. NStep 9. DwellTimeRMSDThreshold"<<endl;
		exit(0);
	}
// 	cout<<"Executing protein grouping simulation.V1\n";

	//1. sizeOfResidueArray:
	int size = atoi(argv[2]);
	
	//2. iterations
	int iterations = atoi(argv[3]);
	
	//4. numOfTimesEach	
	int numOfTimesEach = atoi(argv[5]);
	
	//6. configFileName:
	char *configFileName = argv[7];
	
	//7. configfileIndex:
	int configfileIndex = atoi(argv[8]);
	
	//8. Nstep:
	int NStep = atoi(argv[9]);
	double rmsdDwell = atoi(argv[10]);
	int line;

	foldingComplex FC(size, configFileName);
	
	//3. maxRangeOfLocalConf
	FC.maxRangeOfLocalConf = atoi(argv[4]);
	
	//5. simulationFactor
	FC.simulationFactor = strtod(argv[6], NULL);
	
// 	cout<<"Session Details:\n";
// 	cout<<"----------------\n";
// 	cout<<"residueSize: "<<size<<endl;
// 	cout<<"iterations: "<<iterations<<endl;
// 	cout<<"maxRangeOfLocalConf: "<<FC.maxRangeOfLocalConf<<endl;
// 	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
// 	cout<<"simulationFactor: "<<FC.simulationFactor<<endl;
// // 	cout<<"outputdir: "<<FC.outputDatafileName<<endl;
// 	cout<<"edgesProbability: "<<FC.edgesProbability<<endl;
// 	cout<<"config file name: "<<configFileName<<endl;

	
// 	cout<<"sequence: "<<hp<<endl;
// 	FC.foldAndPrintParamsEachNStep(iterations, configfileIndex, NStep);
	FC.dwellTimeFold(iterations, configfileIndex, rmsdDwell, NStep);
	return 1;
}


int freeFoldSingleDomain(int argc, char**argv)
{
	cout<<"Version 23-08-11, V21 freeFoldSingleDomain"<<endl;
	
	if(argc < 9)
	{
		cout<<"Vxx -freeFold 1. sizeOfResidueArray 2. iterations 3. maxRangeOfLocalConf"<<endl;
		cout<<"4. numOfTimesEach 5. simulationFactor 6. file_output_prefix 7. sequence"<<endl;
		exit(0);
	}
	cout<<"Executing protein grouping simulation.V1\n";

	//1. sizeOfResidueArray:
	int size = atoi(argv[2]);

	foldingComplex FC(size);
	
	//2. iterations
	int iterations = atoi(argv[3]);
	
	//3. maxRangeOfLocalConf
	FC.maxRangeOfLocalConf = atoi(argv[4]);
	
	//4. numOfTimesEach	
	int numOfTimesEach = atoi(argv[5]);
	
	//5. simulationFactor
	FC.simulationFactor = strtod(argv[6], NULL);
	
	//7. index_fileName
	char *hp = argv[8];
	int line;

	//8. outputdir	
	sprintf(FC.outputDatafileName, "%s", argv[7]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<FC.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"simulationFactor: "<<FC.simulationFactor<<endl;
	cout<<"outputdir: "<<FC.outputDatafileName<<endl;
	cout<<"edgesProbability: "<<FC.edgesProbability<<endl;

	
	cout<<"sequence: "<<hp<<endl;
	FC.foldToMinimumEnergy(iterations, numOfTimesEach, hp);
	
	return 1;
}

void getRMSDs2nativeSingleDomains(int argc, char **argv)
{	
	cout<<"Version 26-08-11, V21 getRMSDs2nativeSingleDomains"<<endl<<endl;
	if(argc < 6)
	{
		cout<<"Vxx -RMSD 1.sizeOfResidueArray 2.kineticOutputFilename(data) 3.nativeStructFileName(fdb) 4.maxNumberOfNativeStructs\n";
		exit(1);
	}
	int sizeOfResidueArray = atoi(argv[2]);
	char *kineticFileFname = argv[3];
	char *nativeStructFname = argv[4];
	
	int maxNumberOfNativeStructs = atoi(argv[5]);
	
	configFileHandler kineticCfh(kineticFileFname, sizeOfResidueArray);
	
	char *sequence = new char[sizeOfResidueArray+1];
	char *tmpstr;
	// we assume all file kineticFileFname has the same sequence
	if( (tmpstr = kineticCfh.getConfiguration(sizeOfResidueArray, 0)) == 0) {
		cout<<"ERROR - getRMSDs2nativeSingleDomains - cannot find sequence in "<<kineticFileFname<<endl;
		exit(1);
	}
	strncpy(sequence, tmpstr, sizeOfResidueArray);
	sequence[sizeOfResidueArray] = 0;
	cout<<"#SEQ\t"<<sequence<<":\n";
		
	configFileHandler nativeCfh(nativeStructFname, sizeOfResidueArray);
	
	char *hp = new char[sizeOfResidueArray+1];
	point *nativeStruct = new point[sizeOfResidueArray + 1];
	point *kineticStruct = new point[sizeOfResidueArray + 1];
	if(!nativeStruct || !kineticStruct)
	{
		cout<<"ERROR - mem alloc getRMSDs2nativeSingleDomains\n";
		exit(1);
	}
	int structIndex = 0;
	
	for(int structIndex = 0; structIndex < maxNumberOfNativeStructs; structIndex++) {
		char thermoData[50960];
		if( (tmpstr = nativeCfh.readTextStructureGivenSequenceAndThermoData(sizeOfResidueArray, nativeStruct, sequence, thermoData, structIndex)) != 0) {
			cout<<"#NAS\t"<<structIndex<<endl;
			RMSD rmsd(nativeStruct, sizeOfResidueArray, 0);
			nativeCfh.writeStructure2output(sizeOfResidueArray, nativeStruct, sequence);
			cout<<"#THRMO DATA\n\n"<<thermoData<<endl;
			int kineticIndex = 0;
			char dataLine[128];
			while(kineticCfh.readTextStructureandNextDataLine(sizeOfResidueArray, kineticStruct, dataLine, kineticIndex++) != 0) {
				cout<<"#KRUN\t"<<kineticIndex<<endl;
				kineticCfh.writeStructure2output(sizeOfResidueArray, kineticStruct, sequence);
				double error = rmsd.compute(kineticStruct);
				cout<<"#DATA\tRMSD: "<<error<<", pairwise error percent: "<<rmsd.getPairErrorPercent()<<", "<<dataLine<<endl;
			}
		}
		else {
			cout<<"Didn't find anything for structIndex\n";
			break;
		}
	}
	delete []nativeStruct;	
}
