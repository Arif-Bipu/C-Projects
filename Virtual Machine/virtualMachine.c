// Arif Bipu
// COP 3402, Summer 2019
// Ar455641

// HW 1

#include<stdio.h>
#include<stdlib.h>
#include<strings.h>
#include<string.h>

// pre-defined constraints of the program
#define MAX_STACK_HEIGHT 23
#define MAX_CODE_LENGTH 500
#define MAX_LEXI_LEVELS 3

// struct proffessor provided
struct instruction
{
    int op; // opcode
    int r; // R
    int l; // L
    int m; // M
}instruction;

//declaring program counter, base pointer, and stack pointer
int pc, sp = 0, bp = 1;

//initializing the stack
int stack[MAX_STACK_HEIGHT] = {0};

//initializing the cpu register
int r[16] = {0};

//halt flag
int halt = 0;

//initializing the file input output
FILE *ifp,  *ofp;

// function prototypes
int base(int L, int base);
void fetch();
void execute();
void printStack(int flag);
void print(int count);

// initializing the array for the code that holds the code
struct instruction code[MAX_CODE_LENGTH];

// initializes the instruction register
struct instruction ir;

int main(int flag)
{
	// opens the files to read and write
	ifp = fopen("input.txt", "r");
	ofp = fopen("output.txt", "w");


	if (ifp == NULL)
	{
		return EXIT_SUCCESS;
	}

	// keeps the current instruction count from the input file
	int count = 0;

	// while it has not reached end of file, keep reading the opcodes
	while (!feof(ifp))
	{
		fscanf(ifp, "%d", &code[count].op);
		fscanf(ifp, "%d", &code[count].r);
		fscanf(ifp, "%d", &code[count].l);
		fscanf(ifp, "%d", &code[count].m);
		count++;
	}

	//calls the initial print function for the order
	print(count);

	//re-initializes it back to 0 after the print
	count = 0;

	fprintf(ofp, "\nInitial Values\n\t\t\t\tpc\tbp\tsp\n");

	while(halt == 0)
	{
		//begins the fetching sequence
		fetch();

		//begins the execution
		execute();

		//prints the information into the output file
		fprintf(ofp, "%d\t%d\t%d\t", ir.r, ir.l, ir.m);
		fprintf(ofp, "%d\t%d\t%d\t", pc, bp, sp);
		printStack(flag);

		if ((bp == 0) && (pc == 0) && (sp == 0))
			halt = 1;
	}

	//closes the files
	fclose(ifp);
	fclose(ofp);

	return EXIT_SUCCESS;
}

void print(int count)
{

	int i;

	fprintf(ofp, "\nLine\tOP\tR\tL\tM");

	for (i = 0; i<count; i++)
	{
		int op = code[i].op;

		//switches for each op code type
		switch(op)
		{
			case 1: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "lit\t");
					break;
			case 2: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "rtn\t");
					break;
			case 3: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "lod\t");
					break;
			case 4: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "sto\t");
					break;
			case 5: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "cal\t");
					break;
			case 6: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "inc\t");
					break;
			case 7: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "jmp\t");
					break;
			case 8: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "jpc\t");
					break;
			case 9: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "sio\t");
					break;
			case 10: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "sio\t");
					break;
			case 11: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "sio\t");
					break;
			case 12: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "neg\t");
					break;
			case 13: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "add\t");
					break;
			case 14: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "sub\t");
					break;
			case 15: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "mul\t");
					break;
			case 16: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "div\t");
					break;
			case 17: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "odd\t");
					break;
			case 18: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "mod\t");
					break;
			case 19: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "eql\t");
					break;
			case 20: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "neq\t");
					break;
			case 21: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "lss\t");
					break;
			case 22: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "leq\t");
					break;
			case 23: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "gtr\t");
					break;
			case 24: fprintf(ofp, "\n%d\t", i);
					fprintf(ofp, "geq\t");
					break;
			default: return;
		}

		fprintf(ofp, "%d\t", code[i].r);
		fprintf(ofp, "%d\t", code[i].l);
		fprintf(ofp, "%d\t", code[i].m);
	}
	return;
}

// retrieves the instruction to be executed
void fetch()
{

	// fetches the current instruction
	ir = code[pc];

	fprintf(ofp, "%d\t", pc);

	//increments the program counter
	pc++;

	return;
}

//does the actual execution of the opcodes, following the professors word file on the processes
void execute()
{

	switch(ir.op)
	{
		//lit
		case 1: fprintf(ofp, "lit\t");
				r[ir.r] = ir.m;
				break;
		//rtn
		case 2: fprintf(ofp, "rtn\t");
				sp = bp -1;
				bp = stack[sp+3];
				pc = stack[sp+4];
				break;
		//lod
		case 3: fprintf(ofp, "lod\t");
				r[ir.r] = stack[base(ir.l, bp) + ir.m];
				break;
		//sto
		case 4: fprintf(ofp, "sto\t");
				stack[ base(ir.l, bp) + ir.m] = r[ir.r];
				break;
		//cal
		case 5: fprintf(ofp, "cal\t");
				stack[sp+1] = 0;
				stack[sp+2] = base(ir.l, bp);
				stack[sp+3] = bp;
				stack[sp+4] = pc;
				bp = sp+1;
				pc = ir.m;
				break;
		//inc
		case 6: fprintf(ofp, "inc\t");
				sp = sp + ir.m;
				break;
		//jmp
		case 7: fprintf(ofp, "jmp\t");
				pc = ir.m;
				break;
		//jpc
		case 8: fprintf(ofp, "jpc\t");
				if(r[ir.r] == 0)
					pc = ir.m;
				break;
		//sio - write to screen
		case 9: fprintf(ofp, "sio\t");
				printf("\nR[%d] = %d\n", ir.r, r[ir.r]);
				break;
		//sio - read in value
		case 10: fprintf(ofp, "sio\t");
				scanf("%d", &r[ir.r]);
				break;
		//sio - set halt to 1
		case 11: fprintf(ofp, "sio\t");
				halt = 1;
				break;
		//neg
		case 12: fprintf(ofp, "neg\t");
				 r[ir.r] = 0 - r[ir.l];
				 break;
		//add
		case 13: fprintf(ofp, "add\t");
				 r[ir.r] = r[ir.l] + r[ir.m];
				 break;
		//sub
		case 14: fprintf(ofp, "sub\t");
				r[ir.r] = r[ir.l] - r[ir.m];
				 break;
		//mul
		case 15: fprintf(ofp, "mul\t");
				r[ir.r] = r[ir.l] * r[ir.m];
				 break;
		//div
		case 16: fprintf(ofp, "div\t");
				r[ir.r] = r[ir.l] / r[ir.m];
				 break;
		//odd
		case 17: fprintf(ofp, "odd\t");
				r[ir.r] = r[ir.r]%2;
				 break;
		//mod
		case 18: fprintf(ofp, "mod\t");
				r[ir.r] = r[ir.l]%r[ir.m];
				 break;
		//eql
		case 19: fprintf(ofp, "eql\t");
				if( r[ir.l] == r[ir.m])
					r[ir.r] = 1;
				else
					r[ir.r] = 0;
				 break;
		//neq
		case 20: fprintf(ofp, "neq\t");
				if(r[ir.l] != r[ir.m])
					r[ir.r] = 1;
				else
					r[ir.r] = 0;
				 break;
		//lss
		case 21: fprintf(ofp, "lss\t");
				if( r[ir.l] < r[ir.m])
					r[ir.r] = 1;
				else
					r[ir.r] = 0;
				 break;
		//div
		case 22: fprintf(ofp, "leq\t");
				if( r[ir.l] <= r[ir.m])
					r[ir.r] = 1;
				else
					r[ir.r] = 0;
				 break;
		//gtr
		case 23: fprintf(ofp, "gtr\t");
				if( r[ir.l] > r[ir.m])
					r[ir.r] = 1;
				else
					r[ir.r] = 0;
				 break;
		//geq
		case 24: fprintf(ofp, "geq\t");
				if( r[ir.l] >= r[ir.m])
					r[ir.r] = 1;
				else
					r[ir.r] = 0;
				 break;

		default: return;
	}

	return;
}

//prints the stack out
void printStack(int flag)
{
	if(bp == 0)
		return;
	else
	{
		int i;
		for (i = 1; i<= sp; i++)
		{
			if (flag)
				fprintf(ofp, "%d\t", stack[i]);
		}

		if(flag)
            fprintf(ofp, "\n");
		return;
	}
}


// base function given by the professor
int base (int l, int base)
{
	int b1;
	b1 = base;
	while(l > 0)
	{
		b1 = stack[b1-1];
		l--;
	}
	return b1;
}
