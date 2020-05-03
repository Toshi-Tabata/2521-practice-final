
#include <stdlib.h>

#include "tree.h"

/*
	1. Traverse each node of the tree (I'm doing this in infix order, doesn't really matter what you choose)
	2. Check if it is an odd number (i.e. not even)
	3. Add it to sum if it is

	We're passing in a pointer to sum so we can add our current number across all recursive calls.
	This is kind of like having a global variable, and we're just adding to that same global variable "sum".
	i.e. we're using a pointer to pass by reference

	So when we change *sum inside of infix(), it is actually changing the "int ans = 0" variable inside of TreeSumOdds()
*/


// Infix traversal of the tree
void infix(Tree t, int *sum) {
	if (t == NULL) return;

	infix(t->left, sum);

	// If the number is odd
	if (t->value % 2 != 0) {
		*sum += t->value;
	}

	infix(t->right, sum);
}


int TreeSumOdds(Tree t) {

	// Store the answer
	int ans = 0;

	// Check each node of the tree, if it is odd, add it to ans
	infix(t, &ans);
	return ans;
}

