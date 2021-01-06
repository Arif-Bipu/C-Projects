// Arif bipu
// COP 3502 
// 3961733

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SmartArray.h"

SmartArray *createSmartArray(int length)
{

	SmartArray *smarty = malloc(sizeof(SmartArray));
	int i;

// If the length is less than the DEFAULT_INIT_LEN it should be the value of the predefined variable. Otherwise use the length given.
	if (length <= DEFAULT_INIT_LEN)
		length = DEFAULT_INIT_LEN;

	smarty->array = malloc(sizeof(char*)*length);
	// The capacity of the array itself should be however long the length is as it's how much it can hold
	smarty->capacity = length; 

	// To properly initialize all the array pointers to NULL
	for (i = 0; i < length; i++)
	{
		smarty->array[i] = NULL;

	}

	// Ininitialzing size to 0 as it doesn't have any elements in the array yet
	smarty->size = 0;

	if (smarty != NULL)
	{
		printf("-> Created new SmartArray of size %d.\n", smarty->capacity);		
		return smarty;
	}
	else
		return NULL;
}

SmartArray *destroySmartArray(SmartArray *smarty)
{
	int i;
	// We need to also free up the pointers in the array before freeing the rest and also make sure smarty isnt null
	if(smarty != NULL)
	{
		for (i =0; i < smarty->size; i++)
			free(smarty->array[i]);
		free(smarty->array);
		free(smarty);

	}

	return NULL;

}

SmartArray *expandSmartArray(SmartArray *smarty, int length)
{
	
	char** array1;
	int i;
	if(smarty == NULL)
		return NULL;

	// Need to determine if the new length is greater than the current capacity
	if (length > smarty->capacity)
	{
		// Making a new array of appropriate size to transfer the old one onto
		array1 = malloc(sizeof(char*)*length);

		// Memcpy will copy smarty->array over to array 1 while using the size of array 1
		memcpy(array1, smarty->array, sizeof(char*)*smarty->size);
		free(smarty->array);

		// How to transfer the new array back to the old array
		smarty->array = array1;
		// Capacity here is set to whatever "length" was set to make sure it updates with the expand function
		smarty->capacity = length;

		for (i = smarty->size; i < smarty->capacity; i++)
			{
				smarty->array[i] = NULL;
			}

		printf("-> Expanded SmartArray to size %d.\n", length);
		return smarty;
	}
	// If the length doesn't need to change it won't 
	else if (smarty == NULL || length <= smarty->capacity)
		return smarty;
	else
		return NULL;
		
}

SmartArray *trimSmartArray(SmartArray *smarty)
{
	char** array2;
	if (smarty == NULL)
		return NULL;

	// Need to determine whether the capacity is larger than the size to see how much to trim down
	if (smarty->capacity > smarty->size)
	{
		array2 = malloc(sizeof(char*)*smarty->size);
		memcpy(array2, smarty->array, sizeof(char*)*smarty->size);

		// Smarty->array is freed to be able to transfer it to the new array
		free(smarty->array);
		smarty->array = array2;

		printf("-> Trimmed SmartArray to size %d.\n", smarty->size);

		// Updating capacity once the trim function is used
		smarty->capacity = smarty->size;
		return smarty;
	}
	else if (smarty->capacity == smarty->size)
		return smarty;
	else
		return NULL;
	
}

char *put(SmartArray *smarty, char *str)
{
	int i, wordLen;
	char* Word;

// Test case to make sure that when its NULL it returns NULL
	if (smarty == NULL || str == NULL)
		return NULL;

	// Using strlen to determine the size of the new variable to put in the function
	wordLen = strlen(str);
	Word = malloc(sizeof(char) * (wordLen+1));



	// While the capacity does not equal size, it uses this because it doesn't need to expand the smartarray.
	
	if(smarty->capacity > smarty->size)
		{

		for(i = 0; i < smarty->capacity; i++)
			{
			if (smarty->array[i] == NULL)
				{

				smarty->size++;
				strcpy(Word, str);
				smarty->array[i] = Word;

				return smarty->array[i];
				}
			}	
		}
	// If the capacity == size then the function will need to expand to insert the new str
	else if (smarty->capacity == smarty->size)
		{

		expandSmartArray(smarty, (smarty->capacity)*2+1);

		for(i = 0; i < smarty->capacity; i++)
			{

			if (smarty->array[i] == NULL)
				{

				smarty->size++;
				strcpy(Word, str);
				smarty->array[i] = Word;

				return smarty->array[i];
				}
			}
		} 

	else
		return NULL; 

}

char *get(SmartArray *smarty, int index)
{
	int i;

	// Conditions to make sure that the user cannot go out of bounds 
	if (smarty == NULL || index < 0 || index > smarty->capacity || smarty->array == NULL)
		return NULL;
	else 
		return smarty->array[index];
	
		
}

char *set(SmartArray *smarty, int index, char *str)
{
	int wordLen;
	char* Word;

// Finding wordLen to make sure the new str uses the minimal space it needs
	wordLen = strlen(str);

// Since that index in the array isn't NULL, it is being used and will be replaced by another str 
	if(smarty->array[index] != NULL)
	{
		Word = malloc(sizeof(char*)*(wordLen+1));
		strcpy(Word, str);
		free(smarty->array[index]);

		//This copies the word over to the array of that index
		smarty->array[index] = Word;	

		return smarty->array[index];
	}
	else
		return NULL;

}
char *insertElement(SmartArray *smarty, int index, char *str)
{
	int wordLen, i;
	char* Word1;
	
	if(smarty==NULL || str == NULL)
		return NULL;

// The space allocated for the new word has to take up the minimal space it can
	wordLen = strlen(str);
	Word1 = malloc(sizeof(char*)*(wordLen+1));

// Copying the string into the Word1 to transfer that over to the current index
	strcpy(Word1, str);

// If the size == capacity  then it will expand the array and then call back the function where itll do the else statement
	if (smarty->size == (smarty->capacity))
	{
		expandSmartArray(smarty, (smarty->capacity*2)+1);
		return insertElement(smarty, index, str);
	}

		if (index >= smarty->size)
		{
			return put(smarty, str);
		}
		else if(index < smarty->size)
		{
			// Goes through every box and transfers to the box after it
			for(i = smarty->size; i>index; i--)
				smarty->array[i] = smarty->array[i-1];
			smarty->array[index] = NULL;
			return put(smarty, str);
	
		}
		else 
			return NULL;
		
}

int removeElement(SmartArray *smarty, int index)
{
	int i;

	if (smarty == NULL || index > smarty->size || index < 0)
		return 0;
	else
	{
		// Frees the pointer at that index
		free(smarty->array[index]);

		// Goes through each index to the box before it
    	for(i = index+1; i < (smarty->size); i++)
    			smarty->array[i-1] = smarty->array[i];

    		smarty->array[smarty->size-1] = NULL;

    		smarty->size--;
    		return 1;
    }

}

int getSize(SmartArray *smarty)
{	
	//Conditions to make sure it doesnt return a null pointer
	if (smarty != NULL)
		return smarty->size; 
	else
		return -1; 
}

void printSmartArray(SmartArray *smarty)
{
	int i;
	// Conditions to print out smart array
	if (smarty == NULL || smarty->array == NULL || smarty->size == 0)
	{
		printf("(empty array)\n");
		return;
	}
	else
		for(i = 0; i < smarty->size; i++)
		{
			printf("%s\n", smarty->array[i]);
			
		}
	
}

double difficultyRating(void)
{
	return 4;
}

double hoursSpent(void)
{
	return 25;
}


