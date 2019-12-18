#ifndef RESIDUE_HEADER
#define RESIDUE_HEADER

#include "point.h"
#include "definitions.h"
#include <stdio.h>



#define HYDROPHOBIC		0
#define POLAR_NEUTRAL	1
#define POSITIVE_CHARGE	2
#define NEGATIVE_CHARGE	3


class residue
{
public:
	point position;
	unsigned int mode; //(0 = H, 1 = P, 2 = +, 3 -)
		
	residue():position(), mode(0){}
	residue(int a, int b, unsigned int m):position(a, b), mode(m){}
	
	~residue(){}
	
};


	
class basicResidueArray
{
public:

	residue* res;//[sizeOfResidueArray + 1];
	int sizeOfResidueArray;
	
//Private functions:
	point getDirection(int index1, int index2);
	
	int left_x;
	int right_x;
	int buttom_y;
	int top_y;

	
public:	
	basicResidueArray(){};
	basicResidueArray(int length);
	~basicResidueArray();
	
//TODO: Write copy CTOR and asignment operator	

//application functions: 

	//modifies only the edge = tail of the array
	virtual int tailRotateLeft(int pivot);//0
	virtual int tailRotateRight(int pivot);//1
	virtual int tailRotate180(int pivot);//2
	
	//rotate from the residue after the pivot until the edge
	virtual int fixedRotateLeft(int pivot);//3
	virtual int fixedRotateRight(int pivot);//4
	virtual int fixedRotate180(int pivot);//5
	
	virtual int flipflopCorner(int pivot);//6	//cannot be a tail or a strait line, must be a corner
	
	virtual int nonEdgeSegmentFold(int pivot, int segmentLen);
	
//User functions:

	int printProtein();
	

		
};

class residueArray: public basicResidueArray
{
public:
	
	FILE* fs;
	char fileName[1024];
	char fileMode;
	double numberOfStructures;
	
	residueArray(){}
	residueArray(int length);
	void new_residueArray(int size);
	point getMax_XY();
	point getMin_XY();
	
	/* Association with file */
	residueArray(char *name);
	residueArray(int, char *name);
	residueArray& operator=(const residueArray& rightside);
	residueArray& operator=(const point* rightside);
	residueArray& operator=(const int* rightside);

	
	~residueArray();
	
	int read();
	int write();
	void print();
	
};

#endif
