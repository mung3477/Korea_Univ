#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#define V 10

int find_min(int adj_mat[][V], int visited[], int used, int a, int* weigtSum);

bool is_visited(int* visited, int j, int used);

int main(void)
{

	int adj_mat[V][V] = {	{0, 6, 3, 0, 9, 0, 0, 0, 0, 0},
							{6, 0, 4, 2, 0, 0, 0, 9, 0, 0},
							{3, 4, 0, 2, 9, 9, 0, 0, 0, 0},
							{0, 2, 2, 0, 0, 8, 0, 9, 0, 0},
							{9, 0, 9, 0, 0, 8, 0, 0, 0, 18},
							{0, 0, 9, 8, 8, 0, 9, 7, 0, 10},
							{0, 0, 0, 0, 0, 9, 0, 5, 1, 3},
							{0, 9, 0, 9, 0, 7, 5, 0, 4, 0},
							{0, 0, 0, 0, 0, 0, 1, 4, 0, 4},
							{0, 0, 0, 0, 18, 10, 3, 0, 4, 0} };

	//Prim's algorithm
	int used = 0;
	int min = 0;
	int visited[V];
	for (int i = 0; i < V; i++) {
		visited[i] = 0;
	}

	int start;
	printf("input start node : ");
	scanf(" %d", &start);

	//visited : 지금까지 쓴 노드들 (순서대로 들어감)
	//used : the number of nodes that I visited
	visited[used++] = start;

	printf("%d ", start);

	int weightSum = 0;
	while (used < V) {
			min = find_min(adj_mat, visited, used, V, &weightSum);
			visited[used++] = min;
	}
	printf("\n%d", weightSum);



}

int find_min(int adj_mat[][V], int visited[], int used, int a, int* weightSum)
{
	int min_edge = -1;
	int min_weight = 100;
	//find nearest node from current tree
	for (int i = 0; i < used; i++) {
		for (int j = 0; j < V; j++) {
			//j is not visited && I can reach j && j has nearest weight since now
			if (!is_visited(visited, j, used) && adj_mat[visited[i]][j] && min_weight > adj_mat[visited[i]][j]) {
				min_edge = j;
				min_weight = adj_mat[visited[i]][j];
			}
		}
	}
	printf("-> %d", min_edge);
	//printf("dist : %d\n", min_weight);
	*weightSum += min_weight;
	return min_edge;
}

//j를 쓴 적이 있는가?
bool is_visited(int* visited, int j, int used)
{
	for (int i = 0; i < used; i++) {
		if (j == visited[i]) return true;
	}
	return false;
}
