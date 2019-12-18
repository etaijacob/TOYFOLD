//dynamicLibEnum.cpp

#include "dynamicLibEnum.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

double counter = 0;
int enumMatrix[ENUM_ARR_SIZE*2 + 1][ENUM_ARR_SIZE*2 + 1] = {{0}};

int enumeratePoints(point* parr, dresGroup* dgrp, int x, int y, int len, int** matrix)
{
	//cout<<"Entering func.\n";
	if(len == 0)
	{	
		counter++;
		//cout<<point(x, y)<<endl;
		//cout<<"dprg: "<<dgrp->pMM[y][x]<<endl;
		
		for(int i = 0, j = dgrp->pMM[y][x]->numOfPoints - 1;
				i < dgrp->pMM[y][x]->numOfPoints;
				i++, j--)
		{
			dgrp->pMM[y][x]->pmatrix[matrix[y][x]][i].x = parr[j].x - ENUM_ARR_SIZE; 
			dgrp->pMM[y][x]->pmatrix[matrix[y][x]][i].y = parr[j].y - ENUM_ARR_SIZE; 
			//cout<<dgrp->pMM[y][x]->pmatrix[matrix[y][x]][i]<<", ";
			
		}
		//cout<<endl;
		matrix[y][x]++;
		/*
		for(int i = (ENUM_ARR_SIZE*2); i >= 0 ; i--)
		{
			for(int j = 0; j <= (ENUM_ARR_SIZE*2); j++)
				if(enumMatrix[i][j] == 0)
					cout<<" ";
				else
					cout<<"#";
			cout<<endl;
		}
		*/
		return 1;
	}
	
	//UP:
	
		y++;
		//if position is not occupied:
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			//dirCntArr[1]++;
			
			parr[len - 1].x = x;
			parr[len - 1].y = y;
			enumeratePoints(parr, dgrp, x, y, len - 1, matrix);
			//dirCntArr[1]--;
			enumMatrix[y][x] = 0;
		}
		y--;
	
		//DOWN:
		y--;
		//if position is not occupied:
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			parr[len - 1].x = x;
			parr[len - 1].y = y;
			enumeratePoints(parr, dgrp, x, y, len - 1, matrix);
			enumMatrix[y][x] = 0;
		}
		y++;
		
		//LEFT:
		x--;
		//if position is not occupied:
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			parr[len - 1].x = x;
			parr[len - 1].y = y;
			enumeratePoints(parr, dgrp, x, y, len - 1, matrix);
			enumMatrix[y][x] = 0;
		}
		x++;
		
		//RIGHT:		
		x++;
		//if position is not occupied:
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			parr[len - 1].x = x;
			parr[len - 1].y = y;
			enumeratePoints(parr, dgrp, x, y, len - 1, matrix);
			enumMatrix[y][x] = 0;
		}
		x--;
				
	return 1;
}

int enumerate(char* enumArr, int x, int y, int len, int** matrix)
{
	
	if(len == 0)
	{	
		counter++;
		matrix[y][x]++;
		/*
		for(int i = (ENUM_ARR_SIZE*2); i >= 0 ; i--)
		{
			for(int j = 0; j <= (ENUM_ARR_SIZE*2); j++)
				if(enumMatrix[i][j] == 0)
					cout<<" ";
				else
					cout<<"#";
			cout<<endl;
		}
		*/
		return 1;
	}
	
	//UP:
	
		y++;
		//if position is not occupied:
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			//dirCntArr[1]++;
			enumArr[len - 1] = D_UP;
			enumerate(enumArr, x, y, len - 1, matrix);
			//dirCntArr[1]--;
			enumMatrix[y][x] = 0;
		}
		y--;
	
		//DOWN:
		y--;
		//if position is not occupied:
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			enumArr[len - 1] = D_DOWN;
			enumerate(enumArr, x, y, len - 1, matrix);
			enumMatrix[y][x] = 0;
		}
		y++;
		
		//LEFT:
		x--;
		//if position is not occupied:
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			enumArr[len - 1] = D_LEFT;
			enumerate(enumArr, x, y, len - 1, matrix);
			enumMatrix[y][x] = 0;
		}
		x++;
		
		//RIGHT:		
		x++;
		//if position is not occupied:
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			enumArr[len - 1] = D_RIGHT;
			enumerate(enumArr, x, y, len - 1, matrix);
			enumMatrix[y][x] = 0;
		}
		x--;
				
	return 1;
}




pointMatrix::pointMatrix(int in_numOfPossibilities, int in_numOfPoints)
{
	numOfPossibilities = in_numOfPossibilities;
	numOfPoints = in_numOfPoints;
	
	pmatrix = new point*[numOfPossibilities];
	if(!pmatrix)
	{
		cout<<"\nERROR MOMORY ALLOC - pointMatrix\n";
		exit(1);
	}
	for(int i = 0; i < numOfPossibilities; i++)
	{
		pmatrix[i] = new point[numOfPoints];
		if(!pmatrix[i])
		{
			cout<<"\nERROR MOMORY ALLOC - pointMatrix\n";
			exit(1);
		}
	}
}

void pointMatrix::printMatrix()
{
	for(int i = 0; i < numOfPossibilities; i++)
	{
		for(int j = 0; j < numOfPoints; j++)
			cout<<pmatrix[i][j].x<<", "<<pmatrix[i][j].y<<" ";
		cout<<endl;
	}
}

void pointMatrix::fillMatrix()
{
	for(int i = 0; i < numOfPossibilities; i++)
	{
		for(int j = 0; j < numOfPoints; j++)
		{
			pmatrix[i][j].x = 1;
			pmatrix[i][j].y = 2;
		}
	}
}

pointMatrix::~pointMatrix()
{
	for(int i = 0; i < numOfPossibilities; i++)
		delete []pmatrix[i];
	delete []pmatrix;

}

dresGroup::dresGroup()
{
	//cout<<"Entering dresGroup ctor\n";
	for(int i = 0; i <= MAX_ENUM_LEN*2; i++)
		for(int j = 0; j <= MAX_ENUM_LEN*2; j++)
			pMM[i][j] = NULL;
	
}

dresGroup::~dresGroup()
{
	for(int i = 0; i <= MAX_ENUM_LEN*2; i++)
		for(int j = 0; j <= MAX_ENUM_LEN*2; j++)
			if(!pMM[i][j])
				delete pMM[i][j];
				
}

//input x and y are the original MAX_ENUM_LEN <= (dx, dy)  <= MAX_ENUM_LEN
int dresGroup::addMemeber(int x, int y, pointMatrix* pm)
{
	if( (x > MAX_ENUM_LEN*2) || (x < 0) ||
	    (y > MAX_ENUM_LEN*2) || (y < 0) || 
	    (pm == NULL ) )
		return 0;
	
	if(!pMM[y][x])
		pMM[y][x] = pm;
	else
		return 0;
		

	return 1;
} 

//Counts the number of posibilities for each fixed (dx, dy) with perticular dres
int dresGroup::countSubGroups(int dres)
{
	//initiation:
	//-----------
	if(dres > MAX_ENUM_ARRAY_LEN)
		return 0;
	
	int** matrix;
	
	matrix = new int*[MAX_ENUM_LEN*2 + 1];
	
	if(!matrix)
	{
		cout<<"ERROR ALLOC\n";
		exit(1);
	}
	
	for(int i = 0; i < MAX_ENUM_LEN*2 + 1; i++)
	{
		matrix[i] = new int[MAX_ENUM_LEN*2 + 1];
		if(!matrix[i])
		{
			cout<<"ERROR ALLOC\n";
			exit(1);
		}
		for(int j = 0; j < MAX_ENUM_LEN*2 + 1; j++)
			matrix[i][j] = 0;
	}
		
	//Enumeration:
	//------------
	
	char enumArr[ENUM_ARR_SIZE + 1];

	int x = ENUM_ARR_SIZE, y = ENUM_ARR_SIZE;
	
	enumArr[ENUM_ARR_SIZE] = 0;
	enumMatrix[y][x] = 1;
	enumerate(enumArr, x, y, dres - 1, matrix);
	
	//PRINTING MATRIX:
	int matrixSum = 0;
	for(int i = (MAX_ENUM_LEN*2); i >= 0 ; i--)
	{
		for(int j = 0; j <= (MAX_ENUM_LEN*2); j++)
#ifdef PRINTING_MATRIX
			if(matrix[i][j] == 0)
				cout<<"  ";
			else
			{
#else
			if(matrix[i][j] != 0)
			{
#endif
				matrixSum += matrix[i][j];
#ifdef PRINTING_MATRIX				
				if(matrix[i][j] > 9)		
					cout<<matrix[i][j];
				else
					cout<<" "<<matrix[i][j];
#endif
			}
#ifdef PRINTING_MATRIX
		cout<<endl;
#endif
	}
	//int r = MAX_ENUM_LEN*2;
#ifdef PRINTING_MATRIX
	cout<<"matrixSum: "<<matrixSum<<endl;
#endif
	return 1;
}

int dresGroup::countSubGroups(int dres, int**matrix)
{
	
	if(dres > MAX_ENUM_ARRAY_LEN)
		return 0;
	
	
	//Enumeration:
	//------------
	
	char enumArr[ENUM_ARR_SIZE + 1];

	int x = ENUM_ARR_SIZE, y = ENUM_ARR_SIZE;
	
	enumArr[ENUM_ARR_SIZE] = 0;
	enumMatrix[y][x] = 1;
	enumerate(enumArr, x, y, dres - 1, matrix);
	

	int matrixSum = 0;
	for(int i = (MAX_ENUM_LEN*2); i >= 0 ; i--)
	{
		for(int j = 0; j <= (MAX_ENUM_LEN*2); j++)
#ifdef PRINTING_MATRIX
			if(matrix[i][j] == 0)
				cout<<"  ";
			else
			{
#else
			if(matrix[i][j] != 0)
			{
#endif
				matrixSum += matrix[i][j];
#ifdef PRINTING_MATRIX				
				if(matrix[i][j] > 9)		
					cout<<matrix[i][j];
				else
					cout<<" "<<matrix[i][j];
#endif
			}
#ifdef PRINTING_MATRIX
		cout<<endl;
#endif
	}
	//int r = MAX_ENUM_LEN*2;
#ifdef PRINTING_MATRIX
	cout<<"matrixSum: "<<matrixSum<<endl;
#endif
	return 1;
}


int dresGroup::enumerate_dresGroup(int dres)
{
	//initiation:
	//-----------
	if(dres > MAX_ENUM_ARRAY_LEN)
		return 0;
	
	int** matrix;
	
	matrix = new int*[MAX_ENUM_LEN*2 + 1];
	
	if(!matrix)
	{
		cout<<"ERROR ALLOC\n";
		exit(1);
	}
	
	for(int i = 0; i < MAX_ENUM_LEN*2 + 1; i++)
	{
		matrix[i] = new int[MAX_ENUM_LEN*2 + 1];
		if(!matrix[i])
		{
			cout<<"ERROR ALLOC\n";
			exit(1);
		}
		for(int j = 0; j < MAX_ENUM_LEN*2 + 1; j++)
			matrix[i][j] = 0;
	}
	
	counter = 0;
	countSubGroups(dres, matrix);
	
	
	//Memory allocation:
	//------------------
	for(int y = 0; y < MAX_ENUM_LEN*2 + 1; y++)
		for(int x = 0; x < MAX_ENUM_LEN*2 + 1; x++)
			if(matrix[y][x] > 0)
			{
				if(addMemeber(x, y, new pointMatrix(matrix[y][x], dres - 1)) == 0)
				{
					cout<<"Error adding a member\n";
					exit(1);
				}
				else
				{
					//cout<<"Success in adding: ("<<x<<", "<<y<<") with: "<<matrix[y][x]<<"\n";
					//cout<<"pMM: "<<pMM[y][x]<<endl;
				}
			}
	
	//initiation:
	//-----------
	counter = 0;
	int x = ENUM_ARR_SIZE, y = ENUM_ARR_SIZE;
	point parr[ENUM_ARR_SIZE];
	
	for(int i = 0; i < MAX_ENUM_LEN*2 + 1; i++)
		for(int j = 0; j < MAX_ENUM_LEN*2 + 1; j++)
			matrix[i][j] = 0;
	//cout<<"TILL HERE!!!!\n";
	enumeratePoints(parr, this, x, y, dres - 1, matrix);	
		
	for(int i = 0; i <	MAX_ENUM_LEN*2 + 1; i++)
		delete []matrix[i];
	delete []matrix;
	
	return 1;
}


int enumLibrary::enumerateDBLIB()
{
// 	cout<<"Enumerated dres: ";
	for(int i = 3; i <= MAX_DBLIB_ENUMERATION; i++)
		if(dbLib[i].enumerate_dresGroup(i) == 0)
			cout<<"Error enumerateDBLIB\n";
// 		else
// 			cout<<i<<", ";
// 	cout<<"Successfuly\n";
	return 1;
}

enumLibrary::enumLibrary()
{
	numOf_dres = 0;	
	for(int i = 0; i < MAX_DBLIB_ENUMERATION + 1; i++)
		dbLib[i].dres = i;
}

enumLibrary::~enumLibrary()
{
			
}


/*
int main(int argc, char** argv)
{
	cout<<"\nExecuting main dynamicLibEnum.\n"<<endl;
	
	//dresGroup d;
	//int len = atoi(argv[1]);
	//cout<<"Len of chain: "<<len<<endl;
	//if(d.enumerate_dresGroup(len) == 0)
	//		cout<<"Error main exe\n";
	enumLibrary db;
	db.enumerateDBLIB();
*/
	/*
	dresGroup darr[MAX_ENUM_LEN - 2];
	for(int i = 3; i <= len; i++)
		if(darr[i - 3].enumerate_dresGroup(i) == 0)
			cout<<"Error main enumerate_dresGroup\n";
	
	cout<<"counter: "<<counter<<"\n";
	cout<<"counter/4: "<<counter/4<<endl;
	double mul = 4;
	for(int i = 1; i < len; i++)
		mul *=3;
	cout<<"Number of initial posibilities: "<<mul<<endl;
	cout<<"fraction: "<<counter/mul<<endl;
	cout<<"counter/4: "<<counter/mul/4<<endl;
	*//*
	return 0;
}
*/
