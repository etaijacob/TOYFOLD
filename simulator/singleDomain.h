//doubleDomain.h

//dimersChaperonComplex.h

#ifndef SINGLEDOMAIN_H
#define SINGLEDOMAIN_H

#include "protchap.h"


#define ERROR_FPT_THRESHOLD 0.0
#define ENERGY_BACK_GAP 2.5

class singleDomain: public foldingComplex
{
public:
	singleDomain();
	
	int fold();
	int unfold();
	
	int writeStructures2output();
	
};

#endif
