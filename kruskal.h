//
// Created by propl on 28/5/2023.
//

#ifndef TEST_ERGASIA3_KRUSKAL_H
#define TEST_ERGASIA3_KRUSKAL_H

#endif //TEST_ERGASIA3_KRUSKAL_H
#include <stdio.h>
#include <stdlib.h>

// Struct to represent the edge
struct Edge {
    int source, destination, baros;
    struct Edge* nextEdge;
};

// struct to represetn the unionselection has parenet and ID
struct UnionSelection {
    int parent;
    int UnionID;
};

// Struct to represent a graphKruskal
struct GraphKruskal {
    int vertices;
    struct Edge** adjList;
};


struct GraphKruskal* createGraphKruskal(int Vertices) {
    //create graph of with Vertices
    struct GraphKruskal* newGraph = (struct GraphKruskal*)malloc(sizeof(struct GraphKruskal));
    newGraph->vertices = Vertices;
    newGraph->adjList = (struct Edge**)malloc(Vertices * sizeof(struct Edge*));
    for (int i = 0; i < Vertices; ++i)
    {
        newGraph->adjList[i] = NULL;
    }
    return newGraph;
}


struct Edge* createEdge(int newSource, int newDestination, int newBaros) {
    //create a struct edge and return it
    struct Edge* newEdge = (struct Edge*)malloc(sizeof(struct Edge));
    newEdge->source = newSource;
    newEdge->destination = newDestination;
    newEdge->baros = newBaros;
    newEdge->nextEdge = NULL;
    return newEdge;
}


void addEdgeKruskal(struct GraphKruskal* graph, int newSource, int newDestination, int newBaros) {
    struct Edge* newEdge = createEdge(newSource, newDestination, newBaros);
    newEdge->nextEdge = graph->adjList[newSource];
    graph->adjList[newSource] = newEdge;

    //an undirected graph

    newEdge = createEdge(newDestination, newSource, newBaros);
    newEdge->nextEdge = graph->adjList[newDestination];
    graph->adjList[newDestination] = newEdge;

}


int FindParent(struct UnionSelection *unionSelectionArray, int i) {
    //find the parent of a node
    if (unionSelectionArray[i].parent != i)
    {
        unionSelectionArray[i].parent = FindParent(unionSelectionArray, unionSelectionArray[i].parent);
    }

    return unionSelectionArray[i].parent;
}


void unionSet(struct UnionSelection unionSelectionArray[], int xchild, int ychild) {
    //perform the union of two sets making use of the ID
    int xparent = FindParent(unionSelectionArray, xchild);
    int yparent = FindParent(unionSelectionArray, ychild);

    if (unionSelectionArray[xparent].UnionID <unionSelectionArray[yparent].UnionID)
    {
        unionSelectionArray[xparent].parent = yparent;
    }
    else if (unionSelectionArray[xparent].UnionID > unionSelectionArray[yparent].UnionID)
    {
        unionSelectionArray[yparent].parent = xparent;
    }
    else
    {
        unionSelectionArray[yparent].parent = xparent;
        unionSelectionArray[xparent].UnionID++;
    }
}


int compare(const void* a, const void* b) {
    // comparison function for sorting edges based on their weights
    struct Edge* a1 = *(struct Edge**)a;
    struct Edge* b1 = *(struct Edge**)b;
    return a1->baros - b1->baros;
}


void kruskalMinimun_spanning_tree(struct GraphKruskal* graph) {
    int V = graph->vertices;
    struct Edge* finalResult[V]; // Stores the resul minimum spanning tree
    int sizeofFinal = 0; // Index variable for finalResult[]
    int sizeOfEdges = 0; // Index variable for sorted edges

    // malloc memory for the subsets
    struct UnionSelection* unionSelectionArray = (struct UnionSelection*)malloc(V * sizeof(struct UnionSelection));

    // initialize subsets
    for (int j = 0; j < V; ++j) {
        unionSelectionArray[j].parent = j;
        unionSelectionArray[j].UnionID = 0;
    }

    // store all edges
    struct Edge* allEdges[V * V];
    int numEdges = 0;

    // Traverse the adjacency list and add edges to the array.
    for (int v = 0; v < V; ++v) {
        struct Edge* tempEges = graph->adjList[v];
        while (tempEges != NULL)
        {
            allEdges[numEdges++] = tempEges;
            tempEges = tempEges->nextEdge;
        }
    }

    // Sort all edges in non-decreasing order of their baros
    qsort(allEdges, numEdges, sizeof(struct Edge*), compare);

    while (sizeofFinal < V - 1 && sizeOfEdges < numEdges)
    {
        struct Edge* next_edge = allEdges[sizeOfEdges++];

        int xparent = FindParent(unionSelectionArray, next_edge->source);
        int ychild = FindParent(unionSelectionArray, next_edge->destination);

        if (xparent != ychild)
        {
            finalResult[sizeofFinal++] = next_edge;
            unionSet(unionSelectionArray, xparent, ychild);
        }
    }
    //printf the minimum spanning tree
    printf("\nEdges minimum spanning tree created with Kruskal algorithm :\n");
    for (sizeOfEdges = 0; sizeOfEdges < sizeofFinal; ++sizeOfEdges)
        printf("%d <--> %d\tWeight: %d\n", finalResult[sizeOfEdges]->source, finalResult[sizeOfEdges]->destination, finalResult[sizeOfEdges]->baros);
}