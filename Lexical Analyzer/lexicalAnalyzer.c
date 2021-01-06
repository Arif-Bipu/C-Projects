// Arif Bipu
// COP 3402, Summer 2019
// Lexical Analyzer for the programming language PL/0

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

// Using pre-defined numbers from the slides
#define norw 15
#define imax 32767
#define cmax 11
#define nestmax 5
#define strmax 256
#define MAX_NAME_TABLE_SIZE 500

// Struct from the appendix to use
typedef struct 
{
	int kind;	 	// const = 1, var = 2, etc
	char name[10]; 	// name up to 11 letters
	int val; 		// number (ASCII value)
	int level;		// L Level
	int adr;		// M Address
} namerecord_t;

//Initializing the tables
symbol_table[MAX_NAME_TABLE_SIZE];

// Enumerator to define these as numbers
typedef enum
{
	 nulsym = 1, identsym = 2, numbersym = 3, plussym = 4, minussym = 5, multsym = 6,  slashsym = 7, oddsym = 8, eqsym = 9, neqsym = 10, lessym = 11, leqsym = 12, gtrsym = 13, geqsym = 14, lparentsym = 15, rparentsym = 16, commasym = 17, semicolonsym = 18, periodsym = 19,becomessym = 20, beginsym = 21, endsym = 22, ifsym = 23, thensym = 24, whilesym = 25, dosym = 26, callsym = 27, constsym = 28, varsym = 29, procsym = 30, writesym = 31, readsym = 32, elsesym = 33
} token_type;

// Initialization of the words 
char *word[] = {"null", "begin", "call", "begin", "end", "if", "then", "else", "while", "do", "read", "write"};

// Initializing where the input will go and track its size
char input[5000];
int inputSize = 0;

FILE *ifp;
FILE *ofp;


// Main function/analyzer
void main()
{

	// Opening up the files to be able to use
	ifp = fopen("input.txt", "r");
	ofp = fopen("output.txt", "w");

	// Will end the program if there is no input
	if(ifp == NULL);
		return;


	char temp;
	int i = 0;

	// Scanning in the input file character by character
	while(fscanf(ifp, "%c", &temp) != EOF)
	{
		input[i] = temp;
		i++;
		inputSize++;
	}

	// Closes the file
	fclose(ifp);
	

	
}