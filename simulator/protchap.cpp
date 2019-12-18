//File: protchap.cpp

#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <stdio.h>
//#include <stdio.h>

#include "protchap.h"
#include "utilities.h"

char VERSION[100] = "Version 23-08-11, V21 protchap.cpp";


//V21
#if 1
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
												/*	      H	     P	       +      - */	
double foldingComplex::energyMatrix[4][4] =	
											/* H */ {{ -1.0 ,   0.0    ,  0.0 ,   0.0  },
 											/* P */  {  0.0  , -0.75   , -0.25 , -0.25  },
											/* + */  {  0.0  , -0.25  ,  +1.0 ,  -1.25  },
											/* - */  {  0.0  , -0.25  ,  -1.25 , +1.0  } };
					
#endif

//V20
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
												/*	      H	     P	       +      - */	
double foldingComplex::energyMatrix[4][4] =	/* H */ {{ -0.75 ,  0.0    ,  0.0 ,  0.0  },
 											/* P */  {  0.0  , -0.625  ,  -0.25 ,-0.25  },
											/* + */  {  0.0  , -0.25  ,  +1.0 , -1.0  },
											/* - */  {  0.0  , -0.25  ,  -1.0 , +1.0  } };
					
#endif
//V16
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double foldingComplex::energyMatrix[4][4] =	  /* H */ {{ -0.8     ,  0.0    ,  +0.0625 ,  +0.0625  },
 											 /* P */  {  0.0     , -0.7   ,  -0.375 , -0.375  },
											 /* + */  {  +0.0625  , -0.375  ,  +1.0 , -1.125  },
											 /* - */  {  +0.0625  , -0.375  ,  -1.125 , +1.0  } };
					
#endif

//V11
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double foldingComplex::energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.0625 ,  +0.0625  },
 											 /* P */  {  0.0     , -0.625   ,  -0.375 , -0.375  },
											 /* + */  {  +0.0625  , -0.375  ,  +1.0 , -1.125  },
											 /* - */  {  +0.0625  , -0.375  ,  -1.125 , +1.0  } };
					
#endif

//V10
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double foldingComplex::energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.0625 ,  +0.0625  },
 							 				 /* P */  {  0.0     , -0.625   ,  -0.25 , -0.25  },
											 /* + */  {  +0.0625  , -0.25  ,  +1.0 , -1.125  },
											 /* - */  {  +0.0625  , -0.25  ,  -1.125 , +1.0  } };
					
#endif

//V9
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double foldingComplex::energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.125 ,  +0.125  },
 							 				/* P */  {  0.0     , -0.625   ,  -0.25 , -0.25  },
											 /* + */  {  +0.125  , -0.25  ,  +1.0 , -1.125  },
											 /* - */  {  +0.125  , -0.25  ,  -1.125 , +1.0  } };
					
#endif

//V6
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
														/*	H	       P	      +	        - */	
double foldingComplex::energyMatrix[4][4] =	  /* H */ {{ -1.0     ,  0.0    ,  +0.125 ,  +0.125  },
 											  /* P */  {  0.0     , -0.75   ,  -0.125 , -0.125  },
											  /* + */  {  +0.125  , -0.125  ,  +1.0 , -1.0  },
											  /* - */  {  +0.125  , -0.125  ,  -1.0 , +1.0  } };
					
#endif
//V4
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
													  /*	H	       P	      +	        - */	
double foldingComplex::energyMatrix[4][4] =	  /* H */ {{ -1.0     ,  0.0    ,  +0.125 ,  +0.125  },
 											  /* P */  {  0.0     , -0.5   ,  -0.125 , -0.125  },
											  /* + */  {  +0.125  , -0.125  ,  +1.0 , -1.0  },
											  /* - */  {  +0.125  , -0.125  ,  -1.0 , +1.0  } };
					
#endif

//V3
#if 0
							  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
							 					 /*	 	    H	       P	     +	        -     */	
double foldingComplex::energyMatrix[4][4] =	  /* H */ {{  -0.3     ,  0.0   ,  +0.3    ,  +0.3  },
 											  /* P */  {   0.0     ,  0.0   ,  -0.25   ,  -0.1  },
											  /* + */  {  +0.3     , -0.25  ,  +0.1    ,  -0.7  },
											  /* - */  {  +0.3     , -0.1   ,  -0.7    ,   0.0  } };
		
#endif

//V2
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
													  /*	 	  H	     P	     +	    - */	
double foldingComplex::energyMatrix[4][4] =	  /* H */ {{ -1.0     ,  0.0    ,  +0.125 ,  +0.125  },
 											  /* P */  {  0.0     , -0.25   ,  -0.125 , -0.125  },
											  /* + */  {  +0.125  , -0.125  ,  +1.0 , -1.0  },
											  /* - */  {  +0.125  , -0.125  ,  -1.0 , +1.0  } };
					
#endif

#if 0
double foldingComplex::energyMatrix[4][4] =
							  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
							  /*	 	  H	     P	     +	    - */	
	  						  /* H */ {{ -1.0  ,  0.0,   0.0 ,  0.0  },
 							  /* P */  {  0.0  ,  0.0 ,  -0.125 , -0.125  },
							  /* + */  {  0.0  , -0.125  ,  +1.0 , -1.0  },
							  /* - */  {  0.0  , -0.125  ,  -1.0 , +1.0  } };

#endif


#if 0

							  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
							  /*	 	  H	     P	     +	    - */	
double energyMatrix[4][4] =	  /* H */ {{ -1.0  ,  0.0  ,   0.0 ,  0.0  },
 							  /* P */  {  0.0  ,  0.0  ,  -0.5 , -0.5  },
							  /* + */  {  0.0  , -0.5  ,  +1.0 , -1.0  },
							  /* - */  {  0.0  , -0.5  ,  -1.0 , +1.0  } };
							  
#endif

#if 0
							  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
							  /*	 	  H	     P	     +	    - */	
double energyMatrix[4][4] =	  /* H */ {{ -1.0  , -0.125,   0.0 ,  0.0  },
 							  /* P */  { -0.125, -0.75 ,  -0.5 , -0.5  },
							  /* + */  {  0.0  , -0.5  ,  +1.0 , -1.0  },
							  /* - */  {  0.0  , -0.5  ,  -1.0 , +1.0  } };

#endif




int foldingComplex::modifyBestFoldingArray()
{
  //cout<<"new modifyBestFoldingArray "<<endl;
	if(rmsd) {
		
	if(bestFoldingArray.energy + 0.5 > energy)
	{
		
		double error = rmsd->compute(*this);
		//cout<<"new modifyBestFoldingArray "<<error<<endl;
		if(error < 0.21)
		{
			bestFoldingArray.energy = energy;
			bestFoldingArray.stepNumber = enteringMCAnneal;
			for(int i = 1; i <= sizeOfResidueArray; i++)
				bestFoldingArray.res[i] = res[i];
			firstPassageTime = true;
			return 1;
		}
		else if(bestFoldingArray.energy > energy)
		{
			bestFoldingArray.energy = energy;
			bestFoldingArray.stepNumber = enteringMCAnneal;
			for(int i = 1; i <= sizeOfResidueArray; i++)
				bestFoldingArray.res[i] = res[i];
		}	
			
		
	}
	
	return 0;
	}
	else {
	//cout<<"else"<<endl;

//int foldingComplex::modifyBestFoldingArray()
//{
	//cout<<"foldingArray::modify\n";
#if CONFINED_FOLD
	if(isOnConfinedFold == false)
	{
		bestFoldingArray.energy = energy;
		bestFoldingArray.stepNumber = enteringMCAnneal;
		for(int i = 1; i <= sizeOfResidueArray; i++)
			bestFoldingArray.res[i] = res[i];
	}
	else
#endif					
	if(bestFoldingArray.energy > energy)
	{
		bestFoldingArray.energy = energy;
		bestFoldingArray.stepNumber = enteringMCAnneal;
		for(int i = 1; i <= sizeOfResidueArray; i++)
			bestFoldingArray.res[i] = res[i];
		
	}
	}
	return 0;

}

int foldingComplex::initFoldingComplex()
{
	//cout<<"foldingArray::modify\n";
	
	point zerop(0,0);
	//maxRangeOfLocalConf = MAX_DBLIB_ENUMERATION;
	energy = 0;
	
	firstPassageTime = false;
	Ck = ALPHA_UPPER_BOND;
	successCtr = 0;
	enteringMCAnneal = 0;
	successLocalConf = 0; 
	enterLocalConf = 1;
	//sideStructDBsize = DEFAULT_SIDE_STRUCT_DB_SIZE;
//initialize arrays:

	//char *hp = CfileHdlr.getHPconfiguration();
	int i, y, x;

	for(i = 1; i <= sizeOfResidueArray; i++)
	{
		tmpArr[i] = zerop;
		//hp[i] == 'B' ? res[i].mode = 0 : res[i].mode = 1;
	}
		
		
	for(y = 0; y < top_y; y++)
		for(x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
	bestFoldingArray.energy = 0;
	bestFoldingArray.stepNumber = 0;
#if 1
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		res[i].position.x = bestFoldingArray.res[i].position.x = i - 1;
		res[i].position.y = bestFoldingArray.res[i].position.y = sizeOfResidueArray/2;
	}
#endif
	
#if 0
	for(int i = 1, j = 0, m = 1; i <= sizeOfResidueArray/2; i++, j++, m+=2)
	{
		res[m].position.x = i - 1;
		res[m].position.y = sizeOfResidueArray/2 + j;
		res[m+1].position.x = i;
		res[m+1].position.y = sizeOfResidueArray/2 + j;
	}
#endif
		
	for(i = 1; i <= sizeOfResidueArray; i++)
		occupyPosition(i);
	
		
		//for(int i = 1; i <= sizeOfResidueArray; i++)
			//bestFoldingArray.res[i] = res[i];
		
	
	
	return 0;

}

foldingComplex::foldingComplex(int length, char* confFileName, int useRMSD):
				 RNG(),
				 CfileHdlr(confFileName, length),
				 bestFoldingArray(length),
				 lc(),
		    	 	 residueArray(length)
{
// 	cout<<"folding complex ctor 1"<<endl;
// 	cout<<"ConfigFile: "<<confFileName<<endl;
	//cout<<"Till here !\n";
	edgesProbability = 16;//default
	rmsd = 0;
	firstPassageTime = false;
	if(useRMSD)
	{
		rmsd = new RMSD(this, sizeOfResidueArray, 0);
		if(!rmsd)
		{
			cout<<"cannot create RMSD"<<endl;
			exit(1);
		}
	}
	sideStructDBsize = DEFAULT_SIDE_STRUCT_DB_SIZE;
	simulationFactor = 1;
	edgesProbability = 16;//default
	added_confinedX = right_x - sizeOfResidueArray - 1;
	added_confinedY = top_y - sizeOfResidueArray - 1;
	alphaE = 0;
	
	top_y *= 2;
	right_x *=2;
	
	boolMatrix = new int*[top_y];
	if(!boolMatrix)
	{
		cout<<"ERROR - mem alloc - folding complex ctor\n";
		exit(1);
	}
	
	for(int i = 0; i < top_y; i++)
		if(!(boolMatrix[i] = new int[right_x]) )
		{
			cout<<"ERROR - mem alloc - folding complex ctor\n";
			exit(1);
		}							
	
	tmpArr = new point[sizeOfResidueArray + 1];	
	if(!tmpArr)
	{
		cout<<"ERROR - mem alloc - folding complex ctor\n";
		exit(1);
	}
	point zerop(0,0);
	maxRangeOfLocalConf = MAX_DBLIB_ENUMERATION;
	energy = 0;
	
	Ck = ALPHA_UPPER_BOND;
	successCtr = 0;
	enteringMCAnneal = 0;
	successLocalConf = 0; 
	enterLocalConf = 1;
	
	//initialize arrays:

	char *hp = CfileHdlr.getConfiguration(sizeOfResidueArray, 0);
	//CfileHdlr.getHPconfiguration();
	int i, y, x;

	for(i = 1; i <= sizeOfResidueArray; i++)
	{
		tmpArr[i] = zerop;
		switch(hp[i-1])
		{
			case 'H':
				res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
			
	for(y = 0; y < top_y; y++)
		for(x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
	
	for(i = 1; i <= sizeOfResidueArray; i++)
		occupyPosition(i);
//		boolMatrix[res[i].position.y][res[i].position.x] |= 1;

// 	cout<<"Finished ctor successfuly\n";		
			
}
foldingComplex::foldingComplex(int length):
				 RNG(),
				 bestFoldingArray(length),
				 lc(),
		     residueArray(length)
{
// 	cout<<"folding complex ctor 1"<<endl;
	
	//cout<<"Till here !\n";
	edgesProbability = 16;//default
	rmsd = 0;
	firstPassageTime = false;
	
	sideStructDBsize = DEFAULT_SIDE_STRUCT_DB_SIZE;
	simulationFactor = 1;
	edgesProbability = 16;//default
	added_confinedX = right_x - sizeOfResidueArray - 1;
	added_confinedY = top_y - sizeOfResidueArray - 1;
	alphaE = 0;
	
	top_y *= 2;
	right_x *=2;
	
	boolMatrix = new int*[top_y];
	if(!boolMatrix)
	{
		cout<<"ERROR - mem alloc - folding complex ctor\n";
		exit(1);
	}
	
	for(int i = 0; i < top_y; i++)
		if(!(boolMatrix[i] = new int[right_x]) )
		{
			cout<<"ERROR - mem alloc - folding complex ctor\n";
			exit(1);
		}							
	
	tmpArr = new point[sizeOfResidueArray + 1];	
	if(!tmpArr)
	{
		cout<<"ERROR - mem alloc - folding complex ctor\n";
		exit(1);
	}
	point zerop(0,0);
	maxRangeOfLocalConf = MAX_DBLIB_ENUMERATION;
	energy = 0;
	
	Ck = ALPHA_UPPER_BOND;
	successCtr = 0;
	enteringMCAnneal = 0;
	successLocalConf = 0; 
	enterLocalConf = 1;
	
	//initialize arrays:

	int i, y, x;

	for(i = 1; i <= sizeOfResidueArray; i++)
	{
		tmpArr[i] = zerop;
		res[i].mode = POLAR_NEUTRAL;	
	}
			
	for(y = 0; y < top_y; y++)
		for(x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
	
	for(i = 1; i <= sizeOfResidueArray; i++)
		occupyPosition(i);
//		boolMatrix[res[i].position.y][res[i].position.x] |= 1;

// 	cout<<"Finished ctor successfuly\n";		
			
}


foldingComplex::foldingComplex(int length, char* name, char* confFileName):
				 RNG(),
				 CfileHdlr(confFileName, length),
				 bestFoldingArray(length),
				 lc(),
			     residueArray(length, name)
{
	cout<<"folding complex ctor 2"<<endl;
	point zerop(0,0);
	maxRangeOfLocalConf = MAX_DBLIB_ENUMERATION;
	energy = 0;
	rmsd = 0;
	firstPassageTime = false;
	//rmsd = new RMSD(this, sizeOfResidueArray, 0);
	edgesProbability = 16;//default
	simulationFactor = 1;
	sideStructDBsize = DEFAULT_SIDE_STRUCT_DB_SIZE;
	boolMatrix = new int*[top_y];
	alphaE = 0;
	
	if(!boolMatrix)
	{
		cout<<"ERROR - mem alloc - folding complex ctor\n";
		exit(1);
	}
	
	for(int i = 0; i < top_y; i++)
		if(!(boolMatrix[i] = new int[right_x]) )
		{
			cout<<"ERROR - mem alloc - folding complex ctor\n";
			exit(1);
		}
	
	tmpArr = new point[sizeOfResidueArray + 1];	
	if(!tmpArr)
	{
		cout<<"ERROR - mem alloc - folding complex ctor\n";
		exit(1);
	}
		
	Ck = ALPHA_UPPER_BOND;
	successCtr = 0;
	enteringMCAnneal = 0;
	successLocalConf = 0; 
	enterLocalConf = 1;
	
	//initialize arrays:

	char *hp = CfileHdlr.getHPconfiguration();
	int i, y, x;

	for(i = 1; i <= sizeOfResidueArray; i++)
	{
		tmpArr[i] = zerop;
		switch(hp[i-1])
		{
			case 'H':
				res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
			
	for(y = 0; y < top_y; y++)
		for(x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
	
	for(i = 1; i <= sizeOfResidueArray; i++)
		occupyPosition(i);
//		boolMatrix[res[i].position.y][res[i].position.x] |= 1;				
}

foldingComplex::foldingComplex(char* name, char* confFileName):residueArray(name), 
				 RNG(),
				 lc(),
				 CfileHdlr(confFileName, sizeOfResidueArray),
				 bestFoldingArray(sizeOfResidueArray)
{
	cout<<"folding complex ctor 3"<<endl;
	point zerop(0,0);
	maxRangeOfLocalConf = MAX_DBLIB_ENUMERATION;
	energy = 0;
	rmsd = 0;
	firstPassageTime = false;

	//rmsd = new RMSD(this, sizeOfResidueArray, 0);
	simulationFactor = 1;
	edgesProbability = 16;//default
	boolMatrix = new int*[top_y];
	alphaE = 0;
	
	if(!boolMatrix)
	{
		cout<<"ERROR - mem alloc - folding complex ctor\n";
		exit(1);
	}
	
	for(int i = 0; i < top_y; i++)
		if(!(boolMatrix[i] = new int[right_x]) )
		{
			cout<<"ERROR - mem alloc - folding complex ctor\n";
			exit(1);
		}
	
	tmpArr = new point[sizeOfResidueArray + 1];	
	if(!tmpArr)
	{
		cout<<"ERROR - mem alloc - folding complex ctor\n";
		exit(1);
	}
		
	Ck = ALPHA_UPPER_BOND;
	successCtr = 0;
	enteringMCAnneal = 0;
	successLocalConf = 0; 
	enterLocalConf = 1;
	//initialize arrays:

	char *hp = CfileHdlr.getHPconfiguration();
	int i, y, x;

	for(i = 1; i <= sizeOfResidueArray; i++)
	{
		tmpArr[i] = zerop;
		switch(hp[i-1])
		{
			case 'H':
				res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
			
	for(y = 0; y < top_y; y++)
		for(x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
	
	for(i = 1; i <= sizeOfResidueArray; i++)
		occupyPosition(i);
//		boolMatrix[res[i].position.y][res[i].position.x] |= 1;				
}

foldingComplex::~foldingComplex()
{
// 	cout<<"~foldingComplex\n";
	for(int i = 0; i < top_y; i++)
		delete []boolMatrix[i];
	if(boolMatrix)
		delete []boolMatrix;
	if(tmpArr)
		delete []tmpArr;
	if(rmsd)
		delete rmsd;	
}

int foldingComplex::randLocalMod(int pivot)
{
	if(pivot > (sizeOfResidueArray - 2))
		return 0;
	
	enterLocalConf++;
	
	point p1, p2;
	
	int  max_res = maxRangeOfLocalConf;
	if((max_res + pivot) > sizeOfResidueArray)
		max_res = sizeOfResidueArray - pivot;
	
	int dres = RNG.generateNumberInRange(2, max_res);
	
	point* parr = lc.getNewLocalConf(res[pivot].position, res[pivot + dres].position, dres);
	 
	if( parr == NULL )
	{
//		cout<<"parr == NULL "<<"dres: "<<dres<<endl;
		return 0;
	}
	
	/* On success */
	/*
	cout<<"pivot: "<<pivot<<endl;	
	cout<<"lc.pivotPoint: "<<lc.pivotPoint.x<<", "<<lc.pivotPoint.y<<endl;
	cout<<"other point: "<<res[pivot+2].position.x<<" ,"<<res[pivot+2].position.y<<endl;
	cout<<"res[pivot].position: "<<res[pivot].position.x<<" ,"<<res[pivot].position.y<<endl;
	//cout<<"Matrix before:\n";
	//printBoolMatrix();
	*/
	int i, j;
	for(i = pivot + 1, j = 0; i <= (pivot + dres - 1); i++, j++)
	{
		//cout<<"parr[j]: "<<parr[j].x<<" ,"<<parr[j].y<<endl;
		tmpArr[i] = parr[j] + lc.pivotPoint;//res[pivot].position;
		dismissPosition(i);
	}
	
	
	for(i = pivot + 1, j = 0; i <= (pivot + dres - 1); i++, j++)//(i = 0; i < dres - 1; i++)
	{	 
		if(!isVacant(tmpArr[i]))
		{
			for(j = pivot + 1; j <= (pivot + dres - 1); j++)
				occupyPosition(j);//by the old Residue array
			//cout<<"Non vacant: "<<tmpArr[i]<<endl;
			return 0;
		}
	}
	/* All points are vacant */
	for(j = pivot + 1; j <= (pivot + dres - 1); j++)
	{
			occupyPositionByTmpArr(j);
			//res[j].position = tmpArr[j];//tmp!!!!!
	}
			
		
	double newEnergy = calculateEnergy(pivot, dres);
	//if(newEnergy <= energy)
	//cout<<"new energy: "<<newEnergy<<", energy: " <<energy<<endl;
	if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders(pivot, dres))
	{
		energy = newEnergy;
		for(j = pivot + 1; j <= (pivot + dres - 1); j++)
			res[j].position = tmpArr[j];
		modifyBestFoldingArray();
		successLocalConf++;
		
		return 1;
	}
	else
	{
		for(j = pivot + 1; j <= (pivot + dres - 1); j++)
			dismissPosition(tmpArr[j]);
		for(j = pivot + 1; j <= (pivot + dres - 1); j++)
			occupyPosition(j);
		return 0;
	}
	
	return 0;
}
		
	
	
	
int foldingComplex::tailRotateLeft(int pivot)
{
	// x = -y + dx + dy
	// y =  x - dx + dy
	point newp;
		
	//Right end:
	if(pivot > 1)
	{
	
		newp.x = res[sizeOfResidueArray - 1].position.x +
			 res[sizeOfResidueArray - 1].position.y -
			 res[sizeOfResidueArray].position.y;
		
		newp.y = res[sizeOfResidueArray].position.x -
			 res[sizeOfResidueArray - 1].position.x +
			 res[sizeOfResidueArray - 1].position.y;
			 

		
		if(isVacant(newp))
		{
			dismissPosition(sizeOfResidueArray);
			point prevp = res[sizeOfResidueArray].position;
			res[sizeOfResidueArray].position = newp;
			occupyPosition(sizeOfResidueArray);

			double newEnergy = calculateEnergy();
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders())
			{
				energy = newEnergy;
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(sizeOfResidueArray);
				res[sizeOfResidueArray].position = prevp;
				occupyPosition(sizeOfResidueArray);
				return 0;
			}
				
			
		}
	}
	//Left end:
	else
	{
		newp.x = res[2].position.x + 
			 res[2].position.y - 
			 res[1].position.y;
		
		newp.y = res[1].position.x -
			 res[2].position.x +
			 res[2].position.y;
		
		if(isVacant(newp))
		{
			dismissPosition(1);
			point prevp = res[1].position;
			res[1].position = newp;
			occupyPosition(1);

			double newEnergy = calculateEnergy();
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders())
			{
				energy = newEnergy;
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(1);
				res[1].position = prevp;
				occupyPosition(1);
				return 0;
			}
				
			
		}
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
	}
	return 0;
}

int foldingComplex::tailRotateRight(int pivot)
{
	point newp;
	// x =  y -dy+dx
	// y = -x +dx+dy
	
	//There is no need to initialize tmpArr because we know the
	//positions of update
	
	//Right end:
	if(pivot > 1)
	{
		newp.x = res[sizeOfResidueArray].position.y - 
			 res[sizeOfResidueArray - 1].position.y + 
			 res[sizeOfResidueArray - 1].position.x;
		
		newp.y = - res[sizeOfResidueArray].position.x +
			 res[sizeOfResidueArray - 1].position.x +
			 res[sizeOfResidueArray - 1].position.y;
			 
		if(isVacant(newp))
		{
			dismissPosition(sizeOfResidueArray);
			point prevp = res[sizeOfResidueArray].position;
			res[sizeOfResidueArray].position = newp;
			occupyPosition(sizeOfResidueArray);

			double newEnergy = calculateEnergy();
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders())
			{
				energy = newEnergy;
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(sizeOfResidueArray);
				res[sizeOfResidueArray].position = prevp;
				occupyPosition(sizeOfResidueArray);
				return 0;
			}
				
			
		}
	}
	//Left end:
	else
	{
		newp.x = res[1].position.y - 
			 res[2].position.y + 
			 res[2].position.x;
		
		newp.y = - res[1].position.x +
			 res[2].position.x +
			 res[2].position.y;
		
		if(isVacant(newp))
		{
			dismissPosition(1);
			point prevp = res[1].position;
			res[1].position = newp;
			occupyPosition(1);

			double newEnergy = calculateEnergy();
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders())
			{
				energy = newEnergy;
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(1);
				res[1].position = prevp;
				occupyPosition(1);
				return 0;
			}
				
			
		}
		
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
	}
	return 0;
}

int foldingComplex::tailRotate180(int pivot)
{
	point newp;
		
	//Right end:
	if(pivot > 1)
	{
		newp.x = - res[sizeOfResidueArray].position.x + 2*res[sizeOfResidueArray - 1].position.x;
		newp.y = - res[sizeOfResidueArray].position.y + 2*res[sizeOfResidueArray - 1].position.y;
		
		
		if(isVacant(newp))
		{
			dismissPosition(sizeOfResidueArray);
			point prevp = res[sizeOfResidueArray].position;
			res[sizeOfResidueArray].position = newp;
			occupyPosition(sizeOfResidueArray);

			double newEnergy = calculateEnergy();
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders())
			{
				energy = newEnergy;
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(sizeOfResidueArray);
				res[sizeOfResidueArray].position = prevp;
				occupyPosition(sizeOfResidueArray);
				return 0;
			}
				
			
		}
	}
	//Left end:
	else
	{
		newp.x = - res[1].position.x + 2*res[2].position.x;
		newp.y = - res[1].position.y + 2*res[2].position.y;
		
		if(isVacant(newp))
		{
			dismissPosition(1);
			point prevp = res[1].position;
			res[1].position = newp;
			occupyPosition(1);

			double newEnergy = calculateEnergy();
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders())
			{
				energy = newEnergy;
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(1);
				res[1].position = prevp;
				occupyPosition(1);
				return 0;
			}
				
			
		}	
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
	}
	return 0;
}


//rotate from the residue after the pivot until the edge
int foldingComplex::fixedRotateLeft(int pivot)
{
	point newp;
	int i, j;
	//clean boolMatrix from occupied cordinates from position of pivot+1:
	for(i = pivot + 1; i <= sizeOfResidueArray; i++)
		dismissPosition(i);
	

	
	for(i = pivot + 1; i <= sizeOfResidueArray; i++)
	{	
		newp.x = res[pivot].position.x + 
			 res[pivot].position.y - 
			 res[i].position.y;
		
		newp.y = res[i].position.x -
			 res[pivot].position.x +
			 res[pivot].position.y;
	
		if(isVacant(newp))
		{
			//cout<<"point: ("<<newp.x<<", "<<newp.y<<") - is vacant\n";
			tmpArr[i] = newp;
		}
		else
		{
			//reoccuping the boolMatix by the old cordinates
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				occupyPosition(j);
			return 0;
		}	
//		res[i].position = newp;
	}
	//if folding doesn't runover anything
	if(i > sizeOfResidueArray)
	{
		/*
		for(int j = pivot + 1; j <= sizeOfResidueArray; j++)
		{
			res[j].position = tmpArr[j];
			occupyPosition(j);
		}
		reurn 1;
		*/
		for(j = pivot + 1; j <= sizeOfResidueArray; j++)
			occupyPositionByTmpArr(j);
		
		double newEnergy = calculateEnergy(pivot);
		//if(newEnergy <= energy)
		if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders(pivot))
		{
			energy = newEnergy;
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				res[j].position = tmpArr[j];
			modifyBestFoldingArray();
			return 1;
		}
		else
		{
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				dismissPosition(tmpArr[j]);
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				occupyPosition(j);
			return 0;
		}
	}
		
	
	return 0;
}

int foldingComplex::fixedRotateRight(int pivot)
{
	point newp;
	int i, j;
	//clean boolMatrix from occupied cordinates from position of pivot+1:
	for(i = pivot + 1; i <= sizeOfResidueArray; i++)
		dismissPosition(i);
	//cout<<"This is the new foldingComplex fixedRotateRight func !!!\n";
	
	
	for(i = pivot + 1; i <= sizeOfResidueArray; i++)
	{	
		newp.x = res[i].position.y - 
			 res[pivot].position.y + 
			 res[pivot].position.x;
		
		newp.y = - res[i].position.x +
			 res[pivot].position.x +
			 res[pivot].position.y;
			 
		if(isVacant(newp))
			tmpArr[i] = newp;
		else
		{
			//reoccuping the boolMatix by the old cordinates
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				occupyPosition(j);
			return 0;
		}
		//res[i].position = newp;
	}
	//if folding doesn't runover anything
	if(i > sizeOfResidueArray)
	{
		/*
		for(int j = pivot + 1; j <= sizeOfResidueArray; j++)
		{
			res[j].position = tmpArr[j];
			occupyPosition(j);
		}
		return 1;
		*/
		for(j = pivot + 1; j <= sizeOfResidueArray; j++)
			occupyPositionByTmpArr(j);
		
		double newEnergy = calculateEnergy(pivot);
		//if(newEnergy <= energy)
		if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders(pivot))
		{
			energy = newEnergy;
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				res[j].position = tmpArr[j];
			
			modifyBestFoldingArray();
			return 1;
		}
		else
		{
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				dismissPosition(tmpArr[j]);
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				occupyPosition(j);
			return 0;
		}
	}
	return 0;
}

int foldingComplex::fixedRotate180(int pivot)
{
	point newp;
	int i, j;
	//clean boolMatrix from occupied cordinates from position of pivot+1:
	for(i = pivot + 1; i <= sizeOfResidueArray; i++)
		dismissPosition(i);
	
	for(i = pivot + 1; i <= sizeOfResidueArray; i++)
	{
		newp.x = - res[i].position.x + 2*res[pivot].position.x;
		newp.y = - res[i].position.y + 2*res[pivot].position.y;
		
		if(isVacant(newp))
			tmpArr[i] = newp;
		else
		{
			//reoccuping the boolMatix by the old cordinates
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				occupyPosition(j);
			return 0;
		}
		//res[i].position = newp;
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
	}
	//if folding doesn't runover anything
	if(i > sizeOfResidueArray)
	{
		/*
		for(int j = pivot + 1; j <= sizeOfResidueArray; j++)
		{
			res[j].position = tmpArr[j];
			occupyPosition(j);
		}
		*/
		for(j = pivot + 1; j <= sizeOfResidueArray; j++)
			occupyPositionByTmpArr(j);
		
		double newEnergy = calculateEnergy(pivot);
		//if(newEnergy <= energy)
		if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders(pivot))
		{
			energy = newEnergy;
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				res[j].position = tmpArr[j];
				
			modifyBestFoldingArray();
			return 1;
		}
		else
		{
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				dismissPosition(tmpArr[j]);
			for(j = pivot + 1; j <= sizeOfResidueArray; j++)
				occupyPosition(j);
		
			return 0;
		}
			
	}
	return 0;
}
	
int foldingComplex::flipflopCorner(int pivot)
{
	//cout<<"Start flipflop. Pivot number:"<<pivot<<endl;
	//check if pivot is a corner:
	point arr[3]; 
	arr[0] = getDirection(pivot, pivot - 1);

	arr[2] = getDirection(pivot, pivot + 1);
	
	if(arr[0].abs() == arr[2].abs())
		return 0;//not a corner

	arr[0] = res[pivot - 1].position;	
	arr[1] = res[pivot].position;
	arr[2] = res[pivot + 1].position;
	
	//Get the smallest of the three points:
	point dp;
	
	int smallest;
	
	if(arr[0].x<arr[1].x)
	{
		if(arr[0].x<arr[2].x)
		//arr[0]<arr[2]<arr[1]
			smallest = 0;
		else
		//arr[2]<arr[0]<arr[1]
			smallest = 2;
	}
	else//arr[1]<arr[0]
	{
		if(arr[1].x<arr[2].x)
			smallest = 1;
		else//arr[2]<arr[1]<arr[0]
			smallest = 2;
	}
	dp.x = arr[smallest].x;
	
	if(arr[0].y<arr[1].y)
	{
		if(arr[0].y<arr[2].y)
		//arr[0]<arr[2]<arr[1]
			smallest = 0;
		else
		//arr[2]<arr[0]<arr[1]
			smallest = 2;
	}
	else//arr[1]<arr[0]
	{
		if(arr[1].y<arr[2].y)
			smallest = 1;
		else//arr[2]<arr[1]<arr[0]
			smallest = 2;
	}
	dp.y = arr[smallest].y;
	
	//cout<<"Point 0: ("<<arr[0].x<<", "<<arr[0].y<<") \n";
	//cout<<"Point 1: ("<<arr[1].x<<", "<<arr[1].y<<") \n";
	//cout<<"Point 2: ("<<arr[2].x<<", "<<arr[2].y<<") \n";
	//dp = arr[smallest];
	//cout<<"dp = ("<<dp.x<<", "<<dp.y<<") \n";
	//cout<<"Point pivot before: ("<<arr[1].x<<", "<<arr[1].y<<") \n";
	arr[1] -= dp;
	
	point x(1,1);
	//cout<<"Point pivot before: ("<<arr[1].x<<", "<<arr[1].y<<") \n";
	arr[1] ^= x;
	arr[1] += dp;
	
	if(isVacant(arr[1]))
	{
		dismissPosition(pivot);
		point prevp = res[pivot].position;
		res[pivot].position = arr[1];
		occupyPosition(pivot);

		double newEnergy = calculateEnergy();
		
		//if(newEnergy <= energy)
		if(MontaCarloAnnealing(newEnergy, energy) && !outOfBorders())
		{
			energy = newEnergy;
			modifyBestFoldingArray();
			return 1;
		}
		else
		{
			//reconfiguring old point
			dismissPosition(pivot);
			res[pivot].position = prevp;
			occupyPosition(pivot);
			return 0;
		}
				
		//cout<<"Point pivot after: ("<<arr[1].x<<", "<<arr[1].y<<") \n";	
	}
	
		 
	
	return 0;
}

bool foldingComplex::outOfBorders(int pivot)
{
#if CONFINED_FOLD
	if(isOnConfinedFold)
	{
		point pdxdy = getMin_dx_dy(pivot);
		
		if( (pdxdy.x > (added_confinedX ))||
	    	(pdxdy.y > (added_confinedY ))  )
			return true;
		else
			return false;
			
		//cout<<"GOOD FOLD pdxdy: "<<pdxdy.x<<", "<<pdxdy.y<<endl;
		//CfileHdlr.writeStructure2output(sizeOfResidueArray, (residueArray *)this);

	}
#if !USE_PRE_FOLD
	else
	{
		point pdxdy = getMin_dx_dy(pivot);
		
		//from this point, no more out of border movments are allowed
		if( (pdxdy.x <= (added_confinedX ))&&
	    	(pdxdy.y <= (added_confinedY ))  )
			isOnConfinedFold = true;
		return false;
	}
#endif
						
#endif
	return false;
}	


bool foldingComplex::outOfBorders(int pivot, int range)
{
#if CONFINED_FOLD
	if(isOnConfinedFold)
	{
		point pdxdy = getMin_dx_dy(pivot, range);
		
		if( (pdxdy.x > (added_confinedX ))||
	    	(pdxdy.y > (added_confinedY ))  )
			return true;
		else
			return false;
			
		//cout<<"GOOD FOLD pdxdy: "<<pdxdy.x<<", "<<pdxdy.y<<endl;
		//CfileHdlr.writeStructure2output(sizeOfResidueArray, (residueArray *)this);

	}
#if !USE_PRE_FOLD
	else
	{
		point pdxdy = getMin_dx_dy(pivot, range);
		
		//from this point, no more out of border movments are allowed
		if( (pdxdy.x <= (added_confinedX ))&&
	    	(pdxdy.y <= (added_confinedY ))  )
			isOnConfinedFold = true;
		return false;
	}
#endif
						
#endif
	return false;
}	

bool foldingComplex::outOfBorders()
{
#if CONFINED_FOLD
	if(isOnConfinedFold)
	{
		point pdxdy = getMin_dx_dy();
		
		if( (pdxdy.x > (added_confinedX ))||
	    	(pdxdy.y > (added_confinedY ))  )
		{
			//printHPMatrix();
			//cout<<"Bad fold\n";
			return true;
		}
		else 
			return false;
			
		//cout<<"GOOD FOLD pdxdy: "<<pdxdy.x<<", "<<pdxdy.y<<endl;
		//CfileHdlr.writeStructure2output(sizeOfResidueArray, (residueArray *)this);

	}
#if !USE_PRE_FOLD
	else
	{
		point pdxdy = getMin_dx_dy();
		
		//from this point, no more out of border movments are allowed
		if( (pdxdy.x <= (added_confinedX ))&&
	    	(pdxdy.y <= (added_confinedY ))  )
			isOnConfinedFold = true;
		return false;
		
	}
#endif
						
#endif
	return false;
}	

bool foldingComplex::MontaCarloAnnealing(double newE, double oldE)
{
	
	enteringMCAnneal++;

	//return (newE <= oldE);
	if(newE < oldE)
		return true;
	else if( RNG.generateRandomFraction() <
	   exp((oldE - newE)/(Ck*simulationFactor)) )//((oldE - newE)/Ck)*simulationFactor  )
	{
		//if(newE < bestEnergy)
		//	bestEnergy = newE;	
		return true;
	}

	
	 return false;
} 	

int foldingComplex::nonEdgeSegmentFold(int pivot, int segmentLen)	
{
	return 1;
}



point foldingComplex::getMin_dx_dy(int pivot)
{
	point pdxdy;
	/*
	pdxdy.x = max(x) - min(x)
	pdxdy.y = max(y) - min(y)
	*/
	
	int minX = sizeOfResidueArray + 1, minY = sizeOfResidueArray + 1;
	int maxX = 0, maxY = 0;
	int i;
	for(i = 1; i <= pivot; i++)
	{
		if(minX > res[i].position.x)
			minX = res[i].position.x;
		if(maxX < res[i].position.x)
			maxX = res[i].position.x;
			
		if(minY > res[i].position.y)
			minY = res[i].position.y;
		if(maxY < res[i].position.y)
			maxY = res[i].position.y;
				
	}//end for loop
	for(i = pivot + 1; i <= sizeOfResidueArray; i++)
	{
		if(minX > tmpArr[i].x)
			minX = tmpArr[i].x;
		if(maxX < tmpArr[i].x)
			maxX = tmpArr[i].x;
			
		if(minY > tmpArr[i].y)
			minY = tmpArr[i].y;
		if(maxY < tmpArr[i].y)
			maxY = tmpArr[i].y;
			
	}//end for loop
	
	
	pdxdy.x = maxX - minX;
	pdxdy.y = maxY - minY;
	
	return pdxdy;
}
	
point foldingComplex::getMin_dx_dy(int pivot, int range)
{
	point pdxdy;
	/*
	pdxdy.x = max(x) - min(x)
	pdxdy.y = max(y) - min(y)
	*/
	
	int minX = sizeOfResidueArray + 1, minY = sizeOfResidueArray + 1;
	int maxX = 0, maxY = 0;
	int i;
	for(i = 1; i <= pivot; i++)
	{
		if(minX > res[i].position.x)
			minX = res[i].position.x;
		if(maxX < res[i].position.x)
			maxX = res[i].position.x;
			
		if(minY > res[i].position.y)
			minY = res[i].position.y;
		if(maxY < res[i].position.y)
			maxY = res[i].position.y;
				
	}//end for loop
	
	for(i = pivot + 1; i < range + pivot; i++)
	{
		if(minX > tmpArr[i].x)
			minX = tmpArr[i].x;
		if(maxX < tmpArr[i].x)
			maxX = tmpArr[i].x;
			
		if(minY > tmpArr[i].y)
			minY = tmpArr[i].y;
		if(maxY < tmpArr[i].y)
			maxY = tmpArr[i].y;
			
	}//end for loop
	
	for(; i <= sizeOfResidueArray; i++)
	{
		if(minX > res[i].position.x)
			minX = res[i].position.x;
		if(maxX < res[i].position.x)
			maxX = res[i].position.x;
			
		if(minY > res[i].position.y)
			minY = res[i].position.y;
		if(maxY < res[i].position.y)
			maxY = res[i].position.y;			
				
	}//end for loop
	
	pdxdy.x = maxX - minX;
	pdxdy.y = maxY - minY;
	
	return pdxdy;
}


point foldingComplex::getMin_dx_dy()
{
	point pdxdy;
	/*
	pdxdy.x = max(x) - min(x)
	pdxdy.y = max(y) - min(y)
	*/
	
	int minX, minY;
	int maxX, maxY;
	minX = maxX = res[1].position.x;
	minY = maxY = res[1].position.y;
	
	for(int i = 2; i <= sizeOfResidueArray; i++)
	{
		if(minX > res[i].position.x)
			minX = res[i].position.x;
		if(maxX < res[i].position.x)
			maxX = res[i].position.x;
			
		if(minY > res[i].position.y)
			minY = res[i].position.y;
		if(maxY < res[i].position.y)
			maxY = res[i].position.y;
	}

	pdxdy.x = maxX - minX;
	pdxdy.y = maxY - minY;
	
	return pdxdy;
	
}

int foldingComplex::fold(long times)
{
	int pivot;
	int fold_type;
	
	
	long i;
	
	/* GENERATING ARRAY IN THE BOX */
#if 1
	initFoldingComplex();		
	for(i = 0; i < NUM_OF_PRE_ITERATIONS; i++)
	{
		
		pivot = RNG.generateNumberInRange(1, sizeOfResidueArray);
		
		fold_type = RNG.generateNumberInRange(0, 12);
	
		switch(fold_type)
		{
			case 0: if((pivot == 1) || (pivot == sizeOfResidueArray))
					if(tailRotateLeft(pivot) == 1)
						successCtr++;
					break;
			case 1: if((pivot == 1) || (pivot == sizeOfResidueArray))
					if(tailRotateRight(pivot)) //
						successCtr++;
					break;
			case 2: if((pivot == 1) || (pivot == sizeOfResidueArray))
					if(tailRotate180(pivot))//2
						successCtr++; 
					
					break;
			case 3: if((pivot > 1) && (pivot < sizeOfResidueArray))
					if(flipflopCorner(pivot))//OK
						successCtr++;
				 break; 
			case 4: if(fixedRotateLeft(pivot))//3 
					successCtr++;
					break;
			
			case 5: if(fixedRotateRight(pivot))//4 
					successCtr++;
					break;
			case 6: if(fixedRotate180(pivot))// 
					successCtr++;
					break;
			default:if((pivot > 1) && (pivot < sizeOfResidueArray))
					if(flipflopCorner(pivot))//OK
						successCtr++;
			
		}
		point pdxdy = getMin_dx_dy();
		if( (pdxdy.x < (sizeOfResidueArray/BOX_SIDE_DENOMINATOR ))&&
		    (pdxdy.y < (sizeOfResidueArray/BOX_SIDE_DENOMINATOR ))  )
		{
			//printHPMatrix();
			break;
		}	
		    
		
		
	}
	//cout<<"\nGet out of the loop at: "<<i<<endl;
#endif
	successCtr = 1;
	enteringMCAnneal = 1;
			
	for(i = 0; i < times; i++)
	{
		
		pivot = RNG.generateNumberInRange(1, sizeOfResidueArray);
		fold_type = RNG.generateNumberInRange(0, 16);
	
		switch(fold_type)
		{
			
			case 0: if((pivot == 1) || (pivot == sizeOfResidueArray))
					if(tailRotateLeft(pivot) == 1)
						successCtr++;
					break;

			case 1: if((pivot == 1) || (pivot == sizeOfResidueArray))
					if(tailRotateRight(pivot)) //
						successCtr++;
					break;
			case 2: if((pivot == 1) || (pivot == sizeOfResidueArray))
					if(tailRotate180(pivot))//2
						successCtr++; 
					
					break;
				
			default: if(randLocalMod(pivot))
						successCtr++;
					break;
		
		}
		
		
		
		//DEBUG_lostRes();
		//DEBUG_outOfLimitRes();
		if(i%ALPHA_ITR == 0)
		{
			Ck *= ALPHA;
			if(Ck < ALPHA_LOWER_BOND)
				Ck = ALPHA_LOWER_BOND;
			//cout<<"MCAnnealing:"<<exp( ((-1)/Ck) )<<endl;	
		}	
	}//end for
#if 1	
	cout<<"protSimu made: "<<i<<" iterations\n";
	cout<<"SuccessCounter: "<<successCtr<<endl;
	cout<<"enteringMCAnneal: "<<enteringMCAnneal<<endl;
	cout<<"Percent:"<<100.0*((double)successCtr/(double)(enteringMCAnneal+1.0))<<endl;
	cout<<"\nBest Energy: "<<bestFoldingArray.energy<<endl;
	cout<<"Number of fold steps until best Energy achived:"<<bestFoldingArray.stepNumber<<endl;
	cout<<"(best Energy conformation found)/(number Conformations passed:";
	cout<<(double)bestFoldingArray.stepNumber/(double)enteringMCAnneal<<endl;
#endif	
		
		
	return 1;
}

int foldingComplex::foldInBox()
{
	int pivot;
	int fold_type;
	
	//RMSD rmsd((residueArray *)this, sizeOfResidueArray);
	//PWDA pwda(sizeOfResidueArray);

#if CONFINED_FOLD	
	isOnConfinedFold = false;
#endif
	int i;
	for(i = 0; i < NUM_OF_PRE_ITERATIONS; i++)
	{
		
		pivot = RNG.generateNumberInRange(1, sizeOfResidueArray);
		
		fold_type = RNG.generateNumberInRange(0, 12);
	
		switch(fold_type)
		{
			case 0: if((pivot == 1) || (pivot == sizeOfResidueArray))
					if(tailRotateLeft(pivot) == 1)
						successCtr++;
					break;
			case 1: if((pivot == 1) || (pivot == sizeOfResidueArray))
					if(tailRotateRight(pivot)) //
						successCtr++;
					break;
			case 2: if((pivot == 1) || (pivot == sizeOfResidueArray))
					if(tailRotate180(pivot))//2
						successCtr++; 
					
					break;
			case 3: if((pivot > 1) && (pivot < sizeOfResidueArray))
					if(flipflopCorner(pivot))//OK
						successCtr++;
				 break; 
			case 4: if(fixedRotateLeft(pivot))//3 
					successCtr++;
					break;
			
			case 5: if(fixedRotateRight(pivot))//4 
					successCtr++;
					break;
			case 6: if(fixedRotate180(pivot))// 
					successCtr++;
					break;
			default:if((pivot > 1) && (pivot < sizeOfResidueArray))
					if(flipflopCorner(pivot))//OK
						successCtr++;
			
		}
		point pdxdy = getMin_dx_dy();
		//double rmsdAcc = 0;
		//double pwdaAcc = 0;
	
		//rmsdAcc = rmsd.compute(*this);
		//pwdaAcc = pwda.compute(this);
		//cout<<"In box: "<<", "<<rmsdAcc<<", "<<pwdaAcc<<endl;	
#if CONFINED_FOLD
		if( (pdxdy.x <= (added_confinedX ))&&
		    (pdxdy.y <= (added_confinedY ))  )
		{
			//printHPMatrix();
			//cout<<"Folded in box: "<<added_confinedX<<endl;
			break;
		}
#else
		if( (pdxdy.x < (sizeOfResidueArray/BOX_SIDE_DENOMINATOR ))&&
		    (pdxdy.y < (sizeOfResidueArray/BOX_SIDE_DENOMINATOR ))  )
		{
			//printHPMatrix();
			break;
		}	
#endif	
		    
		
		
	}
	//cout<<"Finished folding in the box\n";
#if CONFINED_FOLD	
	if(i == NUM_OF_PRE_ITERATIONS)
		cout<<"Could not fold in the box !!!\n";
#endif
	return 1;
}	

int foldingComplex::foldOnce()
{
	int pivot = RNG.generateNumberInRange(1, sizeOfResidueArray);
	int fold_type = RNG.generateNumberInRange(0, edgesProbability);
	
	switch(fold_type)
	{
		
		case 0: if((pivot == 1) || (pivot == sizeOfResidueArray))
				if(tailRotateLeft(pivot) == 1)
					successCtr++;
				break;

		case 1: if((pivot == 1) || (pivot == sizeOfResidueArray))
				if(tailRotateRight(pivot)) //
					successCtr++;
				break;
		case 2: if((pivot == 1) || (pivot == sizeOfResidueArray))
				if(tailRotate180(pivot))//2
					successCtr++; 
				
				break;		
		default: if(randLocalMod(pivot))
					successCtr++;
				break;
			
	}
	//cout<<"Folding Once"<<endl;
	//exit(0);
	return 1;
}
/*
int foldingComplex::foldOnceAndCheckRMSD()
{
	int pivot = RNG.generateNumberInRange(1, sizeOfResidueArray);
	int fold_type = RNG.generateNumberInRange(0, 16);
	
	switch(fold_type)
	{
		
		case 0: if((pivot == 1) || (pivot == sizeOfResidueArray))
				if(tailRotateLeft(pivot) == 1)
					successCtr++;
				break;

		case 1: if((pivot == 1) || (pivot == sizeOfResidueArray))
				if(tailRotateRight(pivot)) //
					successCtr++;
				break;
		case 2: if((pivot == 1) || (pivot == sizeOfResidueArray))
				if(tailRotate180(pivot))//2
					successCtr++; 
				
				break;		
		default: if(randLocalMod(pivot))
					successCtr++;
				break;
			
	}
	return 1;
}
*/
int foldingComplex::getStructFromDB(int idx)
{
	
	char name[200];// = "../evolution/DB/36-(6)-mer-struct-enum";
	
	sprintf(name, "../evolution/DB/%d-(%d)-mer-struct-enum-mod", 
			sizeOfResidueArray,
			sideStructDBsize);
	
	FILE* fp = fopen(name, "rb");
	
	if(!fp)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
	cout<<"\nopened file: "<<name<<" for DB\n";	
	fseek(fp, sizeof(int)+sizeof(double)+sizeof(int)*2*sizeOfResidueArray*(idx) ,SEEK_SET);
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		if( (fread(&(res[i].position.x), sizeof(int), 1, fp) != 1)||
			(fread(&(res[i].position.y), sizeof(int), 1, fp) != 1) )
			{
				cout<<"File Read Error - foldingComplex\n";
				fclose(fp);
				exit(1);
			}
	}
	
	for(int y = 0; y < top_y; y++)
		for(int x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
		occupyPosition(i);
	
	fclose(fp);
	//cout<<"\nRMSD reference residueArray: \n";
	//printHPMatrix();
	//cout<<"-----------------------------------------------------\n";
	return 1;
	
}
	
int foldingComplex::fold2RMSD(double times, int configfileIndex)
{
	double i;
	initFoldingComplex();
	
	/* GENERATING ARRAY IN THE BOX */
	structureDBIndex = CfileHdlr.getStructureDBIndex(sizeOfResidueArray, configfileIndex);
	cout<<"structureDBIndex: "<<structureDBIndex<<endl;
	if(structureDBIndex == -1)
		return 0;
	
	char *hp = CfileHdlr.getConfiguration(sizeOfResidueArray, configfileIndex);
	if(!hp)
	{
		cout<<"No more sequences in file: "<<CfileHdlr.fileName<<" .\n"<<"Max size:"<<configfileIndex<<endl;
		return 0;
	}

	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
	
	cout<<"before Getting structindex: "<<structureDBIndex<<endl;
	getStructFromDB(structureDBIndex);
	cout<<"Getting structindex: "<<structureDBIndex<<endl;
	//printBestEnergyArray();
	RMSD rmsd((residueArray *)this, sizeOfResidueArray);
	//PWDA pwda(sizeOfResidueArray);
	
	double rmsdAcc = 0;
	//double pwdaAcc = 0;
#if 1	
	rmsdAcc = rmsd.compute(*this);
	//pwdaAcc = pwda.compute(this);
	//cout<<rmsdAcc<<" "<<pwdaAcc<<endl;	
	//cout<<"Calling foldInBox() !!!\n";
	initFoldingComplex();
	foldInBox();
#endif
	 
	
	successCtr = 1;
	enteringMCAnneal = 1;
	
	
	cout<<"--------------RMSD--------------------\n";
	char tmpstr[120];
	
	sprintf(tmpstr, "%s-%d-%d-DB%d-%d.data", 
			outputDatafileName, 
			sizeOfResidueArray,
			configfileIndex,
			structureDBIndex,
			generalCounter);
	
	
	FILE* fp = fopen(tmpstr, "wb");
	
	if(!fp)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
	double itr = 0, alpha_itr = 0;
	for(i = 0; i < times; i++)
	{
		itr++;
		alpha_itr++;
		
		rmsdAcc += rmsd.compute(*this);
		//pwdaAcc = pwda.compute(this);
		//fprintf(fp, "%d %f\n", i, rmsdAcc);
		//cout<<i<<", "<<rmsdAcc<<", "<<pwdaAcc<<endl;
		foldOnce();
		
		
#if 1
		if(itr == WINDOW_SIZE_AVERAGE)
		{
			//cout<<i<<" "<<rmsdAcc/1000.0<<endl;	
			fprintf(fp, "%f %f\n", i, rmsdAcc/WINDOW_SIZE_AVERAGE);
			rmsdAcc = 0;
			itr = 0;
		}
#endif
				
		if(alpha_itr == ALPHA_ITR)
		{
			alpha_itr = 0;
			
			if(Ck < ALPHA_LOWER_BOND)
				Ck = ALPHA_LOWER_BOND;
			else
				Ck *= ALPHA;	
		}

		//cout<<i<<", "<<rmsdAcc<<endl;
		
	}
	fclose(fp);
#if 1
	cout<<"protSimu made: "<<i<<" iterations\n";
	cout<<"SuccessCounter: "<<successCtr<<endl;
	cout<<"enteringMCAnneal: "<<enteringMCAnneal<<endl;
	cout<<"Percent:"<<100.0*((double)successCtr/(double)(enteringMCAnneal+1.0))<<endl;
	cout<<"\nBest Energy: "<<bestFoldingArray.energy<<endl;
	cout<<"Number of fold steps until best Energy achived:"<<bestFoldingArray.stepNumber<<endl;
	cout<<"(best Energy conformation found)/(number Conformations passed:";
	cout<<(double)bestFoldingArray.stepNumber/(double)enteringMCAnneal<<endl;
#endif	
		
		
	return 1;
}

/*
The function fold2BestEngergyStruct:

1. RMSD from what found on DB by seqSeeker and best Energy structure.
2. Number of mcs for the best energy
3. write 3 files: 
   1. mcs best Energy, rmsd.
   2. best energy, rmsd.
   3. structure cordinates
   
   all files lines are parallel
   
*/
int foldingComplex::fold2BestEngergyStruct(double times, 
					int numOfSimulations, 
					int configfileIndex)
{
	initFoldingComplex();
	
	/* GET STRUCTURE RMSD REFERENCE STRUCT FROM DB */
	
	structureDBIndex = CfileHdlr.getStructureDBIndex(sizeOfResidueArray, configfileIndex);
	cout<<"structureDBIndex: "<<structureDBIndex<<endl;
	if(structureDBIndex == -1)
	{
		cout<<"No more sequences in file: "<<CfileHdlr.fileName<<" .\n"<<"Max size:"<<configfileIndex<<endl;
		return 0;
	}
	
	cout<<"Get config\n";
	char *hp = CfileHdlr.getConfiguration(sizeOfResidueArray, configfileIndex);
	if(!hp)
	{
		cout<<"No more sequences in file: "<<CfileHdlr.fileName<<" .\n"<<"Max size:"<<configfileIndex<<endl;
		return 0;
	}

	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
	
	cout<<"getStructFromDB\n";
	getStructFromDB(structureDBIndex);
	
	
	/* RMSD  CREATION */
	
	cout<<"rmsd\n";
	RMSD rmsd((residueArray *)this, sizeOfResidueArray);
	
	/* CREATING A FILE FOR DATA OUTPUT */
	
	char tmpstr[120];
	
	sprintf(tmpstr, "%s_rmsd_mcs-%d-%d-DB%d-%d.data", 
			outputDatafileName, 
			sizeOfResidueArray,
			configfileIndex,
			structureDBIndex,
			generalCounter);
	
	
	FILE* fp_rmsd_mcs = fopen(tmpstr, "wb");
	
	if(!fp_rmsd_mcs)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
	sprintf(tmpstr, "%s_rmsd_energy-%d-%d-DB%d-%d.data", 
			outputDatafileName, 
			sizeOfResidueArray,
			configfileIndex,
			structureDBIndex,
			generalCounter);
	
	cout<<"Open file\n";
	FILE* fp_rmsd_energy = fopen(tmpstr, "wb");
	
	if(!fp_rmsd_energy)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
	sprintf(tmpstr, "%s_structure-%d-%d-DB%d-%d.data", 
			outputDatafileName, 
			sizeOfResidueArray,
			configfileIndex,
			structureDBIndex,
			generalCounter);
	cout<<"res2file\n";
	residueArray residue2File(sizeOfResidueArray, tmpstr);
	
	
	/* MAIN LOOP */
	int tmpMaxRange = maxRangeOfLocalConf;
	
	cout<<"Run simu\n";
	for(int i = 0; i < numOfSimulations; i++)
	{
		maxRangeOfLocalConf = tmpMaxRange;
		initFoldingComplex();
		foldInBox();

		successCtr = 1;
		//enteringMCAnneal = 1;
	
		double alpha_itr = 0;//, localConf_itr = 0;
	
		/* SIMULATION LOOP */
		
		for(double m = enteringMCAnneal; m < times; m++)
		{
			alpha_itr++;
			foldOnce();
				
			if(alpha_itr == ALPHA_ITR)
			{
				alpha_itr = 0;
				//localConf_itr++;
				
				if(Ck < ALPHA_LOWER_BOND)
					Ck = ALPHA_LOWER_BOND;
				else
					Ck *= ALPHA;
				/*
				if( (maxRangeOfLocalConf > LOCAL_CONF_MIN_BOND)&&
					((localConf_itr*ALPHA_ITR)/times > LOCAL_CONF_ITR_FRACTION) )
				{
					localConf_itr = 0;
					maxRangeOfLocalConf--;
					cout<<"maxRangeOfLocalConf: "<<maxRangeOfLocalConf<<endl;
				}*/
					 
			}
		}
		

		double rmsdResult = rmsd.compute(bestFoldingArray);
		fprintf(fp_rmsd_mcs, "%d %f\n", bestFoldingArray.stepNumber, rmsdResult);
		fprintf(fp_rmsd_energy, "%f %f\n", bestFoldingArray.energy, rmsdResult);
		
		//residue2File = (residueArray)bestFoldingArray;
		for(int i = 1; i <= sizeOfResidueArray; i++)
		{
			residue2File.res[i].position.x = bestFoldingArray.res[i].position.x;
			residue2File.res[i].position.y = bestFoldingArray.res[i].position.y;
			residue2File.res[i].mode = bestFoldingArray.res[i].mode;
		}
		residue2File.write();
		
		
		if(i%20 == 0) 
		{
			cout<<"Done simulation number: "<<i<<endl;
#if 1
			cout<<"Percent:"<<100.0*((double)successCtr/(double)(enteringMCAnneal+1.0))<<endl;
#endif
			bestFoldingArray.print();
		}
	}//END OF OUTER LOOP
	
	fclose(fp_rmsd_mcs);
	fclose(fp_rmsd_energy);
		
	return 1;
}


int foldingComplex::foldAndPrintParamsEachNStep(double times, int configfileIndex, int NStep)
{
	double i;
	initFoldingComplex();
	
	/* GENERATING ARRAY IN THE BOX */
// 	structureDBIndex = CfileHdlr.getStructureDBIndex(sizeOfResidueArray, configfileIndex);
// 	cout<<"structureDBIndex ("<<configfileIndex<<"): "<<structureDBIndex<<endl;
// 	if(structureDBIndex == -1)
// 		return 0;
	point pstruct[120];
	char *hp = CfileHdlr.readTextStructure(sizeOfResidueArray, pstruct, configfileIndex);
// 	CfileHdlr.getConfiguration(sizeOfResidueArray, configfileIndex);
	if(!hp)
	{
		cout<<"No more sequences in file: "<<CfileHdlr.fileName<<" .\n"<<"Max size:"<<configfileIndex<<endl;
		return 0;
	}
	else {
// 		cout<<"seq: "<<hp<<endl;
	}

	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
	
// 	cout<<"before Getting structindex: "<<structureDBIndex<<endl;
// 	getStructFromDB(structureDBIndex);
// 	cout<<"Getting structindex: "<<structureDBIndex<<endl;
	//printBestEnergyArray();
	RMSD rmsd(pstruct, sizeOfResidueArray);
	rmsd.update(pstruct);
// 	PWD pwd(sizeOfResidueArray);
	
	double rmsdAcc = 0;
	double pwdAcc = 0;
#if 1	
	rmsdAcc = rmsd.compute(pstruct);
// 	pwdAcc = pwd.compute(pstruct);
	//cout<<rmsdAcc<<" "<<pwdaAcc<<endl;	
	//cout<<"Calling foldInBox() !!!\n";
	initFoldingComplex();
	foldInBox();
#endif
	 
	
	successCtr = 1;
	enteringMCAnneal = 1;
	
	
// 	cout<<"--------------RMSD--------------------\n";
	char tmpstr[120];
	
// 	sprintf(tmpstr, "%s-%d-%d-DB%d-%d.data", 
// 			outputDatafileName, 
// 			sizeOfResidueArray,
// 			configfileIndex,
// 			structureDBIndex,
// 			generalCounter);
// 	
	
// 	FILE* fp = fopen(tmpstr, "wb");
// 	
// 	if(!fp)
// 	{
// 		cout<<"ERROR - file opening\n";
// 		exit(0);
// 	}
	
	double itr = 0, alpha_itr = 0;
	for(i = 0; i < times; i++)
	{
		itr++;
		alpha_itr++;
		
		rmsdAcc = rmsd.compute(*this);
		pwdAcc = rmsd.computeNativePairDiff(*this);
// 		pwdAcc = pwd.compute(pstruct);
		//fprintf(fp, "%d %f\n", i, rmsdAcc);
		std::cout.precision(3);
// 		cout<<i<<"\t"<<rmsdAcc<<"\t"<<pwdAcc<<endl;
		cout<<rmsdAcc<<"\t"<<this->energy<<endl;
// 		cout<<i<<", "<<rmsdAcc<<endl;

		foldOnce();
		
		
#if 0
		if(itr == NStep)
		{
			cout<<i<<" "<<rmsdAcc/NStep<<endl;	
// 			fprintf(fp, "%f %f\n", i, rmsdAcc/WINDOW_SIZE_AVERAGE);
			rmsdAcc = 0;
			itr = 0;
		}

				
		if(alpha_itr == ALPHA_ITR)
		{
			alpha_itr = 0;
			
			if(Ck < ALPHA_LOWER_BOND)
				Ck = ALPHA_LOWER_BOND;
			else
				Ck *= ALPHA;	
		}
#endif
		//cout<<i<<", "<<rmsdAcc<<endl;
		
	}
// 	fclose(fp);
#if 0
	cout<<"protSimu made: "<<i<<" iterations\n";
	cout<<"SuccessCounter: "<<successCtr<<endl;
	cout<<"enteringMCAnneal: "<<enteringMCAnneal<<endl;
	cout<<"Percent:"<<100.0*((double)successCtr/(double)(enteringMCAnneal+1.0))<<endl;
	cout<<"\nBest Energy: "<<bestFoldingArray.energy<<endl;
	cout<<"Number of fold steps until best Energy achived:"<<bestFoldingArray.stepNumber<<endl;
	cout<<"(best Energy conformation found)/(number Conformations passed:";
	cout<<(double)bestFoldingArray.stepNumber/(double)enteringMCAnneal<<endl;
#endif	
		
		
	return 1;
}

int foldingComplex::foldAndAggregateParamsEachNStep(double times, int configfileIndex, int NStep)
{
	double i;
	int aggRMSD[10000] = { 0 }, aggEnergy[10000] = { 0 };
	initFoldingComplex();
	

	point pstruct[120];
	char *hp = CfileHdlr.readTextStructure(sizeOfResidueArray, pstruct, configfileIndex);
	if(!hp)
	{
		cout<<"No more sequences in file: "<<CfileHdlr.fileName<<" .\n"<<"Max size:"<<configfileIndex<<endl;
		return 0;
	}

	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
	
	RMSD rmsd(pstruct, sizeOfResidueArray);
	rmsd.update(pstruct);

	
	double rmsdAcc = 0;
	double pwdAcc = 0;
#if 1	
	rmsdAcc = rmsd.compute(pstruct);
	initFoldingComplex();
	foldInBox();
#endif
	 
	
	successCtr = 1;
	enteringMCAnneal = 1;
	
	char tmpstr[120];
	
	
	double itr = 0, alpha_itr = 0;
	for(i = 0; i < times; i++)
	{
		itr++;
		alpha_itr++;
		
		rmsdAcc = rmsd.compute(*this);
		pwdAcc = rmsd.computeNativePairDiff(*this);
		//std::cout.precision(5);
		aggRMSD[int(100*rmsdAcc)]++;
		aggEnergy[int(-100*this->energy)]++;
		//cout<<rmsdAcc<<"\t"<<this->energy<<endl;
		foldOnce();
	}	
	for(int k = 0; k < 10000; k++) {
		cout<<double(k)/100<<"\t"<<aggRMSD[k]<<"\t"<<-double(k)/100<<"\t"<<aggEnergy[k]<<endl;
	}
	return 1;
}

int foldingComplex::dwellTimeFold(double times, int configfileIndex, double rmsdDwell, int NStep)
{
	double i;
	initFoldingComplex();
	
	point pstruct[120];
	char *hp = CfileHdlr.readTextStructure(sizeOfResidueArray, pstruct, configfileIndex);
	if(!hp)
	{
		cout<<"No more sequences in file: "<<CfileHdlr.fileName<<" .\n"<<"Max size:"<<configfileIndex<<endl;
		return 0;
	}
	else {
// 		cout<<"seq: "<<hp<<endl;
	}

	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
	
	RMSD rmsd(pstruct, sizeOfResidueArray);
	rmsd.update(pstruct);

	
	double rmsdAcc = 0;
	double pwdAcc = 0;
	
	rmsdAcc = rmsd.compute(pstruct);
	initFoldingComplex();
	foldInBox();
	
	successCtr = 1;
	enteringMCAnneal = 1;
	
	char tmpstr[120];
		
	bool mySwitch = true;
	int switchCount = 0;
	double itr = 0, alpha_itr = 0;
	for(i = 0; i < times; i++)
	{
		itr++;
		alpha_itr++;
		
		rmsdAcc = rmsd.compute(*this);
		if(rmsdAcc > rmsdDwell) {
			if(mySwitch == true) {
				switchCount++;
			}
			else {
				cout<<mySwitch<<"\t"<<switchCount<<endl;
				mySwitch = true;
				switchCount = 1;
			}
		}
		else { 
			if(mySwitch == false) {
				switchCount++;
			}
			else {
				cout<<mySwitch<<"\t"<<switchCount<<endl;
				mySwitch = false;
				switchCount = 1;
			}
		}

// 		std::cout.precision(5);
// 		cout<<i<<"\t"<<rmsdAcc<<"\t"<<pwdAcc<<endl;
// 		cout<<rmsdAcc<<"\t";
// 		cout<<i<<", "<<rmsdAcc<<endl;

		foldOnce();
		if(alpha_itr == ALPHA_ITR)
		{
			alpha_itr = 0;
			
			if(Ck < ALPHA_LOWER_BOND)
				Ck = ALPHA_LOWER_BOND;
			else
				Ck *= ALPHA;	
		}
	}
	cout<<mySwitch<<"\t"<<switchCount<<endl;

#if 0
	cout<<"protSimu made: "<<i<<" iterations\n";
	cout<<"SuccessCounter: "<<successCtr<<endl;
	cout<<"enteringMCAnneal: "<<enteringMCAnneal<<endl;
	cout<<"Percent:"<<100.0*((double)successCtr/(double)(enteringMCAnneal+1.0))<<endl;
	cout<<"\nBest Energy: "<<bestFoldingArray.energy<<endl;
	cout<<"Number of fold steps until best Energy achived:"<<bestFoldingArray.stepNumber<<endl;
	cout<<"(best Energy conformation found)/(number Conformations passed:";
	cout<<(double)bestFoldingArray.stepNumber/(double)enteringMCAnneal<<endl;
#endif	
		
		
	return 1;
}

int foldingComplex::foldToMinimumEnergy(double times, 
					int numOfSimulations, 
					char *hp)
{
	initFoldingComplex();
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				(res)[i].mode = HYDROPHOBIC; break;
 			case 'P':
				(res)[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				(res)[i].mode = POSITIVE_CHARGE; break;
			case '-':
				(res)[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
		
	cout<<"Protchap.cpp: Begin folding:"<<endl;
	
	char fostr[1024];
	cout<<times<<", seq: "<<hp<<endl;
	sprintf(fostr, "%sfc-itr%d.data", outputDatafileName, (int)times);
	cout<<fostr<<endl;
	ofstream of(fostr); 
	of<<"#SEQ\t"<<hp<<endl<<"max mcs: "<<times<<", maxRangeOfLocalConf: "<<maxRangeOfLocalConf<<", edgesProbability: "<<edgesProbability<<", simulationFactor: "<<simulationFactor<<", Method: "<<VERSION<<" foldToMinimumEnergy"<<endl<<endl;
	for(int m = 0; m < numOfSimulations; m++)
	{
		initFoldingComplex();
		
		double itr = 0, alpha_itr = 0;
		
		for(int i = 0; i < times; i++)
		{

			itr++;
			alpha_itr++;
			
			foldOnce();
			if(alpha_itr == ALPHA_ITR)
			{
				alpha_itr = 0;
			
				if(Ck < ALPHA_LOWER_BOND)
					Ck = ALPHA_LOWER_BOND;
				else
					Ck *= ALPHA;	
			}		
		}
		
		for(int pp = 0; pp <= sizeOfResidueArray; pp++) 
			structure[pp] = bestFoldingArray.res[pp].position;
		CfileHdlr.writeStructure2file(sizeOfResidueArray, structure, hp, of);
		of<<"Struct Energy: "<<bestFoldingArray.energy<<", MCS: "<<bestFoldingArray.stepNumber<<endl;
		
	}
	
	of.close();
	delete []structure;
	cout<<"finish seq: "<<hp<<endl;
	return 1;
}

int foldingComplex::foldToMinimumEnergy(double times, 
					int numOfSimulations, 
					int configfileIndex)
{
	initFoldingComplex();
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	char *hp;
	if( (hp = CfileHdlr.getConfiguration(sizeOfResidueArray, configfileIndex)) == 0)
	{
		cout<<"could not Get index: "<<configfileIndex<<endl;
		delete []structure;
		return 0;//exit(0);
	}
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				(res)[i].mode = HYDROPHOBIC; break;
 			case 'P':
				(res)[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				(res)[i].mode = POSITIVE_CHARGE; break;
			case '-':
				(res)[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
		
	cout<<"protchap.cpp: Begin folding:"<<endl;
	
	char fostr[1024];
	cout<<times<<" "<<configfileIndex<<endl;
	sprintf(fostr, "%sfc-itr%d-%d.data", outputDatafileName, (int)times, configfileIndex);
	cout<<fostr<<endl;
	ofstream of(fostr); 
	of<<"#IDX\t"<<configfileIndex<<endl<<"max mcs: "<<times<<", maxRangeOfLocalConf: "<<maxRangeOfLocalConf<<", edgesProbability: "<<edgesProbability<<", simulationFactor: "<<simulationFactor<<endl<<endl;
	for(int m = 0; m < numOfSimulations; m++)
	{
		initFoldingComplex();
		
		double itr = 0, alpha_itr = 0;
		
		for(int i = 0; i < times; i++)
		{

			itr++;
			alpha_itr++;
			
			foldOnce();
			if(alpha_itr == ALPHA_ITR)
			{
				alpha_itr = 0;
			
				if(Ck < ALPHA_LOWER_BOND)
					Ck = ALPHA_LOWER_BOND;
				else
					Ck *= ALPHA;	
			}		
		}
		
		for(int pp = 0; pp <= sizeOfResidueArray; pp++) 
			structure[pp] = bestFoldingArray.res[pp].position;
		CfileHdlr.writeStructure2file(sizeOfResidueArray, structure, hp, of);
		of<<"Struct Energy: "<<bestFoldingArray.energy<<", MCS: "<<bestFoldingArray.stepNumber<<endl;
		
	}
	
	of.close();
	delete []structure;
	cout<<"finish configfileIndex: "<<configfileIndex<<endl;
	return 1;
}

int foldingComplex::fold2BestEngergyStructWithPairwiseRMSD(double times, 
										   				   int numOfSimulations, 
										   				   int configfileIndex)
{
	initFoldingComplex();
	
	/* GET STRUCTURE RMSD REFERENCE STRUCT FROM DB */
	
	structureDBIndex = CfileHdlr.getStructureDBIndex(sizeOfResidueArray, configfileIndex);
	cout<<"structureDBIndex: "<<structureDBIndex<<endl;
	if(structureDBIndex == -1)
	{
		cout<<"No more sequences in file: "<<CfileHdlr.fileName<<" .\n"<<"Max size:"<<configfileIndex<<endl;
		return 0;
	}
	
	cout<<"Get config\n";
	char *hp = CfileHdlr.getConfiguration(sizeOfResidueArray, configfileIndex);
	if(!hp)
	{
		cout<<"No more sequences in file: "<<CfileHdlr.fileName<<" .\n"<<"Max size:"<<configfileIndex<<endl;
		return 0;
	}

	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
	
	cout<<"getStructFromDB\n";
	getStructFromDB(structureDBIndex);
	
	
	/* RMSD  CREATION */
	
	cout<<"rmsd\n";
	RMSD rmsd((residueArray *)this, sizeOfResidueArray, numOfSimulations);

	double *results = new double[numOfSimulations];
	double *energies = new double[numOfSimulations];
	double *pairdiffs = new double[numOfSimulations];
	int *stepnumbers = new int[numOfSimulations];
	if( (!results)||(!stepnumbers)||(!energies)||(!pairdiffs) )
	{
		cout<<"ERROR - mem alloc results array\n";
		exit(1);
	}
	
	/* CREATING A FILE FOR DATA OUTPUT */
	
	char tmpstr[120];
	
///////////////////////////////////////////////////////////////////////////	
	sprintf(tmpstr, "%s_rmsd_mcs-%d-%d-DB%d-%d.data", 
			outputDatafileName, 
			sizeOfResidueArray,
			configfileIndex,
			structureDBIndex,
			generalCounter);
	
	
	FILE* fp_rmsd_mcs = fopen(tmpstr, "wb");
	
	if(!fp_rmsd_mcs)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
///////////////////////////////////////////////////////////////////////////	
	sprintf(tmpstr, "%s_rmsd_energy-%d-%d-DB%d-%d.data", 
			outputDatafileName, 
			sizeOfResidueArray,
			configfileIndex,
			structureDBIndex,
			generalCounter);
	
	cout<<"Open file\n";
	FILE* fp_rmsd_energy = fopen(tmpstr, "wb");
	
	if(!fp_rmsd_energy)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}

///////////////////////////////////////////////////////////////////////////		
	sprintf(tmpstr, "%s_mcs_pairdiff-%d-%d-DB%d-%d.data", 
			outputDatafileName, 
			sizeOfResidueArray,
			configfileIndex,
			structureDBIndex,
			generalCounter);
	
	cout<<"Open file\n";
	FILE* fp_rmsd_pairdiff = fopen(tmpstr, "wb");
	
	if(!fp_rmsd_pairdiff)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}

///////////////////////////////////////////////////////////////////////////
	sprintf(tmpstr, "%s_structure-%d-%d-DB%d-%d.data", 
			outputDatafileName, 
			sizeOfResidueArray,
			configfileIndex,
			structureDBIndex,
			generalCounter);
	//cout<<"res2file\n";
	
	residueArray residue2File(sizeOfResidueArray, tmpstr);
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				residue2File.res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				residue2File.res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				residue2File.res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				residue2File.res[i].mode = NEGATIVE_CHARGE; break;
		}		
	}

///////////////////////////////////////////////////////////////////////////	
	
#if WIDE_MEASURE	
		long winSize = ((long)times)/WIDE_MCS_WINDOW_SIZE;
		int **wideStatistic = new int*[winSize];
		if(!wideStatistic)
		{
			cout<<"ERROR mem alloc wideStatistic\n";
			exit(1);
		}

		for(int w = 0; w < winSize; w++)
		{
			wideStatistic[w] = new int[sizeOfResidueArray+1];
			if(!wideStatistic[w])
			{
				cout<<"ERROR mem alloc wideStatistic\n";
				exit(1);
			}
			
			for(int ss = 0; ss <= sizeOfResidueArray; ss++)
				wideStatistic[w][ss] = 0;
		}
#endif
		
	/* MAIN LOOP */
	int tmpMaxRange = maxRangeOfLocalConf;
	
	//cout<<"Run simu\n";
	for(int i = 0; i < numOfSimulations; i++)
	{
		maxRangeOfLocalConf = tmpMaxRange;
		initFoldingComplex();
		
		double m;
#if USE_PRE_FOLD
		foldInBox();
#endif
		
#if CONFINED_FOLD
		
#if USE_PRE_FOLD
		isOnConfinedFold = true;
		m = enteringMCAnneal;
		point pdxdy = getMin_dx_dy();
		
		if( (pdxdy.x > (added_confinedX ))||
	    	(pdxdy.y > (added_confinedY ))  )
		{
			m = times;
			bestFoldingArray.stepNumber = times;
			cout<<"Could not fold at initiation\n";
		}
		
#else
		isOnConfinedFold = false;
#endif
		
		
#else
		m = enteringMCAnneal;
#endif

#if !USE_PRE_FOLD
		m = 0;
		
#endif
		successCtr = 1;
		//enteringMCAnneal = 1;
	
		double alpha_itr = 0;//, localConf_itr = 0;
	
		/* SIMULATION LOOP */
#if WIDE_MEASURE		
		long long wideMcs = 0, mcsmaxWide = 0;
		point xytmp;
		int maxWide;
		for(int w = 0; w < winSize; w++)
			for(int ss = 0; ss <= sizeOfResidueArray; ss++)
				wideStatistic[w][ss] = 0;	
		int wideStatIdx = 0;
		///////////////////////////////////////////////////////////////////////////		
		sprintf(tmpstr, "%s_mcs_wide_%d-%d-%d-DB%d-%d.data", 
			outputDatafileName, 
			i,
			sizeOfResidueArray,
			configfileIndex,
			structureDBIndex,
			generalCounter);
	
		cout<<"Open file\n";
		FILE* fp_mcs_wide = fopen(tmpstr, "wb");
	
		if(!fp_mcs_wide)
		{
			cout<<"ERROR - file opening\n";
			exit(0);
		}
		
		///////////////////////////////////////////////////////////////////////////		
		sprintf(tmpstr, "%s_wide_cnt_%d-%d-%d-DB%d-%d.data", 
			outputDatafileName, 
			i,
			sizeOfResidueArray,
			configfileIndex,
			structureDBIndex,
			generalCounter);
	
		cout<<"Open file\n";
		FILE* fp_wide_cnt = fopen(tmpstr, "wb");
	
		if(!fp_wide_cnt)
		{
			cout<<"ERROR - file opening\n";
			exit(0);
		}

		maxWide = 0;
		
		int currentWide = 0;		
#endif	

		for(; m < times; m++)
		{
			alpha_itr++;
			foldOnce();
#if WIDE_MEASURE			
			xytmp = getMin_dx_dy();

			if(xytmp.x > xytmp.y)
				currentWide = xytmp.x;
			else
				currentWide = xytmp.y;	
/*			
			if( (xytmp.x + xytmp.y) >= (xymaxWide.x + xymaxWide.y) )
			{
				xymaxWide = xytmp;
				mcsmaxWide = m;
			}
*/
			if( currentWide >= maxWide )
			{
				maxWide = currentWide;
				mcsmaxWide = m;
			}
						
/*			
			if(wideMcs%1000 == 0)
			{
				fprintf(fp_mcs_wide, "%d %d\n", mcsmaxWide, xymaxWide.x + xymaxWide.y);		
				xymaxWide.x = xymaxWide.y = 0;
			}
*/
			wideStatistic[wideStatIdx][currentWide]++;
			if((wideMcs + 1)%WIDE_MCS_WINDOW_SIZE == 0)
			{
				fprintf(fp_mcs_wide, "%d %d\n", mcsmaxWide, maxWide);		
				maxWide = 0;
				wideStatIdx++;
			}
		
			wideMcs++;
#endif						
			if(alpha_itr == ALPHA_ITR)
			{
				alpha_itr = 0;
				//localConf_itr++;
				
				if(Ck < ALPHA_LOWER_BOND)
					Ck = ALPHA_LOWER_BOND;
				else
					Ck *= ALPHA;
					 
			}
		}
#if WIDE_MEASURE
		int *tmpWideStat = new int[sizeOfResidueArray+1];
		if(!tmpWideStat)
		{
			cout<<"Error mem alloc tmpWideStat\n";
			exit(1);
		}
#if 1		
		for(int ss = 0; ss <= sizeOfResidueArray; ss++)
			tmpWideStat[ss] = 0;	
		for(int w = 0; 
				(w*WIDE_MCS_WINDOW_SIZE < bestFoldingArray.stepNumber + WIDE_MCS_WINDOW_SIZE) &&
				(w < winSize);
				w++)
			for(int ss = 1; ss < sizeOfResidueArray; ss++)
				tmpWideStat[ss] += wideStatistic[w][ss];									
						
		
		for(int ss = 1; ss < sizeOfResidueArray; ss++)
			fprintf(fp_wide_cnt, "%d %d\n", ss, tmpWideStat[ss]);
#else		
		for(int w = 0; 
				(w*WIDE_MCS_WINDOW_SIZE < bestFoldingArray.stepNumber + WIDE_MCS_WINDOW_SIZE) &&
				(w < winSize);
				w++)
			for(int ss = 1; ss < sizeOfResidueArray; ss++)
				fprintf(fp_wide_cnt, "%d %d\n", 
						w + ss*(WIDE_MCS_WINDOW_SIZE/sizeOfResidueArray - 1), 
						wideStatistic[w][ss]);	
#endif							
		fclose(fp_wide_cnt);		
		fclose(fp_mcs_wide);

#endif
		//double rmsdResult = rmsd.compute(bestFoldingArray);
		stepnumbers[i] = bestFoldingArray.stepNumber;
		energies[i] = bestFoldingArray.energy;

		
		//residue2File = (residueArray)bestFoldingArray;
		for(int j = 1; j <= sizeOfResidueArray; j++)
		{
			rmsd.structures[i][j].x = residue2File.res[j].position.x = bestFoldingArray.res[j].position.x;
			rmsd.structures[i][j].y = residue2File.res[j].position.y = bestFoldingArray.res[j].position.y;
			residue2File.res[j].mode = bestFoldingArray.res[j].mode;
			
		}
		//if(i%10 == 0)
			/*CfileHdlr.*/writeStructure2output(sizeOfResidueArray, rmsd.structures[i], hp); 
		residue2File.write();
		
		
		if(i%10 == 0) 
		{
			cout<<"\nDone simulation number: "<<i<<endl;
#if 1
			cout<<"Percent:"<<100.0*((double)successCtr/(double)(enteringMCAnneal+1.0))<<endl;
#endif
//			bestFoldingArray.print();
		}
	}//END OF OUTER LOOP
	
	rmsd.pairwiseCompute(numOfSimulations, results, pairdiffs);
	for(int i = 0; i < numOfSimulations; i++)
	{
		fprintf(fp_rmsd_mcs, "%d %f\n", stepnumbers[i], results[i]);
		fprintf(fp_rmsd_energy, "%f %f\n", energies[i], results[i]);		
		fprintf(fp_rmsd_pairdiff, "%d %f\n", stepnumbers[i], pairdiffs[i]);

				
	}

	fclose(fp_rmsd_mcs);
	fclose(fp_rmsd_energy);
	fclose(fp_rmsd_pairdiff);


	delete []stepnumbers;
	delete []energies;
	delete []results;
	delete []pairdiffs;

#if WIDE_MEASURE
	for(int w = 0; w < winSize; w++)
		delete []wideStatistic[w];
		
	delete []wideStatistic;
#endif
	return 1;
}


/*
For each structure of nameOfStructFile run numOfSimulations simulations on fixed sequence configfileIndex
*/
int foldingComplex::foldOverStructures(double times, 
									   int numOfSimulations,
									   int configfileIndex, 
									   char* nameOfStructFile)
{
	cout<<"Structure source file name: "<<nameOfStructFile<<endl;
	initFoldingComplex();
	
	/* GET STRUCTURE RMSD REFERENCE STRUCT FROM STRUCTUREN FILE */
	
	residueArray residue2File(nameOfStructFile);
	int structureDBIndex = 0;
	
	char *hp = CfileHdlr.getConfiguration(sizeOfResidueArray, configfileIndex);
	if(!hp)
	{
		cout<<"No more sequences in file: "<<CfileHdlr.fileName<<" .\n"<<"Max size:"<<configfileIndex<<endl;
		return 0;
	}

	cout<<endl;
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
			res[i].mode = HYDROPHOBIC; cout<<'H'; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; cout<<'P'; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; cout<<'+'; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; cout<<'-'; break;
		}		
	}
	cout<<endl;
	
	while(residue2File.read())
	{
		/* RMSD  CREATION */
		residue2File.print();
		RMSD rmsd(&residue2File, residue2File.sizeOfResidueArray);
	
		/* CREATING A FILE FOR DATA OUTPUT */
	
		char tmpstr[120];
	
		sprintf(tmpstr, "%s_rmsd_mcs-%d-SS%d.data", 
				outputDatafileName, 
				sizeOfResidueArray,
				structureDBIndex);
	
	
		FILE* fp_rmsd_mcs = fopen(tmpstr, "wb");
	
		if(!fp_rmsd_mcs)
		{
			cout<<"ERROR - file opening\n";
			exit(0);
		}
	
		sprintf(tmpstr, "%s_rmsd_energy-%d-SS%d.data", 
				outputDatafileName, 
				sizeOfResidueArray,
				structureDBIndex);
	
	
		FILE* fp_rmsd_energy = fopen(tmpstr, "wb");
	
		if(!fp_rmsd_energy)
		{
			cout<<"ERROR - file opening\n";
			exit(0);
		}
	
		/* MAIN LOOP */
	
		for(int i = 0; i < numOfSimulations; i++)
		{
	
			initFoldingComplex();
			foldInBox();

			successCtr = 1;
			enteringMCAnneal = 1;
	
			double alpha_itr = 0;
	
			/* SIMULATION LOOP */
		
			for(double m = 0; m < times; m++)
			{
				alpha_itr++;
				foldOnce();
				
				if(alpha_itr == ALPHA_ITR)
				{
					alpha_itr = 0;
			
					if(Ck < ALPHA_LOWER_BOND)
						Ck = ALPHA_LOWER_BOND;
					else
						Ck *= ALPHA;	
				}
			}
		
			double rmsdResult = rmsd.compute(bestFoldingArray);
			fprintf(fp_rmsd_mcs, "%d %f\n", bestFoldingArray.stepNumber, rmsdResult);
			fprintf(fp_rmsd_energy, "%f %f\n", bestFoldingArray.energy, rmsdResult);
		
			cout<<"Done simulation number: "<<i<<endl;
		}//END OF OUTER LOOP
	
		fclose(fp_rmsd_mcs);
		fclose(fp_rmsd_energy);

		structureDBIndex++;
	}	
	return 1;
}


void foldingComplex::printBestEnergyArray()
{
	int** matrix = new int*[top_y];
	if(!matrix)
	{
		cout<<"Error = mem alloc foldingComplex\n";
		exit(1);
	}
	for(int i = 0; i < top_y; i++)
		if(!(matrix[i] = new int[right_x]) )
		{
			cout<<"Error = mem alloc foldingComplex\n";
			exit(1);
		}
		
			
		
	
	int i, y, x;
	cout<<"The best energy conformation:\n";
	cout<<"Energy:"<<bestFoldingArray.energy<<endl;
	cout<<"Number of first time to appear:"<<bestFoldingArray.stepNumber<<endl;
	for(y = 0; y < top_y; y++)
		for(x = 0; x < right_x; x++)
			matrix[y][x] = 0;
			
	for(i = 1; i <= sizeOfResidueArray; i++)
		matrix[bestFoldingArray.res[i].position.y][bestFoldingArray.res[i].position.x] = i;
		
	for(y = top_y - 1; y >= 0; y--)
	{
		for(x = 0; x < right_x; x++)
		{
			if(!matrix[y][x])
				cout<<"   ";
			else
			{
				char sgn;
				switch(bestFoldingArray.res[matrix[y][x]].mode)
				{
					case HYDROPHOBIC:
						sgn = 'H'; break;
 					case POLAR_NEUTRAL:
						sgn = 'P'; break;
 					case POSITIVE_CHARGE:
						sgn = '+'; break;	
					case NEGATIVE_CHARGE:
						sgn = '-'; break;
				}
				
				if(matrix[y][x] > 9)
					cout<<sgn<<matrix[y][x];
				else 
					cout<<sgn<<matrix[y][x]<<" ";
			}
		}
		cout<<endl;
	}

	for(int i = 0; i < top_y; i++)
		delete []matrix[i];
	delete []matrix;
}


void foldingComplex::printBoolMatrix()
{
	for(int y = top_y - 1; y >= 0; y--)
	{
		for(int x = 0; x < right_x; x++)
			if(!boolMatrix[y][x])
				cout<<"  ";
			else if(boolMatrix[y][x] > 9)
				cout<<boolMatrix[y][x];
			else 
				cout<<" "<<boolMatrix[y][x];
		cout<<endl;
	}
}

void foldingComplex::printHPMatrix()
{
	for(int y = top_y - 1; y >= 0; y--)
	{
		for(int x = 0; x < right_x; x++)
			if(!boolMatrix[y][x])
				cout<<" ";
			else 
			{
				switch(res[boolMatrix[y][x]].mode)
				{
					case HYDROPHOBIC:
						cout<<"H"; break;
 					case POLAR_NEUTRAL:
						cout<<"P"; break;
 					case POSITIVE_CHARGE:
						cout<<"+"; break;	
					case NEGATIVE_CHARGE:
						cout<<"-"; break;
				}
			}
		cout<<endl;
	}
	cout<<"\nEnergy Level:"<<energy<<endl;
	cout<<"H: Hydrophobic, P: Neutral Polar\n+: Polar charged(+), -: Polar charged(-)\n";
}

double foldingComplex::getEnergyValue(int x, int y, int i)
{  
	if( (boolMatrix[y][x] > 0)&&
	    ( ((boolMatrix[y][x] - i) > 2)||
	      ((boolMatrix[y][x] - i) < -2) ) )
		return energyMatrix[res[boolMatrix[y][x]].mode][res[i].mode] + alphaE;

	return 0.0;
}

double foldingComplex::calculateEnergy()
{
	double energy = 0;

	int i;
	
	
	for(i = 1; i <= sizeOfResidueArray; i++)
	{	
			int x = res[i].position.x;
			int y = res[i].position.y;

			if(y < top_y - 1)
				energy += getEnergyValue(x, y+1, i);
			if(y > buttom_y)
				energy += getEnergyValue(x, y-1, i);
			if(x < right_x -1)
				energy += getEnergyValue(x+1, y, i);
			if(x > left_x)
				energy += getEnergyValue(x-1, y, i);
		
	}//end for loop
		
	//Energy will always be double than should be	
	return (energy/2);
}

double foldingComplex::calculateEnergy(int pivot)
{
	double energy = 0;

	int i;
	
	
	for(i = 1; i <= pivot; i++)
	{
			int x = res[i].position.x;
			int y = res[i].position.y;

			if(y < top_y - 1)
				energy += getEnergyValue(x, y+1, i);
			if(y > buttom_y)
				energy += getEnergyValue(x, y-1, i);
			if(x < right_x -1)
				energy += getEnergyValue(x+1, y, i);
			if(x > left_x)
				energy += getEnergyValue(x-1, y, i);
			
	}//end for loop
	for(i = pivot + 1; i <= sizeOfResidueArray; i++)
	{
			
			int x = tmpArr[i].x;
			int y = tmpArr[i].y;
			
			if(y < top_y - 1)
				energy += getEnergyValue(x, y+1, i);
			if(y > buttom_y)
				energy += getEnergyValue(x, y-1, i);
			if(x < right_x -1)
				energy += getEnergyValue(x+1, y, i);
			if(x > left_x)
				energy += getEnergyValue(x-1, y, i);
			
		
	}//end for loop
	/*
	if(int(energy)%2 != 0)
			{
				printBoolMatrix();
				printHPMatrix();
				cout<<"Exit Error!!!\n";
				exit(0);
			}	
	*/
	//Energy will always be double than should be	
	return (energy/2);
}

double foldingComplex::calculateEnergy(int pivot, int range)
{
	double energy = 0;

	int i;
	
	
	for(i = 1; i <= pivot; i++)
	{
			
			int x = res[i].position.x;
			int y = res[i].position.y;

			if(y < top_y - 1)
				energy += getEnergyValue(x, y+1, i);
			if(y > buttom_y)
				energy += getEnergyValue(x, y-1, i);
			if(x < right_x -1)
				energy += getEnergyValue(x+1, y, i);
			if(x > left_x)
				energy += getEnergyValue(x-1, y, i);
			
				
	}//end for loop
	
	for(i = pivot + 1; i < range + pivot; i++)
	{
			
			int x = tmpArr[i].x;
			int y = tmpArr[i].y;
			
			if(y < top_y - 1)
				energy += getEnergyValue(x, y+1, i);
			if(y > buttom_y)
				energy += getEnergyValue(x, y-1, i);
			if(x < right_x -1)
				energy += getEnergyValue(x+1, y, i);
			if(x > left_x)
				energy += getEnergyValue(x-1, y, i);
			
	}//end for loop
	
	for(; i <= sizeOfResidueArray; i++)
	{
			
			int x = res[i].position.x;
			int y = res[i].position.y;

			if(y < top_y - 1)
				energy += getEnergyValue(x, y+1, i);
			if(y > buttom_y)
				energy += getEnergyValue(x, y-1, i);
			if(x < right_x -1)
				energy += getEnergyValue(x+1, y, i);
			if(x > left_x)
				energy += getEnergyValue(x-1, y, i);
			
				
	}//end for loop
	
	//Energy will always be double than should be	
	return (energy/2);
}


void foldingComplex::DEBUG_lostRes()
{

	int* lostRes = new int[sizeOfResidueArray + 1];
	for(int i = 0; i < sizeOfResidueArray + 1; i++)
		lostRes[i] = 0;

	for(int y = 0; y < top_y; y++)
		for(int x = 0; x < right_x; x++)
			if(boolMatrix[y][x])
				lostRes[boolMatrix[y][x]] = 1;
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
		if(!lostRes[i])
		{
			cout<<"\n-----------------ERROR-----lost res---------\n";
			printBoolMatrix();
			cout<<"\n-----------------ERROR-----lost res---------\n";
			cout<<"lc.pivotPoint: "<<lc.pivotPoint.x<<", "<<lc.pivotPoint.y<<endl;
			int a;
			cin>>a;
			exit(0);
		}
		
	delete []lostRes;

}
void foldingComplex::DEBUG_outOfLimitRes()
{
	for(int j = 1; j < sizeOfResidueArray; j+=2)
	{
		int dx = res[j].position.x - res[j+1].position.x;
		int dy = res[j].position.y - res[j+1].position.y;

		if( (abs(dx) + abs(dy)) > 1 /*((abs(dx) > 1)||(abs(dy) > 1))*/ )
		{
			cout<<"\n-----------------ERROR-----out of limit res---------\n";
			printBoolMatrix();
			cout<<"\n-----------------ERROR-----out of limit res---------\n";
			cout<<"lc.pivotPoint: "<<lc.pivotPoint.x<<", "<<lc.pivotPoint.y<<endl;
			int a;
			cin>>a;
			exit(0);
		}
	}

}
		

