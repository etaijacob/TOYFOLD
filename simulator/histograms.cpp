//histograms.cpp

#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/dir.h>
#include <libgen.h>
#include <fstream.h>
#include <ctype.h>
#include "utilities.h"
#include "configFileHandler.h"

#define NOT_REFERENCED	9999999

double computeChapClusters4dir(char* dirname, char* substr, 
		int segmentWidth, int iterations, double tres, char axe, 
		int sizeOfResidueArray, char *refDir, 
		char *refSubstr, int maxFolded);


int grabl(int argc, char **argv);

double grabLines4dir(char* dirname, char* substrIn, double fromTemp, 
						double toTemp, int colmnIdx, int lineIdx, double itr,
						double thresh);
						
double grabFile2Line(char *sname, int colmnIdx, int lineIdx);

double computeAverageLines4dir(char* dirname, char* substr, 
int ColmnSize, int seqSize, int colmnIdx);

int cald(int argc, char **argv);

int grabFile2Colmn(char *sname, int colmnIdx, int size, double *numbers);

int extractIndex(char *str);

double computeHistogram4dir(char* dirname, char* dname, char* substr, 
		int segmentWidth, int iterations, double tres, char axe,
		int sizeOfResidueArray, char *confFileName);

int countFile4Histogram(char *sname, int segmentWidth, int
		iterations, double tres, char axe, int *countAll);

int countFile4Histogram(char *sname, char *dname, int segmentWidth, 
		                int iterations, double tres, char axe = 'x');


double computeAverage4dir(char* dirname, char* substr, 
		int iterations, double tres, 
		int sizeOfResidueArray, char *confFileName);

int diff(char *n1, char *n2);//, char *conf);

int clust(int argc, char **argv);

int main(int argc, char** argv)
{
#if 1
	clust(argc, argv);
#endif
	
	
#if 0
	grabl(argc, argv);
#endif
	
#if 0
	cald(argc, argv);
#endif
#if 0
	if(argc < 3)
	{
		cout<<"n1 n2\n";// confFile\n";
		exit(0);
	}
	diff(argv[1], argv[2]);//, argv[3]);
#endif
	
#if 0
	if(argc < 7)
	{
		cout<<"usage: dirname substr iterations tres "\
			  "sizeOfResidueArray confFileName\n";
		exit(0);
	}

		
	char *dirname = argv[1];
	char *substr = argv[2];
	int iterations = atoi(argv[3]);
	double tres = strtod(argv[4], NULL);
	char *confFileName = argv[6];
	int sizeOfResidueArray = atoi(argv[5]);

	computeAverage4dir(dirname, substr, iterations, tres, 
					   sizeOfResidueArray, confFileName);
	
#endif
#if 0
	if(argc < 12)
	{
		cout<<"usage: dirname dname substr segmentWidth iterations tres axe"\
			  "sizeOfResidueArray confFileName fromTemp toTemp\n";
		exit(0);
	}
	
	char *dirname = argv[1];
	char *dname = argv[2];
	char *substr = argv[3];
	int segmentWidth = atoi(argv[4]);
	int iterations = atoi(argv[5]);
	double tres = strtod(argv[6], NULL);
	char axe = *argv[7];
	char *confFileName = argv[9];
	int sizeOfResidueArray = atoi(argv[8]);
	double fromTemp = strtod(argv[10], NULL);
	double toTemp = strtod(argv[11], NULL);
	
	char dstStr[120], tSubstr[120], dstYield[120];
	cout<<endl;
	//int i;
	//strcpy(dstYield, dname);
	//for(i = strlen(dstYield); i > 0 && dstYield[i] != '/'; i--);
	//dstYield[i + 1] = 0;
		
	sprintf(dstYield, "%s-yield-f%f-%f.data", dname, fromTemp, toTemp);
	cout<<dstYield<<endl;
	
	FILE * fpy = fopen(dstYield, "wb");
	if(!fpy)
	{
		cout<<"ERror file creaTION\n";
		exit(1);
	}
#if 0 //threshold interval:
	for(double t = fromTemp; t <= toTemp; t += 0.25)
	{
		sprintf(dstStr, "%s-t%f.his", dname, t);
		sprintf(tSubstr, "%s-t-%f", substr, t);
		double ret = computeHistogram4dir(dirname, dstStr, tSubstr, segmentWidth, 
							 iterations, tres, axe, sizeOfResidueArray, confFileName);
		
		//cout<<t<<" "<<ret<<endl;
		fprintf(fpy, "%f %f\n", t, ret);
	}
	fclose(fpy);
#endif	

#if 0//releaseInterval:
	for(int t = fromTemp; t <= toTemp; t += 20000)
	{
		sprintf(dstStr, "%s-r%d.his", dname, t);
		sprintf(tSubstr, "%s-r%d", substr, t);
		double ret = computeHistogram4dir(dirname, dstStr, tSubstr, segmentWidth, 
							 iterations, tres, axe, sizeOfResidueArray, confFileName);
		
		//cout<<t<<" "<<ret<<endl;
		fprintf(fpy, "%d %f\n", t, ret);
	}
	fclose(fpy);
#endif

#if 0//bindInterval:
	for(int t = fromTemp; t <= toTemp; t += 20000)
	{
		sprintf(dstStr, "%s-b%d.his", dname, t);
		sprintf(tSubstr, "%s-b%d", substr, t);
		double ret = computeHistogram4dir(dirname, dstStr, tSubstr, segmentWidth, 
							 iterations, tres, axe, sizeOfResidueArray, confFileName);
		
		//cout<<t<<" "<<ret<<endl;
		fprintf(fpy, "%d %f\n", t, ret);
	}
	fclose(fpy);
#endif
#if 0	//temperature:	
	for(double t = fromTemp; t <= toTemp; t += 0.05)
	{
		sprintf(dstStr, "%s-f%f.his", dname, t);
		sprintf(tSubstr, "%s-f%f", substr, t);
		double ret = computeHistogram4dir(dirname, dstStr, tSubstr, segmentWidth, 
							 iterations, tres, axe, sizeOfResidueArray, confFileName);
		
		//cout<<t<<" "<<ret<<endl;
		fprintf(fpy, "%f %f\n", t, ret);
	}
	fclose(fpy);
#endif
	return 0;
#endif

		
#if 0
	if(argc < 10)
	{
		cout<<"usage: dirname dname substr segmentWidth iterations tres axe"\
			  "sizeOfResidueArray confFileName\n";
		exit(0);
	}
	
	char *dirname = argv[1];
	char *dname = argv[2];
	char *substr = argv[3];
	int segmentWidth = atoi(argv[4]);
	int iterations = atoi(argv[5]);
	double tres = strtod(argv[6], NULL);
	char axe = *argv[7];
	char *confFileName = argv[9];
	int sizeOfResidueArray = atoi(argv[8]);
	
	
	computeHistogram4dir(dirname, dname, substr, segmentWidth, 
						 iterations, tres, axe, sizeOfResidueArray, confFileName);
	return 0;
#endif
}

int clust(int argc, char **argv)
{
	
	if(argc < 10)
	{
		cout<<\
		"char* dirname, char* substr,"\
		"int iterations, double tres, char axe,\n"\
		"int sizeOfResidueArray, char *refDir,"\
		"char *refSubstr, int maxFolded)\n";
		exit(0);
	}
	char* dirname = argv[1];
	char* substr  = argv[2]; 
	int segmentWidth  = 50000;
	int iterations = atoi(argv[3]);
	double tres = strtod(argv[4], NULL);
	char axe = *argv[5];
	int sizeOfResidueArray = atoi(argv[6]);
	char *refDir = argv[7];
	char *refSubstr = argv[8];
	int maxFolded = atoi(argv[9]);
	
	computeChapClusters4dir(dirname, substr, 
		segmentWidth, iterations, tres, axe, 
		sizeOfResidueArray, refDir, 
		refSubstr, maxFolded);
	return 1;
}



double computeFolded4dir(char* dirname, char* substr, 
		int segmentWidth, int iterations, double tres, char axe, 
		double *folded, int maxFolded)
{
	
    DIR* dirp = opendir(dirname);
    if (dirp == NULL) 
	{
    	return 0;
    }
     
	char str[200];
	
	//cout<<"Number of elements: "<<iterations/segmentWidth<<endl;
	int *countAll = new int[iterations/segmentWidth + 1];
	if(!countAll)
	{
		cout<<"ERROR mem alloc Histogram\n";
		exit(1);
	}
	
	for(int i = 0; i < iterations/segmentWidth + 1; i++)
		countAll[i] = 0;
		
	struct direct * dp;  
		  
	int fileCounter = 0;
			
	int n;
	
	while ((dp = readdir(dirp)) != NULL) 
	{
		
		if( strfind(dp->d_name, ".data") == (dp->d_namlen - 5) &&
			strfind(dp->d_name, substr) != -1 )
		{
			sprintf(str, "%s%s", dirname, dp->d_name);
			//cout<<"Doing file: "<<str<<endl;
			fileCounter++;
			
			int confIdx = extractIndex(dp->d_name);
			//cout<<"confIdx: "<<confIdx<<endl;			
				
			for(int i = 0; i <= iterations/segmentWidth; i++)
				countAll[i] = 0;
			
			n = countFile4Histogram(str, segmentWidth, iterations, tres, axe, countAll);
			int sumall = 0;
			for(int i = 0; i <= iterations/segmentWidth; i++)
			{
				//cout<<countAll[i]- tmp[i]<<"/"<<(n/2)<<endl;
				sumall += countAll[i];
			}
			
			if(confIdx < maxFolded)	
				folded[confIdx] = sumall/(double)n;
			else
			{
				cout<<"ERROR confIdx\n";
				exit(1);
			}
				
		}
		
    }
	
    closedir(dirp);
	
	
	delete []countAll;
	
	cout<<"Finished computeHistogram4dir\n";
    return 1.0;

}
double computeChapClusters4dir(char* dirname, char* substr, 
		int segmentWidth, int iterations, double tres, char axe, 
		int sizeOfResidueArray, char *refDir, 
		char *refSubstr, int maxFolded)
{
	double *refFolded = new double[maxFolded];
	double *folded = new double[maxFolded];
	if(!refFolded || !folded)
	{
		cout<<"ERROR mem alloc\n";
		exit(1);
	}
	for(int i = 0; i < maxFolded; i++)
		refFolded[i] = folded[i] = NOT_REFERENCED;
	
	computeFolded4dir(refDir, refSubstr, segmentWidth, iterations, 
					  tres, axe, refFolded, maxFolded);
	
	char tmpstr[200];
	for(int i = 0; i < 1; i++)
	{
		cout<<i<<": ";
		for(int j = 0; j < maxFolded; j++)
			folded[j] = NOT_REFERENCED;

		sprintf(tmpstr, "%s", substr);
		computeFolded4dir(dirname, tmpstr, segmentWidth, iterations, 
						  tres, axe, folded, maxFolded);
		for(int j = 0; j < maxFolded; j++)
			if(folded[j] != NOT_REFERENCED && refFolded[j] != NOT_REFERENCED)
				if( (folded[j] - refFolded[j]) > -110 )
					cout<<j<<" "<<folded[j]<<" "<<refFolded[j];
		cout<<endl;
	}
			
	

    return 1;

}	

double computeHistogram4dir(char* dirname, char* dname, char* substr, 
		int segmentWidth, int iterations, double tres, char axe, 
		int sizeOfResidueArray, char *confFileName)
{
	
    DIR* dirp = opendir(dirname);
    if (dirp == NULL) 
	{
    	return 0;
    }
     
	char str[200];
	
	//cout<<"Number of elements: "<<iterations/segmentWidth<<endl;
	int *countAll = new int[iterations/segmentWidth + 1];
	if(!countAll)
	{
		cout<<"ERROR mem alloc Histogram\n";
		exit(1);
	}
	
	for(int i = 0; i < iterations/segmentWidth + 1; i++)
		countAll[i] = 0;
		
	struct direct * dp;  
	
	FILE *dfp, *dfp2;//, *fpli1, *fpli2;
	
	dfp = fopen(dname, "wb");

	char tmpstr[100];
	sprintf(tmpstr, "%s2", dname);
	dfp2 = fopen(tmpstr, "wb");
	
	//sprintf(tmpstr, "%s_li-f", dname);
	//fpli1 = fopen(tmpstr, "wb");
	
	//sprintf(tmpstr, "%s_li-nf", dname);
	//fpli2 = fopen(tmpstr, "wb");

	if(!dfp || !dfp2)// || !fpli2 || !fpli1)
	{
		cout<<"ERROR CREATION FILE - computeHistogram4dir\n";
		exit(0);
	}
	  
	int fileCounter = 0;
	
	int *tmp = new int[iterations/segmentWidth + 1];
	int *totalFoldable = new int[iterations/segmentWidth + 1];
	if(!tmp || !totalFoldable)
	{
		cout<<"Error mem alloc\n";
		exit(1);
	}

	for(int i = 0; i <= iterations/segmentWidth; i++)
		totalFoldable[i] = 0;
		
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"Error mem alloc.\n";
		exit(1);
	}
	/*
	configFileHandler cfh(confFileName, sizeOfResidueArray);
	double *accFoldableLI = new double[iterations/segmentWidth + 1];
	double *accNonfoldableLI = new double[iterations/segmentWidth + 1];
	
	if(!accFoldableLI || !accNonfoldableLI)
	{
		cout<<"Error mem alloc\n";
		exit(1);
	}

	for(int i = 0; i <= iterations/segmentWidth; i++)
		accFoldableLI[i] = accNonfoldableLI[i] = 0;
	*/
	int n;
	
	while ((dp = readdir(dirp)) != NULL) 
	{
		
		if( strfind(dp->d_name, ".data") == (dp->d_namlen - 5) &&
			strfind(dp->d_name, substr) != -1 )
		{
			sprintf(str, "%s%s", dirname, dp->d_name);
			//cout<<"Doing file: "<<str<<endl;
			fileCounter++;
			
			int confIdx = extractIndex(dp->d_name);
			//cout<<"confIdx: "<<confIdx<<endl;
			//double li = 0;
			
			if(confIdx >= 0)
			{
				//char *hp = cfh.readTextStructure(sizeOfResidueArray, 
				//  						 structure, 
				//  						 confIdx);
				//li = getLocalityIndex(sizeOfResidueArray, structure, hp);
				//li = getStrongInteractionLocalityIndex(sizeOfResidueArray, structure, hp);
			}	
				
			for(int i = 0; i <= iterations/segmentWidth; i++)
				tmp[i] = countAll[i];
			
			n = countFile4Histogram(str, segmentWidth, iterations, tres, axe, countAll);
			//percent - successful folder
			//cout<<countAll[iterations/segmentWidth] - tmp<<endl;
			int sumall = 0;
			
			for(int i = 0; i <= iterations/segmentWidth; i++)
			{
				//cout<<countAll[i]- tmp[i]<<"/"<<(n/2)<<endl;
				sumall += (countAll[i] - tmp[i]);
				if( sumall > n>>1 ) //more then a half
				{
					totalFoldable[i]++;
					//accFoldableLI[i] += li;
					
				}
				//else
					//accNonfoldableLI[i] += li;
				if( (i == iterations/segmentWidth - 1) && sumall < n>>1)
						cout<<confIdx<<endl;	
			}
			

				
		}
		
    }
	
    closedir(dirp);
	
	int total = 0;
	for(int i = 0; i < iterations/segmentWidth + 1; i++)
		total += countAll[i];
	
	int sumall = 0;
	for(int i = 0; i < iterations/segmentWidth + 1; i++)
	{
		sumall += countAll[i];
		double frac = 100.0*(double)sumall/(double)total;
		fprintf(dfp, "%d %f\n", i*segmentWidth, frac);	
	}

	fclose(dfp);
	
	//cout<<"Total foldable: \n";
	for(int i = 0; i <= iterations/segmentWidth; i++)	
	{
		double frac = 100.0*(double)totalFoldable[i]/(double)fileCounter;
		fprintf(dfp2, "%d %f\n", i*segmentWidth, frac);
		/*
		if(totalFoldable[i] == 0)
			frac = 0;
		else
			frac = accFoldableLI[i]/(double)totalFoldable[i];

		fprintf(fpli1, "%d %f\n", i*segmentWidth, frac);
		
		if(fileCounter - totalFoldable[i] == 0)
			frac = 0;
		else
			frac = accNonfoldableLI[i]/(double)(fileCounter - totalFoldable[i]);
		
		fprintf(fpli2, "%d %f\n", i*segmentWidth, frac);
*/
	}
	double tmpRet = 
		100.0*(double)totalFoldable[iterations/segmentWidth - 1]/(double)fileCounter;
	
	fclose(dfp2);
	//fclose(fpli2);
	//fclose(fpli1);
	
	delete []countAll;
	delete []tmp;
	delete []totalFoldable;
	delete []structure;
	//delete []accNonfoldableLI;
	//delete []accFoldableLI;
	
	cout<<"Finished computeHistogram4dir\n";
    return tmpRet;

}	

int extractIndex(char *str)
{
	
	int p = strfind(str, "-25-");
	if(p == -1)
		return -1;
	
	int len = strlen(str);
	char tmp[100];
	int j = 0;
	
	for(int i = p + 4; i < len && isdigit(str[i]); i++, j++)
		tmp[j] = str[i];

	if(j == 0)
		return -1;
	
	tmp[j] = 0;
	return atoi(tmp);
}

		
	
int countFile4Histogram(char *sname, int segmentWidth, int
		iterations, double tres, char axe, int *countAll)
{
	FILE* fp = fopen(sname, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found countFile4Histogram\n";
		exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize < 10)
	{
		fclose(fp);
		return 0;
	}
	fseek(fp, 0, SEEK_SET);
	
	char buffer[1024];
	double accMean[2] = {0}, accVar[2] = {0};
	double numbers[2][1000];
	
	
			
	
	int i = 0, n = 0, state = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[i++] = ch;
		else if(ch == ' ')
		{
			buffer[i] = NULL;
			numbers[state][n] = strtod(buffer, NULL);
			accMean[state] += numbers[state][n]; 
			state = 1;
			i = 0;
			
		}
		else
		{
			buffer[i] = NULL;
			numbers[state][n] = strtod(buffer, NULL);
			if(numbers[state][n] > tres)
				numbers[0][n] = iterations ;	
			accMean[state] += numbers[state][n]; 
			n++;
			state = 0;
			i = 0;
		}
	}		
/*	
	double mean[2], var[2];
	mean[0] = accMean[0]/(double)n;
	mean[1] = accMean[1]/(double)n;
	
	for(i = 0; i < n; i++)
	{
		accVar[0] += pow(((double)numbers[0][i] - mean[0]), 2);
		accVar[1] += pow(((double)numbers[1][i] - mean[1]), 2);
	}
	
	var[0] = accVar[0]/(double)n;
	var[1] = accVar[1]/(double)n;
	*/
//	cout<<"[file name]"<<name<<endl;
//	cout<<"<"<<mean[0]<<" "<<var[0]<<">"<<"<"<<mean[1]<<" "<<var[1]<<">#"<<n<<"\n";

	//cout<<"Avg X: "<<mean[0]<<" Var X: "<< var[0]<<endl;
	
	//cout<<"Avg Y: "<<mean[1]<<" Var Y: "<< var[1]<<endl;
 	fclose(fp);

	//cout<<"Number of elements: "<<iterations/segmentWidth<<endl;
	int *xCount = new int[iterations/segmentWidth + 1];
	if(!xCount)
	{
		cout<<"ERROR mem alloc Histogram\n";
		exit(1);
	}
	
	int *yCount = new int[iterations/segmentWidth + 1];
	if(!yCount)
	{
		cout<<"ERROR mem alloc Histogram\n";
		exit(1);
	}


	for(i = 0; i <= iterations/segmentWidth; i++)
		xCount[i] = yCount[i] = 0;
		
	for(i = 0; i < n; i++)
	{
		int mod = 0;
		while( ((int)numbers[0][i])%(mod + 1) < (int)numbers[0][i] && mod <= iterations) mod += segmentWidth;
		if(mod <= iterations)
			xCount[mod/segmentWidth]++;
		
		mod = 0;
		while( ((int)numbers[1][i])%(mod + 1) < (int)numbers[0][i] && mod <= iterations) mod += segmentWidth;
		if(mod <= iterations)
			yCount[mod/segmentWidth]++;
		
	}
	

	
	for(i = 0; i <= iterations/segmentWidth; i++)
	{
		if(axe == 'x')			 
			countAll[i] += xCount[i];	
		else
			countAll[i] += yCount[i];		 
	}		
	
	
		
	delete []xCount;
	delete []yCount;

				
	return n;
		
}


int countFile4Histogram(char *sname, char *dname, int segmentWidth, 
						int iterations, double tres, char axe)
{
	FILE* fp = fopen(sname, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found countFile4Histogram 2\n";
		exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize < 10)
	{
		fclose(fp);
		return 0;
	}
	fseek(fp, 0, SEEK_SET);
	
	char buffer[1024];
	double accMean[2] = {0}, accVar[2] = {0};
	double numbers[2][1000];
	
	
			
	
	int i = 0, n = 0, state = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[i++] = ch;
		else if(ch == ' ')
		{
			buffer[i] = NULL;
			numbers[state][n] = strtod(buffer, NULL);
			accMean[state] += numbers[state][n]; 
			state = 1;
			i = 0;
			
		}
		else
		{
			buffer[i] = NULL;
			numbers[state][n] = strtod(buffer, NULL);
			if(numbers[state][n] > tres)
				numbers[0][n] = iterations ;	
			accMean[state] += numbers[state][n]; 
			n++;
			state = 0;
			i = 0;
		}
	}		
	
	double mean[2], var[2];
	mean[0] = accMean[0]/(double)n;
	mean[1] = accMean[1]/(double)n;
	
	for(i = 0; i < n; i++)
	{
		accVar[0] += pow(((double)numbers[0][i] - mean[0]), 2);
		accVar[1] += pow(((double)numbers[1][i] - mean[1]), 2);
	}
	
	var[0] = accVar[0]/(double)n;
	var[1] = accVar[1]/(double)n;
	
//	cout<<"[file name]"<<name<<endl;
//	cout<<"<"<<mean[0]<<" "<<var[0]<<">"<<"<"<<mean[1]<<" "<<var[1]<<">#"<<n<<"\n";

	//cout<<"Avg X: "<<mean[0]<<" Var X: "<< var[0]<<endl;
	
	//cout<<"Avg Y: "<<mean[1]<<" Var Y: "<< var[1]<<endl;
 	fclose(fp);

	//cout<<"Number of elements: "<<iterations/segmentWidth<<endl;
	int *xCount = new int[iterations/segmentWidth + 1];
	if(!xCount)
	{
		cout<<"ERROR mem alloc Histogram\n";
		exit(1);
	}
	
	int *yCount = new int[iterations/segmentWidth + 1];
	if(!yCount)
	{
		cout<<"ERROR mem alloc Histogram\n";
		exit(1);
	}


	for(i = 0; i <= iterations/segmentWidth; i++)
		xCount[i] = yCount[i] = 0;
		
	for(i = 0; i < n; i++)
	{
		int mod = 0;
		while( ((int)numbers[0][i])%(mod + 1) < (int)numbers[0][i] && mod <= iterations) mod += segmentWidth;
		if(mod <= iterations)
			xCount[mod/segmentWidth]++;
		
		mod = 0;
		while( ((int)numbers[1][i])%(mod + 1) < (int)numbers[0][i] && mod <= iterations) mod += segmentWidth;
		if(mod <= iterations)
			yCount[mod/segmentWidth]++;
		
	}
	
	fp = fopen(dname, "wb");
	if(!fp)
	{
		cout<<"ERROR - file cannot open\n";
		exit(0);
	}

	int countAll = 0;
	for(i = 0; i <= iterations/segmentWidth; i++)
	{
		if(axe == 'x')
		{
			fprintf(fp, "%d %d\n", i*segmentWidth, xCount[i]);		 
			countAll += xCount[i];	
		}
		else
		{
			fprintf(fp, "%d %d\n", i*segmentWidth, yCount[i]);
			countAll += yCount[i];
		}	
			 
	}		
	
	fclose(fp);
	cout<<"Check count: "<<countAll<<endl;
		
	delete []xCount;
	delete []yCount;

				
	return 1;
		
}

int averageFile(char *sname, int iterations, double tres)
{
	FILE* fp = fopen(sname, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found averageFile\n";
		exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize < 10)
	{
		fclose(fp);
		return 0;
	}
	fseek(fp, 0, SEEK_SET);
	
	char buffer[1024];
	double accMean[2] = {0}, accVar[2] = {0};
	double numbers[2][1000];
	
	
			
	
	int i = 0, n = 0, state = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[i++] = ch;
		else if(ch == ' ')
		{
			buffer[i] = NULL;
			numbers[state][n] = strtod(buffer, NULL);
			accMean[state] += numbers[state][n]; 
			state = 1;
			i = 0;
			
		}
		else
		{
			buffer[i] = NULL;
			numbers[state][n] = strtod(buffer, NULL);
			if(numbers[state][n] > tres)
				numbers[0][n] = iterations ;	
			accMean[state] += numbers[state][n]; 
			n++;
			state = 0;
			i = 0;
		}
	}		
	
	double mean[2], var[2];
	mean[0] = accMean[0]/(double)n;
	mean[1] = accMean[1]/(double)n;
	
	for(i = 0; i < n; i++)
	{
		accVar[0] += pow(((double)numbers[0][i] - mean[0]), 2);
		accVar[1] += pow(((double)numbers[1][i] - mean[1]), 2);
	}
	
	var[0] = accVar[0]/(double)n;
	var[1] = accVar[1]/(double)n;
	
//	cout<<"[file name]"<<name<<endl;
//	cout<<"<"<<mean[0]<<" "<<var[0]<<">"<<"<"<<mean[1]<<" "<<var[1]<<">#"<<n<<"\n";

	int index = extractIndex(sname);
	//cout<<index<<" "<<mean[0]<<" "<< var[0]<<endl;
	
	//cout<<index<<" "<<mean[1]<<endl;//" "<< var[1]<<endl;
	cout<<index<<" "<< var[1]<<endl;
 	fclose(fp);
				
	return 1;
		
}

double computeAverage4dir(char* dirname, char* substr, 
		int iterations, double tres, 
		int sizeOfResidueArray, char *confFileName)
{
	
    DIR* dirp = opendir(dirname);
    if (dirp == NULL) 
	{
    	return 0;
    }
     
	char str[200];
	
		
	struct direct * dp;  
	
	  
	int fileCounter = 0;
	
		
	point *structure = new point[sizeOfResidueArray + 1];
	if(!structure)
	{
		cout<<"Error mem alloc.\n";
		exit(1);
	}
	
	configFileHandler cfh(confFileName, sizeOfResidueArray);
	
	int n;
	
	while ((dp = readdir(dirp)) != NULL) 
	{
		
		if( strfind(dp->d_name, ".data") == (dp->d_namlen - 5) &&
			strfind(dp->d_name, substr) != -1 )
		{
			sprintf(str, "%s%s", dirname, dp->d_name);
			//cout<<"Doing file: "<<str<<endl;
			fileCounter++;
			
			double li = 0;
			int confIdx = extractIndex(dp->d_name);
			if(confIdx >= 0)
			{
				char *hp = cfh.readTextStructure(sizeOfResidueArray, 
				  						 structure, 
				  						 confIdx);
				li = getLocalityIndex(sizeOfResidueArray, structure, hp);
				//li = getStrongInteractionLocalityIndex(sizeOfResidueArray, structure, hp);
			}	
				
			
			n = averageFile(str, iterations, tres);
		}
		
    }
	
    closedir(dirp);
	

	delete []structure;
    return 1;

}	
//do: n1 - n2 on second field
int diff(char *n1, char *n2)//, char *conf)
{
	FILE* fp1 = fopen(n1, "rb");
	FILE* fp2 = fopen(n2, "rb");
	if(!fp1 || !fp2)
	{
		cout<<"ERROR - file not found diff\n";
		exit(0);
	}
	
	fseek(fp1, 0, SEEK_SET);
	fseek(fp2, 0, SEEK_SET);
	
	char buffer[1024];
	double numbers[2][2][1000];
	
	
			
	
	int i = 0, N1 = 0, N2 = 0, state = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp1)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[i++] = ch;
		else if(ch == ' ')
		{
			buffer[i] = NULL;
			numbers[0][state][N1] = strtod(buffer, NULL); 
			state = 1;
			i = 0;
			
		}
		else
		{
			buffer[i] = NULL;
			numbers[0][state][N1] = strtod(buffer, NULL);
			N1++;
			state = 0;
			i = 0;
		}
	}		
	i = 0;
	while((intch = fgetc(fp2)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[i++] = ch;
		else if(ch == ' ')
		{
			buffer[i] = NULL;
			numbers[1][state][N2] = strtod(buffer, NULL); 
			state = 1;
			i = 0;
			
		}
		else
		{
			buffer[i] = NULL;
			numbers[1][state][N2] = strtod(buffer, NULL);
			N2++;
			state = 0;
			i = 0;
		}
	}		
	
	int min = N1;
	if(N1 > N2)
		min = N2;
	//min = 100;
	//configFileHandler cfh(conf, 25);
	//point structure[26];
	for(i = 0; i < min; i++)
	{
					
	    //char *hp = cfh.readTextStructure(25, structure, i);
		//double li = getLocalityIndex(25, structure, hp);
		//double li = getStrongInteractionLocalityIndex(25, structure, hp);
		cout<<i<<" "<<numbers[0][1][i] - numbers[1][1][i]<<endl;
	}	

 	fclose(fp1);
	fclose(fp2);
				
	return 1;
		
}	

int grabFile2Colmn(char *sname, int colmnIdx, int size, double *numbers)
{
	FILE* fp = fopen(sname, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found grabFile2Colmn\n";
		exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize < 10)
	{
		fclose(fp);
		return 0;
	}
	fseek(fp, 0, SEEK_SET);
	
	char buffer[1024];		
	
	int i = 0, n = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[i++] = ch;
		else if(ch == ' ')
		{
			buffer[i] = NULL;
			if(n < size && colmnIdx == 0)
				numbers[n] += strtod(buffer, NULL);
			
			i = 0;
			
		}
		else
		{
			buffer[i] = NULL;
			//numbers[n] = strtod(buffer, NULL);
			if(n < size && colmnIdx == 1)
				numbers[n] += strtod(buffer, NULL);

			n++;
			i = 0;
		}
	}		
	
	fclose(fp);				
	return n;
		
}

double grabFile2Line(char *sname, int colmnIdx, int lineIdx)
{
	FILE* fp = fopen(sname, "rb");
	if(!fp)
	{
		cout<<"ERROR - file not found grabFile2Line\n";
		exit(0);
	}
	
	fseek(fp, 0, SEEK_END);
	int fileSize = ftell(fp);
	if(fileSize < 10)
	{
		fclose(fp);
		return 0;
	}
	fseek(fp, 0, SEEK_SET);
	
	char buffer[1024];		
	
	int i = 0, n = 0;
	
	char ch;
	int intch;
	
	while((intch = fgetc(fp)) != EOF)
	{
		ch = intch;
		if( (ch != ' ') && (ch != '\n') )
			buffer[i++] = ch;
		else if(ch == ' ')
		{
			buffer[i] = NULL;
			if(colmnIdx == 0 && n == lineIdx)
			{
				double ret = strtod(buffer, NULL);
				fclose(fp);
				return ret;
			}
			i = 0;
			
		}
		else
		{
			buffer[i] = NULL;
			//numbers[n] = strtod(buffer, NULL);
			if(colmnIdx == 1 && n == lineIdx)
			{
				double ret = strtod(buffer, NULL);
				fclose(fp);
				return ret;
			}

			n++;
			i = 0;
		}
	}		
	
	fclose(fp);	
	cout<<"ERROR - not found line number\n";
	exit(0);			
	return n;
		
}

int cald(int argc, char **argv)
{
	if(argc < 6)
	{
		cout<<"char* dirname, char* substr, int ColmnSize, int seqSize, int colmnIdx\n";
		exit(0);
	}
	char* dirname = argv[1];
	char* substr = argv[2]; 
	int ColmnSize = atoi(argv[3]);
	int seqSize = atoi(argv[4]);
	int colmnIdx = atoi(argv[5]);
	
	computeAverageLines4dir(dirname, substr, ColmnSize, seqSize, colmnIdx);
	return 1;
}

double computeAverageLines4dir(char* dirname, char* substr, int ColmnSize, int seqSize, int colmnIdx)
{
	double *numbers = new double[ColmnSize];
	if(!numbers)
	{
		cout<<"Error mem alloc\n";
		exit(1);
	}
	
	for(int j = 0; j < ColmnSize; j++)
		numbers[j] = 0;
	
	for(int i = seqSize - 1; i < seqSize; i++)
	{
   		DIR* dirp = opendir(dirname);
	    if (dirp == NULL) 
		{
    		return 0;
    	}
     
		char str[200];
		
		struct direct * dp;   
		int fileCounter = 0;
	
		int n = 0;
	
		while ((dp = readdir(dirp)) != NULL) 
		{
		
			if( strfind(dp->d_name, ".data") == (dp->d_namlen - 5) &&
				strfind(dp->d_name, substr) != -1 )
			{
				sprintf(str, "%s%s", dirname, dp->d_name);
				
				fileCounter++;
			
				int confIdx = extractIndex(dp->d_name);
				if(confIdx == i)
				{
					//cout<<"Doing file: "<<str<<endl;
					n++;
					grabFile2Colmn(str, colmnIdx, ColmnSize, numbers);	
				}	
			}
    	}
		closedir(dirp);
		//cout<<"Number of Files: "<<n<<endl;
		for(int j = 0; j < ColmnSize; j++)
		{
			numbers[j] /= (double)n;
			cout<<j<<" "<<numbers[j]<<endl;
		}

	}
	
    
	

	delete []numbers;
    return 1;

}	


double grabLines4dir(char* dirname, char* substrIn, double fromTemp, 
						double toTemp, int colmnIdx, int lineIdx, double itr,
						double thresh)
{
	char substr[1000];
	double vals[1000] = {0};
	int fileCounter = 0;
	
	int cntr = 0;
	for(double i = fromTemp; i <= toTemp; i += itr)
	{
		sprintf(substr, "%s-f%f", substrIn, i);
   		DIR* dirp = opendir(dirname);
	    if (dirp == NULL) 
		{
    		return 0;
    	}
     
		char str[200];
		
		struct direct * dp;   
		fileCounter = 0;
	
		
	
		while ((dp = readdir(dirp)) != NULL) 
		{
		
			if( strfind(dp->d_name, ".data") == (dp->d_namlen - 5) &&
				strfind(dp->d_name, substr) != -1 )
			{
				sprintf(str, "%s%s", dirname, dp->d_name);
				
				//cout<<"Doing file: "<<str<<endl;
				if(grabFile2Line(str, colmnIdx, lineIdx) >= thresh)
					vals[cntr]++;			
				fileCounter++;
			}
    	}
		vals[cntr] /= (double)fileCounter;
		cntr++;
		closedir(dirp);
	}
	cntr = 0;
	for(double i = fromTemp; i <= toTemp; i += itr, cntr++)
		cout<<i<<" "<<vals[cntr]<<endl;
	//cout<<"number of Files: "<<fileCounter<<endl;
    
    return 1;
}	

double grabSeqLines4dir(char* dirname, char* substrIn, double fromTemp, 
						double toTemp, int colmnIdx, int lineIdx, double itr,
						double thresh)
{
	char substr[1000];
	double vals[1000] = {0};
	int fileCounter = 0;
	
	int cntr = 0;
	for(double i = fromTemp; i <= toTemp; i += itr)
	{
		sprintf(substr, "%s-f%f", substrIn, i);
   		DIR* dirp = opendir(dirname);
	    if (dirp == NULL) 
		{
    		return 0;
    	}
     
		char str[200];
		
		struct direct * dp;   
		fileCounter = 0;
	
		
	
		while ((dp = readdir(dirp)) != NULL) 
		{
		
			if( strfind(dp->d_name, ".data") == (dp->d_namlen - 5) &&
				strfind(dp->d_name, substr) != -1 )
			{
				sprintf(str, "%s%s", dirname, dp->d_name);
				
				//cout<<"Doing file: "<<str<<endl;
				if(grabFile2Line(str, colmnIdx, lineIdx) >= thresh)
				{
					cout<<extractIndex(dp->d_name)<<endl;
					vals[cntr]++;
				}			
				fileCounter++;
			}
    	}
		vals[cntr] /= (double)fileCounter;
		cntr++;
		closedir(dirp);
	}
	cntr = 0;
	for(double i = fromTemp; i <= toTemp; i += itr, cntr++)
		cout<<i<<" "<<vals[cntr]<<endl;
	//cout<<"number of Files: "<<fileCounter<<endl;
    
    return 1;
}	

int grabl(int argc, char **argv)
{
	if(argc < 9)
	{
		cout<<"char* dirname, char* substrIn, double fromTemp,"\
			  "double toTemp, int colmnIdx, int lineIdx, double itr,\n"\
			  "double thresh\n";
		exit(0);
	}
	char* dirname = argv[1];
	char* substrIn = argv[2]; 
	double fromTemp = strtod(argv[3], NULL);
	double toTemp = strtod(argv[4], NULL);
	int colmnIdx = atoi(argv[5]);
	int lineIdx = atoi(argv[6]);
	double itr = strtod(argv[7], NULL);
	double thresh = strtod(argv[8], NULL);
	
	//grabLines4dir(dirname, substrIn, fromTemp, 
	//			  toTemp, colmnIdx, lineIdx, itr, thresh);
	grabSeqLines4dir(dirname, substrIn, fromTemp, 
				  toTemp, colmnIdx, lineIdx, itr, thresh);

	return 1;
}
