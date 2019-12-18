
#include "residue.h"
#include <stdlib.h>
#include <iostream>

using namespace std;
		
basicResidueArray::basicResidueArray(int length)
{
	
	sizeOfResidueArray = length;
	
	res = new residue[sizeOfResidueArray + 1];
	if(!res)
	{
		cout<<"ERROR - mem alloc residue array\n";
		exit(1);
	}
	
	left_x = 0;
	right_x = sizeOfResidueArray*2 + BOX_SPACE;
	buttom_y = 0;
	top_y = sizeOfResidueArray*2 + BOX_SPACE;
	
#if 1
	for(int i = 1, j = 0, m = 1; i <= sizeOfResidueArray/2; i++, j++, m+=2)
	{
		res[m].position.x = i - 1;
		res[m].position.y = sizeOfResidueArray/2 + j;
		res[m+1].position.x = i;
		res[m+1].position.y = sizeOfResidueArray/2 + j;
	}
#endif
#if 0
	/*REGULAR:*/
	//cout<<"ctor ---- basicResidueArray\n";
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		res[i].position.x = i - 1;
		res[i].position.y = sizeOfResidueArray/2;
		res[i].mode = i%4;
	}
#endif
	
}

basicResidueArray::~basicResidueArray()
{
	//cout<<"enter basic res Array DTOR\n.";
	if(res)
	{
		delete []res;	
		res = 0;
	}
	//cout<<"basicResidueArray dtor"<<endl;
}
	


//can have four different outputs
point basicResidueArray::getDirection(int index1, int index2)
{
	
	point p;

	p.x = res[index2].position.x - res[index1].position.x;
	p.y = res[index2].position.y - res[index1].position.y;
	
	return p;
}

//application functions: 

//modifies only the edge = tail of the array
int basicResidueArray::tailRotateRight(int pivot)
{
	point newp;
	
	/*
	 x =  y -dy+dx
	 y = -x +dx+dy

	*/

		
	//Right end:
	if(pivot > 0)
	{
		newp.x = res[sizeOfResidueArray].position.y - 
			 res[sizeOfResidueArray - 1].position.y + 
			 res[sizeOfResidueArray - 1].position.x;
		
		newp.y = - res[sizeOfResidueArray].position.x +
			 res[sizeOfResidueArray - 1].position.x +
			 res[sizeOfResidueArray - 1].position.y;
			 

		
		res[sizeOfResidueArray].position = newp;
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
		
		
		res[1].position = newp;
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
	}
	return 1;
}
int basicResidueArray::tailRotateLeft(int pivot)
{
	// x = -y + dx + dy
	// y =  x - dx + dy
	
	point newp;
		
	//Right end:
	if(pivot > 0)
	{
	
		newp.x = res[sizeOfResidueArray - 1].position.x +
			 res[sizeOfResidueArray - 1].position.y -
			 res[sizeOfResidueArray].position.y;
		
		newp.y = res[sizeOfResidueArray].position.x -
			 res[sizeOfResidueArray - 1].position.x +
			 res[sizeOfResidueArray - 1].position.y;
			 

		
		res[sizeOfResidueArray].position = newp;
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
			 
		res[1].position = newp;
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
	}
	return 1;
}
int basicResidueArray::tailRotate180(int pivot)
{
	point newp;
		
	//Right end:
	if(pivot > 0)
	{
		newp.x = - res[sizeOfResidueArray].position.x + 2*res[sizeOfResidueArray - 1].position.x;
		newp.y = - res[sizeOfResidueArray].position.y + 2*res[sizeOfResidueArray - 1].position.y;
		
		
		res[sizeOfResidueArray - 1].position = newp;
	}
	//Left end:
	else
	{
		newp.x = - res[1].position.x + 2*res[2].position.x;
		newp.y = - res[1].position.y + 2*res[2].position.y;
		
		
		res[1].position = newp;
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
	}
	return 1;
}
	
//rotate from the residue after the pivot until the edge
//input pivot must be smaller than sizeOfResidueArray
int basicResidueArray::fixedRotateRight(int pivot)
{
	point newp;

	for(int i = pivot + 1; i <= sizeOfResidueArray; i++)
	{	
		newp.x = res[i].position.y - 
			 res[pivot].position.y + 
			 res[pivot].position.x;
		
		newp.y = - res[i].position.x +
			 res[pivot].position.x +
			 res[pivot].position.y;
			 
		
		res[i].position = newp;
	}
	return 1;
}
int basicResidueArray::fixedRotateLeft(int pivot)
{
	point newp;

	for(int i = pivot + 1; i <= sizeOfResidueArray; i++)
	{	
		newp.x = res[pivot].position.x + 
			 res[pivot].position.y - 
			 res[i].position.y;
		
		newp.y = res[i].position.x -
			 res[pivot].position.x +
			 res[pivot].position.y;
			
		res[i].position = newp;
	}
	return 1;
}
int basicResidueArray::fixedRotate180(int pivot)
{
	point newp;

	for(int i = pivot + 1; i <= sizeOfResidueArray; i++)
	{
		newp.x = - res[i].position.x + 2*res[pivot].position.x;
		newp.y = - res[i].position.y + 2*res[pivot].position.y;
		
		
		res[i].position = newp;
		//cout<<"\npoint: ("<<newp.x<<", "<<newp.y<<")\n";
		
	}
	return 1;
}
		
//pivot must not be a tail
int basicResidueArray::flipflopCorner(int pivot)	//cannot be a tail or a strait line, must be a corner
{
	//cout<<"Start flipflop\n";
	//check if pivot is a corner:
	point arr[3]; 
	arr[0] = getDirection(pivot, pivot - 1);

	arr[2] = getDirection(pivot, pivot + 1);
	
	if(arr[0].abs() == arr[2].abs())
		return 0;//not a corner

	arr[0] = res[pivot - 1].position;	
	arr[1] = res[pivot].position;
	arr[2] = res[pivot + 1].position;
	
	//Get the smallest of the three points:
	point dp;
	
	int smallest;
	
	if(arr[0].x<arr[1].x)
	{
		if(arr[0].x<arr[2].x)
		//arr[0]<arr[2]<arr[1]
			smallest = 0;
		else
		//arr[2]<arr[0]<arr[1]
			smallest = 2;
	}
	else//arr[1]<arr[0]
	{
		if(arr[1].x<arr[2].x)
			smallest = 1;
		else//arr[2]<arr[1]<arr[0]
			smallest = 2;
	}
	dp.x = arr[smallest].x;
	
	if(arr[0].y<arr[1].y)
	{
		if(arr[0].y<arr[2].y)
		//arr[0]<arr[2]<arr[1]
			smallest = 0;
		else
		//arr[2]<arr[0]<arr[1]
			smallest = 2;
	}
	else//arr[1]<arr[0]
	{
		if(arr[1].y<arr[2].y)
			smallest = 1;
		else//arr[2]<arr[1]<arr[0]
			smallest = 2;
	}
	dp.y = arr[smallest].y;
	
	
	arr[1] -= dp;
	
	point x(1,1);
	
	arr[1] ^= x;
	arr[1] += dp;
	res[pivot].position = arr[1];	 
	return 1;
}

int basicResidueArray::nonEdgeSegmentFold(int pivot, int segmentLen)
{
	return 1;
}

//User functions:

int basicResidueArray::printProtein()
{
	int** printArr;
	printArr = new int*[top_y + sizeOfResidueArray];
	if(!printArr)
	{
		cout<<"ERROR mem alloc - basicResidueArray print protein\n";
		exit(1);
	}

	for(int i = 0; i <= top_y + sizeOfResidueArray; i++)
	{
		printArr[i] = new int[2*sizeOfResidueArray];
		if(!printArr[i])
		{
			cout<<"ERROR mem alloc - basicResidueArray print protein\n";
			exit(1);
		}
	}
	

	int i, j, m;
	for(i = 0; i < top_y+sizeOfResidueArray; i++)
		for(m = 0; m < 2*sizeOfResidueArray; m++)	
			printArr[i][m] = -1;
	
	for(i = 1; i <= sizeOfResidueArray; i++)	
		printArr[res[i].position.y+sizeOfResidueArray][res[i].position.x+sizeOfResidueArray]
		= res[i].mode;
	
	
	for(j = top_y +sizeOfResidueArray- 1; j >= 0; j--)
	{
		for(m = 0; m < 2*sizeOfResidueArray; m++)	
		{
			if(printArr[j][m] == -1)
				cout<<" ";
			else
			{	
				switch(printArr[j][m])
				{
					case HYDROPHOBIC:
						cout<<"H"; break;
 					case POLAR_NEUTRAL:
						cout<<"P"; break;
 					case POSITIVE_CHARGE:
						cout<<"+"; break;	
					case NEGATIVE_CHARGE:
						cout<<"-"; break;
				}
				
			}
		}
		cout<<endl;
	}
	
	
		
	return 1;
}


//-----------------------------------------------------------------------------------------------

//write
residueArray::residueArray(int length, char *name):basicResidueArray(length)
{
	strcpy(fileName, name);
	fileMode = 'w';
	numberOfStructures = 0;
	
	fs = fopen(name, "wb");
	if(!fs)
	{
		cout<<"Error io - failbit - open r/w file\n";
		exit(0);
	}
	
	fwrite(&sizeOfResidueArray, sizeof(int), 1, fs);
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		fwrite(&(res[i].mode), sizeof(int), 1, fs);
		cout<<res[i].mode;
	}
	
	//Place for the numberOfStructures:
	fseek(fs, sizeof(double), SEEK_CUR);
	//cout<<"ctor residueArray"<<endl;
	


}
void residueArray::new_residueArray(int size)
{
	sizeOfResidueArray = size;
	
	res = new residue[sizeOfResidueArray + 1];
	if(!res)
	{
		cout<<"ERROR - mem alloc residue array\n";
		exit(1);
	}
	
	left_x = 0;
	right_x = sizeOfResidueArray*2 + BOX_SPACE;
	buttom_y = 0;
	top_y = sizeOfResidueArray*2 + BOX_SPACE;
}

//associates with read	
residueArray::residueArray(char *name)
{
	sizeOfResidueArray = 0;
	numberOfStructures = 0;
	strcpy(fileName, name);
	fileMode = 'r';
	
	fs = fopen(name, "rb"); 
	
	if(!fs)
	{
		cout<<"Error io - failbit - open r/w file\n";
		exit(0);
	}
	
	fread(&sizeOfResidueArray, sizeof(int), 1, fs);
	//cout<<"sizeOfResidueArray: "<<sizeOfResidueArray<<endl;
	
	if( (sizeOfResidueArray <= 0) || (sizeOfResidueArray > 10000) )
	{
		cout<<"Error input file: "<<name<<endl;
		exit(0);
	}
	
	
	res = new residue[sizeOfResidueArray + 1];
	if(!res)
	{
		cout<<"ERROR - mem alloc residue array\n";
		exit(1);
	}
	
	left_x = 0;
	right_x = sizeOfResidueArray*2 + BOX_SPACE;
	buttom_y = 0;
	top_y = sizeOfResidueArray*2 + BOX_SPACE;
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		//res[i].mode = 0;
		fread(&(res[i].mode), sizeof(int), 1, fs);
		//cout<<res[i].mode;
	}
	fread(&numberOfStructures, sizeof(double), 1, fs);
	//cout<<"numberOfStructures: "<<numberOfStructures<<endl;

}

int residueArray::read()
{
	if(numberOfStructures)
	{
		for(int i = 1; i <= sizeOfResidueArray; i++)
		{
			
			if(fread(&res[i].position.x, sizeof(int), 1, fs) != 1)
				return 0;
			if(fread(&res[i].position.y, sizeof(int), 1, fs) != 1)
				return 0;
			//cout<<res[i].position;
			
		}
		--numberOfStructures;
		return 1;
	}
	else
		return 0;
		
}

int residueArray::write()
{
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{	
		if(fwrite(&res[i].position.x, sizeof(int), 1, fs) != 1)
			return 0;
		if(fwrite(&res[i].position.y, sizeof(int), 1, fs) != 1)
			return 0;
		//cout<<res[i].position;
	}
	++numberOfStructures;
	return 1;
}

residueArray::residueArray(int length):basicResidueArray(length)
{
	fileMode = 0;
}

residueArray::~residueArray()
{
	if(fileMode == 'r')
		fclose(fs);
	else if(fileMode == 'w')
	{
		fseek(fs, sizeof(int) + sizeof(int)*sizeOfResidueArray, SEEK_SET);
		if(fwrite(&numberOfStructures, sizeof(double), 1, fs) != 1)
		{
			cout<<"ERROR - WRITING FILE .EXIT PROG. ~residueArray()\n";
			exit(0);
		}
		fclose(fs);
	}
	//cout<<"enter res Array DTOR\n.";
	if(res)
	{
		delete []res;
		res = 0;
	}
	//cout<<"~residueArray"<<endl;	
}

residueArray& residueArray::operator=(const residueArray& rightside)
{
    if(sizeOfResidueArray != rightside.sizeOfResidueArray)
	{
		cout<<"Enter residueArray = Size doesn't match\n";
		delete []res;
		sizeOfResidueArray = rightside.sizeOfResidueArray;
		res = new residue[sizeOfResidueArray + 1];
		if(!res)
		{
			cout<<"ERROR - mem alloc residue array\n";
			exit(1);
		}
	
		left_x = 0;
		right_x = sizeOfResidueArray*2 + BOX_SPACE;
		buttom_y = 0;
		top_y = sizeOfResidueArray*2 + BOX_SPACE;
	}
	
	//cout<<"ResidueArray =\n";
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		res[i].position.x = rightside.res[i].position.x;
		res[i].position.y = rightside.res[i].position.y;
		res[i].mode = rightside.res[i].mode;
	}
	 	
	return *this;
}

residueArray& residueArray::operator=(const point* rightside)
{
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		res[i].position.x = rightside[i-1].x;
		res[i].position.y = rightside[i-1].y;
	}
	return *this;
}

residueArray& residueArray::operator=(const int* rightside)
{
	for(int i = 1; i <= sizeOfResidueArray; i++)
		res[i].mode = rightside[i-1];
	
	return *this;
}

void residueArray::print()
{
	int** matrix = new int*[top_y];
	if(!matrix)
	{
		cout<<"Error = mem alloc foldingComplex\n";
		exit(1);
	}
	for(int i = 0; i < top_y; i++)
		if(!(matrix[i] = new int[right_x]) )
		{
			cout<<"Error = mem alloc foldingComplex\n";
			exit(1);
		}
		
			
		
	
	int i, y, x;
	
	for(y = 0; y < top_y; y++)
		for(x = 0; x < right_x; x++)
			matrix[y][x] = 0;
			
	for(i = 1; i <= sizeOfResidueArray; i++)
		matrix[res[i].position.y][res[i].position.x] = i;
		
	for(y = top_y - 1; y >= 0; y--)
	{
		for(x = 0; x < right_x; x++)
		{
			if(!matrix[y][x])
				cout<<" ";
			else
			{
				char sgn;
				switch(res[matrix[y][x]].mode)
				{
					case HYDROPHOBIC:
						sgn = 'H'; break;
 					case POLAR_NEUTRAL:
						sgn = 'P'; break;
 					case POSITIVE_CHARGE:
						sgn = '+'; break;	
					case NEGATIVE_CHARGE:
						sgn = '-'; break;
				}
				
				if(matrix[y][x] > 9)
					cout<<sgn;//<<matrix[y][x];
				else 
					cout<<sgn;//<<matrix[y][x]<<" ";
			}
		}
		cout<<endl;
	}

	for(int i = 0; i < top_y; i++)
		delete []matrix[i];
	delete []matrix;
}

point residueArray::getMax_XY()
{
	point out;
	out.x = left_x;
	out.y = buttom_y;
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		if(out.x < res[i].position.x)
			out.x = res[i].position.x;
		if(out.y < res[i].position.y)
			out.y = res[i].position.y;
	}

	return out;
}	

point residueArray::getMin_XY()
{
	point out;
	out.x = right_x;
	out.y = top_y;
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		if(out.x > res[i].position.x)
			out.x = res[i].position.x;
		if(out.y > res[i].position.y)
			out.y = res[i].position.y;
	}

	return out;
}	

	
		
#if 0
int main(int argc, char** argv)
{
	cout<<"Writing structures:\n";
	
#if 0
	residueArray resArr(4, "myFirstResArrFile");
	int len = atoi(argv[1]);
	
	for(int i = 0; i < len; i++)
		resArr.write();
#endif
	//cout<<"output: "<<endl;
#if 1
	residueArray resArr("myFirstResArrFile");
	cout<<"resArr.numberOfStructures :"<<resArr.numberOfStructures;
	while(resArr.numberOfStructures)
	{
		//cout<<endl;
		resArr.read();
	}
#endif
	cout<<endl;
	return 0;
}

#endif
