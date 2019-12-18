//proteinChaperonComplex.cpp

#include "proteinChaperonComplex.h"
#include "utilities.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>


double proteinChaperonComplex::getEnergyValueWithoutChaperon(int x, int y, int i)
{
	if( (boolMatrix[y][x] > 0)&&
	    (  ((boolMatrix[y][x] - i) >  2)  ||
	       ((boolMatrix[y][x] - i) < -2)  ||
		   (boolMatrix[y][x] > sizeOfResidueArray)     )  )
	{		
		if(boolMatrix[y][x] > sizeOfResidueArray)
			return 0;		
		else
			return energyMatrix[res[boolMatrix[y][x]].mode][res[i].mode] + alphaE;	
	}
	return 0.0;
	
}

double proteinChaperonComplex::calculateEnergyWithoutChaperon()
{
	double energy = 0;

	int i;
	
	
	for(i = 1; i <= sizeOfResidueArray; i++)
	{	
			int x = res[i].position.x;
			int y = res[i].position.y;

			if(y < top_y - 1)
				energy += getEnergyValueWithoutChaperon(x, y+1, i);
			if(y > buttom_y)
				energy += getEnergyValueWithoutChaperon(x, y-1, i);
			if(x < right_x -1)
				energy += getEnergyValueWithoutChaperon(x+1, y, i);
			if(x > left_x)
				energy += getEnergyValueWithoutChaperon(x-1, y, i);
		
	}//end for loop
		
	//Energy will always be double than should be	
	return (energy/2);
}

/*
int proteinChaperonComplex::modifyBestFoldingArray()
{
	double tmpEnergy = calculateEnergyWithoutChaperon();
	if(bestFoldingArray.energy > tmpEnergy)
	{
		bestFoldingArray.energy = tmpEnergy;
		bestFoldingArray.stepNumber = enteringMCAnneal;
		for(int i = 1; i <= sizeOfResidueArray; i++)
			bestFoldingArray.res[i] = res[i];
		
	}
	
	return 0;

}
*/



double proteinChaperonComplex::getEnergyValue(int x, int y, int i)
{
	if( (boolMatrix[y][x] > 0)&&
	    ( ((boolMatrix[y][x] - i) > 2)||
	      ((boolMatrix[y][x] - i) < -2) ) )
	{
		
		if(boolMatrix[y][x] > sizeOfResidueArray)
#if USE_CHAPERON_WITH_POTENTIAL
			return energyMatrix[chap->res[boolMatrix[y][x] - sizeOfResidueArray].mode][res[i].mode] + alphaE;
#else
			return 0;
#endif		
		else
			return energyMatrix[res[boolMatrix[y][x]].mode][res[i].mode] + alphaE;	
	}
	return 0.0;
	
}

proteinChaperonComplex::proteinChaperonComplex(int length, char* confFileName, int findex, char *cname, int isSmart):
foldingComplex(length, confFileName),
useZeroPotential(true)
{
	cout<<"proteinChaperonComplex ctor 1"<<endl;
	added_confinedX = sqrt((double)length) + 2;
	added_confinedY = sqrt((double)length) + 2;
	firstPassageTime = false;
	if(isSmart)
		chap = new smartChaperone(findex, cname);
	else
		chap = new chaperon(findex, cname);	
}

proteinChaperonComplex::proteinChaperonComplex(char *name, char* confFileName, int findex, char *cname, int isSmart):
foldingComplex(name, confFileName),
useZeroPotential(true)
{
	cout<<"proteinChaperonComplex ctor 2"<<endl;
	firstPassageTime = false;
	if(isSmart)
		chap = new smartChaperone(findex, cname);
	else
		chap = new chaperon(findex, cname);	
	
}

proteinChaperonComplex::proteinChaperonComplex(int length, char *name, char* confFileName, int findex, char *cname, int isSmart):
foldingComplex(length, name, confFileName),
useZeroPotential(true)		
{
	cout<<"proteinChaperonComplex ctor 3"<<endl;
	firstPassageTime = false;
	if(isSmart)
		chap = new smartChaperone(findex, cname);
	else
		chap = new chaperon(findex, cname);	

}

int proteinChaperonComplex::releaseProteinFromChaperon()
{
	for(int y = 0; y < top_y; y++)
		for(int x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
		
	point minProtein = getMin_XY();
	point dxdy = getMin_dx_dy();
	
	int dx = (right_x + dxdy.x)/2 - minProtein.x - dxdy.x;
	int dy = (top_y + dxdy.y)/2 - minProtein.y - dxdy.y;
		
	transformProtein(dx, dy);
	energy = calculateEnergy();
	chap->init();
	//cout<<"Energy After Chaperon Release: "<<energy<<endl;
	//cout<<"----------------------------------------------\n";
	return 0;
	

	return 1;
}
int proteinChaperonComplex::cageProteinInChaperon(double energyThreshold)
{
	chap->init();
	point min = chap->getMin_XY();
	point width = chap->getMin_dx_dy();
	
	point dxdy = getMin_dx_dy();

	if( (width.y - dxdy.y) < 0 || (width.x - dxdy.x) < 0 )
		return 0;

	double currentEnergy = calculateEnergy();
	//put the chaperon in the middle of the surface:
	int dx = (right_x + width.x)/2 - min.x - width.x;
	int dy = (top_y + width.y)/2 - min.y - width.y;
	/*
	cout<<"dx:"<<dx<<" dy: "<<dy<<endl;
	cout<<"Min: "<<min<<endl;
	cout<<"Width: "<<width<<endl;
	cout<<"Right_X: "<<right_x<<endl;
	
	cout<<"pos before: \n";
	*/
	for(int i = 1; i <= chap->sizeOfResidueArray; i++)
	{
		//cout<<chap->res[i].position<<endl;
		chap->res[i].position.x += dx;
		chap->res[i].position.y += dy;
	}
	
	for(int y = 0; y < top_y; y++)
		for(int x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
	

	for(int i = 1; i <= chap->sizeOfResidueArray; i++)
		occupyChaperonPosition(i);
	//exit(0);
	
	int ylimit = (width.y - dxdy.y - 2);
	int xlimit = (width.x - dxdy.x - 2);
	
	min = chap->getMin_XY();
	point minProtein = getMin_XY();
	point startp;
	startp.x = min.x - minProtein.x + 1;
	startp.y = min.y - minProtein.y + 1;
	
	
	
	bool cont = true;
	for(int y = startp.y; cont && y <= ylimit + startp.y; y++)
		for(int x = startp.x; x <= xlimit + startp.x; x++)
			if(transformProtein(x, y))
			{
				cont = false;
				break;
			}
			
	if(cont == true)
	{
		for(int y = 0; y < top_y; y++)
			for(int x = 0; x < right_x; x++)
				boolMatrix[y][x] &= 0;
		
		int dx = (right_x + dxdy.x)/2 - minProtein.x - dxdy.x;
		int dy = (top_y + dxdy.y)/2 - minProtein.y - dxdy.y;
		
		transformProtein(dx, dy);
		cout<<"Could not cage protein with chaperon.\nThe protein structure:\n";
		writeStructures2output();
		cout<<"----------------------------------------------\n";
		return 0;
	}

	double tmpEnergy = calculateEnergy();
	if( (tmpEnergy - currentEnergy) > energyThreshold )
	{
		for(int y = 0; y < top_y; y++)
			for(int x = 0; x < right_x; x++)
				boolMatrix[y][x] &= 0;
		
		int dx = (right_x + dxdy.x)/2 - minProtein.x - dxdy.x;
		int dy = (top_y + dxdy.y)/2 - minProtein.y - dxdy.y;
		
		transformProtein(dx, dy);
		cout<<"The change in energy level does not exceed threshold:\n"\
				<<(tmpEnergy -currentEnergy)<<endl;
		//writeStructures2output();
		//cout<<"----------------------------------------------\n";
		return 2;
	}		
	//cout<<"Protein in chaperon when begins: \n";	
	//writeStructures2output();	
	
	//bestFoldingArray.energy = 0;
	//bestFoldingArray.stepNumber = 0;
	cout<<"SUCCESS IN CAGING: "<<(tmpEnergy -currentEnergy)<<"\n";
	if(smartChaperone *sc = dynamic_cast<smartChaperone*>(chap))
		sc->init(this);

	return 1;
}

int proteinChaperonComplex::cageProteinInChaperon()
{
	point max;
	max = chap->getMax_XY();
	
	int dx = right_x - max.x - 1;
	int dy = top_y - max.y - 1;
	
	
	for(int i = 1; i <= chap->sizeOfResidueArray; i++)
	{
		chap->res[i].position.x += dx;
		chap->res[i].position.y += dy;
	}
	
	for(int y = 0; y < top_y; y++)
		for(int x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
	
	//bestFoldingArray.energy = 0;
	//bestFoldingArray.stepNumber = 0;

	for(int i = 1; i <= chap->sizeOfResidueArray; i++)
		occupyChaperonPosition(i);

	point dxdy = getMin_dx_dy();
	point chapd = chap->getMin_dx_dy();

	if( (chapd.y - dxdy.y) < 0 || (chapd.x - dxdy.x) < 0 )
		return 0;
	
	int ylimit = top_y - 2 - (chapd.y - dxdy.y - 2);
	int xlimit = right_x - 2 - (chapd.x - dxdy.x - 2);
	max = getMax_XY();
	
	bool cont = true;
	for(int y = top_y - 2; cont && y >= ylimit; y--)
		for(int x = right_x - 2; x >= xlimit; x--)
			if(transformProtein(x - max.x, y - max.y))
			{
				cont = false;
				break;
			}
	cout<<"Protein in chaperon when begins: \n";	
	writeStructures2output();
	if(smartChaperone *sc = dynamic_cast<smartChaperone*>(chap))
		sc->init(this);
	
	return 1;
}

int proteinChaperonComplex::transformProtein(int dx, int dy)
{
	for(int i = 1; i <= sizeOfResidueArray; i++)
		if(!isVacant(res[i].position.x + dx, res[i].position.y + dy))
			return 0;
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		res[i].position.x += dx;
		res[i].position.y += dy;
		occupyPosition(i);
	}
	return 1;
}	
	 
void proteinChaperonComplex::occupyChaperonPosition(int residueArrayIndex)
{
	int y = chap->res[residueArrayIndex].position.y;
	int x = chap->res[residueArrayIndex].position.x;
	//cout<<"pos: "<<x<<" "<<y<<endl;
	boolMatrix[y][x] = residueArrayIndex + sizeOfResidueArray;
}

int proteinChaperonComplex::foldInChaperon(double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   bool inChaperon,
										   bool dynamic)
{
	initFoldingComplex();
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	char *hp;
	if( (hp = CfileHdlr.readTextStructure(sizeOfResidueArray, structure, configfileIndex)) == 0)
	{
		cout<<"could not Get index: "<<configfileIndex<<endl;
		delete []structure;
		return 0;//exit(0);
	}
	
	UPDATE_PROTEIN_MODES(res)
	 		
	RMSD rmsd(this, sizeOfResidueArray, 0);
	rmsd.update(structure);
///////////////////////////////////////////////////////////////////////////////////
	char tmpstr[120], datafn[120];
	FILE *rmsd_mcs, *rmsd_energy;

	strcpy(datafn, "rmsd_mcs");
	CREATE_FILE(rmsd_mcs)

	
	strcpy(datafn, "rmsd_energy");
	CREATE_FILE(rmsd_energy)
	
	
	strcpy(datafn, "structure");
	sprintf(tmpstr, "%s/%s-%d-%d.data", outputDatafileName, datafn, sizeOfResidueArray, configfileIndex);
	
	residueArray residue2File(sizeOfResidueArray, tmpstr);	
	UPDATE_PROTEIN_MODES(residue2File.res)
	
///////////////////////////////////////////////////////////////////////////////////
		
	cout<<"Begin folding:\n";
	for(int m = 0; m < numOfSimulations; m++)
	{
		initFoldingComplex();
		
		if(inChaperon)
		{
			int r;
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
				return 0;
			}
			cout<<"Energy Before Chaperon: "<<calculateEnergy()<<endl;
	
			if(cageProteinInChaperon(0) == 0)
			{
				cout<<"-----------------Could not cage protein------------------\n";
				fclose(rmsd_mcs);
				fclose(rmsd_energy);

				return 1;
			}
 		
			energy = calculateEnergy();
			cout<<"Energy After Chaperon: "<<energy<<endl;
		
			//bestFoldingArray.energy = energy;
			//bestFoldingArray.stepNumber = enteringMCAnneal;
			//for(int i = 1; i <= sizeOfResidueArray; i++)
			//	bestFoldingArray.res[i] = res[i];
		}
		
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
			if(dynamic)
				chap->step();
				
		}

	
		double error = rmsd.compute(bestFoldingArray);
		cout<<"Error: "<<error<<endl;
		cout<<"Protein in chaperon when terminates: \n";
		cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
		writeStructures2output();
		cout<<"best folding Array: \n";
		CfileHdlr.writeStructure2output(sizeOfResidueArray, &bestFoldingArray);
		
		residue2File = bestFoldingArray;
		residue2File.write();
		fprintf(rmsd_mcs, "%d %f\n", bestFoldingArray.stepNumber, error);
		fprintf(rmsd_energy, "%f %f\n", bestFoldingArray.energy, error);		


	}

	fclose(rmsd_mcs);
	fclose(rmsd_energy);
	
	return 1;
}

int proteinChaperonComplex::foldInChaperonWithBindReleaseMechanism
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   bool inChaperon,
										   bool dynamic,
										   int bindInterval,
		                                   int releaseInterval,
		                                   double energyThreshold)
{
	initFoldingComplex();
	
	//foldOnce();//temp 25.1.06
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	char *hp;
	if( (hp = CfileHdlr.readTextStructure(sizeOfResidueArray, structure, configfileIndex)) == 0)
	{
		cout<<"could not Get index: "<<configfileIndex<<endl;
		delete []structure;
		return 0;//exit(0);
	}
	
	UPDATE_PROTEIN_MODES(res)
	 		
	rmsd = new RMSD(this, sizeOfResidueArray, 0);
	//cout<<"blabla"<<endl;
	
	rmsd->update(structure);
///////////////////////////////////////////////////////////////////////////////////
	char tmpstr[220], datafn[120];
	FILE *rmsd_mcs, *rmsd_energy, *rmsd_binds;

	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "rmsd_mcs", simulationFactor, energyThreshold, 
												  releaseInterval, bindInterval);
	//strcpy(datafn, "rmsd_mcs");
	CREATE_FILE(rmsd_mcs)

	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "rmsd_energy", simulationFactor, energyThreshold, 
													 releaseInterval, bindInterval);
	//strcpy(datafn, "rmsd_energy");
	CREATE_FILE(rmsd_energy)
	
	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "structure", simulationFactor, energyThreshold, 
												   releaseInterval, bindInterval);
	//strcpy(datafn, "structure");
	sprintf(tmpstr, "%s%s-%d-%d.data", outputDatafileName, datafn, sizeOfResidueArray, configfileIndex);
	
	residueArray residue2File(sizeOfResidueArray, tmpstr);	
	UPDATE_PROTEIN_MODES(residue2File.res)
	
	if(inChaperon)
	{
		sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "rmsd_binds", simulationFactor, energyThreshold, 
														releaseInterval, bindInterval);
		//strcpy(datafn, "rmsd_binds");
		CREATE_FILE(rmsd_binds)
	}
	
///////////////////////////////////////////////////////////////////////////////////
		
	cout<<"Begin folding:"<<endl;
	for(int m = 0; m < numOfSimulations; m++)
	{
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
				
				double error = rmsd->compute(bestFoldingArray);
				
				cout<<"Protein in chaperon when terminates: \n";
				cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
				//writeStructures2output();
				//cout<<"best folding Array: \n";
				//CfileHdlr.writeStructure2output(sizeOfResidueArray, &bestFoldingArray);
		
				residue2File = bestFoldingArray;
				residue2File.write();
				fprintf(rmsd_mcs, "%d %f\n", bestFoldingArray.stepNumber, error);
				fprintf(rmsd_energy, "%f %f\n", bestFoldingArray.energy, error);
				if(inChaperon)
					fprintf(rmsd_binds, "%d %f\n", bindTryCounter, error);		

				//fclose(rmsd_mcs);
				//fclose(rmsd_energy);
				//if(inChaperon)
				//	fclose(rmsd_binds);

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

							//fclose(rmsd_mcs);
							//fclose(rmsd_energy);
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
						//writeStructures2output();
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

		
		double error = rmsd->compute(bestFoldingArray);
		//cout<<"Error: "<<error<<endl;
		//if(inChaperon)
			//cout<<"Protein in chaperon when terminates: \n";
		//cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
		//writeStructures2output();
		//cout<<"best folding Array: \n";
		//CfileHdlr.writeStructure2output(sizeOfResidueArray, &bestFoldingArray);
		
		residue2File = bestFoldingArray;
		residue2File.write();
		fprintf(rmsd_mcs, "%d %f\n", bestFoldingArray.stepNumber, error);
		fprintf(rmsd_energy, "%f %f\n", bestFoldingArray.energy, error);
		if(inChaperon)
			fprintf(rmsd_binds, "%d %f\n", bindTryCounter, error);		

		//cout<<"foldInChaperonWithBindReleaseMechanism"<<endl;
	}
	
	fclose(rmsd_mcs);
	fclose(rmsd_energy);
	if(inChaperon)
		fclose(rmsd_binds);
	delete []structure;
	delete rmsd;
	cout<<"finish configfileIndex: "<<configfileIndex<<endl;
	return 1;
}


#if 0
int proteinChaperonComplex::dimer_foldInChaperonWithBindReleaseMechanismPro
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   int *fromto,
										   bool inChaperon,
										   bool dynamic,
										   int bindInterval,
		                                   int releaseInterval,
		                                   double energyThreshold)
{
	initFoldingComplex();
	
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
	 		
	RMSD rmsd(this, sizeOfResidueArray, 0);
	rmsd.update(structure);
///////////////////////////////////////////////////////////////////////////////////
	char tmpstr[220], datafn[120];
	FILE *rmsd_mcs, *rmsd_energy, *rmsd_binds;

	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "rmsd_mcs_energy", simulationFactor, energyThreshold, 
												  releaseInterval, bindInterval);
	//strcpy(datafn, "rmsd_mcs");
	CREATE_FILE(rmsd_mcs)

	
	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "structure", simulationFactor, energyThreshold, 
												   releaseInterval, bindInterval);
	//strcpy(datafn, "structure");
	sprintf(tmpstr, "%s%s-%d-%d.data", outputDatafileName, datafn, sizeOfResidueArray, configfileIndex);
	
	residueArray residue2File(sizeOfResidueArray, tmpstr);	
	UPDATE_PROTEIN_MODES(residue2File.res)
	
	if(inChaperon)
	{
		sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "rmsd_binds", simulationFactor, energyThreshold, 
														releaseInterval, bindInterval);
		//strcpy(datafn, "rmsd_binds");
		CREATE_FILE(rmsd_binds)
	}
	
///////////////////////////////////////////////////////////////////////////////////
		
	cout<<"Begin folding:"<<endl;
	for(int m = 0; m < numOfSimulations; m++)
	{
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
				
				double error = rmsd->compute(bestFoldingArray);
				
				cout<<"Protein in chaperon when terminates: \n";
				cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
				//writeStructures2output();
				//cout<<"best folding Array: \n";
				//CfileHdlr.writeStructure2output(sizeOfResidueArray, &bestFoldingArray);
		
				residue2File = bestFoldingArray;
				residue2File.write();
				fprintf(rmsd_mcs, "%d %f\n", bestFoldingArray.stepNumber, error);
				fprintf(rmsd_energy, "%f %f\n", bestFoldingArray.energy, error);
				if(inChaperon)
					fprintf(rmsd_binds, "%d %f\n", bindTryCounter, error);		

				//fclose(rmsd_mcs);
				//fclose(rmsd_energy);
				//if(inChaperon)
				//	fclose(rmsd_binds);

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
							fclose(rmsd_mcs);
							fclose(rmsd_energy);
			
							return 1;
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
						//writeStructures2output();
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

		
		double error = rmsd->compute(bestFoldingArray);
		//cout<<"Error: "<<error<<endl;
		//if(inChaperon)
			//cout<<"Protein in chaperon when terminates: \n";
		//cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
		//writeStructures2output();
		//cout<<"best folding Array: \n";
		//CfileHdlr.writeStructure2output(sizeOfResidueArray, &bestFoldingArray);
		
		residue2File = bestFoldingArray;
		residue2File.write();
		fprintf(rmsd_mcs, "%d %f\n", bestFoldingArray.stepNumber, error);
		fprintf(rmsd_energy, "%f %f\n", bestFoldingArray.energy, error);
		if(inChaperon)
			fprintf(rmsd_binds, "%d %f\n", bindTryCounter, error);		

		//cout<<"foldInChaperonWithBindReleaseMechanism"<<endl;
	}
	
	fclose(rmsd_mcs);
	fclose(rmsd_energy);
	if(inChaperon)
		fclose(rmsd_binds);
	delete []structure;
	delete rmsd;
	cout<<"finish configfileIndex: "<<configfileIndex<<endl;
	return 1;
}

int proteinChaperonComplex::dimer_foldInChaperonWithBindReleaseMechanism
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   int *fromto,
										   bool inChaperon,
										   bool dynamic,
										   int bindInterval,
		                                   int releaseInterval,
		                                   double energyThreshold)
{
	initFoldingComplex();
	
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
	 		
	RMSD rmsd(this, sizeOfResidueArray, 0);
	rmsd.update(structure);
///////////////////////////////////////////////////////////////////////////////////
	char tmpstr[220], datafn[120];
	FILE *rmsd_mcs, *rmsd_energy, *rmsd_binds;

	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "rmsd_mcs", simulationFactor, energyThreshold, 
												  releaseInterval, bindInterval);
	//strcpy(datafn, "rmsd_mcs");
	CREATE_FILE(rmsd_mcs)

	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "rmsd_energy", simulationFactor, energyThreshold, 
													 releaseInterval, bindInterval);
	//strcpy(datafn, "rmsd_energy");
	CREATE_FILE(rmsd_energy)
	
	sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "structure", simulationFactor, energyThreshold, 
												   releaseInterval, bindInterval);
	//strcpy(datafn, "structure");
	sprintf(tmpstr, "%s%s-%d-%d.data", outputDatafileName, datafn, sizeOfResidueArray, configfileIndex);
	
	residueArray residue2File(sizeOfResidueArray, tmpstr);	
	UPDATE_PROTEIN_MODES(residue2File.res)
	
	if(inChaperon)
	{
		sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "rmsd_binds", simulationFactor, energyThreshold, 
														releaseInterval, bindInterval);
		//strcpy(datafn, "rmsd_binds");
		CREATE_FILE(rmsd_binds)
	}
	
///////////////////////////////////////////////////////////////////////////////////
		
	cout<<"Begin folding:\n";
	for(int m = 0; m < numOfSimulations; m++)
	{
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
				
				double error = rmsd.dimer_compute(bestFoldingArray, fromto[0], fromto[1], fromto[2], fromto[3]);
				cout<<"Error: "<<error<<endl;
				cout<<"Protein in chaperon when terminates: \n";
				cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
				//writeStructures2output();
				//cout<<"best folding Array: \n";
				//CfileHdlr.writeStructure2output(sizeOfResidueArray, &bestFoldingArray);
		
				residue2File = bestFoldingArray;
				residue2File.write();
				fprintf(rmsd_mcs, "%d %f\n", bestFoldingArray.stepNumber, error);
				fprintf(rmsd_energy, "%f %f\n", bestFoldingArray.energy, error);
				if(inChaperon)
					fprintf(rmsd_binds, "%d %f\n", bindTryCounter, error);		

				//fclose(rmsd_mcs);
				//fclose(rmsd_energy);
				//if(inChaperon)
				//	fclose(rmsd_binds);

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
							fclose(rmsd_mcs);
							fclose(rmsd_energy);
			
							return 1;
						}
						else if(rslt == 1)
						{
							cout<<"protein is binded\n";
							cout<<"Mode: "<<chap->res[1].mode<<endl;
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
						//writeStructures2output();
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

	
		double error = rmsd.dimer_compute(bestFoldingArray, fromto[0], fromto[1], fromto[2], fromto[3]);

		cout<<"Error: "<<error<<endl;
		cout<<"Protein in chaperon when terminates: \n";
		cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
		//writeStructures2output();
		cout<<"best folding Array: \n";
		CfileHdlr.writeStructure2output(sizeOfResidueArray, &bestFoldingArray);
		
		residue2File = bestFoldingArray;
		residue2File.write();
		fprintf(rmsd_mcs, "%d %f\n", bestFoldingArray.stepNumber, error);
		fprintf(rmsd_energy, "%f %f\n", bestFoldingArray.energy, error);
		if(inChaperon)
			fprintf(rmsd_binds, "%d %f\n", bindTryCounter, error);		


	}

	fclose(rmsd_mcs);
	fclose(rmsd_energy);
	if(inChaperon)
		fclose(rmsd_binds);
	delete []structure;
	return 1;
}
#endif
int proteinChaperonComplex::unFoldInChaperonWithBindReleaseMechanism
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   bool inChaperon,
										   bool dynamic,
										   int bindInterval,
		                                   int releaseInterval,
		                                   double energyThreshold,
								    	   int sampleRate)
{
	initFoldingComplex();
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	char *hp;
	if( (hp = CfileHdlr.readTextStructure(sizeOfResidueArray, structure, configfileIndex)) == 0)
	{
		cout<<"could not Get index: "<<configfileIndex<<endl;
		delete []structure;
		return 0;//exit(0);
	}
	
	UPDATE_PROTEIN_MODES(res)
	UPDATE_PROTEIN_STRUCTURE
	energy = calculateEnergy(); 
			
	RMSD rmsd(this, sizeOfResidueArray, 0);
	rmsd.update(structure);
///////////////////////////////////////////////////////////////////////////////////
	char tmpstr[120], datafn[120];
	FILE *rmsd_mcs, *rmsd_energy, *rmsd_binds;

	
///////////////////////////////////////////////////////////////////////////////////
		
	cout<<"Begin folding:\n";
	for(int m = 0; m < numOfSimulations; m++)
	{
		sprintf(datafn, "%s-f%f-t%f-r%d-b%d-m%d", "rmsd_mcs", simulationFactor, energyThreshold, 
												  releaseInterval, bindInterval, m);
		CREATE_FILE(rmsd_mcs)

		sprintf(datafn, "%s-f%f-t%f-r%d-b%d-m%d", "energy_mcs", simulationFactor, energyThreshold, 
													 releaseInterval, bindInterval, m);
		CREATE_FILE(rmsd_energy)
	
	
		initFoldingComplex();
		UPDATE_PROTEIN_STRUCTURE
		energy = calculateEnergy();
		
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
				if(r%sampleRate == 0)
					UPDATE_INPUT_FILES(r)
			}
		
			if(r == times)
			{
				cout<<"Could not fold to size: ("<<added_confinedX<<", "<<added_confinedY<<")\n";
				
				double error = rmsd.compute(bestFoldingArray);
				cout<<"Error: "<<error<<endl;
				cout<<"Protein in chaperon when terminates: \n";
				cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;	
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
						if(i%sampleRate == 0)
							UPDATE_INPUT_FILES(i)
						
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
							fclose(rmsd_mcs);
							fclose(rmsd_energy);
			
							return 1;
						}
						else if(rslt == 1)
						{
							cout<<"protein is binded\n";
							cout<<"Mode: "<<chap->res[1].mode<<endl;
							bindedCtr = 0;
							proteinIsBinded = true;	
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

			foldOnce();
			if(i%sampleRate == 0)
				UPDATE_INPUT_FILES(i)
				
			if(alpha_itr == ALPHA_ITR)
			{
				alpha_itr = 0;
			
				if(Ck < ALPHA_LOWER_BOND)
					Ck = ALPHA_LOWER_BOND;
				else
					Ck *= ALPHA;	
			}		
		}

		fclose(rmsd_mcs);
		fclose(rmsd_energy);
		if(inChaperon)
			fclose(rmsd_binds);

	}

	delete []structure;
	return 1;
}

///////////////////////////
int proteinChaperonComplex::unFoldThreshInChaperonWithBindReleaseMechanism
										  (double times, 
										   int numOfSimulations, 
										   int configfileIndex, 
										   bool inChaperon,
										   bool dynamic,
										   int bindInterval,
		                                   int releaseInterval,
		                                   double energyThreshold,
								    	   int sampleRate,
										   double threshold)
{
	
	initFoldingComplex();
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	char *hp;
	if( (hp = CfileHdlr.readTextStructure(sizeOfResidueArray, structure, configfileIndex)) == 0)
	{
		cout<<"could not Get index: "<<configfileIndex<<endl;
		delete []structure;
		return 0;//exit(0);
	}
	
	UPDATE_PROTEIN_MODES(res)
	UPDATE_PROTEIN_STRUCTURE
	energy = calculateEnergy(); 
			
	RMSD rmsd(this, sizeOfResidueArray, 0);
	rmsd.update(structure);
///////////////////////////////////////////////////////////////////////////////////
	char tmpstr[120], datafn[120];
	FILE *rmsd_mcs;

	//for(int z = 0; z < 15; z++)
	//{
		sprintf(datafn, "%s-f%f-t%f-r%d-b%d", "rmsd_cnt", simulationFactor, energyThreshold, 
												  releaseInterval, bindInterval);
		CREATE_FILE(rmsd_mcs)
	//}


	
///////////////////////////////////////////////////////////////////////////////////

	int thresholdCtr[15];
	for(int z = 0; z < 15; z++)
		thresholdCtr[z] = 0;	
		
	cout<<"Begin unfolding:\n";
	
	for(int m = 0; m < numOfSimulations; m++)
	{
	
		for(int z = 0; z < 15; z++)
			thresholdCtr[z] = 0;	

		initFoldingComplex();
		UPDATE_PROTEIN_STRUCTURE
		energy = calculateEnergy();
		
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
				if(r%sampleRate == 0)
				{
					double error = rmsd.compute(*this);
					int g = 0;
					for(double z = 0.1; g <= 15; z += 0.1, g++)
						if(error <= z)
							thresholdCtr[g]++;
				}		
			}
			
			if(r == times)
			{
				cout<<"Could not fold to size: ("<<added_confinedX<<", "<<added_confinedY<<")\n";
				
				double error = rmsd.compute(bestFoldingArray);
				cout<<"Error: "<<error<<endl;
				cout<<"Protein in chaperon when terminates: \n";
				cout<<"FPT: "<<bestFoldingArray.stepNumber<<endl;
				for(int z = 0; z < 15; z++)	
					fprintf(rmsd_mcs, "%f %f\n", (double)(z+1)*0.1,
						(double)thresholdCtr[z]/((double)times/(double)sampleRate));

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
						
						if(i%sampleRate == 0)
						{
							double error = rmsd.compute(*this);
							int g = 0;
							for(double z = 0.1; g <= 15; z += 0.1, g++)
								if(error <= z)
									thresholdCtr[g]++;
						}		

						
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
							//for(int z = 0; z < 15; z++)
								fclose(rmsd_mcs);
							
			
							return 1;
						}
						else if(rslt == 1)
						{
							cout<<"protein is binded\n";
							cout<<"Mode: "<<chap->res[1].mode<<endl;
							bindedCtr = 0;
							proteinIsBinded = true;	
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

			foldOnce();
			if(i%sampleRate == 0)
			{
				double error = rmsd.compute(*this);
				int g = 0;
				for(double z = 0.1; g <= 15; z += 0.1, g++)
					if(error <= z)
						thresholdCtr[g]++;
			}		
	
				
			if(alpha_itr == ALPHA_ITR)
			{
				alpha_itr = 0;
			
				if(Ck < ALPHA_LOWER_BOND)
					Ck = ALPHA_LOWER_BOND;
				else
					Ck *= ALPHA;	
			}
					
		}
		for(int z = 0; z < 15; z++)
		{
			fprintf(rmsd_mcs, "%f %f\n", (double)(z+1)*0.1,
				(double)thresholdCtr[z]/((double)times/(double)sampleRate));
			cout<<"val: "<<(double)thresholdCtr[z]/((double)times/(double)sampleRate)<<endl;
		}
	}
	delete []structure;
	//for(int z = 0; z < 15; z++)
		fclose(rmsd_mcs);
	return 1;
}

int proteinChaperonComplex::writeStructures2output() 
{

	int Xmin, Xmax, Ymin, Ymax;
	getMatrixBounds(boolMatrix, top_y, &Xmin, &Xmax, &Ymin, &Ymax);
	
	cout<<endl;
	for(int y = Ymax; y >= Ymin; y--)
	{
		for(int x = Xmin; x <= Xmax; x++)
		{
			if(boolMatrix[y][x] > 9)
				cout<<"("<<boolMatrix[y][x]<<")";
			else if(boolMatrix[y][x] > 0)
				cout<<"( "<<boolMatrix[y][x]<<")";
			if(!boolMatrix[y][x])
				cout<<"    ";
		}
		cout<<endl;
	}
	cout<<endl;
				
	 
	return 1;
}

