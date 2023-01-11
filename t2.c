#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "t2.h"

static char val2char(int val) {
    if(val<0 || val>25) {
        return -1;
    }
    
    return val+'A';
}

Graph* create_graph(int num_nodes) {
    Graph* g = malloc(sizeof(Graph));
    if(g==NULL) {
        return NULL;
    }
    g->num_nodes =  num_nodes;
    for(int i=0; i<num_nodes; i++) {
        for(int j=0; j<num_nodes; j++) {
            g->adj_matrix[i][j] = 0;
        }
    }
    return g;
}

void add_edge(Graph *g, int from, int to, int weight) {
    if(g==NULL) {
        return;
    }
    if(g->num_nodes==0) {
        return;
    }
    if(from < 0 || to < 0 || from >= g->num_nodes || to >= g->num_nodes) {
        return;
    }
    if(from == to && weight!=0) {
        return;
    }
    g->adj_matrix[from][to] = weight;
    g->adj_matrix[to][from] = weight;
    return;
}

int find_min_dist_vertex(int v[], int d[], int length) {
    int min_val = INT_MAX;
    int min_vertex = INT_MAX;
    for(int i=0; i<length; i++) {
        if(d[i]<min_val && v[i]==0) {
            min_val = d[i];
            min_vertex = i;
        }
        else if(d[i]==min_val && min_val!=INT_MAX && v[i]==0) {
            if(i<min_vertex) {
                min_vertex = i;
            }
        }
    }
    return min_vertex;
}

void dijkstra(Graph *g, int origin) {
    if(origin < 0 || origin >= g->num_nodes) {
        return;
    }
    int* visited = malloc(g->num_nodes * sizeof(int));
    int* pred = malloc(g->num_nodes * sizeof(int));
    int* dist = malloc(g->num_nodes * sizeof(int));

    // Initializtion steps to set predecessor array, visited and distance arrays
    for(int i=0; i<g->num_nodes; i++) {
        visited[i] = 0;
        pred[i] = -1;
        dist[i] = INT_MAX;
    }
    dist[origin] = 0;
    for(int i=0; i<g->num_nodes; i++) {
        int min_node = find_min_dist_vertex(visited, dist, g->num_nodes);
        visited[min_node] = 1;
        printf("%c ", val2char(min_node));
        for(int j=0; j<g->num_nodes; j++) {
            if(g->adj_matrix[min_node][j]!=0) {
                if((dist[j] > dist[min_node] + g->adj_matrix[min_node][j]) && visited[j]==0){
                    dist[j] = dist[min_node] + g->adj_matrix[min_node][j];
                    pred[j] = min_node;
                }
            }
        }
    }
    printf("\n");
    for(int i=0; i<g->num_nodes; i++) {
        printf("The length of the shortest path between %c and %c is %d\n", val2char(origin), val2char(i), dist[i]);
    }
}

void delete_graph(Graph *g) {
    if(g==NULL) {
        return;
    }
    free(g);
    return;
}