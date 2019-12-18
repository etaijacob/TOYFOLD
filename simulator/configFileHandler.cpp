//configFileHandler.cpp

#include "configFileHandler.h"
#include "point.h"
#include "utilities.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <math.h>
#include <sys/stat.h>
#include <ctype.h>

using namespace std; 

int configFileHandler::getDynamics(int &i, char *&dynamics)
{
	int m = 0;
	for(; buffer[i + m] != '\n' && (i + m) < lengthOfText; m++);
	
	dynamics = new char[m + 1];
	if(!dynamics)
	{
		cout<<"ERROR - mem alloc\n";
		exit(1);
	}
	
	for(int s = 0; s < m; s++, i++)
		dynamics[s] = buffer[i];
	
	dynamics[m] = 0;
	cout<<"Dynamics: "<< dynamics<<endl;
	
	while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
		i++;
	
	if(buffer[i] == '[' || i == lengthOfText)
	{
		cout<<"configFileHandler: config file - no structure txt match found 1\n";
		return 0;
	}
 	i++;
	return 1;
}

//calling object must free memory on termination
int configFileHandler::getSmart (int &i, 
								int **&sides,
								char *&dynamics,		 
								int &numberOfSides)
{			
	int m = 0;
	char tmpstr[20]; 
		
	while(i < lengthOfText && buffer[i] != '\n')
	{
		tmpstr[m] = buffer[i];
		m++;
		i++;
	}
	tmpstr[m + 1] = 0;
	i++;
	numberOfSides = atoi(tmpstr);
	cout<<"numberOfSides: "<<numberOfSides<<endl;
	
	sides = new int*[numberOfSides];
	if(!sides)
	{
		cout<<"ERROR - mem Alloc getSmart::sides\n";
		exit(1);
	}
	for(int s = 0; s < numberOfSides; s++)
	{
		sides[s] = new int[2];
		if(!sides[s])
		{
			cout<<"ERROR - mem Alloc getSmart::sides\n";
			exit(1);
		}
	}	
	for(int s = 0; s < numberOfSides; s++)
	{
		while(buffer[i++] == '\n');
		
		int p = 0;
		while(i < lengthOfText - 1 && buffer[i++] != ':')

		int p = 0;
		while(i < lengthOfText && isdigit(buffer[i]) )
			tmpstr[p++] = buffer[i++];
		tmpstr[p] = 0;
		sides[s][0] = atoi(tmpstr);
		i++;//because it is not a digit
		
		p = 0;
		while(i < lengthOfText && isdigit(buffer[i]) )
			tmpstr[p++] = buffer[i++];
		tmpstr[p] = 0;
		sides[s][1] = atoi(tmpstr);
		cout<<s<<":"<<sides[s][0]<<"-"<<sides[s][1]<<endl; 
	}
	i++;	
	if(i >= lengthOfText)
	{
		cout<<"ERROR - end of file in the middle of data\n";
		return 0;
	}
	return getDynamics(i, dynamics);
}


char* configFileHandler::getSmartChaperonData(int maxSizeOfResidueArray, 
				  						 	 point *structure, 
				  							 int index, 
											 int *sizeOfCurrentArray,
											 int **&modes,
											 int &numberOfModes,
											 char *&dynamics,
											 int **&sides,
			  								 char *&sideDynamics,		 
											 int &numberOfSides)
{
	char *confRes;
	int count = 0;
	bool continueSearch = true;
	int i;
	for(i = 0; i < lengthOfText && continueSearch; i++)
	{
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) < maxSizeOfResidueArray)
			{
				//cout<<"Count: "<<count<<" index: "<<index<<endl;
				if(count == index)
				{
					(*sizeOfCurrentArray) = atoi(tmpstr);
					//cout<<"size "<<(*sizeOfCurrentArray)<<endl;
					currentArrayPosition = i + 1;
					confRes = &buffer[currentArrayPosition];
					//cout<<"confRes: "<<(int)confRes<<endl;
					continueSearch = false;
				}
				else
					count++;
			}
		}
	}
	if(continueSearch == true)
	{
		//cout<<"configFileHandler: ERROR config file - no array length match found\n";
		return 0;
	}
	else
	{
		int done = 0;
		while(done < 4)
		{
		
			char tmpstr[20] = {0};

			getDataName(tmpstr, i);
			
	
			if(strcmp(tmpstr, "structure") == 0)
			{
				i++;
				getStructure(i, sizeOfCurrentArray, structure);
				done++;
			}
			else if(strcmp(tmpstr, "modes") == 0)
			{
				i++;
				getModes(i, *sizeOfCurrentArray, modes, numberOfModes);
				done++;
			
			}
			else if(strcmp(tmpstr, "dynamics") == 0)
			{
				cout<<tmpstr<<endl;
				i++;
				getDynamics(i, dynamics);
				done++;
				cout<<"done: "<<done<<endl;
			}
			else if(strcmp(tmpstr, "smart") == 0)
			{
					cout<<tmpstr<<endl;
					i++;
					done += getSmart(i, sides, sideDynamics, numberOfSides);
					cout<<"done doing getSmart: "<<done<<endl;
			}
		}
		
	}	
	return confRes;
}

int configFileHandler::getModes(int &i, 
								int sizeOfCurrentArray, 
								int **&modes,		 
								int &numberOfModes)
{			
	int m = 0;
	char tmpstr[20]; 
		
	while(i < lengthOfText && buffer[i] != '\n')
	{
		tmpstr[m] = buffer[i];
		m++;
		i++;
	}
	tmpstr[m + 1] = 0;
	i++;
	numberOfModes = atoi(tmpstr);
	cout<<"numberOfModes: "<<numberOfModes<<endl;
	
	modes = new int*[numberOfModes];
	if(!modes)
	{
		cout<<"ERROR - mem Alloc\n";
		exit(1);
	}
	
	for(int z = 0; z < numberOfModes; z++)
		if(!(modes[z] = new int[sizeOfCurrentArray]) )
		{
			cout<<"ERROR - mem Alloc\n";
			exit(1);
		}
				
	cout<<"Modes: \n";
	for(int z = 0; z < numberOfModes; z++)
	{
		while(!isalpha(buffer[i]))
				i++;
		for(int s = 0; s < sizeOfCurrentArray; s++, i++)
		{
			switch(buffer[i])
			{
				case 'H':
					modes[z][s] = HYDROPHOBIC; break;
 				case 'P':
					modes[z][s] = POLAR_NEUTRAL; break;
 				case '+':
					modes[z][s] = POSITIVE_CHARGE; break;	
				case '-':
					modes[z][s] = NEGATIVE_CHARGE; break;
			}
			cout<<modes[z][s];
		}
		cout<<endl;			
	}
	
	while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
		i++;
	
	if(buffer[i] == '[' || i == lengthOfText)
	{
		cout<<"configFileHandler: config file - no structure txt match found 2\n";
		return 0;
	}
	i++;
	return 1;
}


int configFileHandler::getStructure(int &i, int *&sizeOfCurrentArray, point *&structure)
{			
	int y = (*sizeOfCurrentArray)*2 - 1;
	int x = 0;
			
	bool keepGoing = true;
	int m;
	//cout<<"------------------------------------\n";
	for(; i < lengthOfText && keepGoing; i++)
	{		
		switch(buffer[i])
		{
			case  ' ':
						int s;
						for(s = 1; buffer[i] == ' ' && s < 4; s++, i++);
						if(s < 4)
						{
							cout<<"ERROR residue text space syntax\n";
							return 0;
						}
						x++;
						break;
					
			case '\n':
						y--;
						x = 0;
						break;
					
			case '(' :{
						i++;
						char strnum[10] = {0};
						while(buffer[i] == ' ')
							i++;
						m = 0;
						while(buffer[i] != ')')
							strnum[m++] = buffer[i++];
						if(atoi(strnum) > (*sizeOfCurrentArray))
						{
							cout<<"ERROR residue text index\n";
							return 0;
						}
						if(x >= (*sizeOfCurrentArray)*2 || y >= (*sizeOfCurrentArray)*2)
						{
							cout<<"ERROR size of y or x\n";
							cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
							return 0;
						}
						//cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
						structure[atoi(strnum)].x = x;
						structure[atoi(strnum)].y = y; 
						
						x++;
						break;
					}
			case '$' :	i++;
						keepGoing = false;
						break;
						
			default  :
						break;
		}
	}
	return 1;
}
		

int configFileHandler::getDataName(char *tmpstr, int &i)
{
	int m = 0;

	while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
		i++;
	if(buffer[i] == '[' || i == lengthOfText)
	{
		cout<<"configFileHandler: config file - no structure txt match found 3\n";
		return 0;
	}
		
	m = 0;
	i++;
		
	while(i < lengthOfText && buffer[i] != '\n')
	{
		tmpstr[m] = buffer[i];
		m++;
		i++;
	}
	tmpstr[m + 1] = 0;
	if(buffer[i] != '\n')
	{
		cout<<"configFileHandler: config file - ERROR syntax\n";
		return 0;
	}
	
	return 1;
}

char* configFileHandler::getChaperonData(int maxSizeOfResidueArray, 
				  						 point *structure, 
				  						 int index, 
										 int *sizeOfCurrentArray,
										 int **&modes,
										 int &numberOfModes,
										 char *&dynamics)
{
	char *confRes;
	int count = 0;
	bool continueSearch = true;
	int i;
	for(i = 0; i < lengthOfText && continueSearch; i++)
	{
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) < maxSizeOfResidueArray)
			{
				//cout<<"Count: "<<count<<" index: "<<index<<endl;
				if(count == index)
				{
					(*sizeOfCurrentArray) = atoi(tmpstr);
					//cout<<"size "<<(*sizeOfCurrentArray)<<endl;
					currentArrayPosition = i + 1;
					confRes = &buffer[currentArrayPosition];
					//cout<<"confRes: "<<(int)confRes<<endl;
					continueSearch = false;
				}
				else
					count++;
			}
		}
	}
	if(continueSearch == true)
	{
		//cout<<"configFileHandler: ERROR config file - no array length match found\n";
		return 0;
	}
	else
	{
		int done = 0;
		while(done < 3)
		{
		
			char tmpstr[20] = {0};

			getDataName(tmpstr, i);
			
	
			if(strcmp(tmpstr, "structure") == 0)
			{
				i++;
				getStructure(i, sizeOfCurrentArray, structure);
				done++;
			}
			else if(strcmp(tmpstr, "modes") == 0)
			{
				i++;
				getModes(i, *sizeOfCurrentArray, modes, numberOfModes);
				done++;
			
			}
			else if(strcmp(tmpstr, "dynamics") == 0)
			{
				i++;
				getDynamics(i, dynamics);
				done++;
				cout<<"done: "<<done<<endl;
			}
		}
		
	}	
	return confRes;
}



char* configFileHandler::readUnknownLengthTextStructure(int maxSizeOfResidueArray, 
				  						 point *structure, 
				  						 int index, int *sizeOfCurrentArray)
{
	char *confRes;
	int count = 0;
	bool continueSearch = true;
	int i;
	for(i = 0; i < lengthOfText && continueSearch; i++)
	{
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) < maxSizeOfResidueArray)
			{
				//cout<<"Count: "<<count<<" index: "<<index<<endl;
				if(count == index)
				{
					(*sizeOfCurrentArray) = atoi(tmpstr);
					//cout<<"size "<<(*sizeOfCurrentArray)<<endl;
					currentArrayPosition = i + 1;
					confRes = &buffer[currentArrayPosition];
					//cout<<"confRes: "<<(int)confRes<<endl;
					continueSearch = false;
				}
				else
					count++;
			}
		}
	}
	if(continueSearch == true)
	{
		//cout<<"configFileHandler: ERROR config file - no array length match found\n";
		return 0;
	}
	else
	{
		//get the structure:
		char tmpstr[20] = {0};
		int m = 0;
		do {
		while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
			i++;
		if(buffer[i] == '[' || i == lengthOfText)
		{
			cout<<"configFileHandler: config file - no structure txt match found 4\n";
			return 0;
		}
		
		m = 0;
		i++;
		
		while(i < lengthOfText && buffer[i] != '\n')
		{
			tmpstr[m] = buffer[i];
			m++;
			i++;
		}
		tmpstr[m + 1] = 0;
		if(buffer[i] != '\n')
		{
			cout<<"configFileHandler: config file - ERROR syntax\n";
			return 0;
		}
	}while(strcmp(tmpstr, "structure") != 0);
	
		if(strcmp(tmpstr, "structure") == 0)
		{
			i++;
			int y = (*sizeOfCurrentArray)*2 - 1;
			int x = 0;
			
			bool keepGoing = true;
			int m;
			//cout<<"------------------------------------\n";
			for(; i < lengthOfText && keepGoing; i++)
			{		
				switch(buffer[i])
				{
					case  ' ':
						int s;
						for(s = 1; buffer[i] == ' ' && s < 4; s++, i++);
						if(s < 4)
						{
							cout<<"ERROR residue text space syntax\n";
							return 0;
						}
						x++;
						break;
					
					case '\n':
						y--;
						x = 0;
						break;
					
					case '(' :{
						i++;
						char strnum[10] = {0};
						while(buffer[i] == ' ')
							i++;
						m = 0;
						while(buffer[i] != ')')
							strnum[m++] = buffer[i++];
						if(atoi(strnum) > (*sizeOfCurrentArray))
						{
							cout<<"ERROR residue text index\n";
							return 0;
						}
						if(x >= (*sizeOfCurrentArray)*2 || y >= (*sizeOfCurrentArray)*2)
						{
							cout<<"ERROR size of y or x\n";
							cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
							return 0;
						}
						//cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
						structure[atoi(strnum)].x = x;
						structure[atoi(strnum)].y = y; 
						
						x++;
						break;
					}
					case '$' :
						keepGoing = false;
						break;
						
					default  :
						break;
				}
			}
		}//end else if
	}//end for				
	//cout<<"return no prob\n";		
	return confRes;
}


configFileHandler::~configFileHandler()
{
	delete []buffer;	
}

int configFileHandler::init(char *name)
{
	strcpy(fileName, name);
	ifstream fi;

	struct stat statresults;
    if(stat(name, &statresults) != 0)
	{
    	cout<<"ERROR - file not fiound or size too small\n";
		return 0;  
	}
    
	buffer = new char[statresults.st_size + 4];

	fi.open(fileName);
	fi.get(buffer, statresults.st_size, EOF);
	fi.close();
	
	lengthOfText = strlen(buffer);
	if(lengthOfText < 10)
	{
		cout<<"ERROR config file too small\n";
		return 0;
	}
	return 1;
}

configFileHandler::configFileHandler(char *name, int sizeOfResidueArray, int index)
{
	strcpy(fileName, name);
	ifstream fi;
// 	cout<<"got to configFileHandler ctor "<<name<<", "<<sizeOfResidueArray<<" "<<index<<"\n";		
    struct stat statresults;
    if(stat(name, &statresults) != 0)
	{
    	cout<<"ERROR - file not found or size too small "<<name<<"\n";
		exit(0);  
	}
  currentArrayPosition = 0;  	
	buffer = new char[statresults.st_size + 4];
	
	fi.open(fileName);
	fi.get(buffer, statresults.st_size, EOF);
	fi.close();
	
	lengthOfText = strlen(buffer);
// 	cout<<"lengthOfText:"<<lengthOfText<<endl;
// 	cout<<"The file: \n"<<buffer<<endl;
	int count = 0;
	for(int i = 0; i < lengthOfText; i++)
	{
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10] = {0};
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			j++;
			tmpstr[j] = '\0';//NULL
			
// 			cout<<"tmpstr: "<<tmpstr<<" "<<i<<endl;	
			if(atoi(tmpstr) == sizeOfResidueArray)
			{
				if(count == index)
				{
					currentArrayPosition = i + 1;
					//cout<<"count: "<<count<<endl;
					return;
				}
				else
					count++;
			}
		}
	}
	cout<<"configFileHandler: ERROR config file - no array length match found "<<name<<endl<<count<<" "<<currentArrayPosition<<endl;
	exit(0);

}
//return -1 if not found
int configFileHandler::getStructureDBIndex(int sizeOfResidueArray, int index)
{
	int count = 0;
	for(int i = 0; i < lengthOfText; i++)
	{
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j = 0;
			while( (buffer[i] != ']')&&(i < lengthOfText) )
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			if(i == lengthOfText)
					return -1;
			
			tmpstr[++j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) == sizeOfResidueArray)
			{
				if(count == index)
				{
					while( (buffer[i] != '<')&&(i < lengthOfText) )
						i++;
					if(i == lengthOfText)
						return -1;
					
					char tmpIndex[12];
					int m = 0;
					i++;
					while( (buffer[i] != '>')&&(i < lengthOfText) )
					{
						tmpIndex[m] = buffer[i];
						m++;
						i++;
					}
					if(i == lengthOfText)
						return -1;
					
					tmpIndex[++m] = 0;//NULL
					//cout<<"tmpIndex: "<<tmpIndex<<endl;
					return atoi(tmpIndex);
					 
				}
				else
					count++;
			}
		}
	}
	//cout<<"configFileHandler: No more on DB\n";
	return -1;

}


char* configFileHandler::getConfiguration(int sizeOfResidueArray, int index)
{
	int count = 0;
	for(int i = 0; i < lengthOfText; i++)
	{
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) == sizeOfResidueArray)
			{
				//cout<<"Count: "<<count<<" index: "<<index<<endl;
				if(count == index)
				{
					currentArrayPosition = i + 1;
					return &buffer[currentArrayPosition];
				}
				else
					count++;
			}
		}
	}
// 	cout<<"configFileHandler: ERROR config file - no array length match found\n";
	return NULL;

}

#if 1
//Zero based input index
char* configFileHandler::readTextStructure(int sizeOfResidueArray, 
				  						 point *structure, 
				  						 int index)
{
	char *confRes;
	int count = -1;
	bool continueSearch = true;
	int i;
	for(i = 0; i < lengthOfText && continueSearch; i++)
	{
		if(buffer[i] == '#')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != '\n')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;
			count = atoi(tmpstr);
		}
		
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) == sizeOfResidueArray)
			{
				
				if(count == index)
				{
					currentArrayPosition = i + 1;
					confRes = &buffer[currentArrayPosition];
					//cout<<"confRes: "<<(int)confRes<<endl;
					continueSearch = false;
// 					cout<<"Count: "<<count<<" index: "<<index<<endl;
// 					for(int kk = 0; kk < sizeOfResidueArray; kk++) {
// 						cout<<buffer[i+kk+1];
// 					}
// 					cout<<endl;
				}
// 				else
// 					count++;
			}
		}
	}
	if(continueSearch == true)
	{
		//cout<<"configFileHandler: ERROR config file - no array length match found\n";
		return 0;
	}
	else
	{
		//get the structure:
		char tmpstr[20] = {0};
		int m = 0;
		do 
		{
		while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
			i++;
		if(buffer[i] == '[' || i == lengthOfText)
		{
			cout<<"configFileHandler: config file - no structure txt match found 5\n";
			return 0;
		}
		//char tmpstr[20] = {0};
		m = 0;
		i++;
		
		while(i < lengthOfText && buffer[i] != '\n')
		{
			tmpstr[m] = buffer[i];
			m++;
			i++;
		}
		tmpstr[m + 1] = 0;
		
		if(buffer[i] != '\n')
		{
			cout<<"configFileHandler: config file - ERROR syntax\n";
			return 0;
		}
	}while(strcmp(tmpstr, "structure") != 0);
	
		if(strcmp(tmpstr, "structure") == 0)
		{
			i++;
			int y = sizeOfResidueArray*2 - 1;
			int x = 0;
			
			bool keepGoing = true;
			int m;
			//cout<<"------------------------------------\n";
			for(; i < lengthOfText && keepGoing; i++)
			{		
				switch(buffer[i])
				{
					case  ' ':
						int s;
						for(s = 1; buffer[i] == ' ' && s < 4; s++, i++);
						if(s < 4)
						{
							cout<<"ERROR residue text space syntax\n";
							return 0;
						}
						x++;
						break;
					
					case '\n':
						y--;
						x = 0;
						break;
					
					case '(' :{
						i++;
						char strnum[10] = {0};
						while(buffer[i] == ' ')
							i++;
						m = 0;
						while(buffer[i] != ')')
							strnum[m++] = buffer[i++];
						if(atoi(strnum) > sizeOfResidueArray)
						{
							cout<<"ERROR residue text index\n";
							return 0;
						}
						if(x >= sizeOfResidueArray*2 || y >= sizeOfResidueArray*2)
						{
							cout<<"ERROR size of y or x\n";
							cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
							return 0;
						}
						//cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
						structure[atoi(strnum)].x = x;
						structure[atoi(strnum)].y = y; 
						
						x++;
						break;
					}
					case '$' :
						keepGoing = false;
						break;
						
					default  :
						break;
				}
			}
		}//end else if
	}//end for				
	//cout<<"return no prob\n";		
	return confRes;
}

char* configFileHandler::readTextStructureandNextDataLine(int sizeOfResidueArray, 
				  						 point *structure, char *addData,
				  						 int index)
{
	char *confRes;
	int count = 0;
	bool continueSearch = true;
	int i;
	for(i = 0; i < lengthOfText && continueSearch; i++)
	{
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) == sizeOfResidueArray)
			{
				//cout<<"Count: "<<count<<" index: "<<index<<endl;
				if(count == index)
				{
					currentArrayPosition = i + 1;
					confRes = &buffer[currentArrayPosition];
					//cout<<"confRes: "<<(int)confRes<<endl;
					continueSearch = false;
				}
				else
					count++;
			}
		}
	}
	if(continueSearch == true)
	{
		//cout<<"configFileHandler: ERROR config file - no array length match found\n";
		return 0;
	}
	else
	{
		//get the structure:
		char tmpstr[2000] = {0};
		int m = 0;
		do 
		{
		while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
			i++;
		if(buffer[i] == '[' || i == lengthOfText)
		{
			cout<<"configFileHandler: config file - no structure txt match found 5\n";
			return 0;
		}
		//char tmpstr[20] = {0};
		m = 0;
		i++;
		
		while(i < lengthOfText && buffer[i] != '\n')
		{
			tmpstr[m] = buffer[i];
			m++;
			i++;
		}
		tmpstr[m + 1] = 0;
		
		if(buffer[i] != '\n')
		{
			cout<<"configFileHandler: config file - ERROR syntax\n";
			return 0;
		}
	}while(strcmp(tmpstr, "structure") != 0);
	
		if(strcmp(tmpstr, "structure") == 0)
		{
			i++;
			int y = sizeOfResidueArray*2 - 1;
			int x = 0;
			
			bool keepGoing = true;
			int m;
			//cout<<"------------------------------------\n";
			for(; i < lengthOfText && keepGoing; i++)
			{		
				switch(buffer[i])
				{
					case  ' ':
						int s;
						for(s = 1; buffer[i] == ' ' && s < 4; s++, i++);
						if(s < 4)
						{
							cout<<"ERROR residue text space syntax\n";
							return 0;
						}
						x++;
						break;
					
					case '\n':
						y--;
						x = 0;
						break;
					
					case '(' :{
						i++;
						char strnum[10] = {0};
						while(buffer[i] == ' ')
							i++;
						m = 0;
						while(buffer[i] != ')')
							strnum[m++] = buffer[i++];
						if(atoi(strnum) > sizeOfResidueArray)
						{
							cout<<"ERROR residue text index\n";
							return 0;
						}
						if(x >= sizeOfResidueArray*2 || y >= sizeOfResidueArray*2)
						{
							cout<<"ERROR size of y or x\n";
							cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
							return 0;
						}
						//cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
						structure[atoi(strnum)].x = x;
						structure[atoi(strnum)].y = y; 
						
						x++;
						break;
					}
					case '$' :
						keepGoing = false;
						break;
						
					default  :
						break;
				}
			}
		}//end else if
	}//end for				
	//cout<<"return no prob\n";	
	char tmpstr[2000] = {0};
	int m = 0;
	i++;
	
	while(i < lengthOfText && buffer[i] != '\n')
	{
		tmpstr[m] = buffer[i];
		m++;
		i++;
	}
	tmpstr[m + 1] = 0;	
	strcpy(addData, tmpstr);
	return confRes;
}

char* configFileHandler::readDoubleDomainTextStructureGivenSequence(int sizeOfResidueArray, int domainSize, int linkerLength,
				  						 point *struct1, point *struct2, 
				  						 char *inseq, char *seq1, char *seq2, 
				  						 int minStructIdx)
{
	char *confRes;
	int count = 0;
	bool continueSearch = true;
	int i;
	for(i = 0; i < lengthOfText && continueSearch; i++)
	{
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) == sizeOfResidueArray)
			{
				//cout<<"Count: "<<count<<" index: "<<index<<endl;
				currentArrayPosition = i + 1;
				confRes = &buffer[currentArrayPosition];
					//cout<<"confRes: "<<(int)confRes<<endl;
// 					continueSearch = false;
				if(strncmp(confRes, inseq, sizeOfResidueArray) == 0) {
					if(minStructIdx == count) {
						continueSearch = false; 
					}
					count++;
				}
			}
		}
	}
	if(continueSearch == true)
	{
		cout<<"configFileHandler: didn't find struct for "<<inseq<<"\n";
		return 0;
	}
	else
	{
		int si;
		strncpy(seq1, confRes, domainSize);
		strncpy(seq2, &confRes[domainSize + linkerLength], domainSize);
		
// 		for(si = 0; si < domainSize; si++)
// 			seq1[si] = confRes[si];
// 		seq1[si] = '\0';
// 		for(si = domainSize + linkerLength; si < sizeOfResidueArray; si++)
// 			seq1[si] = confRes[si];
// 		seq2[si] = '\0';
		 
		//get the domain structures:
		char tmpstr[20] = {0};
		int m = 0;
		do 
		{
			while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
				i++;
			if(buffer[i] == '[' || i == lengthOfText)
			{
				cout<<"configFileHandler: config file - no structure txt match found 5\n";
				return 0;
			}
			//char tmpstr[20] = {0};
			m = 0;
			i++;
			
			while(i < lengthOfText && buffer[i] != '\n')
			{
				tmpstr[m] = buffer[i];
				m++;
				i++;
			}
			tmpstr[m + 1] = 0;
			
			if(buffer[i] != '\n')
			{
				cout<<"configFileHandler: config file - ERROR syntax\n";
				return 0;
			}
		}while(strcmp(tmpstr, "structure") != 0);
	
		if(strcmp(tmpstr, "structure") == 0)
		{
			i++;
			int y = domainSize*2 - 1;
			int x = 0;
			
			bool keepGoing = true;
			int m;
			//cout<<"------------------------------------\n";
			for(; i < lengthOfText && keepGoing; i++)
			{		
				switch(buffer[i])
				{
					case  ' ':
						int s;
						for(s = 1; buffer[i] == ' ' && s < 4; s++, i++);
						if(s < 4)
						{
							cout<<"ERROR residue text space syntax\n";
							return 0;
						}
						x++;
						break;
					
					case '\n':
						y--;
						x = 0;
						break;
					
					case '(' :{
						i++;
						char strnum[10] = {0};
						while(buffer[i] == ' ')
							i++;
						m = 0;
						while(buffer[i] != ')')
							strnum[m++] = buffer[i++];
						if(atoi(strnum) > domainSize)
						{
							cout<<"ERROR residue text index\n";
							return 0;
						}
						if(x >= domainSize*2 || y >= domainSize*2)
						{
							cout<<"ERROR size of y or x\n";
							cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
							return 0;
						}
						//cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
						struct1[atoi(strnum)].x = x;
						struct1[atoi(strnum)].y = y; 
						
						x++;
						break;
					}
					case '$' :
						keepGoing = false;
						break;
						
					default  :
						break;
				}
			}
		}//end else if
		
		//Second structure:
		do 
		{
			while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
				i++;
			if(buffer[i] == '[' || i == lengthOfText)
			{
				cout<<"configFileHandler: config file - no structure txt match found 5\n";
				return 0;
			}
			//char tmpstr[20] = {0};
			m = 0;
			i++;
			
			while(i < lengthOfText && buffer[i] != '\n')
			{
				tmpstr[m] = buffer[i];
				m++;
				i++;
			}
			tmpstr[m + 1] = 0;
			
			if(buffer[i] != '\n')
			{
				cout<<"configFileHandler: config file - ERROR syntax\n";
				return 0;
			}
		}while(strcmp(tmpstr, "structure") != 0);
		
		if(strcmp(tmpstr, "structure") == 0)
		{
			i++;
			int y = domainSize*2 - 1;
			int x = 0;
			
			bool keepGoing = true;
			int m;
			//cout<<"------------------------------------\n";
			for(; i < lengthOfText && keepGoing; i++)
			{		
				switch(buffer[i])
				{
					case  ' ':
						int s;
						for(s = 1; buffer[i] == ' ' && s < 4; s++, i++);
						if(s < 4)
						{
							cout<<"ERROR residue text space syntax\n";
							return 0;
						}
						x++;
						break;
					
					case '\n':
						y--;
						x = 0;
						break;
					
					case '(' :{
						i++;
						char strnum[10] = {0};
						while(buffer[i] == ' ')
							i++;
						m = 0;
						while(buffer[i] != ')')
							strnum[m++] = buffer[i++];
						if(atoi(strnum) > domainSize)
						{
							cout<<"ERROR residue text index\n";
							return 0;
						}
						if(x >= domainSize*2 || y >= domainSize*2)
						{
							cout<<"ERROR size of y or x\n";
							cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
							return 0;
						}
						//cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
						struct2[atoi(strnum)].x = x;
						struct2[atoi(strnum)].y = y; 
						
						x++;
						break;
					}
					case '$' :
						keepGoing = false;
						break;
						
					default  :
						break;
				}
			}
		}//end else if
		
	}//end for				
	//cout<<"return no prob\n";		
	return confRes;
}

char* configFileHandler::readTextStructureGivenSequence(int sizeOfResidueArray, 
				  						 point *structure, 
				  						 char *sequence, int minStructIdx)
{
	char *confRes;
	int count = 0;
	bool continueSearch = true;
	int i;
	for(i = 0; i < lengthOfText && continueSearch; i++)
	{
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) == sizeOfResidueArray)
			{
				//cout<<"Count: "<<count<<" index: "<<index<<endl;
				currentArrayPosition = i + 1;
				confRes = &buffer[currentArrayPosition];
					//cout<<"confRes: "<<(int)confRes<<endl;
// 					continueSearch = false;
				if(strncmp(confRes, sequence, sizeOfResidueArray) == 0) {
					if(minStructIdx == count) {
						continueSearch = false; 
					}
					count++;
				}
			}
		}
	}
	if(continueSearch == true)
	{
		cout<<"configFileHandler: didn't find struct for "<<sequence<<"\n";
		return 0;
	}
	else
	{
		//get the structure:
		char tmpstr[20] = {0};
		int m = 0;
		do 
		{
		while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
			i++;
		if(buffer[i] == '[' || i == lengthOfText)
		{
			cout<<"configFileHandler: config file - no structure txt match found 5\n";
			return 0;
		}
		//char tmpstr[20] = {0};
		m = 0;
		i++;
		
		while(i < lengthOfText && buffer[i] != '\n')
		{
			tmpstr[m] = buffer[i];
			m++;
			i++;
		}
		tmpstr[m + 1] = 0;
		
		if(buffer[i] != '\n')
		{
			cout<<"configFileHandler: config file - ERROR syntax\n";
			return 0;
		}
	}while(strcmp(tmpstr, "structure") != 0);
	
		if(strcmp(tmpstr, "structure") == 0)
		{
			i++;
			int y = sizeOfResidueArray*2 - 1;
			int x = 0;
			
			bool keepGoing = true;
			int m;
			//cout<<"------------------------------------\n";
			for(; i < lengthOfText && keepGoing; i++)
			{		
				switch(buffer[i])
				{
					case  ' ':
						int s;
						for(s = 1; buffer[i] == ' ' && s < 4; s++, i++);
						if(s < 4)
						{
							cout<<"ERROR residue text space syntax\n";
							return 0;
						}
						x++;
						break;
					
					case '\n':
						y--;
						x = 0;
						break;
					
					case '(' :{
						i++;
						char strnum[10] = {0};
						while(buffer[i] == ' ')
							i++;
						m = 0;
						while(buffer[i] != ')')
							strnum[m++] = buffer[i++];
						if(atoi(strnum) > sizeOfResidueArray)
						{
							cout<<"ERROR residue text index\n";
							return 0;
						}
						if(x >= sizeOfResidueArray*2 || y >= sizeOfResidueArray*2)
						{
							cout<<"ERROR size of y or x\n";
							cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
							return 0;
						}
						//cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
						structure[atoi(strnum)].x = x;
						structure[atoi(strnum)].y = y; 
						
						x++;
						break;
					}
					case '$' :
						keepGoing = false;
						break;
						
					default  :
						break;
				}
			}
		}//end else if
	}//end for				
	//cout<<"return no prob\n";		
	return confRes;
}

char* configFileHandler::readTextStructureGivenSequenceAndThermoData(int sizeOfResidueArray, 
				  						 point *structure, 
				  						 char *sequence, char *addData, int minStructIdx)
{
// 	cout<<"configFileHandler::readTextStructureGivenSequenceAndThermoData "<<minStructIdx<<endl;
	char *confRes;
	int count = 0;
	bool continueSearch = true;
	int i;
	int fromData, toData;
	
	for(i = 0; i < lengthOfText && continueSearch; i++)
	{
		if(buffer[i] == '#') {
			while(i < lengthOfText && buffer[i] != '\n') {
				i++;
			}
			fromData = i;
			while(i < lengthOfText && buffer[i] != '[') i++;
			toData = i-1;
			strncpy(addData, &buffer[fromData], toData - fromData + 1);
			addData[toData - fromData + 1] = 0;
		}
		
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) == sizeOfResidueArray)
			{
				//cout<<"Count: "<<count<<" index: "<<index<<endl;
				currentArrayPosition = i + 1;
				confRes = &buffer[currentArrayPosition];
					//cout<<"confRes: "<<(int)confRes<<endl;
// 					continueSearch = false;
				if(strncmp(confRes, sequence, sizeOfResidueArray) == 0) {
					if(minStructIdx == count) {
						continueSearch = false; 
// 						cout<<"Found: "<<count<<endl;
					}
					count++;
				}
			}
		}
	}
	if(continueSearch == true)
	{
		cout<<"configFileHandler: didn't find struct for "<<sequence<<"\n";
		return 0;
	}
	else
	{
		//get the structure:
		char tmpstr[20] = {0};
		int m = 0;
		do 
		{
		while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
			i++;
		if(buffer[i] == '[' || i == lengthOfText)
		{
			cout<<"configFileHandler: config file - no structure txt match found 5\n";
			return 0;
		}
		//char tmpstr[20] = {0};
		m = 0;
		i++;
		
		while(i < lengthOfText && buffer[i] != '\n')
		{
			tmpstr[m] = buffer[i];
			m++;
			i++;
		}
		tmpstr[m + 1] = 0;
		
		if(buffer[i] != '\n')
		{
			cout<<"configFileHandler: config file - ERROR syntax\n";
			return 0;
		}
	}while(strcmp(tmpstr, "structure") != 0);
	
		if(strcmp(tmpstr, "structure") == 0)
		{
			i++;
			int y = sizeOfResidueArray*2 - 1;
			int x = 0;
			
			bool keepGoing = true;
			int m;
			//cout<<"------------------------------------\n";
			for(; i < lengthOfText && keepGoing; i++)
			{		
				switch(buffer[i])
				{
					case  ' ':
						int s;
						for(s = 1; buffer[i] == ' ' && s < 4; s++, i++);
						if(s < 4)
						{
							cout<<"ERROR residue text space syntax\n";
							return 0;
						}
						x++;
						break;
					
					case '\n':
						y--;
						x = 0;
						break;
					
					case '(' :{
						i++;
						char strnum[10] = {0};
						while(buffer[i] == ' ')
							i++;
						m = 0;
						while(buffer[i] != ')')
							strnum[m++] = buffer[i++];
						if(atoi(strnum) > sizeOfResidueArray)
						{
							cout<<"ERROR residue text index\n";
							return 0;
						}
						if(x >= sizeOfResidueArray*2 || y >= sizeOfResidueArray*2)
						{
							cout<<"ERROR size of y or x\n";
							cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
							return 0;
						}
						//cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
						structure[atoi(strnum)].x = x;
						structure[atoi(strnum)].y = y; 
						
						x++;
						break;
					}
					case '$' :
						keepGoing = false;
						break;
						
					default  :
						break;
				}
			}
		}//end else if
	}//end for				
	//cout<<"return no prob\n";		
	return confRes;
}

#endif
char* configFileHandler::dimer_readTextStructure(int sizeOfResidueArray, 
				  						 		 point *structure, 
												 int linkerLength,
				  						 		 int index)
{
	char *confRes;
	int count = 0;
	bool continueSearch = true;
	int i;
	char tmpstr[20] = {0};
	int m = 0;
	
	int y = sizeOfResidueArray*2 - 1;
	int x = 0;

	for(i = 0; i < lengthOfText && continueSearch; i++)
	{
		if(buffer[i] == '[')
		{
			i++;
			char tmpstr[10];
			int j =0;
			while(buffer[i] != ']')
			{
				tmpstr[j] = buffer[i];
				j++;
				i++;
			}
			tmpstr[j] = 0;//NULL
			
			//cout<<"tmpstr:"<<tmpstr<<endl;	
			if(atoi(tmpstr) == sizeOfResidueArray)
			{
				//cout<<"Count: "<<count<<" index: "<<index<<endl;
				if(count == index)
				{
					currentArrayPosition = i + 1;
					confRes = &buffer[currentArrayPosition];
					//cout<<"confRes: "<<(int)confRes<<endl;
					continueSearch = false;
				}
				else
					count++;
			}
		}
	}
	if(continueSearch == true)
	{
		//cout<<"configFileHandler: ERROR config file - no array length match found\n";
		return 0;
	}
	else
	{
		//get the structure:
		
		do 
		{
		while(i < lengthOfText && buffer[i] != '$' && buffer[i] != '[')
			i++;
		if(buffer[i] == '[' || i == lengthOfText)
		{
			cout<<"configFileHandler: config file - no structure txt match found 5\n";
			return 0;
		}
		//char tmpstr[20] = {0};
		m = 0;
		i++;
		
		while(i < lengthOfText && buffer[i] != '\n')
		{
			tmpstr[m] = buffer[i];
			m++;
			i++;
		}
		tmpstr[m + 1] = 0;
		
		if(buffer[i] != '\n')
		{
			cout<<"configFileHandler: config file - ERROR syntax\n";
			return 0;
		}
	}while(strcmp(tmpstr, "structure") != 0);
	
	
		if(strcmp(tmpstr, "structure") == 0)
		{
			i++;
			bool keepGoing = true;
			int m;
			//cout<<"------------------------------------\n";
			for(; i < lengthOfText && keepGoing; i++)
			{		
				switch(buffer[i])
				{
					case  ' ':
						int s;
						for(s = 1; buffer[i] == ' ' && s < 4; s++, i++);
						if(s < 4)
						{
							cout<<"ERROR residue text space syntax\n";
							return 0;
						}
						x++;
						break;
					
					case '\n':
						y--;
						x = 0;
						break;
					
					case '(' :{
						i++;
						char strnum[10] = {0};
						while(buffer[i] == ' ')
							i++;
						m = 0;
						while(buffer[i] != ')')
							strnum[m++] = buffer[i++];
						if(atoi(strnum) > sizeOfResidueArray)
						{
							cout<<"ERROR residue text index\n";
							return 0;
						}
						if(x >= sizeOfResidueArray*2 || y >= sizeOfResidueArray*2)
						{
							cout<<"ERROR size of y or x\n";
							cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
							return 0;
						}
						//cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
						structure[atoi(strnum)].x = x;
						structure[atoi(strnum)].y = y; 
						
						x++;
						break;
					}
					case '$' :
						keepGoing = false;
						break;
						
					default  :
						break;
				}
			}
		}//end else if
	}//end outer for
	y--;
	x = 0;
	int startSecond = (sizeOfResidueArray - linkerLength)/2 + 1;
	int endPoint = sizeOfResidueArray;
	for(int place = 0; place < linkerLength; place++)
	{
		structure[startSecond].y = y;
		structure[startSecond++].x = x++;
	}
	y--;
	startSecond--;
	x = 0;
	y--;
	//second monomer
	while(i < lengthOfText && buffer[i] != '$')
		i++;
	
		m = 0;
		i++;
		
		while(i < lengthOfText && buffer[i] != '\n')
		{
			tmpstr[m] = buffer[i];
			m++;
			i++;
		}
		tmpstr[m + 1] = 0;
		
		if(buffer[i] != '\n')
		{
			cout<<"configFileHandler: config file - ERROR syntax\n";
			return 0;
		}
		
		if(strcmp(tmpstr, "structure") == 0)
		{
			i++;
			//int y = sizeOfResidueArray*2 - 1;
			//int x = 0;
			
			bool keepGoing = true;
			int m;
			//cout<<"------------------------------------\n";
			for(; i < lengthOfText && keepGoing; i++)
			{		
				switch(buffer[i])
				{
					case  ' ':
						int s;
						for(s = 1; buffer[i] == ' ' && s < 4; s++, i++);
						if(s < 4)
						{
							cout<<"ERROR residue text space syntax\n";
							return 0;
						}
						x++;
						break;
					
					case '\n':
						y--;
						x = 0;
						break;
					
					case '(' :{
						i++;
						char strnum[10] = {0};
						while(buffer[i] == ' ')
							i++;
						m = 0;
						while(buffer[i] != ')')
							strnum[m++] = buffer[i++];
						if(atoi(strnum) > sizeOfResidueArray)
						{
							cout<<"ERROR residue text index\n";
							return 0;
						}
						if(x >= sizeOfResidueArray*2 || y >= sizeOfResidueArray*2)
						{
							cout<<"ERROR size of y or x\n";
							cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
							return 0;
						}
						//cout<<"("<<x<<", "<<y<<") "<<atoi(strnum)<<endl;
						structure[startSecond + atoi(strnum)].x = x;
						structure[startSecond + atoi(strnum)].y = y; 
						
						x++;
						break;
					}
					case '$' :
						keepGoing = false;
						break;
						
					default  :
						break;
				}
			}//end  for
		}//if struct
		else
		{
			cout<<"configFileHandler: config file - ERROR syntax - not a dimer\n";
			return 0;
		}			
	//cout<<"return no prob\n";		
	return confRes;
}

int configFileHandler::generateDimerTextStructure(int index1, int index2, 
												  int originalSize,
												  int linkerSize)
{
	point structure1[1024], structure2[1024];
	char *hp1,*hp2;
	
	if(originalSize*2 + linkerSize > 1024)
	{
		cout<<"ERROR - size too big\n";
		return 0;
	}
	
	if( (hp1 = readTextStructure(originalSize, structure1, index1)) == 0)
	{
		cout<<"could not Get index: "<<index1<<endl;
		return 0;
	}
	
	if( (hp2 = readTextStructure(originalSize, structure2, index2)) == 0)
	{
		cout<<"could not Get index: "<<index2<<endl;
		return 0;
	}

	bool begin1 = false, begin2 = false;
	bool end1 = false, end2 = false;
	
	int **matrix = new int*[originalSize*2 + 2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < originalSize*2 + 2; i++)
	{
		if( !(matrix[i] = new int[originalSize*2 + 2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < originalSize*2 + 2; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 1; i <= originalSize; i++)
		matrix[structure1[i].y + 1][structure1[i].x + 1] = i;

	//end:
	if( (matrix[structure1[originalSize].y + 1 - 1][structure1[originalSize].x + 1] == 0) ||//up
		(matrix[structure1[originalSize].y + 1 + 1][structure1[originalSize].x + 1] == 0) ||//down
		(matrix[structure1[originalSize].y + 1][structure1[originalSize].x + 1 - 1] == 0) ||//left
		(matrix[structure1[originalSize].y + 1][structure1[originalSize].x + 1 + 1] == 0))//right
			end1 = true;
	//begin:
	if( (matrix[structure1[1].y + 1 - 1][structure1[1].x + 1] == 0) ||//up
		(matrix[structure1[1].y + 1 + 1][structure1[1].x + 1] == 0) ||//down
		(matrix[structure1[1].y + 1][structure1[1].x + 1 - 1] == 0) ||//left
		(matrix[structure1[1].y + 1][structure1[1].x + 1 + 1] == 0))//right
			begin1 = true;

	for(int i = 0; i < originalSize*2 + 2; i++)
	{
		for(int j = 0; j < originalSize*2 + 2; j++)
			matrix[i][j] = 0;		
	}
	
	for(int i = 1; i <= originalSize; i++)
		matrix[structure2[i].y + 1][structure2[i].x + 1] = i;
	
		//end:
	if( (matrix[structure2[originalSize].y + 1 - 1][structure2[originalSize].x + 1] == 0) ||//up
		(matrix[structure2[originalSize].y + 1 + 1][structure2[originalSize].x + 1] == 0) ||//down
		(matrix[structure2[originalSize].y + 1][structure2[originalSize].x + 1 - 1] == 0) ||//left
		(matrix[structure2[originalSize].y + 1][structure2[originalSize].x + 1 + 1] == 0))//right
			end2 = true;
	//begin:
	if( (matrix[structure2[1].y + 1 - 1][structure2[1].x + 1] == 0) ||//up
		(matrix[structure2[1].y + 1 + 1][structure2[1].x + 1] == 0) ||//down
		(matrix[structure2[1].y + 1][structure2[1].x + 1 - 1] == 0) ||//left
		(matrix[structure2[1].y + 1][structure2[1].x + 1 + 1] == 0))//right
			begin2 = true;
	
	for(int i = 0; i < originalSize*2 + 2 ; i++)
		delete []matrix[i];
	delete []matrix;

	//always take first point of structure1 to first point of structure2
	point tmpStruct1[1024];
	point tmpStruct2[1024];
	
	bool identical = true;
	for(int i = 0; i < originalSize; i++)
	{
		if(hp2[i] != hp1[i])
		{
			identical = false;
			break;
		}
	}
		
	if(end1 && begin2)//-->-->
	{
		for(int i = 1; i <= originalSize; i++)
			tmpStruct1[i] = structure1[i];
		for(int i = 1; i <= originalSize; i++)
			tmpStruct2[i] = structure2[i];
		
		cout<<"["<<originalSize*2 + linkerSize<<"]";
		for(int i = 0; i < originalSize; i++)
			cout<<hp1[i];
		for(int i = 0; i < linkerSize; i++)
			cout<<"P"; 
		for(int i = 0; i < originalSize; i++)
			cout<<hp2[i];
		cout<<endl;
		writeStructure2output(originalSize, tmpStruct1);
		writeStructure2output(originalSize, tmpStruct2);
		cout<<"-----------------------------------------------------\n";
	}
	
	if(end1 && end2)//--><--
	{
		for(int i = 1; i <= originalSize; i++)
			tmpStruct1[i] = structure1[i];
		for(int i = 1; i <= originalSize; i++)
			tmpStruct2[originalSize - i + 1] = structure2[i];
		
		cout<<"["<<originalSize*2 + linkerSize<<"]";
		for(int i = 0; i < originalSize; i++)
			cout<<hp1[i];
		for(int i = 0; i < linkerSize; i++)
			cout<<"P"; 
		for(int i = originalSize - 1; i >= 0; i--)
			cout<<hp2[i];
		cout<<endl;
		
		writeStructure2output(originalSize, tmpStruct1);
		writeStructure2output(originalSize, tmpStruct2);
		cout<<"-----------------------------------------------------\n";
	}
	
	if(begin1 && begin2)//<---->
	{
		for(int i = 1; i <= originalSize; i++)
			tmpStruct1[originalSize - i + 1] = structure1[i];
		for(int i = 1; i <= originalSize; i++)
			tmpStruct2[i] = structure2[i];
		
		cout<<"["<<originalSize*2 + linkerSize<<"]";
		for(int i = originalSize - 1; i >= 0; i--)
			cout<<hp1[i];
		for(int i = 0; i < linkerSize; i++)
			cout<<"P"; 
		for(int i = 0; i < originalSize; i++)
			cout<<hp2[i];
		cout<<endl;
		
		writeStructure2output(originalSize, tmpStruct1);
		writeStructure2output(originalSize, tmpStruct2);
		cout<<"-----------------------------------------------------\n";
	}
	
	if(begin1 && end2 && !identical)//<--<--
	{
		for(int i = 1; i <= originalSize; i++)
			tmpStruct2[i] = structure1[i];
		for(int i = 1; i <= originalSize; i++)
			tmpStruct1[i] = structure2[i];
		
		cout<<"["<<originalSize*2 + linkerSize<<"]";
		for(int i = 0; i < originalSize; i++)
			cout<<hp2[i];
		for(int i = 0; i < linkerSize; i++)
			cout<<"P"; 
		for(int i = 0; i < originalSize; i++)
			cout<<hp1[i];
		cout<<endl;
		writeStructure2output(originalSize, tmpStruct1);
		writeStructure2output(originalSize, tmpStruct2);
		cout<<"-----------------------------------------------------\n";
	}
	
	return 1;
}


int configFileHandler::generateDimerTextStructureFromTwoFiles
												 (int index1, int index2, 
												  int originalSize,
												  int linkerSize,
												  char *fn2)
{
	configFileHandler cfh2(fn2, originalSize, 0);

	point structure1[1024], structure2[1024];
	char *hp1,*hp2;
	
	if(originalSize*2 + linkerSize > 1024)
	{
		cout<<"ERROR - size too big\n";
		return 0;
	}
	
	if( (hp1 = readTextStructure(originalSize, structure1, index1)) == 0)
	{
		cout<<"could not Get index: "<<index1<<endl;
		return 0;
	}
	
	if( (hp2 = cfh2.readTextStructure(originalSize, structure2, index2)) == 0)
	{
		cout<<"could not Get index: "<<index2<<endl;
		return 0;
	}

	bool begin1 = false, begin2 = false;
	bool end1 = false, end2 = false;
	
	int **matrix = new int*[originalSize*2 + 2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < originalSize*2 + 2; i++)
	{
		if( !(matrix[i] = new int[originalSize*2 + 2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < originalSize*2 + 2; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 1; i <= originalSize; i++)
		matrix[structure1[i].y + 1][structure1[i].x + 1] = i;

	//end:
	if(recursiveIsExternalEdge(structure1[originalSize], matrix, originalSize)) {
// 		cout<<"Has an edge end1"<<endl;
		end1 = true;
	}
	if(recursiveIsExternalEdge(structure1[1], matrix, originalSize)) {
// 		cout<<"Has an edge begin1"<<endl;
		begin1 = true;
	}
	for(int i = 0; i < originalSize*2 + 2; i++)
	{
		for(int j = 0; j < originalSize*2 + 2; j++)
			matrix[i][j] = 0;		
	}
	
	for(int i = 1; i <= originalSize; i++)
		matrix[structure2[i].y + 1][structure2[i].x + 1] = i;

	if(recursiveIsExternalEdge(structure2[originalSize], matrix, originalSize)) {
// 		cout<<"Has an edge end2"<<endl;
		end2 = true;
	}
	if(recursiveIsExternalEdge(structure2[1], matrix, originalSize)) {
// 		cout<<"Has an edge begin2"<<endl;
		begin2 = true;
	}
	
	
	for(int i = 0; i < originalSize*2 + 2 ; i++)
		delete []matrix[i];
	delete []matrix;

	//always take first point of structure1 to first point of structure2
	point tmpStruct1[1024];
	point tmpStruct2[1024];
	
	bool identical = true;
	for(int i = 0; i < originalSize; i++)
	{
		if(hp2[i] != hp1[i])
		{
			identical = false;
			break;
		}
	}
		
	if(end1 && begin2)//-->-->
	{
		for(int i = 1; i <= originalSize; i++)
			tmpStruct1[i] = structure1[i];
		for(int i = 1; i <= originalSize; i++)
			tmpStruct2[i] = structure2[i];
		
		cout<<"["<<originalSize*2 + linkerSize<<"]";
		for(int i = 0; i < originalSize; i++)
			cout<<hp1[i];
		for(int i = 0; i < linkerSize; i++)
			cout<<"P"; 
		for(int i = 0; i < originalSize; i++)
			cout<<hp2[i];
		cout<<endl;
		writeStructure2output(originalSize, tmpStruct1);
		writeStructure2output(originalSize, tmpStruct2);
		cout<<"-----------------------------------------------------\n";
	}
	else {
		cout<<"No edges to create structure\n";
	}
#if 0
	if(end1 && end2)//--><--
	{
		for(int i = 1; i <= originalSize; i++)
			tmpStruct1[i] = structure1[i];
		for(int i = 1; i <= originalSize; i++)
			tmpStruct2[originalSize - i + 1] = structure2[i];
		
		cout<<"["<<originalSize*2 + linkerSize<<"]";
		for(int i = 0; i < originalSize; i++)
			cout<<hp1[i];
		for(int i = 0; i < linkerSize; i++)
			cout<<"P"; 
		for(int i = originalSize - 1; i >= 0; i--)
			cout<<hp2[i];
		cout<<endl;
		
		writeStructure2output(originalSize, tmpStruct1);
		writeStructure2output(originalSize, tmpStruct2);
		cout<<"-----------------------------------------------------\n";
	}
	
	if(begin1 && begin2)//<---->
	{
		for(int i = 1; i <= originalSize; i++)
			tmpStruct1[originalSize - i + 1] = structure1[i];
		for(int i = 1; i <= originalSize; i++)
			tmpStruct2[i] = structure2[i];
		
		cout<<"["<<originalSize*2 + linkerSize<<"]";
		for(int i = originalSize - 1; i >= 0; i--)
			cout<<hp1[i];
		for(int i = 0; i < linkerSize; i++)
			cout<<"P"; 
		for(int i = 0; i < originalSize; i++)
			cout<<hp2[i];
		cout<<endl;
		
		writeStructure2output(originalSize, tmpStruct1);
		writeStructure2output(originalSize, tmpStruct2);
		cout<<"-----------------------------------------------------\n";
	}
	
	if(begin1 && end2 && !identical)//<--<--
	{
		for(int i = 1; i <= originalSize; i++)
			tmpStruct2[i] = structure1[i];
		for(int i = 1; i <= originalSize; i++)
			tmpStruct1[i] = structure2[i];
		
		cout<<"["<<originalSize*2 + linkerSize<<"]";
		for(int i = 0; i < originalSize; i++)
			cout<<hp2[i];
		for(int i = 0; i < linkerSize; i++)
			cout<<"P"; 
		for(int i = 0; i < originalSize; i++)
			cout<<hp1[i];
		cout<<endl;
		writeStructure2output(originalSize, tmpStruct1);
		writeStructure2output(originalSize, tmpStruct2);
		cout<<"-----------------------------------------------------\n";
	}
#endif	
	return 1;
}
	
char* configFileHandler::getHPconfiguration()
{

	return &buffer[currentArrayPosition];
}

int configFileHandler::writeStructure2output(int sizeOfResidueArray, 
						point *structure, 
						char *confRes) 
{
	int **matrix = new int*[sizeOfResidueArray*6];
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < sizeOfResidueArray*6; i++)
	{
		if( !(matrix[i] = new int[sizeOfResidueArray*6]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < sizeOfResidueArray*6; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
		matrix[structure[i].y][structure[i].x] = i;


	int Xmin, Xmax, Ymin, Ymax;
	getMatrixBounds(matrix, sizeOfResidueArray*6, &Xmin, &Xmax, &Ymin, &Ymax);
	
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
				
	for(int i = 0; i < sizeOfResidueArray*6; i++)
		delete []matrix[i];
	
	delete []matrix;
	 
	return 1;
}

int configFileHandler::writeContactMap2Output(int sizeOfResidueArray, point *structure, char *confRes)
{
	int **matrix = new int*[sizeOfResidueArray*2];
	int **CM = new int*[sizeOfResidueArray+1];
	
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
	
	for(int i = 1; i <= sizeOfResidueArray; i++) {
		matrix[structure[i].y][structure[i].x] = i;
	}
	
	if(!CM)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i <= sizeOfResidueArray; i++)
	{
		if( !(CM[i] = new int[sizeOfResidueArray+1]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j <= sizeOfResidueArray; j++)
			CM[i][j] = 0;
			
	}
	
	

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
				
	cout<<"Min Max X: "<<Xmin<<" "<<Xmax<<endl;
	cout<<"Min Max Y: "<<Ymin<<" "<<Ymax<<endl;
	
	for(int i = 1; i <= sizeOfResidueArray; i++) {
// 		cout<<structure[i].y<<" "<<structure[i].x<<"\t";
		int y = structure[i].y;
		int x = structure[i].x;

		if(y == 0) {
			CM[i][0] = 1;
			CM[0][i] = 1;
		}
		else if(matrix[y - 1][x] == 0 || (matrix[y - 1][x] - i > 2 || matrix[y - 1][x] - i < -2)) {
			CM[i][matrix[y - 1][x]] = 1;
			CM[matrix[y - 1][x]][i] = 1;
		}
		if(y >= sizeOfResidueArray*2 - 1) {
			CM[i][0] = 1;
			CM[0][i] = 1;
		}
		else if(matrix[y + 1][x] == 0 || (matrix[y + 1][x] - i > 2 || matrix[y + 1][x] - i < -2)) {
			CM[i][matrix[y + 1][x]] = 1;
			CM[matrix[y + 1][x]][i] = 1;
		}
		if(x == 0) {
			CM[i][0] = 1;
			CM[0][i] = 1;
		}
		else if(matrix[y][x - 1] == 0 || (matrix[y][x - 1] - i > 2 || matrix[y][x - 1] - i < -2)) {
			CM[i][matrix[y][x - 1]] = 1;
			CM[matrix[y][x - 1]][i] = 1;
		}
		if(x >= sizeOfResidueArray*2 - 1) { 
			CM[i][0] = 1;
			CM[0][i] = 1;
		}
		else if(matrix[y][x + 1] == 0 || (matrix[y][x + 1] - i > 2 || matrix[y][x + 1] - i < -2)) {
			CM[i][matrix[y][x + 1]] = 1;
			CM[matrix[y][x + 1]][i] = 1;
		}
// 		CM[matrix[structure[i].y - 1][structure[i].x]][i] = 1;
// 		CM[matrix[structure[i].y + 1][structure[i].x]][i] = 1;
// 		CM[matrix[structure[i].y][structure[i].x - 1]][i] = 1;
// 		CM[matrix[structure[i].y][structure[i].x + 1]][i] = 1;
	}
	cout<<"\n$contact map\n\n-  ";
	for(int i = 0; i <= 9; i++) 
		cout<<i<<"  ";
	for(int i = 10; i <= sizeOfResidueArray; i++) 
		cout<<i<<" ";
	cout<<endl;
	for(int i = 0; i <= 9; i++) {
		cout<<i<<"  ";
		for(int j = 0; j <= sizeOfResidueArray; j++) 
			cout<<CM[i][j]<<"  ";
		cout<<endl;
	}
	for(int i = 10; i <= sizeOfResidueArray; i++) {
		cout<<i<<" ";
		for(int j = 0; j <= sizeOfResidueArray; j++) 
			cout<<CM[i][j]<<"  ";
		cout<<endl;
	}
	cout<<"$\n";
	cout<<"\n\n$Contact vector:\n\n";
	
	cout<<"Contact_0_1 ";
	for(int i = 0; i <= sizeOfResidueArray - 2; i++) 
		for(int j = i + 2; j <= sizeOfResidueArray; j++) 
			cout<<"Contact_"<<i<<"_"<<j<<" ";
	cout<<endl;
	
	cout<<CM[0][1]<<" ";
	for(int i = 0; i <= sizeOfResidueArray - 2; i++) 
		for(int j = i + 2; j <= sizeOfResidueArray; j++) 
			cout<<CM[i][j]<<" ";
	cout<<endl<<"$\n";	
// 	for(int j = 0; j <= 9; j++) 
// 			cout<<CM[i][j]<<"  ";
// 	for(int j = 10; j <= sizeOfResidueArray; j++) 
// 			cout<<CM[i][j]<<" ";
// 		
// 		cout<<endl;
// 	}
	for(int i = 0; i < sizeOfResidueArray*2; i++)
		delete []matrix[i];
	
	delete []matrix;
	delete []CM; 
	return 1;
}

int configFileHandler::writeStructure2file(int sizeOfResidueArray, 
						point *structure, 
						char *confRes,
						ofstream &of) 
{
	int msize = sizeOfResidueArray*8 + 1;
	int **matrix = new int*[msize];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < msize; i++)
	{
		if( !(matrix[i] = new int[msize]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < msize; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
		matrix[structure[i].y][structure[i].x] = i;


	int Xmin, Xmax, Ymin, Ymax;
	getMatrixBounds(matrix, msize, &Xmin, &Xmax, &Ymin, &Ymax);
	
	if(confRes)
	{
		of<<"\n["<<sizeOfResidueArray<<"]";
		for(int i = 0; i < sizeOfResidueArray; i++)
			of<<confRes[i];
		of<<endl<<endl;

		for(int y = Ymax; y >= Ymin; y--)
		{
			for(int x = Xmin; x <= Xmax; x++)
			{
				if(matrix[y][x])
					of<<confRes[matrix[y][x] - 1];
				else
					of<<" ";
			}
			of<<endl;
		}
	}

	of<<"\n$structure\n";
	for(int y = Ymax; y >= Ymin; y--)
	{
		for(int x = Xmin; x <= Xmax; x++)
		{
			if(matrix[y][x] > 9)
				of<<"("<<matrix[y][x]<<")";
			else if(matrix[y][x] > 0)
				of<<"( "<<matrix[y][x]<<")";
			if(!matrix[y][x])
				of<<"    ";
		}
		of<<endl;
	}
	of<<"$\n";
				
	for(int i = 0; i < msize; i++)
		delete []matrix[i];
	
	delete []matrix;
	 
	return 1;
}

int configFileHandler::readBinStructure(char *fn, point *structure, int idx)
{
	FILE *fp = fopen(fn, "rb"); 
	
	if(!fp)
	{
		cout<<"Error io - failbit - open r/w file\n";
		exit(0);
	}
	
	int sizeOfResidueArray = -1;
	fread(&sizeOfResidueArray, sizeof(int), 1, fp);
	
	
	if( (sizeOfResidueArray <= 0) || (sizeOfResidueArray > 10000) )
	{
		cout<<"Error input file: "<<sizeOfResidueArray<<endl;
		exit(0);
	}

	if(fseek(fp, sizeof(int)*sizeOfResidueArray, 1) < 0)
	{
		cout<<"Error -fseek\n";
		exit(0);
	}

	int numberOfStructures;
	fread(&numberOfStructures, sizeof(double), 1, fp);

	//idx begins from zero
	if(fseek(fp, sizeof(int)*2*sizeOfResidueArray*idx, 1) < 0)
	{
		cout<<"Error -fseek\n";
		exit(0);
	}

	
	if(numberOfStructures)
	{
		for(int i = 1; i <= sizeOfResidueArray; i++)
		{
			
			if(fread(&structure[i].x, sizeof(int), 1, fp) != 1)
				return 0;
			if(fread(&structure[i].y, sizeof(int), 1, fp) != 1)
				return 0;
			//cout<<res[i].position;
			
		}
		fclose(fp);
		return 1;
	}
	else
	{
		fclose(fp);
		return 0;
	}
}

int configFileHandler::writeStructure2output(int sizeOfResidueArray, 
											 residueArray *structure) 
{
	int **matrix = new int*[sizeOfResidueArray*6];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < sizeOfResidueArray*6; i++)
	{
		if( !(matrix[i] = new int[sizeOfResidueArray*6]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < sizeOfResidueArray*6; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
		matrix[structure->res[i].position.y][structure->res[i].position.x] = i;


	int Xmin, Xmax, Ymin, Ymax;
	getMatrixBounds(matrix, sizeOfResidueArray*6, &Xmin, &Xmax, &Ymin, &Ymax);
	
		cout<<"\n["<<sizeOfResidueArray<<"]";
		for(int i = 1; i <= sizeOfResidueArray; i++)
		{
			char sign;
			switch(structure->res[i].mode)
			{
				case HYDROPHOBIC:
					sign  = 'H'; break;
 				case POLAR_NEUTRAL:
					sign  = 'P'; break;
 				case POSITIVE_CHARGE:
					sign  = '+'; break;	
				case NEGATIVE_CHARGE:
					sign  = '-'; break;
			}
			cout<<sign;
		}

		cout<<endl<<endl;

		for(int y = Ymax; y >= Ymin; y--)
		{
			for(int x = Xmin; x <= Xmax; x++)
			{
				char sign;
				if(matrix[y][x])
				{
					switch(structure->res[matrix[y][x]].mode)
					{
						case HYDROPHOBIC:
							sign  = 'H'; break;
 						case POLAR_NEUTRAL:
							sign  = 'P'; break;
 						case POSITIVE_CHARGE:
							sign  = '+'; break;	
						case NEGATIVE_CHARGE:
							sign  = '-'; break;
					}
					cout<<sign;
				}
				else
					cout<<" ";
			}
			cout<<endl;
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
	
				
	for(int i = 0; i < sizeOfResidueArray*6; i++)
		delete []matrix[i];
	
	delete []matrix;
	 
	return 1;
}

int configFileHandler::writeStructure2file(int sizeOfResidueArray, 
											 											 residueArray *structure, 
											 											 ofstream &of) 
{
	int **matrix = new int*[sizeOfResidueArray*4];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < sizeOfResidueArray*4; i++)
	{
		if( !(matrix[i] = new int[sizeOfResidueArray*4]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < sizeOfResidueArray*4; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
		matrix[structure->res[i].position.y][structure->res[i].position.x] = i;


	int Xmin, Xmax, Ymin, Ymax;
	getMatrixBounds(matrix, sizeOfResidueArray*4, &Xmin, &Xmax, &Ymin, &Ymax);
	
		of<<"\n["<<sizeOfResidueArray<<"]";
		for(int i = 1; i <= sizeOfResidueArray; i++)
		{
			char sign;
			switch(structure->res[i].mode)
			{
				case HYDROPHOBIC:
					sign  = 'H'; break;
 				case POLAR_NEUTRAL:
					sign  = 'P'; break;
 				case POSITIVE_CHARGE:
					sign  = '+'; break;	
				case NEGATIVE_CHARGE:
					sign  = '-'; break;
			}
			of<<sign;
		}

		of<<endl<<endl;

		for(int y = Ymax; y >= Ymin; y--)
		{
			for(int x = Xmin; x <= Xmax; x++)
			{
				char sign;
				if(matrix[y][x])
				{
					switch(structure->res[matrix[y][x]].mode)
					{
						case HYDROPHOBIC:
							sign  = 'H'; break;
 						case POLAR_NEUTRAL:
							sign  = 'P'; break;
 						case POSITIVE_CHARGE:
							sign  = '+'; break;	
						case NEGATIVE_CHARGE:
							sign  = '-'; break;
					}
					of<<sign;
				}
				else
					of<<" ";
			}
			of<<endl;
		}

	of<<"\n$structure\n";
	for(int y = Ymax; y >= Ymin; y--)
	{
		for(int x = Xmin; x <= Xmax; x++)
		{
			if(matrix[y][x] > 9)
				of<<"("<<matrix[y][x]<<")";
			else if(matrix[y][x] > 0)
				of<<"( "<<matrix[y][x]<<")";
			if(!matrix[y][x])
				of<<"    ";
		}
		of<<endl;
	}
	of<<"$\n";
	
				
	for(int i = 0; i < sizeOfResidueArray*4; i++)
		delete []matrix[i];
	
	delete []matrix;
	 
	return 1;
}


/*
void grabNativeStructuresFromDirectory(int argc, char **argv)
{	
	if(argc < 6)
	{
		cout<<"usage: sizeOfResidueArray configFileName workingDir substr treshold [confIndexFileName] \n";
		exit(0);
	}
	int sizeOfResidueArray = atoi(argv[1]);
	
	configFileHandler cfh(argv[2], sizeOfResidueArray);
	
	cout<<"DB treshold: "<<atoi(argv[5])<<endl;
	cout<<"ConfigFileName: "<<argv[2]<<endl;
	
	char *hp;
	char fileFounded[300], substr[300];
	int index = 0;
	int counter = 0;
	if(argc == 7)
	{
		for(int i = 0; index > -1; i++)
			if( (index = getConfigurationIndexFromFile(argv[6], i)) == -1)
			{
				cout<<" Counted: "<<counter<<"/"<<i<<endl;
				break;
			}
			else
			{
				hp = cfh.getConfiguration(sizeOfResidueArray, index);
				if(hp == 0)
				{
					cout<<" Counted: "<<counter<<"/"<<i<<endl;
					exit(0);
				}
				sprintf(substr, "%s-%d-",argv[4], index);
			
				cout<<"\nfile searched: "<<substr<<endl;
				if(findFileInDir(argv[3], fileFounded, substr) == 0)
					cout<<"-------------Could not find file-------------\n";
				else if(grabNativeStructureFromSimulationsFile(fileFounded, atoi(argv[5]), hp))
						counter++;
			}
	}
	else
	{		
		for(index = 0; index < 1000000; index++)
		{
			hp = cfh.getConfiguration(sizeOfResidueArray, index);
			if(hp == 0)
			{
				cout<<" Counted: "<<counter<<"/"<<index<<endl;
				exit(0);
			}

			sprintf(substr, "%s-%d-",argv[4], index);
			
			cout<<"\nfile searched: "<<substr<<endl;
			if(findFileInDir(argv[3], fileFounded, substr) == 0)
				cout<<"-------------Could not find file-------------\n";
			else if(grabNativeStructureFromSimulationsFile(fileFounded, strtod(argv[5],
				NULL), hp))
					counter++;	
		}
	}				
		
	
	
}
*/
/*
void computeRMSD2NativeStructureForDirectory(int argc, char **argv)
{	
	if(argc < 5)
	{
		cout<<"usage: sizeOfResidueArray configFileName workingDir substr\n";
		exit(0);
	}
	int sizeOfResidueArray = atoi(argv[1]);
	
	configFileHandler cfh(argv[2], sizeOfResidueArray);
	
	//cout<<"ConfigFileName: "<<argv[2]<<endl;
	
	char *hp;
	char fileFounded[512], substr1[512], substr2[512], substr3[512];
	int index = 0;
	int counter = 0;
	char fnameMCS[512];
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
			
	for(index = 0; index < 1000000; index++)
	{
		
		if( (hp = cfh.readTextStructure(sizeOfResidueArray, structure, index)) == 0)
		{
			//cout<<" Counted: "<<counter<<"/"<<index<<endl;
			delete []structure;
			exit(0);
		}
		
		//if(hp == 0)
			//cout<<"hp: NULL"<<endl;
		//else
			//cout<<"hp is not ZERPO\n";
		
		
		sprintf(substr2, "%s_mcs_pairdiff-%d-%d-", argv[4], sizeOfResidueArray, index);
		sprintf(substr1, "%s_structure-%d-%d-", argv[4], sizeOfResidueArray, index);
		sprintf(substr3, "%s%s_mcs_rmsd2Native-%d-%d.data", argv[3], argv[4], sizeOfResidueArray, index);	
		
		cout<<"\nfile searched: "<<substr1<<endl;
// 		if( findFileInDir(argv[3], fnameMCS   , substr2) == 0 ||
// 			findFileInDir(argv[3], fileFounded, substr1) == 0 )	
// 			cout<<"-------------Could not find file-------------\n";
// 		else if(getRMSD2NativeStructureFromFile(fileFounded, fnameMCS, structure,
// 												substr3, hp))
			counter++;


	}
					
	delete []structure;	
}
*/
/*
void computeFractionOfFolded2Native(int argc, char **argv)
{	
	if(argc < 7)
	{
		cout<<"usage: sizeOfResidueArray configFileName workingDir substr tresFrac segmentWidth\n";
		exit(0);
	}
	int sizeOfResidueArray = atoi(argv[1]);
	
	double tresFrac = strtod(argv[5], NULL);
	int segmentWidth = atoi(argv[6]);
	
	configFileHandler cfh(argv[2], sizeOfResidueArray);
	
	//cout<<"ConfigFileName: "<<argv[2]<<endl;
	
	char *hp;
	char fileFounded[512], substr1[512], substr2[512], substr3[512];
	int index = 0;
	int counter = 0;
	char fnameMCS[512];
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	int xCount[1000], yCount[1000];//iterations/segmentWidth
	for(int i = 0; i <= 1000; i++)
		xCount[i] = yCount[i] = 0;
	int maxSegLen = 0, minSegLen = 1000;
		
	for(index = 0; index < 1000000; index++)
	{
		
		if( (hp = cfh.readTextStructure(sizeOfResidueArray, structure, index)) == 0)
		{
			double *X, *Y;
			X = new double[maxSegLen - minSegLen];
			Y = new double[maxSegLen - minSegLen];
			if(!X || !Y)
			{
				cout<<"error mem loc\n";
				exit(1);
			}
			
			for(int i = minSegLen, j = 0; i < maxSegLen; i++, j++)
			{
				if(xCount[i] > 0)
				{
					X[j] = i*segmentWidth; 
					Y[j] = ((double)yCount[i]/(double)xCount[i]);
					cout<<xCount[i]<<" "<<X[j]<<" "<<Y[j]<<endl;
				}
			}
			//cout<<" Counted: "<<counter<<"/"<<index<<endl;
			cout<<"Correlation: "<<getPearsonCorrelation(maxSegLen - minSegLen, X, Y)<<endl;
			
			delete []structure;
			delete []X;
			delete []Y;
			exit(0);
		}
		
		//if(hp == 0)
		//	cout<<"hp: NULL"<<endl;
		//else
		//	cout<<"hp is not ZERPO\n";
		
		sprintf(substr2, "%s_mcs_pairdiff-%d-%d-", argv[4], sizeOfResidueArray, index);
		sprintf(substr1, "%s_structure-%d-%d-", argv[4], sizeOfResidueArray, index);
		sprintf(substr3, "%s%s_mcs_rmsd2Native-%d-%d.data", argv[3], argv[4], sizeOfResidueArray, index);	
		
		double frac = 0;
		
		//cout<<"\nfile searched: "<<substr1<<endl;
		if( findFileInDir(argv[3], fnameMCS   , substr2) == 0 ||
			findFileInDir(argv[3], fileFounded, substr1) == 0 )	
			cout<<"-------------Could not find file-------------\n";
		else 
		{
			frac = getFractionOfFolded2Native(fileFounded, fnameMCS, structure,
												substr3, hp);
			double li = getLocalityIndex(sizeOfResidueArray, structure, hp);
			
			int mod = 0;
			while( ((int)li)%(mod + 1) < (int)li) mod += segmentWidth;
			
			xCount[mod/segmentWidth]++;
			
			if(frac >= tresFrac)
				yCount[mod/segmentWidth]++;	
			
			if(maxSegLen <= mod/segmentWidth)
				maxSegLen = mod/segmentWidth;
			if(minSegLen >= mod/segmentWidth)
				minSegLen = mod/segmentWidth;


			//cout<<li<<" "<<frac<<endl;
			counter++;
		}


	}
	//print: {locality index group} {fraction folded}
	for(int i = minSegLen; i < maxSegLen; i++)
		cout<<i*segmentWidth<<" "<<(double)yCount[i]/(double)xCount[i]<<" "<<xCount[i]<<endl;
				
	delete []structure;	
}
*/
/*
void computeAverageRMSD2NativeStructure(int argc, char **argv)
{	
	if(argc < 9)
	{
		cout<<"usage: sizeOfResidueArray configFileName workingDir substr tresFrac segmentWidth\n"
			  "workingDir2 substr2\n";
		exit(0);
	}
	int sizeOfResidueArray = atoi(argv[1]);
	
	double tresFrac = strtod(argv[5], NULL);
	int segmentWidth = atoi(argv[6]);
	
	configFileHandler cfh(argv[2], sizeOfResidueArray);
	
	//cout<<"ConfigFileName: "<<argv[2]<<endl;
	
	char *hp;
	char fileFounded1[512], fileFounded2[512], substr1[512], substr2[512];
	int index = 0;
	int counter = 0;
	int maxSegLen = 0, minSegLen = 1000;
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	double xCount[1000], yCount[1000];//iterations/segmentWidth
	for(int i = 0; i <= 1000; i++)
		xCount[i] = yCount[i] = 0;

		
	for(index = 0; index < 1000; index++)
	{
		
		if( (hp = cfh.readTextStructure(sizeOfResidueArray, structure, index)) == 0)
		{	
			
			double *X, *Y;
			X = new double[maxSegLen - minSegLen];
			Y = new double[maxSegLen - minSegLen];
			if(!X || !Y)
			{
				cout<<"error mem loc\n";
				exit(1);
			}
			
			int j = 0;
			for(int i = minSegLen; i < maxSegLen; i++)
			{
				if(xCount[i] > 0)
				{
					X[j] = i*segmentWidth; 
					Y[j] = ((double)yCount[i]/(double)xCount[i]);
					cout<<X[j]<<" "<<Y[j]<<endl;
//					if(Y[j] <= 0.05)
//						cout<<i<<" "<<X[j]<<" "<<Y[j]<<endl;
					j++;
				}
					
				
			}
		
			//cout<<" Counted: "<<counter<<"/"<<index<<endl;
			cout<<"Correlation: "<<getPearsonCorrelation(j, X, Y)<<endl;
			
			delete []structure;
			exit(0);
		}
		sprintf(substr2, "%s_structure-%d-%d-", argv[8], sizeOfResidueArray, index);
		sprintf(substr1, "%s_structure-%d-%d-", argv[4], sizeOfResidueArray, index);
				
		if( findFileInDir(argv[7], fileFounded2,substr2) == 0 ||
			findFileInDir(argv[3], fileFounded1, substr1) == 0 )	
			cout<<"-------------Could not find file-------------\n";
		else 
		{
			//frac = getFractionOfFolded2Native(fileFounded, fnameMCS, structure,
			//									substr3, hp);
			double avgRMSDd = getAverageRMSD2NativeStructureFromFile(fileFounded1, structure, hp);//not confined
			double li = getLocalityIndex(sizeOfResidueArray, structure, hp);
			
			int mod = 0;
			while( ((int)li)%(mod + 1) < (int)li) mod += segmentWidth;
			xCount[mod/segmentWidth] += avgRMSDd;
			avgRMSDd -= getAverageRMSD2NativeStructureFromFile(fileFounded2, structure, hp);

			//xCount[mod/segmentWidth]++;
			
			yCount[mod/segmentWidth] += avgRMSDd;	
			
			if(maxSegLen <= mod/segmentWidth)
				maxSegLen = mod/segmentWidth;
			if(minSegLen >= mod/segmentWidth)
				minSegLen = mod/segmentWidth;

			//xCount[index] = li;
			//yCount[index] = avgRMSDd;
			//cout<<xCount[index]<<" "<<yCount[index]<<endl;
			counter++;
		}


	}
				
	delete []structure;	
}
*/

/*
void computeAverageMCS2NativeStructure(int argc, char **argv)
{	
	if(argc < 9)
	{
		cout<<"usage: sizeOfResidueArray configFileName workingDir substr tresFrac segmentWidth\n"
			  "workingDir2 substr2\n";
		exit(0);
	}
	int sizeOfResidueArray = atoi(argv[1]);
	
	double tresFrac = strtod(argv[5], NULL);
	int segmentWidth = atoi(argv[6]);
	
	configFileHandler cfh(argv[2], sizeOfResidueArray);
	
	//cout<<"ConfigFileName: "<<argv[2]<<endl;
	
	char *hp;
	char fileFounded1[512], fileFounded2[512], substr1[512], substr2[512], substr3[512], substr4[512], fnameMCS1[512], fnameMCS2[512];
	int index = 0;
	int counter = 0;
	int maxSegLen = 0, minSegLen = 1000;
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	double xCount[1000], yCount[1000];//iterations/segmentWidth
	for(int i = 0; i <= 1000; i++)
		xCount[i] = yCount[i] = 0;

		
	for(index = 0; index < 1000; index++)
	{
		
		if( (hp = cfh.readTextStructure(sizeOfResidueArray, structure, index)) == 0)
		{	
			
			double *X, *Y;
			X = new double[maxSegLen - minSegLen];
			Y = new double[maxSegLen - minSegLen];
			if(!X || !Y)
			{
				cout<<"error mem loc\n";
				exit(1);
			}
			
			int j = 0;
			for(int i = minSegLen; i < maxSegLen; i++)
			{
				if(xCount[i] > 0)
				{
					X[j] = i*segmentWidth; 
					Y[j] = ((double)yCount[i]/(double)xCount[i]);
					cout<<X[j]<<" "<<Y[j]<<endl;
//					if(Y[j] <= 0.05)
//						cout<<i<<" "<<X[j]<<" "<<Y[j]<<endl;
					j++;
				}
					
				
			}
		
			//cout<<" Counted: "<<counter<<"/"<<index<<endl;
			cout<<"Correlation: "<<getPearsonCorrelation(j, X, Y)<<endl;
			
			delete []structure;
			exit(0);
		}
		sprintf(substr4, "%s_mcs_pairdiff-%d-%d-", argv[8], sizeOfResidueArray, index);
		sprintf(substr3, "%s_mcs_pairdiff-%d-%d-", argv[4], sizeOfResidueArray, index);
		sprintf(substr2, "%s_structure-%d-%d-", argv[8], sizeOfResidueArray, index);
		sprintf(substr1, "%s_structure-%d-%d-", argv[4], sizeOfResidueArray, index);
		
				
		if( findFileInDir(argv[7], fileFounded2,substr2) == 0 ||
			findFileInDir(argv[3], fileFounded1, substr1) == 0 ||
			findFileInDir(argv[7], fnameMCS2, substr4) == 0	||
			findFileInDir(argv[3], fnameMCS1, substr3) == 0		)	
			cout<<"-------------Could not find file-------------\n";
		else 
		{
			//frac = getFractionOfFolded2Native(fileFounded, fnameMCS, structure,
			//									substr3, hp);
			double avgMCSd = getAverageMCS2NativeStructureFromFile(fileFounded1, fnameMCS1, structure, hp);//(fileFounded1, structure, hp);//not confined
			double tmp = avgMCSd;
			avgMCSd -= getAverageMCS2NativeStructureFromFile(fileFounded2, fnameMCS2, structure, hp);//(fileFounded2, structure, hp);
			double li = getLocalityIndex(sizeOfResidueArray, structure, hp);
			
			int mod = 0;
			while( ((int)li)%(mod + 1) < (int)li) mod += segmentWidth;
			xCount[mod/segmentWidth] += tmp;


			//xCount[mod/segmentWidth]++;
			
			yCount[mod/segmentWidth] += avgMCSd;	
			
			if(maxSegLen <= mod/segmentWidth)
				maxSegLen = mod/segmentWidth;
			if(minSegLen >= mod/segmentWidth)
				minSegLen = mod/segmentWidth;

			//xCount[index] = li;
			//yCount[index] = avgRMSDd;
			//cout<<xCount[index]<<" "<<yCount[index]<<endl;
			counter++;
		}


	}
				
	delete []structure;	
}
*/
int getIntegerFromFile(char *sname, int idx)
{
	FILE* fp = fopen(sname, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found\n";
		exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize < 1)
	{
		fclose(fp);
		return -1;
	}
	fseek(fp, 0, SEEK_SET);
	
	char buffer[1024];		
	
	int i = 0, n = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( isdigit(intch) )
			buffer[i++] = ch;
		else 
		{
			if(n == idx)
			{
				fclose(fp);
				buffer[i] = NULL;
				cout<<"getIntegerFromFile: "<<atoi(buffer)<<endl;
				return atoi(buffer);
			}
			if(n < idx)
			{
				n++;
				i = 0;
			}
			
		}
	}		
	
	fclose(fp);				
	return -1;
		
}

bool recursiveIsExternalEdge(point p, int **matrix, int size)
{
	if(p.x == 0 || p.x == size*2 || p.y == 0 || p.y == size*2 ) {
// 		cout<<"Final did it! "<<p.x<<", "<<p.y<<endl;
		return true;
	}
	if(matrix[p.y + 1 + 1][p.x + 1] == 0)
	{
		matrix[p.y + 1 + 1][p.x + 1] = -1;
// 		cout<<"y+ "<<p.y<<endl;
		p.y++;
		if(recursiveIsExternalEdge(p, matrix, size))
			return true;
		p.y--;
	}
	
	if(matrix[p.y + 1 - 1][p.x + 1] == 0)
	{
		matrix[p.y + 1 - 1][p.x + 1] = -1;
// 		cout<<"y- "<<p.y<<endl;
		p.y--;
		if(recursiveIsExternalEdge(p, matrix, size))
			return true;
		p.y++;
	}

	if(matrix[p.y + 1][p.x + 1 + 1] == 0)
	{
		matrix[p.y + 1][p.x + 1 + 1] = -1;
// 		cout<<"x+ "<<p.x<<endl;
		p.x++;
		if(recursiveIsExternalEdge(p, matrix, size))
			return true;
		p.x--;
	}

	if(matrix[p.y + 1][p.x + 1 - 1] == 0)
	{
		matrix[p.y + 1][p.x + 1 - 1] = -1;
// 		cout<<"x- "<<p.x<<endl;
		p.x--;
		if(recursiveIsExternalEdge(p, matrix, size))
			return true;
		p.x++;
	}
// 	cout<<"Return false"<<endl;
	return false;	
	
}

int countExternalEdges4AllresiduesPro(point *structure, int originalSize, double *edgeCnt)
{
	int sumEdges = 0;
		
	int **matrix = new int*[originalSize*2 + 2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < originalSize*2 + 2; i++)
	{
		if( !(matrix[i] = new int[originalSize*2 + 2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < originalSize*2 + 2; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 1; i <= originalSize; i++)
		matrix[structure[i].y][structure[i].x] = i;

	for(int i = 1; i <= originalSize; i++)
	{
		
		if(recursiveIsExternalEdge(structure[i], matrix, originalSize))
		{
				edgeCnt[i]++;
				sumEdges++;
				
				if(i == originalSize || i == originalSize - 1 || i == 1 || i == 2)
					cout<<i<<" 1 ";	
		}
		else
			if(i == originalSize || i == originalSize - 1 || i == 1 || i == 2)
				cout<<i<<" 0 ";	
	
		
		for(int m = 0; m < originalSize*2 + 2; m++)
			for(int n = 0; n < originalSize*2 + 2; n++)
				matrix[m][n] = 0;
		for(int m = 1; m <= originalSize; m++)
			matrix[structure[m].y][structure[m].x] = m;

	
	}
	
	
	for(int i = 0; i < originalSize*2 + 2 ; i++)
		delete []matrix[i];
	delete []matrix;

	return sumEdges;
}

int countExternalEdges4Allresidues(point *structure, int originalSize, double *edgeCnt)
{
	int sumEdges = 0;
		
	int **matrix = new int*[originalSize*2 + 2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < originalSize*2 + 2; i++)
	{
		if( !(matrix[i] = new int[originalSize*2 + 2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < originalSize*2 + 2; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 1; i <= originalSize; i++)
		matrix[structure[i].y + 1][structure[i].x + 1] = i;

	for(int i = 1; i <= originalSize; i++)
	{
		
		if( (matrix[structure[i].y - 1 + 1][structure[i].x + 1] == 0) ||//up
			(matrix[structure[i].y + 1 + 1][structure[i].x + 1] == 0) ||//down
			(matrix[structure[i].y + 1][structure[i].x - 1 + 1] == 0) ||//left
			(matrix[structure[i].y + 1][structure[i].x + 1 + 1] == 0))//right
		{
				edgeCnt[i]++;
				sumEdges++;
		}
	
	}
	
	
	for(int i = 0; i < originalSize*2 + 2 ; i++)
		delete []matrix[i];
	delete []matrix;

	return sumEdges;
}

void countAllTextStructureEdges(char *fname, char *indexfName, int sizeOfResidueArray)
{
	point structure[256];
	//cout<<"begin"<<endl<<fname<<endl;
	configFileHandler cfh(fname, sizeOfResidueArray);
	//cout<<"begin"<<endl<<indexfName<<endl;
	FILE *fi = fopen(indexfName, "r");
	if(!fi)
	{
		cout<<"Cannot open file "<<indexfName<<endl;
		exit(0);
	}
	char buffer[1024*8];
	int nread = 0;
		

	double total = 0, edgeCnt[512] = {0.0};
	int cntr = 0;
	do
	{
		nread = fread(buffer, 1, 1024*8, fi);
		//cout<<buffer;
		char *index = strtok(buffer, "\n");
		while(index)
		{
			//cout<<"index: "<<atoi(index)<<endl;
			cfh.readTextStructure(sizeOfResidueArray, structure, atoi(index));
			cout<<atoi(index)<<" ";
			total += (double)countExternalEdges4AllresiduesPro(structure, sizeOfResidueArray, edgeCnt);
			cout<<endl;
			cntr++;
			index = strtok(NULL, "\n");
		}
						
	}while(nread ==1024*8);	
	
	fclose(fi);
	/*
	cout<<"Edges:\n------\n";
	for(int j = 1; j <= sizeOfResidueArray; j++)
		cout<<j<<": "<<edgeCnt[j]<<" "<<edgeCnt[j]/cntr*100.0<<" %\n";
	
	cout<<"total:\n------\n"<<total<<" "<<total/(cntr*sizeOfResidueArray)*100.0<<" %\n";
	*/
}

int countExternalExposure4AllAA(point *structure, int originalSize, double *edgeCnt, int *totalCnt, char *cnfRes)
{
	int sumEdges = 0;
		
	int **matrix = new int*[originalSize*2 + 2];
	
	if(!matrix)
	{
		cout<<"ERROR Alloc mem - configFileHandler\n";
		exit(1);
	}
	
	for(int i = 0; i < originalSize*2 + 2; i++)
	{
		if( !(matrix[i] = new int[originalSize*2 + 2]) )
		{
			cout<<"ERROR Alloc mem - configFileHandler\n";
			exit(1);
		}
		for(int j = 0; j < originalSize*2 + 2; j++)
			matrix[i][j] = 0;
			
	}
	
	for(int i = 1; i <= originalSize; i++)
		matrix[structure[i].y][structure[i].x] = i;

	for(int i = 1; i <= originalSize; i++)
	{
		
		if(recursiveIsExternalEdge(structure[i], matrix, originalSize))
		{
				switch(cnfRes[i - 1])
				{
					case 'H':	edgeCnt[0]++;	
						break;
					case 'P':	edgeCnt[1]++;
						break;
					case '+':	edgeCnt[2]++;
						break;
					case '-':	edgeCnt[3]++;
						break;
				}
				sumEdges++;
		}
		
		switch(cnfRes[i - 1])
		{
			case 'H':	totalCnt[0]++;	
				break;
			case 'P':	totalCnt[1]++;
				break;
			case '+':	totalCnt[2]++;
				break;
			case '-':	totalCnt[3]++;
				break;
		}
	
		for(int m = 0; m < originalSize*2 + 2; m++)
			for(int n = 0; n < originalSize*2 + 2; n++)
				matrix[m][n] = 0;
		for(int m = 1; m <= originalSize; m++)
			matrix[structure[m].y][structure[m].x] = m;

	}	
	
	for(int i = 0; i < originalSize*2 + 2 ; i++)
		delete []matrix[i];
	delete []matrix;

	return sumEdges;
}
void countAllTextStructureExposureByAA(char *fname, char *indexfName, int sizeOfResidueArray)
{
	point structure[256];
	cout<<"begin"<<endl<<fname<<endl;
	configFileHandler cfh(fname, sizeOfResidueArray);
	cout<<"begin"<<endl<<indexfName<<endl;
	FILE *fi = fopen(indexfName, "r");
	if(!fi)
	{
		cout<<"Cannot open file "<<indexfName<<endl;
		exit(0);
	}
	char buffer[1024*8];
	int nread = 0;
		

	double total = 0, edgeCnt[4] = {0.0};
	int cntr = 0, totalCnt[4] = {0};
	char *cnfRes = NULL;
	do
	{
		nread = fread(buffer, 1, 1024*8, fi);
		//cout<<buffer;
		char *index = strtok(buffer, "\n");
		while(index)
		{
			//cout<<"index: "<<atoi(index)<<endl;
			cnfRes = cfh.readTextStructure(sizeOfResidueArray, structure, atoi(index));
			if(cnfRes)
			{
				//cout<<atoi(index)<<" ";
				total += (double)countExternalExposure4AllAA(structure, sizeOfResidueArray, edgeCnt, totalCnt, cnfRes);
				//cout<<endl;
				cntr++;
			}
				index = strtok(NULL, "\n");
		}
						
	}while(nread ==1024*8);	
	
	fclose(fi);

	cout<<"Exposure by Amino Acid. (out of "<<cntr<<" structures: \n"<<endl;
	cout<<"H: "<<edgeCnt[0]/totalCnt[0]*100.0<<" %"<<endl;
	cout<<"P: "<<edgeCnt[1]/totalCnt[1]*100.0<<" %"<<endl;
	cout<<"+: "<<edgeCnt[2]/totalCnt[2]*100.0<<" %"<<endl;
	cout<<"-: "<<edgeCnt[3]/totalCnt[3]*100.0<<" %"<<endl;

}		
#if 0

int main(int argc, char **argv)
{
#if 0
	if(argc < 4)
	{
		cout<<"char *fname, char *indexfName, sizeOfResidueArray"<<endl;
		exit(0);
	}	
	
	int sizeOfResidueArray = atoi(argv[3]);
	char *fname = argv[1]; 
	char *indexfName = argv[2];
	countAllTextStructureExposureByAA(fname, indexfName, sizeOfResidueArray);
#endif
#if 0	
	countAllTextStructureEdges(fname, indexfName, sizeOfResidueArray);
#endif
#if 0
	printStructureFromFile(argc, argv);
#endif
	
#if 1
	createDimer(argc, argv);
#endif
#if 0
	configFileHandler cfh(argv[1], 25, 0);	
#endif
	
#if 0
	computeAverageMCS2NativeStructure(argc, argv);
#endif
	
#if 0
	computeAverageRMSD2NativeStructure(argc, argv);
#endif
	
#if 0
	computeFractionOfFolded2Native(argc, argv);
#endif

		
#if 0
	computeRMSD2NativeStructureForDirectory(argc, argv);
#endif
	
#if 0 //test for cfh
	cout<<"Begin testing\n";
	
	int sizeOfResidueArray = atoi(argv[2]);
	configFileHandler cfh(argv[1], sizeOfResidueArray, 0);
	
	point *structure = new point[sizeOfResidueArray + 1];
	char *confRes = 0;
	int index = 0;
	//cfh.readTextStructure(sizeOfResidueArray, structure, confRes, index);
	//cfh.writeStructure2output(sizeOfResidueArray, structure, confRes);
	
	while(cfh.readTextStructure(sizeOfResidueArray, structure, confRes, index) != 0)
	{
		cfh.writeStructure2output(sizeOfResidueArray, structure, confRes);
		index++;
	}
	
#endif	

#if 0
	grabNativeStructuresFromDirectory(argc, argv);	
#endif	
#if 0
	if(argc < 7 )
	{
		cout<<"FileName sizeOfResidueArray sideStructDBsize ";
		cout<<"WorkingDirectory substring pdtres [segmentWidth]\n";
		exit(0);
	}
	
	int sizeOfResidueArray = atoi(argv[2]);
	int sideStructDBsize = atoi(argv[3]);
	configFileHandler cfh(argv[1], sizeOfResidueArray, 0);
	
	double pdtres = atof(argv[6]);
	int segmentWidth = 0;
	if(argc == 8)
		segmentWidth = atoi(argv[7]);
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"Error alloc\n";
		exit(1);
	}
		

	int confIdx = 0;
	int structIdx;
	char *hp;
	/*
	Pearson Product Moment Correlation:

	r =                 (N*sumof(X*Y) - sumof(X)*sumof(Y))
	    ___________________________________________________________________
		sqrt( (N*sumof(X^2) - (sumof(X))^2)*(N*sumof(Y^2) - (sumof(Y))^2) )
		
     where N is the number of pairs of scores.
	*/
	double N;
	double sumofXY = 0, sumofX = 0, sumofY = 0, sumofSqX = 0, sumofSqY = 0;
	double X, Y;

//	cout<<"Locality index of DB file: "<<argv[1]<<endl;
	for(; confIdx < 10000; confIdx++)
	{
		structIdx = cfh.getStructureDBIndex(sizeOfResidueArray, confIdx);
		hp = cfh.getConfiguration(sizeOfResidueArray, confIdx);
		
		if(structIdx ==  -1)
			break;

		getStructFromDB(structIdx, structure, sizeOfResidueArray, sideStructDBsize);
		X = getLocalityIndex(sizeOfResidueArray, structure, hp);
//		X = getStrongInteractionLocalityIndex(sizeOfResidueArray, structure, hp, segmentWidth);	
		
		statistics s;
		double statisticX[2], statisticY[2];
	
		if(s.compute4file(confIdx, argv[4], argv[5], statisticX, statisticY) ==  0)
			break;
		else
		{
			Y = statisticX[0]; // *statisticX[0];
			
			if(/*Y*/statisticY[0] < pdtres)
			{
				cout<<X<<" "<<Y<<endl;
				
				sumofXY += X*Y;
				sumofX += X;
				sumofY += Y;
				sumofSqX += X*X;
				sumofSqY += Y*Y;
				N++;
			}
		}//end else
	}
	//N++;
	double dX = N*sumofSqX - sumofX*sumofX;
	double dY = N*sumofSqY - sumofY*sumofY;
	
	double r = (N*sumofXY - sumofX*sumofY)/sqrt(dX*dY);
	 
	cout<<"\nAvg: "<<sumofX/N<<" Total of: "<<N<<endl;
	cout<<"Correlation value: "<<r<<endl;
	delete []structure;
#endif

#if 0//only prints the locality index data
	if(argc < 4 )
	{
		cout<<"FileName sizeOfResidueArray sideStructDBsize\n";
		exit(0);
	}
	
	int sizeOfResidueArray = atoi(argv[2]);
	int sideStructDBsize = atoi(argv[3]);
	configFileHandler cfh(argv[1], sizeOfResidueArray, 0);
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"Error alloc\n";
		exit(1);
	}
		

	int confIdx = 0;
	int structIdx;
	char *hp;
	double sum = 0;
	cout<<"Locality index of DB file: "<<argv[1]<<endl;
	for(; confIdx < 10000; confIdx++)
	{
		structIdx = cfh.getStructureDBIndex(sizeOfResidueArray, confIdx);
		hp = cfh.getConfiguration(sizeOfResidueArray, confIdx);
		
		if(structIdx ==  -1)
		{
			//cout<<"End of structures\n";
			break;
		}

		getStructFromDB(structIdx, structure, sizeOfResidueArray, sideStructDBsize);
		double tmp = getLocalityIndex(sizeOfResidueArray, structure, hp);
		sum += tmp;
		cout<<confIdx<<", "<<structIdx<<": "<<tmp<<endl;
	}
	cout<<"\nAvg: "<<sum/(double)confIdx<<" Total of: "<<confIdx + 1<<endl;
	delete []structure;
#endif
	return 0;
}	
	
#endif	

	
int createDimer(int argc, char**argv)
{
	if(argc < 7)
	{
		cout<<"1.FileName_S1 2.sizeOfResidueArray 3.index_S1 4.index_S2 5.linkerLength 6. fileName_S2\n";
		exit(0);
	} 
	int sizeOfResidueArray = atoi(argv[2]);
	configFileHandler cfh(argv[1], sizeOfResidueArray, 0);
			
	int index1 = atoi(argv[3]);
	int index2 = atoi(argv[4]);
	int linkerLength = atoi(argv[5]);
	//cout<<"index1: "<<index1<" index2: "<<index2<<endl;
	cfh.generateDimerTextStructureFromTwoFiles(index1, index2, sizeOfResidueArray, linkerLength,
			argv[6]);
	
	return 1;
}


int printStructureFromFile(int argc, char **argv)
{
	if(argc < 6)
	{
		cout<<"structure_file_name config_file_name sizeOfResidueArray index\n \
				index1, index2, index3, ...\n";
		return 0;
	}
	int sizeOfResidueArray = atoi(argv[3]);
	configFileHandler cfh(argv[2], sizeOfResidueArray, atoi(argv[4]));
	point structure[1024];
	
	for(int i = 5; atoi(argv[i]) > -1; i++)
	{
		cfh.readBinStructure(argv[1], structure, atoi(argv[i]));
		cfh.writeStructure2output(sizeOfResidueArray, structure, cfh.getHPconfiguration());
	}
	return 0;	
}


