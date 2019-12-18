//pcsimu.cpp
#include "protchap.h"
#include "dynamicLibEnum.h"
#include <math.h>
#include <iostream.h>
#include <stdlib.h>
#include "definitions.h"

int main(int argc, char**argv)
{
	cout<<"ALPHA: "<<ALPHA<<"\nALPHA_ITR: "<<ALPHA_ITR<<"\nALPHA_LOWER_BOND: "<<ALPHA_LOWER_BOND;
	cout<<"\nALPHA_UPPER_BOND: "<<ALPHA_UPPER_BOND<<endl;
#if 0
	if(argc < 9)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach\n";
		cout<<"configFileName configfileIndex structSrcFileName outputDatafileName\n";
		exit(0);
	}
	int size = atoi(argv[1]);
	
	foldingComplex fc(size, argv[5]);
	
	int iterations = atoi(argv[2]);
	
	fc.maxRangeOfLocalConf = atoi(argv[3]);
	
	strcpy(fc.outputDatafileName, argv[8]);
	int num = atoi(argv[4]);
	int configfileIndex = atoi(argv[6]);
	fc.simulationFactor = 1.25;
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<fc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<num<<endl;
	cout<<"configFileName: "<<argv[5]<<endl;
	cout<<"configfileIndex: "<<configfileIndex<<endl;
	cout<<"structSrcFileName: "<<argv[7]<<endl;
	cout<<"outputDatafileName: "<<fc.outputDatafileName<<endl;
	cout<<"simulationFactor: "<<fc.simulationFactor<<endl;
	
	fc.foldOverStructures(iterations, num, configfileIndex, argv[7]);
#endif

#if 0//RMSD reference: one base structure
	if(argc < 8)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach simulationFactor configFileName outputDatafileName\n";
		exit(0);
	}
	int size = atoi(argv[1]);
	
	foldingComplex fc(size, argv[6]);
	
	int iterations = atoi(argv[2]);
	
	fc.maxRangeOfLocalConf = atoi(argv[3]);
	
	char outputDatafileName[200];
	
	strcpy(outputDatafileName, argv[7]);
	int num = atoi(argv[4]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<fc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<num<<endl;
	cout<<"simulationFactor lower bond: "<<argv[5]<<" Upper bond: 3.0\n";
	cout<<"configFileName: "<<argv[6]<<endl;
	cout<<"outputDatafileName: "<<outputDatafileName<<"X\n";
	
	
	int line = 0;
	fc.generalCounter = 0;

#if 1	
	strcpy(fc.outputDatafileName, outputDatafileName);
	fc.simulationFactor = strtod(argv[5], NULL);

	
	while(fc.fold2BestEngergyStruct(iterations, num, line))
				line++;
	
#endif
	
#if 0	
	for(fc.simulationFactor = strtod(argv[5], NULL); 
		fc.simulationFactor < 3.0; 
		fc.simulationFactor += 0.25, line = 0)
		{
			sprintf(fc.outputDatafileName, "%s-SF%f", outputDatafileName, fc.simulationFactor);
			while(fc.fold2BestEngergyStruct(iterations, num, line))
				line++;
		}
#endif
	
#endif

#if 0//rmsd reference: pairwise
	if(argc < 8)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach";
		cout<<" simulationFactor configFileName outputDatafileName [index2start]\n";
		exit(0);
	}
	int size = atoi(argv[1]);
	
	foldingComplex fc(size, argv[6]);
	
	int iterations = atoi(argv[2]);
	
	fc.maxRangeOfLocalConf = atoi(argv[3]);
	
	char outputDatafileName[200];
	
	strcpy(outputDatafileName, argv[7]);
	int num = atoi(argv[4]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<fc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<num<<endl;
	cout<<"simulationFactor lower bond: "<<argv[5]<<" Upper bond: 3.0\n";
	cout<<"configFileName: "<<argv[6]<<endl;
	cout<<"outputDatafileName: "<<outputDatafileName<<"X\n";
	
	
	int line = 0;
	if(argc == 9)
		line = atoi(argv[8]);
	cout<<"First index in config file to start from: "<<line<<endl;
	
	fc.generalCounter = 0;

#if 1	
	strcpy(fc.outputDatafileName, outputDatafileName);
	fc.simulationFactor = strtod(argv[5], NULL);

	
	while(fc.fold2BestEngergyStructWithPairwiseRMSD(iterations, num, line))
				line++;
	
#endif
	
	
#endif

#if 1//rmsd reference: pairwise - loop thru all local lib
	if(argc < 7)
	{
		cout<<"residueSize iterations numOfTimesEach";
		cout<<" simulationFactor configFileName outputDatafileName ";
		cout<<"[llstart] [confinedFrom] [confinedTo] [alphaE]\n";
		exit(0);
	}
	int size = atoi(argv[1]);
	
	foldingComplex fc(size, argv[5]);
	
	int iterations = atoi(argv[2]);
	

	
	char outputDatafileName[200];
	
	strcpy(outputDatafileName, argv[6]);
	int num = atoi(argv[3]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<fc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<num<<endl;
	cout<<"simulationFactor: "<<argv[4]<<endl;
	cout<<"configFileName: "<<argv[5]<<endl;
	cout<<"outputDatafileName: "<<outputDatafileName<<"X\n";
	
		
	fc.generalCounter = 0;


	strcpy(fc.outputDatafileName, outputDatafileName);
	fc.simulationFactor = strtod(argv[4], NULL);

	char tmpFile[200];
	
	int i = 0;
	if(argc >= 8)
		i = atoi(argv[7]);
	
#if CONFINED_FOLD
	int confFrom = 0, confTo = 0;
	if(argc > 8)
	{
		confFrom = atoi(argv[8]);
		confTo = confFrom + 1;
	}
	if(argc > 9)
		confTo = atoi(argv[9]);
	cout<<"confFrom: "<<confFrom<<" confTo: "<<confTo<<endl;
	if(argc > 10)
		fc.alphaE = strtod(argv[10], NULL);
	cout<<"alphaE: "<<fc.alphaE<<endl;
#else
	if(argc > 8)
		fc.alphaE = strtod(argv[8], NULL);
	cout<<"alphaE: "<<fc.alphaE<<endl;
#endif
			
	for(; i < 6; i++)
	{
		int line = 0;
		fc.maxRangeOfLocalConf = i;
		cout<<"maxRangeOfLocalConf: "<<i<<endl;
#if CONFINED_FOLD
		confFrom = atoi(argv[8]);
		if( confFrom && confTo )
		{
			for(; confFrom < confTo; confFrom++)
			{
				line = 0;
				sprintf(tmpFile, "%sll%d_conf%d", outputDatafileName, i, confFrom);
				fc.added_confinedX = confFrom;
				fc.added_confinedY = confFrom;
				cout<<"Confinment side is: "<<fc.added_confinedX<<endl;
				 
				strcpy(fc.outputDatafileName, tmpFile);
				while(fc.fold2BestEngergyStructWithPairwiseRMSD(iterations, num, line))
						line++;
			}
		}

#else
		sprintf(tmpFile, "%sll%d", outputDatafileName, i); 

		strcpy(fc.outputDatafileName, tmpFile);
		while(fc.fold2BestEngergyStructWithPairwiseRMSD(iterations, num, line))
					line++;
#endif
	}

	
	
#endif
			
#if 0
	if(argc < 7)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach configFileName outputDatafileName\n";
		exit(0);
	}
	int size = atoi(argv[1]);
	
	foldingComplex fc(size, argv[5]);
	
	int iterations = atoi(argv[2]);
	
	fc.maxRangeOfLocalConf = atoi(argv[3]);
	
	strcpy(fc.outputDatafileName, argv[6]);
	int num = atoi(argv[4]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<fc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<num<<endl;
	cout<<"configFileName: "<<argv[5]<<endl;
	cout<<"outputDatafileName: "<<fc.outputDatafileName<<endl;
	
	
	int line = 0;
	fc.generalCounter = 0;
	while(fc.fold2BestEngergyStruct(iterations, num, line))
		line++;
#endif
	
#if 0 //this loop does simulations num times for all the configFile sequences:
	
	if(argc < 7)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach configFileName outputDatafileName\n";
		exit(0);
	}
	int size = atoi(argv[1]);
	int numOfTimesEach = atoi(argv[4]);
	
	foldingComplex fc(size, argv[5]);
	
	int iterations = atoi(argv[2]);
	
	fc.maxRangeOfLocalConf = atoi(argv[3]);
	
	strcpy(fc.outputDatafileName, argv[6]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<fc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"configFileName: "<<argv[5]<<endl;
	cout<<"outputDatafileName: "<<fc.outputDatafileName<<endl;
	
	for(int i = 0; i < numOfTimesEach; i++)
	{
		fc.generalCounter = i;
		int line = 0;
		while(fc.fold2RMSD(iterations, line))
		{
			line++;
			cout<<"Did: "<<i<<endl;
		}
	}
#endif
	return 0;
}

