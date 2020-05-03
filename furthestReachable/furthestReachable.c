
#include <stdio.h>
#include <stdlib.h>

#include "Graph.h"
#include "Queue.h"

void initVisited(int visited[1000], int size);
void bfs(Graph g, int src, int visited[1000], int orderSeen[1000], int *size);

/*
	Solutions:
	- Create a visited array and check the path length of each node in the graph to src
		- The largest vertex with the longest path is your answer
		- This is essentially what I did

	- Keep track of the current path length as you BFS
		- If your current path length > maxPathLength, update maxPathLength, and the furthestNode
		- If currPathLength == maxPathLength, compare vertex numbers
		- You'll need to store a tuple inside the BFS queue, e.g. (vertexNumber, nodeDepth)
			- If you add to the queue, nodeDepth = curr's NodeDepth + 1
		- It's way faster and probably shorter to implement but isn't what the question wanted you to do LOL

*/



// Find the furthest node
/*
1. Loop BACKWARDS through the orderSeen array
- We will check the furthest nodes from the src node

2. Get the path length from from the "curr" node to "src" node using Visited Array

3. If the path length is longer than the one we've previously seen
- Update furthestNode = curr
- Update maxPathLength = currPathLength

4. If it is equal in length, check if curr's vertex number > furthestNode number
	- If it is, update furthestNode

5. If currPathLength < maxPathLength, then we are done.
	- We won't find another node that has a longer path length so we return

Let pathLength = number of edges from curr to src
Worst case we have O(pathLength * numVertices)
- Each vertex has the same path length
- Have to check each vertex O(numVertices) for its path length O(pathLength) and vertex number
*/
int getFurthestNode(int orderSeen[1000], int visited[1000], int size, int src) {

	int lastSeen = orderSeen[size];
	int maxPathLength = 0;
	int furthestNode = lastSeen;

	// Check each node that we had seen in orderSeen
	for (int i = size; i >= 0; i--) {

		// We're getting the path length of curr in each loop iteration
		int curr = orderSeen[i];

		// Traverse through the visited array and get the path length
		lastSeen = curr;
		int currPathLength = 0;

		// Traverse the visited array and find the path we took to get there
		while (lastSeen != -1 && lastSeen != src) {
			lastSeen = visited[lastSeen];
			currPathLength++;
		}

		if (currPathLength > maxPathLength) {
			maxPathLength = currPathLength;
			furthestNode = curr;

		// If we found a node that has the same path length AND a larger vertex number
		} else if (currPathLength == maxPathLength && furthestNode < curr) {
			furthestNode = curr;

		} else if (currPathLength < maxPathLength) {

			// We won't find a shorter path, so we return the furthestNode we found
			return furthestNode;
		}
	}
	return furthestNode;

}

int furthestReachable(Graph g, int src) {
	if (g == NULL) return -1;

	// Set all nodes in visited to -1
	int visited[1000] = {0};
	initVisited(visited, GraphNumVertices(g));
	visited[src] = src;

	// Store the order in which we visit nodes (last nodes we visit are the furthest from src)
	int orderSeen[1000] = {0};

	// Store the location (size of orderSeen) of the last node we see
	int size = 1;
	initVisited(orderSeen, GraphNumVertices(g));
	orderSeen[0] = src;

	// BFS to create a visited array
	bfs(g, src, visited, orderSeen, &size);

	// Get the furthest node
	return getFurthestNode(orderSeen, visited, size, src);
}


void initVisited(int visited[1000], int size) {
	for (int i = 0; i < size; i++)
		visited[i] = -1;
}

// Super standard BFS
// visited is a normal visited array, where we visited index and went to value, index->value
// We also store the order in which we see the nodes (last nodes that we see have maximum path length)
void bfs(Graph g, int src, int visited[1000], int orderSeen[1000], int *size) {
	int length = GraphNumVertices(g);
	Queue q = QueueNew();
	QueueEnqueue(q, src);

	while (!QueueIsEmpty(q)) {
		// Current vertex being visited
		int curr = QueueDequeue(q);

		for (int i = 0; i < length; i++) {

			// if the node is unvisited and adjacent
			if (visited[i] == -1 && GraphIsAdjacent(g, curr, i)) {
				visited[i] = curr;
				QueueEnqueue(q, i);

				orderSeen[*size] = i;
				(*size)++;
			}

		}
		

	}
	QueueFree(q);
}