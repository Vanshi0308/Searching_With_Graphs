#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "t3.h"

// Array for storing the serial number of vertices corresponding to the stop_id
node *vertices[1000];
int s_no = 0;
int num_edges = 0;

struct node* create_node(int id, char* name, long double lati, long double longi) {
    node* new_node = malloc(sizeof(node));
    if(new_node==NULL) {
        return NULL;
    }
    new_node->stop_no = s_no;
    s_no++;
    new_node->stop_id = id;
    new_node->stop_name = name;
    new_node->lat = lati;
    new_node->lon = longi;
    return new_node;
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

int load_vertices(char *fname) {
    FILE *f = fopen(fname, "r");
    if(f==NULL) {
        return 0;
    }
    for(int i=0; i<1000; i++) {
        vertices[i] = NULL;
    }
    char line[250];
    //Discarding the header before running the loop
    fgets(line, sizeof(line), f);
    while(fgets(line, sizeof(line), f)) {
        int tok_ctr = 0;
        int id;
        char *name;
        long double lati, longi;
        char *token;
        token = strtok(line, ",");
        while(token!=NULL && tok_ctr<4) {
            if(tok_ctr==0) {
                id = strtol(token, NULL, 10);
                if(s_no==0) {
                    printf("%s\n", token);
                    printf("%d\n", id);
                }
            }
            else if(tok_ctr==1) {
                name = token;
                if(s_no==0) {
                    printf("%s\n", name);
                }
            }
            else if(tok_ctr==2) {
                lati = strtold(token, NULL);
                if(s_no==0) {
                    printf("%s\n", token);
                    printf("%Lf\n", lati);
                }
            }
            else if(tok_ctr==3) {
                longi = strtold(token, NULL);
                if(s_no==0) {
                    printf("%s\n", token);
                    printf("%Lf\n", longi);
                }
            }
            token = strtok(NULL, ",");
            tok_ctr++;
        }
        node* ptr = create_node(id, name, lati, longi);
        if(ptr==NULL) {
            return 0;
        }
        // Storing the reference to node corresponsing to the id
        vertices[id] = ptr;
    }
    printf("Loaded %d vertices\n", s_no);
    printf("Vertex 2: %s %Lf %Lf", vertices[2]->stop_name, vertices[2]->lat, vertices[2]->lon);
    return 1;
}

int load_edges(char *fname) {
    FILE *f = fopen(fname, "r");
    if(f==NULL) {
        return 0;
    }
    Graph* g = create_graph(s_no);
    if(g==NULL) {
        return 0;
    }
    char line[40];
    //Discarding the header before running the loop
    fgets(line, sizeof(line), f);
    while(fgets(line, sizeof(line), f)) {
        int tok_ctr = 0;
        int from, to, dist;
        char *token;
        token = strtok(line, ",");
        while(token!=NULL && tok_ctr<3) {
            if(tok_ctr==0) {
                from = strtol(token, NULL, 10);
            }
            else if(tok_ctr==1) {
                to = strtol(token, NULL, 10);
            }
            else if(tok_ctr==2) {
                dist = strtol(token, NULL, 10);
            }
            token = strtok(NULL, ",");
            tok_ctr++;
        }
        g->adj_matrix[vertices[from]->stop_no][vertices[to]->stop_no] = dist;
        g->adj_matrix[vertices[to]->stop_no][vertices[from]->stop_no] = dist;
        num_edges++;
    }
    printf("Loaded %d edges\n", num_edges);
    printf("Third edge: %d", g->adj_matrix[vertices[10]->stop_no][vertices[18]->stop_no]);
    return 1;
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

int visited[MAX_VERTICES];
int pred[MAX_VERTICES];
int dist[MAX_VERTICES];

void dijkstra(Graph *g, int origin) {
    if(origin < 0 || origin >= g->num_nodes) {
        return;
    }

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
        for(int j=0; j<g->num_nodes; j++) {
            if(g->adj_matrix[min_node][j]!=0) {
                if((dist[j] > dist[min_node] + g->adj_matrix[min_node][j]) && visited[j]==0){
                    dist[j] = dist[min_node] + g->adj_matrix[min_node][j];
                    pred[j] = min_node;
                }
            }
        }
    }
    return;
}

void shortest_path(int startNode, int endNode) {
    return;
}

void free_memory() {
    free(vertices);
}