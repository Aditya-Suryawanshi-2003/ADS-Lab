#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adjMatrix[MAX][MAX];
int visited[MAX];
int queue[MAX];
int front = -1, rear = -1;
int n; // Number of vertices

void addEdge(int start, int end) {
    adjMatrix[start][end] = 1;
    adjMatrix[end][start] = 1; // Assuming it's an undirected graph
}

void createGraph() {
    int i, j, edges, start, end;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            adjMatrix[i][j] = 0;
        }
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (i = 0; i < edges; i++) {
        printf("Enter edge (start end): ");
        scanf("%d %d", &start, &end);
        addEdge(start, end);
    }
}

void bfs(int start) {
    int i;
    front = rear = 0;
    queue[rear] = start;
    visited[start] = 1;

    while (front <= rear) {
        int current = queue[front++];
        printf("%d ", current);

        for (i = 0; i < n; i++) {
            if (adjMatrix[current][i] == 1 && !visited[i]) {
                queue[++rear] = i;
                visited[i] = 1;
            }
        }
    }
}

void dfs(int start) {
    int i;
    printf("%d ", start);
    visited[start] = 1;

    for (i = 0; i < n; i++) {
        if (adjMatrix[start][i] == 1 && !visited[i]) {
            dfs(i);
        }
    }
}

void resetVisited() {
    for (int i = 0; i < n; i++) {
        visited[i] = 0;
    }
}

int main() {
    int startVertex;

    createGraph();

    printf("Enter the starting vertex for BFS: ");
    scanf("%d", &startVertex);
    resetVisited();
    printf("BFS traversal starting from vertex %d: ", startVertex);
    bfs(startVertex);
    printf("\n");

    printf("Enter the starting vertex for DFS: ");
    scanf("%d", &startVertex);
    resetVisited();
    printf("DFS traversal starting from vertex %d: ", startVertex);
    dfs(startVertex);
    printf("\n");

    return 0;
}
