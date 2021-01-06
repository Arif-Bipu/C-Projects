// Arif Bipu ar455641
// COP 3502, Spring 2017

#include <stdio.h>
#include "Varg.h"
#include <stdarg.h>

char mostFrequentChar(int first, ...)
{
	int i, n;
	int count = 0;
	int array_of_letters[26] = {0};
	char cMax = '\0';

	va_list argp;
	va_start(argp, first);

// The for loop depends on what the first integer is, creating a loop going as many times as first equals, where each increment will go through all the letters in the function.
// Also contains the function where n = each letter in the argument
	for (i=0; i < first; i++)
	{

		n = va_arg(argp, int);
		array_of_letters[n-'a']++;

// If loop used to continously repeat the function of creating a new max valued character using each argument and comparing it to the current count of the highest counted character		
		if (array_of_letters[n-'a'] > count)
		{
			cMax = n;
			count = array_of_letters[n-'a'];
		}
	
	}

	va_end(argp);
	return cMax;

}


char fancyMostFrequentChar(char c, ...)
{

	int count = 0;
	int n; 
	int array_of_letters[26] = {0};
	char cMax = '\0';

	va_list argp;
	va_start(argp, c);


// For loop made where the function will run starting at c, and continuing to run as long as the n integer != 0 while also putting each letter into the loop with it's argument (e.g. 'n'). 
	for (n = c; n != '\0'; n = va_arg(argp, int))
	{

		array_of_letters[n-'a']++;

// If loop used to continously repeat the function of creating a new max valued character using each argument and comparing it to the current count of the highest counted character
		if (array_of_letters[n-'a'] > count)
		{

			cMax = n;
			count = array_of_letters[n-'a'];

		}

	} 

	va_end(argp);
	return cMax;

}

double difficultyRating(void)
{
	return 4;
}

double hoursSpent(void)
{
	return 5;
}