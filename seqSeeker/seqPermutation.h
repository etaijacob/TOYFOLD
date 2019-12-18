//seqPermutation.h



#ifndef SEQ_PERMUTATION_HEADER
#define SEQ_PERMUTATION_HEADER

#include "../simulator/randomNumberGenerator.h"
#include <iostream>

using namespace std;

class seqPermutation
{
public:
	int* array;	
	int* positionArr;
	int* secondArr;
	int size;
	double counter;
	static double alphabetStatistics[4];
	int alphabet[4];
	int tmp_alphabet[4];	
	
	randomNumberGenerator RNG;
	seqPermutation(int length);
	seqPermutation(seqPermutation& sp);
	
	seqPermutation& operator=(const seqPermutation& sp);
	
	~seqPermutation();
	
	int generateAll();

//private functions:
	
	void permutate(int length);
	int shuffle();
	
	friend ostream& operator<<(ostream &out, seqPermutation p);
		
};

#endif //SEQ_PERMUTATION_HEADER
