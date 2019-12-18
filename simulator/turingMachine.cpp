//turingMachine.cpp

#include "turingMachine.h"
#include <iostream>
#include <stdlib.h>
#include <ctype.h>

turingMachine::turingMachine(char *str, int mcsWinSize):
MCSctr(0),
winCtr(0),
mcsWindowSize(mcsWinSize),
stoped(false),
repeats(*(new REPEATER)),
repeatStrIdx(-1),
maxRepeats(0),
iRepeat(-1),
currentMode(0),
currentState(0),
newStateFlag(false)
{
	
	comstr = new char[strlen(str) + 1];
	if(!comstr)
	{
		cout<<"ERROR - mem aloc turingMachine\n";
		exit(1);
	}
	
	strcpy(comstr, str);
	
	comstrLength = strlen(comstr);
	currPos = 0;
	
	
	int pos = 0;
	createRepeats(pos, *repeats.root);
	
	
	cout<<"TM was created.\n";
}

int turingMachine::loadNewRepeats(char *str)
{
	repeats.deleteTree();
	delete []comstr;
	comstr = new char[strlen(str) + 1];
	if(!comstr)
	{
		cout<<"ERROR - mem aloc turingMachine\n";
		exit(1);
	}
	
	strcpy(comstr, str);
	
	comstrLength = strlen(comstr);
	currPos = 0;
	
	int pos = 0;
	createRepeats(pos, *repeats.root);
	init();
	repeats.init();
	
	return 1;
}

	
int turingMachine::isNewState()
{
	if(newStateFlag)
		return currentState;
	else
		return 0;
}

int turingMachine::openChild(int &pos, node<REPEATER> &n)
{
	//cout<<"{ Open child on: "<<pos<<endl;
	
	int currentChild;
	n.createChild(*(new REPEATER));
	currentChild = n.numberOfChildren - 1;
	
	pos++;
	for(; comstr[pos] == ' '; pos++);
	char tmp[100];
	int i;
						
	for(i = 0; isdigit(comstr[pos]); i++, pos++)
		tmp[i] = comstr[pos];
						
	tmp[i] = 0;
	n.children[currentChild]->key->repeatCtr = atoi(tmp) - 1;
	n.children[currentChild]->key->currentRepeatCtr = n.children[currentChild]->key->repeatCtr;
	for(; comstr[pos] == ' '; pos++);
	n.children[currentChild]->key->beginRepeatIdx = pos;
	
	return currentChild;
}

int turingMachine::closeChild(int &pos, node<REPEATER> &n)		
{
	//cout<<"} Close child on: "<<pos<<endl;
	n.children[n.numberOfChildren - 1]->key->endRepeatIdx = pos - 1;
	pos++;
	return n.numberOfChildren - 1;
}
		
int turingMachine::createRepeats(int &pos, node<REPEATER> &n)
{
	GO_FORWARD;	
	
	while(comstr[pos] == '{')
	{
		//cout<<"Level: "<<n.level<<endl;
		openChild(pos, n);
		//cout<<"Sub: "<<n.numberOfChildren - 1<<endl;
		createRepeats(pos, *n.children[n.numberOfChildren - 1]);
		GO_FORWARD;

		if(comstr[pos] == '}')
			closeChild(pos, n);
		GO_FORWARD;
	}
	
	if(comstr[pos] == 0)
		return 1;
	return 1;							
	
}
	


#if 0			
int turingMachine::buildRepeats(int pos, int index)
{
	cout<<"buildRepeats: "<<pos<<" "<<index<<"\n";
	for(; comstr[pos] != '{' && comstr[pos] != '}' && comstr[pos] != 0; pos++);
	if(comstr[pos] == '{')
	{
		pos++;
		for(; comstr[pos] == ' '; pos++);
		char tmp[100];
		int i;
						
		for(i = 0; isdigit(comstr[pos]); i++, pos++)
			tmp[i] = comstr[pos];
						
		tmp[i] = 0;
		repeatCtr[index] = atoi(tmp) - 1;
		cout<<"{ "<<"Rept: "<<repeatCtr[index]<<endl;
		for(; comstr[pos] == ' '; pos++);
		beginRepeatIdx[index] = pos;
		cout<<"beginRepeatIdx[index]: "<<beginRepeatIdx[index]<<endl;
		
		for(; comstr[pos] != '{' && comstr[pos] != '}' && comstr[pos] != 0; pos++);
	}
		
	
	switch(comstr[pos])
	{
		case 0  : return pos;
		
		case '{': pos = buildRepeats(pos, index + 1);
				  for(; comstr[pos] != '}' && comstr[pos] != 0; pos++);
				  if(comstr[pos] == 0)
				  {
					  cout<<"ERROR - syntax {} is wrong\n";
					  exit(0);
				  }
		
		case '}': endRepeatIdx[index] = pos - 1; 
				  cout<<"endRepeatIdx[index]: "<<endRepeatIdx[index]<<endl;
				  pos++;
				  if(index >= maxRepeats)
				  {
					  maxRepeats = index + 1;
					  cout<<"maxRepeats: "<<maxRepeats<<endl;
				  }
				 
				  return pos;
		
		default : cout<<"ERROR - no such alphabet\n";
				  exit(0);
	} 
	
	cout<<"Shouldn't get here\n";
	return pos;
}	
#endif

int turingMachine::init()
{
	MCSctr = 0;
	winCtr = 0;
	stoped = false;
	newStateFlag = false;
	currPos = 0;
	
	repeatStrIdx = -1;
	maxRepeats = 0;
	iRepeat = -1;
	currentMode = 0;
	currentState = 0;

	repeats.init();
	
	return 1;
}
	
		
int turingMachine::step()
{	
	//cout<<MCSctr<<": \n"; 
	if(stoped)
		return -1;
	MCSctr++;
	//cout<<"winCtr: "<<winCtr<<endl;
	if(winCtr > 0)
	{
		if( (MCSctr)%mcsWindowSize == 0)
			winCtr--;
		newStateFlag = false;
		return 0;
	}
	
	bool cont = true;
	
	for(; comstr[currPos] == ' '; currPos++);
	
	while(cont){
	switch(comstr[currPos])
	{
		case 'A':
		case 'W':
		case 'H':
		case 'G': //cout<<"MODE\n"<<"currPos: "<<currPos<<endl;
				  currentState != comstr[currPos] ? newStateFlag = true : newStateFlag = false;
				  currentState = comstr[currPos++];
				  //cout<<"MODE\n"<<"currPos: "<<currPos<<comstr<<endl;
				  
				  break;
				  
		case '{': 
				  repeats.forward();
				  currentRepeat = repeats.current->key;
				  currPos = currentRepeat->beginRepeatIdx;
				  break;
				  
				  
		case '}': if(currentRepeat->currentRepeatCtr > 0)
				  {
					  currentRepeat->currentRepeatCtr--;
					  currPos = currentRepeat->beginRepeatIdx;
				  }
				  else
				  {
				  	  currentRepeat->currentRepeatCtr = currentRepeat->repeatCtr;
					  currPos++;
					  repeats.backward();
					  currentRepeat = repeats.current->key;
					  repeats.nextChild();
					  //cout<<"repeats.currentChildIndex: "<<repeats.currentChildIndex<<endl;
				  }
				  break;
		
		case 'T': currPos++;
				  for(; comstr[currPos] == ' '; currPos++);
				  char tmp[100];
				  int i;
						
				  for(i = 0; isdigit(comstr[currPos]); i++, currPos++)
					  tmp[i] = comstr[currPos];
						
				  tmp[i] = 0;
				  winCtr = atoi(tmp);
				  for(; comstr[currPos] != 'M'; currPos++);
				  
				  //cout<<" T: "<<winCtr;
		case 'M': currPos++;{	
				  //char tmp[100];
				  //int i;
						
				  for(i = 0; isdigit(comstr[currPos]); i++, currPos++)
					  tmp[i] = comstr[currPos];
						
				  tmp[i] = 0;
				  int prevMode = currentMode;
				  currentMode = atoi(tmp);
				  //cout<<"M currPos: "<<currPos<<endl;
				  for(; comstr[currPos] == ' '; currPos++);
				  //cout<<"M: "<<currentMode<<" "<<endl;
				  if( (MCSctr)%mcsWindowSize == 0)
				  	  winCtr--;
				  if(prevMode == currentMode)
				  	return 0;
				  else return currentMode;
				  break;
				  }
		case '\n':cont = false;
				  cout<<endl;
				  stoped = true;
				  //cout<<"stoped\n";
				  break;
		case ' ': currPos++;
				  break;
				  
		default : stoped = true;
				  //cout<<"stoped\n";
				  cont = false;	
				 
		}//end switch
	}
	//cout<<"End of dynamic str\n";
	return -1;		

}

#if 0
int turingMachine::step()
{	

	if(stoped)
		return -1;
	MCSctr++;
	//cout<<"winCtr: "<<winCtr<<endl;
	if(winCtr > 0)
	{
		if( (MCSctr + 1)%mcsWindowSize == 0)
			winCtr--;
		newStateFlag = false;
		return 0;
	}
	
	bool cont = true;
	
	for(; comstr[currPos] == ' '; currPos++);
	
	while(cont){
	switch(comstr[currPos])
	{
		case 'A':
		case 'W':
		case 'H':
		case 'G': cout<<"MODE\n"<<"currPos: "<<currPos<<endl;
				  currentState != comstr[currPos] ? newStateFlag = true : newStateFlag = false;
				  currentState = comstr[currPos++];
				  cout<<"MODE\n"<<"currPos: "<<currPos<<comstr<<endl;
				  
				  break;
				  
		case '{': iRepeat++;
				  cout<<"[iRepeat]: "<<iRepeat<<endl;
				  if(repeatStrIdx != currPos)
				  {
				  		repeatStrIdx = currPos = beginRepeatIdx[iRepeat]; 
				  		
						break;
				  }	
				  break;
				  
		case '}': cout<<"repeatCtr: "<<currentRepeatCtr[iRepeat]<<endl;
				  if(currentRepeatCtr[iRepeat] > 0)
				  {
					  currentRepeatCtr[iRepeat]--;
					  currPos = beginRepeatIdx[iRepeat];
					  
					  currentRepeatCtr[iRepeat + 1] = repeatCtr[iRepeat + 1];
				  }
				  else
				  {
					  currPos++;
					  for(; comstr[currPos] == ' '; currPos++);
					  repeatStrIdx = -1;
					  cout<<"close repeat: "<<iRepeat<<endl;
					  iRepeat--;
				  }
				  cout<<"}";	
				  break;
		
		case 'T': currPos++;
				  for(; comstr[currPos] == ' '; currPos++);
				  char tmp[100];
				  int i;
						
				  for(i = 0; isdigit(comstr[currPos]); i++, currPos++)
					  tmp[i] = comstr[currPos];
						
				  tmp[i] = 0;
				  winCtr = atoi(tmp);
				  for(; comstr[currPos] != 'M'; currPos++);
				  cout<<"T: "<<winCtr;
		case 'M': currPos++;	
				  //char tmp[100];
				  //int i;
						
				  for(i = 0; isdigit(comstr[currPos]); i++, currPos++)
					  tmp[i] = comstr[currPos];
						
				  tmp[i] = 0;
				  currentMode = atoi(tmp);
				  cout<<"M currPos: "<<currPos<<endl;
				  for(; comstr[currPos] == ' '; currPos++);
				  cout<<"M: "<<currentMode<<" "<<endl;
				  return currentMode;
				  break;
				  
		case '\n':cont = false;
				  cout<<endl;
				  stoped = true;
				  cout<<"stoped\n";
				  break;
		case ' ': currPos++;
				  break;
				  
		default : stoped = true;
				  cout<<"stoped\n";
				  cont = false;	
				 
		}//end switch
	}
	cout<<"End of dynamic str\n";
	return 0;		

}
#endif



#if 0
int main(int argc, char **argv)
{
	turingMachine tm(argv[1], 2);
	
	
	for(int i = 0; i < atoi(argv[2]); i++)
	{
		int n = tm.step();
		cout<<n<<", ";
	}
	cout<<endl;
	/*
	REPEATER rep;
	tree<REPEATER> repeats(rep);
	
	for(int i = 0; i < atoi(argv[1]); i++)
	{
		repeats.root->createChild(rep);
		for(int j = 0; j < atoi(argv[1]); j++)
			repeats.root->children[i]->createChild(rep);
	}	
	*/
	return 0;
}
#endif
