#include "randomNumberGenerator.h"
#include "definitions.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

	
randomNumberGenerator::randomNumberGenerator():eventCounter(0)
{
#ifndef USE_RAND48
	srand((unsigned)time(0)); 
#else
	srand48((unsigned)time(0));
	//seed48((char)time(0));
#endif
	stack = 0;
//	cout<<"stack "<<stack<<endl;
}
/*
int randomNumberGenerator::getNewPivot()
{
       
       int random_integer; 
       int lowest = 1, highest = SIZE_OF_RESIDUE_ARRAY; 
       int range=(highest-lowest)+1; 
       
#ifndef USE_RAND48     
       random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0)); 
       //cout << random_integer << endl; 
#else
       random_integer = lowest+int(range*(double)lrand48()/((double)MAX_RAND48 + 1.0)); 
       	
#endif
       return random_integer;
}
*/
int randomNumberGenerator::generateNumberInRange(int lowest, int highest)
{ 
	int random_integer; 
	int range=(highest-lowest)+1; 

#ifndef USE_RAND48        
	random_integer = lowest+int(range*rand()/(RAND_MAX + 1.0)); 
#else
	random_integer = lowest+int(range*(double)lrand48()/((double)MAX_RAND48 + 1.0));
	
#endif
	return random_integer; 
}

double randomNumberGenerator::generateFractionInRange(double lowest, double highest)
{
	 
	double rand_num; 
	double range=(highest-lowest); 

#ifndef USE_RAND48       
	rand_num = lowest + range*(double)rand()/((double)RAND_MAX); 
#else
	rand_num = lowest + range*drand48();
#endif
	return rand_num; 
}

double randomNumberGenerator::generateRandomFraction()//(0,1)
{
	 
	double rand_num;  

#ifndef USE_RAND48       
	rand_num = (double)rand()/((double)RAND_MAX); 
#else
	rand_num = drand48();
	//cout<<"Random fraction:"<<rand_num<<endl;
#endif
	return rand_num; 
}

//random stack generates integers from zero to stackSize
int randomNumberGenerator::initStack(int stackSize)
{
	if(stack)
		delete []stack;
	
	stack = new int[stackSize];
	this->stackSize = stackSize;
	
	for(int i = 0; i < stackSize; i++)
		stack[i] = i;
	
	return 1;
}

int randomNumberGenerator::generateRandomStackInteger()
{
	if(stackSize == 0)
		return -1;
	
	int random_integer; 
	int range = stackSize; 

#ifndef USE_RAND48        
	random_integer = int(range*rand()/(RAND_MAX + 1.0)); 
#else
	random_integer = int(range*(double)lrand48()/((double)MAX_RAND48 + 1.0));	
#endif
	int retVal = stack[random_integer];
	stack[random_integer] = stack[stackSize - 1];
	stackSize--;
	if(stackSize == 0)
	{
		delete []stack;
		stack = 0;
	}
	
	return retVal;

}	


