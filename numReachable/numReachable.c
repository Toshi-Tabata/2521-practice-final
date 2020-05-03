#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

/*
	If you're stuck on how to approach this question, here's some hints

	1. Use recursive DFS to solve this 
	(we weren't given a queue/stack implementation, so it's unlikely we have to do iterative BFS/DFS)

	2. We aren't given the graph's data structure in Graph.h, so use it as an ADT
	(We have "typedef struct graph *Graph;" which means we can't access the graph directly)
	(i.e. use the functions contained within Graph.h to solve this question)

	3. Use the functions, 
	int GraphNumVertices(Graph g); to get how many vertices we have in the graph
	bool GraphIsAdjacent(Graph g, Vertex v, Vertex w); to find what edges are adjacent to our current vertex
	- This is useful since we need to DFS across adjacent vertices
*/

/*
Notes about my implementation:
- visited[] array being passed in will be update the original visited array
	- i.e. pass by reference
- int *count is doing the same thing as the visited[] array - it's pass by reference
	- i.e. changing the *count value will change it "globally"
	- This is how we're keeping track of how many nodes we have visited

- We don't know what nodes are adjacent, so we loop through all nodes and
	check if it is adjacent to our current src ndoe

- The src node is the vertex that we're starting each new recursive DFS call on

- Our base case for dfs() is when all nodes are visited (that are reachable)
*/

// Standard recursive DFS implementation on a graph
void dfs(Graph g, int src, int visited[1000], int *count) {
	int size = GraphNumVertices(g);

	// Loop through all adjacent vertices
	// j = adjacent vertex
	for (int j = 0; j < size; j++) {

		// If it is adjacent and unvisited, recursively dfs
		if (visited[j] == 0 && GraphIsAdjacent(g, src, j)) {
			
			// Set j, our adjacent vertex, as visited
			visited[j] = 1;

			// We have reached a new reachable vertex, so we increment count
			*count += 1;

			// Continue to DFS, starting from j
			dfs(g, j, visited, count);
		}			
	}
}


// Returns number of vertices reachable from the given src
int numReachable(Graph g, int src) {
	if (g == NULL) return 0;

	// Create a "global" visited array - doesn't need to be global since arrays are pass by reference
	int visited[1000] = {0};

	// Mark the starting node as visited
	visited[src] = 1;

	// Store the number of reachable nodes (start count at 1 to include src node)
	int count = 1;

	// Do a standard recursive DFS on the graph.
	dfs(g, src, visited, &count);
	return count;
}

