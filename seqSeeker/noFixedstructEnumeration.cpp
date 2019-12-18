//structEnumeration.cpp
#include "../simulator/point.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std; 

#define ENUM_ARR_SIZE 4
#define DB_FILE_OUTPUT 1

int sideA = 0, sideB = 0;
int enumArrSize = 0;
int enumArrMatrixSize = 0;
double counter = 0;
int** enumMatrix;//[ENUM_ARR_SIZE*2 + 1][ENUM_ARR_SIZE*2 + 1] = {{0}};
point tmppoint;

#define ASSERTP(N)	( ((N.x) < sideA) && ((N.y) < sideB))
#define ASSERT(N)	( ((N) >= 0) && ((N) < enumArrMatrixSize) )

point get_dx_dy(point *parr, int maxsize, int minsize)
{
	point pdxdy;
	/*
	pdxdy.x = max(x) - min(x)
	pdxdy.y = max(y) - min(y)
	*/
	
	int minX, minY;
	int maxX, maxY;
	minX = maxX = parr[maxsize - 1].x;
	minY = maxY = parr[maxsize - 1].y;
	
	for(int i = maxsize - 2; i >= minsize; i--)
	{
		if(minX > parr[i].x)
			minX = parr[i].x;
		if(maxX < parr[i].x)
			maxX = parr[i].x;
			
		if(minY > parr[i].y)
			minY = parr[i].y;
		if(maxY < parr[i].y)
			maxY = parr[i].y;
	}

	pdxdy.x = maxX - minX;
	pdxdy.y = maxY - minY;
	
	return pdxdy;
	
}

std::ostream& operator<<(std::ostream &out, point p)
{
	
	out<<"("<<p.x<<", "<<p.y<<")";
	return out;
}

void printStruct(point *parr, int len)
{
	int **enumMatrix2 = new int*[enumArrMatrixSize];

	for(int i = 0; i < enumArrMatrixSize; i++)
	{
		enumMatrix2[i] = new int[enumArrMatrixSize];
		for(int j = 0; j < enumArrMatrixSize; j++)
			enumMatrix2[i][j] = -1;
	}
	
	for(int i = 0; i < len; i++)
		enumMatrix2[parr[i].y][parr[i].x] = i;
	
	for(int i = (enumArrMatrixSize - 1); i >= 0 ; i--)
	{
		for(int j = 0; j < enumArrMatrixSize; j++)
			if(enumMatrix2[i][j] == -1)
				cout<<"  ";
			else if(enumMatrix2[i][j] > 9)
				cout<<enumMatrix2[i][j];
			else
				cout<<" "<<enumMatrix2[i][j];
		cout<<endl;
	}
	cout<<endl;
	
	
		
}
	
int enumeratePoints(point* parr, int x, int y, int len, FILE* fp)
{
	//cout<<"Entering func.\n";

	tmppoint = get_dx_dy(parr, enumArrSize, len);
	if(!ASSERTP(tmppoint))
		return 1;

	if(len == 0)
	{	
		counter++;
#if DB_FILE_OUTPUT
		for(int i = 0; i < enumArrSize; i++)
		{
			fwrite(&parr[i].x, sizeof(int), 1, fp);
			fwrite(&parr[i].y, sizeof(int), 1, fp);
			//cout<<parr[i]<<", ";			
		}
		//cout<<endl;
#endif
		
#if 0		
	printStruct(parr, enumArrSize);
#endif
		return 1;
	}
	

	//Regards only the first point
	//When first point is at (0, 0):
	//and second point
	if(!enumMatrix[y][x])
	{			
		parr[len - 1].x = x;
		parr[len - 1].y = y;
		enumMatrix[y][x] = 1;	
		len--;
		
		
		while(len > 0)
		{
			parr[len - 1].x = ++x;
			parr[len - 1].y = y;
			enumMatrix[y][x] = 1;
			len--;
			
			if(len > 0)
			{
				parr[len - 1].x = x;
				parr[len - 1].y = ++y;
				enumMatrix[y][x] = 1;
				enumeratePoints(parr, x, y, len - 1, fp);
				enumMatrix[y][x] = 0;
				--y;
			}
			else
				enumeratePoints(parr, x, y, len, fp);
			
		}
		return 1;
	}
		
	//UP:
	
	y++;
	//cout<<y<<", ";
	if(ASSERT(y))
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			
			parr[len - 1].x = x;
			parr[len - 1].y = y;
			enumeratePoints(parr, x, y, len - 1, fp);
			
			enumMatrix[y][x] = 0;
		}
	y--;
	
		//DOWN:
		y--;
		//cout<<y<<", ";
	if(ASSERT(y))
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			parr[len - 1].x = x;
			parr[len - 1].y = y;
			enumeratePoints(parr, x, y, len - 1, fp);
			enumMatrix[y][x] = 0;
		}
		y++;
		
		//LEFT:
		x--;
		//cout<<x<<", ";
	if(ASSERT(x))
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			parr[len - 1].x = x;
			parr[len - 1].y = y;
			enumeratePoints(parr, x, y, len - 1, fp);
			enumMatrix[y][x] = 0;
		}
		x++;
		
		//RIGHT:		
		x++;
		//cout<<x<<", ";
	if(ASSERT(x))
		if(!enumMatrix[y][x])
		{
			enumMatrix[y][x] = 1;	
			parr[len - 1].x = x;
			parr[len - 1].y = y;
			enumeratePoints(parr, x, y, len - 1, fp);
			enumMatrix[y][x] = 0;
		}
		x--;
				
	return 1;
}


int main(int argc, char**argv)
{
	if(argc < 5)
	{
		cout<<"chain_length addA addB outputfile\n";
		exit(0);
	}
	cout<<"Start enumeration: \n";
	enumArrSize = atoi(argv[1]);
	
	sideA = (int) sqrt((double)enumArrSize) + atoi(argv[2]);
	sideB = (int) sqrt((double)enumArrSize) + atoi(argv[3]);
	char *name = argv[4];
	
	if(sideA > enumArrSize)
	{
		cout<<"error add input: "<<sideA<<"\n";
		exit(0);
	}
	 
	enumArrMatrixSize = enumArrSize*2;
	cout<<"Matrix size: "<<enumArrMatrixSize<<endl;
	
	enumMatrix = new int*[enumArrMatrixSize];

	for(int i = 0; i < enumArrMatrixSize; i++)
	{
		enumMatrix[i] = new int[enumArrMatrixSize];
		for(int j = 0; j < enumArrMatrixSize; j++)
			enumMatrix[i][j] = 0;
	}
	
	
	
	cout<<"sideA: "<<sideA<<", sideB: "<<sideB<<endl;
	
	 
	// = {0};
	//name = 
	//char str[30] = "-mer-struct-enum-mod-n";
	int len = enumArrSize;
	FILE* fp;
	
#if DB_FILE_OUTPUT	
	//sprintf(name, "./DB/%d-(%d)%s", len, sideA, str);
	
	
	fp = fopen(name, "wb");
	
	if(!fp)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
	
	fwrite(&len, sizeof(int), 1, fp);
	fseek(fp, sizeof(double), SEEK_CUR);
#endif	
	point* parr = new point[enumArrSize];
	
	int x = enumArrSize, y = enumArrSize;
	cout<<"gettillhere\n";
	
	enumeratePoints(parr, x, y, len, fp);
#if DB_FILE_OUTPUT
	fseek(fp, sizeof(int), SEEK_SET);
	fwrite(&counter, sizeof(double), 1, fp);
	fclose(fp);

	cout<<"Created file name: "<<name<<endl;
#endif
	cout<<"Counter of "<<len<<" 2D combinations: "<<counter<<endl;
	
		
}

