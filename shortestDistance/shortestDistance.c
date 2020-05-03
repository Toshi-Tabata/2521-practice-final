
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void bfs(Graph g, int src, int dest, int visited[1000]) {
	int length = GraphNumVertices(g);
	Queue q = QueueNew();
	QueueEnqueue(q, src);
	visited[src] = src;

	while (!QueueIsEmpty(q)) {

		int curr = QueueDequeue(q);

		for (int i = 0; i < length; i++) {
			if (visited[i] == -1 && GraphIsAdjacent(g, curr, i)) {
				visited[i] = curr;
				QueueEnqueue(q, i);
				if (i == dest) {
					QueueFree(q);
					return;
				}
			}


		}

	}
	QueueFree(q);
}

int shortestDistance(Graph g, int src, int dest) {
	int length = GraphNumVertices(g);
	int visited[1000] = {0};
	for (int i = 0; i < length; i++) {
		visited[i] = -1;
	}

	bfs(g, src, dest, visited);

	int curr = visited[dest];
	if (curr == -1) return -1;
	if (curr == dest) return 0;
	int pathLength = 1;
	while (curr != -1 && curr != src) {
		curr = visited[curr];
		pathLength++;
	}
	return pathLength;
}

