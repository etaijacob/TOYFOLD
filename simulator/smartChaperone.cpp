//smartChaperone.cpp

#include "smartChaperone.h"
#include <iostream>
#include <stdlib.h>

smartChaperone::smartChaperone(int findex, char *name)
{
	cout<<"enter smartChaperone ctor\n";
	iterationsCounter = 0;
	logoStr = 0;
	
	sizeOfResidueArray = 0;

	if(name && singleton == 0)
	{
		if(!cfh.init(name))
		{
			cout<<"Error cfh.init\n";
			exit(0);
		}
		singleton = 1;
	}
	else if(!name) 
	{
		cout<<"Error, first chaperon ctor but no file name\n";
		exit(0);
	}
	
	point parr[MAX_SIZE_OF_TMP_STRUCTURE];
	int tmpsize = 0;
	
	char* hp = cfh.getSmartChaperonData(MAX_SIZE_OF_TMP_STRUCTURE, 
				  				   parr, 
				  				   findex, 
								   &tmpsize,
								   modes,
								   numberOfModes,
								   dynamics,
								   sides,
			  					   sideDynamics,		 
								   numberOfSides);

	new_residueArray(tmpsize);
	//cout<<"sizeOfResidueArray: "<<sizeOfResidueArray<<endl;
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				res[i].mode = HYDROPHOBIC; break;
 			case 'P':
				res[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				res[i].mode = POSITIVE_CHARGE; break;	
			case '-':
				res[i].mode = NEGATIVE_CHARGE; break;
		}
		res[i].position.x = parr[i].x;		
		res[i].position.y = parr[i].y;
	}
	TM = new turingMachine(sideDynamics, mcsWindowSize);
	
	sideModes = new int*[numberOfSides + 1];//zero place is for all Hydrophobic 
	if(!sideModes)
	{
		cout<<"ERROR alloc -smartChaperone ctor"<<endl;
		exit(1);
	}
	for(int i = 0; i <= numberOfSides; i++)
	{
		if(!(sideModes[i] = new int[sizeOfResidueArray + 1]))
		{
			cout<<"ERROR alloc -smartChaperone ctor"<<endl;
			exit(1);	
		}
	}
	for(int i = 0; i <= sizeOfResidueArray; i++)
		sideModes[0][i] = HYDROPHOBIC;
	
	if(!(onSide = new int[sizeOfResidueArray + 1]))
	{
		cout<<"ERROR alloc -smartChaperone ctor"<<endl;
		exit(1);	
	}	
	
	onSide[0] = 0;
	int i = 1;
	for(int j = 0; j < numberOfSides; j++)
			while(i >= sides[j][0] && i <= sides[j][1])
				onSide[i++] = j;
	cout<<"\nsides:\n";
	for(i = 1; i <= sizeOfResidueArray; i++)
		cout<<onSide[i];
	cout<<endl;
	cfh.writeStructure2output(sizeOfResidueArray, this);
	//for(int i = 0; i < numberOfSides; i++)
	//	buildSmartSides(i);
			
}


smartChaperone::~smartChaperone()
{
	if(logoStr)
		delete []logoStr;
	for(int z = 0; z < numberOfModes; z++)
		delete []modes[z];
	
	delete []modes;
	delete []dynamics;
	delete TM;
	
	delete sideDynamics;
	for(int s = 0; s < numberOfSides; s++)
		delete []sides[s];
	delete []sides;
	for(int i = 0; i <= numberOfSides; i++)
		delete []sideModes[i];
	delete []sideModes;

	delete []onSide;	
}

//builds the smart sides according to the protein location in chaperone
//the sideModes structure will hold the relevant modes.
int smartChaperone::buildSmartSides(int sideToStart)
{
	sideToStart = (sideToStart + 1)%numberOfSides;//from the next;
	cout<<"Starting from: "<<sideToStart<<endl;
	for(int i = sideToStart, j = 1; j <= numberOfSides; j++, i = (i + 1)%numberOfSides)
	{
		for(int l = sides[(i + 1)%numberOfSides][0]; 
		   l != sides[sideToStart][0]; 
		   l = (l + 1)%(sizeOfResidueArray +1))
			sideModes[j][l] = HYDROPHOBIC;
		for(int m = j; m <= numberOfSides; m++)
			for(int k = sides[i][0]; k <= sides[i][1]; k++)
				sideModes[m][k] = POLAR_NEUTRAL;
	}
	/*for(int m = 0; m <= numberOfSides; m++)
	{
		for(int k = 1; k <= sizeOfResidueArray; k++)
			cout<<sideModes[m][k];
		cout<<endl;
	}
	*/
	return 1;
}

//m is the side which it should begin [0,n]
int smartChaperone::init(foldingComplex *pcc)
{
	cout<<"init smart chaperone !\n";
	if(pcc)
	{
		int s = getInteractionSide(pcc);
		if(s >= 0)
			buildSmartSides(s);
		else
			buildSmartSides(1);
	}
	else
		buildSmartSides(1);
	
	TM->init();
	updateMode(1);//start with all hydrophobic
	return 1;	
}

int smartChaperone::updateMode(int modeNumber)
{
	//cout<<"updating to mode on smart chap: "<<modeNumber - 1<<endl;
	//cout<<"Updated mode: ";
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		res[i].mode = sideModes[modeNumber - 1][i];
		//cout<<res[i].mode;
	}
	//cout<<endl;
	return 1;
}

//returns the index [0, numberOfsides) side of chaperone which the protein is conected to.
//if no connection exist return -1.
int smartChaperone::getInteractionSide(foldingComplex *pcc)
{
	int sideCounter[64] = {0};
	
	for(int i = 1; i <= pcc->sizeOfResidueArray; i++)
	{
		int x = pcc->res[i].position.x;
		int y = pcc->res[i].position.y;
			
		if(y < pcc->top_y - 1 && pcc->boolMatrix[y + 1][x] > pcc->sizeOfResidueArray)
		{
			sideCounter[onSide[pcc->boolMatrix[y + 1][x] - pcc->sizeOfResidueArray]]++;
			//cout<<pcc->boolMatrix[y + 1][x] - pcc->sizeOfResidueArray<<endl;
		}

		if(y > pcc->buttom_y && pcc->boolMatrix[y - 1][x] > pcc->sizeOfResidueArray)
		{
			sideCounter[onSide[pcc->boolMatrix[y - 1][x] - pcc->sizeOfResidueArray]]++;
			//cout<<pcc->boolMatrix[y - 1][x] - pcc->sizeOfResidueArray<<endl;
		}
			
		if(x < pcc->right_x - 1 && pcc->boolMatrix[y][x + 1] > pcc->sizeOfResidueArray)
		{
			sideCounter[onSide[pcc->boolMatrix[y][x + 1] - pcc->sizeOfResidueArray]]++;
			//cout<<pcc->boolMatrix[y][x + 1] - pcc->sizeOfResidueArray<<endl;
		}	
			
		if(x > pcc->left_x && pcc->boolMatrix[y][x - 1] > pcc->sizeOfResidueArray)
		{
			sideCounter[onSide[pcc->boolMatrix[y][x - 1] - pcc->sizeOfResidueArray]]++;
			//cout<<pcc->boolMatrix[y][x - 1] - pcc->sizeOfResidueArray<<endl;
		}	
	}
	
/*	chosing the max side:
	int max = 0;
	cout<<"side Counter: "<<endl<<sideCounter[0]<<", ";
	for(int i = 1; i < numberOfSides; i++)
	{
		if(sideCounter[max] < sideCounter[i])
			max = i;
		cout<<sideCounter[i]<<", ";
	}
	cout<<" chosen: "<<max<<endl;
	if(sideCounter[max] == 0)
		return -1;
	return max;
*/
/*	chosing the last side of interaction */
	int last = -1;
	for(int i = 0; i < numberOfSides; i++)
	{
		cout<<sideCounter[i]<<", ";
		if(sideCounter[i] > 0)
			last = i;
	}
	cout<<"\nchosen: "<<last<<endl;
	return last;
}

#if 0
int main(int argc, char **argv)
{
	chaperon *sc = new chaperon(1, argv[1]);
//	for(int i = 0; i < 4; i++)
//		sc->buildSmartSides(i);
		sc->init();
	for(int i = 0; i < 1000000; i++)
		sc->step();

	return 0;
}
#endif
