//dimersChaperonComplex.cpp

#include "protchap.h"
#include "doubleDomain.h"
#include "utilities.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>
 
char VERSIONDD[100] = "Version 04-09-11, V21 doubleDomain.cpp";

int doubleDomain::foldToMinimumEnergy
										  (double times, 
										   int numOfSimulations, 
										   char *hp)
{
	
	cout<<"Double domain folding func foldToMinimumEnergy, "<<VERSIONDD<<endl;
	
	//initFoldingComplex();
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	int linkerLength = fromto[2] - fromto[1] - 1;//e.g. 1 25 31 55: 31-25=6 
	int domain_A_length = fromto[1] - fromto[0] + 1;//e.g. 25-1=24
	int domain_B_length = fromto[3] - fromto[2] + 1;
	
	UPDATE_PROTEIN_MODES(res)
	 		
	cout<<"doubledomain foldToMinimumEnergy: Begin folding:"<<endl;
	
	char fostr[1024];
	cout<<times<<", seq: "<<hp<<endl;
	sprintf(fostr, "%sfc-itr%d.data", outputDatafileName, (int)times);
	cout<<fostr<<endl;
	ofstream of(fostr); 
	of<<"#SEQ\t"<<hp<<endl<<"max mcs: "<<times<<", maxRangeOfLocalConf: "<<maxRangeOfLocalConf<<", edgesProbability: "<<edgesProbability<<", simulationFactor: "<<simulationFactor<<", Method: "<<VERSIONDD<<" foldToMinimumEnergy"<<endl<<endl;
	of<<"#DOUBLEDOMAIN\t"<<fromto[0]<<" "<<fromto[1]<<" "<<fromto[2]<<" "<<fromto[3]<<endl;
	for(int m = 0; m < numOfSimulations; m++)
	{
		cout<<"Doing itr: "<<m<<endl;
		initFoldingComplex();
		
		double itr = 0, alpha_itr = 0;
		
		for(int i = 0; i < times; i++)
		{

			itr++;
			alpha_itr++;
			
			foldOnce();
			if(alpha_itr == ALPHA_ITR)
			{
				alpha_itr = 0;
			
				if(Ck < ALPHA_LOWER_BOND)
					Ck = ALPHA_LOWER_BOND;
				else
					Ck *= ALPHA;	
			}		
		}
		
		CfileHdlr.writeStructure2file(sizeOfResidueArray, BFA[0], of);
		of<<"Struct-D Energy: "<<BFA[0]->energy<<", MCS: "<<BFA[0]->stepNumber<<endl<<endl;
		
		int dd, sd;
		for(dd = fromto[0], sd = 1; dd <= fromto[1]; dd++, sd++) 
			structure[sd] = BFA[1]->res[dd].position;
		CfileHdlr.writeStructure2file(domain_A_length, structure, &hp[fromto[0] - 1], of);
		of<<"Struct-A Energy: "<<BFA[1]->energy<<", MCS: "<<BFA[1]->stepNumber<<endl<<endl;
		
		for(dd = fromto[2], sd = 1; dd <= fromto[3]; dd++, sd++) 
			structure[sd] = BFA[2]->res[dd].position;
		CfileHdlr.writeStructure2file(domain_B_length, structure, &hp[fromto[2] - 1], of);
		of<<"Struct-B Energy: "<<BFA[2]->energy<<", MCS: "<<BFA[2]->stepNumber<<endl<<endl;
	}
	
	of.close();
	delete []structure;
	cout<<"finish seq: "<<hp<<endl;
	return 1;
}	
	

double doubleDomain::getEnergyValue(int x, int y, int i)
{
	//cout<<boolMatrix[y][x]<<" gev"<<endl;
	if( (boolMatrix[y][x] > 0)&&
	    ( (boolMatrix[y][x] - i) >  2  ||
	      (boolMatrix[y][x] - i) < -2) ) 
	{
		return energyMatrix[res[boolMatrix[y][x]].mode][res[i].mode] + alphaE;	
	}
	return 0.0;
}

//fromtoIn - 1 base!!!
doubleDomain::doubleDomain(int length, int *fromtoIn):
foldingComplex(length)
{
	cout<<"doubleDomain ctor 1"<<endl;
	for(int i = 0; i < 4; i++)
	{
		fromto[i] = fromtoIn[i];
		cout<<fromto[i]<<" ";
	}
	
	for(int i = 0; i < 3; i++)
	{
		BFA[i] = new foldingArray(length);
		MINENERGY_BFA[i] = new foldingArray(length);
	}
}

doubleDomain::~doubleDomain()
{
	cout<<"~doubleDomain"<<endl;
	for(int i = 0; i < 3; i++)
	{
		if(BFA[i])
			delete BFA[i];
		if(MINENERGY_BFA[i])
			delete MINENERGY_BFA[i];
	}
}

double doubleDomain::getSingleDomainEnergyValue(int x, int y, int i, int from, int to)
{
	if(boolMatrix[y][x] < from || boolMatrix[y][x] > to) {
		return 0.0;
	}
	if( ((boolMatrix[y][x] - i) >  2)  || ((boolMatrix[y][x] - i) < -2) )
	{		
			return energyMatrix[res[boolMatrix[y][x]].mode][res[i].mode] + alphaE;	
	}
	return 0.0;
}

//Returns energy[0] - energy of whole sequence, energy[1] - energy by single domain sequence
double doubleDomain::calculateMonomersEnergy(char which, double *energy)
{
	energy[0] = 0;
	energy[1] = 0;

	int i;
	int from, to;
	
	switch(which)
	{
		case 'A':
					from = fromto[0];
					to = fromto[1];
					break;
		case 'B':
					from = fromto[2];
					to = fromto[3];
					break;
		default :	
		case 'D':
					from = 1;
					to = sizeOfResidueArray;
					break;
	}
		
	
	for(i = from; i <= to; i++)
	{	
		
			int x = res[i].position.x;
			int y = res[i].position.y;
// cout<<"3 Got here!!! "<<i<<" "<<from<<", "<<to<<" "<<x<<" "<<y<<endl;
			if(y < top_y - 1)
			{
				if(boolMatrix[y+1][x] > 0 && (boolMatrix[y+1][x] < from || boolMatrix[y+1][x] > to)) { 
					energy[0] += getEnergyValue(x, y+1, i)*2;
				}
				else {
					energy[0] += getEnergyValue(x, y+1, i);
				}
				energy[1] += getSingleDomainEnergyValue(x, y+1, i, from, to);
			}
			if(y > buttom_y)
			{
				if(boolMatrix[y-1][x] > 0 && (boolMatrix[y-1][x] < from || boolMatrix[y-1][x] > to)) { 
					energy[0] += getEnergyValue(x, y-1, i)*2;
				}
				else {
					energy[0] += getEnergyValue(x, y-1, i);
				}
				energy[1] += getSingleDomainEnergyValue(x, y-1, i, from, to);
			}
			if(x < right_x -1)
			{
				if(boolMatrix[y][x+1] > 0 && (boolMatrix[y][x+1] < from || boolMatrix[y][x+1] > to)) { 
					energy[0] += getEnergyValue(x+1, y, i)*2;
				}
				else {
					energy[0] += getEnergyValue(x+1, y, i);
				}
				energy[1] += getSingleDomainEnergyValue(x+1, y, i, from, to);
			}
			if(x > left_x)
			{
				if(boolMatrix[y][x-1] > 0 && (boolMatrix[y][x-1] < from || boolMatrix[y][x-1] > to)) { 
					energy[0] += getEnergyValue(x-1, y, i)*2;
				}
				else {
					energy[0] += getEnergyValue(x-1, y, i);
				}
				energy[1] += getSingleDomainEnergyValue(x-1, y, i, from, to);
			}
		
	}//end for loop
		
	//Energy will always be double than should be	
	energy[0] /= 2;
	energy[1] /= 2;
	
	return (energy[0]);
}


int doubleDomain::modifyBestFoldingArray()
{
// 	cout<<"Dimers modifyBestFoldingArray func"<<endl;
	if(rmsd) 
	{
		{
			double error[6];
			rmsd->dimer_compute(*this, 
								fromto[0], fromto[1],
								fromto[2], fromto[3], error);
		
			//0, 1 - global
			//2, 3 - monomer A
			//4, 5 - monomer B
			
			//MIN ENERGY given best folding array of whole sequence:
			double monomerEnergy[2];
			calculateMonomersEnergy('D', monomerEnergy);
			if(MINENERGY_BFAenergy[0] > monomerEnergy[1])
			{
				MINENERGY_BFA[0]->energy = monomerEnergy[0];
				MINENERGY_BFA[0]->stepNumber = enteringMCAnneal;
				MINENERGY_BFAenergy[0] = monomerEnergy[1];
				MINENERGY_BFAerror[0] = error[0];
				MINENERGY_BFAerror[1] = error[1];
				
				MINENERGY_BFA[1]->energy = calculateMonomersEnergy('A', monomerEnergy);
				MINENERGY_BFA[1]->stepNumber = enteringMCAnneal;
				MINENERGY_BFAenergy[1] = monomerEnergy[1];
				MINENERGY_BFAerror[2] = error[2];
				MINENERGY_BFAerror[3] = error[3];

				MINENERGY_BFA[2]->energy = calculateMonomersEnergy('B', monomerEnergy);
				MINENERGY_BFA[2]->stepNumber = enteringMCAnneal;
				MINENERGY_BFAenergy[2] = monomerEnergy[1];
				MINENERGY_BFAerror[4] = error[4];
				MINENERGY_BFAerror[5] = error[5];
				
				
				for(int i = 1; i <= sizeOfResidueArray; i++)
					MINENERGY_BFA[0]->res[i] = MINENERGY_BFA[1]->res[i] = MINENERGY_BFA[2]->res[i] = res[i];
			}

			//MIN RMSD given best folding array of first domains seq :
			if(error[2] < BFAerror[2])
			{
				double monomerEnergy[2];
				BFA[1]->energy = calculateMonomersEnergy('A', monomerEnergy);
				BFAenergy[1] = monomerEnergy[1];
				BFA[1]->stepNumber = enteringMCAnneal;
				BFAerror[2] = error[2];
				BFAerror[3] = error[3];
				for(int i = 1; i <= sizeOfResidueArray; i++)
					BFA[1]->res[i] = res[i];
			}
			//MIN RMSD given best folding array of second domains seq :
			if(error[4] < BFAerror[4])
			{
				double monomerEnergy[2];
				BFA[2]->energy = calculateMonomersEnergy('B', monomerEnergy);
				BFAenergy[2] = monomerEnergy[1];
				BFA[2]->stepNumber = enteringMCAnneal;
				BFAerror[4] = error[4];
				BFAerror[5] = error[5];
				for(int i = 1; i <= sizeOfResidueArray; i++)
					BFA[2]->res[i] = res[i];
			}
			if(error[0] <= ERROR_FPT_THRESHOLD)
			{
				BFA[0]->energy = energy;
				
				double monomerEnergy[2];
				calculateMonomersEnergy('D', monomerEnergy);
				BFAenergy[0] = monomerEnergy[1];
				
				BFA[0]->stepNumber = enteringMCAnneal;
				BFAerror[0] = error[0];
				BFAerror[1] = error[1];
				for(int i = 1; i <= sizeOfResidueArray; i++)
					BFA[0]->res[i] = res[i];
				firstPassageTime = true;
				return 1;
			}
			else if(error[0] < BFAerror[0])
			{
				BFA[0]->energy = energy;

				double monomerEnergy[2];
				calculateMonomersEnergy('D', monomerEnergy);
				BFAenergy[0] = monomerEnergy[1];

				BFA[0]->stepNumber = enteringMCAnneal;
				BFAerror[0] = error[0];
				BFAerror[1] = error[1];
				for(int i = 1; i <= sizeOfResidueArray; i++)
					BFA[0]->res[i] = res[i];
			}	
		}
	
		return 0;
	}
	else 
// 	minimal energy of sequence:
// 	1. by domain sequence (structure of domain given minimal energy of that domain) + minimal structure of whole seq
// 	2. by whole sequence (structure of domain given minimal energy of whole seq) + minimal structure of whole seq
//  BFA: 0 - dimer, 1 - monomer A, 2 - monomer B

	{
	
		double A_energy[2], B_energy[2], D_energy[2];
// 		cout<<"1 Got here!!!"<<endl;
		calculateMonomersEnergy('A', A_energy);
		calculateMonomersEnergy('B', B_energy);
		calculateMonomersEnergy('D', D_energy);
// 		cout<<"2 Got here!!!"<<endl;
		if(BFA[1]->energy > A_energy[1]) {
			BFA[1]->energy = A_energy[1];
			BFA[1]->stepNumber = enteringMCAnneal;
			for(int i = 1; i <= sizeOfResidueArray; i++)
				BFA[1]->res[i] = res[i];
		}
		
		if(BFA[2]->energy > B_energy[1]) {
			BFA[2]->energy = B_energy[1];
			BFA[2]->stepNumber = enteringMCAnneal;
			for(int i = 1; i <= sizeOfResidueArray; i++)
				BFA[2]->res[i] = res[i];
		}
		
		if(BFA[0]->energy > D_energy[1]) {
			BFA[0]->energy = D_energy[1];
			BFA[0]->stepNumber = enteringMCAnneal;
			for(int i = 1; i <= sizeOfResidueArray; i++)
				BFA[0]->res[i] = res[i];
		}
	}
	
	return 0;

}

int doubleDomain::initFoldingComplex()
{
	cout<<"doubleDomain::initFoldingComplex"<<endl;
	
	point zerop(0,0);
	energy = 0;
	
	firstPassageTime = false;
	Ck = ALPHA_UPPER_BOND;
	successCtr = 0;
	enteringMCAnneal = 0;
	successLocalConf = 0; 
	enterLocalConf = 1;

	int i, y, x;

	for(i = 1; i <= sizeOfResidueArray; i++)
		tmpArr[i] = zerop;
	
	for(y = 0; y < top_y; y++)
		for(x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
	
	for(i = 0; i < 3; i++)
	{
		BFA[i]->energy = 100;
		BFA[i]->stepNumber = 0;
		BFAerror[2*i] = 100;
		BFAerror[2*i + 1] = 100;
		BFAenergy[i] = 100;
		
		MINENERGY_BFA[i]->energy = 100;
		MINENERGY_BFA[i]->stepNumber = 0;
		MINENERGY_BFAerror[2*i] = 100;
		MINENERGY_BFAerror[2*i + 1] = 100;
		MINENERGY_BFAenergy[i] = 100;
		
		for(int j = 1; j <= sizeOfResidueArray; j++)
		{
			BFA[i]->res[j].position.x = j - 1;
			BFA[i]->res[j].position.y = sizeOfResidueArray/2;
			MINENERGY_BFA[i]->res[j].position.x = j - 1;
			MINENERGY_BFA[i]->res[j].position.y = sizeOfResidueArray/2;

		}
		
	}
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		res[i].position.x = i - 1;
		res[i].position.y = sizeOfResidueArray/2;
	}

	
		
	for(i = 1; i <= sizeOfResidueArray; i++)
		occupyPosition(i);
	return 0;

}
