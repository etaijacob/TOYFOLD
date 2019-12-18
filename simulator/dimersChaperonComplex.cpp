//dimersChaperonComplex.cpp

#include "dimersChaperonComplex.h"
#include "utilities.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

int dimersChaperonComplex::foldOneDomainInDimer
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   int *fromtoIn)
{
	
	cout<<"Dimers folding func"<<endl;
	
	initFoldingComplex();
	
	for(int i = 0; i < 4; i++)
	{
		fromto[i] = fromtoIn[i];
		cout<<fromto[i]<<" ";
	}
	cout<<endl;
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	char *hp;
	int linkerLength = fromto[2] - fromto[1]; 
	if( (hp = CfileHdlr.dimer_readTextStructure(sizeOfResidueArray, structure, linkerLength, configfileIndex))== 0)
	{
		cout<<"could not Get index: "<<configfileIndex<<endl;
		delete []structure;
		return 0;//exit(0);
	}
	
	UPDATE_PROTEIN_MODES(res)
	 		
	rmsd = new RMSD(this, sizeOfResidueArray, 0);
	rmsd->update(structure);
///////////////////////////////////////////////////////////////////////////////////
	char tmpstr[220], datafn[120];
// 	FILE *rmsd_all;
// 
// 	sprintf(datafn, "%s-f%f", "rmsd_allData", simulationFactor);
// 	//strcpy(datafn, "rmsd_mcs");
// 	CREATE_FILE(rmsd_all)
// 
// 	
// 	sprintf(datafn, "%s-f%f", "structure_min_rmsd", simulationFactor);
// 	sprintf(tmpstr, "%s%s-%d-%d.data", outputDatafileName, datafn, sizeOfResidueArray, configfileIndex);
// 	cout<<"calling resArr ctor"<<endl;
// 	residueArray residue2File(sizeOfResidueArray, tmpstr);	
// 	UPDATE_PROTEIN_MODES(residue2File.res)
// 	
// 	sprintf(datafn, "%s-f%f", "structure_min_energy", simulationFactor);
// 	sprintf(tmpstr, "%s%s-%d-%d.data", outputDatafileName, datafn, sizeOfResidueArray, configfileIndex);
// 	residueArray residue2FileEnergy(sizeOfResidueArray, tmpstr);	
// 	UPDATE_PROTEIN_MODES(residue2FileEnergy.res)
	
///////////////////////////////////////////////////////////////////////////////////
		
	cout<<endl<<"Begin folding:"<<endl;
	for(int m = 0; m < numOfSimulations; m++)
	{
		cout<<"Doing "<<m<<" run:"<<endl;
		firstPassageTime = false;
		initFoldingComplex();
		int bindTryCounter = 0;
		int r = 0;
		
		double itr = 0, alpha_itr = 0;
		bool proteinIsBinded = false;
		int releasedCtr = 0, bindedCtr = 0;
		
		for(int i = r; i < times; i++)
		{
			itr++;
			alpha_itr++;
			
			if(firstPassageTime)
				break;	
			
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
/*
		double error =
				rmsd->dimer_compute(bestFoldingArray, 
									fromto[0], fromto[1],
									fromto[2], fromto[3], ddd);

		double error = rmsd->compute(bestFoldingArray);
		*/
		//cout<<"Error: "<<error<<endl;
		//if(inChaperon)
			//cout<<"Protein in chaperon when terminates: \n";
		//cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
		//writeStructures2output();
		//cout<<"best folding Array: \n";
				

		CfileHdlr.writeStructure2output(sizeOfResidueArray, BFA[1]);
		CfileHdlr.writeStructure2output(sizeOfResidueArray, BFA[2]);
		
// 			residue2File = *BFA[0];
// 			residue2File.write();
// 			fprintf(rmsd_all, "D %d %f %f %f %f %d\n", 
// 					BFA[0]->stepNumber, 
// 					BFA[0]->energy, BFAenergy[0], 
// 					BFAerror[0], BFAerror[1],  
// 					bindTryCounter);
// 			fprintf(rmsd_all, "A %d %f %f %f %f\n", 
// 					BFA[1]->stepNumber, 
// 					BFA[1]->energy, BFAenergy[1], 
// 					BFAerror[2], BFAerror[3]);
// 			fprintf(rmsd_all, "B %d %f %f %f %f\n", 
// 					BFA[2]->stepNumber, 
// 					BFA[2]->energy, BFAenergy[2], 
// 					BFAerror[4], BFAerror[5]);
// 
// 			residue2FileEnergy = *MINENERGY_BFA[0];
// 			residue2FileEnergy.write();
// 			fprintf(rmsd_all, "MINIMAL ENERGY:\n");
// 			fprintf(rmsd_all, "D %d %f %f %f %f %d\n", 
// 					MINENERGY_BFA[0]->stepNumber, 
// 					MINENERGY_BFA[0]->energy, MINENERGY_BFAenergy[0], 
// 					MINENERGY_BFAerror[0], MINENERGY_BFAerror[1],  
// 					bindTryCounter);
// 			fprintf(rmsd_all, "A %d %f %f %f %f\n", 
// 					MINENERGY_BFA[1]->stepNumber, 
// 					MINENERGY_BFA[1]->energy, MINENERGY_BFAenergy[1], 
// 					MINENERGY_BFAerror[2], MINENERGY_BFAerror[3]);
// 			fprintf(rmsd_all, "B %d %f %f %f %f\n", 
// 					MINENERGY_BFA[2]->stepNumber, 
// 					MINENERGY_BFA[2]->energy, MINENERGY_BFAenergy[2], 
// 					MINENERGY_BFAerror[4], MINENERGY_BFAerror[5]);
			
			cout<<"D "<<BFA[0]->stepNumber<<" "<<BFA[0]->energy<<" "<<BFAenergy[0]<<" "<<\
					" "<<BFAerror[0]<<" "<<BFAerror[1]<<endl;//BFAerror[0] = error in abs of position, BFAerror[1] = error in abs of same position or not.
			cout<<"A "<<BFA[1]->stepNumber<<" "<<BFA[1]->energy<<" "<<BFAenergy[1]<<" "<<\
					" "<<BFAerror[2]<<" "<<BFAerror[3]<<endl;
			cout<<"B "<<BFA[2]->stepNumber<<" "<<BFA[2]->energy<<" "<<BFAenergy[2]<<" "<<\
					" "<<BFAerror[4]<<" "<<BFAerror[5]<<endl;
			printf("MINIMAL ENERGY:\n");
			printf("D %d %f %f %f %f\n", 
					MINENERGY_BFA[0]->stepNumber, 
					MINENERGY_BFA[0]->energy, MINENERGY_BFAenergy[0], 
					MINENERGY_BFAerror[0], MINENERGY_BFAerror[1]);
			printf("A %d %f %f %f %f\n", 
					MINENERGY_BFA[1]->stepNumber, 
					MINENERGY_BFA[1]->energy, MINENERGY_BFAenergy[1], 
					MINENERGY_BFAerror[2], MINENERGY_BFAerror[3]);
			printf("B %d %f %f %f %f\n", 
					MINENERGY_BFA[2]->stepNumber, 
					MINENERGY_BFA[2]->energy, MINENERGY_BFAenergy[2], 
					MINENERGY_BFAerror[4], MINENERGY_BFAerror[5]);

		//cout<<"foldInChaperonWithBindReleaseMechanism"<<endl;
	}
	
// 	fclose(rmsd_all);
	delete []structure;
	delete rmsd;
	//cout<<"finish configfileIndex: "<<configfileIndex<<endl;
	return 1;
}



int dimersChaperonComplex::foldDimer
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   int *fromtoIn)
{
	
	cout<<"Dimers folding func"<<endl;
	
	initFoldingComplex();
	
	for(int i = 0; i < 4; i++)
	{
		fromto[i] = fromtoIn[i];
		cout<<fromto[i]<<" ";
	}
	cout<<endl;
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	char *hp;
	int linkerLength = fromto[2] - fromto[1]; 
	if( (hp = CfileHdlr.dimer_readTextStructure(sizeOfResidueArray, structure, linkerLength, configfileIndex))== 0)
	{
		cout<<"could not Get index: "<<configfileIndex<<endl;
		delete []structure;
		return 0;//exit(0);
	}
	
	UPDATE_PROTEIN_MODES(res)
	 		
	rmsd = new RMSD(this, sizeOfResidueArray, 0);
	rmsd->update(structure);
///////////////////////////////////////////////////////////////////////////////////
	char tmpstr[220], datafn[120];
// 	FILE *rmsd_all;
// 
// 	sprintf(datafn, "%s-f%f", "rmsd_allData", simulationFactor);
// 	//strcpy(datafn, "rmsd_mcs");
// 	CREATE_FILE(rmsd_all)
// 
// 	
// 	sprintf(datafn, "%s-f%f", "structure_min_rmsd", simulationFactor);
// 	sprintf(tmpstr, "%s%s-%d-%d.data", outputDatafileName, datafn, sizeOfResidueArray, configfileIndex);
// 	cout<<"calling resArr ctor"<<endl;
// 	residueArray residue2File(sizeOfResidueArray, tmpstr);	
// 	UPDATE_PROTEIN_MODES(residue2File.res)
// 	
// 	sprintf(datafn, "%s-f%f", "structure_min_energy", simulationFactor);
// 	sprintf(tmpstr, "%s%s-%d-%d.data", outputDatafileName, datafn, sizeOfResidueArray, configfileIndex);
// 	residueArray residue2FileEnergy(sizeOfResidueArray, tmpstr);	
// 	UPDATE_PROTEIN_MODES(residue2FileEnergy.res)
	
///////////////////////////////////////////////////////////////////////////////////
		
	cout<<endl<<"Begin folding:"<<endl;
	for(int m = 0; m < numOfSimulations; m++)
	{
		cout<<"Doing "<<m<<" run:"<<endl;
		firstPassageTime = false;
		initFoldingComplex();
		int bindTryCounter = 0;
		int r = 0;
		
		double itr = 0, alpha_itr = 0;
		bool proteinIsBinded = false;
		int releasedCtr = 0, bindedCtr = 0;
		
		for(int i = r; i < times; i++)
		{
			itr++;
			alpha_itr++;
			
			if(firstPassageTime)
				break;	
			
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
/*
		double error =
				rmsd->dimer_compute(bestFoldingArray, 
									fromto[0], fromto[1],
									fromto[2], fromto[3], ddd);

		double error = rmsd->compute(bestFoldingArray);
		*/
		//cout<<"Error: "<<error<<endl;
		//if(inChaperon)
			//cout<<"Protein in chaperon when terminates: \n";
		//cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
		//writeStructures2output();
		//cout<<"best folding Array: \n";
				

		CfileHdlr.writeStructure2output(sizeOfResidueArray, BFA[1]);
		CfileHdlr.writeStructure2output(sizeOfResidueArray, BFA[2]);
		
// 			residue2File = *BFA[0];
// 			residue2File.write();
// 			fprintf(rmsd_all, "D %d %f %f %f %f %d\n", 
// 					BFA[0]->stepNumber, 
// 					BFA[0]->energy, BFAenergy[0], 
// 					BFAerror[0], BFAerror[1],  
// 					bindTryCounter);
// 			fprintf(rmsd_all, "A %d %f %f %f %f\n", 
// 					BFA[1]->stepNumber, 
// 					BFA[1]->energy, BFAenergy[1], 
// 					BFAerror[2], BFAerror[3]);
// 			fprintf(rmsd_all, "B %d %f %f %f %f\n", 
// 					BFA[2]->stepNumber, 
// 					BFA[2]->energy, BFAenergy[2], 
// 					BFAerror[4], BFAerror[5]);
// 
// 			residue2FileEnergy = *MINENERGY_BFA[0];
// 			residue2FileEnergy.write();
// 			fprintf(rmsd_all, "MINIMAL ENERGY:\n");
// 			fprintf(rmsd_all, "D %d %f %f %f %f %d\n", 
// 					MINENERGY_BFA[0]->stepNumber, 
// 					MINENERGY_BFA[0]->energy, MINENERGY_BFAenergy[0], 
// 					MINENERGY_BFAerror[0], MINENERGY_BFAerror[1],  
// 					bindTryCounter);
// 			fprintf(rmsd_all, "A %d %f %f %f %f\n", 
// 					MINENERGY_BFA[1]->stepNumber, 
// 					MINENERGY_BFA[1]->energy, MINENERGY_BFAenergy[1], 
// 					MINENERGY_BFAerror[2], MINENERGY_BFAerror[3]);
// 			fprintf(rmsd_all, "B %d %f %f %f %f\n", 
// 					MINENERGY_BFA[2]->stepNumber, 
// 					MINENERGY_BFA[2]->energy, MINENERGY_BFAenergy[2], 
// 					MINENERGY_BFAerror[4], MINENERGY_BFAerror[5]);
			
			cout<<"D "<<BFA[0]->stepNumber<<" "<<BFA[0]->energy<<" "<<BFAenergy[0]<<" "<<\
					" "<<BFAerror[0]<<" "<<BFAerror[1]<<endl;//BFAerror[0] = error in abs of position, BFAerror[1] = error in abs of same position or not.
			cout<<"A "<<BFA[1]->stepNumber<<" "<<BFA[1]->energy<<" "<<BFAenergy[1]<<" "<<\
					" "<<BFAerror[2]<<" "<<BFAerror[3]<<endl;
			cout<<"B "<<BFA[2]->stepNumber<<" "<<BFA[2]->energy<<" "<<BFAenergy[2]<<" "<<\
					" "<<BFAerror[4]<<" "<<BFAerror[5]<<endl;
			printf("MINIMAL ENERGY:\n");
			printf("D %d %f %f %f %f\n", 
					MINENERGY_BFA[0]->stepNumber, 
					MINENERGY_BFA[0]->energy, MINENERGY_BFAenergy[0], 
					MINENERGY_BFAerror[0], MINENERGY_BFAerror[1]);
			printf("A %d %f %f %f %f\n", 
					MINENERGY_BFA[1]->stepNumber, 
					MINENERGY_BFA[1]->energy, MINENERGY_BFAenergy[1], 
					MINENERGY_BFAerror[2], MINENERGY_BFAerror[3]);
			printf("B %d %f %f %f %f\n", 
					MINENERGY_BFA[2]->stepNumber, 
					MINENERGY_BFA[2]->energy, MINENERGY_BFAenergy[2], 
					MINENERGY_BFAerror[4], MINENERGY_BFAerror[5]);

		//cout<<"foldInChaperonWithBindReleaseMechanism"<<endl;
	}
	
// 	fclose(rmsd_all);
	delete []structure;
	delete rmsd;
	//cout<<"finish configfileIndex: "<<configfileIndex<<endl;
	return 1;
}

double dimersChaperonComplex::getEnergyValue(int x, int y, int i)
{
	//cout<<boolMatrix[y][x]<<" gev"<<endl;
	if( (boolMatrix[y][x] > 0)&&
	    (  ((boolMatrix[y][x] - i) >  2)  ||
	       ((boolMatrix[y][x] - i) < -2)  ||
		   (boolMatrix[y][x] > sizeOfResidueArray)     )  )
	{
#if 0 //only when considering V21 with no interaction between chaperone and protein.		
		if(boolMatrix[y][x] > sizeOfResidueArray && 
		   chap->res[boolMatrix[y][x] - sizeOfResidueArray].mode == 1 &&
		   res[i].mode == 1)
		{
			return 0.0;		
		}
		else
		{
			if(boolMatrix[y][x] > sizeOfResidueArray)
				return energyMatrix[chap->res[boolMatrix[y][x] -
						sizeOfResidueArray].mode][res[i].mode] + alphaE;
			else
				return energyMatrix[res[boolMatrix[y][x]].mode][res[i].mode] + alphaE;	
		}
#endif
		if(boolMatrix[y][x] > sizeOfResidueArray)
			return energyMatrix[chap->res[boolMatrix[y][x] -
						sizeOfResidueArray].mode][res[i].mode] + alphaE;
		else
			return energyMatrix[res[boolMatrix[y][x]].mode][res[i].mode] + alphaE;	

	}
	return 0.0;
/*		if( (boolMatrix[y][x] > 0)&&
	    ( ((boolMatrix[y][x] - i) > 2)||
	      ((boolMatrix[y][x] - i) < -2) ) )
		return energyMatrix[res[boolMatrix[y][x]].mode][res[i].mode] + alphaE;

	return 0.0;
*/
}

dimersChaperonComplex::dimersChaperonComplex(int length, char* confFileName,
					     int findex, char *cname, int isSmart):
proteinChaperonComplex(length, confFileName, findex, cname, isSmart)
{
	cout<<"dimersChaperonComplex ctor 1"<<endl;
	
	for(int i = 0; i < 3; i++)
	{
		BFA[i] = new foldingArray(length);
		MINENERGY_BFA[i] = new foldingArray(length);
	}
}

dimersChaperonComplex::~dimersChaperonComplex()
{
	cout<<"~dimersChaperonComplex"<<endl;
	for(int i = 0; i < 3; i++)
	{
		if(BFA[i])
			delete BFA[i];
		if(MINENERGY_BFA[i])
			delete MINENERGY_BFA[i];
	}
}
double dimersChaperonComplex::calculateMonomersEnergy(char which, double *energy)
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
					to = sizeOfResidueArray + 1;
					break;
	}
		
	
	for(i = from; i < to; i++)
	{	
			int x = res[i].position.x;
			int y = res[i].position.y;

			if(y < top_y - 1)
			{
				energy[0] += getEnergyValue(x, y+1, i);
				energy[1] += getEnergyValueWithoutChaperon(x, y+1, i);
			}
			if(y > buttom_y)
			{
				energy[0] += getEnergyValue(x, y-1, i);
				energy[1] += getEnergyValueWithoutChaperon(x, y-1, i);
			}
			if(x < right_x -1)
			{
				energy[0] += getEnergyValue(x+1, y, i);
				energy[1] += getEnergyValueWithoutChaperon(x+1, y, i);
			}
			if(x > left_x)
			{
				energy[0] += getEnergyValue(x-1, y, i);
				energy[1] += getEnergyValueWithoutChaperon(x-1, y, i);
			}
		
	}//end for loop
		
	//Energy will always be double than should be	
	energy[0] /= 2;
	energy[1] /= 2;
	
	return (energy[0]);
}


int dimersChaperonComplex::modifyBestFoldingArray()
{
	//cout<<"Dimers modifyBestFoldingArray func"<<endl;
	if(rmsd) 
	{
		//cout<<"new modifyBestFoldingArray "<<endl;	
		//if(BFA[0]->energy + ENERGY_BACK_GAP > energy)
		{
			double error[6];
			rmsd->dimer_compute(*this, 
								fromto[0], fromto[1],
								fromto[2], fromto[3], error);
		
			//0, 1 - global
			//2, 3 - monomer A
			//4, 5 - monomer B
			
			//MIN ENERGY:
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

			//MIN RMSD:
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
	else //not FPT technic
	{
		if(BFA[0]->energy > energy)
		{
			BFA[0]->energy = energy;

			double monomerEnergy[2];
			calculateMonomersEnergy('D', monomerEnergy);
			BFAenergy[0] = monomerEnergy[1];

			BFA[0]->stepNumber = enteringMCAnneal;
			for(int i = 1; i <= sizeOfResidueArray; i++)
				BFA[0]->res[i] = res[i];
		
		}
	}
	return 0;

}

int dimersChaperonComplex::initFoldingComplex()
{
	cout<<"dimersChaperonComplex::initFoldingComplex"<<endl;
	
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

int dimersChaperonComplex::foldInChaperonWithBindReleaseMechanism
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   int *fromtoIn,
										   bool inChaperon,
										   bool dynamic,
										   int bindInterval,
		                   int releaseInterval,
		                   double energyThreshold,
										   int addedX,
										   int addedY)
{
	
	cout<<"Dimers foldInChap func"<<endl;
	added_confinedX = sqrt((double)sizeOfResidueArray) + addedX;
	added_confinedY = sqrt((double)sizeOfResidueArray) + addedY;
	cout<<"added_confinedX: "<<added_confinedX<<endl;
	cout<<"added_confinedY: "<<added_confinedY<<endl;
	
	initFoldingComplex();
	
	for(int i = 0; i < 4; i++)
	{
		fromto[i] = fromtoIn[i];
		cout<<fromto[i]<<" ";
	}
	cout<<endl;
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	char *hp;
	int linkerLength = fromto[2] - fromto[1]; 
	if( (hp = CfileHdlr.dimer_readTextStructure(sizeOfResidueArray, structure, linkerLength, configfileIndex))== 0)
	{
		cout<<"could not Get index: "<<configfileIndex<<endl;
		delete []structure;
		return 0;//exit(0);
	}
	
	UPDATE_PROTEIN_MODES(res)
	 		
	rmsd = new RMSD(this, sizeOfResidueArray, 0);
	rmsd->update(structure);
///////////////////////////////////////////////////////////////////////////////////
	char tmpstr[220], datafn[120];
	FILE *rmsd_all;

	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "rmsd_allData", simulationFactor, energyThreshold, 
												  releaseInterval, bindInterval);
	//strcpy(datafn, "rmsd_mcs");
	CREATE_FILE(rmsd_all)

	
	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "structure_min_rmsd", simulationFactor, energyThreshold, 
												   releaseInterval, bindInterval);
	sprintf(tmpstr, "%s%s-%d-%d.data", outputDatafileName, datafn, sizeOfResidueArray, configfileIndex);
	cout<<"calling resArr ctor"<<endl;
	residueArray residue2File(sizeOfResidueArray, tmpstr);	
	UPDATE_PROTEIN_MODES(residue2File.res)
	
	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "structure_min_energy", simulationFactor, energyThreshold, 
												   releaseInterval, bindInterval);
	sprintf(tmpstr, "%s%s-%d-%d.data", outputDatafileName, datafn, sizeOfResidueArray, configfileIndex);
	residueArray residue2FileEnergy(sizeOfResidueArray, tmpstr);	
	UPDATE_PROTEIN_MODES(residue2FileEnergy.res)
	
///////////////////////////////////////////////////////////////////////////////////
		
	cout<<endl<<"Begin folding:"<<endl;
	for(int m = 0; m < numOfSimulations; m++)
	{
		cout<<"Doing "<<m<<" run:"<<endl;
		firstPassageTime = false;
		initFoldingComplex();
		int bindTryCounter = 0;
		int r = 0;
		if(inChaperon)
		{
			for(r = 0; r < times; r++)
			{
				foldOnce();
				point pdxdy = getMin_dx_dy();
				if( ((pdxdy.x + 1) <= added_confinedX) &&
					((pdxdy.y + 1) <= added_confinedY) )
					break;
			}
			
			if(r == times)
			{
				cout<<"Could not fold to size: ("<<added_confinedX<<", "<<added_confinedY<<")\n";
				/*
				double error =
				rmsd->dimer_compute(BFA, 
									fromto[0], fromto[1],
									fromto[2], fromto[3], ddd);
				*/
				cout<<"Protein in chaperon when terminates: \n";
				cout<<"FPT: "<<BFA[0]->stepNumber<<endl;	
				//writeStructures2output();
				//cout<<"best folding Array: \n";
				//CfileHdlr.writeStructure2output(sizeOfResidueArray, &bestFoldingArray);
				
				residue2File = *BFA[0];
				residue2File.write();
				fprintf(rmsd_all, "MINIMAL RMSD:\n");
				fprintf(rmsd_all, "D %d %f %f %f %f %d\n", 
						BFA[0]->stepNumber, 
						BFA[0]->energy, BFAenergy[0], 
						BFAerror[0], BFAerror[1],  
						bindTryCounter);
				fprintf(rmsd_all, "A %d %f %f %f %f\n", 
						BFA[1]->stepNumber, 
						BFA[1]->energy, BFAenergy[1], 
						BFAerror[2], BFAerror[3]);
				fprintf(rmsd_all, "B %d %f %f %f %f\n", 
						BFA[2]->stepNumber, 
						BFA[2]->energy, BFAenergy[2], 
						BFAerror[4], BFAerror[5]);

				residue2FileEnergy = *MINENERGY_BFA[0];
				residue2FileEnergy.write();
				fprintf(rmsd_all, "MINIMAL ENERGY:\n");
				fprintf(rmsd_all, "D %d %f %f %f %f %d\n", 
						MINENERGY_BFA[0]->stepNumber, 
						MINENERGY_BFA[0]->energy, MINENERGY_BFAenergy[0], 
						MINENERGY_BFAerror[0], MINENERGY_BFAerror[1],  
						bindTryCounter);
				fprintf(rmsd_all, "A %d %f %f %f %f\n", 
						MINENERGY_BFA[1]->stepNumber, 
						MINENERGY_BFA[1]->energy, MINENERGY_BFAenergy[1], 
						MINENERGY_BFAerror[2], MINENERGY_BFAerror[3]);
				fprintf(rmsd_all, "B %d %f %f %f %f\n", 
						MINENERGY_BFA[2]->stepNumber, 
						MINENERGY_BFA[2]->energy, MINENERGY_BFAenergy[2], 
						MINENERGY_BFAerror[4], MINENERGY_BFAerror[5]);
				
				continue;
			}
			//cout<<"Energy Before Chaperon: "<<calculateEnergy()<<endl;
			//cout<<"-----------------------------------------------------\n";
	 		
		}
		
		double itr = 0, alpha_itr = 0;
		bool proteinIsBinded = false;
		int releasedCtr = 0, bindedCtr = 0;
		
		for(int i = r; i < times; i++)
		{
			if(inChaperon)
			{
				if( !proteinIsBinded && (releasedCtr + 1)%bindInterval == 0 )
				{
					for(; i < times; i++)
					{
						foldOnce();
						if(firstPassageTime)
							break;
						point pdxdy = getMin_dx_dy();
						if( ((pdxdy.x + 1) <= added_confinedX) &&
						((pdxdy.y + 1) <= added_confinedY) )
							break;
						itr++;
						alpha_itr++;
				
						if(alpha_itr == ALPHA_ITR)
						{
							alpha_itr = 0;
				
							if(Ck < ALPHA_LOWER_BOND)
								Ck = ALPHA_LOWER_BOND;
							else
								Ck *= ALPHA;	
						}
						
					}
					if(i < times)
					{
						int rslt = cageProteinInChaperon(energyThreshold);
						bindTryCounter++;
						if(rslt == 0)
						{
							cout<<"-----------------Could not cage protein------------------\n";
							
							for(int mm = 0; mm < 1000; mm++)
								foldOnce();	
							i += 1000;
							cout<<"try again"<<endl;
							//fclose(rmsd_all);
							//return 1;
						}
						else if(rslt == 1)
						{
							//cout<<"protein is binded\n";
							//cout<<"Mode: "<<chap->res[1].mode<<endl;
							bindedCtr = 0;
							proteinIsBinded = true;	
							//writeStructures2output();
						}
						else
							releasedCtr = 0;
					}
						
				}
				
				if(proteinIsBinded)
				{
					
					if(dynamic)
						chap->step();

					bindedCtr++;
					if( (bindedCtr + 1)%releaseInterval == 0 )
					{
						cout<<"Protein in chaperon before release: \n";
						writeStructures2output();
						releaseProteinFromChaperon();	
						proteinIsBinded = false;
						releasedCtr = 0;
					}
				}
				else
					releasedCtr++;
			}//endif - in chaperon
			itr++;
			alpha_itr++;
			
			if(firstPassageTime)
				break;	
			
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
/*
		double error =
				rmsd->dimer_compute(bestFoldingArray, 
									fromto[0], fromto[1],
									fromto[2], fromto[3], ddd);

		double error = rmsd->compute(bestFoldingArray);
		*/
		//cout<<"Error: "<<error<<endl;
		//if(inChaperon)
			//cout<<"Protein in chaperon when terminates: \n";
		//cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
		//writeStructures2output();
		//cout<<"best folding Array: \n";
				

		CfileHdlr.writeStructure2output(sizeOfResidueArray, BFA[1]);
		CfileHdlr.writeStructure2output(sizeOfResidueArray, BFA[2]);
		
			residue2File = *BFA[0];
			residue2File.write();
			fprintf(rmsd_all, "D %d %f %f %f %f %d\n", 
					BFA[0]->stepNumber, 
					BFA[0]->energy, BFAenergy[0], 
					BFAerror[0], BFAerror[1],  
					bindTryCounter);
			fprintf(rmsd_all, "A %d %f %f %f %f\n", 
					BFA[1]->stepNumber, 
					BFA[1]->energy, BFAenergy[1], 
					BFAerror[2], BFAerror[3]);
			fprintf(rmsd_all, "B %d %f %f %f %f\n", 
					BFA[2]->stepNumber, 
					BFA[2]->energy, BFAenergy[2], 
					BFAerror[4], BFAerror[5]);

			residue2FileEnergy = *MINENERGY_BFA[0];
			residue2FileEnergy.write();
			fprintf(rmsd_all, "MINIMAL ENERGY:\n");
			fprintf(rmsd_all, "D %d %f %f %f %f %d\n", 
					MINENERGY_BFA[0]->stepNumber, 
					MINENERGY_BFA[0]->energy, MINENERGY_BFAenergy[0], 
					MINENERGY_BFAerror[0], MINENERGY_BFAerror[1],  
					bindTryCounter);
			fprintf(rmsd_all, "A %d %f %f %f %f\n", 
					MINENERGY_BFA[1]->stepNumber, 
					MINENERGY_BFA[1]->energy, MINENERGY_BFAenergy[1], 
					MINENERGY_BFAerror[2], MINENERGY_BFAerror[3]);
			fprintf(rmsd_all, "B %d %f %f %f %f\n", 
					MINENERGY_BFA[2]->stepNumber, 
					MINENERGY_BFA[2]->energy, MINENERGY_BFAenergy[2], 
					MINENERGY_BFAerror[4], MINENERGY_BFAerror[5]);
			
			cout<<"D "<<BFA[0]->stepNumber<<" "<<BFA[0]->energy<<" "<<BFAenergy[0]<<" "<<\
					" "<<BFAerror[0]<<" "<<BFAerror[1]<<" "<<bindTryCounter<<endl;
			cout<<"A "<<BFA[1]->stepNumber<<" "<<BFA[1]->energy<<" "<<BFAenergy[1]<<" "<<\
					" "<<BFAerror[2]<<" "<<BFAerror[3]<<" "<<bindTryCounter<<endl;
			cout<<"B "<<BFA[2]->stepNumber<<" "<<BFA[2]->energy<<" "<<BFAenergy[2]<<" "<<\
					" "<<BFAerror[4]<<" "<<BFAerror[5]<<" "<<bindTryCounter<<endl;


		//cout<<"foldInChaperonWithBindReleaseMechanism"<<endl;
	}
	
	fclose(rmsd_all);
	delete []structure;
	delete rmsd;
	//cout<<"finish configfileIndex: "<<configfileIndex<<endl;
	return 1;
}
