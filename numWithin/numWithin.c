
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

/*	
	Notes:
	1. recursively DFS 
	2. Everytime we recurse, increment path length
	- need to check that we haven't counted this node before
	- only add nodes in the current path as visited 
		(if we return, remove all nodes in the path from visited)
	3. Stop if pathLength > dist 

	BFS would have a better time complexity but a longer implementation
	- Would prevent re-traversals over the same nodes
	- Basically same implementation as numReachable but counting how many nodes in the path is valid
		- too damn long so I did it with DFS


*/
void dfs(Graph g, int src, int dist, int depth, int *count, int visited[1000], int counted[1000]) {
	if (depth > dist) {
		// printf("I'm at node %d but its depth was %d > %d\n", src, depth, dist);
		return;
	}
	// printf("Found %d within the range\n", src);
	visited[src] = 1;
	if (counted[src] == 0)
		(*count)++;
	counted[src] = 1;

	int length = GraphNumVertices(g);

	for (int i = 0; i < length; i++) {
		
		// Node is unvisited and is adjacent
		if (visited[i] == 0 && GraphIsAdjacent(g, src, i)) {
			dfs(g, i, dist, depth + 1, count, visited, counted);
			visited[i] = 0;
		}
	}
}


int numWithin(Graph g, int src, int dist) {
	int count = 0;
	int visited[1000] = {0};
	int counted[1000] = {0};
	visited[src] = 1;
	dfs(g, src, dist, 0, &count, visited, counted);

	return count;
}

