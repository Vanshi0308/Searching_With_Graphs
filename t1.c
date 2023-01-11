#include <stdio.h>
#include <stdlib.h>
#include "t1.h"

static struct node* create_node(int vertex) {
    node* new_node = malloc(sizeof(node));
    if(new_node==NULL) {
        return NULL;
    }
    new_node->vertex = vertex;
    new_node->next = NULL;
    return new_node;
}

static char val2char(int val) {
    if(val<0 || val>25) {
        return -1;
    }
    
    return val+'A';
}

struct Graph* create_graph(int num_nodes) {
    Graph* new_graph = malloc(sizeof(Graph));
    if(new_graph==NULL) {
        return NULL;
    }
    new_graph->num_nodes = num_nodes;
    new_graph->adj_lists = malloc(num_nodes * sizeof(node*));
    if(new_graph->adj_lists==NULL) {
        return NULL;
    }
    for(int i=0; i<num_nodes; i++) {
        new_graph->adj_lists[i] = NULL;
    }
    return new_graph;
}

void add_edge(Graph *g, int from, int to) {
    if(g==NULL) {
        return;
    }
    if(g->num_nodes==0) {
        return;
    }
    if(from < 0 || to < 0 || from >= g->num_nodes || to >= g->num_nodes) {
        return;
    }
    node* new_node = create_node(to);
    new_node->next = g->adj_lists[from];
    g->adj_lists[from] = new_node;
}

struct queue {
    node* front;
    node* rear;
};

void enqueue(struct queue* q, int v) {
    node* ele = create_node(v);
    if(ele==NULL) {
        printf("Not enough space available\n");
        return;
    }
    if(q->front==NULL) {
        q->front = ele;
        q->rear = ele;
    }
    else {
        q->rear->next = ele;
        q->rear = ele;
    }
    return;
}

int dequeue(struct queue* q) {
    if(q->front==NULL) {
        return -1;
    }
    int val;
    node* ptr = q->front;
    val = ptr->vertex;
    q->front = q->front->next;
    free(ptr);
    return val;
}

void bfs(Graph *g, int origin) {
    if(origin<0 || origin >=g->num_nodes) {
        return;
    }
    if(g==NULL) {
        return;
    }
    if(g->num_nodes==0) {
        return;
    }
    struct queue q;
    q.front = NULL;
    q.rear = NULL;
    int* visited = malloc(g->num_nodes * sizeof(int));
    for(int i=0; i<g->num_nodes; i++) {
        visited[i] = 0;
    }
    enqueue(&q, origin);
    visited[origin] = 1;
    int* traversed = malloc(g->num_nodes * sizeof(int));
    int idx = 0;
    while(q.front!=NULL) {
        int cur_vertex = dequeue(&q);
        traversed[idx]  = cur_vertex;
        idx++;
        struct node* tmp = g->adj_lists[cur_vertex];
        while(tmp) {
            if(visited[tmp->vertex]==0) {
                visited[tmp->vertex] = 1;
                enqueue(&q, tmp->vertex);
            }
            tmp = tmp->next;
        }
    }
    printf("BFS: ");
    for(int j=0; j<g->num_nodes; j++) {
        printf("%c ", val2char(traversed[j]));
    }
    printf("\n");
    return;
}

struct stack {
    node* top;
};

void put(struct stack* s, int v) {
    node* ele = create_node(v);
    if(ele==NULL) {
        printf("Not enough space available\n");
        return;
    }
    if(s->top==NULL) {
        s->top = ele;
    }
    else {
        ele->next = s->top;
        s->top = ele; 
    }
    return;
    
}

int pop(struct stack* s) {
    if(s->top==NULL) {
        return -1;
    }
    int val;
    node* ptr = s->top;
    val = ptr->vertex;
    s->top = s->top->next;
    free(ptr);
    return val;
}

void dfs(Graph *g, int origin) {
    if(origin<0 || origin >=g->num_nodes) {
        return;
    }
    if(g==NULL) {
        return;
    }
    if(g->num_nodes==0) {
        return;
    }
    struct stack s;
    s.top = NULL;
    int* visited = malloc(g->num_nodes * sizeof(int));
    for(int i=0; i<g->num_nodes; i++) {
        visited[i] = 0;
    }
    put(&s, origin);
    visited[origin] = 1;
    int* traversed = malloc(g->num_nodes * sizeof(int));
    int idx = 0;
    while(s.top!=NULL){
        int cur_vertex = pop(&s);
        traversed[idx] = cur_vertex;
        idx++;
        struct node* tmp = g->adj_lists[cur_vertex];
        while(tmp) {
            if(visited[tmp->vertex]==0) {
                visited[tmp->vertex] = 1;
                put(&s, tmp->vertex);
            }
            tmp = tmp->next;
        }
    }
    printf("DFS: ");
    for(int j=0; j<g->num_nodes; j++) {
        printf("%c ", val2char(traversed[j]));
    }
    printf("\n");
    return;
}

void delete_graph(Graph *g) {
    if(g==NULL) {
        return;
    }
    if(g->num_nodes==0) {
        free(g);
        return;
    }
    for(int i=0; i<g->num_nodes; i++) {
        while(g->adj_lists[i]!=NULL) {
            node* ptr = g->adj_lists[i];
            g->adj_lists[i] = g->adj_lists[i]->next;
            free(ptr);
        }
    }
    free(g->adj_lists);
    free(g);
}