// Arif bipu
// COP 3502 
// 3961733

#include <stdio.h>
#include <stdlib.h>
#include "KindredSpirits.h"

int node_count(node *root)
{
	int count;
	if (root == NULL)
		return (0);

	// returns count using root = 1 + counting the root on the left and the right
	count = 1 + node_count(root->left) + node_count(root->right);
	return count;
}

void preorder(node *root, int *i, int *array)
{

	if (root == NULL)
		return;
	else
	{
		if (root != NULL)
		{
			// uses array of dereferenced i so it stays persistent, also preorder is root, left branch then right branch
			array[*i] = root->data;
			(*i)++;
			preorder(root->left, i, array);
			preorder(root->right, i, array);

		}
	}
}

void postorder(node *root, int *i, int *array)
{

	if (root == NULL)
		return;
	else
	{
		if (root != NULL)
		{
			// uses array of dereferenced i so it stays persistent, also postorder is left branch, right branch then root
			postorder(root->left, i, array);
			postorder(root->right, i, array);
			array[*i] = root->data;
			(*i)++;
		}
	}
}

int isReflection(node *a, node *b)
{
	if (node_count(a) != node_count(b))
		return 0;
	else 
	{
		//if both branches are NULL then it is either the end of the bst or no nodes so they are reflections
		if(a == NULL && b == NULL)
			return 1;
		//base cases of values being equal, and if one node is null while the other isnt
		if ((a->data != b->data) || (a == NULL && b != NULL) || (a != NULL && b == NULL) )
			return 0;
		else 
		{
			//will return 1 if theyre both true and 0 if theyre not both true
			return isReflection(a->left, b->right) && isReflection(b->left, a->right);
		}

	}
}

int arrayCompare(int *array1, int *array2, int arrayLen)
{
	//helper function to compare two arrays
	int k;

	for (k =0; k < arrayLen; k++)
	{
		if (array1[k] != array2[k])
			return 0;
	}
		return 1;
}

node *makeReflection(node *root)
{

	//allocates memory for the new node
	node *reflect = malloc(sizeof(node));

	if (root == NULL)
		return NULL;

	//copies the data from one node to the next
	reflect->data = root->data;
	// it is recursive since the function returns the node, it will return the correct node for the left/right
	reflect->left = makeReflection(root->right);
	reflect->right = makeReflection(root->left);
	return reflect;

}

int kindredSpirits(node *a, node *b)
{
	//If both are NULL then it is either end of bst or no nodes so it will be a kindred spirit
	if (a == NULL && b == NULL) 
		return 1;
	if ((a != NULL && b == NULL) || (a == NULL && b != NULL) || (node_count(a) != node_count(b)))
		return 0;

	//declaring arrays for each pre and post order from the two nodes
	int arrayAPre[node_count(b)];
	int arrayBPost[node_count(b)];
	int arrayAPost[node_count(b)];
	int arrayBPre[node_count(b)];
	int i = 0;
	int j = 0;
	int k = 0;
	int l = 0;


	//these are to find both the post and pre order of each node into arrays
	preorder(a, &i, arrayAPre);
	postorder(b, &j, arrayBPost);

	preorder(b, &k, arrayBPre);
	postorder(a, &l, arrayAPost);

	//they need to both be true to return 1, else it will fail
	return arrayCompare(arrayAPre, arrayBPost, node_count(a)) || arrayCompare(arrayBPre, arrayAPost, node_count(a)); 

}

double difficultyRating(void)
{
	return 4;
}

double hoursSpent(void)
{
	return 10;
}

