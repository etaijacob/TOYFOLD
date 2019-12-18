//chaperon.h
#ifndef CHAPERON_H
#define CHAPERON_H

#include "residue.h"
#include "configFileHandler.h"
#include "turingMachine.h"
#include "protchap.h"

#define MAX_SIZE_OF_TMP_STRUCTURE	128
#define MCS_WINDOW_SIZE				1000

enum chaperonState 
{
ALONE = 1,
WELCOM,
HOSTING,
GOODBYE,
MAXSTATES
};

class chaperon: public residueArray
{
public:

	static const int mcsWindowSize;	
	static int singleton;
	static configFileHandler cfh;

	turingMachine *TM;
	
	//chaperon data:
	//--------------
	int **modes;
	int numberOfModes;
	char *dynamics;
	
	
	char *logoStr;
	int logoSize;
	
	long long iterationsCounter;
	
	chaperon(int findex, char *name = 0);
	chaperon(){};
	virtual ~chaperon();
	
	int logo2structure(char *str = 0);
	int structure2logo(point *structure = 0);
	virtual int updateMode(int modeNumber);
	//chaperon dynamics API:
	//----------------------
	virtual int step();
	virtual int init(foldingComplex *pcc = 0);
	
	chaperonState currentState;
	//int MCStoGo;
	
	point getMin_dx_dy();
			
		
/*
State machine:
--------------


----------------------------------------
\                                      \
-->ALONE --> WELCOM --> HOSTING --> GOODBYE
     ^           \        ^   \
	 \           \        \   \
	 -------------		  -----
	 

Chaperon dynamics description language:
---------------------------------------
{...} - The block to repeat. followed by an integer of times to repeat.
i.e. {T12S14T3S5}22


M - Mode
Then let M1 be configuration mode of array {H, P, +, -}of kind 1, 
		 M2 be conf. mode of array of kind 2, M3...., ....

A - represents Alone state.
W - represents Welcom state.
H - represents Hosting state.
G - represents Goodbye state.

T - will be followed by the duration (number of mcsWindowSize) of the following mode:
	i.e. T12M1 - 12*mcsWindowSize mcs occurences of mode  M1
	
General i.e.

AT12M1T4M3WT4M5HT300M4GT2M8

Alone state begins with 12 mcsWindowSize of Mode M1 then passes to M3 for additional
4 mcsWindowSize, then passes to state Welcom....

	

Energy:
-------
Hosting has a finite energy consumption that is consumed for the benefit
of dynamic wall mode changes and time of being in HOSTING state.
Rules:
1. The transition from one state to the other consumes Energy.
2. Occuping the HOSTING state consumes Energy.


Structure:
----------
Structure is discribed by  the LOGO alphbet: {F, f, +, -}

Modes:
------
Defined by the {H, P, +, -} model and time slots of size T units of MCS.
		
				
*/

				
};

#endif
