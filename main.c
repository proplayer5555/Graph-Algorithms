#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "kruskal.h"
#include "reverse_delete.h"
#include <unistd.h>
#include <string.h>

struct AdjListNode {
    int destination;
    int baros;
    struct AdjListNode* nextlist;
};

// struct for the adjacency list
struct AdjList {
    struct AdjListNode* header; // pointer to head node of list
};

// struct of the graph with a list of adjacency lists and num of Vertices as 'Vertices'
struct Graph {
    int Vertices;
    struct AdjList* list;
};
//orismos synartisewn prim algorithm
struct AdjListNode* newAdjListNode(int destination, int baros);
struct Graph* createGraph(int Vertices);
void addEdge(struct Graph* current_graph, int source, int destination, int baros);
int minKey(int *cost, bool *visited, int Vertices);
void print_minimum_spanning_tree(int *parent, int graphSize, int** graph);
void primMST(struct Graph* graph, int** graphMatrix);
void printGraph(struct Graph* graph);

int main() {

    int numVertices=0, percentageToRemove=0;
    double sum=0,sum2=0,sum3=0;
    double cpu_time_used_for_prim[4];
    double cpu_time_used_for_kruskal[4];
    double cpu_time_used_for_Reverse_delete[4];
    clock_t start1, end1, start2, end2, start3 , end3;

    //setbuf(stdout, 0);
    do{
        printf("Enter the number of nodes: ");
        scanf("%d", &numVertices);
    }while(numVertices<2);

    do
    {
        printf("Enter the percentage of edges to remove: ");
        scanf("%d", &percentageToRemove);
    }while(percentageToRemove>100 || percentageToRemove<0);

    for(int k=0;k<4;k++)
    {
        //create the  struct for each algorithm and initialize the maxEdges=N(N-1)/2,where N is the numVertices
        //int maxEdges=(numVertices*(numVertices-1))/2;
        int numEdges = 0;
        struct Graph *graph = createGraph(numVertices);
        struct GraphKruskal *graphKruskal = createGraphKruskal(numVertices);
        GraphReverse* graphReverse = createGraphReverse(numVertices, numEdges);
        srand(time(NULL));
        sleep(2);
        //double for numvertices*numvertices and random put edges (the same graph for each algorithm)
        for (int i = 0; i < numVertices; ++i) {
            for (int j = i + 1; j < numVertices; ++j) {
                if (rand() % 100 >= percentageToRemove) {
                    int weight1 = rand() % 100 + 1;
                    addEdge(graph, i, j, weight1);//prim
                    addEdgeKruskal(graphKruskal, i, j, weight1);//kruskal
                    addEdgeReverse(graphReverse, i, j, weight1);//Reverse

                }
            }
        }


        // malloc for 2d matrix for the graph
        int **graphMatrix = (int **) malloc(numVertices * sizeof(int *));
        for (int i = 0; i < numVertices; ++i)
            graphMatrix[i] = (int *) malloc(numVertices * sizeof(int));

        for (int i = 0; i < numVertices; ++i) {
            struct AdjListNode *temp = graph->list[i].header;
            while (temp != NULL) {
                graphMatrix[i][temp->destination] = temp->baros;
                temp = temp->nextlist;
            }
        }

        printf("======== Graph#%d ========\n",k+1);
        //printGraph(graph);
        printf("Prim : \n");
        start1 = clock();//αρχίζουμε το clock
        primMST(graph, graphMatrix);
        end1 = clock();//τελειώνουμε το clock
        cpu_time_used_for_prim[k]= (double)(end1 - start1) / (CLOCKS_PER_SEC);//κάνουμε την πράξη για τον χρόνο
        sum = sum + cpu_time_used_for_prim[k];//αποθηκεύουομε τον χρόνο στο sum
        printf("-------------------------------\n");

        printf("Kruskal : \n");
        start2 = clock();//αρχίζουμε το clock
        kruskalMinimun_spanning_tree(graphKruskal);
        end2 = clock();//τελειώνουμε το clock
        cpu_time_used_for_kruskal[k]= (double)(end2 - start2) / (CLOCKS_PER_SEC);//κάνουμε την πράξη για τον χρόνο
        sum2 = sum2 + cpu_time_used_for_kruskal[k];//αποθηκεύουομε τον χρόνο στο sum
        printf("-------------------------------\n");

        printf("Reverse-delete : \n");
        start3 = clock();//αρχίζουμε το clock
        reverseDelete(graphReverse);
        end3 = clock();//τελειώνουμε το clock
        cpu_time_used_for_Reverse_delete[k]= (double)(end3 - start3) / (CLOCKS_PER_SEC);//κάνουμε την πράξη για τον χρόνο
        sum3 = sum3 + cpu_time_used_for_Reverse_delete[k];//αποθηκεύουομε τον χρόνο στο sum
        printf("-------------------------------\n");

        //numVertices = numVertices + 5; //for the next loop make numvertices + onenumber

    }
    for(int q=0;q<4;q++) {
        //printf the time for each loop
        printf("O xronos poy etreje o Prim thn %d fora einai :(prim)%lf ms\n", q + 1, cpu_time_used_for_prim[q]);
        printf("-------------------------------\n");
        printf("O xronos poy etreje o Kruskal thn %d fora einai :(kruskal)%lf ms\n", q + 1, cpu_time_used_for_kruskal[q]);
        printf("-------------------------------\n");
        printf("O xronos poy etreje o Reverse-delete thn %d fora einai :(Reverse-delete)%lf ms\n", q + 1, cpu_time_used_for_Reverse_delete[q]);
        printf("-------------------------------\n");
    }
    //printf the average time of the four loops
    printf("Average time of prim is:(prim)%lf ms\n",sum / (double) 4);//διαιρούμε με το 4 για να βρούμε τον μέσο όρo
    printf("Average time of kruskal is:(kruskal)%lf ms\n",sum2 / (double) 4);//διαιρούμε με το 4 για να βρούμε τον μέσο όρo
    printf("Average time of Reserve delete is:(Reverse-delete)%lf ms\n",sum3 / (double) 4);//διαιρούμε με το 4 για να βρούμε τον μέσο όρo

    return 0;
}
struct AdjListNode* newAdjListNode(int destination, int baros)
{
    struct AdjListNode* newNode_make= (struct AdjListNode*)malloc(sizeof(struct AdjListNode));
    newNode_make->destination = destination;
    newNode_make->baros = baros;
    newNode_make->nextlist = NULL;
    return newNode_make;
}

struct Graph* createGraph(int Vertices) {
    //create graph of with Vertices
    struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
    graph->Vertices = Vertices;
    graph->list = (struct AdjList*)malloc(Vertices * sizeof(struct AdjList));
    //initialize the header of each list to NULL
    for (int i = 0; i < Vertices; ++i)
        graph->list[i].header = NULL;
    //return the graph
    return graph;
}


void addEdge(struct Graph* current_graph, int source, int destination, int baros)
{
    // addedge to andirected graph, addEdge has graph, source,destination,baros
    struct AdjListNode* newNode_make= newAdjListNode(destination, baros);
    newNode_make->nextlist = current_graph->list[source].header;
    current_graph->list[source].header = newNode_make;

    //as long as it is undirected add edge from destination to source also
    newNode_make = newAdjListNode(source, baros);
    newNode_make->nextlist = current_graph->list[destination].header;
    current_graph->list[destination].header = newNode_make;
}

// Function to find the vertex with the minimum cost value
int minKey(int *cost, bool *visited, int Vertices) {
    int min = INT_MAX;// initialize min to the biggest int number limits.h
    int min_vertex_ID; //minimun value of the smallest vertex

    for (int i = 0; i < Vertices; ++i)
    {
        //if we haven't visited the node & it is false and if it is smaller than mininum update the minimun_index_ID
        if (visited[i] == false && cost[i] < min)
        {
            min = cost[i];
            min_vertex_ID = i;
        }
    }

    return min_vertex_ID;
}


void print_minimum_spanning_tree(int *parent, int graphSize, int** graph) {
    printf("The algorithm with the Adjacency Lists gives the following minimum spanning tree:\n");
    //printf the minimum spanning tree of prim algorithm
    for (int j = 1; j < graphSize; ++j)
    {
        //undirected graph
        printf("%d <--> %d :weight: %d\n", parent[j], j, graph[j][parent[j]]);
    }
}


void primMST(struct Graph* graph, int** graphMatrix){
    int VerticesNumber = graph->Vertices;
    int parent[VerticesNumber];
    int cost[VerticesNumber];//matrix for the cost of each size:VerticesNumber
    bool visited[VerticesNumber];//matrix for the visited and unvisited nodes of the prim algorithm size:VerticesNumber

    //initialize with a for the size VerticesNumber the cost to INT_MAX and do all things in visited false as we haven't
    //visited anything by this moment
    for (int v = 0; v < VerticesNumber; ++v)
    {
        cost[v] = INT_MAX;
        visited[v] = false;
    }

    cost[0] = 0;//include the first vertex
    parent[0] = -1;  // the first node is the root

    for (int count = 0; count < VerticesNumber - 1; ++count)
    {
        int u = minKey(cost, visited, VerticesNumber);

        visited[u] = true;

        struct AdjListNode* temp = graph->list[u].header;
        while (temp != NULL)
        {
            int v = temp->destination;
            int weight = temp->baros;

            if (visited[v] == false && weight < cost[v])
            {
                parent[v] = u;
                cost[v] = weight;
            }
            temp = temp->nextlist;
        }
    }

    print_minimum_spanning_tree(parent, VerticesNumber, graphMatrix);
}
void printGraph(struct Graph* graph) {
    //function to printf the graph if we want
    for (int v = 0; v < graph->Vertices; ++v)
    {
        struct AdjListNode* temp = graph->list[v].header;
        while (temp) {
            printf("Node %d: %d->%d W: %d\n", v, v, temp->destination, temp->baros);
            temp = temp->nextlist;
        }
    }
}


