//seqPermutation.cpp

#include "seqPermutation.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

 /* (0 = H, 1 = P(neutral), 2 = +, 3 -) */
/* Data from swissProt 1.2.05 */ 


double seqPermutation::alphabetStatistics[4] = {
50,//skBB 50, skBB2 30
//66,
//6.71+1.15+4.84+4+2.37+9.62+5.91+6.93+1.56+7.81,
/* H
Neutral, Non-polar:	50.9
-------------------
Valine, Val			6.71
Tryptophan, trp ~	1.15
Proline, pro		4.84
Phenylalanine, phe	4.00
Methionine, met		2.37
Leucine, leu		9.62
Isoleucine, ile		5.91
Glycine, gly		6.93
Cysteine, cys ~		1.56
Alanine, ala		7.81
*/
30, //skBB 30, skBB2 50
//34,
//3.07+5.45+6.88+3.94+4.2,
/* P
Neutral, Polar:		23.54
---------------
Tyrosine, tyr		3.07  
Threonine, thr		5.45
Serine, ser			6.88
Glutamine, gln		3.94
Asparagine, asn		4.20
*/


10,
//5.93+2.28+5.32,
/* +
Basic, Polar:		13.53
-------------
Lysine, lys			5.93
Histidine, his		2.28
Arginine, arg		5.32
*/
10};
//6.61+5.3};
/* -
Acidic, Polar:		11.91
--------------
Glutamic Acid, glu	6.61
Aspartic Acid, asp	5.3

*/

	
ostream& operator<<(ostream &out, seqPermutation p)
{
	
	for(int i = 0; i < p.size; i++)
		switch(p.array[i])
		{
			case 0: out<<"H"; break;
			case 1: out<<"P"; break;
			case 2: out<<"+"; break;
			case 3: out<<"-"; break;
			default: out<<"ERROR"; break;
		}

	return out;
}

	
seqPermutation::seqPermutation(seqPermutation& sp)
{
	seqPermutation(sp.size);
	for(int i = 0; i < size; i++)
		array[i] = sp.array[i];
}
	
seqPermutation& seqPermutation::operator=(const seqPermutation& sp)
{
   	seqPermutation(sp.size);
	for(int i = 0; i < size; i++)
		array[i] = sp.array[i];
    return *this;
}
			
seqPermutation::seqPermutation(int length):RNG()
{
	array = new int[length];
	if(!array)
	{
		cout<<"ERROR alloc mem seqPermutation\n";
		exit(1);
	}
	
	size = length;
	for(int i = 0; i < size; i++)
		array[i] = -1;
	
	positionArr = new int[size];
	secondArr = new int[size];
	if((!positionArr)||(!secondArr))
	{
		cout<<"ERROR mem alloc - seqPermutation\n";
		exit(1);
	}
	
	int sum = 0;
	
	for(int i = 0; i < 4; i++)
	{
		alphabet[i] = (int)((alphabetStatistics[i]*(double)size)/100.0);
		sum += 	alphabet[i]; 
		//cout<<alphabet[i]<<", ";
	}
	int m = 1;
	int l = 0;
	while((size - sum) > 0)
	{
		if(m%8 == 0)
		{
			sum++;
			
			if(l%2 == 0)
				alphabet[2]++;
			else
				alphabet[3]++;
			l++;
		}
		else if(m%4 == 0)
		{
			sum++;
			alphabet[1]++;
		}
		else if(m%2 == 0)
		{
			sum++;
			alphabet[0]++;
		}
		m++;
	}

	//cout<<endl;
	int sum2 = 0;
	for(int i = 0; i < 4; i++)
	{
		//cout<<alphabet[i]<<", ";
		sum2 += alphabet[i];
	}
	//cout<<" = "<<sum2;
	cout<<endl;
	
}		

seqPermutation::~seqPermutation()
{
	//cout<<"~seqPermutation()"<<endl;
	if(array)
		delete []array;
	if(positionArr)
		delete []positionArr;
	if(secondArr)
		delete []secondArr;
}

int seqPermutation::generateAll()
{
	counter = 0;
	for(int i = 0; i < 4; i++)
		tmp_alphabet[i] = alphabet[i];
	
	permutate(size);
	
	return 1;
}


void seqPermutation::permutate(int length)
{	
	if(length == 0)
	{
		//cout<<this<<endl;
		cout<<"["<<size<<"]";
		for(int i = 0; i < size; i++)
		switch(array[i])
		{
			case 0: cout<<"H"; break;
			case 1: cout<<"P"; break;
			case 2: cout<<"+"; break;
			case 3: cout<<"-"; break;
			default: cout<<"ERROR"; break;
		}
		cout<<endl;
		counter++;
		return;
	}
	
	for(int i = 0; i < 4; i++)
	{
		if(tmp_alphabet[i] > 0)
		{
			array[length - 1] = i;
			tmp_alphabet[i]--;

			permutate(length - 1);
			
			tmp_alphabet[i]++;
		}
	}
}
	
#if 0
int seqPermutation::shuffle()
{
	int randNumber, randomPosition;
	
	int randArr[4] = {0, 1, 2, 3};
	
	
	
	for(int i = 0; i < size; i++)
		positionArr[i] = i;
	int maxPositions = size - 1;
	
	for(int i = 0; i < 4; i++)
		tmp_alphabet[i] = alphabet[i];
	

	int max = 3;

		
	while(maxPositions >= 0)
	{
		randNumber = RNG.generateNumberInRange(0, max);
		randomPosition = RNG.generateNumberInRange(0, maxPositions);
		
		
		if(tmp_alphabet[randArr[randNumber]] > 0)
		{
			tmp_alphabet[randArr[randNumber]]--;
			array[positionArr[randomPosition]] = randArr[randNumber];
			positionArr[randomPosition] = positionArr[maxPositions];
			maxPositions--;		
		}
		else
		{
			//move max instead of the consumed one:
			if(randNumber < max)
				randArr[randNumber] = randArr[max];
			max--;
		}
			
	}
		
		
	cout<<*this<<endl;
			
	return 1;
}	

#endif

int seqPermutation::shuffle()
{
	int randomPosition;
	
	for(int i = 0; i < size; i++)
		positionArr[i] = i;
	
	int maxPositions = size - 1;
	
	int m = 0;
	
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < alphabet[i]; j++)
		{
			secondArr[m] = i;
			m++;
		}
		
	while(maxPositions >= 0)
	{
		randomPosition = RNG.generateNumberInRange(0, maxPositions);
		
		array[positionArr[randomPosition]] = secondArr[maxPositions];
		
		positionArr[randomPosition] = positionArr[maxPositions];
		maxPositions--;		
	}
			
	
#if 1
	cout<<"["<<size + 2<<"]+";
		
	for(int i = 0; i < size; i++)
		switch(array[i])
		{
			case 0: cout<<"H"; break;
			case 1: cout<<"P"; break;
			case 2: cout<<"+"; break;
			case 3: cout<<"-"; break;
			default: cout<<"ERROR"; break;
		}
	cout<<"-"<<endl;		
#endif
	
	return 1;
}	

#if 1
int main(int argc, char** argv)
{
	if(argc < 7)
	{
		cout<<"seqLength times %H P + -"<<endl;
		exit(0);
	}
	
	double sum = 0;
	seqPermutation::alphabetStatistics[0] = atoi(argv[3]);
	seqPermutation::alphabetStatistics[1] = atoi(argv[4]);
	seqPermutation::alphabetStatistics[2] = atoi(argv[5]);
	seqPermutation::alphabetStatistics[3] = atoi(argv[6]);
	for(int i = 0; i < 4; i++) 
	{
		cout<<seqPermutation::alphabetStatistics[i]<<endl;
		sum += seqPermutation::alphabetStatistics[i];
	}
	cout<<"----\n"<<sum<<endl;
	
	int len = atoi(argv[1]);
	seqPermutation sp(len);
	
	for(int i = 0; i < atoi(argv[2]); i++)
		sp.shuffle();
	//sp.generateAll();	
	cout<<endl;
	//sp.generateAll();	
	//cout<<"Counter: "<<sp.counter<<endl;
}
#endif
