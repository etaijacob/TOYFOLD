//localConformations.h
#ifndef LOCAL_CONFORMATION_HEADER
#define LOCAL_CONFORMATION_HEADER

#include "point.h"
#include "randomNumberGenerator.h"
#include "dynamicLibEnum.h"

class localConformations
{
public:
	
	
	randomNumberGenerator RNG;
	point pivotPoint;
	enumLibrary db;
	
	localConformations();
	~localConformations(){}
	
	point* getNewLocalConf(point p1, point p2, int dres);
	
	
	
};

#endif //LOCAL_CONFORMATION_HEADER
