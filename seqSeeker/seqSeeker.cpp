
//seqSeeker.cpp

#include "seqSeeker.h"
#include "../simulator/protchap.h"
#include "../simulator/utilities.h"
#include "../simulator/configFileHandler.h"
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

//V21
#if 1
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
								/*	       H	     P	       +      - */	
double energyMatrix[4][4] =	
							/* H */ {{ -1.0 ,  0.0    ,  0.0 ,  0.0  },
 							/* P */  {  0.0  , -0.75   ,  -0.25 ,-0.25  },
							/* + */  {  0.0  , -0.25  ,  +1.0 , -1.25  },
							/* - */  {  0.0  , -0.25  ,  -1.25 , +1.0  } };
					
#endif

//V20
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
								/*	      H	     P	       +      - */	
double energyMatrix[4][4] =	/* H */ {{ -0.75 ,  0.0    ,  0.0 ,  0.0  },
 							/* P */  {  0.0  , -0.625  ,  -0.25 ,-0.25  },
							/* + */  {  0.0  , -0.25  ,  +1.0 , -1.0  },
							/* - */  {  0.0  , -0.25  ,  -1.0 , +1.0  } };
					
#endif

//V19
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
								/*	      H	     P	       +      - */	
double energyMatrix[4][4] =	/* H */ {{ -1.0 ,  0.0    ,  0.0 ,  0.0  },
 							/* P */  {  0.0  , -0.75   ,  -0.25 ,-0.25  },
							/* + */  {  0.0  , -0.25  ,  +1.0 , -1.0  },
							/* - */  {  0.0  , -0.25  ,  -1.0 , +1.0  } };
					
#endif

//V18
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
								/*	      H	     P	       +      - */	
double energyMatrix[4][4] =	/* H */ {{ -0.75 ,  0.0    ,  0.0 ,  0.0  },
 							/* P */  {  0.0  , -0.5   ,  -0.25 ,-0.25  },
							/* + */  {  0.0  , -0.25  ,  +1.0 , -1.0  },
							/* - */  {  0.0  , -0.25  ,  -1.0 , +1.0  } };
					
#endif

//V17
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.8     ,  0.0    ,  +0.0625 ,  +0.0625  },
 							 /* P */  {  0.0     , -0.7   ,  -0.375 , -0.375  },
							 /* + */  {  +0.0625  , -0.375  ,  +0.8 , -1.125  },
							 /* - */  {  +0.0625  , -0.375  ,  -1.125 , +0.8  } };
					
#endif
//V16
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.8     ,  0.0    ,  +0.0625 ,  +0.0625  },
 							 /* P */  {  0.0     , -0.7   ,  -0.375 , -0.375  },
							 /* + */  {  +0.0625  , -0.375  ,  +1.0 , -1.125  },
							 /* - */  {  +0.0625  , -0.375  ,  -1.125 , +1.0  } };
					
#endif
//V15
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.0625 ,  +0.0625  },
 							 /* P */  {  0.0     , -0.7   ,  -0.375 , -0.375  },
							 /* + */  {  +0.0625  , -0.375  ,  +1.0 , -1.125  },
							 /* - */  {  +0.0625  , -0.375  ,  -1.125 , +1.0  } };
					
#endif
//V14
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.625     ,  0.0    ,  +0.0625 ,  +0.0625  },
 							 /* P */  {  0.0     , -0.5   ,  -0.375 , -0.375  },
							 /* + */  {  +0.0625  , -0.375  ,  +1.0 , -1.125  },
							 /* - */  {  +0.0625  , -0.375  ,  -1.125 , +1.0  } };
					
#endif
//V13
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.5     ,  0.0    ,  +0.0625 ,  +0.0625  },
 							 /* P */  {  0.0     , -0.4   ,  -0.375 , -0.375  },
							 /* + */  {  +0.0625  , -0.375  ,  +1.0 , -1.125  },
							 /* - */  {  +0.0625  , -0.375  ,  -1.125 , +1.0  } };
					
#endif

//V12
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.0625 ,  +0.0625  },
 							 /* P */  {  0.0     , -0.75   ,  -0.375 , -0.375  },
							 /* + */  {  +0.0625  , -0.375  ,  +1.0 , -1.125  },
							 /* - */  {  +0.0625  , -0.375  ,  -1.125 , +1.0  } };
					
#endif
//V11
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.0625 ,  +0.0625  },
 							 /* P */  {  0.0     , -0.625   ,  -0.375 , -0.375  },
							 /* + */  {  +0.0625  , -0.375  ,  +1.0 , -1.125  },
							 /* - */  {  +0.0625  , -0.375  ,  -1.125 , +1.0  } };
					
#endif

//V10
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.0625 ,  +0.0625  },
 							 /* P */  {  0.0     , -0.625   ,  -0.25 , -0.25  },
							 /* + */  {  +0.0625  , -0.25  ,  +1.0 , -1.125  },
							 /* - */  {  +0.0625  , -0.25  ,  -1.125 , +1.0  } };
					
#endif

//V9
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.125 ,  +0.125  },
 							 /* P */  {  0.0     , -0.625   ,  -0.25 , -0.25  },
							 /* + */  {  +0.125  , -0.25  ,  +1.0 , -1.125  },
							 /* - */  {  +0.125  , -0.25  ,  -1.125 , +1.0  } };
					
#endif

//V8
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.125 ,  +0.125  },
 							 /* P */  {  0.0     , -0.625   ,  -0.125 , -0.125  },
							 /* + */  {  +0.125  , -0.125  ,  +1.0 , -1.0  },
							 /* - */  {  +0.125  , -0.125  ,  -1.0 , +1.0  } };
					
#endif

//V7
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.125 ,  +0.125  },
 							 /* P */  {  0.0     , -0.5   ,  -0.125 , -0.125  },
							 /* + */  {  +0.125  , -0.125  ,  +1.0 , -1.0  },
							 /* - */  {  +0.125  , -0.125  ,  -1.0 , +1.0  } };
					
#endif

//V6
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -1.0     ,  0.0    ,  +0.125 ,  +0.125  },
 							 /* P */  {  0.0     , -0.75   ,  -0.125 , -0.125  },
							 /* + */  {  +0.125  , -0.125  ,  +1.0 , -1.0  },
							 /* - */  {  +0.125  , -0.125  ,  -1.0 , +1.0  } };
					
#endif
//V5
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -0.75     ,  0.0    ,  +0.25 ,  +0.25  },
 							 /* P */  {  0.0     , -0.5   ,  -0.125 , -0.0625  },
							 /* + */  {  +0.25  , -0.125  ,  +1.0 , -1.25  },
							 /* - */  {  +0.25  , -0.0625  ,  -1.25 , +1.0  } };
					
#endif
//V4
#if 0
												  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
										/*	H	       P	      +	        - */	
double energyMatrix[4][4] =	  /* H */ {{ -1.0     ,  0.0    ,  +0.125 ,  +0.125  },
 							 /* P */  {  0.0     , -0.5   ,  -0.125 , -0.125  },
							 /* + */  {  +0.125  , -0.125  ,  +1.0 , -1.0  },
							 /* - */  {  +0.125  , -0.125  ,  -1.0 , +1.0  } };
					
#endif
//V3
#if 0
							  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
							  /*	 	    H	       P	     +	        -     */	
double energyMatrix[4][4] =	  /* H */ {{  -0.3     ,  0.0   ,  +0.3    ,  +0.3  },
 							  /* P */  {   0.0     ,  0.0   ,  -0.25   ,  -0.1  },
							  /* + */  {  +0.3     , -0.25  ,  +0.1    ,  -0.7  },
							  /* - */  {  +0.3     , -0.1   ,  -0.7    ,   0.0  } };

#endif

//V2
#if 0
							  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
							  /*	 	  H	     P	     +	    - */	
double energyMatrix[4][4] =	  /* H */ {{ -1.0     ,  0.0    ,  +0.125 ,  +0.125  },
 							  /* P */  {  0.0     , -0.25   ,  -0.125 , -0.125  },
							  /* + */  {  +0.125  , -0.125  ,  +1.0 , -1.0  },
							  /* - */  {  +0.125  , -0.125  ,  -1.0 , +1.0  } };

#endif


//V1
#if 0
							  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
							  /*	 	  H	     P	     +	    - */	
double energyMatrix[4][4] =	  /* H */ {{ -1.0  ,  0.0,   0.0 ,  0.0  },
 							  /* P */  {  0.0  ,  0.0 ,  -0.125 , -0.125  },
							  /* + */  {  0.0  , -0.125  ,  +1.0 , -1.0  },
							  /* - */  {  0.0  , -0.125  ,  -1.0 , +1.0  } };

#endif

#if 0 //hHYX model (Borenberg-Bauer)

							  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
							  /*	 	  H	     P	     +	    - */	
double energyMatrix[4][4] =	  /* H */ {{ -2.0  , -4.0,   -1.0 ,  2.0  },
 							  /* P */  { -4.0  , -3.0 ,  -1.0 ,  0.0  },
							  /* + */  { -1.0  , -1.0  ,  0.0 ,  2.0  },
							  /* - */  {  2.0  ,  0.0  ,  2.0 ,  0.0  } };

#endif

seqSeeker::seqSeeker(int length, int maxBest, int lrc):sp(length)
{
	seqLength = length;	
	maxBestSeqs = maxBest;
	lowRangeCounterTres = lrc;
	 
	bestSeqs = new residueArray*[maxBestSeqs];
	
	bestSeqsStatistics = new seqStatistics[maxBestSeqs];
	
	if( (!bestSeqs) || (!bestSeqsStatistics))
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
	
	for(int i = 0; i < maxBestSeqs; i++)
		if( !(bestSeqs[i] = new residueArray(seqLength)) )
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);	
		}
		
	
	char name[100];// = {0};
	char str[30] = "-mer-struct-enum-mod";
	int side = (int) sqrt((double)seqLength);
	
	sprintf(name, "./DB/%d-(%d)%s", seqLength, side, str);
	
	FILE* fp = fopen(name, "rb");
	
	if(!fp)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
	cout<<"\nopened file: "<<name<<" for DB\n";

	int tmp;
	if(fread(&tmp, sizeof(int), 1, fp) != 1)
	{
		cout<<"File Read Error - seqSeeker\n";
		fclose(fp);
		exit(1);
	}
	
	if(tmp != seqLength)
	{
		cout<<"Incompatible lengths - ERROR\n";
		fclose(fp);
	}
 	
	double buf = 0;
	if(fread(&buf, sizeof(double), 1, fp) != 1)
	{
		cout<<"File Read Error - seqSeeker\n";
		fclose(fp);
		exit(1);
	}
	sizeOfDB = buf;
	cout<<"Sequence length: "<<seqLength<<" Size of DB: "<<sizeOfDB<<endl;
	
	structureDB = new point*[sizeOfDB];
	
	if(!structureDB)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
	
	for(int i = 0; i < sizeOfDB; i++)
	{
		if( !(structureDB[i] = new point[seqLength]) )
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);
		}
	}
			
	//loading the cordinates from the file:
	for(int i = 0; i < sizeOfDB; i++)
	{
		for(int j = 0; j < seqLength; j++)
		{
			if( (fread(&(structureDB[i][j].x), sizeof(int), 1, fp) != 1)||
				(fread(&(structureDB[i][j].y), sizeof(int), 1, fp) != 1) )
			{
				cout<<"File Read Error - seqSeeker\n";
				fclose(fp);
				exit(1);
			}
		}
	}
	
	matrix = new int*[seqLength*2];
	if(!matrix)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
		
	for(int j = 0; j < seqLength*2; j++)
		if(!(matrix[j] = new int[seqLength*2]))
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);
		}
		
	for(int i = 0; i < seqLength*2; i++)
		for(int j = 0; j < seqLength*2; j++)		
			matrix[i][j] = -1;
	
	currentStructIdx = 0;
	
	eng = new double[sizeOfDB];
	if(!eng)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}	
	fclose(fp);
	//points** structureDB;
	
}



seqSeeker::seqSeeker(int length, int maxBest, int sideadd, int lrc):sp(length)
{
	//cout<<"Begin seqSeeker ctor\n";
	seqLength = length;	
	maxBestSeqs = maxBest;
	lowRangeCounterTres = lrc;
	 
	bestSeqs = new residueArray*[maxBestSeqs];
	
	bestSeqsStatistics = new seqStatistics[maxBest];
	
	if( (!bestSeqs) || (!bestSeqsStatistics))
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
	
	for(int i = 0; i < maxBestSeqs; i++)
		if( !(bestSeqs[i] = new residueArray(seqLength)) )
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);	
		}
		
	
	char name[100];// = {0};
	//char str[30] = "-mer-struct-enum-mod-n";
	char str[30] = "-mer-struct-enum-mod";
	int side = (int) sqrt((double)seqLength);
	
	sprintf(name, "./DB/%d-(%d)%s", seqLength, side + sideadd, str);
	
	FILE* fp = fopen(name, "rb");
	
	if(!fp)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
	cout<<"\nopened file: "<<name<<" for DB\n";

	int tmp;
	if(fread(&tmp, sizeof(int), 1, fp) != 1)
	{
		cout<<"File Read Error - seqSeeker\n";
		fclose(fp);
		exit(1);
	}
	
	if(tmp != seqLength)
	{
		cout<<"Incompatible lengths - ERROR\n";
		fclose(fp);
	}
 	
	double buf = 0;
	if(fread(&buf, sizeof(double), 1, fp) != 1)
	{
		cout<<"File Read Error - seqSeeker\n";
		fclose(fp);
		exit(1);
	}
	sizeOfDB = buf;
	
	cout<<"Sequence length: "<<seqLength<<" Size of DB: "<<sizeOfDB<<endl;
	
	
	structureDB = new point*[sizeOfDB];
	
	if(!structureDB)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
	

	
	for(int i = 0; i < sizeOfDB; i++)
	{
		if( !(structureDB[i] = new point[seqLength]) )
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);
		}
	}
		
	//loading the cordinates from the file:
	for(int i = 0; i < sizeOfDB; i++)
	{
		for(int j = 0; j < seqLength; j++)
		{
			if( (fread(&(structureDB[i][j].x), sizeof(int), 1, fp) != 1)||
				(fread(&(structureDB[i][j].y), sizeof(int), 1, fp) != 1) )
			{
				cout<<"File Read Error - seqSeeker\n";
				fclose(fp);
				exit(1);
			}
		}
	}
	
	matrix = new int*[seqLength*2];
	if(!matrix)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
		
	for(int j = 0; j < seqLength*2; j++)
		if(!(matrix[j] = new int[seqLength*2]))
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);
		}
		
	for(int i = 0; i < seqLength*2; i++)
		for(int j = 0; j < seqLength*2; j++)		
			matrix[i][j] = -1;
	
	currentStructIdx = 0;
	
	eng = new double[sizeOfDB];
	if(!eng)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}	
	fclose(fp);
	//points** structureDB;
	cout<<"Finished ctor With no prob.\n";
		
	
}

seqSeeker::seqSeeker(int length, int maxBest, int sideadd, char *name, int lrc):sp(length)
{
	//cout<<"Begin seqSeeker ctor\n";
	seqLength = length;	
	maxBestSeqs = maxBest;
	lowRangeCounterTres = lrc;
	 
	bestSeqs = new residueArray*[maxBestSeqs];
	
	bestSeqsStatistics = new seqStatistics[maxBest];
	
	if( (!bestSeqs) || (!bestSeqsStatistics))
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
	
	for(int i = 0; i < maxBestSeqs; i++)
		if( !(bestSeqs[i] = new residueArray(seqLength)) )
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);	
		}
		
	
// 	char name[100];// = {0};
	//char str[30] = "-mer-struct-enum-mod-n";
	char str[30] = "-mer-struct-enum-mod";
	int side = (int) sqrt((double)seqLength);
	
// 	sprintf(name, "./DB/%d-(%d)%s", seqLength, side + sideadd, str);
	
	FILE* fp = fopen(name, "rb");
	
	if(!fp)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
	cout<<"\nopened file: "<<name<<" for DB\n";

	int tmp;
	if(fread(&tmp, sizeof(int), 1, fp) != 1)
	{
		cout<<"File Read Error - seqSeeker\n";
		fclose(fp);
		exit(1);
	}
	
	if(tmp != seqLength)
	{
		cout<<"Incompatible lengths - ERROR\n";
		fclose(fp);
	}
 	
	double buf = 0;
	if(fread(&buf, sizeof(double), 1, fp) != 1)
	{
		cout<<"File Read Error - seqSeeker\n";
		fclose(fp);
		exit(1);
	}
	sizeOfDB = buf;
	
	cout<<"Sequence length: "<<seqLength<<" Size of DB: "<<sizeOfDB<<endl;
	
	
	structureDB = new point*[sizeOfDB];
	
	if(!structureDB)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
	

	
	for(int i = 0; i < sizeOfDB; i++)
	{
		if( !(structureDB[i] = new point[seqLength]) )
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);
		}
	}
		
	//loading the cordinates from the file:
	for(int i = 0; i < sizeOfDB; i++)
	{
		for(int j = 0; j < seqLength; j++)
		{
			if( (fread(&(structureDB[i][j].x), sizeof(int), 1, fp) != 1)||
				(fread(&(structureDB[i][j].y), sizeof(int), 1, fp) != 1) )
			{
				cout<<"File Read Error - seqSeeker\n";
				fclose(fp);
				exit(1);
			}
		}
	}
	
	matrix = new int*[seqLength*2];
	if(!matrix)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
		
	for(int j = 0; j < seqLength*2; j++)
		if(!(matrix[j] = new int[seqLength*2]))
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);
		}
		
	for(int i = 0; i < seqLength*2; i++)
		for(int j = 0; j < seqLength*2; j++)		
			matrix[i][j] = -1;
	
	currentStructIdx = 0;
	
	eng = new double[sizeOfDB];
	if(!eng)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}	
	fclose(fp);
	//points** structureDB;
	cout<<"Finished ctor With no prob.\n";
		
	
}


seqSeeker::seqSeeker(int length, int maxBest, char *inf):sp(length)
{
	//cout<<"Begin seqSeeker ctor\n";
	int lrc = 5;
	seqLength = length;	
	maxBestSeqs = maxBest;
	lowRangeCounterTres = lrc;
	 
	bestSeqs = new residueArray*[maxBestSeqs];
	
	bestSeqsStatistics = new seqStatistics[maxBest];
	
	if( (!bestSeqs) || (!bestSeqsStatistics))
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
	
	for(int i = 0; i < maxBestSeqs; i++)
		if( !(bestSeqs[i] = new residueArray(seqLength)) )
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);	
		}
		
		
	FILE* fp = fopen(inf, "rb");
	
	if(!fp)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
	cout<<"\nopened file: "<<inf<<" for DB\n";

	int tmp;
	if(fread(&tmp, sizeof(int), 1, fp) != 1)
	{
		cout<<"File Read Error - seqSeeker\n";
		fclose(fp);
		exit(1);
	}
	
	if(tmp != seqLength)
	{
		cout<<"Incompatible lengths - ERROR\n";
		fclose(fp);
	}
 	
	double buf = 0;
	fseek(fp, sizeof(int)*seqLength , SEEK_CUR);
	if(fread(&buf, sizeof(double), 1, fp) != 1)
	{
		cout<<"File Read Error - seqSeeker\n";
		fclose(fp);
		exit(1);
	}
	sizeOfDB = buf;
	
	cout<<"Sequence length: "<<seqLength<<" Size of DB: "<<sizeOfDB<<endl;
	
	
	structureDB = new point*[sizeOfDB];
	
	if(!structureDB)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
	

	
	for(int i = 0; i < sizeOfDB; i++)
	{
		if( !(structureDB[i] = new point[seqLength]) )
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);
		}
	}
		
	//loading the cordinates from the file:
	for(int i = 0; i < sizeOfDB; i++)
	{
		for(int j = 0; j < seqLength; j++)
		{
			if( (fread(&(structureDB[i][j].x), sizeof(int), 1, fp) != 1)||
				(fread(&(structureDB[i][j].y), sizeof(int), 1, fp) != 1) )
			{
				cout<<"File Read Error - seqSeeker\n";
				fclose(fp);
				exit(1);
			}
		}
	}
	
	matrix = new int*[seqLength*2];
	if(!matrix)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
		
	for(int j = 0; j < seqLength*2; j++)
		if(!(matrix[j] = new int[seqLength*2]))
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);
		}
		
	for(int i = 0; i < seqLength*2; i++)
		for(int j = 0; j < seqLength*2; j++)		
			matrix[i][j] = -1;
	
	currentStructIdx = 0;
	
	eng = new double[sizeOfDB];
	if(!eng)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}	
	fclose(fp);
	//points** structureDB;
	cout<<"Finished ctor With no prob.\n";
		
	
}

	
seqSeeker::~seqSeeker()
{
	//cout<<"~seqSeeker()"<<endl;
	delete []bestSeqsStatistics;
	delete []eng;
	for(int i = 0; i < maxBestSeqs; i++)
		delete bestSeqs[i];
	delete []bestSeqs;
	
	for(int i = 0; i < sizeOfDB; i++)
		delete []structureDB[i];
	delete []structureDB;
	
	for(int j = 0; j < seqLength*2; j++)
		delete []matrix[j];
	delete []matrix;
	
		
}
	


double seqSeeker::getEnergyValue(int x, int y, int i)
{  
	if( (matrix[y][x] > -1)&&
	    ( ((matrix[y][x] - i) > 2)||
	      ((matrix[y][x] - i) < -2) ) )
		return energyMatrix[sp.array[matrix[y][x]]][sp.array[i]];

	return 0.0;
}

double seqSeeker::calculateEnergy()
{
	double energy = 0;

	if(currentStructIdx > 0)
		for(int j = 0; j < seqLength; j++)
			matrix[structureDB[currentStructIdx - 1][j].y][structureDB[currentStructIdx - 1][j].x] = -1;
	else //corrected bug founded by Orly (24/8/2011)
  	for(int j = 0; j < seqLength; j++)
       matrix[structureDB[sizeOfDB - 1][j].y][structureDB[sizeOfDB - 1][j].x] = -1;
       
	for(int j = 0; j < seqLength; j++)
			matrix[structureDB[currentStructIdx][j].y][structureDB[currentStructIdx][j].x] = j;
	
	for(int i = 0; i < seqLength; i++)
	{	
		int x = structureDB[currentStructIdx][i].x;
		int y = structureDB[currentStructIdx][i].y;

		if(y < seqLength*2 - 2)
			energy += getEnergyValue(x, y+1, i);
		if(y > 0)
			energy += getEnergyValue(x, y-1, i);
		if(x < seqLength*2 - 2)
			energy += getEnergyValue(x+1, y, i);
		if(x > 0)
			energy += getEnergyValue(x-1, y, i);
		
	}
		
	//Energy will always be double than should be	
	return (energy/2);
}

void seqSeeker::printCurrent(int structIdx)
{
#if 0
	int** Pmatrix = new int*[seqLength];
	if(!Pmatrix)
	{
		cout<<"ERROR - mem alloc - seqSeeker ctor\n";
		exit(1);
	}
		
	for(int j = 0; j < seqLength; j++)
		if(!(Pmatrix[j] = new int[seqLength]))
		{
			cout<<"ERROR - mem alloc - seqSeeker ctor\n";
			exit(1);
		}
		
	for(int i = 0; i < seqLength; i++)
		for(int j = 0; j < seqLength; j++)		
			Pmatrix[i][j] = -1;	

	for(int i = 0; i < seqLength; i++)
		Pmatrix[structureDB[structIdx][i].y][structureDB[structIdx][i].x] = i;
	
	for(int y = seqLength - 1; y >= 0; y--)
	{
		for(int x = 0; x < seqLength; x++)
			if(Pmatrix[y][x] == -1)
				cout<<" ";
			else 
			{
				if(Pmatrix[y][x] < 9)
					cout<<Pmatrix[y][x]<<" ";
				else
					cout<<Pmatrix[y][x];
				
				switch(sp.array[Pmatrix[y][x]])
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
	cout<<"-----------------------------------\n";	
	for(int j = 0; j < seqLength; j++)
		delete []Pmatrix[j];
	delete []Pmatrix;
#endif

	#if 1
	cout<<"["<<seqLength<<"]";	
	for(int i = 0; i < seqLength; i++)
		switch(sp.array[i])
		{
			case 0: cout<<"H"; break;
			case 1: cout<<"P"; break;
			case 2: cout<<"+"; break;
			case 3: cout<<"-"; break;
			default: cout<<"ERROR"; break;
		}
	cout<<" <"<<structIdx<<">\n";
#endif
	//cout<<"-----------------------------------\n";		
	
}
	
int seqSeeker::computeEnergyLandscape(char* fileName, int sizeOfResidueArray, int configFileIndex)
{
	configFileHandler cfh(fileName, sizeOfResidueArray);
	
	char *hp = cfh.getConfiguration(sizeOfResidueArray, configFileIndex);
	if(!hp)
	{
		cout<<"No more sequences in file: "<<cfh.fileName<<" .\n"<<"Max size:"<<configFileIndex<<endl;
		return 0;
	}

	for(int i = 0; i < sizeOfResidueArray; i++)
	{
		switch(hp[i])
		{
			case 'H':
				sp.array[i] = HYDROPHOBIC; break;
 			case 'P':
				sp.array[i] = POLAR_NEUTRAL; break;
 			case '+':
				sp.array[i] = POSITIVE_CHARGE; break;	
			case '-':
				sp.array[i] = NEGATIVE_CHARGE; break;
		}		
	}
	
	residueArray resArr(sizeOfResidueArray);
	currentStructIdx = 0;
	resArr = structureDB[currentStructIdx];
	
	RMSD rmsd(&resArr, sizeOfResidueArray);
	
	for(int i = 0; i < sizeOfDB; i++)
	{
		//eng[i] = calculateEnergy();
		//cout<<eng[i]<<" "<<i<<endl;
		resArr = structureDB[currentStructIdx];
		//cout<<rmsd.compute(resArr)<<" "<<eng[i]<<endl;
		cout<<i<<" "<<rmsd.compute(resArr)<<endl;
		currentStructIdx++;
	}
	return 1;
}		


int seqSeeker::computeSeqThroughDB(char* confFileName, int configfileIndex)
{
	currentStructIdx = 0;
	configFileHandler CfileHdlr(confFileName, seqLength);
	char *hp = CfileHdlr.getConfiguration(seqLength, configfileIndex);
	if(!hp)
	{
		cout<<"No more sequences in file: "<<CfileHdlr.fileName<<" .\n"<<"Max size:"<<configfileIndex<<endl;
		return 0;
	}

	for(int i = 0; i < sp.size; i++)
	{
		switch(hp[i])
		{
			case 'H':
				sp.array[i] = HYDROPHOBIC; break;
 			case 'P':
				sp.array[i] = POLAR_NEUTRAL; break;
 			case '+':
				sp.array[i] = POSITIVE_CHARGE; break;	
			case '-':
				sp.array[i] = NEGATIVE_CHARGE; break;
		}		
	}
	
	double acc = 0;
		
	currStatistics.max = currStatistics.min = 0;
	for(int i = 0; i < sizeOfDB; i++)
	{
		eng[i] = calculateEnergy();
		currentStructIdx++;
		
		acc += eng[i];
		if(eng[i] > currStatistics.max)
		{
			currStatistics.max = eng[i];
			currStatistics.maxStructIndex = i;
		}
		else if(eng[i] < currStatistics.min)
		{
			currStatistics.min = eng[i];
			currStatistics.minStructIndex = i;
		}
	}
	currStatistics.expectation = acc/((double)sizeOfDB);
	
	currStatistics.variance = 0;
	
	for(int i = 0; i < sizeOfDB; i++)
		currStatistics.variance += pow((eng[i] - currStatistics.expectation), 2);
	
	currStatistics.variance /= sizeOfDB;
	
	currStatistics.numInLowRange = 0;
	
	double tres = currStatistics.min + currStatistics.variance;
	
	int m = 0;
	for(int i = 0; i < sizeOfDB; i++)
	{
		if(eng[i] < tres)
		{
			currStatistics.numInLowRange++;
			if(m < maxBestSeqs)
			{
				bestSeqsStatistics[m].minStructIndex = i;
				bestSeqsStatistics[m].min = eng[i];
				m++;
			}
		}
	}
	
	if(currStatistics.numInLowRange < lowRangeCounterTres)
	{			
		currStatistics.print();
		for(int i = 0; i < m; i++)
		{
			cout<<"Min energy: "<<bestSeqsStatistics[i].min<<endl;
			cout<<"Struct index: "<<bestSeqsStatistics[i].minStructIndex<<endl;
		}
		printCurrent(currStatistics.minStructIndex);
		cout<<"------------------------------------------\n";

	} 	
	return 1;
} 
		
int seqSeeker::computeSeqThroughDB()
{
	currentStructIdx = 0;
	sp.shuffle();
	
	
	double acc = 0;
		
	currStatistics.max = currStatistics.min = 0;
	for(int i = 0; i < sizeOfDB; i++)
	{
		eng[i] = calculateEnergy();
		currentStructIdx++;
		
		acc += eng[i];
		if(eng[i] > currStatistics.max)
		{
			currStatistics.max = eng[i];
			currStatistics.maxStructIndex = i;
		}
		else if(eng[i] < currStatistics.min)
		{
			currStatistics.min = eng[i];
			currStatistics.minStructIndex = i;
		}
	}
	currStatistics.expectation = acc/((double)sizeOfDB);
	currStatistics.variance = 0;
	
	for(int i = 0; i < sizeOfDB; i++)
		currStatistics.variance += pow((eng[i] - currStatistics.expectation), 2);
	
	currStatistics.variance /= sizeOfDB;
	
	currStatistics.numInLowRange = 0;
	double tres = currStatistics.min + currStatistics.variance;
	
	int m = 0;
	for(int i = 0; i < sizeOfDB; i++)
	{
		if(eng[i] < tres)
		{
			currStatistics.numInLowRange++;
			if(m < maxBestSeqs)
			{
				bestSeqsStatistics[m].minStructIndex = i;
				bestSeqsStatistics[m].min = eng[i];
				m++;
			}
		}
	}
	
	if(currStatistics.numInLowRange < lowRangeCounterTres)
	{			
		currStatistics.print();
		for(int i = 0; i < m; i++)
		{
			cout<<"Min energy: "<<bestSeqsStatistics[i].min<<endl;
			cout<<"Struct index: "<<bestSeqsStatistics[i].minStructIndex<<endl;
		}
		printCurrent(currStatistics.minStructIndex);
		cout<<"------------------------------------------\n";

	} 	
	return 1;
} 

int seqSeeker::computeIndexedSeqThroughDB(char* fileName, int sizeOfResidueArray, char *indexFileName)
{
	 
	configFileHandler cfh(fileName, sizeOfResidueArray);
	
	int configFileIndex = getIntegerFromFile(indexFileName, 0);
	for(int idx = 0; (configFileIndex = getIntegerFromFile(indexFileName, idx)) != -1; idx++)
	{
		currentStructIdx = 0;
		char *hp = cfh.getConfiguration(sizeOfResidueArray, configFileIndex);
		if(!hp)
		{
			cout<<"No more sequences in file: "<<cfh.fileName<<" .\n"<<"Max size:"<<configFileIndex<<endl;
			return 0;
		}
		//for(int i = 1; i <= 25; i++) 
		//	cout<<hp[i];
		cout<<endl;
		for(int i = 0; i < sizeOfResidueArray; i++)
		{
			switch(hp[i])
			{
				case 'H':
					sp.array[i] = HYDROPHOBIC; break;
 				case 'P':
					sp.array[i] = POLAR_NEUTRAL; break;
 				case '+':
					sp.array[i] = POSITIVE_CHARGE; break;	
				case '-':
					sp.array[i] = NEGATIVE_CHARGE; break;
			}		
		}
	
	
		double acc = 0;
		
		currStatistics.max = currStatistics.min = currStatistics.minStructIndex = 0;
		for(int i = 0; i < sizeOfDB; i++)
		{
			eng[i] = calculateEnergy();
			currentStructIdx++;
		
			acc += eng[i];
			if(eng[i] > currStatistics.max)
			{
				currStatistics.max = eng[i];
				currStatistics.maxStructIndex = i;
			}
			else if(eng[i] < currStatistics.min)
			{
				currStatistics.min = eng[i];
				currStatistics.minStructIndex = i;
			}
		}
		currStatistics.expectation = acc/((double)sizeOfDB);
		currStatistics.variance = 0;
	
		for(int i = 0; i < sizeOfDB; i++)
			currStatistics.variance += pow((eng[i] - currStatistics.expectation), 2);
	
		currStatistics.variance /= sizeOfDB;
	
		currStatistics.numInLowRange = 0;
		double tres = currStatistics.min + currStatistics.variance;
	
		for(int i = 0; i < sizeOfDB; i++)
			if(eng[i] < tres)
				currStatistics.numInLowRange++;
	
		cout<<"#"<<configFileIndex<<"\n";		
		currStatistics.print();
		//printCurrent(currStatistics.minStructIndex);
		
		cfh.writeStructure2output(sizeOfResidueArray, 
								  &structureDB[currStatistics.minStructIndex][0] - 1, 
								  hp);
		configFileIndex++;
		cout<<"\n---------------------------------------------\n";
		
	}//end while	
	return 1;
} 

int seqSeeker::computeIndexedSeqThroughDBdeviations(char* fileName, int sizeOfResidueArray, char *indexFileName)
{
	 
	configFileHandler cfh(fileName, sizeOfResidueArray);
	
	int configFileIndex = getIntegerFromFile(indexFileName, 0);
	for(int idx = 0; (configFileIndex = getIntegerFromFile(indexFileName, idx)) != -1; idx++)
	{
		currentStructIdx = 0;
		char *hp = cfh.getConfiguration(sizeOfResidueArray, configFileIndex);
		if(!hp)
		{
			cout<<"No more sequences in file: "<<cfh.fileName<<" .\n"<<"Max size:"<<configFileIndex<<endl;
			return 0;
		}
		//for(int i = 1; i <= 25; i++) 
		//	cout<<hp[i];
		cout<<endl;
		for(int i = 0; i < sizeOfResidueArray; i++)
		{
			switch(hp[i])
			{
				case 'H':
					sp.array[i] = HYDROPHOBIC; break;
 				case 'P':
					sp.array[i] = POLAR_NEUTRAL; break;
 				case '+':
					sp.array[i] = POSITIVE_CHARGE; break;	
				case '-':
					sp.array[i] = NEGATIVE_CHARGE; break;
			}		
		}
	
	
		double acc = 0;
		
		currStatistics.max = currStatistics.min = currStatistics.minStructIndex = 0;
		for(int i = 0; i < sizeOfDB; i++)
		{
			eng[i] = calculateEnergy();
			currentStructIdx++;
		
			acc += eng[i];
			if(eng[i] > currStatistics.max)
			{
				currStatistics.max = eng[i];
				currStatistics.maxStructIndex = i;
			}
			else if(eng[i] < currStatistics.min)
			{
				currStatistics.min = eng[i];
				currStatistics.minStructIndex = i;
			}
		}
		currStatistics.expectation = acc/((double)sizeOfDB);
		currStatistics.variance = 0;
	
		for(int i = 0; i < sizeOfDB; i++)
			currStatistics.variance += pow((eng[i] - currStatistics.expectation), 2);
	
		currStatistics.variance /= sizeOfDB;
	
		currStatistics.numInLowRange = 0;
		double tres = currStatistics.min + currStatistics.variance;
	
		double sdv = sqrt(currStatistics.variance);
		double varThresh[9];
		int varCnt[9] = {0};
		for(int s = 1; s < 9; s++)
			varThresh[s] = currStatistics.min + sdv/(double)s;
		
		for(int i = 0; i < sizeOfDB; i++)
		{
			for(int s = 1; s < 9; s++)
				if(eng[i] < varThresh[s])
					varCnt[s]++;	
			if(eng[i] < tres)
				currStatistics.numInLowRange++;
		}
		cout<<"#"<<configFileIndex<<"\n";		
		currStatistics.print();
		cout<<"\nLow range SDV: "<< varThresh[1]<<endl;
		for(int s = 1; s < 9; s++)
			cout<<varThresh[s]<<" "<<varCnt[s]<<endl;
		
		
		cfh.writeStructure2output(sizeOfResidueArray, 
								  &structureDB[currStatistics.minStructIndex][0] - 1, 
								  hp);
		configFileIndex++;
		cout<<"\n---------------------------------------------\n";
		
	}//end while	
	return 1;
} 

int seqSeeker::computeAllSeqThroughDBdeviations(char* fileName, int sizeOfResidueArray)
{
	 
	int configFileIndex = 0;
	 
	configFileHandler cfh(fileName, sizeOfResidueArray);
	
	while(true)
	{
		currentStructIdx = 0;
		char *hp = cfh.getConfiguration(sizeOfResidueArray, configFileIndex);
		if(!hp)
		{
			cout<<"No more sequences in file: "<<cfh.fileName<<" .\n"<<"Max size:"<<configFileIndex<<endl;
			return 0;
		}
	
		
		//for(int i = 1; i <= 25; i++) 
		//	cout<<hp[i];
		cout<<endl;
		for(int i = 0; i < sizeOfResidueArray; i++)
		{
			switch(hp[i])
			{
				case 'H':
					sp.array[i] = HYDROPHOBIC; break;
 				case 'P':
					sp.array[i] = POLAR_NEUTRAL; break;
 				case '+':
					sp.array[i] = POSITIVE_CHARGE; break;	
				case '-':
					sp.array[i] = NEGATIVE_CHARGE; break;
			}		
		}
	
	
		double acc = 0;
		
		currStatistics.max = currStatistics.min = currStatistics.minStructIndex = 0;
		for(int i = 0; i < sizeOfDB; i++)
		{
			eng[i] = calculateEnergy();
			currentStructIdx++;
		
			acc += eng[i];
			if(eng[i] > currStatistics.max)
			{
				currStatistics.max = eng[i];
				currStatistics.maxStructIndex = i;
			}
			else if(eng[i] < currStatistics.min)
			{
				currStatistics.min = eng[i];
				currStatistics.minStructIndex = i;
			}
		}
		currStatistics.expectation = acc/((double)sizeOfDB);
		currStatistics.variance = 0;
	
		for(int i = 0; i < sizeOfDB; i++)
			currStatistics.variance += pow((eng[i] - currStatistics.expectation), 2);
	
		currStatistics.variance /= sizeOfDB;
	
		currStatistics.numInLowRange = 0;
		double tres = currStatistics.min + currStatistics.variance;
	
		double sdv = sqrt(currStatistics.variance);
		double varThresh[9];
		int varCnt[9] = {0};
		for(int s = 1; s < 9; s++)
			varThresh[s] = currStatistics.min + sdv/(double)s;
		
		int additionalMinStructs = 0;
		int indexOfminStructs[100001];
		for(int i = 0; i < sizeOfDB; i++)
		{	
			if(currStatistics.min == eng[i] && currStatistics.minStructIndex != i && additionalMinStructs < 100000) {
				additionalMinStructs++;
				indexOfminStructs[additionalMinStructs] = i;
			}
			for(int s = 1; s < 9; s++)
				if(eng[i] < varThresh[s])
					varCnt[s]++;	
			if(eng[i] < tres)
				currStatistics.numInLowRange++;
		}
		cout<<"#"<<configFileIndex<<"\n";		
		currStatistics.print();
		cout<<"\nLow range SDV: "<< varThresh[1]<<endl;
		for(int s = 1; s < 9; s++)
			cout<<varThresh[s]<<" "<<varCnt[s]<<endl;
		cout<<"\n"<<"Additional minimal structures: "<<additionalMinStructs<<"\n";
		
		cout<<"Min structures:\n\n";
		int sn = 1;
		cout<<"SN:"<<configFileIndex<<"."<<sn<<"\n";
		cfh.writeStructure2output(sizeOfResidueArray, 
								  &structureDB[currStatistics.minStructIndex][0] - 1, 
								  hp);
		cout<<"\n";
		for(int j = 1; j <= additionalMinStructs; j++) {
			sn++;
			cout<<"SN:"<<configFileIndex<<"."<<sn<<"\n";
			cfh.writeStructure2output(sizeOfResidueArray, 
								  &structureDB[indexOfminStructs[j]][0] - 1, 
								  hp);
		}
		cout<<"\n";
		configFileIndex++;
		cout<<"\n---------------------------------------------\n";
		
	}//end while	
	return 1;
} 


int seqSeeker::computeAllSeqThroughDB(char* fileName, int sizeOfResidueArray)
{
	
	int configFileIndex = 0;
	 
	configFileHandler cfh(fileName, sizeOfResidueArray);
	
	while(true)
	{
		currentStructIdx = 0;
		char *hp = cfh.getConfiguration(sizeOfResidueArray, configFileIndex);
		if(!hp)
		{
			cout<<"No more sequences in file: "<<cfh.fileName<<" .\n"<<"Max size:"<<configFileIndex<<endl;
			return 0;
		}
		//for(int i = 1; i <= 25; i++) 
		//	cout<<hp[i];
		cout<<endl;
		for(int i = 0; i < sizeOfResidueArray; i++)
		{
			switch(hp[i])
			{
				case 'H':
					sp.array[i] = HYDROPHOBIC; break;
 				case 'P':
					sp.array[i] = POLAR_NEUTRAL; break;
 				case '+':
					sp.array[i] = POSITIVE_CHARGE; break;	
				case '-':
					sp.array[i] = NEGATIVE_CHARGE; break;
			}		
		}
	
	
		double acc = 0;
		
		currStatistics.max = currStatistics.min = currStatistics.minStructIndex = 0;
		for(int i = 0; i < sizeOfDB; i++)
		{
			eng[i] = calculateEnergy();
			currentStructIdx++;
		
			acc += eng[i];
			if(eng[i] > currStatistics.max)
			{
				currStatistics.max = eng[i];
				currStatistics.maxStructIndex = i;
			}
			else if(eng[i] < currStatistics.min)
			{
				currStatistics.min = eng[i];
				currStatistics.minStructIndex = i;
			}
		}
		currStatistics.expectation = acc/((double)sizeOfDB);
		currStatistics.variance = 0;
	
		for(int i = 0; i < sizeOfDB; i++)
			currStatistics.variance += pow((eng[i] - currStatistics.expectation), 2);
	
		currStatistics.variance /= sizeOfDB;
	
		currStatistics.numInLowRange = 0;
		double tres = currStatistics.min + currStatistics.variance;
	
		for(int i = 0; i < sizeOfDB; i++)
			if(eng[i] < tres)
				currStatistics.numInLowRange++;
	
		cout<<"#"<<configFileIndex<<"\n";		
		currStatistics.print();
		//printCurrent(currStatistics.minStructIndex);
		
		cfh.writeStructure2output(sizeOfResidueArray, 
								  &structureDB[currStatistics.minStructIndex][0] - 1, 
								  hp);
		configFileIndex++;
		cout<<"\n---------------------------------------------\n";
		
	}//end while	
	return 1;
} 

int seqSeeker::getLowestEnergyStructures(int numOfLowEnergyStruct)
{
	sortedStack ss(numOfLowEnergyStruct);	
	currentStructIdx = 0;
	sp.shuffle();
	
	
	for(int i = 0; i < sizeOfDB; i++)
	{
		ss.insert(calculateEnergy(), i);
		currentStructIdx++;
		
	}
	
	

		//ss.print();
		//printCurrent(ss.getLowestItemIndex());
		if(ss.isUnique() > 0)
		{
			ss.print();
			printCurrent(ss.getLowestItemIndex());	
		}
		/*cout<<"is the only one !\n";
		else
			cout<<"Not unique\n";*/
		cout<<"--------------------------------------------------\n";
		
	return 1;
}

void seqSeeker::printDBasText(char *fileName)
{
	char hp[100] = "HHHHHHHHHHHHHHHHHHHHHHHHHHHHHH";
	int sizeOfResidueArray = 25;
	configFileHandler cfh(fileName, sizeOfResidueArray);
	for(int i = 0; i < sizeOfDB; i++)
	{
		cfh.writeStructure2output(sizeOfResidueArray, 
								  &structureDB[i][0] - 1, 
								  hp);
	}
	cout<<endl;
}

	
void seqSeeker::countDB4externalEdges()
{
	double both = 0, e1 = 0, e2 = 0, et1 = 0, et2 = 0;
	int i;
	for(i = 0; i < sizeOfDB; i++)
	{
		if((double)countExternalEdges(structureDB[i], e1, e2) == 2)
			both++;
		et1 += e1;
		et2 += e2;
	}
	
	cout<<"\nBoth Edges: "<<both<<" out of: "<<i<<endl;
	cout<<"Percent both: "<<(both/(i))*100.0<<endl;
	
	cout<<"\nedge 1 : "<<et1<<" out of: "<<i<<endl;
	cout<<"Percent edge 1: "<<(et1/(i))*100.0<<endl;

	cout<<"\nedge 2 : "<<et2<<" out of: "<<i<<endl;
	cout<<"Percent edge 2: "<<(et2/(i))*100.0<<endl;

	
}	

	
void seqSeeker::countDB4AllexternalEdges()
{
	
	double total = 0, edgeCnt[512] = {0.0};
	int i;
	for(i = 0; i < sizeOfDB; i++)
		total += (double)countExternalEdges4AllresiduesPro(structureDB[i], seqLength, edgeCnt);
	
	cout<<"Edges:\n------\n";
	for(int j = 0; j < seqLength; j++)
		cout<<j+1<<": "<<edgeCnt[j]<<" "<<edgeCnt[j]/i*100.0<<" %\n";
	
	cout<<"total:\n------\n"<<total<<" "<<total/(i*seqLength)*100.0<<" %\n";
	
	
}	

bool seqSeeker::recursiveIsExternalEdge(point p, int **matrix, int size)
{
	//cout<<"get here "<<p.x<<" "<<p.y<<endl;
	if(p.x == 0 + 1|| p.x == size*2 - 1 || p.y == 0 + 1|| p.y == size*2 - 1)
		return true;
	
	if(matrix[p.y + 1 + 1][p.x + 1] == 0)
	{
		matrix[p.y + 1 + 1][p.x + 1] = -1;
		p.y++;
		if(recursiveIsExternalEdge(p, matrix, size))
			return true;
		p.y--;
	}
	
	if(matrix[p.y - 1 + 1][p.x + 1] == 0)
	{
		matrix[p.y - 1 + 1][p.x + 1] = -1;
		p.y--;
		if(recursiveIsExternalEdge(p, matrix, size))
			return true;
		p.y++;
	}

	if(matrix[p.y + 1][p.x + 1 + 1] == 0)
	{
		matrix[p.y + 1][p.x + 1 + 1] = -1;
		p.x++;
		if(recursiveIsExternalEdge(p, matrix, size))
			return true;
		p.x--;
	}

	if(matrix[p.y + 1][p.x - 1 + 1] == 0)
	{
		matrix[p.y + 1][p.x - 1 + 1] = -1;
		p.x--;
		if(recursiveIsExternalEdge(p, matrix, size))
			return true;
		p.x++;
	}
	
	return false;	
	
}

int seqSeeker::countExternalEdges4AllresiduesPro(point *structure, int originalSize, double *edgeCnt)
{
	
	int sumEdges = 0;
		
	int **matrix = new int*[originalSize*2 + 2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < originalSize*2 + 2; i++)
	{
		if( !(matrix[i] = new int[originalSize*2 + 2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < originalSize*2 + 2; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 0; i < originalSize; i++)
		matrix[structure[i].y + 1][structure[i].x + 1] = i + 1;
	
	for(int i = 0; i < originalSize; i++)
	{
		
		if(recursiveIsExternalEdge(structure[i], matrix, originalSize))
		{
				edgeCnt[i]++;
				sumEdges++;
				
		/*		if(i == originalSize || i == originalSize - 1 || i == 1 || i == 2)
					cout<<i<<" 1 ";	*/
		}
		/*else
			if(i == originalSize || i == originalSize - 1 || i == 1 || i == 2)
				cout<<i<<" 0 ";	
	*/
		
		for(int m = 0; m < originalSize*2 + 2; m++)
			for(int n = 0; n < originalSize*2 + 2; n++)
				matrix[m][n] = 0;
		for(int m = 0; m < originalSize; m++)
			matrix[structure[m].y + 1][structure[m].x + 1] = m + 1;

	
	}
	
	
	for(int i = 0; i < originalSize*2 + 2 ; i++)
		delete []matrix[i];
	delete []matrix;
	
	return sumEdges;
}

//structure here is from zero !!!
int seqSeeker::countExternalEdges4Allresidues(point *structure1, double *edgeCnt)
{
	int originalSize = seqLength;
	int sumEdges = 0;
		
	int **matrix = new int*[originalSize*2 + 2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < originalSize*2 + 2; i++)
	{
		if( !(matrix[i] = new int[originalSize*2 + 2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < originalSize*2 + 2; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 0; i < originalSize; i++)
		matrix[structure1[i].y + 1][structure1[i].x + 1] = i + 1;

	for(int i = 0; i < originalSize; i++)
	{
		
		if( (matrix[structure1[i].y + 1 - 1][structure1[i].x + 1] == 0) ||//up
			(matrix[structure1[i].y + 1 + 1][structure1[i].x + 1] == 0) ||//down
			(matrix[structure1[i].y + 1][structure1[i].x + 1 - 1] == 0) ||//left
			(matrix[structure1[i].y + 1][structure1[i].x + 1 + 1] == 0))//right
		{
				edgeCnt[i]++;
				sumEdges++;
		}
	
	}
	
	
	for(int i = 0; i < originalSize*2 + 2 ; i++)
		delete []matrix[i];
	delete []matrix;

	return sumEdges;
}

//structure here is from zero !!!
int seqSeeker::countExternalEdges(point *structure1, double &edgeCnt1, double &edgeCnt2)
{
	int originalSize = seqLength;
	
	edgeCnt1 = 0;
	edgeCnt2 = 0;
	
	int **matrix = new int*[originalSize*2 + 2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < originalSize*2 + 2; i++)
	{
		if( !(matrix[i] = new int[originalSize*2 + 2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < originalSize*2 + 2; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 0; i < originalSize; i++)
		matrix[structure1[i].y + 1][structure1[i].x + 1] = i + 1;

	originalSize--;
	//end:
	if( (matrix[structure1[originalSize].y + 1 - 1][structure1[originalSize].x + 1] == 0) ||//up
		(matrix[structure1[originalSize].y + 1 + 1][structure1[originalSize].x + 1] == 0) ||//down
		(matrix[structure1[originalSize].y + 1][structure1[originalSize].x + 1 - 1] == 0) ||//left
		(matrix[structure1[originalSize].y + 1][structure1[originalSize].x + 1 + 1] == 0))//right
			edgeCnt1++;
	//begin:
	if( (matrix[structure1[0].y + 1 - 1][structure1[0].x + 1] == 0) ||//up
		(matrix[structure1[0].y + 1 + 1][structure1[0].x + 1] == 0) ||//down
		(matrix[structure1[0].y + 1][structure1[0].x + 1 - 1] == 0) ||//left
		(matrix[structure1[0].y + 1][structure1[0].x + 1 + 1] == 0))//right
			edgeCnt2++;

	originalSize++;
	
	for(int i = 0; i < originalSize*2 + 2 ; i++)
		delete []matrix[i];
	delete []matrix;

	return edgeCnt1 + edgeCnt2;
}
void seqStatistics::print()
{
	cout<<"\nstatistics:\n";
	cout<<"E: "<<expectation<<", "<<"V: "<<variance<<endl;
	cout<<"Max: "<<max<<", Min: "<<min;
	cout<<", Low Range counter: "<< numInLowRange<<endl;
	cout<<"minStructIndex: "<<minStructIndex<<endl;
}


int main(int argc, char** argv)
{
	
	//line: 426 -n/
#if 0
	
	if(argc < 2)
	{	
		cout<<"file_name\n";
		exit(0);
	}
	seqSeeker ss(25, 5, argv[1]);
	ss.countDB4AllexternalEdges();
#endif
	
#if 0
	if(argc < 2)
	{	
		cout<<"add\n";
		exit(0);
	}
	seqSeeker ss(25, 5, atoi(argv[1]), atoi(argv[1]));
	ss.countDB4AllexternalEdges();
#endif	
	
#if 1
	if(argc < 4)
	{
		cout<<"seqSeeker sequence_length sequenceFileName_Input bindb_name_Input\n";
		exit(0);
	}
	
	seqSeeker ss(atoi(argv[1]), 5, 1, argv[3], 1);
	
	ss.computeAllSeqThroughDBdeviations(argv[2], atoi(argv[1]));
// 	ss.computeAllSeqThroughDB(argv[2], 25);
	//ss.computeIndexedSeqThroughDB(argv[1], 25, argv[2]);
// 	ss.computeIndexedSeqThroughDBdeviations(argv[1], 25, argv[2]);
	return 0;
#endif

#if 0
	if(argc < 3)
	{	
		cout<<"add, filename\n";
		exit(0);
	}
	seqSeeker ss(25, 5, atoi(argv[1]), atoi(argv[1]));
	//ss.countDB4AllexternalEdges();
	ss.printDBasText(argv[2]);
			
#endif
	
#if 0
	seqSeeker ss(25, 5, 1, 1);
	ss.countDB4externalEdges();
#endif
	
	
#if 0
	if(argc < 3)
	{
		cout<<"configFileName configFileIndex\n";
		exit(0);
	}
	
	seqSeeker ss(36, 5, 0, 1);
	
	ss.computeEnergyLandscape(argv[1], 36, atoi(argv[2]));
	return 0;
#endif
	
#if 0
	if(argc < 3)
	{
		cout<<"iteretions lowRangeCounterTres\n";
		exit(0);
	}
	
	seqSeeker ss(36, 5, atoi(argv[2]));
	for(int i = 0; i < atoi(argv[1]); i++) 
		ss.computeSeqThroughDB();
		return 0;
#endif
		
#if 0
	if(argc < 3)
	{
		cout<<"iteretions lowRangeCounterTres\n";
		exit(0);
	}
	
	seqSeeker ss(25, 5, 1, atoi(argv[2]));
	for(int i = 0; i < atoi(argv[1]); i++) 
		ss.computeSeqThroughDB();
	return 0;
#endif
		
#if 0
	if(argc < 3)
	{
		cout<<"lowRangeCounterTres filename configfileIndex\n";
		exit(0);
	}
	
	seqSeeker ss(18, 5, 2, atoi(argv[1]));
	 
	ss.computeSeqThroughDB(argv[2], atoi(argv[3]));
	return 0;
#endif
	
#if 0
	if(argc < 3)
	{
		cout<<"iteretions numOfLowEnergyStruct\n";
		exit(0);
	}

	int numOfLowEnergyStruct = atoi(argv[2]);	
	seqSeeker ss(25, 5, 1, numOfLowEnergyStruct);
	

	for(int i = 0; i < atoi(argv[1]); i++) 
		ss.getLowestEnergyStructures(numOfLowEnergyStruct);
	return 0;
#endif

		
}
