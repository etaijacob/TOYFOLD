//randomNumberGenerator.h
#ifndef RANDOM_NUMBER_GENERATOR_HEADER
#define RANDOM_NUMBER_GENERATOR_HEADER

#define USE_RAND48
const unsigned long MAX_RAND48 = 2147483647;//pow(2.0,31);


class randomNumberGenerator
{
public:
	unsigned long eventCounter;
	int *stack;
	int stackSize;
	
	randomNumberGenerator();
	~randomNumberGenerator(){ if(stack) delete []stack; }
	
	int generateNumberInRange(int lowest, int highest);
	double generateFractionInRange(double lowest,double highest);
	double generateRandomFraction();//(0,1)
	
	int generateRandomStackInteger();
	int initStack(int stackSize);

 
	
};
#endif //RANDOM_NUMBER_GENERATOR_HEADER
