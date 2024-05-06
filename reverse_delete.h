//
// Created by propl on 28/5/2023.
//

#ifndef TEST_ERGASIA3_REVERSE_DELETE_H
#define TEST_ERGASIA3_REVERSE_DELETE_H

#endif //TEST_ERGASIA3_REVERSE_DELETE_H
#include <stdio.h>
#include <stdbool.h>

#define MAX_VERTICES 1000000

// Struct to represent an edge of the Reverse Delete algorithm
typedef struct {
    int source;
    int destination;
    int weight;
} EdgeReverse;

// Structure to represent a graph reverse delete
typedef struct {
    int numVertices;
    int numEdges;
    EdgeReverse edges[MAX_VERTICES];
} GraphReverse;

// Function to create a graph reverse delete
GraphReverse* createGraphReverse(int numVertices, int numEdges) {
    //initialize the graph that has numberofvertices and numberofedges
    GraphReverse* graph = (GraphReverse*)malloc(sizeof(GraphReverse));
    graph->numVertices = numVertices;
    graph->numEdges = numEdges;
    return graph;
}
void addEdgeReverse(GraphReverse * graph, int source, int destination, int weight) {
    graph->edges[graph->numEdges].source = source;
    graph->edges[graph->numEdges].destination = destination;
    graph->edges[graph->numEdges].weight = weight;
    graph->numEdges++;
}


void DFS(int currentNode, bool* visited,EdgeReverse* edgeReverse , int numEdges) {
    visited[currentNode] = true;

    for (int i = 0; i < numEdges; i++) {
        if ((edgeReverse[i].source == currentNode || edgeReverse[i].destination == currentNode) && edgeReverse[i].weight != -1) {
            int neighbor = (edgeReverse[i].source == currentNode) ? edgeReverse[i].destination : edgeReverse[i].source;
            if (!visited[neighbor]) {
                DFS(neighbor, visited, edgeReverse, numEdges);
            }
        }
    }
   // for(int j=0;j<sizeof(visited);j++)
    //{
      //  printf("visited is:%d\n",visited[j]);
    //}
}
// Function to apply reverse delete algorithm and find the minimum spanning tree
void reverseDelete(GraphReverse * graph) {
    int i, j;
    bool visited[graph->numVertices];

    /*for(int i=0;i<graph->numEdges;i++)
    {
        printf("%d-%d-%d\n",graph->edges[i].source,graph->edges[i].destination,graph->edges[i].weight);
    }*/
    // Sort the edges in descending order based on weight
    for (i = 0; i < graph->numEdges; i++) {
        for (j = i + 1; j < graph->numEdges; j++) {
            if (graph->edges[i].weight < graph->edges[j].weight) {
                // Swap edges
                EdgeReverse temp = graph->edges[i];
                graph->edges[i] = graph->edges[j];
                graph->edges[j] = temp;
            }
        }
    }
    printf("=====================\n");
    /*for(int i=0;i<graph->numEdges;i++)
    {
        printf("%d-%d-%d\n",graph->edges[i].source,graph->edges[i].destination,graph->edges[i].weight);
    }
*/
    printf("Minimum Spanning Tree Edges:\n");
    // Iterate over the sorted edges
    for (i = 0; i < graph->numEdges; i++) {
        // Temporary remove the edge from the graph
        EdgeReverse currentEdge = graph->edges[i];
        graph->edges[i].weight = -1;


        // Check if the graph remains connected after removing the edge
        bool isConnected = true;
        for(int i=0;i<graph->numVertices;i++)
        {
            visited[i] = false;
        }
        DFS(0,visited,graph->edges,graph->numEdges);
        for(int k=0;k<graph->numVertices;k++)
        {
            if(visited[k]==false)
            {
                isConnected = false;
            }
        }
        //printf("is connected:%d\n",isConnected);
        if (!isConnected)
        {
            graph->edges[i].weight=currentEdge.weight;
            //printf MST minimum spanning tree
            printf("%d <--> %d\tWeight: %d\n", graph->edges[i].source, graph->edges[i].destination, graph->edges[i].weight);
        }
    }


}

