#include <stdio.h>
#include <stdlib.h>
#define V 10
//D[j] = min(D[j], D[w] + Cost(W, j))


int mini(int a, int b);
int nearest(int* distance, int* used);
void print_distances(int* distance, int* P);

int main(void)
{
	int graph[10][10] = {
	  {0, 6, 3, 0, 9, 0, 0, 0, 0, 0},
	  {6, 0, 4, 2, 0, 0, 0, 9, 0, 0},
	  {3, 4, 0, 2, 9, 9, 0, 0, 0, 0},
	  {0, 2, 2, 0, 0, 8, 0, 9, 0, 0},
	  {9, 0, 9, 0, 0, 8, 0, 0, 0, 18},
	  {0, 0, 9, 8, 8, 0, 9, 7, 0, 10},
	  {0, 0, 0, 0, 0, 9, 0, 5, 1, 3},
	  {0, 9, 0, 9, 0, 7, 5, 0, 4, 0},
	  {0, 0, 0, 0, 0, 0, 1, 4, 0, 4},
	  {0, 0, 0, 0, 18,10, 3, 0, 4, 0}
	};

	for (int i = 0; i < V; i++) {
		for (int j = 0; j < V; j++) {
			if (!graph[i][j]) graph[i][j] = 1000;
		}
	}
		//initialize
	int Distance[V] = { 0 };
	int P[V] = { 0, };
	int used[V] = { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	for (int i = 1; i < V; i++) {
		if (graph[0][i]) Distance[i] = graph[0][i];
		else Distance[i] = 1000;
	}

	//dijkstra
	for (int k = 0; k < 9; k++) {
		int u = nearest(Distance, used);

		//update
		for (int i = 0; i < V; i++) {
			Distance[i] = mini(Distance[i], Distance[u] + graph[u][i]);
			if (Distance[i] == Distance[u] + graph[u][i]) {
				P[i] = u;
			}
		}
	}

	print_distances(Distance, P);
	return 0;
}

int mini(int a, int b)
{
	if (a < b) return a;
	else return b;
}

//find nearest node since now
int nearest(int* distance, int* used)
{
	int minDist = 1000;
	int nearest = 0;
	for (int i = 0; i < V; i++) {
		//not used yet && near
		if (used[i] == 0 && minDist > distance[i]) {
			minDist = distance[i];
			nearest = i;
		}
	}
	used[nearest] = 1;
	return nearest;
}
void print_path(int P[], int i)
{
	if (i == 0) {
		printf("%d ->", i + 1);
		return;
	}
	else {
		print_path(P, P[i]);
		printf("%d ->", i + 1);
	}
}

void print_distances(int* distance, int* P)
{
	for (int i = 0; i < V; i++) {
		printf("\n1 to %d : %d\n", i + 1, distance[i]);
		print_path(P, i);
	}
}
