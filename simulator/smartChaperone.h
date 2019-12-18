//smartChaperone.h

#ifndef SMARTCHAPERONE_H
#define SMARTCHAPERONE_H

#include "chaperon.h"
#include "protchap.h"

class smartChaperone: public chaperon
{
public:
	
	int **sides;//sides[n][0] = begining index of residue belong to side n, sides[n][1] = end
	int numberOfSides;//from zero
	int *onSide;//length of chaperone, holds the index number of the ascribed side for each residue
	
	int **sideModes;//numberOfSides + 1 //zero for the hydrophobic begining
	//turingMachine *sideTM; may not be nessesary
	char *sideDynamics;
	
	smartChaperone(int findex, char *name = 0);
	~smartChaperone();
	
	//infrastructure functions:
	//-------------------------
	int buildSmartSides(int sideToStart);
						 //builds the smart sides according to the protein location in chaperone
						 //the sideModes structure will hold the relevant modes.
	
	int getInteractionSide(foldingComplex *pcc);//returns the index [0, numberOfsides) side of chaperone which the
						                               //protein is connected to.
	virtual int updateMode(int modeNumber);

	
	//chaperone API:
	//--------------
	//virtual int step();//called each MCS step
	virtual int init(foldingComplex *pcc = 0);//is used each time protein is caged in the chaperone
	
};
#endif //SMARTCHAPERONE_H
