#include "stdlib.h"
#include "stdafx.h"
#include "string.h"
#include <stdio.h>

typedef struct
{
	char state[40];
	int income[3];
} record;

record records[100];
int nstates = 0;

int readFile();
record getData(char *);
void printLowestAllYears();
void printHighestAllYears();
void printLowestYear(int year);
void printHighestYear(int year);


int main()
{
	int nyears = 0;

	if (readFile())
	{
		printLowestAllYears();
		printHighestAllYears();
		printLowestYear(2004);
		printHighestYear(2004);
	}

	return 0;

}

int readFile()
{
	record temp;

	FILE *fptr;
	char line[300];
	int i;

	fptr = fopen("C:\\Users\\0063190s\\income.txt", "r");

	if (fptr == NULL)
	{
		printf("File could not be opened !!\n");
		return 0;
	}
	else
	{
		
		for (i = 0;i<2;i++) fgets(line, 300, fptr);

		while (!feof(fptr))
		{
			fgets(line, 300, fptr);
			temp = getData(line);
			records[nstates] = temp;
			nstates++;
		}

		fclose(fptr);
		return 1;
	}
}

record getData(char *ptr)
{
	record temp;
	char *token;
	char delim[] = "\t";

	//get state name 
	token = strtok(ptr, delim);
	strcpy(temp.state, token);

	// get income 2003
	token = strtok(NULL, delim);
	temp.income[0] = atoi(token);

	// get income 2004
	token = strtok(NULL, delim);
	temp.income[1] = atoi(token);

	// get income 2005
	token = strtok(NULL, delim);
	temp.income[2] = atoi(token);

	return temp;
}

void printLowestAllYears()
{
	int i, j;
	int lowestYear = 2003;
	int lowestIncome = 1000000;
	char state[40];

	for (i = 0;i<nstates; i++)
	{
		for (j = 0;j<3;j++)
		{
			if (records[i].income[j] < lowestIncome)
			{
				lowestYear = j + 2003;
				lowestIncome = records[i].income[j];
				strcpy(state, records[i].state);
			}
		}
	}

	printf("Lowest Median Income was $%d in %s in %d\n\n", lowestIncome, state, lowestYear);
}

void printHighestAllYears()
{
	int i, j;
	int highestYear = 2003;
	int highestIncome = 0;
	char state[40];

	for (i = 0;i<nstates; i++)
	{
		for (j = 0;j<3;j++)
		{
			if (records[i].income[j] > highestIncome)
			{
				highestYear = j + 2003;
				highestIncome = records[i].income[j];
				strcpy(state, records[i].state);
			}
		}
	}
	printf("Highest Median Income was $%d in %s in %d\n\n", highestIncome, state, highestYear);
}

void printLowestYear(int year)
{
	int i;
	int lowestIncome = 1000000;
	char state[40];

	for (i = 0;i<nstates; i++)
	{
		if (records[i].income[year - 2003] < lowestIncome)
		{
			lowestIncome = records[i].income[year - 2003];
			strcpy(state, records[i].state);
		}
	}
	printf("Lowest Median Income in %d was $%d in %s \n\n", year, lowestIncome, state);
}

void printHighestYear(int year)
{
	int i;
	int highestIncome = 0;
	char state[40];

	for (i = 0;i<nstates; i++)
	{
		if (records[i].income[year - 2003] > highestIncome)
		{
			highestIncome = records[i].income[year - 2003];
			strcpy(state, records[i].state);
		}
	}
	printf("Highest Median Income in %d was $%d in %s \n\n", year, highestIncome, state);
}
