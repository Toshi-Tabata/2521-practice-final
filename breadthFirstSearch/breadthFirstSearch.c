
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void bfs(Graph g, int src, int visited[1000]) {
	int size = GraphNumVertices(g);
	
	Queue q = QueueNew();
	QueueEnqueue(q, src);

	while (!QueueIsEmpty(q)) {
		// Curr = current vertex being visited
		int curr = QueueDequeue(q);

		for (int i = 0; i < size; i++) {
			// if the current vertex, i, is unvisited and adjacent
			if (GraphIsAdjacent(g, curr, i) && visited[i] == 0) {
				visited[i] = 1;
				printf("%d ", i);
				QueueEnqueue(q, i);
			}
		}
	}

	QueueFree(q);
}


void breadthFirstSearch(Graph g, int src) {

	// Usually you would set everything to -1, but we don't need to
	// find the path created from visited, so we can get away with it being 0
	int visited[1000] = {0};

	// Set src node as being visited
	visited[src] = 1;
	printf("%d ", src);

	bfs(g, src, visited);
}

