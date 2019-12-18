//utilities.cpp


#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <libgen.h>
#include <fstream>
#include <ctype.h>
#include "utilities.h"

using namespace std;

//from 1 to chainLength+1
PWD::PWD(int chainLength)
{
// 	cout<<"pwd::ctor "<<chainLength<<endl;
	if(chainLength < 3)
	{
		cout<<"PWD - chainLength error\n";
		exit(0);
	}

	N = ++chainLength;
	
	length = countPairCombinations();
			
	if(length < 1)
	{
		cout<<"PWD - Error countPairCombinations\n";
		exit(0);
	}
	
	pairDistanceArray = new double/*int*/[length];
	if(!pairDistanceArray)
	{
		cout<<"PWD - Error mem alloc\n";
		exit(1);
	}
	
}	
	
PWD::~PWD()
{
// 	cout<<"dtor PWD"<<endl;
	delete []pairDistanceArray;
}

unsigned long PWD::countPairCombinations()
{
	/*
	We avoid repetition because we have 
	a simetric matrix of combinations.
	*/
	unsigned long cnt = 0;
	
	for(int x = 1; x < N; x++)
		for(int y = x + 2; y < N; y++) 		
					cnt++;
		
	return cnt;
}



double PWD::compute(residueArray *resArr)
{
	int m = 0;
	
	for(int i = 1; i < N; i++)
	{
		for(int j = i + 2; j < N; j++, m++) 
		{
			/*
			pairDistanceArray[m] = 
					
				ABS(resArr->res[i].position.x - resArr->res[j].position.x) +
				ABS(resArr->res[i].position.y - resArr->res[j].position.y);
*/
			pairDistanceArray[m] = sqrt((double)
				((resArr->res[i].position.x - resArr->res[j].position.x)*
				 (resArr->res[i].position.x - resArr->res[j].position.x) +
			     (resArr->res[i].position.y - resArr->res[j].position.y)*
				 (resArr->res[i].position.y - resArr->res[j].position.y)) );

#if PRINT_DEBUG
			if(m%2 == 0)
					cout<<endl;
			cout<<"("<<i<<" ,"<<j<<"): ";
			cout<<resArr->res[i].position<<", ";
			cout<<resArr->res[j].position<<", ";
			
			cout<<pairDistanceArray[m]<<", ";
#endif		
		}
	}
	return 1;
}	

double CO(int N, point *pArr)
{
	double co = 0;
	int cnt = 0;

	for(int i = 1; i <= N - 2; i++)
	{
		for(int j = i + 2; j <= N; j++) 
		{
			if(pArr[i].x - pArr[j].x == 0) 
				if(pArr[i].y - pArr[j].y == 1 || pArr[i].y - pArr[j].y == -1) {
					co += (j - i);
					cnt++;
				}
			else if(pArr[i].y - pArr[j].y == 0) 
				if(pArr[i].x - pArr[j].x == 1 || pArr[i].x - pArr[j].x == -1) {
					co += (j - i);
					cnt++;
				}
		}
	}
	if(cnt == 0)
		return -1;
	return co/cnt;
}

double PWD::compute(point *pArr)
{
	int m = 0;
// 	cout<<"pwd::compute point "<<N<<endl;
	for(int i = 1; i < N; i++)
	{
		for(int j = i + 2; j < N; j++, m++) 
		{
			//cout<<j<<" "<<N<<endl;
			pairDistanceArray[m] = sqrt((double)
				((pArr[i].x - pArr[j].x)*(pArr[i].x - pArr[j].x) +
			     (pArr[i].y - pArr[j].y)*(pArr[i].y - pArr[j].y)) );
					
				//ABS(pArr[i].x - pArr[j].x) +
				//ABS(pArr[i].y - pArr[j].y);
		}
	}
	return 1;
}

	
//---------------------------------------------------------------------------------------------------

PWDA::PWDA(int chainLength):PWD(chainLength)
{

}




double PWDA::compute(residueArray *resArr)
{
	double acc = 0;
	for(int i = 1; i < N; i++)
		for(int j = i + 2; j < N; j++) 
		{
			acc += 
				ABS(resArr->res[i].position.x - resArr->res[j].position.x) +
				ABS(resArr->res[i].position.y - resArr->res[j].position.y);
		}
	
	return (acc/(double)length);
	
}

	
//---------------------------------------------------------------------------------------------------

PWD_XY::PWD_XY(int chainLength)
{
	if(chainLength < 3)
	{
		cout<<"PWD - chainLength error\n";
		exit(0);
	}

	N = ++chainLength;
	
	length = countPairCombinations();
			
	if(length < 1)
	{
		cout<<"PWD - Error countPairCombinations\n";
		exit(0);
	}
	
	pairDistanceArrayX = new int[length];
	pairDistanceArrayY = new int[length];
	
	if( (!pairDistanceArrayX)||(!pairDistanceArrayY) )
	{
		cout<<"PWD_XY - Error mem alloc\n";
		exit(1);
	}
	
}	
	
PWD_XY::~PWD_XY()
{
	delete []pairDistanceArrayX;
	delete []pairDistanceArrayY;
}

unsigned long PWD_XY::countPairCombinations()
{
	/*
	We avoid repetition because we have 
	a simetric matrix of combinations.
	*/
	unsigned long cnt = 0;
	
	for(int x = 1; x < N; x++)
		for(int y = x + 2; y < N; y++) 		
					cnt++;
		
	return cnt;
}



void PWD_XY::compute(residueArray *resArr)
{
	int m = 0;
	
	for(int i = 1; i < N; i++)
	{
		for(int j = i + 2; j < N; j++, m++) 
		{
			pairDistanceArrayX[m] = 
				ABS(resArr->res[i].position.x - resArr->res[j].position.x);
				
			pairDistanceArrayY[m] = 
				ABS(resArr->res[i].position.y - resArr->res[j].position.y);
#if PRINT_DEBUG
			if(m%2 == 0)
					cout<<endl;
			cout<<"("<<i<<" ,"<<j<<"): ";
			cout<<resArr->res[i].position<<", ";
			cout<<resArr->res[j].position<<", ";
			
			cout<<pairDistanceArray[m]<<", ";
#endif		
		}
	}
}	

//---------------------------------------------------------------------------------------------------

RMSD::RMSD(residueArray* resArr, int chainLength, int maxStructures):src(chainLength)
{
	N = chainLength + 1;
// 	cout<<"RMSD ctor 1"<<endl;
	src.compute(resArr);
	
	
	this->maxStructures = maxStructures;
	if(maxStructures == 0)
		return;
	
	structures = new point*[maxStructures];
	if(!structures)
	{
		cout<<"ERROR - mem alloc rmsd ctor\n";
		exit(1);
	}
				
	for(int i = 0; i < maxStructures; i++)
		if(!(structures[i] = new point[N]))
		{
			cout<<"ERROR - mem alloc rmsd ctor\n";
			exit(1);
		}
		
	rmsdResults = new double*[maxStructures];
	if(!rmsdResults)
	{
		cout<<"ERROR mem alloc - rmsd ctor\n";
		exit(1);
	}

	for(int i = 0; i < maxStructures; i++)
		if(!(rmsdResults[i] = new double[maxStructures]))
		{
			cout<<"ERROR mem alloc - rmsd ctor\n";
			exit(1);
		}	
}	

RMSD::RMSD(point* pArr, int chainLength, int maxStructures):src(chainLength)
{
	N = chainLength + 1;
// 	cout<<"RMSD ctor 1"<<endl;
	src.compute(pArr);
	
	
	this->maxStructures = maxStructures;
	if(maxStructures == 0)
		return;
	
	structures = new point*[maxStructures];
	if(!structures)
	{
		cout<<"ERROR - mem alloc rmsd ctor\n";
		exit(1);
	}
				
	for(int i = 0; i < maxStructures; i++)
		if(!(structures[i] = new point[N]))
		{
			cout<<"ERROR - mem alloc rmsd ctor\n";
			exit(1);
		}
		
	rmsdResults = new double*[maxStructures];
	if(!rmsdResults)
	{
		cout<<"ERROR mem alloc - rmsd ctor\n";
		exit(1);
	}

	for(int i = 0; i < maxStructures; i++)
		if(!(rmsdResults[i] = new double[maxStructures]))
		{
			cout<<"ERROR mem alloc - rmsd ctor\n";
			exit(1);
		}	
}	

int RMSD::update(residueArray* resArr)
{
	src.compute(resArr);
	return 1;
}

int RMSD::update(point* pArr)
{
	src.compute(pArr);
	return 1;
}

	
RMSD::~RMSD()
{
	for(int i = 0; i < maxStructures; i++)
	{
		delete []structures[i];
		delete []rmsdResults[i];
	}
	if(maxStructures > 0)
	{
		delete []structures;
		delete []rmsdResults;
	}
	
// 	cout<<"finish dtor RMSD "<<maxStructures<<endl;
	
}

/*
Root Mean Square Distance computation:
output = square of the sum of all pairs that ( (|dx1| + |dy1|) - (|dx2| + |dy2|) )^2
*/
double RMSD::compute(residueArray& resArr)
{
	double acc = 0;
	int m = 0;
	
	pairsDiffCtr = 0;
	//cout<<"rmsd here"<<endl;
	for(int i = 1; i < N; i++)
		for(int j = i + 2; j < N; j++, m++) 
		{
			/*
			double d = ABS(resArr.res[i].position.x - resArr.res[j].position.x) +
					   ABS(resArr.res[i].position.y - resArr.res[j].position.y) - 
					   src.pairDistanceArray[m];
			*/
			double d = sqrt((double)
				       (resArr.res[i].position.x - resArr.res[j].position.x)*
					   (resArr.res[i].position.x - resArr.res[j].position.x) +
					   (resArr.res[i].position.y - resArr.res[j].position.y)*
					   (resArr.res[i].position.y - resArr.res[j].position.y) ) - 
					   src.pairDistanceArray[m];
					
			if(d != 0)
				pairsDiffCtr++;
			
			acc += d*d;
		}
			
					
	
	return sqrt( (acc/(double)src.length) );

	
}

double RMSD::computeNativePairDiff(residueArray& resArr)
{
	double acc = 0;
	int m = 0;
	
	pairsDiffCtr = 0;
	//cout<<"rmsd here"<<endl;
	for(int i = 1; i < N; i++)
		for(int j = i + 2; j < N; j++, m++) 
		{
			/*
			double d = ABS(resArr.res[i].position.x - resArr.res[j].position.x) +
					   ABS(resArr.res[i].position.y - resArr.res[j].position.y) - 
					   src.pairDistanceArray[m];
			*/
			double d = sqrt((double)
				       (resArr.res[i].position.x - resArr.res[j].position.x)*
					   (resArr.res[i].position.x - resArr.res[j].position.x) +
					   (resArr.res[i].position.y - resArr.res[j].position.y)*
					   (resArr.res[i].position.y - resArr.res[j].position.y) ) - 
					   src.pairDistanceArray[m];
					
			if(d != 0)
				pairsDiffCtr++;
			
			acc += d*d;
		}
			
					
	
	return pairsDiffCtr;

	
}



double RMSD::compute(point* pArr)
{
	double acc = 0;
	int m = 0;
	
	pairsDiffCtr = 0;
	
	for(int i = 1; i < N; i++)
		for(int j = i + 2; j < N; j++, m++) 
		{
			/*
			double d = ABS(pArr[i].x - pArr[j].x) +
					   ABS(pArr[i].y - pArr[j].y) - 
					   src.pairDistanceArray[m];
			*/
			double d = sqrt((double)
					   (pArr[i].x - pArr[j].x)*(pArr[i].x - pArr[j].x)+
					   (pArr[i].y - pArr[j].y)*(pArr[i].y - pArr[j].y) ) - 
					   src.pairDistanceArray[m];

			if(d != 0)
				pairsDiffCtr++;
			
			acc += d*d;
		}
			
					
	
	return sqrt( (acc/(double)src.length) );

	
}

double RMSD::dimer_compute(residueArray& resArr, int from1, int to1, int from2, int to2)
{
	double acc = 0;
	int m = 0;
	
	pairsDiffCtr = 0;
	
	for(int i = 1; i < N; i++)
		for(int j = i + 2; j < N; j++, m++) 
		{
			/*
			double d = ABS(resArr.res[i].position.x - resArr.res[j].position.x) +
					   ABS(resArr.res[i].position.y - resArr.res[j].position.y) - 
					   src.pairDistanceArray[m];
			*/
			if( (i >= from1 && j >= from1 && i < to1 && j < to1) ||
				(i >= from2 && j >= from2 && i < to2 && j < to2) )
			{
				double d = sqrt((double)
				       (resArr.res[i].position.x - resArr.res[j].position.x)*
					   (resArr.res[i].position.x - resArr.res[j].position.x) +
					   (resArr.res[i].position.y - resArr.res[j].position.y)*
					   (resArr.res[i].position.y - resArr.res[j].position.y) ) - 
					   src.pairDistanceArray[m];
					
				if(d != 0)
					pairsDiffCtr++;
			
				acc += d*d;
			}
		}
			
					
	
	return sqrt( (acc/(double)src.length) );

	
}
//0, 1 - global, 2, 3 - monomer A, 4, 5 - monomer B
double RMSD::dimer_compute(point* pArr, int from1, int to1, int from2, int to2, double *ddd)
{
	double acc = 0, acc1 = 0, acc2 = 0;
	int m = 0;
	double pairsDiffCtr1 = 0, pairsDiffCtr2 = 0, acctotal1 = 0, acctotal2 = 0;
	pairsDiffCtr = 0;
	
	for(int i = 1; i < N; i++)
		for(int j = i + 2; j < N; j++, m++) 
		{
			if(i >= from1 && j >= from1 && i < to1 && j < to1)		
			{
				double d = sqrt((double)
						   (pArr[i].x - pArr[j].x)*(pArr[i].x - pArr[j].x)+
						   (pArr[i].y - pArr[j].y)*(pArr[i].y - pArr[j].y) ) - 
					   		src.pairDistanceArray[m];

				if(d != 0)
					pairsDiffCtr1++;
				acctotal1++;
				acc1 += d*d;
			}
			if(i >= from2 && j >= from2 && i < to2 && j < to2)
			{
				double d = sqrt((double)
						   (pArr[i].x - pArr[j].x)*(pArr[i].x - pArr[j].x)+
						   (pArr[i].y - pArr[j].y)*(pArr[i].y - pArr[j].y) ) - 
					   		src.pairDistanceArray[m];

				if(d != 0)
					pairsDiffCtr2++;
				acctotal2++;
				acc2 += d*d;
				
			}	
		}
			
	//acc = acc1 + acc2;
	//pairsDiffCtr = pairsDiffCtr1 + pairsDiffCtr2;
	//double acctotal = acctotal1 + acctotal2;
	

	ddd[2] = sqrt(acc1/(double)acctotal1);
	ddd[3] = pairsDiffCtr1/(double)acctotal1;
	
	ddd[4] = sqrt(acc2/(double)acctotal2);
	ddd[5] = pairsDiffCtr2/(double)acctotal2;

	ddd[0] = ddd[2] + ddd[4];
	ddd[1] = ddd[3] + ddd[5];
	

	return ddd[0];
	
}

//0, 1 - global, 2, 3 - monomer A, 4, 5 - monomer B
double RMSD::dimer_compute(residueArray& resArr, int from1, int to1, int from2, int to2, double *ddd)
{
	double acc = 0, acc1 = 0, acc2 = 0;
	int m = 0;
	double pairsDiffCtr1 = 0, pairsDiffCtr2 = 0, acctotal1 = 0, acctotal2 = 0;
	pairsDiffCtr = 0;
	
	for(int i = 1; i < N; i++)
		for(int j = i + 2; j < N; j++, m++) 
		{
			if(i >= from1 && j >= from1 && i < to1 && j < to1)		
			{
				double d = sqrt((double)
				       (resArr.res[i].position.x - resArr.res[j].position.x)*
					   (resArr.res[i].position.x - resArr.res[j].position.x) +
					   (resArr.res[i].position.y - resArr.res[j].position.y)*
					   (resArr.res[i].position.y - resArr.res[j].position.y) ) - 
					   		src.pairDistanceArray[m];

				if(d != 0)
					pairsDiffCtr1++;
				acctotal1++;
				acc1 += d*d;
			}
			if(i >= from2 && j >= from2 && i < to2 && j < to2)
			{
				double d = sqrt((double)
				       (resArr.res[i].position.x - resArr.res[j].position.x)*
					   (resArr.res[i].position.x - resArr.res[j].position.x) +
					   (resArr.res[i].position.y - resArr.res[j].position.y)*
					   (resArr.res[i].position.y - resArr.res[j].position.y) ) - 
					   		src.pairDistanceArray[m];

				if(d != 0)
					pairsDiffCtr2++;
				acctotal2++;
				acc2 += d*d;
				
			}	
		}
			
	//acc = acc1 + acc2;
	//pairsDiffCtr = pairsDiffCtr1 + pairsDiffCtr2;
	//double acctotal = acctotal1 + acctotal2;
	

	ddd[2] = sqrt(acc1/(double)acctotal1);
	ddd[3] = pairsDiffCtr1/(double)acctotal1;
	
	ddd[4] = sqrt(acc2/(double)acctotal2);
	ddd[5] = pairsDiffCtr2/(double)acctotal2;

	ddd[0] = ddd[2] + ddd[4];
	ddd[1] = ddd[3] + ddd[5];
	

	return ddd[0];

	
}

double RMSD::dimer_compute(point* pArr, int from1, int to1, int from2, int to2)
{
	double acc = 0;
	int m = 0;
	
	pairsDiffCtr = 0;
	
	for(int i = 1; i < N; i++)
		for(int j = i + 2; j < N; j++, m++) 
		{
			/*
			double d = ABS(pArr[i].x - pArr[j].x) +
					   ABS(pArr[i].y - pArr[j].y) - 
					   src.pairDistanceArray[m];
			*/
			if( (i >= from1 && j >= from1 && i < to1 && j < to1) ||
				(i >= from2 && j >= from2 && i < to2 && j < to2) )
			{
				double d = sqrt((double)
						   (pArr[i].x - pArr[j].x)*(pArr[i].x - pArr[j].x)+
						   (pArr[i].y - pArr[j].y)*(pArr[i].y - pArr[j].y) ) - 
					   		src.pairDistanceArray[m];

				if(d != 0)
					pairsDiffCtr++;
			
				acc += d*d;
			}
		}
			
					
	
	return sqrt( acc/(double)(to1 - from1 + to2 - from2) );

	
}

void RMSD::pairwiseCompute(char *name, int *structureDBindexs, int size, double *results)
{
	
	FILE* fp = fopen(name, "rb");
	
	if(!fp)
	{
		cout<<"ERROR - file opening. RMSD\n";
		exit(0);
	}
	
	cout<<"\nopened file: "<<name<<" for DB\n";	
	for(int i = 0; i < size; i++)
	{
		fseek(fp, 
			  sizeof(int)+sizeof(double)+sizeof(int)*2*(N - 1)*(structureDBindexs[i]),
		  	  SEEK_SET);
		for(int j = 1; j <= (N - 1); j++)
		{
			if( (fread(&(structures[i][j].x), sizeof(int), 1, fp) != 1)||
				(fread(&(structures[i][j].y), sizeof(int), 1, fp) != 1) )
				{
					cout<<"File Read Error - RMSD\n";
					fclose(fp);
					exit(1);
				}
		}
	}
	fclose(fp);
	pairwiseCompute(size, results);
	
}


void RMSD::pairwiseCompute(int size, double *results, double *pairdiffs)
{
	if(size > maxStructures)
	{
		cout<<"Error - Num of structures exceeds maxStructures value\nExit program.\n";
		exit(0);
	}
	
	int counter = 0;
	double rmsdAccAvg = 0, rmsdAccVar = 0;
	 
	for(int i = 0; i < size; i++)
	{		
		update(structures[i]);
		results[i] = 0;
		if(pairdiffs)
			pairdiffs[i] = 0;
		for(int j = 0; j < size; j++)
		{
				rmsdResults[i][j] = compute(structures[j]);
				//cout<<rmsdResults[i][j]<<endl;
				rmsdAccAvg += rmsdResults[i][j];
				results[i] += rmsdResults[i][j];
				if(pairdiffs)
					pairdiffs[i] += getPairErrorPercent();
				counter++;
		}
		results[i] /= (double)size;
		if(pairdiffs)
			pairdiffs[i] /= (double)size;
	}
	

	rmsdAccAvg /= (double)counter;	
				
	for(int i = 0; i < size; i++)	
		for(int j = 0; j < size; j++)
				rmsdAccVar += pow((rmsdResults[i][j] - rmsdAccAvg), 2);
		
	rmsdAccVar /= (double)counter;
	cout<<"RMSD - avg: "<<rmsdAccAvg<<"var: "<<rmsdAccVar<<endl; 
}	

double RMSD::getPairErrorPercent()
{
// 	return ( (double)pairsDiffCtr/( (double)(/*src.length*/(N - 1))) );
	return ( int( (double)pairsDiffCtr/src.countPairCombinations() * 100) );
}

//--------------------------------------------------------------------------------------------------
RMSD_XY::RMSD_XY(residueArray* resArr, int chainLength):src(chainLength)
{
	N = chainLength + 1;

	src.compute(resArr);
	
}

bool RMSD_XY::compute(residueArray& resArr, double& accX, double& accY)
{
	accX = 0;
	accY = 0;
	
	int m = 0;
	
	for(int i = 1; i < N; i++)
		for(int j = i + 2; j < N; j++, m++) 
		{
			
			double dx = ABS(resArr.res[i].position.x - resArr.res[j].position.x) -
						src.pairDistanceArrayX[m];
			double dy = ABS(resArr.res[i].position.y - resArr.res[j].position.y) -
					    src.pairDistanceArrayY[m];
			
			accX += dx*dx;
			accY += dy*dy;
		}
	accX = sqrt( (accX/(double)src.length) );
	accY = sqrt( (accY/(double)src.length) );
	return true;

	
}
/*
int statistics::compute4file(char* name, FILE* dfp0, FILE* dfp1)
{
	FILE* fp = fopen(name, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found\n";
		exit(0);
	}
	
	char buffer[2][1024];
	double accMean[2] = {0}, accVar[2] = {0};
	double numbers[2][SIZE_OF_NUM_STATISTICS_BUFFER];
	
	int i = 0, n = 0, state = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[state][i++] = ch;
		else if(ch == ' ')
		{
			buffer[state][i] = NULL;
			numbers[state][n] = strtod(buffer[state], NULL);
			accMean[state] += numbers[state][n]; 
			state = 1;
			i = 0;
			
		}
		else
		{
			buffer[state][i] = NULL;
			numbers[state][n] = strtod(buffer[state], NULL);
			accMean[state] += numbers[state][n]; 
			n++;
			state = 0;
			i = 0;
		}
	}		
	
	double mean[2], var[2];
	mean[0] = accMean[0]/(double)n;
	mean[1] = accMean[1]/(double)n;
	
	for(i = 0; i < n; i++)
	{
		accVar[0] += pow(((double)numbers[0][i] - mean[0]), 2);
		accVar[1] += pow(((double)numbers[1][i] - mean[1]), 2);
	}
	
	var[0] = accVar[0]/(double)n;
	var[1] = accVar[1]/(double)n;
	
	cout<<"[file name]"<<name<<endl;
	cout<<"<"<<mean[0]<<" "<<var[0]<<">"<<"<"<<mean[1]<<" "<<var[1]<<">#"<<n<<"\n";
	fprintf(dfp0, "%f %f\n", mean[0], var[0]);
	fprintf(dfp1, "%f %f\n", mean[1], var[1]); 
			
 	fclose(fp);
	
	return 1;
		
}
//statisticX-Y var is double[2] where 0 - mean, 1- variance

int statistics::compute4file(char* name, double *statisticX, double *statisticY)
{
	FILE* fp = fopen(name, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found\n";
		exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize < 10)
	{
		fclose(fp);
		return 0;
	}
	fseek(fp, 0, SEEK_SET);
	
	char buffer[2][1024];
	double accMean[2] = {0}, accVar[2] = {0};
	double numbers[2][SIZE_OF_NUM_STATISTICS_BUFFER];
	
	int i = 0, n = 0, state = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[state][i++] = ch;
		else if(ch == ' ')
		{
			buffer[state][i] = NULL;
			numbers[state][n] = strtod(buffer[state], NULL);
			accMean[state] += numbers[state][n]; 
			state = 1;
			i = 0;
			
		}
		else
		{
			buffer[state][i] = NULL;
			numbers[state][n] = strtod(buffer[state], NULL);
			accMean[state] += numbers[state][n]; 
			n++;
			state = 0;
			i = 0;
		}
	}		
	
	double mean[2], var[2];
	mean[0] = accMean[0]/(double)n;
	mean[1] = accMean[1]/(double)n;
	
	for(i = 0; i < n; i++)
	{
		accVar[0] += pow(((double)numbers[0][i] - mean[0]), 2);
		accVar[1] += pow(((double)numbers[1][i] - mean[1]), 2);
	}
	
	var[0] = accVar[0]/(double)n;
	var[1] = accVar[1]/(double)n;
	
//	cout<<"[file name]"<<name<<endl;
//	cout<<"<"<<mean[0]<<" "<<var[0]<<">"<<"<"<<mean[1]<<" "<<var[1]<<">#"<<n<<"\n";

	statisticX[0] = mean[0];
	statisticX[1] = var[0];
	
	statisticY[0] = mean[1];
	statisticY[1] = var[1];
 	fclose(fp);
	
	return 1;
		
}
	
int statistics::compute4file(int index, char* dirname, char *substr, 
							 double *statisticX, double *statisticY)
{
    DIR* dirp = opendir(dirname);
    if (dirp == NULL) 
	{
    	return 0;
    }
     
	char str[200];
	
	struct direct * dp;  
		
	char idxStr[10];
	sprintf(idxStr, "-%d-", index);

	bool found = false;
	  
	while ((dp = readdir(dirp)) != NULL) 
	{
		
		if( strfind(dp->d_name, ".data") == (dp->d_namlen - 5) &&
			strfind(dp->d_name, substr) != -1 &&
			strfind(dp->d_name, idxStr) != -1 && found == false )
		{
			sprintf(str, "%s%s", dirname, dp->d_name);
			compute4file(str, statisticX, statisticY);
			found = true;	
		}
		
    }
    closedir(dirp);
	if(found)
	    return 1;
	else
		return 0;

}	

int statistics::compute4dir(char* name, char* dstFilePrefix, char* substr)
{
	
    DIR* dirp = opendir(name);
    if (dirp == NULL) 
	{
    	return 0;
    }
     
	char str[200];
	
	struct direct * dp;  
	
	FILE *dfp0, *dfp1;
	
	char tmp[200];
	sprintf(tmp, "%s-%s-X.statistics", dstFilePrefix, substr); 
	cout<<tmp<<endl; 
	dfp0 = fopen(tmp, "wb");
	sprintf(tmp, "%s-%s-Y.statistics", dstFilePrefix, substr);  
	dfp1 = fopen(tmp, "wb");
	
	if((!dfp0) || (!dfp1) )
	{
		cout<<"ERROR CREATION FILE - compute4dir\n";
		exit(0);
	}
	  
	while ((dp = readdir(dirp)) != NULL) 
	{
		
		if( strfind(dp->d_name, ".data") == (dp->d_namlen - 5) &&
			strfind(dp->d_name, substr) != -1 )
		{
			sprintf(str, "%s%s", name, dp->d_name);
			compute4file(str, dfp0, dfp1);	
		}
		
    }
    closedir(dirp);
	fclose(dfp0);
	fclose(dfp1);
	
    return 1;

}	
*/
sortedStack::sortedStack(int sizeOfStack)
{
	if(sizeOfStack < 2)
		return;
	items = new double[sizeOfStack];
	dataIndex = new int[sizeOfStack];

	if( (!items)||(!dataIndex) )
	{
		cout<<"ERROR - memory alloc sortedStack\n";
		exit(1);
	}
	maxSize = sizeOfStack;
	currentSize = 0;
}
//lowest is last (maxSize - 1)
int sortedStack::insert(double value, int dataIndexValue)
{
	if(currentSize == 0)
	{
		items[currentSize] = value;
		dataIndex[currentSize] = dataIndexValue;
		currentSize++;
	}
	else if(currentSize < maxSize)
	{
		for(int i = currentSize - 1; i >=0; i--)
		{
			if(value <= items[i])
			{
				items[i + 1] = value;
				dataIndex[i + 1] = dataIndexValue;
				currentSize++;
				break;
			}
			else
			{
				items[i + 1] = items[i];
				dataIndex[i + 1] = dataIndex[i];
				if(i < 1)
				{
					items[i] = value;
					dataIndex[i] = dataIndexValue;
					currentSize++;
					break;
				}
			}
		}//end for loop
	}
	else
	{
		for(int i = 0; i < maxSize; i++)
		{
			if(value <= items[i])
			{
				if(i > 0)
				{
					items[i - 1] = items[i];
					dataIndex[i - 1] = dataIndex[i];
				}
					
				if(i == (maxSize - 1))
				{
					items[i] = value;
					dataIndex[i] = dataIndexValue;
					break;
				}
			}
			else
			{
				if(i == 0)
					break;
				items[i - 1] = value;
				dataIndex[i - 1] = dataIndexValue;
				break;
			}
		}
	}
	return 1;
					
}	

int sortedStack::getLowestItemIndex()
{
	if(currentSize == 0)
		return -1;
	else
		return dataIndex[currentSize - 1];
}
		
int sortedStack::isUnique(int itemIdx)
{
	if(itemIdx == -1)
	{
		if(currentSize == 0)
			return -1;
		if(currentSize == 1)
			return 1;
		if(items[currentSize - 1] < items[currentSize - 2])
			return 1;
		else 
			return 0;
	}
	else
	{
		if(itemIdx > currentSize - 1)
			return -1;
		if(itemIdx == currentSize - 1)
		{
			if(items[itemIdx] < items[itemIdx - 1])
				return 1;
			else
				return 0;
		}
		else
		{
			if( (items[itemIdx] < items[itemIdx - 1])&&
				(items[itemIdx] > items[itemIdx + 1]) )
				return 1;
			else
				return 0;
		}
	}
	return -1;		
				
				
}
													
void sortedStack::print()
{
	cout<<"\nStack content: \n";
	for(int i = maxSize - 1; i >= 0; i--)
		cout<<items[i]<<", "<<dataIndex[i]<<endl;
}

int getMatrixBounds(int **matrix, int sizeOfResidueArray, int *Xmin, int *Xmax, int *Ymin, int *Ymax)
{
	bool flag = true;
	
	/* get min X */
	for(int x = 0; x < sizeOfResidueArray && flag; x++)
		for(int y = 0; y < sizeOfResidueArray && flag; y++)
			if(matrix[y][x])
			{
				*Xmin = x;
				flag = false;
			}
	
	flag = true;		
	/* get Min Y */
	for(int y = 0; y < sizeOfResidueArray && flag; y++)
		for(int x = 0; x < sizeOfResidueArray && flag; x++)
			if(matrix[y][x])
			{
				*Ymin = y;
				flag = false;
			}
		
	flag = true;
	/* get Max X */
	for(int x = sizeOfResidueArray - 1; x >= 0 && flag; x--)
	{
		for(int y = sizeOfResidueArray - 1; y >= 0 && flag; y--)
			if(matrix[y][x])
			{
				*Xmax = x;
				flag = false;
			}
	}
	
	flag = true;					
	/* get Max Y */
	for(int y = sizeOfResidueArray - 1; y >= 0 && flag; y--)
		for(int x = sizeOfResidueArray - 1; x >= 0 && flag; x--)
			if(matrix[y][x])
			{
				*Ymax = y;
				flag = false;
			}

	return 1;
}		

double getLocalityIndex(int sizeOfResidueArray, point *structure, char *hp)
{
#if 1
							  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
							  /*	 	  H	     P	     +	    - */	
double energyMatrix[4][4] =	  /* H */ {{ -1.0  ,  0.0,   0.0 ,  0.0  },
 							  /* P */  {  0.0  ,  0.0 ,  -0.125 , -0.125  },
							  /* + */  {  0.0  , -0.125  ,  +1.0 , -1.0  },
							  /* - */  {  0.0  , -0.125  ,  -1.0 , +1.0  } };

#endif


	double index = 0.0;
	
	int **matrix = new int*[sizeOfResidueArray*2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < sizeOfResidueArray*2; i++)
	{
		if( !(matrix[i] = new int[sizeOfResidueArray*2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < sizeOfResidueArray*2; j++)
			matrix[i][j] = 0;
			
	}

	for(int i = 1; i <= sizeOfResidueArray; i++)
		matrix[structure[i].y][structure[i].x] = i;

	int *mode = new int[sizeOfResidueArray];
	if(!mode)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				mode[i] = HYDROPHOBIC; break;
 			case 'P':
				mode[i] = POLAR_NEUTRAL; break;
 			case '+':
				mode[i] = POSITIVE_CHARGE; break;	
			case '-':
				mode[i] = NEGATIVE_CHARGE; break;
		}		
	}

	double tmp = 0;
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		int x = structure[i].x;
		int y = structure[i].y;

			if(y < sizeOfResidueArray*2 - 1)
			{
				int diff = ABS_INT(matrix[y + 1][x] - matrix[y][x]);
				if(diff > 2)
				{
					tmp = energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]]*
						 (double)(sizeOfResidueArray - diff);
					index -= tmp;
					//cout<<tmp<<", "<<energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]];
					//cout<<", "<<ABS_INT(matrix[y + 1][x] - matrix[y][x])<<endl;
				}
			}
			if(y > 0)
			{
				int diff = ABS_INT(matrix[y - 1][x] - matrix[y][x]);
				if(diff > 2)
				{

					tmp = energyMatrix[mode[matrix[y - 1][x]]][mode[matrix[y][x]]]*
							 (double)(sizeOfResidueArray - diff);
					index -= tmp;
					//cout<<tmp<<", "<<energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]];
					//cout<<", "<<ABS_INT(matrix[y + 1][x] - matrix[y][x])<<endl;
				}
			}
			if(x < sizeOfResidueArray*2 -1)
			{
				int diff = ABS_INT(matrix[y][x + 1] - matrix[y][x]);
				if(diff > 2)
				{

					tmp = energyMatrix[mode[matrix[y][x + 1]]][mode[matrix[y][x]]]*
							 (double)(sizeOfResidueArray - diff);
					index -= tmp;				
					//cout<<tmp<<", "<<energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]];
					//cout<<", "<<ABS_INT(matrix[y + 1][x] - matrix[y][x])<<endl;
				}
			}
			if(x > 0)
			{
				int diff = ABS_INT(matrix[y][x - 1] - matrix[y][x]);
				if(diff > 2)
				{

					tmp = energyMatrix[mode[matrix[y ][x - 1]]][mode[matrix[y][x]]]*
							 (double)(sizeOfResidueArray - diff);
					index -= tmp;				
					//cout<<tmp<<", "<<energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]];
					//cout<<", "<<ABS_INT(matrix[y + 1][x] - matrix[y][x])<<endl;
				}
			}
	}
	
	index /= 2.0;
		
	for(int i = 0; i < sizeOfResidueArray*2; i++)
		delete []matrix[i];
	
	delete []matrix;
	delete[]mode;
	
	return index;
}


double getStrongInteractionLocalityIndex(int sizeOfResidueArray, 
										 point *structure, 
										 char *hp, 
										 int segmentWidth)
{
#if 1
							  /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
							  
							  /*	 	  H	     P	     +	    - */	
double energyMatrix[4][4] =	  /* H */ {{ -1.0  ,  0.0,   0.0 ,  0.0  },
 							  /* P */  {  0.0  ,  0.0 ,  -0.125 , -0.125  },
							  /* + */  {  0.0  , -0.125  ,  +1.0 , -1.0  },
							  /* - */  {  0.0  , -0.125  ,  -1.0 , +1.0  } };

#endif
	
	int **matrix = new int*[sizeOfResidueArray*2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < sizeOfResidueArray*2; i++)
	{
		if( !(matrix[i] = new int[sizeOfResidueArray*2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < sizeOfResidueArray*2; j++)
			matrix[i][j] = 0;
			
	}

	for(int i = 1; i <= sizeOfResidueArray; i++)
		matrix[structure[i].y][structure[i].x] = i;

	int *mode = new int[sizeOfResidueArray];
	if(!mode)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				mode[i] = HYDROPHOBIC; break;
 			case 'P':
				mode[i] = POLAR_NEUTRAL; break;
 			case '+':
				mode[i] = POSITIVE_CHARGE; break;	
			case '-':
				mode[i] = NEGATIVE_CHARGE; break;
		}		
	}

	double energyAvg = 0;
	int interactionCounter = 0;
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		int x = structure[i].x;
		int y = structure[i].y;

			if(y < sizeOfResidueArray*2 - 1)
			{
				int diff = ABS_INT(matrix[y + 1][x] - matrix[y][x]);
				if(diff > 2)
				{
					energyAvg += energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]];
					interactionCounter++;
				}
						
			}
			if(y > 0)
			{
				int diff = ABS_INT(matrix[y - 1][x] - matrix[y][x]);
				if(diff > 2)
				{
					energyAvg += energyMatrix[mode[matrix[y - 1][x]]][mode[matrix[y][x]]];
					interactionCounter++;
				}
				
			}
			if(x < sizeOfResidueArray*2 -1)
			{
				int diff = ABS_INT(matrix[y][x + 1] - matrix[y][x]);
				if(diff > 2)
				{
					energyAvg += energyMatrix[mode[matrix[y][x + 1]]][mode[matrix[y][x]]];
					interactionCounter++;
				}
				
			}
			if(x > 0)
			{
				int diff = ABS_INT(matrix[y][x - 1] - matrix[y][x]);
				if(diff > 2)
				{
					energyAvg += energyMatrix[mode[matrix[y ][x - 1]]][mode[matrix[y][x]]];
					interactionCounter++;
				}
				
			}
	}

	energyAvg /= interactionCounter;
	
	double index = 0.0;
	double tmp = 0;
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		int x = structure[i].x;
		int y = structure[i].y;

			if(y < sizeOfResidueArray*2 - 1)
			{
				int diff = ABS_INT(matrix[y + 1][x] - matrix[y][x]);
				if(diff > 2)
				{
					tmp = 
						ABS(energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]] - energyAvg)
						 *(double)(sizeOfResidueArray - diff);
					index += tmp;
					//cout<<tmp<<", "<<energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]];
					//cout<<", "<<ABS_INT(matrix[y + 1][x] - matrix[y][x])<<endl;
				}
			}
			if(y > 0)
			{
				int diff = ABS_INT(matrix[y - 1][x] - matrix[y][x]);
				if(diff > 2)
				{

					tmp = 
						ABS(energyMatrix[mode[matrix[y - 1][x]]][mode[matrix[y][x]]] - energyAvg)
							 *(double)(sizeOfResidueArray - diff);
					index += tmp;
					//cout<<tmp<<", "<<energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]];
					//cout<<", "<<ABS_INT(matrix[y + 1][x] - matrix[y][x])<<endl;
				}
			}
			if(x < sizeOfResidueArray*2 -1)
			{
				int diff = ABS_INT(matrix[y][x + 1] - matrix[y][x]);
				if(diff > 2)
				{

					tmp = 
						ABS(energyMatrix[mode[matrix[y][x + 1]]][mode[matrix[y][x]]] - energyAvg)
							 *(double)(sizeOfResidueArray - diff);
					index += tmp;				
					//cout<<tmp<<", "<<energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]];
					//cout<<", "<<ABS_INT(matrix[y + 1][x] - matrix[y][x])<<endl;
				}
			}
			if(x > 0)
			{
				int diff = ABS_INT(matrix[y][x - 1] - matrix[y][x]);
				if(diff > 2)
				{

					tmp = 
						ABS(energyMatrix[mode[matrix[y ][x - 1]]][mode[matrix[y][x]]] - energyAvg)
							 *(double)(sizeOfResidueArray - diff);
					index += tmp;				
					//cout<<tmp<<", "<<energyMatrix[mode[matrix[y + 1][x]]][mode[matrix[y][x]]];
					//cout<<", "<<ABS_INT(matrix[y + 1][x] - matrix[y][x])<<endl;
				}
			}
	}
	
	index /= 2.0;
		
	for(int i = 0; i < sizeOfResidueArray*2; i++)
		delete []matrix[i];
	
	delete []matrix;
	delete[]mode;
	
	//quantization:
	if(segmentWidth)
	{
		int mod = 0;
		while( ((int)index)%(mod + 1) < (int)index) mod += segmentWidth;
		return mod;
	}
		
	return index;
}


int writeStructure2output(int sizeOfResidueArray, 
						  point *structure, 
						  char *confRes) 
{
	int **matrix = new int*[sizeOfResidueArray*2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < sizeOfResidueArray*2; i++)
	{
		if( !(matrix[i] = new int[sizeOfResidueArray*2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < sizeOfResidueArray*2; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
		if( (structure[i].y > sizeOfResidueArray*2 - 1) && 
			(structure[i].x > sizeOfResidueArray*2 - 1) )
		{
			cout<<"ERROR - out of limit writeStructure2output\n";
			for(int i = 0; i < sizeOfResidueArray*2; i++)
				delete []matrix[i];
	
			delete []matrix;
			return 0;
		}

		else
			matrix[structure[i].y][structure[i].x] = i;


	int Xmin, Xmax, Ymin, Ymax;
	getMatrixBounds(matrix, sizeOfResidueArray*2, &Xmin, &Xmax, &Ymin, &Ymax);
	
	if(confRes)
	{
		cout<<"\n["<<sizeOfResidueArray<<"]";
		for(int i = 0; i < sizeOfResidueArray; i++)
			cout<<confRes[i];
		cout<<endl<<endl;

		for(int y = Ymax; y >= Ymin; y--)
		{
			for(int x = Xmin; x <= Xmax; x++)
			{
				if(matrix[y][x])
					cout<<confRes[matrix[y][x] - 1];
				else
					cout<<" ";
			}
			cout<<endl;
		}
	}

	cout<<"\n$structure\n";
	for(int y = Ymax; y >= Ymin; y--)
	{
		for(int x = Xmin; x <= Xmax; x++)
		{
			if(matrix[y][x] > 9)
				cout<<"("<<matrix[y][x]<<")";
			else if(matrix[y][x] > 0)
				cout<<"( "<<matrix[y][x]<<")";
			if(!matrix[y][x])
				cout<<"    ";
		}
		cout<<endl;
	}
	cout<<"$\n";
	cout<<"------------------------------------------------------------------------------";
	
				
	for(int i = 0; i < sizeOfResidueArray*2; i++)
		delete []matrix[i];
	
	delete []matrix;
	 
	return 1;
}
int getStructFromDB(int idx, point *structure, int sizeOfResidueArray, int sideStructDBsize)
{
	
	char name[200];
	
	sprintf(name, "../evolution/DB/%d-(%d)-mer-struct-enum-mod", 
			sizeOfResidueArray,
			sideStructDBsize);
	
	FILE* fp = fopen(name, "rb");
	
	if(!fp)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}
	
	//cout<<"\nopened file: "<<name<<" for DB\n";	
	fseek(fp, sizeof(int)+sizeof(double)+sizeof(int)*2*sizeOfResidueArray*(idx) ,SEEK_SET);
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		if( (fread(&(structure[i].x), sizeof(int), 1, fp) != 1)||
			(fread(&(structure[i].y), sizeof(int), 1, fp) != 1) )
			{
				cout<<"File Read Error - foldingComplex\n";
				fclose(fp);
				exit(1);
			}
	}
		
	fclose(fp);
	return 1;
	
}

//returns -1 if eof
int getConfigurationIndexFromFile(char *fname, int index)
{
	ifstream fi;

	char localBuffer[10000];
	
	fi.open(fname);
	fi.get(localBuffer, 10000, EOF);
	fi.close();

	int bufSize = strlen(localBuffer);
	
	int spaces = 0;
	int i = 0, j = 0;
	char tmpBuffer[100];

	while(i < bufSize)
	{
		//clean spaces;
		for(j = 0;i < bufSize && (localBuffer[i] == ' ' || localBuffer[i] == '\n'); i++, j++);
	
		for(j = 0;
			i < bufSize && j < 100 && 
			(localBuffer[i] != ' ' && localBuffer[i] != '\n'); 
			i++, j++)
			tmpBuffer[j] = localBuffer[i];

		if(j == 0)
		{
			if(i == bufSize)
			{
				cout<<"End of source index file\n";
				return -1;
			}
			cout<<"Error reading spaces - getConfigurationIndexFromFile "<<bufSize<<endl;
			return -1; 
		}
	
		//if i == bufSize || localBuffer[i] == white space
		tmpBuffer[j] = 0;
		int number = atoi(tmpBuffer);	
		//cout<<"n: "<<number<<endl;
	
		if(spaces == index)
		{
			//cout<<"Return number\n";
			return number;
		}
		spaces++;
	}
	cout<<"End of file: getConfigurationIndexFromFile\n";
	return -1;
}	

/*
int findFileInDir(char* name, char* fileFounded, char* substr)
{
	
    DIR* dirp = opendir(name);
    if (dirp == NULL) 
	{
    	return 0;
    }
     
	struct direct * dp;  
	  
	while ((dp = readdir(dirp)) != NULL) 
	{
		
		if( strfind(dp->d_name, ".data") == (dp->d_namlen - 5) &&
			strfind(dp->d_name, substr) != -1 )
		{
			sprintf(fileFounded, "%s%s", name, dp->d_name);
			break;	
		}
		
    }
    closedir(dirp);

	if(dp == NULL)
		return 0;
    return 1;

}	
*/
//this function runs through all the file and prints out the minimum pairwisedistant structure.
int grabNativeStructureFromSimulationsFile(char *fname, double threshold, char *seqMode)
{
	residueArray reader(fname);
	int numberOfStructures = reader.numberOfStructures;
	
	if(reader.numberOfStructures == 0)
	{
		cout<<"-------Error reading no structures on file----------\n";
		return 0;
	}
	
	RMSD rmsd(&reader, reader.sizeOfResidueArray, numberOfStructures);
	
	if(!seqMode)
	{
		seqMode = new char[reader.sizeOfResidueArray];
		if(!seqMode)
		{
			cout<<"Error mem alloc\n";
			exit(1);
		}
	
		for(int i = 1; i <= reader.sizeOfResidueArray; i++)
		{
			switch(reader.res[i].mode)
			{
				case HYDROPHOBIC:
					seqMode[i-1] = 'H'; break;
 				case POLAR_NEUTRAL:
					seqMode[i-1] = 'P'; break;
 				case POSITIVE_CHARGE:
					seqMode[i-1] = '+'; break;	
				case NEGATIVE_CHARGE:
					seqMode[i-1] = '-'; break;
			}		
		}
	}



	double *results = new double[numberOfStructures];
	double *pairdiffs = new double[numberOfStructures];
	
	if(!results || !pairdiffs)
	{
		cout<<"ERROR mem alloc printNativeStructureFromSimulations\n";
		exit(1);
	}
	
	for(int i = 0; reader.read(); i++)
	{
		//cout<<i<<", ";
		for(int j = 1; j <= reader.sizeOfResidueArray; j++)
		{
			rmsd.structures[i][j].x = reader.res[j].position.x;
			rmsd.structures[i][j].y = reader.res[j].position.y;		
		}
	}
	

	rmsd.pairwiseCompute(numberOfStructures, results, pairdiffs);

	int minPairdiff = 0;
	
	for(int i = 1; i < numberOfStructures; i++)
		if(pairdiffs[minPairdiff] >= pairdiffs[i])
			minPairdiff = i;
	cout<<"Minimal structure number: "<<minPairdiff<<" Pairdiff: "<<pairdiffs[minPairdiff]<<endl;
	double li = getLocalityIndex(reader.sizeOfResidueArray, rmsd.structures[minPairdiff], seqMode);
	cout<<"$Locality Index "<<li<<" $\n";

	if( (threshold > 0 && pairdiffs[minPairdiff] < threshold) ||
		(threshold < 0 && pairdiffs[minPairdiff] > -1*threshold) )
	{
		writeStructure2output(reader.sizeOfResidueArray, rmsd.structures[minPairdiff], seqMode);		
		cout<<"------------------------------------------------------------------------------\n";
	}
	else
	{
		cout<<"------------------------------------------------------------------------------\n";
		delete []results;
		delete []pairdiffs;
		return 0;
		//cout<<"Sequence does not below the treshold "<<threshold<<endl;
	}
	
	delete []results;
	delete []pairdiffs;
	return 1;
}

//this function runs through all the file and prints out the minimum pairwisedistant structure.
int getRMSD2NativeStructureFromFile(char *fnameStruct, char *fnameMCS, 
									point *structure, char *dstfname, char *seqMode)
{
	FILE* fp = fopen(fnameMCS, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found\n";
		exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize < 10)
	{
		fclose(fp);
		return 0;
	}
	fseek(fp, 0, SEEK_SET);
	
	char buffer[1024];
	int numbers[1000];
	
	int i = 0, n = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[i++] = ch;
		else if(ch == ' ')
		{
			buffer[i] = NULL;
			numbers[n] = atoi(buffer);
			i = 0;
		}
		else
		{
			n++;
			i = 0;
		}
	}		
	fclose(fp);
	
	residueArray reader(fnameStruct);
	int numberOfStructures = reader.numberOfStructures;
	
	if(reader.numberOfStructures == 0)
	{
		cout<<"-------Error reading no structures on file----------\n";
		return 0;
	}
	
	if(!seqMode)
	{
		seqMode = new char[reader.sizeOfResidueArray];
		if(!seqMode)
		{
			cout<<"Error mem alloc\n";
			exit(1);
		}
	
		for(int i = 1; i <= reader.sizeOfResidueArray; i++)
		{
			switch(reader.res[i].mode)
			{
				case HYDROPHOBIC:
					seqMode[i-1] = 'H'; break;
 				case POLAR_NEUTRAL:
					seqMode[i-1] = 'P'; break;
 				case POSITIVE_CHARGE:
					seqMode[i-1] = '+'; break;	
				case NEGATIVE_CHARGE:
					seqMode[i-1] = '-'; break;
			}		
		}
	}

	RMSD rmsd(&reader, reader.sizeOfResidueArray, numberOfStructures);
	rmsd.update(structure);
	
	FILE* fp_dst = fopen(dstfname, "wb");
	
	if(!fp_dst)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}

	for(i = 0; reader.read(); i++)
	{
		double rmsdResult = rmsd.compute(reader);
		//cout<<numbers[i]<<" "<<rmsdResult<<endl;
		fprintf(fp_dst, "%d %f\n", numbers[i], rmsdResult);	
	}
	fclose(fp_dst);
	

	return 1;
}


//this function runs through all the file and prints out the minimum pairwisedistant structure.
double getAverageRMSD2NativeStructureFromFile(char *fnameStruct, point *structure, char *seqMode)
{
	

	residueArray reader(fnameStruct);
	int numberOfStructures = reader.numberOfStructures;
	
	if(reader.numberOfStructures == 0)
	{
		cout<<"-------Error reading no structures on file----------\n";
		return 0;
	}
	
	if(!seqMode)
	{
		seqMode = new char[reader.sizeOfResidueArray];
		if(!seqMode)
		{
			cout<<"Error mem alloc\n";
			exit(1);
		}
	
		for(int i = 1; i <= reader.sizeOfResidueArray; i++)
		{
			switch(reader.res[i].mode)
			{
				case HYDROPHOBIC:
					seqMode[i-1] = 'H'; break;
 				case POLAR_NEUTRAL:
					seqMode[i-1] = 'P'; break;
 				case POSITIVE_CHARGE:
					seqMode[i-1] = '+'; break;	
				case NEGATIVE_CHARGE:
					seqMode[i-1] = '-'; break;
			}		
		}
	}

	RMSD rmsd(&reader, reader.sizeOfResidueArray, numberOfStructures);
	rmsd.update(structure);
	
	double rmsdResult = 0, i;
	for(i = 0; reader.read(); i++)
	{
		rmsdResult += rmsd.compute(reader);
	}
	
	return rmsdResult/i;
}


//this function runs through all the file and prints out the minimum pairwisedistant structure.
double getFractionOfFolded2Native(char *fnameStruct, char *fnameMCS, 
									point *structure, char *dstfname, char *seqMode)
{
	FILE* fp = fopen(fnameMCS, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found\n";
		exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize < 10)
	{
		fclose(fp);
		return -1.0;
	}
	fseek(fp, 0, SEEK_SET);
	
	char buffer[1024];
	int numbers[1000];
	
	int i = 0, n = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[i++] = ch;
		else if(ch == ' ')
		{
			buffer[i] = NULL;
			numbers[n] = atoi(buffer);
			i = 0;
		}
		else
		{
			n++;
			i = 0;
		}
	}		
	fclose(fp);
	
	residueArray reader(fnameStruct);
	int numberOfStructures = reader.numberOfStructures;
	
	if(reader.numberOfStructures == 0)
	{
		cout<<"-------Error reading no structures on file----------\n";
		return -1.0;
	}
	
	if(!seqMode)
	{
		seqMode = new char[reader.sizeOfResidueArray];
		if(!seqMode)
		{
			cout<<"Error mem alloc\n";
			exit(1);
		}
	
		for(int i = 1; i <= reader.sizeOfResidueArray; i++)
		{
			switch(reader.res[i].mode)
			{
				case HYDROPHOBIC:
					seqMode[i-1] = 'H'; break;
 				case POLAR_NEUTRAL:
					seqMode[i-1] = 'P'; break;
 				case POSITIVE_CHARGE:
					seqMode[i-1] = '+'; break;	
				case NEGATIVE_CHARGE:
					seqMode[i-1] = '-'; break;
			}		
		}
	}

	RMSD rmsd(&reader, reader.sizeOfResidueArray, numberOfStructures);
	rmsd.update(structure);
	
	/*FILE* fp_dst = fopen(dstfname, "wb");
	
	if(!fp_dst)
	{
		cout<<"ERROR - file opening\n";
		exit(0);
	}*/
	double counter = 0;
	for(i = 0; reader.read(); i++)
	{
		double rmsdResult = rmsd.compute(reader);
		//cout<<numbers[i]<<" "<<rmsdResult<<endl;
		//fprintf(fp_dst, "%d %f\n", numbers[i], rmsdResult);	
		if(rmsdResult < 0.1)
			counter++;
	}
	//fclose(fp_dst);
	

	return counter/(double)i;
}

double getPearsonCorrelation(double N, double *dataX, double *dataY)
{
	
	/*
	Pearson Product Moment Correlation:

	r =                 (N*sumof(X*Y) - sumof(X)*sumof(Y))
	    ___________________________________________________________________
		sqrt( (N*sumof(X^2) - (sumof(X))^2)*(N*sumof(Y^2) - (sumof(Y))^2) )
		
     where N is the number of pairs of scores.
	*/
	
	double sumofXY = 0, sumofX = 0, sumofY = 0, sumofSqX = 0, sumofSqY = 0;
	double X, Y;

	for(int i = 0; i < N; i++)
	{
		X = dataX[i]; 
		Y = dataY[i];
		//cout<<X<<" "<<Y<<endl;
				
		sumofXY += X*Y;
		sumofX += X;
		sumofY += Y;
		sumofSqX += X*X;
		sumofSqY += Y*Y;
		
	}
		
	
	double dX = N*sumofSqX - sumofX*sumofX;
	double dY = N*sumofSqY - sumofY*sumofY;
	
	double r = (N*sumofXY - sumofX*sumofY)/sqrt(dX*dY);
	return r;
}

double getAverageMCS2NativeStructureFromFile(char *fnameStruct, char *fnameMCS, 
									point *structure, char *seqMode)
{
	//return 1;
	FILE* fp = fopen(fnameMCS, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found\n";
		exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	//cout<<fnameMCS<<endl;
	//fclose(fp);
	//return 1;
	if(fileSize < 10)
	{
		fclose(fp);
		return 0;
	}
	fseek(fp, 0, SEEK_SET);
	
	char buffer[1024];
	int numbers[1000];
	
	int i = 0, n = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[i++] = ch;
		else if(ch == ' ')
		{
			buffer[i] = NULL;
			numbers[n] = atoi(buffer);
			i = 0;
		}
		else
		{
			n++;
			i = 0;
		}
	}		
	fclose(fp);
	
	residueArray reader(fnameStruct);
	int numberOfStructures = reader.numberOfStructures;
	
	if(reader.numberOfStructures == 0)
	{
		cout<<"-------Error reading no structures on file----------\n";
		return -1.0;
	}
	
	if(!seqMode)
	{
		seqMode = new char[reader.sizeOfResidueArray];
		if(!seqMode)
		{
			cout<<"Error mem alloc\n";
			exit(1);
		}
	
		for(int i = 1; i <= reader.sizeOfResidueArray; i++)
		{
			switch(reader.res[i].mode)
			{
				case HYDROPHOBIC:
					seqMode[i-1] = 'H'; break;
 				case POLAR_NEUTRAL:
					seqMode[i-1] = 'P'; break;
 				case POSITIVE_CHARGE:
					seqMode[i-1] = '+'; break;	
				case NEGATIVE_CHARGE:
					seqMode[i-1] = '-'; break;
			}		
		}
	}

	RMSD rmsd(&reader, reader.sizeOfResidueArray, numberOfStructures);
	rmsd.update(structure);
	

	double counter = 0, mcsAcc = 0;
	for(i = 0; reader.read(); i++)
	{
		double rmsdResult = rmsd.compute(reader);
		//cout<<numbers[i]<<" "<<rmsdResult<<endl;
	
		if(rmsdResult < 0.1)
		{
			mcsAcc += (double)numbers[i];
			counter++;
		}
	}
	
	if(counter == 0.0)
		return 3000000.0;
	return mcsAcc/counter;

}
#if 0
int main(int argc, char** argv)
{
	
#if 1
	if(argc < 8)
	{
		cout<<"usage: dirname dname substr segmentWidth iterations tres axe\n";
		exit(0);
	}
	
	char *dirname = argv[1];
	char *dname = argv[2];
	char *substr = argv[3];
	int segmentWidth = atoi(argv[4]);
	int iterations = atoi(argv[5]);
	double tres = strtod(argv[6], NULL);
	char axe = *argv[7];

	//computeHistogram4dir(dirname, dname, substr, segmentWidth, iterations, tres, axe);
#endif
		
#if 0//hisstogram:
	if(argc < 6)
	{
		cout<<"usage: srcFileName dstFileName segmentWidth iterations tres [axe]\n";
		exit(0);
	}
	
	countFile4Histogram(argv[1], argv[2], atoi(argv[3]), atoi(argv[4]), strtod(argv[5], NULL));
	
#endif
	
#if 0
	int num = 0;
	for(int i = 0; i < 50; i++)
		if( (num = getConfigurationIndexFromFile(argv[1], i)) == -1)
			break;
	
#endif
#if 0	
	statistics s;
	
	if(argc < 3)
	{
		cout<<"WorkingDirectory substring\n";
		exit(0);
	}

	double statisticX[2], statisticY[2];
	
	int index = 0;
	while(true) 
	{
		if(s.compute4file(index, argv[1], argv[2], statisticX, statisticY) ==  0)
			break;
		cout<<index<<" "<<statisticY[0]<<" "<<statisticY[1]<<endl;
		index++;
	}
#endif
	
#if 0
	statistics s;
	//s.readme(argv[1]);
	//s.compute4file(argv[1]);
	if(argc < 4)
	{
		cout<<"WorkingDirectory substring dstFilePrefix\n";
		exit(0);
	}
	s.compute4dir(argv[1], argv[3], argv[2] );
#endif
	/*
	sortedStack ss(10);
	srand48((unsigned)time(0));
	
	for(int i = 0; i < atoi(argv[1]); i++)
		ss.insert(20.0*drand48(), i);
	ss.print();
	*/
	
	
	return 0;
}
#endif	
//--------------------------------------------------------------------------------------------------
