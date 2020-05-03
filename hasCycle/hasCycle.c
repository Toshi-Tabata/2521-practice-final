
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Stack.h"

// Return true if we have a cycle
int dfs(Graph g, int src, int visited[1000], int prev) {
	int size = GraphNumVertices(g);
	// For each adjacent node, DFS

	int ans = false;

	for (int i = 0; i < size; i++) {

		// If vertex is unvisited and adjacent
		if (visited[i] == 0 && GraphIsAdjacent(g, src, i)) {
			visited[i] = 1;
			ans = dfs(g, i, visited, src);

			// If we return from dfs and have a cycle later on, return true;
			if (ans) return ans;

		// If we have visited this node before, and it isn't the
		// previous node or the current node and it is adjacent to current node
		} else if (
			visited[i] != 0 && 
			i != prev && 
			i != src && 
			GraphIsAdjacent(g, src, i)
		) {

			// Then we have a cycle
			return true;
		}

	}
	return false;
}


// DFS each node in the graph
// Need to dfs each node since it may not be one connected graph
bool hasCycle(Graph g) {
	int length = GraphNumVertices(g);
	bool ans = false;

	int visited[1000] = {0};

	for (int i = 0; i < length; i++) {
		// If we have already checked this connected subgraph, skip it
		if (visited[i]) continue;
		
		// Set current vertex as visited and DFS from this starting point
		visited[i] = 1;
		ans = dfs(g, i, visited, i);

		// If we have a cycle, we can return true
		if (ans) return ans;
	}


	return ans;
}

