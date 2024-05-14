#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

int adjMatrix[MAX][MAX];
int n; // Number of vertices

void createGraph() {
    int i, j, edges, start, end, weight;

    printf("Enter the number of vertices: ");
    scanf("%d", &n);

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            adjMatrix[i][j] = INF;
        }
    }

    printf("Enter the number of edges: ");
    scanf("%d", &edges);

    for (i = 0; i < edges; i++) {
        printf("Enter edge (start end weight): ");
        scanf("%d %d %d", &start, &end, &weight);
        adjMatrix[start][end] = weight;
        adjMatrix[end][start] = weight; // Assuming it's an undirected graph
    }
}

int minKey(int key[], int mstSet[]) {
    int min = INF, minIndex;

    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], minIndex = v;

    return minIndex;
}

void printMST(int parent[]) {
    printf("Edge \tWeight\n");
    for (int i = 1; i < n; i++)
        printf("%d - %d \t%d \n", parent[i], i, adjMatrix[i][parent[i]]);
}

void primMST() {
    int parent[MAX]; // Array to store constructed MST
    int key[MAX];    // Key values used to pick minimum weight edge in cut
    int mstSet[MAX]; // To represent set of vertices not yet included in MST

    for (int i = 0; i < n; i++) {
        key[i] = INF;
        mstSet[i] = 0;
    }

    key[0] = 0;     // Make key 0 so that this vertex is picked as first vertex
    parent[0] = -1; // First node is always root of MST

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet);

        mstSet[u] = 1;

        for (int v = 0; v < n; v++)
            if (adjMatrix[u][v] && mstSet[v] == 0 && adjMatrix[u][v] < key[v]) {
                parent[v] = u, key[v] = adjMatrix[u][v];
            }
    }

    printMST(parent);
}

int main() {
    createGraph();
    primMST();
    return 0;
}
