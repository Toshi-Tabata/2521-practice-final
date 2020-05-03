
#include "list.h"

void insertNode(List list1, int value);
int isNodeUnique(List s1, Node curr);

/*
1. Create a "new" copy of s1 (since we can't modify s1 or s2) - there's a function given to do this
2. For each value in s2, check if it is in "new"
3. If is NOT in "new", add it to "new"
*/

// Overall O(n^2 + n*m) == O(n(n + m)) because of listSortedCopy, otherwise O(n*m)
// Returns a new list that is the union of s1 and s2
// Note that s1 and s2 are mathematical sets (no repeats)
List listSetUnion(List s1, List s2) {
	
	// O(n^2) - for each node (n times), insert it in order (n comparisons)
	// Can implement my own list copy for O(n) but I'm lazy
	List new = listSortedCopy(s1);  
	Node curr = s2->head;

	// Loop through each node (curr) in s2 (set 2)
	while (curr != NULL) {
		
		// Check if curr's value is already inside of new
		int is_unique = isNodeUnique(new, curr);

		// Curr's value was not in "new", so we add curr's value to new
		if (is_unique) insertNode(new, curr->value);
		
		curr = curr->next;
	}

	return new;
}


// Loop through each node in the list
// If curr->val is inside of list, return 0 (it isn't unique)
// If curr->val isn't found inside of list, return 1 (it is unique)
int isNodeUnique(List list, Node curr2) {

	Node curr = list->head;
	while (curr != NULL) {

		if (curr->value == curr2->value) return 0;
		
		curr = curr->next;
	}

	return 1;
}


// We just insert the node willy nilly into the list, it doesn't matter
// where we put it LOL 
// Here, we're attaching value after the head
// i.e. head->(newNode with value)-> rest of the list -> NULL
// I did it this way cuz it's constant time insertion and I don't want to update the head (lazy)
void insertNode(List list1, int value) {
	if (list1->head == NULL) {
		list1->head = newNode(value);
		return;
	}

	Node new = newNode(value);
	Node temp = list1->head->next;
	list1->head->next = new;
	new->next = temp;
}
