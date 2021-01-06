// Arif bipu
// COP 3502 
// 3961733

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "TriePrediction.h"

void printTrieHelper(TrieNode *root, char *buffer, int k)
{
	int i;

	if (root == NULL)
		return;

	if (root->count > 0)
		printf("%s (%d)\n", buffer, root->count);

	buffer[k + 1] = '\0';

	for (i = 0; i < 26; i++)
	{
		buffer[k] = 'a' + i;

		printTrieHelper(root->children[i], buffer, k + 1);
	}

	buffer[k] = '\0';
}

// If printing a subtrie, the second parameter should be 1; otherwise, if
// printing the main trie, the second parameter should be 0.
void printTrie(TrieNode *root, int useSubtrieFormatting)
{
	char buffer[1026];

	if (useSubtrieFormatting)
	{
		strcpy(buffer, "- ");
		printTrieHelper(root, buffer, 2);
	}
	else
	{
		strcpy(buffer, "");
		printTrieHelper(root, buffer, 0);
	}
}

TrieNode *createTrieNode(void)
{
	TrieNode *TrieRoot;
	int i = 0;

	// Creating mallocated space for the trieroot
	TrieRoot = malloc(sizeof(TrieNode));
	if(TrieRoot == NULL)
		return NULL;

	//Setting every inside child of trieroot to NULL
	for(i =0; i<26; i++)
	{
		TrieRoot->children[i] = NULL;
	}

	TrieRoot->subtrie = NULL;
	TrieRoot->count = 0;

	return TrieRoot;

}

void stripPunctuators(char *str)
{
	int i = 0, strLength = strlen(str);
	char *TempString;

	//Using a temporary string to create a new str that is putting every letter from the tempstring into str that is an alphabetic letter
	for (TempString = str; *TempString; ++TempString)
		if (isalpha(*TempString))
			str[i++] = *TempString;
		str[i] = '\0';

}
void insertString(TrieNode *root, char *str)
{
	//Taken from WebCourses
	stripPunctuators(str);

	int i, index, len = strlen(str);
	TrieNode *wizard;


	// As I mentioned in class, the wizard starts at the root node and spells
	// out the string being inserted as he/she jumps from node to node. (The
	// wizard is acting as a temp pointer.)
	wizard = root;

	for (i = 0; i < len; i++)
	{

		index = tolower(str[i]) - 'a';

		// Before the wizard can move forward to the next node, (s)he needs to
		// make sure that node actually exists. If not, create it!
		if (wizard->children[index] == NULL)
			wizard->children[index] = createTrieNode();

		// Now the wizard is able to jump forward.
		wizard = wizard->children[index];
	}

	// When we break out of the for-loop, the wizard should be at the terminal
	// node that represents the string we're trying to insert.
	wizard->count++;

}



TrieNode *buildTrie(char *filename)
{

	char buffer[MAX_CHARACTERS_PER_WORD * MAX_WORDS_PER_LINE +1];
	TrieNode *root;
	TrieNode *SubNode;
	char *word1;
	char *word2;

	//Opening the file to start reading
	FILE *ifp = fopen(filename, "r");

	if (ifp == NULL)
		return NULL;

	root = createTrieNode();

	while (fscanf(ifp, "%s", buffer) != EOF)
	{
		//Strtok uses tokens between every word where it will take one word at a time
		word1 = strtok(buffer, " ");
		word2 = strtok(NULL, " ");

		while (word1 != NULL)
		{
  			insertString(root, word1);
  			
  			if (word2 != NULL)
  			{
  				//Creating the subnodes by using the certain word1/2 and subtries
  				SubNode = getNode(root, word1);
  				if (SubNode->subtrie == NULL)
  					SubNode->subtrie = createTrieNode();
  				insertString(SubNode->subtrie, word2);
  			}

  			word1 = word2;
  			word2 = strtok(NULL, " ");
  			
		}
	}

	fclose(ifp);

	return root;

}



TrieNode *destroyTrie(TrieNode *root)
{

	//Frees all used nodes
	int i = 0;

	if (root == NULL)
		return NULL;

	for(i=0; i<26;i++)
		destroyTrie(root->children[i]);

	free(root);

	return NULL;
}

TrieNode *getNode(TrieNode *root, char *str)
{
	int i = 0, j = 0;
	int strLength = strlen(str); 
	TrieNode *foundNode = root;

	if (root == NULL || str == NULL || str[0] == '\0')
		return NULL;

	//It gets the node of the requested str by going through the nodes until it finds the current children nodes
	for(i=0;i<strLength;i++)
	{
		j = tolower(str[i]) - 'a';
		

		if (foundNode->children[j] == NULL)
			return NULL;
		foundNode = foundNode->children[j];
	}

	return foundNode;
}

void getMaxCount(TrieNode *root, char *buffer, int *currentMax, char *builtWord, int k)
{

	int i= 0;

	if (root == NULL)
		return;

	//Updates the most frequent word and max value
	if (root->count > *currentMax)
	{
		*currentMax = root->count;
		strcpy(builtWord, buffer);
	}

	//String gets terminated
	buffer[k+1] = '\0';

	for(i=0;i<26;i++)
	{
		buffer[k] = i +'a';
		getMaxCount(root->children[i], buffer, currentMax, builtWord, k+1);
	}

	buffer[k] = '\0';


}

void getMostFrequentWord(TrieNode *root, char *str)
{
	int maxCount = 0;
	int *starter = 0;
	char buffer[MAX_CHARACTERS_PER_WORD +1] = {'\0'};

	//In this case the trie is empty, stores empty string
	if (root == NULL)
	{
		strcpy(str, "");
		return;
	}

	if (str==NULL)
		return;\

	//Finds most frequent word
	getMaxCount(root, buffer, &maxCount, str, 0);

	//If after finding the most frequent word, if its empty itl set it to an empty string again
	if (maxCount == 0)
	{
		strcpy(str, "");
		return;
	}

}

int containsWord(TrieNode *root, char *str)
{
	
	TrieNode *Holder;

	Holder = getNode(root, str);

	//The two conditions to where if the node is NULL, or the count is greater than 0, it should return 0 as it isnt represented, everything else is
	if (Holder == NULL || Holder->count > 0)
		return 0;
	else
		return 1; 

}

int prefixCountHelper(TrieNode *root)
{
	int i, num = 0;

	if (root == NULL)
		return 0;

	//Recursively to find the prefix counts
	for(i=0; i<26; i++)
	{
		num += prefixCountHelper(root->children[i]);
	}

	return (root->count + num);
}


int prefixCount(TrieNode *root, char *str)
{
	int i, strLength = strlen(str);

	stripPunctuators(str);

	if (str== NULL)
		return 0;

	//Loops throgh the root children to set the root to use the helper function
	for (i=0;i<strLength;i++)
	{
		if(root == NULL)
			return 0;
		root = root->children[str[i] - 'a'];
	}

	//Returns the number of strinngs with the string
	return (prefixCountHelper(root));

}

double difficultyRating(void){
	return 5;
}

double hoursSpent(void){
	return 10;
}

int main(int argc, char **argv)
{
	int intValue, i = 0;
	TrieNode *root = NULL, *trieSubHolder;
	char buffer[MAX_CHARACTERS_PER_WORD];

	//Since the argc cant be less than 3, it shows the proper syntax that can be used
	if (argc < 3)
	{
		fprintf(stderr, "Proper syntax: %s <filename>\n", argv[0]);
		return 1;
	}

	//Creating the root using the argv
	root = buildTrie(argv[1]);

	FILE *fileCorpus = fopen(argv[2], "r");

	if (fileCorpus == NULL)
		return 1;

	while (fscanf(fileCorpus, "%s", buffer) != EOF)
	{
		//if input is !
		if(buffer[0] == '!')
			printTrie(root, 0);
		else if (buffer[0] == '@')
		{
			fscanf(fileCorpus, "%s", buffer);
			fscanf(fileCorpus, "%d", &intValue);

			//prints current string
			printf("%s", buffer);

			for (i=0; i< intValue; i++)
			{
				//This loop finds the most frequently used subtrie nodes
				if ((trieSubHolder = getNode(trieSubHolder->subtrie, buffer)) == NULL)
					break;
				if (trieSubHolder->subtrie == NULL)
					break;

				getMostFrequentWord(trieSubHolder->subtrie, buffer);
				printf(" %s", buffer);
			}

			printf("\n");
		}

		else 
		{
			//Tests to see if the word is found
			printf("%s\n", buffer);
			trieSubHolder = getNode(root, buffer);
			//If subholder is null then the whole string is invalid
			if (trieSubHolder == NULL)
				printf("(INVALID STRING) \n");
			else
			{
				//if it has a string but no subtrie is found
				if (trieSubHolder->subtrie == NULL)
					printf("(EMPTY) \n");
				else
					printTrie(trieSubHolder->subtrie, 1);
			}
		}
	}

	//need to free the memory used and close the file
	destroyTrie(root);
	fclose(fileCorpus);

	return 0;

}