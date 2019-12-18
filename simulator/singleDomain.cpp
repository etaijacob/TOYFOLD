

int singleDomain::freeFold(double times, 
													 int numOfSimulations, 
													 char *hp)
{
	initFoldingComplex();
	
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"ERROR - mem alloc \n";
		exit(1);
	}
	
	for(int i = 1; i <= sizeOfResidueArray; i++)
	{
		switch(hp[i-1])
		{
			case 'H':
				(res)[i].mode = HYDROPHOBIC; break;
 			case 'P':
				(res)[i].mode = POLAR_NEUTRAL; break;
 			case '+':
				(res)[i].mode = POSITIVE_CHARGE; break;
			case '-':
				(res)[i].mode = NEGATIVE_CHARGE; break;
		}		
	}
		
	cout<<"Begin folding:"<<endl;
	
	char fostr[1024];
	cout<<times<<" "<<configfileIndex<<endl;
	sprintf(fostr, "%sfc-itr%d-%s.data", outputDatafileName, (int)times, hp);
	cout<<fostr<<endl;
	ofstream of(fostr); 
	for(int m = 0; m < numOfSimulations; m++)
	{
		initFoldingComplex();
		
		double itr = 0, alpha_itr = 0;
		
		for(int i = 0; i < times; i++)
		{

			itr++;
			alpha_itr++;
			
			foldOnce();
			if(alpha_itr == ALPHA_ITR)
			{
				alpha_itr = 0;
			
				if(Ck < ALPHA_LOWER_BOND)
					Ck = ALPHA_LOWER_BOND;
				else
					Ck *= ALPHA;	
			}		
		}
		
		for(int pp = 0; pp <= sizeOfResidueArray; pp++) 
			structure[pp] = bestFoldingArray.res[pp].position;
		CfileHdlr.writeStructure2file(sizeOfResidueArray, structure, hp, of);
		of<<"Energy: "<<bestFoldingArray.energy<<" ,Step number: "<<bestFoldingArray.stepNumber<<endl;
	}
	
	of.close();
	delete []structure;
	cout<<"finish configfileIndex: "<<hp<<endl;
	return 1;
}