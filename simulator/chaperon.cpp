//chaperon.cpp

#include "chaperon.h"
#include <ctype.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
	
const int chaperon::mcsWindowSize = MCS_WINDOW_SIZE;
int chaperon::singleton = 0;
configFileHandler chaperon::cfh;

point chaperon::getMin_dx_dy()
{
	point pdxdy;
	/*
	pdxdy.x = max(x) - min(x)
	pdxdy.y = max(y) - min(y)
	*/
	
	int minX, minY;
	int maxX, maxY;
	minX = maxX = res[1].position.x;
	minY = maxY = res[1].position.y;
	
	for(int i = 2; i <= sizeOfResidueArray; i++)
	{
		if(minX > res[i].position.x)
			minX = res[i].position.x;
		if(maxX < res[i].position.x)
			maxX = res[i].position.x;
			
		if(minY > res[i].position.y)
			minY = res[i].position.y;
		if(maxY < res[i].position.y)
			maxY = res[i].position.y;
	}

	pdxdy.x = maxX - minX;
	pdxdy.y = maxY - minY;
	
	return pdxdy;
	
}

int chaperon::logo2structure(char *str)
{
	if(str == 0)
		str = logoStr;
	
	int Xstep = 0, Ystep = 1;//initial position Head UP
	int currentRes = 1, tmp;
	
	point position(sizeOfResidueArray, sizeOfResidueArray - 1);
	
	for(int i = 0; str[i] && currentRes <= sizeOfResidueArray; i++)
	{
		//cout<<","<<i<<endl;
		switch(str[i])
		{
			case 'F':	position.x += Xstep;
						position.y += Ystep;
						//cout<<position<<endl;
						res[currentRes].position.x = position.x;
						res[currentRes].position.y = position.y;
						currentRes++;
						break;
						
			case 'f':	position.x += Xstep;
						position.y += Ystep;
						break;
				
			case '+':/*	Right rotation x =  y 
	 								   y = -x  */
					
						tmp = Xstep;
						Xstep = Ystep;
						Ystep = -1*tmp;
						break;
						
			case '-':/*	Left rotation x = -y 
	 								  y =  x  */
					
						tmp = Xstep;
						Xstep = -1*Ystep;
						Ystep = tmp;
						break;
				
			default : cout<<"ERROR input logo2structure\n";
					  exit(0);
		}
	}
	//cout<<"finish with logo2struct\n";
	return 1;
}

int chaperon::structure2logo(point *structure)
{
	int logoidx = 0;
	
	char tmpStr[MAX_SIZE_OF_TMP_STRUCTURE*8];
	
	tmpStr[logoidx++] = 'S';
	 
	for(int i = 2; i <= sizeOfResidueArray; i++)
	{
		int dx; 
		int dy; 
		
		if(structure)
		{
			dx = structure[i].x - structure[i - 1].x;	
			dy = structure[i].y - structure[i - 1].y;
		}
		else
		{
			dx = res[i].position.x - res[i - 1].position.x;	
			dy = res[i].position.y - res[i - 1].position.y;
		}
			
		//move with pen up:
		for(; dx > 1; dx--)
			tmpStr[logoidx] = 'r';
		for(; dx < -1; dx++)
			tmpStr[logoidx] = 'l';
		for(; dy > 1; dy--)
			tmpStr[logoidx] = 'u';
		for(; dx < -1; dx++)
			tmpStr[logoidx] = 'd';
		
		if( (dx ==  1 && dy ==  1) || 
			(dx ==  1 && dy == -1) )
		{
			tmpStr[logoidx] = 'r';
			dx--;
		}
		
		if( (dx ==  -1 && dy ==  1) || 
			(dx ==  -1 && dy == -1) )
			
		{
			tmpStr[logoidx] = 'l';
			dx++;
		}
		
		
		if(dy ==  1)
			tmpStr[logoidx] = 'U';			
		else if(dx ==  1)
			tmpStr[logoidx] = 'R';
		else if(dx == -1)
			tmpStr[logoidx] = 'L';
		else if(dy == -1)
			tmpStr[logoidx] = 'D';

		logoidx++;	
	}	
	
	tmpStr[logoidx] = 0;
	
	cout<<"tmpStr: "<<tmpStr<<endl;
	if(logoStr)
		delete [] logoStr;

	logoStr = new char[logoidx*2 + 1]; 
	if(!logoStr)
	{
		cout<<"ERROR alloc mem\n";
		exit(1);
	}
	
	logoidx = 1;
	logoStr[0] = 'F';
	
	 
	for(int i = 1; tmpStr[i]; i++)
	{
		char prev = toupper(tmpStr[i - 1]);
		char curr = toupper(tmpStr[i]);
		if( prev != curr )
		{
			if(prev == 'U')
				if(curr == 'L')
					logoStr[logoidx++] = '-';
				else if(curr == 'R')
					logoStr[logoidx++] = '+';
				else
				{
					cout<<"ERROR structure - runover: "<<prev<<curr<<"\n";
					return 0;
				}
			if(prev == 'D')
				if(curr == 'L')
					logoStr[logoidx++] = '+';
				else if(curr == 'R')
					logoStr[logoidx++] = '-';
				else
				{
					cout<<"ERROR structure - runover: "<<prev<<curr<<"\n";
					return 0;
				}
			if(prev == 'L')
				if(curr == 'U')
					logoStr[logoidx++] = '+';
				else if(curr == 'D')
					logoStr[logoidx++] = '-';
				else
				{
					cout<<"ERROR structure - runover: "<<prev<<curr<<"\n";
					return 0;
				}
			if(prev == 'R')
				if(curr == 'D')
					logoStr[logoidx++] = '+';
				else if(curr == 'U')
					logoStr[logoidx++] = '-';
				else
				{
					cout<<"ERROR structure - runover: "<<prev<<curr<<"\n";
					return 0;
				}
	
		}
		if(isupper(tmpStr[i]))
			logoStr[logoidx++] = 'F';
		else
			logoStr[logoidx++] = 'f';
	}
	logoStr[logoidx] = 0;
	logoSize = logoidx;
		
	return 1;
}
chaperon::~chaperon()
{
	cout<<"~chaperon\n";
	if(logoStr)
		delete []logoStr;
	for(int z = 0; z < numberOfModes; z++)
		delete []modes[z];
	
	if(modes)
		delete []modes;
	if(dynamics)
		delete []dynamics;
	if(TM)
		delete TM;
	
}

chaperon::chaperon(int findex, char *name)
{
	//cout<<"enter chaperon ctor\n";
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
	
	if(name) {
		point parr[MAX_SIZE_OF_TMP_STRUCTURE];
		int tmpsize = 0;
		
		//char* hp = cfh.readUnknownLengthTextStructure(MAX_SIZE_OF_TMP_STRUCTURE, parr, findex, &tmpsize);
		char* hp = cfh.getChaperonData(MAX_SIZE_OF_TMP_STRUCTURE, 
												parr, 
												findex, 
													&tmpsize,
											modes,
											numberOfModes,
											dynamics);
	
		new_residueArray(tmpsize);
		cout<<"sizeOfResidueArray: "<<sizeOfResidueArray<<endl;
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
		TM = new turingMachine(dynamics, mcsWindowSize);
		
		cfh.writeStructure2output(sizeOfResidueArray, this);
	}		
	else //if(!name) 
	{
		cout<<"Assuming user wishes to simulate folding without chaperon, first chaperon ctor but no file name\n";
	}
}

int chaperon::updateMode(int modeNumber)
{
	//cout<<"updating to mode: "<<modeNumber - 1<<endl;
	//cout<<"Updated mode: ";
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		res[i].mode = modes[modeNumber - 1][i - 1];
		//cout<<res[i].mode;
	}
	//cout<<endl;
	return 1;
}

int chaperon::step()
{
	int modeNumber;
	if( (modeNumber = TM->step()) > 0 )
	{
		updateMode(modeNumber);
		//cfh.writeStructure2output(sizeOfResidueArray, this);
	}
	
	return 1;
}

int chaperon::init(foldingComplex *pcc )
{
	//cout<<"init chaperon !\n";
	TM->init();
	updateMode(1);
	return 1;	
}
			
#if 0
int main(int argc, char **argv)
{
	chaperon chap(0, argv[1]);
	
	//chap.structure2logo();
	//cout<<"LOGO: "<<chap.logoStr<<endl;
	//chap.logo2structure();//argv[2]);//"FFFFFF-FFFFFFFFFFFFFFFFFFF");
	//chaperon::cfh.writeStructure2output(chap.sizeOfResidueArray, &chap);
	
	for(int i = 0; i < atoi(argv[2]); i++)
	{
		chap.step();
		while(getchar() != '\n');
	}
	return 0;
}
#endif
