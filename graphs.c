#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Maximum vertices
#define MAX 100

// Node structure for adjacency list
typedef struct Node
{
    int vertex;
    struct Node *next;
} Node;

// Edge structure for Kruskal's Algorithm
typedef struct Edge
{
    int src, dest, weight;
} Edge;

// Union-Find structure
typedef struct Subset
{
    int parent;
    int rank;
} Subset;

// Global variables
Node *adjList[MAX] = {NULL};
int graph[MAX][MAX] = {0}; // Adjacency matrix for weighted graph

// Function to create a new adjacency list node
Node *createNode(int vertex)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->vertex = vertex;
    newNode->next = NULL;
    return newNode;
}

// Add edge to adjacency list
void addEdgeList(int u, int v)
{
    Node *newNode = createNode(v);
    newNode->next = adjList[u];
    adjList[u] = newNode;

    newNode = createNode(u); // For undirected graph
    newNode->next = adjList[v];
    adjList[v] = newNode;
}

// BFS Traversal
void BFS(int start, int vertices)
{
    int visited[MAX] = {0};
    int queue[MAX], front = 0, rear = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS Traversal: ");
    while (front < rear)
    {
        int current = queue[front++];
        printf("%d ", current);

        for (Node *temp = adjList[current]; temp != NULL; temp = temp->next)
        {
            if (!visited[temp->vertex])
            {
                visited[temp->vertex] = 1;
                queue[rear++] = temp->vertex;
            }
        }
    }
    printf("\n");
}

// DFS Traversal
void DFSUtil(int vertex, int visited[])
{
    printf("%d ", vertex);
    visited[vertex] = 1;

    for (Node *temp = adjList[vertex]; temp != NULL; temp = temp->next)
    {
        if (!visited[temp->vertex])
        {
            DFSUtil(temp->vertex, visited);
        }
    }
}

void DFS(int start, int vertices)
{
    int visited[MAX] = {0};
    printf("DFS Traversal: ");
    DFSUtil(start, visited);
    printf("\n");
}

// Dijkstra's Shortest Path
void dijkstra(int start, int vertices)
{
    int dist[MAX], visited[MAX] = {0};

    for (int i = 0; i < vertices; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[start] = 0;

    for (int i = 0; i < vertices; i++)
    {
        int u = -1;
        for (int j = 0; j < vertices; j++)
        {
            if (!visited[j] && (u == -1 || dist[j] < dist[u]))
            {
                u = j;
            }
        }

        visited[u] = 1;

        for (int v = 0; v < vertices; v++)
        {
            if (graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
            {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }

    printf("Dijkstra's Shortest Path (from vertex %d):\n", start);
    for (int i = 0; i < vertices; i++)
    {
        printf("Vertex %d: %d\n", i, dist[i]);
    }
}

// Kruskal's Algorithm Helper Functions
int find(Subset subsets[], int i)
{
    if (subsets[i].parent != i)
    {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

void Union(Subset subsets[], int x, int y)
{
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank)
    {
        subsets[rootX].parent = rootY;
    }
    else if (subsets[rootX].rank > subsets[rootY].rank)
    {
        subsets[rootY].parent = rootX;
    }
    else
    {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

// Kruskal's Algorithm
int compareEdges(const void *a, const void *b)
{
    return ((Edge *)a)->weight - ((Edge *)b)->weight;
}

void kruskal(Edge edges[], int vertices, int edgeCount)
{
    Subset subsets[MAX];
    for (int i = 0; i < vertices; i++)
    {
        subsets[i].parent = i;
        subsets[i].rank = 0;
    }

    qsort(edges, edgeCount, sizeof(Edge), compareEdges);

    printf("Kruskal's Minimum Spanning Tree:\n");
    for (int i = 0, count = 0; count < vertices - 1 && i < edgeCount; i++)
    {
        Edge nextEdge = edges[i];

        int x = find(subsets, nextEdge.src);
        int y = find(subsets, nextEdge.dest);

        if (x != y)
        {
            printf("Edge (%d, %d) with weight %d\n", nextEdge.src, nextEdge.dest, nextEdge.weight);
            Union(subsets, x, y);
            count++;
        }
    }
}

// Main Function
int main()
{
    int vertices = 6;

    // Adjacency List Edges
    addEdgeList(0, 1);
    addEdgeList(0, 2);
    addEdgeList(1, 3);
    addEdgeList(2, 4);
    addEdgeList(3, 5);

    // Adjacency Matrix for Weighted Graph (for Dijkstra's)
    graph[0][1] = 2;
    graph[0][2] = 4;
    graph[1][3] = 1;
    graph[2][4] = 3;
    graph[3][5] = 7;

    // BFS and DFS Traversals
    BFS(0, vertices);
    DFS(0, vertices);

    // Dijkstra's Algorithm
    dijkstra(0, vertices);

    // Kruskal's MST
    Edge edges[] = {
        {0, 1, 2}, {0, 2, 4}, {1, 3, 1}, {2, 4, 3}, {3, 5, 7}};
    kruskal(edges, vertices, 5);

    return 0;
}