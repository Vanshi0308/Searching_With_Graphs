#ifndef T3_H_
#define T3_H_

typedef struct node{
    int stop_no;
    int stop_id;
    char *stop_name;
    long double lat;
    long double lon;
}node;

#define MAX_VERTICES 4806
typedef struct Graph{
    int num_nodes;
    int adj_matrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

int load_edges ( char *fname ); //loads the edges from the CSV file of name fname
int load_vertices ( char *fname );  //loads the vertices from the CSV file of name fname
void shortest_path(int startNode, int endNode); // prints the shortest path between startNode and endNode, if there is any
void free_memory ( void ) ; // frees any memory that was used

#endif