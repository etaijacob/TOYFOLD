//main.cpp

#include "dimersChaperonComplex.h"
#include "configFileHandler.h"
#include <iostream.h>
#include <stdlib.h>
#include "utilities.h"
#include <math.h>

int pcc(int argc, char**argv);
int upcc(int argc, char**argv);
int upcct(int argc, char**argv);
int pccf(int argc, char**argv);
int pccfc(int argc, char**argv);
int dpccfc(int argc, char**argv);
int edgepcc(int argc, char**argv);
int minimumEnergyGrouping(int argc, char**argv);
int monomerFoldInChaperone(int argc, char**argv);
int foldDoubleDomain(int argc, char**argv);

int main(int argc, char **argv)
{
	foldDoubleDomain(argc, argv);
	//monomerFoldInChaperone(argc, argv);
	//minimumEnergyGrouping(argc, argv);
// 	dpccfc(argc, argv);
	//edgepcc(argc, argv);
	//pccfc(argc, argv);
	//upcct(argc, argv);
	//cout<<"end of simulation\n";
	return 0;
}

int foldDoubleDomain(int argc, char**argv)
{
	cout<<"Version 01-12-10, V21"<<endl;
	if(argc < 13)//one additional for zero !!!
	{
		cout<<"1.residueSize 2.iterations 3.maxRangeOfLocalConf 4.numOfTimesEach 5.simulationFactor 6.seqConfigFileName\n7.outputdir 8.from1 9.to1 10.from2 11.to2 12.configFileIndex\n";
		exit(0);
	}
	cout<<"Dimer folding index: "<<argv[12]<<".\n";
	int size = atoi(argv[1]);
	int iterations = atoi(argv[2]);
	int numOfTimesEach = atoi(argv[4]);
	int fromto[4];
	int configFileIndex = atoi(argv[12]);
	
	for(int i = 0; i < 4; i++)
		fromto[i] = atoi(argv[8 + i]);
	
	int line;
	{
		dimersChaperonComplex pcc(size, argv[6], 0, 0, 0);	//folding without chaperon: last three args are zero.
		
		pcc.maxRangeOfLocalConf = atoi(argv[3]);
		pcc.simulationFactor = strtod(argv[5], NULL);
		pcc.generalCounter = 0;
		pcc.edgesProbability = (int)(3.0/0.15) - 1;
		
		//sprintf(pcc.outputDatafileName, "%schap%d-", argv[8], chaperonIndex);
	
		cout<<"Session Details:\n";
		cout<<"----------------\n";
		cout<<"residueSize: "<<size<<endl;
		cout<<"iterations: "<<iterations<<endl;
		cout<<"maxRangeOfLocalConf: "<<pcc.maxRangeOfLocalConf<<endl;
		cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
		cout<<"simulationFactor: "<<argv[5]<<"\n";
		cout<<"configFileName: "<<argv[6]<<endl;
		cout<<"outputdir: "<<argv[7]<<endl;
		cout<<"edgesProbability: 0.15"<<endl;
		
		pcc.dimersChaperonComplex::foldDimer(iterations, numOfTimesEach, configFileIndex, fromto);
		cout<<"did a simulation\n";
	}
	return 1;
}

int pcc(int argc, char**argv)
{
	if(argc < 11)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach";
		cout<<" simulationFactor seqConfigFileName chaperonConfFileName\n"\
			  "outputdir fromTemp toTemp [chaperonIndex] [dynamic]\n"\
			  "[ bindInterval releaseInterval energyThreshold ]\n";
		exit(0);
	}
	cout<<"Executing protein chaperon simulation.\n";
	int size = atoi(argv[1]);
	int iterations = atoi(argv[2]);
	int numOfTimesEach = atoi(argv[4]);
	double fromTemp = strtod(argv[9], NULL);
	double toTemp = strtod(argv[10], NULL);
	
	int chaperonIndex = 0;
	bool inChaperon = false;
	int bindInterval = 1;
	int releaseInterval = iterations + 1;
	double energyThreshold = 0;
	
	
	if(argc > 11)
	{
		inChaperon = true;
		chaperonIndex = atoi(argv[11]);
		cout<<"Folding in chaperone index number: "<<chaperonIndex<<endl;
	}
	else
	{
		chaperonIndex = 0;	
		cout<<"Folding without chaperon\n";
	}
	
	bool dynamic = false;
	if(argc > 10)
	{
		dynamic = atoi(argv[12]);	
		cout<<"Dynamic (steps) chaperone complexd is: "<<dynamic<<endl;
	}
		

	proteinChaperonComplex pcc(size, argv[6], chaperonIndex, argv[7]);
	
	pcc.maxRangeOfLocalConf = atoi(argv[3]);
	pcc.simulationFactor = strtod(argv[5], NULL);
	pcc.generalCounter = 0;
	strcpy(pcc.outputDatafileName, argv[8]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<pcc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"simulationFactor: "<<argv[5]<<"\n";
	cout<<"configFileName: "<<argv[6]<<endl;
	cout<<"outputdir: "<<argv[8]<<endl;
	
	if(argc == 16)
	{
		bindInterval = atoi(argv[13]);
		releaseInterval = atoi(argv[14]);
		energyThreshold = strtod(argv[15], NULL);
		cout<<"bindInterval: "<<bindInterval<<endl;
		cout<<"releaseInterval: "<<releaseInterval<<endl;
		cout<<"energyThreshold: "<<energyThreshold<<endl;
	}	
	
	

	int line;
	
	//for(double temp = fromTemp; temp <= toTemp; temp += 0.25)//0.05)
	//for(int temp = fromTemp; temp <= toTemp; temp += 20000)//0.05)
	for(double temp = fromTemp; temp <= toTemp; temp += 0.05)
	{
		pcc.simulationFactor = temp;
		cout<<"Simulation factor: "<<temp<<endl;
		//energyThreshold = -temp;
		//cout<<"energyThreshold: "<<energyThreshold<<endl;
//		releaseInterval = temp;
//		cout<<"releaseInterval: "<<releaseInterval<<endl;
		//bindInterval = temp;
		//cout<<"bindInterval: "<<bindInterval<<endl;
			
		for(line = 100; line < 300; line++)
		{
			if(!pcc.foldInChaperonWithBindReleaseMechanism(iterations, 
													   numOfTimesEach, 
													   line, 
													   inChaperon,
													   dynamic,
													   bindInterval,
		                    			               releaseInterval,
		                        			           energyThreshold) )
				break;
		}
		//if(line < 100)
		//	break;
	}
	return 1;
}

//unfold
int upcc(int argc, char**argv)
{
	if(argc < 12)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach";
		cout<<" simulationFactor seqConfigFileName chaperonConfFileName\n"\
			  "outputdir fromTemp toTemp sampleRate \n[chaperonIndex] [dynamic] "\
			  "[ bindInterval releaseInterval energyThreshold ]\n";
		exit(0);
	}
	cout<<"Executing protein chaperon simulation.\n";
	int size = atoi(argv[1]);
	int iterations = atoi(argv[2]);
	int numOfTimesEach = atoi(argv[4]);
	double fromTemp = strtod(argv[9], NULL);
	double toTemp = strtod(argv[10], NULL);
	int sampleRate = atoi(argv[11]);
	
	int chaperonIndex = 0;
	bool inChaperon = false;
	int bindInterval = 1;
	int releaseInterval = iterations + 1;
	double energyThreshold = 0;
	
	
	if(argc > 12)
	{
		inChaperon = true;
		chaperonIndex = atoi(argv[12]);
		cout<<"Folding in chaperone index number: "<<chaperonIndex<<endl;
	}
	else
	{
		chaperonIndex = 0;	
		cout<<"Folding without chaperon\n";
	}
	
	bool dynamic = false;
	if(argc > 11)
	{
		dynamic = atoi(argv[13]);	
		cout<<"Dynamic (steps) chaperone complexd is: "<<dynamic<<endl;
	}
		

	proteinChaperonComplex pcc(size, argv[6], chaperonIndex, argv[7]);
	
	pcc.maxRangeOfLocalConf = atoi(argv[3]);
	pcc.simulationFactor = strtod(argv[5], NULL);
	pcc.generalCounter = 0;
	strcpy(pcc.outputDatafileName, argv[8]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<pcc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"simulationFactor: "<<argv[5]<<"\n";
	cout<<"configFileName: "<<argv[6]<<endl;
	cout<<"outputdir: "<<argv[8]<<endl;
	
	if(argc == 17)
	{
		bindInterval = atoi(argv[14]);
		releaseInterval = atoi(argv[15]);
		energyThreshold = strtod(argv[16], NULL);
		cout<<"bindInterval: "<<bindInterval<<endl;
		cout<<"releaseInterval: "<<releaseInterval<<endl;
		cout<<"energyThreshold: "<<energyThreshold<<endl;
	}	
	
	

	int line;
	
	for(double temp = fromTemp; temp <= toTemp; temp += 0.25)//0.05)
	//for(int temp = fromTemp; temp <= toTemp; temp += 20000)//0.05)
	{
		pcc.simulationFactor = temp;
		cout<<"Simulation factor: "<<temp<<endl;
		//energyThreshold = -temp;
		//cout<<"energyThreshold: "<<energyThreshold<<endl;
//		releaseInterval = temp;
//		cout<<"releaseInterval: "<<releaseInterval<<endl;
		//bindInterval = temp;
		//cout<<"bindInterval: "<<bindInterval<<endl;
			
		for(line = 0; line < 100; line++)
		{
			if(!pcc.unFoldInChaperonWithBindReleaseMechanism(iterations, 
													   numOfTimesEach, 
													   line, 
													   inChaperon,
													   dynamic,
													   bindInterval,
		                    			               releaseInterval,
		                        			           energyThreshold,
													   sampleRate) )
				break;
		}
	}
	return 1;
}

//unfold
int upcct(int argc, char**argv)
{
	if(argc < 13)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach";
		cout<<" simulationFactor seqConfigFileName chaperonConfFileName\n"\
			  "outputdir fromTemp toTemp sampleRate thershold\n[chaperonIndex] [dynamic] "\
			  "[ bindInterval releaseInterval energyThreshold ]\n";
		exit(0);
	}
	cout<<"Executing protein chaperon simulation.\n";
	int size = atoi(argv[1]);
	int iterations = atoi(argv[2]);
	int numOfTimesEach = atoi(argv[4]);
	double fromTemp = strtod(argv[9], NULL);
	double toTemp = strtod(argv[10], NULL);
	int sampleRate = atoi(argv[11]);
	double thershold = strtod(argv[12], NULL);
	
	int chaperonIndex = 0;
	bool inChaperon = false;
	int bindInterval = 1;
	int releaseInterval = iterations + 1;
	double energyThreshold = 0;
	
	
	if(argc > 13)
	{
		inChaperon = true;
		chaperonIndex = atoi(argv[13]);
		cout<<"Folding in chaperone index number: "<<chaperonIndex<<endl;
	}
	else
	{
		chaperonIndex = 0;	
		cout<<"Folding without chaperon\n";
	}
	
	bool dynamic = false;
	if(argc > 13)
	{
		dynamic = atoi(argv[14]);	
		cout<<"Dynamic (steps) chaperone complexd is: "<<dynamic<<endl;
	}
		

	proteinChaperonComplex pcc(size, argv[6], chaperonIndex, argv[7]);
	
	pcc.maxRangeOfLocalConf = atoi(argv[3]);
	pcc.simulationFactor = strtod(argv[5], NULL);
	pcc.generalCounter = 0;
	strcpy(pcc.outputDatafileName, argv[8]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<pcc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"simulationFactor: "<<argv[5]<<"\n";
	cout<<"configFileName: "<<argv[6]<<endl;
	cout<<"outputdir: "<<argv[8]<<endl;
	cout<<"thershold: "<<thershold<<endl;
	if(argc == 18)
	{
		bindInterval = atoi(argv[15]);
		releaseInterval = atoi(argv[16]);
		energyThreshold = strtod(argv[17], NULL);
		cout<<"bindInterval: "<<bindInterval<<endl;
		cout<<"releaseInterval: "<<releaseInterval<<endl;
		cout<<"energyThreshold: "<<energyThreshold<<endl;
	}	
	
	

	int line;
	
	for(double temp = fromTemp; temp <= toTemp; temp += 0.25)//0.05)
	//for(int temp = fromTemp; temp <= toTemp; temp += 20000)//0.05)
	{
		pcc.simulationFactor = temp;
		cout<<"Simulation factor: "<<temp<<endl;
		//energyThreshold = -temp;
		//cout<<"energyThreshold: "<<energyThreshold<<endl;
//		releaseInterval = temp;
//		cout<<"releaseInterval: "<<releaseInterval<<endl;
		//bindInterval = temp;
		//cout<<"bindInterval: "<<bindInterval<<endl;
		
		
		for(line = 0; line < 1000; line++)
		{
			cout<<"doing line: "<<line<<endl;	
			if(!pcc.unFoldThreshInChaperonWithBindReleaseMechanism(iterations, 
													   numOfTimesEach, 
													   line, 
													   inChaperon,
													   dynamic,
													   bindInterval,
		                    			               releaseInterval,
		                        			           energyThreshold,
													   sampleRate,
													   thershold) )
				break;
		}
	}
	return 1;
}



int pccf(int argc, char**argv)
{
	if(argc < 12)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach";
		cout<<" simulationFactor seqConfigFileName chaperonConfFileName\n"\
			  "outputdir fromTemp toTemp indexFile [chaperonIndex] [dynamic]\n"\
			  "[ bindInterval releaseInterval energyThreshold ]\n";
		exit(0);
	}
	cout<<"Executing protein chaperon simulation.\n";
	int size = atoi(argv[1]);
	int iterations = atoi(argv[2]);
	int numOfTimesEach = atoi(argv[4]);
	double fromTemp = strtod(argv[9], NULL);
	double toTemp = strtod(argv[10], NULL);
	
	char *indexFile = argv[11];
	int chaperonIndex = 0;
	bool inChaperon = false;
	int bindInterval = 1;
	int releaseInterval = iterations + 1;
	double energyThreshold = 0;
	
	
	if(argc > 12)
	{
		inChaperon = true;
		chaperonIndex = atoi(argv[12]);
		cout<<"Folding in chaperone index number: "<<chaperonIndex<<endl;
	}
	else
	{
		chaperonIndex = 0;	
		cout<<"Folding without chaperon\n";
	}
	
	bool dynamic = false;
	if(argc > 11)
	{
		dynamic = atoi(argv[13]);	
		cout<<"Dynamic (steps) chaperone complexd is: "<<dynamic<<endl;
	}
		

	proteinChaperonComplex pcc(size, argv[6], chaperonIndex, argv[7]);
	
	pcc.maxRangeOfLocalConf = atoi(argv[3]);
	pcc.simulationFactor = strtod(argv[5], NULL);
	pcc.generalCounter = 0;
	strcpy(pcc.outputDatafileName, argv[8]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<pcc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"simulationFactor: "<<argv[5]<<"\n";
	cout<<"configFileName: "<<argv[6]<<endl;
	cout<<"outputdir: "<<argv[8]<<endl;
	
	if(argc == 17)
	{
		bindInterval = atoi(argv[14]);
		releaseInterval = atoi(argv[15]);
		energyThreshold = strtod(argv[16], NULL);
		cout<<"bindInterval: "<<bindInterval<<endl;
		cout<<"releaseInterval: "<<releaseInterval<<endl;
		cout<<"energyThreshold: "<<energyThreshold<<endl;
	}	
	
	

	int line;
#if 1 //All	
	for(pcc.simulationFactor = 0.2; pcc.simulationFactor <= 3.0; pcc.simulationFactor += 0.05)
		for(energyThreshold = -3.0; energyThreshold <= 0.0; energyThreshold += 0.25)
			for(bindInterval = 20000; bindInterval <= 380000; bindInterval += 20000)
				for(releaseInterval = 20000; releaseInterval <= 900000; releaseInterval += 20000)
				{
		
					cout<<"Simulation factor: "<<pcc.simulationFactor<<endl;
					cout<<"energyThreshold: "<<energyThreshold<<endl;
					cout<<"releaseInterval: "<<releaseInterval<<endl;
					cout<<"bindInterval: "<<bindInterval<<endl;
			
					for(int idx = 0; (line = getIntegerFromFile(indexFile, idx)) != -1; idx++)
					{
						if(!pcc.foldInChaperonWithBindReleaseMechanism(iterations, 
																	   numOfTimesEach, 
																	   line, 
													   				   inChaperon,
																	   dynamic,
																	   bindInterval,
		                    							               releaseInterval,
		                        			    				       energyThreshold) )
							break;
				
						cout<<"line: "<<line<<", ";
					}
					cout<<endl;
				}
#endif

#if 0 //one parameter at a time	
	//for(double temp = fromTemp; temp <= toTemp; temp += 0.25)//0.05)
	for(int temp = fromTemp; temp <= toTemp; temp += 20000)//0.05)
	//for(double temp = fromTemp; temp <= toTemp; temp += 0.05)
	{
		//pcc.simulationFactor = temp;
		//cout<<"Simulation factor: "<<temp<<endl;
		//energyThreshold = -temp;
		//cout<<"energyThreshold: "<<energyThreshold<<endl;
		//releaseInterval = temp;
		//cout<<"releaseInterval: "<<releaseInterval<<endl;
		bindInterval = temp;
		cout<<"bindInterval: "<<bindInterval<<endl;
			
		for(int idx = 0; (line = getIntegerFromFile(indexFile, idx)) != -1; idx++)
		{
			if(!pcc.foldInChaperonWithBindReleaseMechanism(iterations, 
													   numOfTimesEach, 
													   line, 
													   inChaperon,
													   dynamic,
													   bindInterval,
		                    			               releaseInterval,
		                        			           energyThreshold) )
				break;
				
			cout<<"line: "<<line<<", ";
		}
		cout<<endl;
	}
#endif
	return 1;
}

int pccfc(int argc, char**argv)
{
	if(argc < 12)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach";
		cout<<" simulationFactor seqConfigFileName chaperonConfFileName\n"\
			  "outputdir fromTemp toTemp indexFile [chaperonIndex] [dynamic]\n"\
			  "[ bindInterval releaseInterval energyThreshold ]\n";
		exit(0);
	}
	cout<<"Executing protein chaperon simulation.\n";
	int size = atoi(argv[1]);
	int iterations = atoi(argv[2]);
	int numOfTimesEach = atoi(argv[4]);
	double fromTemp = strtod(argv[9], NULL);
	double toTemp = strtod(argv[10], NULL);
	
	char *indexFile = argv[11];
	int chaperonIndex = 0;
	bool inChaperon = false;
	int bindInterval = 1;
	int releaseInterval = iterations + 1;
	double energyThreshold = 0;
	
	
	if(argc > 12)
	{
		inChaperon = true;
		chaperonIndex = atoi(argv[12]);
		cout<<"Folding in chaperone index number: "<<chaperonIndex<<endl;
	}
	else
	{
		chaperonIndex = 0;	
		cout<<"Folding without chaperon\n";
	}
	
	bool dynamic = false;
	if(argc > 11)
	{
		dynamic = atoi(argv[13]);	
		cout<<"Dynamic (steps) chaperone complexd is: "<<dynamic<<endl;
	}
		
	//proteinChaperonComplex pcc(size, argv[6], chaperonIndex, argv[7]);
	if(argc == 17)
	{
		bindInterval = atoi(argv[14]);
		releaseInterval = atoi(argv[15]);
		energyThreshold = strtod(argv[16], NULL);
		cout<<"bindInterval: "<<bindInterval<<endl;
		cout<<"releaseInterval: "<<releaseInterval<<endl;
		cout<<"energyThreshold: "<<energyThreshold<<endl;
	}	
	
	

	int line;

	
#if 1
	for(int temp = fromTemp; temp <= toTemp; temp++)
	{
		chaperonIndex = temp;
		cout<<"chaperonIndex: "<<chaperonIndex<<endl;
		proteinChaperonComplex pcc(size, argv[6], chaperonIndex, argv[7]);	
		
		pcc.maxRangeOfLocalConf = atoi(argv[3]);
		pcc.simulationFactor = strtod(argv[5], NULL);
		pcc.generalCounter = 0;
		
		sprintf(pcc.outputDatafileName, "%schap%d-", argv[8], chaperonIndex);
	
		cout<<"Session Details:\n";
		cout<<"----------------\n";
		cout<<"residueSize: "<<size<<endl;
		cout<<"iterations: "<<iterations<<endl;
		cout<<"maxRangeOfLocalConf: "<<pcc.maxRangeOfLocalConf<<endl;
		cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
		cout<<"simulationFactor: "<<argv[5]<<"\n";
		cout<<"configFileName: "<<argv[6]<<endl;
		cout<<"outputdir: "<<argv[8]<<endl;
		
		for(int idx = 0; (line = getIntegerFromFile(indexFile, idx)) != -1; idx++)
		{
			if(!pcc.foldInChaperonWithBindReleaseMechanism(iterations, 
									numOfTimesEach, 
									line, 
									inChaperon,
									dynamic,
									bindInterval,
		                    			                releaseInterval,
		                        			        energyThreshold) )
				break;
				
			cout<<"line: "<<line<<", ";
		}
		
		cout<<endl;
	}
#endif
	return 1;
}

int dpccfc(int argc, char**argv)
{
	cout<<"Version 13-9-06, V1"<<endl;
	if(argc < 16)//one additional for zero !!!
	{
		cout<<"1.residueSize 2.iterations 3.maxRangeOfLocalConf 4.numOfTimesEach";
		cout<<" simulationFactor 6.seqConfigFileName\n 7.chaperonConfFileName"\
			  "8.outputdir 9.fromChapIdx 10.toChapIdx 11.indexFile 12.from1 13.to1 14.from2 15.to2 \n16.[chaperonIndex] 17.[dynamic]"\
			  "[ 18.bindInterval 19.releaseInterval 20.energyThreshold 21.addedX 22.addedX]\n";

		exit(0);
	}
	cout<<"Executing protein chaperon simulation.\n";
	int size = atoi(argv[1]);
	int iterations = atoi(argv[2]);
	int numOfTimesEach = atoi(argv[4]);
	double fromChapIdx = strtod(argv[9], NULL);
	double toChapIdx = strtod(argv[10], NULL);
	
	char *indexFile = argv[11];
	int chaperonIndex = 0;
	bool inChaperon = false;
	int bindInterval = 1;
	int releaseInterval = iterations + 1;
	double energyThreshold = 0;
	int fromto[4];
	
	for(int i = 0; i < 4; i++)
		fromto[i] = atoi(argv[12 + i]);
	
	if(argc > 16)
	{
		inChaperon = true;
		chaperonIndex = atoi(argv[16]);
		cout<<"Folding in chaperone index number: "<<chaperonIndex<<endl;
	}
	else
	{
		chaperonIndex = 0;	
		cout<<"Folding without chaperon\n";
	}
	
	bool dynamic = false;
	if(argc > 16)
	{
		dynamic = atoi(argv[17]);	
		cout<<"709 Dynamic (steps) chaperone complexd is: "<<dynamic<<endl;
	}
		

	//proteinChaperonComplex pcc(size, argv[6], chaperonIndex, argv[7]);
	int addedX, addedY;
	if(argc >= 21)
	{
		for(int dd = 18; dd <=22; dd++)
			cout<<argv[dd]<<endl;
		bindInterval = atoi(argv[18]);
		releaseInterval = atoi(argv[19]);
		energyThreshold = strtod(argv[20], NULL);
		addedX = atoi(argv[21]);
		addedY = atoi(argv[22]);
		cout<<"bindInterval: "<<bindInterval<<endl;
		cout<<"releaseInterval: "<<releaseInterval<<endl;
		cout<<"energyThreshold: "<<energyThreshold<<endl;
		cout<<"addedX/Y: "<<addedX<<"/"<<addedY<<endl;
		cout<<"got here"<<endl;
	}	
	
	int line;

	for(int temp = fromChapIdx; temp <= toChapIdx; temp++)
	{
		chaperonIndex = temp;
		cout<<"chaperonIndex: "<<chaperonIndex<<endl;
		dimersChaperonComplex pcc(size, argv[6], chaperonIndex, argv[7], 1);	
		
		pcc.maxRangeOfLocalConf = atoi(argv[3]);
		pcc.simulationFactor = strtod(argv[5], NULL);
		pcc.generalCounter = 0;
		pcc.edgesProbability = (int)(3.0/0.15) - 1;
		
		sprintf(pcc.outputDatafileName, "%schap%d-", argv[8], chaperonIndex);
	
		cout<<"Session Details:\n";
		cout<<"----------------\n";
		cout<<"residueSize: "<<size<<endl;
		cout<<"iterations: "<<iterations<<endl;
		cout<<"maxRangeOfLocalConf: "<<pcc.maxRangeOfLocalConf<<endl;
		cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
		cout<<"simulationFactor: "<<argv[5]<<"\n";
		cout<<"configFileName: "<<argv[6]<<endl;
		cout<<"outputdir: "<<argv[8]<<endl;
		cout<<"edgesProbability: 0.15"<<endl;
		/*******************************************
		test:
		char *hp;
		point structure[100];
		if( (hp = pcc.CfileHdlr.dimer_readTextStructure(size, structure, 7, 0)) == 0)
		{
			cout<<"could not Get index: "<<argv[6]<<endl;
			//delete []structure;
			return 0;//exit(0);
		}
		pcc.CfileHdlr.writeStructure2output(size, structure, hp);
		
		point structure2[100];
		
		if( (hp = pcc.CfileHdlr.readTextStructure(size, structure2, 1)) == 0)
		{
			cout<<"could not Get index: "<<argv[6]<<endl;
			//delete []structure;
			return 0;//exit(0);
		}
		
		if( (hp = pcc.CfileHdlr.dimer_readTextStructure(size, structure2, 7, 0)) == 0)
		{
			cout<<"could not Get index: "<<argv[6]<<endl;
			//delete []structure;
			return 0;//exit(0);
		}
		pcc.CfileHdlr.writeStructure2output(size, structure2, hp);
		RMSD rmsd(&pcc, size, 0);
		rmsd.update(structure2);
		double error = rmsd.dimer_compute(structure, fromto[0], fromto[1], fromto[2], fromto[3]);
		cout<<"\nError: "<<error<<endl;
		*/
		
		for(int idx = 0; (line = getIntegerFromFile(indexFile, idx)) != -1; idx++)
		{
			if(!pcc.foldInChaperonWithBindReleaseMechanism(iterations, 
													   	   numOfTimesEach, 
		   												   line,
														   fromto,
													   	   inChaperon,
													   	   dynamic,
													   	   bindInterval,
		                    			               	   releaseInterval,
		                        			           	   energyThreshold,
														   addedX,
														   addedY) )
				break;
				
			cout<<"line: "<<line<<", ";
		}
		
		cout<<endl;
	}
	return 1;
}
//code of publication in bioinformatics - don't change !!!
int edgepcc(int argc, char**argv)
{
	if(argc < 12)
	{
		cout<<"residueSize iterations maxRangeOfLocalConf numOfTimesEach";
		cout<<" simulationFactor seqConfigFileName chaperonConfFileName\n"\
			  "outputdir chapIdx edgesProbability indexFile [chaperonIndex] [dynamic]\n"\
			  "[ bindInterval releaseInterval energyThreshold ]\n";
		exit(0);
	}
	cout<<"Executing protein chaperon simulation.\n";
	int size = atoi(argv[1]);
	int iterations = atoi(argv[2]);
	int numOfTimesEach = atoi(argv[4]);
	double chapIdx = strtod(argv[9], NULL);//fromTmp
	int edgesProbability = (int)(3.0/strtod(argv[10], NULL)) - 1;//double toTmp
	
	char *indexFile = argv[11];
	int chaperonIndex = 0;
	bool inChaperon = false;
	int bindInterval = 1;
	int releaseInterval = iterations + 1;
	double energyThreshold = 0;
	
	
	if(argc > 12)
	{
		inChaperon = true;
		chaperonIndex = atoi(argv[12]);
		cout<<"Folding in chaperone index number: "<<chaperonIndex<<endl;
	}
	else
	{
		chaperonIndex = 0;	
		cout<<"Folding without chaperon\n";
	}
	
	bool dynamic = false;
	if(argc > 11)
	{
		dynamic = atoi(argv[13]);	
		cout<<"Dynamic (steps) chaperone complexd is: "<<dynamic<<endl;
	}
	
	if(argc == 17)
	{
		bindInterval = atoi(argv[14]);
		releaseInterval = atoi(argv[15]);
		energyThreshold = strtod(argv[16], NULL);
		cout<<"bindInterval: "<<bindInterval<<endl;
		cout<<"releaseInterval: "<<releaseInterval<<endl;
		cout<<"energyThreshold: "<<energyThreshold<<endl;
	}	
	int line;

	chaperonIndex = chapIdx;
	cout<<"chaperonIndex: "<<chaperonIndex<<endl;
	proteinChaperonComplex pcc(size, argv[6], chaperonIndex, argv[7]);	
		
	pcc.maxRangeOfLocalConf = atoi(argv[3]);
	pcc.simulationFactor = strtod(argv[5], NULL);
	pcc.generalCounter = 0;
	pcc.edgesProbability = edgesProbability;
	
		
	sprintf(pcc.outputDatafileName, "%schap%d-", argv[8], chaperonIndex);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<pcc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"simulationFactor: "<<argv[5]<<"\n";
	cout<<"configFileName: "<<argv[6]<<endl;
	cout<<"outputdir: "<<argv[8]<<endl;
	cout<<"edgesProbability: "<<pcc.edgesProbability<<endl;
	line = getIntegerFromFile(indexFile, 0);
	cout<<"line: "<<line<<endl;
	for(int idx = 0; (line = getIntegerFromFile(indexFile, idx)) != -1; idx++)
	{
		cout<<"here!"<<endl;
		if(!pcc.foldInChaperonWithBindReleaseMechanism(iterations, 
								numOfTimesEach, 
								line, 
								inChaperon,
								dynamic,
								bindInterval,
		                    			        releaseInterval,
		                        			energyThreshold) )
				break;
				
		cout<<"line: "<<line<<", ";
	}
		
	cout<<endl;
	return 1;
}

int minimumEnergyGrouping(int argc, char**argv)
{
	if(argc < 9)
	{
		cout<<"1. sizeOfResidueArray 2. iterations 3. maxRangeOfLocalConf"<<endl;
		cout<<"4. numOfTimesEach 5. simulationFactor 6. seq_config_fileName 7. index_fileName"<<endl;
		cout<<"8. outputdir"<<endl;
		exit(0);
	}
	cout<<"Executing protein grouping simulation.V1\n";

	//1. sizeOfResidueArray:
	int size = atoi(argv[1]);

	//6. seq_config_fileName
	char* confFileName = argv[6];

	foldingComplex FC(size, confFileName, 0);
	
	//2. iterations
	int iterations = atoi(argv[2]);
	
	//3. maxRangeOfLocalConf
	FC.maxRangeOfLocalConf = atoi(argv[3]);
	
	//4. numOfTimesEach	
	int numOfTimesEach = atoi(argv[4]);
	
	//5. simulationFactor
	FC.simulationFactor = strtod(argv[5], NULL);
	
	//7. index_fileName
	char *indexFile = argv[7];
	int line;

	//8. outputdir	
	sprintf(FC.outputDatafileName, "%s", argv[8]);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<FC.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"simulationFactor: "<<FC.simulationFactor<<endl;
	cout<<"configFileName: "<<confFileName<<endl;
	cout<<"outputdir: "<<FC.outputDatafileName<<endl;
	cout<<"edgesProbability: "<<FC.edgesProbability<<endl;

	for(int idx = 0; (line = getIntegerFromFile(indexFile, idx)) != -1; idx++)
	{
		cout<<"index number: "<<line<<endl;
		FC.foldToMinimumEnergy(iterations, numOfTimesEach, line);
	}
	return 1;
}

int monomerFoldInChaperone(int argc, char**argv)
{
	if(argc < 12)
	{
		cout<<"monomerFoldInChaperone"<<endl;
		cout<<"1.residueSize 2.iterations 3.maxRangeOfLocalConf 4.numOfTimesEach\n";
		cout<<"5.simulationFactor 6.seqConfigFileName 7.chaperonConfFileName\n"\
			  "8.outputdir 9.chapIdx 10.edgesProbability 11.indexFile 12.[chaperonIndex] 13.[dynamic]\n"\
			  "[ 14.bindInterval 15.releaseInterval 16.energyThreshold 17.addedX 18.addedY]\n";
		exit(0);
	}
	cout<<"Executing protein chaperon simulation.\nmonomerFoldInChaperone\n";
	int size = atoi(argv[1]);
	int iterations = atoi(argv[2]);
	int numOfTimesEach = atoi(argv[4]);
	double chapIdx = strtod(argv[9], NULL);//fromTmp
	int edgesProbability = (int)(3.0/strtod(argv[10], NULL)) - 1;//double toTmp
	
	char *indexFile = argv[11];
	int chaperonIndex = 0;
	bool inChaperon = false;
	int bindInterval = 1;
	int releaseInterval = iterations + 1;
	double energyThreshold = 0;
	
	
	if(argc > 12)
	{
		inChaperon = true;
		chaperonIndex = atoi(argv[12]);
		cout<<"Folding in chaperone index number: "<<chaperonIndex<<endl;
	}
	else
	{
		chaperonIndex = 0;	
		cout<<"Folding without chaperon\n";
	}
	
	bool dynamic = false;
	if(argc > 11)
	{
		dynamic = atoi(argv[13]);	
		cout<<"Dynamic (steps) chaperone complexd is: "<<dynamic<<endl;
	}
	
	int addedX, addedY;
	if(argc == 19)
	{
		bindInterval = atoi(argv[14]);
		releaseInterval = atoi(argv[15]);
		energyThreshold = strtod(argv[16], NULL);
		addedX = atoi(argv[17]);
		addedY = atoi(argv[18]);
		cout<<"bindInterval: "<<bindInterval<<endl;
		cout<<"releaseInterval: "<<releaseInterval<<endl;
		cout<<"energyThreshold: "<<energyThreshold<<endl;
		cout<<"addedX: "<<addedX<<endl;
		cout<<"addedY: "<<addedY<<endl;
		
	}	
	int line;

	chaperonIndex = chapIdx;
	cout<<"chaperonIndex: "<<chaperonIndex<<endl;
	proteinChaperonComplex pcc(size, argv[6], chaperonIndex, argv[7]);	
		
	pcc.maxRangeOfLocalConf = atoi(argv[3]);
	pcc.simulationFactor = strtod(argv[5], NULL);
	pcc.generalCounter = 0;
	pcc.edgesProbability = edgesProbability;
	
	pcc.added_confinedX = sqrt((double)pcc.sizeOfResidueArray) + addedX;
	pcc.added_confinedY = sqrt((double)pcc.sizeOfResidueArray) + addedY;

		
	sprintf(pcc.outputDatafileName, "%schap%d-", argv[8], chaperonIndex);
	
	cout<<"Session Details:\n";
	cout<<"----------------\n";
	cout<<"residueSize: "<<size<<endl;
	cout<<"iterations: "<<iterations<<endl;
	cout<<"maxRangeOfLocalConf: "<<pcc.maxRangeOfLocalConf<<endl;
	cout<<"numOfTimesEach: "<<numOfTimesEach<<endl;
	cout<<"simulationFactor: "<<argv[5]<<"\n";
	cout<<"configFileName: "<<argv[6]<<endl;
	cout<<"outputdir: "<<argv[8]<<endl;
	cout<<"edgesProbability: "<<pcc.edgesProbability<<endl;
	cout<<"added_confinedX: "<<pcc.added_confinedX<<endl;
	cout<<"added_confinedY: "<<pcc.added_confinedY<<endl;
	line = getIntegerFromFile(indexFile, 0);
	cout<<"line: "<<line<<endl;
	for(int idx = 0; (line = getIntegerFromFile(indexFile, idx)) != -1; idx++)
	{
		cout<<"here!"<<endl;
		if(!pcc.foldInChaperonWithBindReleaseMechanism(iterations, 
								numOfTimesEach, 
								line, 
								inChaperon,
								dynamic,
								bindInterval,
		                    			        releaseInterval,
		                        			energyThreshold) )
				break;
				
		cout<<"line: "<<line<<", ";
	}
		
	cout<<endl;
	return 1;
}
