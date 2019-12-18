//turingMachine.h

#ifndef TURING_MACHINE_H
#define TURING_MACHINE_H

#include "tree.h"

#define MAX_NUMBER_OF_REPEATS	20
#define GO_FORWARD	for(; comstr[pos] != '{' && comstr[pos] != '}' && comstr[pos] != 0; pos++)

typedef struct repeater
{
	int repeatCtr;
	int currentRepeatCtr;
	int beginRepeatIdx;
	int endRepeatIdx;
	
	repeater():
	repeatCtr(0),
	currentRepeatCtr(0),
	beginRepeatIdx(0),
	endRepeatIdx(0)
	{}
	
	
	
} REPEATER;
 

class turingMachine
{
public:
	
	char *comstr;
	int currPos;
	int comstrLength;
	int mcsWindowSize;
	
	turingMachine(char *str, int mcsWinSize);
	~turingMachine(){ delete []comstr; }
	
	bool stoped;
	long long MCSctr;
	int winCtr;

	tree<REPEATER> repeats;
	REPEATER *currentRepeat;
	
	int repeatStrIdx;
	int maxRepeats;
	int iRepeat;

	int currentMode;
	int currentState;
	bool newStateFlag;
	
	//if no change then return 0
	//if changed then return new mode number
	//need to check if the state has changed
	int step();
	
	int buildRepeats(int pos, node<REPEATER> &n);
	int createRepeats(int &pos, node<REPEATER> &n);
	int closeChild(int &pos, node<REPEATER> &n);
	int openChild(int &pos, node<REPEATER> &n);
	
	//if new state return the new state char value
	//if not new return 0;
	//if finished return -1;
	int isNewState();
	int init();
	int loadNewRepeats(char *str);
			
};


#endif
