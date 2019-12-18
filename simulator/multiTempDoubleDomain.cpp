//multiTempDoubleDomain.cpp

#include "multiTempDoubleDomain.h"
#include <math.h>
#include <iostream>
#include <stdlib.h>

using namespace std;

char VERSIONDD1[100] = "Version 22-09-13, V21 multiTempDoubleDomain.cpp";

// TODO: 1. clean print to file to include only dwell time data
//       
//			 
int multiTempDoubleDomain::FoldAndPrintDwellTime
										  (double times, 
										   int numOfSimulations, 
										   char *hp,
										   double rmsdDwell,
										   bool breaking)
{
	
	cout<<"multiTempDoubleDomain folding func FoldAndPrintDwellTime, "<<VERSIONDD1<<endl;
	
	//initFoldingComplex();
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	int linkerLength = fromto[2] - fromto[1] - 1;//e.g. 1 25 31 55: 31-25=6 
	int domain_A_length = fromto[1] - fromto[0] + 1;//e.g. 25-1=24
	int domain_B_length = fromto[3] - fromto[2] + 1;
	
	
	point *currStruct = new point[toFocus - fromFocus + 1];
	if(!currStruct)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	point * domainInFocusStruct;
	if(domainInFocus == 1)
		domainInFocusStruct = domain_A_struct;
	else if(domainInFocus == 2)
		domainInFocusStruct = domain_B_struct;
	else {
		cout<<"ERROR - domain in focus is not A or B. Aborting\n";
		exit(1);
	}
	
	CfileHdlr.writeStructure2output(domain_A_length, domainInFocusStruct, hp);
	RMSD rmsd(domainInFocusStruct, toFocus - fromFocus + 1, 1);
	rmsd.update(domainInFocusStruct);
	
	UPDATE_PROTEIN_MODES(res)
	 		
	cout<<"doubledomain FoldAndPrintDwellTime: Begin folding:"<<endl;
	
	char fostr[1024];
	cout<<times<<", seq: "<<hp<<endl;
	sprintf(fostr, "%s.dwell%.2f-mtdd-itr%d.data", outputDatafileName, rmsdDwell, (int)times);
	cout<<fostr<<endl;
	ofstream of(fostr); 
	cout<<"#SEQ\t"<<hp<<endl<<"max mcs: "<<times<<", maxRangeOfLocalConf: "<<maxRangeOfLocalConf<<", edgesProbability: "<<edgesProbability<<", simulationFactor: A:"<<domain_A_temp<<", B:"<<domain_B_temp<<", perturbationFactor: A:"<<domain_A_perturbation<<", B:"<<domain_B_perturbation<<", Method: "<<VERSIONDD1<<" foldToMinimumEnergy"<<endl<<", collisionsWithConfinment: "<<collisionsWithConfinment<<endl;
	cout<<"#DOUBLEDOMAIN\t"<<fromto[0]<<" "<<fromto[1]<<" "<<fromto[2]<<" "<<fromto[3]<<endl;
	
	of<<"state\t"<<"mcs"<<endl;
	for(int m = 0; m < numOfSimulations; m++)
	{
		cout<<"Doing itr: "<<m<<endl;
		initFoldingComplex();
		int focusSuccessFlag = 0;
		double itr = 0, alpha_itr = 0;
			
		if(confine) {
			int r;
			preConfinement = true;
			for(r = 0; r < times*10; r++)
			{
				foldOnce();
				point pdxdy = getMaxDist();
	// 			cout<<"dxdy: "<<pdxdy<<endl;
				if( (pdxdy.x + 1 <= confineXsize) &&
						(pdxdy.y + 1 <= confineYsize) ) {
					cout<<"Confined! took "<<r<<" times"<<endl<<pdxdy<<endl;
					CfileHdlr.writeStructure2output(sizeOfResidueArray, this);
					preConfinement = false;
					break;
				}
			}
			if(r == times*10) {
				cout<<"ERROR - Could not confine."<<endl;
				continue;
			}
			initParameters();
// 			cout<<"Struct-B Energy: "<<BFA[2]->energy<<", MCS: "<<BFA[2]->stepNumber<<", anyInterDomainInteractions: "<<anyInterDomainInteractions<<", successfulInterDomainInteractions: "<<successfulInterDomainInteractions<<", collisionsWithDomainNotInFocus: "<<collisionsWithDomainNotInFocus<<endl<<endl;
		}
		
		double rmsdAcc = 0;
		bool mySwitch = true;
		int switchCount = 0;
		
	
		for(int i = 0; i < times; i++)
		{
// 			domainInFocusItr = i;
			itr++;
// 			alpha_itr++;
// 			cout<<"---------------------- "<<i<<" ----------------------------"<<endl;
			int SuccessFlag = 0;
			if(foldOnce()) {
// 				cout<<"Success ####!!!"<<endl;
				SuccessFlag = 1;
			}
			// Only counting domainInFocus steps
			if(domainInFocus == 1 || domainInFocus == 2)
				if(!movementIncludesDomainInFocus() || (confine && wasOutOfConfinedRegion)) {
					wasOutOfConfinedRegion = false;
					i--;
// 					cout<<"Going down "<<i<<endl;
				}
				else {
					focusSuccessFlag += SuccessFlag;
					
					getDomainInFocusStruct(currStruct);
					rmsdAcc = rmsd.compute(currStruct);
// 					cout<<rmsdAcc<<endl;
					if(rmsdAcc > rmsdDwell) {
						if(mySwitch == true) {
							switchCount++;
						}
						else {
							of<<mySwitch<<"\t"<<switchCount<<endl;
							mySwitch = true;
							switchCount = 1;
						}
					}
					else { 
						if(mySwitch == false) {
							switchCount++;
						}
						else {
							if(breaking) {
								cout<<"Breaking itr = "<<m<<endl;
								break;
							}
							
							of<<mySwitch<<"\t"<<switchCount<<endl;
							mySwitch = false;
							switchCount = 1;
						}
					}
				}
		}
		of<<mySwitch<<"\t"<<switchCount<<endl;
		
		cout<<"focus ctr: "<<focusSuccessFlag<<" success ctr: "<<successCtr<<" all:"<<itr<<" f="<<successCtr/itr<<endl;
		CfileHdlr.writeStructure2output(sizeOfResidueArray, BFA[0]);
		cout<<"Struct-D Energy: "<<BFA[0]->energy<<", MCS: "<<BFA[0]->stepNumber<<endl<<endl;
		
		int dd, sd;
		for(dd = fromto[0], sd = 1; dd <= fromto[1]; dd++, sd++) 
			structure[sd] = BFA[1]->res[dd].position;
			cout<<"papa goes to hollywood.."<<domain_A_length<<endl;
		CfileHdlr.writeStructure2output(domain_A_length, structure, &hp[fromto[0]]);
		cout<<"Struct-A Energy: "<<BFA[1]->energy<<", MCS: "<<BFA[1]->stepNumber<<", anyInterDomainInteractions: "<<anyInterDomainInteractions<<", successfulInterDomainInteractions: "<<successfulInterDomainInteractions<<", collisionsWithDomainNotInFocus: "<<collisionsWithDomainNotInFocus<<", collisionsWithConfinment: "<<collisionsWithConfinment<<endl;
		char signs[4] = {'H', 'P', '+', '-'};
		cout<<"IntraContacts-A: ";
		for(int q = 0; q < 4; q++)
			for(int u = q; u < 4; u++) {
				int intCnts = intraContacts1[q][u];
				if(q != u)
					intCnts += intraContacts1[u][q];
				cout<<signs[u]<<signs[q]<<": "<<intCnts;
				if(q < 3 || u < 3)
					cout<<", ";
			}
		cout<<endl;
		cout<<"LinkerContacts-A: ";
		for(int q = 0; q < 4; q++)
			for(int u = q; u < 4; u++) {
				int intCnts = linkerContacts1[q][u];
				if(q != u)
					intCnts += linkerContacts1[u][q];
				cout<<signs[u]<<signs[q]<<": "<<intCnts;
				if(q < 3 || u < 3)
					cout<<", ";
			}
		cout<<endl;
		for(dd = fromto[2], sd = 1; dd <= fromto[3]; dd++, sd++) 
			structure[sd] = BFA[2]->res[dd].position;
		CfileHdlr.writeStructure2output(domain_B_length, structure, &hp[fromto[2] - 1]);
		cout<<"Struct-B Energy: "<<BFA[2]->energy<<", MCS: "<<BFA[2]->stepNumber<<", anyInterDomainInteractions: "<<anyInterDomainInteractions<<", successfulInterDomainInteractions: "<<successfulInterDomainInteractions<<", collisionsWithDomainNotInFocus: "<<collisionsWithDomainNotInFocus<<", collisionsWithConfinment: "<<collisionsWithConfinment<<", domainInFocusMCS: "<<domainInFocusMCS<<endl;
		cout<<"IntraContacts-B: ";
		for(int q = 0; q < 4; q++)
			for(int u = q; u < 4; u++) {
				int intCnts = intraContacts2[q][u];
				if(q != u)
					intCnts += intraContacts2[u][q];
				cout<<signs[u]<<signs[q]<<": "<<intCnts;
				if(q < 3 || u < 3)
					cout<<", ";
			}
		cout<<endl;
		cout<<"LinkerContacts-B: ";
		for(int q = 0; q < 4; q++)
			for(int u = q; u < 4; u++) {
				int intCnts = linkerContacts2[q][u];
				if(q != u)
					intCnts += linkerContacts2[u][q];
				cout<<signs[u]<<signs[q]<<": "<<intCnts;
				if(q < 3 || u < 3)
					cout<<", ";
			}
		cout<<endl;
		
		intraContacts1[4][4], intraContacts2[4][4], interContacts[4][4], linkerContacts1[4][4], linkerContacts2[4][4];
		cout<<"InterContacts: ";
		for(int q = 0; q < 4; q++)
			for(int u = q; u < 4; u++) {
				int intCnts = interContacts[q][u];
				if(q != u)
					intCnts += interContacts[u][q];
				cout<<signs[u]<<signs[q]<<": "<<intCnts;
				if(q < 3 || u < 3)
					cout<<", ";
			}
		cout<<endl;
	}
	
	of.close();
	delete []structure;
	cout<<"finish seq: "<<hp<<endl;
	return 1;
}	




int multiTempDoubleDomain::foldToMinimumEnergy
										  (double times, 
										   int numOfSimulations, 
										   char *hp)
{
	
	cout<<"multiTempDoubleDomain folding func foldToMinimumEnergy, "<<VERSIONDD1<<endl;
	
	//initFoldingComplex();
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	int linkerLength = fromto[2] - fromto[1] - 1;//e.g. 1 25 31 55: 31-25=6 
	int domain_A_length = fromto[1] - fromto[0] + 1;//e.g. 25-1=24
	int domain_B_length = fromto[3] - fromto[2] + 1;
	
	UPDATE_PROTEIN_MODES(res)
	 		
	cout<<"doubledomain foldToMinimumEnergy: Begin folding:"<<endl;
	
	char fostr[1024];
	cout<<times<<", seq: "<<hp<<endl;
	sprintf(fostr, "%smtdd-itr%d.data", outputDatafileName, (int)times);
	cout<<fostr<<endl;
	ofstream of(fostr); 
	of<<"#SEQ\t"<<hp<<endl<<"max mcs: "<<times<<", maxRangeOfLocalConf: "<<maxRangeOfLocalConf<<", edgesProbability: "<<edgesProbability<<", simulationFactor: A:"<<domain_A_temp<<", B:"<<domain_B_temp<<", perturbationFactor: A:"<<domain_A_perturbation<<", B:"<<domain_B_perturbation<<", Method: "<<VERSIONDD1<<" foldToMinimumEnergy"<<endl<<", collisionsWithConfinment: "<<collisionsWithConfinment<<endl;
	of<<"#DOUBLEDOMAIN\t"<<fromto[0]<<" "<<fromto[1]<<" "<<fromto[2]<<" "<<fromto[3]<<endl;
	
	for(int m = 0; m < numOfSimulations; m++)
	{
		cout<<"Doing itr: "<<m<<endl;
		initFoldingComplex();
		int focusSuccessFlag = 0;
		double itr = 0, alpha_itr = 0;
			
		if(confine) {
			int r;
			preConfinement = true;
			for(r = 0; r < times*10; r++)
			{
				foldOnce();
				point pdxdy = getMaxDist();
	// 			cout<<"dxdy: "<<pdxdy<<endl;
				if( (pdxdy.x + 1 <= confineXsize) &&
						(pdxdy.y + 1 <= confineYsize) ) {
					cout<<"Confined! took "<<r<<" times"<<endl<<pdxdy<<endl;
					CfileHdlr.writeStructure2output(sizeOfResidueArray, this);
					preConfinement = false;
					break;
				}
			}
			if(r == times*10) {
				cout<<"ERROR - Could not confine."<<endl;
				continue;
			}
			initParameters();
// 			cout<<"Struct-B Energy: "<<BFA[2]->energy<<", MCS: "<<BFA[2]->stepNumber<<", anyInterDomainInteractions: "<<anyInterDomainInteractions<<", successfulInterDomainInteractions: "<<successfulInterDomainInteractions<<", collisionsWithDomainNotInFocus: "<<collisionsWithDomainNotInFocus<<endl<<endl;
		}
		
		for(int i = 0; i < times; i++)
		{

			itr++;
// 			alpha_itr++;
// 			cout<<"---------------------- "<<i<<" ----------------------------"<<endl;
			int SuccessFlag = 0;
			if(foldOnce()) {
// 				cout<<"Success ####!!!"<<endl;
				SuccessFlag = 1;
			}
			// Only counting domainInFocus steps
			if(domainInFocus == 1 || domainInFocus == 2)
				if(!movementIncludesDomainInFocus() || (confine && wasOutOfConfinedRegion)) {
					wasOutOfConfinedRegion = false;
					i--;
// 					cout<<"Going down "<<i<<endl;
				}
				else {
					focusSuccessFlag += SuccessFlag;
				}
		}
		cout<<"focus ctr: "<<focusSuccessFlag<<" success ctr: "<<successCtr<<" all:"<<itr<<" f="<<successCtr/itr<<endl;
		CfileHdlr.writeStructure2file(sizeOfResidueArray, BFA[0], of);
		of<<"Struct-D Energy: "<<BFA[0]->energy<<", MCS: "<<BFA[0]->stepNumber<<endl<<endl;
		
		int dd, sd;
		for(dd = fromto[0], sd = 1; dd <= fromto[1]; dd++, sd++) 
			structure[sd] = BFA[1]->res[dd].position;
		CfileHdlr.writeStructure2file(domain_A_length, structure, &hp[fromto[0] - 1], of);
		of<<"Struct-A Energy: "<<BFA[1]->energy<<", MCS: "<<BFA[1]->stepNumber<<", anyInterDomainInteractions: "<<anyInterDomainInteractions<<", successfulInterDomainInteractions: "<<successfulInterDomainInteractions<<", collisionsWithDomainNotInFocus: "<<collisionsWithDomainNotInFocus<<", collisionsWithConfinment: "<<collisionsWithConfinment<<endl;
		char signs[4] = {'H', 'P', '+', '-'};
		of<<"IntraContacts-A: ";
		for(int q = 0; q < 4; q++)
			for(int u = q; u < 4; u++) {
				int intCnts = intraContacts1[q][u];
				if(q != u)
					intCnts += intraContacts1[u][q];
				of<<signs[u]<<signs[q]<<": "<<intCnts;
				if(q < 3 || u < 3)
					of<<", ";
			}
		of<<endl;
		of<<"LinkerContacts-A: ";
		for(int q = 0; q < 4; q++)
			for(int u = q; u < 4; u++) {
				int intCnts = linkerContacts1[q][u];
				if(q != u)
					intCnts += linkerContacts1[u][q];
				of<<signs[u]<<signs[q]<<": "<<intCnts;
				if(q < 3 || u < 3)
					of<<", ";
			}
		of<<endl;
		for(dd = fromto[2], sd = 1; dd <= fromto[3]; dd++, sd++) 
			structure[sd] = BFA[2]->res[dd].position;
		CfileHdlr.writeStructure2file(domain_B_length, structure, &hp[fromto[2] - 1], of);
		of<<"Struct-B Energy: "<<BFA[2]->energy<<", MCS: "<<BFA[2]->stepNumber<<", anyInterDomainInteractions: "<<anyInterDomainInteractions<<", successfulInterDomainInteractions: "<<successfulInterDomainInteractions<<", collisionsWithDomainNotInFocus: "<<collisionsWithDomainNotInFocus<<", collisionsWithConfinment: "<<collisionsWithConfinment<<", domainInFocusMCS: "<<domainInFocusMCS<<endl;
		of<<"IntraContacts-B: ";
		for(int q = 0; q < 4; q++)
			for(int u = q; u < 4; u++) {
				int intCnts = intraContacts2[q][u];
				if(q != u)
					intCnts += intraContacts2[u][q];
				of<<signs[u]<<signs[q]<<": "<<intCnts;
				if(q < 3 || u < 3)
					of<<", ";
			}
		of<<endl;
		of<<"LinkerContacts-B: ";
		for(int q = 0; q < 4; q++)
			for(int u = q; u < 4; u++) {
				int intCnts = linkerContacts2[q][u];
				if(q != u)
					intCnts += linkerContacts2[u][q];
				of<<signs[u]<<signs[q]<<": "<<intCnts;
				if(q < 3 || u < 3)
					of<<", ";
			}
		of<<endl;
		
		intraContacts1[4][4], intraContacts2[4][4], interContacts[4][4], linkerContacts1[4][4], linkerContacts2[4][4];
		of<<"InterContacts: ";
		for(int q = 0; q < 4; q++)
			for(int u = q; u < 4; u++) {
				int intCnts = interContacts[q][u];
				if(q != u)
					intCnts += interContacts[u][q];
				of<<signs[u]<<signs[q]<<": "<<intCnts;
				if(q < 3 || u < 3)
					of<<", ";
			}
		of<<endl;
	}
	
	of.close();
	delete []structure;
	cout<<"finish seq: "<<hp<<endl;
	return 1;
}	


void multiTempDoubleDomain::countSingleInteraction(int x, int y, int i, int state1) 
{
	int state2;
	if(boolMatrix[y][x] == 0)
		return;
		
	if(boolMatrix[y][x] >= fromto[0] && boolMatrix[y][x] <= fromto[1]) 
		state2 = 1;
	else if(boolMatrix[y][x] >= fromto[2] && boolMatrix[y][x] <= fromto[3])
		state2 = 2;
	else { //linker
		state2 = 4;
// 		cout<<"linker: "<<boolMatrix[y][x]<<" "<<fromto[1]<<" - "<<fromto[2]<<endl;
	} 
		
	switch(state1 + state2) {
		case 1+1:	intraContacts1[res[boolMatrix[y][x]].mode][res[i].mode]++;
							break;
		case 2+2:	intraContacts2[res[boolMatrix[y][x]].mode][res[i].mode]++;
							break;
		case 1+2:	interContacts[res[boolMatrix[y][x]].mode][res[i].mode]++;
							break;
		case 1+4:	linkerContacts1[res[boolMatrix[y][x]].mode][res[i].mode]++;
							break;
		case 2+4:	linkerContacts2[res[boolMatrix[y][x]].mode][res[i].mode]++;
							break;
		default:	break;
	}
// 	if((res[boolMatrix[y][x]].mode == POSITIVE_CHARGE && res[i].mode == NEGATIVE_CHARGE) ||
// 	   (res[boolMatrix[y][x]].mode == NEGATIVE_CHARGE && res[i].mode == POSITIVE_CHARGE) ) {
// 		saltBridgeInteractions++;
// 	}
// 	if(res[boolMatrix[y][x]].mode == HYDROPHOBIC && res[i].mode == HYDROPHOBIC) {
// 		saltBridgeInteractions++;
// 	}
	if((state1 == 4)^(state2 == 4))
		saltBridgeInteractions++;
}

void multiTempDoubleDomain::calculateMoveContactStatistics()
{
	int state1;
	saltBridgeInteractions = 0;
	
	if(currentMoveSize == 0) {
		int i = currentSimulationPivot;
		int x = res[i].position.x;
		int y = res[i].position.y;
		
		if(i >= fromto[0] && i <= fromto[1])
			state1 = 1;
		else if(i >= fromto[2] && i <= fromto[3])
			state1 = 2;
		else // linker
			state1 = 4;
			
		if(y < top_y - 1)
			countSingleInteraction(x, y + 1, i, state1); 
		if(y > buttom_y)
			countSingleInteraction(x, y - 1, i, state1);
		if(x < right_x -1)
			countSingleInteraction(x + 1, y, i, state1);
		if(x > left_x)
			countSingleInteraction(x - 1, y, i, state1);
	}
	else {
		for(int i = currentSimulationPivot; i <= currentSimulationPivot + currentMoveSize - 1; i++)
		{
			int x = tmpArr[i].x;
			int y = tmpArr[i].y;
			if(i >= fromto[0] && i <= fromto[1])
				state1 = 1;
			else if(i >= fromto[2] && i <= fromto[3])
				state1 = 2;
			else // linker
				state1 = 4;
				
			if(y < top_y - 1)
				countSingleInteraction(x, y + 1, i, state1); 
			if(y > buttom_y)
				countSingleInteraction(x, y - 1, i, state1);
			if(x < right_x -1)
				countSingleInteraction(x + 1, y, i, state1);
			if(x > left_x)
				countSingleInteraction(x - 1, y, i, state1);
		}	
	}
}



point multiTempDoubleDomain::getMaxDist()
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

point multiTempDoubleDomain::getMaxDistInMovement()
{
	point pdxdy;
	/*
	pdxdy.x = max(x) - min(x)
	pdxdy.y = max(y) - min(y)
	*/
	
	int minX, minY;
	int maxX, maxY;\
	
	minX = maxX = res[1].position.x;
	minY = maxY = res[1].position.y;
		
	if(currentMoveSize == 0) {			
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
	else {
		int i = 2;
		for(; i < currentSimulationPivot; i++)
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
		for(; i <= currentSimulationPivot + currentMoveSize - 1; i++)
		{
			if(minX > tmpArr[i].x)
				minX = tmpArr[i].x;
			if(maxX < tmpArr[i].x)
				maxX = tmpArr[i].x;
				
			if(minY > tmpArr[i].y)
				minY = tmpArr[i].y;
			if(maxY < tmpArr[i].y)
				maxY = tmpArr[i].y;
		}
		for(; i <= sizeOfResidueArray; i++)
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
}

int multiTempDoubleDomain::foldOnce()
{
	int pivot = RNG.generateNumberInRange(1, sizeOfResidueArray);
	int fold_type = RNG.generateNumberInRange(0, edgesProbability);
	int success = 0;
	currentSimulationPivot = pivot;
	
	switch(fold_type)
	{	
		case 0: if(pivot == 1) {
							if(tailRotateLeft(pivot) == 1)
								success++;
						}
						else if(pivot == sizeOfResidueArray) {
							if(tailRotateLeft(pivot) == 1)
								success++;
						}
						break;

		case 1:	if(pivot == 1) {
							if(tailRotateRight(pivot) == 1)
								success++;
						}
						else if(pivot == sizeOfResidueArray) {
							if(tailRotateRight(pivot) == 1)
								success++;
						} 
						break;
						
		case 2:	if(pivot == 1) {
							if(tailRotate180(pivot) == 1)
								success++;
						}
						else if(pivot == sizeOfResidueArray) {
							if(tailRotate180(pivot) == 1)
								success++;
						} 
						break;
						 
		default:if(randLocalMod(pivot))
						 		success++;
						break;
			
	}
	successCtr += success;
	return success;
}

bool multiTempDoubleDomain::hasCollisionWithDomainNotInFocus(point p)
{
	if( (p.x < left_x) || (p.x >= right_x) )
		{
			//cout<<"out of limits\n";
			return false;
		}
		if( (p.y < buttom_y) || (p.y >= top_y) )
		{
			//cout<<"out of limits\n";
			return false;
		}

		return (boolMatrix[p.y][p.x] >= fromNotInFocus && boolMatrix[p.y][p.x] <= toNotInFocus);
}
	
int multiTempDoubleDomain::randLocalMod(int pivot)
{
	if(pivot > (sizeOfResidueArray - 2))
		return 0;
	
	enterLocalConf++;
	
	point p1, p2;
	
	int  max_res = maxRangeOfLocalConf;
	if((max_res + pivot) > sizeOfResidueArray)
		max_res = sizeOfResidueArray - pivot;
	
	int dres = RNG.generateNumberInRange(2, max_res);
	currentMoveSize = dres;
	// Check if detaching from domain in focus:
	bool wasInFocus = false;
	tmpArr[pivot] = res[pivot].position;
	for(int i = pivot + 1; i <= (pivot + dres - 1); i++)
	{
		tmpArr[i] = res[i].position;//res[pivot].position;
	}
	
	bool movementIncludesDomainInFocus1 = movementIncludesDomainInFocus();
	bool haveInteractionWithDomainInFocus1 = haveInteractionWithDomainInFocus();
	
	switch(domainInFocus)
	{
		case 1: 
		case 2: if(movementIncludesDomainInFocus1 || haveInteractionWithDomainInFocus1) {
							wasInFocus = true;
// 							cout<<"Was in focus!!"<<endl;
						}
						break;
		case 0:
		case 3: break;
	}
	
	point* parr = lc.getNewLocalConf(res[pivot].position, res[pivot + dres].position, dres);
	 
	if( parr == NULL )
	{
//		cout<<"parr == NULL "<<"dres: "<<dres<<endl;
		return 0;
	}
	
	/* On success */
	/*
	cout<<"pivot: "<<pivot<<endl;	
	cout<<"lc.pivotPoint: "<<lc.pivotPoint.x<<", "<<lc.pivotPoint.y<<endl;
	cout<<"other point: "<<res[pivot+2].position.x<<" ,"<<res[pivot+2].position.y<<endl;
	cout<<"res[pivot].position: "<<res[pivot].position.x<<" ,"<<res[pivot].position.y<<endl;
	//cout<<"Matrix before:\n";
	//printBoolMatrix();
	*/
	int i, j;
// 	cout<<"Assign: "<<res[pivot].position<<endl;
	tmpArr[pivot] = res[pivot].position; //this is in order that function movementIncludesDomainInFocus() will also be able to check if the pivot position has any interaction with the focus domain.
	for(i = pivot + 1, j = 0; i <= (pivot + dres - 1); i++, j++)
	{
		point tt = parr[j] + lc.pivotPoint;
// 		cout<<"parr[j]: "<<j<<", "<<tt.x<<" ,"<<tt.y<<endl;
		tmpArr[i] = parr[j] + lc.pivotPoint;//res[pivot].position;
		dismissPosition(i);
	}
	
	
	for(i = pivot + 1, j = 0; i <= (pivot + dres - 1); i++, j++)//(i = 0; i < dres - 1; i++)
	{	 
		if(!isVacant(tmpArr[i]))
		{
			if(movementIncludesDomainInFocus1 && hasCollisionWithDomainNotInFocus(tmpArr[i]))
				collisionsWithDomainNotInFocus++;
				
			for(j = pivot + 1; j <= (pivot + dres - 1); j++)
				occupyPosition(j);//by the old Residue array
			//cout<<"Non vacant: "<<tmpArr[i]<<endl;
			return 0;
		}
	}
	/* All points are vacant */
	for(j = pivot + 1; j <= (pivot + dres - 1); j++)
	{
			occupyPositionByTmpArr(j);
			//res[j].position = tmpArr[j];//tmp!!!!!
	}
			
	
	double newEnergy = calculateEnergy(pivot, dres); //270813
	//if(newEnergy <= energy)
	//cout<<"new energy: "<<newEnergy<<", energy: " <<energy<<endl;
	if(MontaCarloAnnealing(newEnergy, energy, wasInFocus) && !outOfBorders(pivot, dres)) //270813
// 	if(MonteCarloAnnealingByDomain(wasInFocus) && !outOfBorders(pivot, dres))//270813
	{
		energy = newEnergy;//270813
// 		updateEnergiesByDomains();//270813
		
		for(j = pivot + 1; j <= (pivot + dres - 1); j++)
			res[j].position = tmpArr[j];
// 		cout<<"1 Got here!"<<endl;
		modifyBestFoldingArray();
// 		cout<<"2 Got here!"<<endl;
		successLocalConf++;
		
		return 1;
	}
	else
	{
		for(j = pivot + 1; j <= (pivot + dres - 1); j++)
			dismissPosition(tmpArr[j]);
		for(j = pivot + 1; j <= (pivot + dres - 1); j++)
			occupyPosition(j);
		return 0;
	}
	return 0;
}
		
	
	
	
int multiTempDoubleDomain::tailRotateLeft(int pivot)
{
	// x = -y + dx + dy
	// y =  x - dx + dy
	point newp;
	currentMoveSize = 0;
	// Check if detaching from domain in focus:
	bool wasInFocus = false;
	bool movementIncludesDomainInFocus1 = movementIncludesDomainInFocus();
	bool haveInteractionWithDomainInFocus1 = haveInteractionWithDomainInFocus();
	switch(domainInFocus)
	{
		case 1: 
		case 2: if(movementIncludesDomainInFocus1 || haveInteractionWithDomainInFocus1) {
							wasInFocus = true;
						}
						break;
		case 0:
		case 3: break;
	}
	
	//Right end:
	if(pivot > 1)
	{
	
		newp.x = res[sizeOfResidueArray - 1].position.x +
			 res[sizeOfResidueArray - 1].position.y -
			 res[sizeOfResidueArray].position.y;
		
		newp.y = res[sizeOfResidueArray].position.x -
			 res[sizeOfResidueArray - 1].position.x +
			 res[sizeOfResidueArray - 1].position.y;
			 

		
		if(isVacant(newp))
		{
			dismissPosition(sizeOfResidueArray);
			point prevp = res[sizeOfResidueArray].position;
			res[sizeOfResidueArray].position = newp;
			occupyPosition(sizeOfResidueArray);

			double newEnergy = calculateEnergy();//270813
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy, wasInFocus) && !outOfBorders())
// 			if(MonteCarloAnnealingByDomain(wasInFocus) && !outOfBorders())//270813
			{
			energy = newEnergy;//270813
// 				updateEnergiesByDomains();//270813
				
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(sizeOfResidueArray);
				res[sizeOfResidueArray].position = prevp;
				occupyPosition(sizeOfResidueArray);
				return 0;
			}
				
			
		}
		else {
			if(movementIncludesDomainInFocus1 && hasCollisionWithDomainNotInFocus(newp))
				collisionsWithDomainNotInFocus++;
		}
	}
	//Left end:
	else
	{
		newp.x = res[2].position.x + 
			 res[2].position.y - 
			 res[1].position.y;
		
		newp.y = res[1].position.x -
			 res[2].position.x +
			 res[2].position.y;
		
		if(isVacant(newp))
		{
			dismissPosition(1);
			point prevp = res[1].position;
			res[1].position = newp;
			occupyPosition(1);

						double newEnergy = calculateEnergy();//270813
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy, wasInFocus) && !outOfBorders())
// 			if(MonteCarloAnnealingByDomain(wasInFocus) && !outOfBorders())//270813
			{
				energy = newEnergy;//270813
// 				updateEnergiesByDomains();//270813
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(1);
				res[1].position = prevp;
				occupyPosition(1);
				return 0;
			}
		}
		else {
			if(movementIncludesDomainInFocus1 && hasCollisionWithDomainNotInFocus(newp))
				collisionsWithDomainNotInFocus++;
		}
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
		
	}
	return 0;
}

int multiTempDoubleDomain::tailRotateRight(int pivot)
{
	point newp;
	currentMoveSize = 0;
	// x =  y -dy+dx
	// y = -x +dx+dy
	// Check if detaching from domain in focus:
	bool wasInFocus = false;
	bool movementIncludesDomainInFocus1 = movementIncludesDomainInFocus();
	bool haveInteractionWithDomainInFocus1 = haveInteractionWithDomainInFocus();
	
	switch(domainInFocus)
	{
		case 1: 
		case 2: if(movementIncludesDomainInFocus1 || haveInteractionWithDomainInFocus1) {
							wasInFocus = true;
						}
						break;
		case 0:
		case 3: break;
	}
	//There is no need to initialize tmpArr because we know the
	//positions of update
	
	//Right end:
	if(pivot > 1)
	{
		newp.x = res[sizeOfResidueArray].position.y - 
			 res[sizeOfResidueArray - 1].position.y + 
			 res[sizeOfResidueArray - 1].position.x;
		
		newp.y = - res[sizeOfResidueArray].position.x +
			 res[sizeOfResidueArray - 1].position.x +
			 res[sizeOfResidueArray - 1].position.y;
			 
		if(isVacant(newp))
		{
			dismissPosition(sizeOfResidueArray);
			point prevp = res[sizeOfResidueArray].position;
			res[sizeOfResidueArray].position = newp;
			occupyPosition(sizeOfResidueArray);

						double newEnergy = calculateEnergy();//270813
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy, wasInFocus) && !outOfBorders())
// 			if(MonteCarloAnnealingByDomain(wasInFocus) && !outOfBorders())//270813
			{
			energy = newEnergy;//270813
// 				updateEnergiesByDomains();//270813
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(sizeOfResidueArray);
				res[sizeOfResidueArray].position = prevp;
				occupyPosition(sizeOfResidueArray);
				return 0;
			}
		}
		else {
			if(movementIncludesDomainInFocus1 && hasCollisionWithDomainNotInFocus(newp))
				collisionsWithDomainNotInFocus++;
		}
	}
	//Left end:
	else
	{
		newp.x = res[1].position.y - 
			 res[2].position.y + 
			 res[2].position.x;
		
		newp.y = - res[1].position.x +
			 res[2].position.x +
			 res[2].position.y;
		
		if(isVacant(newp))
		{
			dismissPosition(1);
			point prevp = res[1].position;
			res[1].position = newp;
			occupyPosition(1);

						double newEnergy = calculateEnergy();//270813
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy, wasInFocus) && !outOfBorders())
// 			if(MonteCarloAnnealingByDomain(wasInFocus) && !outOfBorders())//270813
			{
			energy = newEnergy;//270813
// 				updateEnergiesByDomains();//270813
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(1);
				res[1].position = prevp;
				occupyPosition(1);
				return 0;
			}
		}
		else {
			if(movementIncludesDomainInFocus1 && hasCollisionWithDomainNotInFocus(newp))
				collisionsWithDomainNotInFocus++;
		}
		
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
	}
	return 0;
}

int multiTempDoubleDomain::tailRotate180(int pivot)
{
	point newp;
	currentMoveSize = 0;	
	// Check if detaching from domain in focus:
	bool wasInFocus = false;
	bool movementIncludesDomainInFocus1 = movementIncludesDomainInFocus();
	bool haveInteractionWithDomainInFocus1 = haveInteractionWithDomainInFocus();
	
	switch(domainInFocus)
	{
		case 1: 
		case 2: if(movementIncludesDomainInFocus1 || haveInteractionWithDomainInFocus1) {
							wasInFocus = true;
						}
						break;
		case 0:
		case 3: break;
	}
	//Right end:
	if(pivot > 1)
	{
		newp.x = - res[sizeOfResidueArray].position.x + 2*res[sizeOfResidueArray - 1].position.x;
		newp.y = - res[sizeOfResidueArray].position.y + 2*res[sizeOfResidueArray - 1].position.y;
		
		
		if(isVacant(newp))
		{
			dismissPosition(sizeOfResidueArray);
			point prevp = res[sizeOfResidueArray].position;
			res[sizeOfResidueArray].position = newp;
			occupyPosition(sizeOfResidueArray);

						double newEnergy = calculateEnergy();//270813
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy, wasInFocus) && !outOfBorders())
// 			if(MonteCarloAnnealingByDomain(wasInFocus) && !outOfBorders())//270813
			{
			energy = newEnergy;//270813
// 				updateEnergiesByDomains();//270813
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(sizeOfResidueArray);
				res[sizeOfResidueArray].position = prevp;
				occupyPosition(sizeOfResidueArray);
				return 0;
			}
		}
		else {
			if(movementIncludesDomainInFocus1 && hasCollisionWithDomainNotInFocus(newp))
				collisionsWithDomainNotInFocus++;
		}
	}
	//Left end:
	else
	{
		newp.x = - res[1].position.x + 2*res[2].position.x;
		newp.y = - res[1].position.y + 2*res[2].position.y;
		
		if(isVacant(newp))
		{
			dismissPosition(1);
			point prevp = res[1].position;
			res[1].position = newp;
			occupyPosition(1);

						double newEnergy = calculateEnergy();//270813
			//if(newEnergy <= energy)
			if(MontaCarloAnnealing(newEnergy, energy, wasInFocus) && !outOfBorders())
// 			if(MonteCarloAnnealingByDomain(wasInFocus) && !outOfBorders())//270813
			{
			energy = newEnergy;//270813
// 				updateEnergiesByDomains();//270813
				modifyBestFoldingArray();
				return 1;
			}
			else
			{
				//reconfiguring old point
				dismissPosition(1);
				res[1].position = prevp;
				occupyPosition(1);
				return 0;
			}
		}	
		else {
			if(movementIncludesDomainInFocus1 && hasCollisionWithDomainNotInFocus(newp))
				collisionsWithDomainNotInFocus++;
		}
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
	}
	return 0;
}

bool multiTempDoubleDomain::movementIncludesLinker() {
	if((currentSimulationPivot > fromto[1] && currentSimulationPivot < fromto[2])) //||
// 		 (currentMoveSize > 1 & currentSimulationPivot + currentMoveSize - 1 > fromto[1] && currentSimulationPivot + currentMoveSize - 1 < fromto[2]))
		 return true;
	return false;
}

bool multiTempDoubleDomain::movementIncludesDomainInFocus() {
// 	cout<<"pivot: "<<currentSimulationPivot<<" dres: "<<currentMoveSize<<endl;
	if(currentSimulationPivot >= fromFocus && currentSimulationPivot <= toFocus) {
// 		cout<<"in focus"<<endl;
		return true;
	}
	else if(currentMoveSize > 1 & currentSimulationPivot + currentMoveSize - 1 >= fromFocus && currentSimulationPivot + currentMoveSize - 1 <= toFocus) {
// 		cout<<"in focus"<<endl;
		return true;
	}
	else {
// 		cout<<"Not in focus"<<endl;
		return false;
	}
}

bool multiTempDoubleDomain::haveInteractionWithDomainInFocus() {
	
// 	cout<<"int pivot: "<<currentSimulationPivot<<" dres: "<<currentMoveSize<<endl;
	// tail moves (tmpArr is not used):
	if(currentMoveSize == 0) {
		for(int i = currentSimulationPivot; i <= currentSimulationPivot; i++)
		{	
// 			cout<<"0 Res: "<<i<<endl;
			int x = res[i].position.x;
			int y = res[i].position.y;
// 			cout<<"tail interacting res idx: "<< (y < top_y - 1 ? boolMatrix[y+1][x] : -1)<<", ";
// 			cout<< (y > buttom_y ? boolMatrix[y-1][x] : -1) <<", ";
// 			cout<< (x < right_x - 1 ? boolMatrix[y][x+1] : -1) <<", ";
// 			cout<< (x > left_x ? boolMatrix[y][x-1] : -1) <<endl;
			
			if(y < top_y - 1 && boolMatrix[y+1][x] >= fromFocus && boolMatrix[y+1][x] <= toFocus) {
// 				cout<<"In focus!!!\n";
				return true;
			}
			if(y > buttom_y && boolMatrix[y-1][x] >= fromFocus && boolMatrix[y-1][x] <= toFocus) {
// 			cout<<"In focus!!!\n";
				return true;
			}
			if(x < right_x -1 && boolMatrix[y][x+1] >= fromFocus && boolMatrix[y][x+1] <= toFocus) {
// 			cout<<"In focus!!!\n";
				return true;
			}
			if(x > left_x && boolMatrix[y][x-1] >= fromFocus && boolMatrix[y][x-1] <= toFocus) {
// 			cout<<"In focus!!!\n";
				return true;
			}
		}//end for loop
	}
	else {
	// rand moves (tmpArr is accounted):
// 		cout<<"rand moves"<<endl;
		for(int i = currentSimulationPivot; i <= currentSimulationPivot + currentMoveSize - 1; i++)
		{
// 			cout<<"Res: "<<i<<endl;
			int x = tmpArr[i].x;
			int y = tmpArr[i].y;
// 			cout<<"i, x, y:"<<i<<", "<<x<<", "<<y<<endl;
// 			for(int ti = 0; ti <= sizeOfResidueArray; ti++)
// 				cout<<tmpArr[ti].x;
// 			cout<<endl;
// 			cout<<"rand interacting res idx: "<< (y < top_y - 1 ? boolMatrix[y+1][x] : -1)<<", ";
// 			cout<< (y > buttom_y ? boolMatrix[y-1][x] : -1) <<", ";
// 			cout<< (x < right_x - 1 ? boolMatrix[y][x+1] : -1) <<", ";
// 			cout<< (x > left_x ? boolMatrix[y][x-1] : -1) <<endl;
			//cout<<"rand interacting res idx: "<<boolMatrix[y+1][x]<<", "<<boolMatrix[y-1][x]<<", "<<boolMatrix[y][x+1]<<", "<<boolMatrix[y][x-1]<<endl;
			if(y < top_y - 1 && boolMatrix[y+1][x] >= fromFocus && boolMatrix[y+1][x] <= toFocus) {
// 				cout<<"In focus!!!\n";
				return true;
			}
			if(y > buttom_y && boolMatrix[y-1][x] >= fromFocus && boolMatrix[y-1][x] <= toFocus) {
// 				cout<<"In focus!!!\n";
				return true;
			}
			if(x < right_x -1 && boolMatrix[y][x+1] >= fromFocus && boolMatrix[y][x+1] <= toFocus) {
// 				cout<<"In focus!!!\n";
				return true;
			}
			if(x > left_x && boolMatrix[y][x-1] >= fromFocus && boolMatrix[y][x-1] <= toFocus) {
// 				cout<<"In focus!!!\n";
				return true;
			}
		}	
	}//end for loop
// 	cout<<"not in focus"<<endl;
	return false;
}

void multiTempDoubleDomain::getDomainInFocusStruct(point *mystruct) {
	int m = 1;
	for(int i = fromFocus; i <= toFocus; i++, m++) {
		mystruct[m].x = res[i].position.x;
		mystruct[m].y = res[i].position.y;
	}
}

void multiTempDoubleDomain::updateEnergiesByDomains() {
	double monomerEnergy[2];
	calculateMonomersEnergy('A', monomerEnergy);
	energyA = monomerEnergy[0];
	calculateMonomersEnergy('B', monomerEnergy);
	energyB = monomerEnergy[0];
	calculateMonomersEnergy('D', monomerEnergy);
	energy = monomerEnergy[1];
}

bool multiTempDoubleDomain::MonteCarloAnnealingByDomain(bool wasInFocus)
{
	double newE;
	double oldE;
	double monomerEnergy[2];
	
	if(currentSimulationPivot >= fromto[0] && currentSimulationPivot <= fromto[1]) {
		oldE = energyA;
		calculateMonomersEnergy('A', monomerEnergy);
		newE = monomerEnergy[0];
	} 
	else if(currentSimulationPivot >= fromto[2] && currentSimulationPivot <= fromto[3]) {
		oldE = energyB;
		calculateMonomersEnergy('B', monomerEnergy);
		newE = monomerEnergy[0];
	}
	else { //linker = D
		oldE = energy;
		calculateMonomersEnergy('D', monomerEnergy);
		newE = monomerEnergy[0];
	}
	point dxdy = getMaxDistInMovement();
	wasOutOfConfinedRegion = dxdy.x + 1 <= confineXsize && dxdy.y + 1 <= confineYsize;
	if(confine && !preConfinement) { 
		if(!wasOutOfConfinedRegion) {
			collisionsWithConfinment++;
// 			cout<<"wasOutOfConfinedRegion: "<<wasOutOfConfinedRegion<<": "<<dxdy<<endl;
			return false;
		}
// 		cout<<" Did good! "<<dxdy<<endl;
	}
	
	enteringMCAnneal++;
	// If the move is part of the linker only than what counts is the pivot
	double currPerturbationFactor = perturbationFactor[currentSimulationPivot];
	double currTemp = sequenceTemperature[currentSimulationPivot];
	
	bool movementIncludesDomainInFocus1 = movementIncludesDomainInFocus();
	bool haveInteractionWithDomainInFocus1 = haveInteractionWithDomainInFocus();
	if(movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1) 
		anyInterDomainInteractions++;
		
	if(!enableInteractionsBetweenDomains && movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1) {
		return false;
	}
	
// 	if(movementIncludesLinker()) {
// 		currPerturbationFactor = 0.1;
// 		currTemp = 10;
// 	}
// 	else {
		switch(domainInFocus)
		{
			case 1: if(wasInFocus || movementIncludesDomainInFocus1 || haveInteractionWithDomainInFocus1) {
								currTemp = domain_A_temp;
								currPerturbationFactor = domain_A_perturbation;
							}
							break;
			case 2: if(wasInFocus || movementIncludesDomainInFocus1 || haveInteractionWithDomainInFocus1) {
								currTemp = domain_B_temp;
								currPerturbationFactor = domain_B_perturbation;
							}
							break;
			case 0:
			case 3: break;
		}
// 	}
	
// 	if(currTemp == 0)
// 		return false;
	if(newE < oldE) {
		if(currPerturbationFactor == 1) {
// 		cout<<"1 Got here!!"<<endl;
			calculateMoveContactStatistics();
			if(movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1) {
// 				if(saltBridgeInteractions > 0) {
// 					saltBridgeInteractions = 0;
// 					return false;
// 				}
				successfulInterDomainInteractions++;
			}
			return true;
		}
		else if(RNG.generateRandomFraction() <= currPerturbationFactor) {
// 		cout<<"2 Got here!!"<<endl;
			calculateMoveContactStatistics();
			if(movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1)  {
// 				if(saltBridgeInteractions > 0) {
// 					saltBridgeInteractions = 0;
// 					return false;
// 				}
				successfulInterDomainInteractions++;
			}
			return true;
		}
		else {
// 		cout<<"3 Got here!!"<<endl;
			return false;
		}
		if(movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1)  {
// 			if(saltBridgeInteractions > 0) {
// 				saltBridgeInteractions = 0;
// 				return false;
// 			}
			successfulInterDomainInteractions++;
		}
		return true;
	}
	else if( RNG.generateRandomFraction() < exp((oldE - newE)/(Ck*currTemp)) ) {	
// 	   cout<<":::::"<<movementIncludesDomainInFocus1<<"::::"<<haveInteractionWithDomainInFocus1<<endl;
		calculateMoveContactStatistics();
	  if(movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1) {
// 	  	if(saltBridgeInteractions > 0) {
// 				saltBridgeInteractions = 0;
// 				return false;
// 			}
			successfulInterDomainInteractions++;
		}
// 			cout<<"4 Got here!!"<<endl; 
		return true;
	}
	
	return false;
}

bool multiTempDoubleDomain::MontaCarloAnnealing(double newE, double oldE, bool wasInFocus)
{
	
	point dxdy = getMaxDistInMovement();
	wasOutOfConfinedRegion = dxdy.x + 1 <= confineXsize && dxdy.y + 1 <= confineYsize;
	if(confine && !preConfinement) { 
		if(!wasOutOfConfinedRegion) {
			collisionsWithConfinment++;
// 			cout<<"wasOutOfConfinedRegion: "<<wasOutOfConfinedRegion<<": "<<dxdy<<endl;
			return false;
		}
// 		cout<<" Did good! "<<dxdy<<endl;
	}
	
	enteringMCAnneal++;
	// If the move is part of the linker only than what counts is the pivot
	double currPerturbationFactor = perturbationFactor[currentSimulationPivot];
	double currTemp = sequenceTemperature[currentSimulationPivot];
	
	bool movementIncludesDomainInFocus1 = movementIncludesDomainInFocus();
	bool haveInteractionWithDomainInFocus1 = haveInteractionWithDomainInFocus();
	if(movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1) 
		anyInterDomainInteractions++;
	if(movementIncludesDomainInFocus1)
		domainInFocusItr++;
		
	if(!enableInteractionsBetweenDomains && movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1) {
		return false;
	}
// 	if(movementIncludesLinker()) {
// 		currPerturbationFactor = 0.1;
// 		currTemp = 10;
// 	}
	else {
		switch(domainInFocus)
		{
			case 1: if(wasInFocus || movementIncludesDomainInFocus1 || haveInteractionWithDomainInFocus1) {
								currTemp = domain_A_temp;
								currPerturbationFactor = domain_A_perturbation;
							}
							break;
			case 2: if(wasInFocus || movementIncludesDomainInFocus1 || haveInteractionWithDomainInFocus1) {
								currTemp = domain_B_temp;
								currPerturbationFactor = domain_B_perturbation;
							}
							break;
			case 0:
			case 3: break;
		}
	}
	
// 	if(currTemp == 0)
// 		return false;
// 	cout<<"MontaCa 1"<<endl;
	if(newE < oldE) {
		if(currPerturbationFactor == 1) {
// 		cout<<"1 Got here!!"<<endl;
			calculateMoveContactStatistics();
			if(movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1) {
// 				if(saltBridgeInteractions > 0) {
// 					saltBridgeInteractions = 0;
// 					return false;
// 				}
				successfulInterDomainInteractions++;
			}
// 			cout<<"MontaCa true"<<endl;
			return true;
		}
		else if(RNG.generateRandomFraction() <= currPerturbationFactor) {
// 		cout<<"2 Got here!!"<<endl;
			calculateMoveContactStatistics();
			if(movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1)  {
// 				if(saltBridgeInteractions > 0) {
// 					saltBridgeInteractions = 0;
// 					return false;
// 				}
				successfulInterDomainInteractions++;
			}
			return true;
		}
		else {
// 		cout<<"3 Got here!!"<<endl;
			return false;
		}
		if(movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1)  {
// 			if(saltBridgeInteractions > 0) {
// 				saltBridgeInteractions = 0;
// 				return false;
// 			}
			successfulInterDomainInteractions++;
		}
		return true;
	}
	else if( RNG.generateRandomFraction() < exp((oldE - newE)/(Ck*currTemp)) ) {	
// 	   cout<<":::::"<<movementIncludesDomainInFocus1<<"::::"<<haveInteractionWithDomainInFocus1<<endl;
		calculateMoveContactStatistics();
	  if(movementIncludesDomainInFocus1^haveInteractionWithDomainInFocus1) {
// 	  	if(saltBridgeInteractions > 0) {
// 				saltBridgeInteractions = 0;
// 				return false;
// 			}
			successfulInterDomainInteractions++;
		}
// 			cout<<"4 Got here!!"<<endl; 
		return true;
	}
	
	return false;
}
 	
int multiTempDoubleDomain::initTemperature(double Atemp, double Btemp, double Aperturb, double Bperturb) {
	
	domain_A_temp = Atemp;
	domain_B_temp = Btemp;
	domain_A_perturbation = Aperturb;
	domain_B_perturbation = Bperturb;
	
	sequenceTemperature = new double[sizeOfResidueArray + 1];
	perturbationFactor = new double[sizeOfResidueArray + 1];
	if(!sequenceTemperature || !perturbationFactor)
	{
		cout<<"ERROR - mem alloc multiTempDoubleDomain::initTemperature\n";
		exit(1);
	}
  	
  for(int i = fromto[0]; i <= fromto[1]; i++) {
  	 sequenceTemperature[i] = domain_A_temp;
  	 perturbationFactor[i] = domain_A_perturbation;	
  }
  for(int i = fromto[2]; i <= fromto[3]; i++) {
  	 sequenceTemperature[i] = domain_B_temp;
  	 perturbationFactor[i] = domain_B_perturbation;	
  }
  double linkerLength = fromto[2] - fromto[1] - 1;
  
  for(int i = fromto[1] + 1; i <= fromto[2] - 1; i++) {
		switch(domainInFocus)
		{
			case 1: sequenceTemperature[i] = domain_A_temp;
							perturbationFactor[i] = domain_A_perturbation;
							break;
			case 2: sequenceTemperature[i] = domain_B_temp;
							perturbationFactor[i] = domain_B_perturbation;
							break;
			case 0:
			case 3: sequenceTemperature[i] = domain_A_temp + (i - fromto[1])*((domain_B_temp - domain_A_temp)/(linkerLength));//from[1]=25 
							perturbationFactor[i] = domain_A_perturbation + (i - fromto[1])*((domain_B_perturbation - domain_A_perturbation)/(linkerLength));//from[1]=25
							break;
		}
	}
  
  cout<<"array temperature:\n";
  for(int i = 1; i <= sizeOfResidueArray; i++)
  	cout<<sequenceTemperature[i]<<" ";
  cout<<endl;
  cout<<"array perturbationFactor:\n";
  for(int i = 1; i <= sizeOfResidueArray; i++)
  	cout<<perturbationFactor[i]<<" ";
  cout<<endl;
  return 1;
}

multiTempDoubleDomain::multiTempDoubleDomain(int length, int* fromtoIn, double domain_A_tempIn, double domain_B_tempIn, double Aperturb, 
																						 double Bperturb, int domainInFocusIn, bool enableInteractionsBetweenDomainsIn, 
																						 bool confineIn, int confineXsizeIn, int confineYsizeIn):
doubleDomain(length, fromtoIn)
{
	cout<<"multiTempDoubleDomain ctor 1"<<endl;
	domainInFocus = domainInFocusIn;
	initTemperature(domain_A_tempIn, domain_B_tempIn, Aperturb, Bperturb);
	enableInteractionsBetweenDomains = enableInteractionsBetweenDomainsIn;
	anyInterDomainInteractions = 0;
	successfulInterDomainInteractions = 0;
	collisionsWithDomainNotInFocus = 0;
	saltBridgeInteractions = 0;
	
	wasOutOfConfinedRegion = false;
	collisionsWithConfinment = 0;
	preConfinement = false;
	
	domain_A_struct = 0;
	domain_B_struct = 0;
	
	
	whichDomainToAssign = 'C';
	
	cout<<"init domain in focus: "<<domainInFocus<<endl;
	
	confine = confineIn;
	
	if(confine) {
		confineXsize = confineXsizeIn;
		confineYsize = confineYsizeIn;
	}
	
	switch(domainInFocus)
	{
		// A
		case 1: fromFocus = fromto[0]; 
						toFocus = fromto[1];
						fromNotInFocus = fromto[2];
						toNotInFocus = fromto[3];
						cout<<"domain in focus: A"<<endl;
						break;
		// B
		case 2: fromFocus = fromto[2];
						toFocus = fromto[3];
						fromNotInFocus = fromto[0];
						toNotInFocus = fromto[1];
						cout<<"domain in focus: B"<<endl;
						break;
		// NA or A & B
		case 0: cout<<"NA "<<endl;
		case 3: cout<<"AB in focus"<<endl;
	}
	cout<<"Coor: "<<fromFocus<<", "<<toFocus<<endl;
	for(int i = 0; i < 4; i++) 
		for(int j = 0; j < 4; j++)
			intraContacts1[i][j] = intraContacts2[i][j] = interContacts[i][j] = linkerContacts1[i][j] = linkerContacts2[i][j] = 0;
}

multiTempDoubleDomain::multiTempDoubleDomain(int length, int* fromtoIn, double domain_A_tempIn, double domain_B_tempIn, double Aperturb, 
																						 double Bperturb, point *domain_struct, char whichDomain, int domainInFocusIn, bool enableInteractionsBetweenDomainsIn,
																						 bool confineIn, int confineXsizeIn, int confineYsizeIn):
doubleDomain(length, fromtoIn)
{
	cout<<"multiTempDoubleDomain ctor 2"<<endl;
	domainInFocus = domainInFocusIn;
	initTemperature(domain_A_tempIn, domain_B_tempIn, Aperturb, Bperturb);
	enableInteractionsBetweenDomains = enableInteractionsBetweenDomainsIn;
	anyInterDomainInteractions = 0;
	successfulInterDomainInteractions = 0;
	collisionsWithDomainNotInFocus = 0;
	saltBridgeInteractions = 0;
	
	wasOutOfConfinedRegion = false;
	collisionsWithConfinment = 0;
	preConfinement = false;
	
	domain_A_struct = 0;
	domain_B_struct = 0;
	domainInFocus = domainInFocusIn;
	cout<<"init domain in focus: "<<domainInFocus<<endl;
	
	if(whichDomain == 'A' || whichDomain == 'B')
		whichDomainToAssign = whichDomain;
	else
		whichDomainToAssign = 'C';
		
	confine = confineIn;
	
	if(confine) {
		confineXsize = confineXsizeIn;
		confineYsize = confineYsizeIn;
		cout<<"Confine: "<<confine<<" - "<<confineXsize<<", "<<confineYsize<<endl;
	}
	switch(domainInFocus)
	{
		// A
		case 1: fromFocus = fromto[0]; 
						toFocus = fromto[1];
						fromNotInFocus = fromto[2];
						toNotInFocus = fromto[3];
						cout<<"domain in focus: A"<<endl;
						break;
		// B
		case 2: fromFocus = fromto[2];
						toFocus = fromto[3];
						fromNotInFocus = fromto[0];
						toNotInFocus = fromto[1];
						cout<<"domain in focus: B"<<endl;
						break;
		// NA or A & B
		case 0: cout<<"NA "<<endl;
		case 3: cout<<"AB in focus"<<endl;
	}
	cout<<"Coor: "<<fromFocus<<", "<<toFocus<<endl;
	int domainSize = fromto[1] - fromto[0] + 1;
	if(whichDomain == 'A' && domain_struct) {
		domain_A_struct = new point[domainSize + 1];
		if(!domain_A_struct)
		{
			cout<<"ERROR - mem alloc ctor 2 multiTempDoubleDomain::domain_A_struct\n";
			exit(1);
		}
		cout<<"assigning struct A\n";
		for(int i = 1; i <= domainSize; i++) {
			domain_A_struct[i] = domain_struct[i];
		}
	}
	
	if(whichDomain == 'B' && domain_struct) {
		domain_B_struct = new point[domainSize + 1];
		if(!domain_B_struct)
		{
			cout<<"ERROR - mem alloc ctor 2 multiTempDoubleDomain::domain_B_struct\n";
			exit(1);
		}
		cout<<"assinging struct B\n";	
		for(int i = 1; i <= domainSize; i++) {
			domain_B_struct[i] = domain_struct[i];
		}
	}
	for(int i = 0; i < 4; i++) 
		for(int j = 0; j < 4; j++)
			intraContacts1[i][j] = intraContacts2[i][j] = interContacts[i][j] = linkerContacts1[i][j] = linkerContacts2[i][j] = 0;
			
}

multiTempDoubleDomain::multiTempDoubleDomain(int length, int* fromtoIn, double domain_A_tempIn, double domain_B_tempIn, double Aperturb, 
																						 double Bperturb, point *domain_struct1, point *domain_struct2, char whichDomain, int domainInFocusIn, bool enableInteractionsBetweenDomainsIn,
																						 bool confineIn, int confineXsizeIn, int confineYsizeIn):
doubleDomain(length, fromtoIn)
{
	cout<<"multiTempDoubleDomain ctor 2"<<endl;
	domainInFocus = domainInFocusIn;
	initTemperature(domain_A_tempIn, domain_B_tempIn, Aperturb, Bperturb);
	enableInteractionsBetweenDomains = enableInteractionsBetweenDomainsIn;
	anyInterDomainInteractions = 0;
	successfulInterDomainInteractions = 0;
	collisionsWithDomainNotInFocus = 0;
	saltBridgeInteractions = 0;
	
	wasOutOfConfinedRegion = false;
	collisionsWithConfinment = 0;
	preConfinement = false;
	
	domain_A_struct = 0;
	domain_B_struct = 0;
	domainInFocus = domainInFocusIn;
	if(whichDomain == 'A' || whichDomain == 'B')
		whichDomainToAssign = whichDomain;
	else
		whichDomainToAssign = 'C';
	
	cout<<"init domain in focus: "<<domainInFocus<<endl;
	
	confine = confineIn;
	
	if(confine) {
		confineXsize = confineXsizeIn;
		confineYsize = confineYsizeIn;
		cout<<"Confine: "<<confine<<" - "<<confineXsize<<", "<<confineYsize<<endl;
	}
	switch(domainInFocus)
	{
		// A
		case 1: fromFocus = fromto[0]; 
						toFocus = fromto[1];
						fromNotInFocus = fromto[2];
						toNotInFocus = fromto[3];
						cout<<"domain in focus: A"<<endl;
						break;
		// B
		case 2: fromFocus = fromto[2];
						toFocus = fromto[3];
						fromNotInFocus = fromto[0];
						toNotInFocus = fromto[1];
						cout<<"domain in focus: B"<<endl;
						break;
		// NA or A & B
		case 0: cout<<"NA "<<endl;
		case 3: cout<<"AB in focus"<<endl;
	}
	cout<<"Coor: "<<fromFocus<<", "<<toFocus<<endl;
	int domainSize = fromto[1] - fromto[0] + 1;
	if(domain_struct1) {
		domain_A_struct = new point[domainSize + 1];
		if(!domain_A_struct)
		{
			cout<<"ERROR - mem alloc ctor 2 multiTempDoubleDomain::domain_A_struct\n";
			exit(1);
		}
		cout<<"assigning struct A\n";
		for(int i = 1; i <= domainSize; i++) {
			domain_A_struct[i] = domain_struct1[i];
		}
	}
	
	if(domain_struct2) {
		domain_B_struct = new point[domainSize + 1];
		if(!domain_B_struct)
		{
			cout<<"ERROR - mem alloc ctor 2 multiTempDoubleDomain::domain_B_struct\n";
			exit(1);
		}
		cout<<"assinging struct B\n";	
		for(int i = 1; i <= domainSize; i++) {
			domain_B_struct[i] = domain_struct2[i];
		}
	}
	for(int i = 0; i < 4; i++) 
		for(int j = 0; j < 4; j++)
			intraContacts1[i][j] = intraContacts2[i][j] = interContacts[i][j] = linkerContacts1[i][j] = linkerContacts2[i][j] = 0;
			
}

multiTempDoubleDomain::~multiTempDoubleDomain()
{
	delete sequenceTemperature;
	delete perturbationFactor;
	if(domain_A_struct) 
		delete domain_A_struct;
	if(domain_B_struct) 
		delete domain_B_struct;
		
		
}

int multiTempDoubleDomain::initParameters() {
	cout<<"multiTempDoubleDomain::initParameters"<<endl;
	
	point zerop(0,0);
	
	energy = 0;
	energyA = 0;
	energyB = 0;
	
	anyInterDomainInteractions = 0;
	successfulInterDomainInteractions = 0;
	collisionsWithDomainNotInFocus = 0;
	saltBridgeInteractions = 0;
	
	wasOutOfConfinedRegion = false;
	collisionsWithConfinment = 0;
	preConfinement = false;
	
	firstPassageTime = false;
	Ck = ALPHA_UPPER_BOND;
	successCtr = 0;
	enteringMCAnneal = 0;
	successLocalConf = 0; 
	enterLocalConf = 1;

	domainInFocusItr = 0;
	domainInFocusMCS = 0;
	
	for(int i = 0; i < 4; i++) 
		for(int j = 0; j < 4; j++)
			intraContacts1[i][j] = intraContacts2[i][j] = interContacts[i][j] = linkerContacts1[i][j] = linkerContacts2[i][j] = 0;
			
	int i, y, x;

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
	return 0;

}
int multiTempDoubleDomain::initFoldingComplex()
{
	cout<<"multiTempDoubleDomain::initFoldingComplex"<<endl;
	
	point zerop(0,0);
	energy = 0;
	energyA = 0;
	energyB = 0;
	anyInterDomainInteractions = 0;
	successfulInterDomainInteractions = 0;
	collisionsWithDomainNotInFocus = 0;
	
	saltBridgeInteractions = 0;
	
	wasOutOfConfinedRegion = false;
	collisionsWithConfinment = 0;
	preConfinement = false;
	
	firstPassageTime = false;
	Ck = ALPHA_UPPER_BOND;
	successCtr = 0;
	enteringMCAnneal = 0;
	successLocalConf = 0; 
	enterLocalConf = 1;

	domainInFocusItr = 0;
	domainInFocusMCS = 0;
	
	for(int i = 0; i < 4; i++) 
		for(int j = 0; j < 4; j++)
			intraContacts1[i][j] = intraContacts2[i][j] = interContacts[i][j] = linkerContacts1[i][j] = linkerContacts2[i][j] = 0;
			
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
	
	if(whichDomainToAssign == 'A' || whichDomainToAssign == 'B') {
		assignDomainStructs(whichDomainToAssign);
	}
// 	if(domain_A_struct) {
// 		assignDomainStructs('A');
// 	}
// 	else if(domain_B_struct) { 
// 		assignDomainStructs('B');		
// 	}
	else { // no structural oocupancy
		for(int i = 1; i <= sizeOfResidueArray; i++)
		{
			res[i].position.x = i - 1;
			res[i].position.y = sizeOfResidueArray/2;
		}
		for(i = 1; i <= sizeOfResidueArray; i++)
			occupyPosition(i);
	}
// 	cout<<"Got here!!"<<endl;
// 	cout<<"Got here!"<<endl;
// 	updateEnergiesByDomains();
	return 0;

}

int multiTempDoubleDomain::assignDomainStructs(char whichDomain) {
	cout<<"multiTempDoubleDomain::assignDomainStructs: "<<whichDomain<<endl;
	for(int y = 0; y < top_y; y++)
		for(int x = 0; x < right_x; x++)
			boolMatrix[y][x] &= 0;
 	cout<<"boolmat: "<<top_y<<", "<<right_x<<", "<<buttom_y<<", "<<left_x<<endl;
	point centerp(sizeOfResidueArray, sizeOfResidueArray);
// 	cout<<"continue:"<<endl;		
	if(whichDomain == 'A') {
		cout<<"doing domain A:\n";
		for(int i = fromto[0], j = 1; i <= fromto[1]; i++, j++) {
			res[i].position = domain_A_struct[j] + centerp;
			occupyPosition(i);
		}
// 		cout<<"struct before recursive build:\n";
// 		CfileHdlr.writeStructure2output(sizeOfResidueArray, this);
		if(recursiveOccupyPositions(fromto[1] + 1, fromto[3], res[fromto[1]].position)) {
			cout<<"struct after recursive build:\n";
			CfileHdlr.writeStructure2output(sizeOfResidueArray, this);
		} 
		else {
			cout<<"ERROR - Could not recursive build struct !!!!"<<endl;
			exit(1);
		}
	}
	else if(whichDomain == 'B') {
		cout<<"doing domain B:\n";
		for(int i = fromto[2], j = 1; i <= fromto[3]; i++, j++) {
			res[i].position = domain_B_struct[j] + centerp;
			occupyPosition(i);
		}
// 		exit(0);
// 		cout<<"struct before recursive build:\n";
// 		CfileHdlr.writeStructure2output(fromto[3]-fromto[2] +1, this);
// 		cout<<endl;
		if(reverseRecursiveOccupyPositions(fromto[0], fromto[2] - 1, res[fromto[2]].position)) {
			cout<<"struct after recursive build:\n";
			CfileHdlr.writeStructure2output(sizeOfResidueArray, this);
		}
	}
	else {
		cout<<"multiTempDoubleDomain::assignDomainStructs - ERROR. no such domain:"<<whichDomain<<endl;
		return 0;
	}
	return 1;	
}

bool multiTempDoubleDomain::recursiveOccupyPositions(int from, int to, point p) {
	if(from > to) {
		return 1;
	}
	//right
	if(occupyAndAssignIfVacant(++p.x, p.y, from) && recursiveOccupyPositions(from + 1, to, p)) {
		return 1;	
	}
	//up
	else if(dismissPositionIfRelevant(p, from) && occupyAndAssignIfVacant(--p.x, ++p.y, from) && recursiveOccupyPositions(from + 1, to, p)) {
		return 1;	
	}
	//left
	else if(dismissPositionIfRelevant(p, from) && occupyAndAssignIfVacant(--p.x, --p.y, from) && recursiveOccupyPositions(from + 1, to, p)) {
		return 1;	
	}
	//down
	else if(dismissPositionIfRelevant(p, from) && occupyAndAssignIfVacant(++p.x, --p.y, from) && recursiveOccupyPositions(from + 1, to, p)) {
		return 1;	
	}
	else {	
		return 0;
	}
}

bool multiTempDoubleDomain::reverseRecursiveOccupyPositions(int from, int to, point p) {
// 	cout<<"rev: "<<from<<" "<<to<<", ";
	if(to < from) {
		return 1;
	}
	
	//right
	if(occupyAndAssignIfVacant(++p.x, p.y, to) && reverseRecursiveOccupyPositions(from, to - 1, p)) {
		return 1;	
	}
	//up
	else if(dismissPositionIfRelevant(p, to) && occupyAndAssignIfVacant(--p.x, ++p.y, to) && reverseRecursiveOccupyPositions(from, to - 1, p)) {
		return 1;	
	}
	//left
	else if(dismissPositionIfRelevant(p, to) && occupyAndAssignIfVacant(--p.x, --p.y, to) && reverseRecursiveOccupyPositions(from, to - 1, p)) {
		return 1;	
	}
	//down
	else if(dismissPositionIfRelevant(p, to) && occupyAndAssignIfVacant(++p.x, --p.y, to) && reverseRecursiveOccupyPositions(from, to - 1, p)) {
		return 1;	
	}
	else {	
		return 0;
	}
}

int multiTempDoubleDomain::modifyBestFoldingArray() {
	double A_energy[2], B_energy[2], D_energy[2];
// 		cout<<"1 Got here!!!"<<endl;
	calculateMonomersEnergy('A', A_energy);
	calculateMonomersEnergy('B', B_energy);
	calculateMonomersEnergy('D', D_energy);
// 		cout<<"2 Got here!!!"<<endl;
	if(BFA[1]->energy > A_energy[1]) {
		BFA[1]->energy = A_energy[1];
// 		cout<<"Hi! 1"<<endl;
		BFA[1]->stepNumber = enteringMCAnneal;
		if(domainInFocus == 1)
			domainInFocusMCS = domainInFocusItr;
			
		for(int i = 1; i <= sizeOfResidueArray; i++)
			BFA[1]->res[i] = res[i];
	}
	
	if(BFA[2]->energy > B_energy[1]) {
// 		cout<<"Hi! 2"<<endl;
		BFA[2]->energy = B_energy[1];
		BFA[2]->stepNumber = enteringMCAnneal;
		if(domainInFocus == 2)
			domainInFocusMCS = domainInFocusItr;
			
		for(int i = 1; i <= sizeOfResidueArray; i++)
			BFA[2]->res[i] = res[i];
	}
	
	if(BFA[0]->energy > D_energy[1]) {
// 		cout<<"Hi! 3"<<endl;
		BFA[0]->energy = D_energy[1];
		BFA[0]->stepNumber = enteringMCAnneal;
		if(domainInFocus == 3)
			domainInFocusMCS = domainInFocusItr;
// 		CfileHdlr.writeStructure2output(sizeOfResidueArray, (residueArray*)res);
		for(int i = 1; i <= sizeOfResidueArray; i++) {
			BFA[0]->res[i] = res[i];
// 			cout<<res[i].position<<endl;
		}
	}
	return 0;
}








