//doubleDomain.cpp


int doubleDomain::foldOnce()
{
	int pivot = RNG.generateNumberInRange(1, sizeOfResidueArray);
	PIVOT = pivot;
	int fold_type = RNG.generateNumberInRange(0, edgesProbability);
	
	switch(fold_type)
	{
		
		case 0: if((pivot == 1) || (pivot == sizeOfResidueArray))
				if(tailRotateLeft(pivot) == 1)
					successCtr++;
				break;

		case 1: if((pivot == 1) || (pivot == sizeOfResidueArray))
				if(tailRotateRight(pivot)) //
					successCtr++;
				break;
		case 2: if((pivot == 1) || (pivot == sizeOfResidueArray))
				if(tailRotate180(pivot))//2
					successCtr++; 
				
				break;		
		default: if(randLocalMod(pivot))
					successCtr++;
				break;
			
	}
	//cout<<"Folding Once"<<endl;
	//exit(0);
	return 1;
}

bool doubleDomain::MontaCarloAnnealing(double newE, double oldE)
{
	
	enteringMCAnneal++;
	double currentTemperature = simulationFactor;
	//return (newE <= oldE);
	if(newE < oldE)
		return true;
	else 
	{
		if(PIVOT <= fromto[1]) { //A domain
			currentTemperature = A_temperature;
		}
		else if(PIVOT >= fromto[2]) { //B domain
			currentTemperature = B_temperature;
		}
		else { //linker
			currentTemperature = getLinkerTemperature();
		}
		if( RNG.generateRandomFraction() <
			exp((oldE - newE)/(Ck*currentTemperature)) )
		{
			return true;
		}
	}
	return false;
} 	

double doubleDomain::getLinkerTemperature()
{
	return A_temperature + (PIVOT - from[2])*((B_temperature - A_temperature)/(from[3] - from[2])) 
}

doubleDomain::doubleDomain(int length, char* confFileName, int findex, char *cname):
foldingComplex(length, confFileName),
useZeroPotential(true)
{
	//TODO: add fromto assignments
	cout<<"doubleDomain ctor 1"<<endl;
	added_confinedX = sqrt((double)length) + 2;
	added_confinedY = sqrt((double)length) + 2;
	firstPassageTime = false;
		
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
