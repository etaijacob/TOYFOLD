//localConformations.cpp

#include "localConformations.h"

localConformations::localConformations():RNG()
{
	db.enumerateDBLIB();	
}
	
	
point* localConformations::getNewLocalConf(point p1, point p2, int dres)
{
	p2 -= p1;
	pivotPoint = p1;
	p2.x += ENUM_ARR_SIZE;
	p2.y += ENUM_ARR_SIZE;	
	
	int numOfPossibilities = db.getNumberOfPossibilities(dres + 1, p2);
	if(numOfPossibilities == 0)
		return NULL;
	
	int position = RNG.generateNumberInRange(0, numOfPossibilities - 1);
	
	
	return db.getPointsOfConformation(dres + 1, p2, position);
}
