
#include <stdlib.h>

#include "BSTree.h"


/*
	2 Solutions in this file
	- Traverse in infix order and increment a counter 
		(use a pointer to the counter so we can hold the value across recursive calls)

	- Use tree partitioning to find the k'th position (without rotation)
		Not that this is O(n^2) given that the trees do not hold a "size" member of the struct
		- The partitioning algorithm requires getting the size of the entire subtree, which is O(n) time for each node == O(n^2)
		Could improve by copying the tree and implementing a size member in the new tree struct, then traverse
			- But this has a run time of 2n (copy n nodes to new tree, then partition n nodes) vs first solution with n run time
			- Asymptotically better than O(n^2) though, which I implemented
*/



void infix(BSTree t, int k, int *counter, int *ans);
bool isTargetFound(int *counter, int *ans, int k, int value);

int size(BSTree t);
int partition(BSTree t, int i);


int BSTreeGetKth(BSTree t, int k) {
	// O(n) solution with counter
	int counter = 0, ans = 0;
	infix(t, k, &counter, &ans);
	return ans;

	// O(n^2) solution with partitioning, uncomment next line
	// return partition(t, k);

}

/*
1. Traverse tree depth first
2. Keep a counter that increments in infix order
3. When counter == k, return the number
O(n) complexity
*/

// Traverse tree in infix order and check if target is found
void infix(BSTree t, int k, int *counter, int *ans) {
	if (t == NULL) return;

	infix(t->left, k, counter, ans);

	if (isTargetFound(counter, ans, k, t->value))
		return;
	(*counter)++;

	infix(t->right, k, counter, ans);
}


// Checks if the counter == k, if so, set our value to current node's value
bool isTargetFound(int *counter, int *ans, int k, int value) {

	// If we have the correct k'th value, set the answer to it
	if (*counter == k) {
		*ans = value;
		(*counter)++; // Increment counter so we don't keep changing ans
		return true;

	} else if (*counter > k) 
		// early return for faster run time
		return true;
	
	return false;
}


// Returns number of nodes in current tree
int size(BSTree t) {
	return (t == NULL) ? 0 : size(t->left) + size(t->right) + 1;
}

// Partitions the tree (finds i'th node based on sizes of subtrees)
int partition(BSTree t, int i) {
	if (t == NULL) return -1;

	int n = size(t->left);

	if (i == n) return t->value;

	return (i < n) ? partition(t->left, i) : partition(t->right, i - n - 1);
}