//dynamicLibEnum.h

#ifndef DYNAMICLIBENUM_HEADER
#define DYNAMICLIBENUM_HEADER

#include <iostream>

#define MAX_ENUM_LEN			20
#define MAX_ENUM_ARRAY_LEN 		MAX_ENUM_LEN
#define ENUM_ARR_SIZE			MAX_ENUM_LEN

#define D_UP					'1'
#define D_DOWN		 			'2'
#define D_LEFT		 			'3'
#define D_RIGHT	 				'4'
	
#define MAX_DBLIB_ENUMERATION	14

#include "point.h"


class pointMatrix
{
public:

	point** pmatrix;
	int numOfPossibilities;
	int numOfPoints;
	

	pointMatrix(int numOfPossibilities, int numOfPoints);
	~pointMatrix();
	
	void printMatrix();
	void fillMatrix();
};

class dresGroup
{
public:
	pointMatrix* pMM[MAX_ENUM_LEN*2 + 1][MAX_ENUM_LEN*2 + 1];
	int dres;
	
	dresGroup();
	~dresGroup();
	
	int addMemeber(int x, int y, pointMatrix* pm);
	int countSubGroups(int dres);
	int countSubGroups(int dres, int**matrix);
	int enumerate_dresGroup(int dres);
	
	
};

class enumLibrary
{
public:
	dresGroup dbLib[MAX_ENUM_LEN];
	int numOf_dres;
	
	enumLibrary();
	~enumLibrary();
	
	int enumerateDBLIB();
	
	int getNumberOfPossibilities(int dres_in, point dp)
	{
		if( (dres_in < 3)||(dres_in > MAX_DBLIB_ENUMERATION) )
		{
			//cout<<"dres_in:"<<dres_in<<endl;
			return 0;
		}
		/*
		cout<<dp<<endl;
		for(int i = 0; i < MAX_ENUM_LEN*2 + 1; i++)
			for(int j = 0; j < MAX_ENUM_LEN*2 + 1; j++)
				if(dbLib[dres_in].pMM[i][j])
					cout<<"pMM is: "<<j<<", "<<i<<"\n";
		*/
		//dbLib[dres_in].pMM[dp.y][dp.x]
		if(dbLib[dres_in].pMM[dp.y][dp.x])
		{
			//cout<<"dbLib:num of pos: "<<dbLib[dres_in].pMM[dp.y][dp.x]->numOfPossibilities<<endl;
			return dbLib[dres_in].pMM[dp.y][dp.x]->numOfPossibilities;
		}
		return 0;
	
	}

	point* getPointsOfConformation(int dres_in, point dp, int position)
	{
		if( (dres_in < 3)||(dres_in > MAX_DBLIB_ENUMERATION) )
			return NULL;

		if(dbLib[dres_in].pMM[dp.y][dp.x])	
			return dbLib[dres_in].pMM[dp.y][dp.x]->pmatrix[position];
		return NULL;
	
	}
	
};

#endif //DYNAMICLIBENUM_HEADER
