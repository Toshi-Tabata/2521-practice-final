
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"

void dfs(Graph g, int src, int visited[1000]) {
	int size = GraphNumVertices(g);

	// Loop through each vertex that is adjacent to src
	for (int i = 0; i < size; i++) {

		// vertex 'i' is adjacent to src and is unvisited
		if (GraphIsAdjacent(g, src, i) && visited[i] == 0) {
			visited[i] = 1;
			printf("%d ", i);
			dfs(g, i, visited);
		}
	}

}

void depthFirstSearch(Graph g, int src) {
	int visited[1000] = {0};

	// Set the src as visited and print it to stdout as required by specs
	visited[src] = 1;
	printf("%d ", src);

	dfs(g, src, visited);
}

