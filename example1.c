/*Determinati daca exista sau nu drum direct intre doua restaurante dintr-o retea de tip graf*/

#include <stdlib.h>
#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct Graph {
    int num_vertices;
    int *visited;
    Node **adj_lists;
} Graph;

typedef struct Stack {
    int top;
    int capacity;
    int *array;
} Stack;

/// pentru simplitate, folosim int uri pt a numi restaurantel/locatiile
/// ex: 1 - restaurantul 1 si tot asa

Node *create_node(int vertex_value) {
    Node *new_node = malloc(sizeof(Node));
    new_node->data = vertex_value;
    new_node->next = NULL;
    return new_node;
}

void add_edge(Graph *graph, int source_vertex, int destination_vertex) {
    Node *new_node_to_dest = create_node(destination_vertex);
    new_node_to_dest->next = graph->adj_lists[source_vertex];
    graph->adj_lists[source_vertex] = new_node_to_dest;

    Node *new_node_to_src = create_node(source_vertex);
    new_node_to_src->next = graph->adj_lists[destination_vertex];
    graph->adj_lists[destination_vertex] = new_node_to_src;
}

Graph *create_graph(int num_vertices_param) {
    Graph *graph = malloc(sizeof(Graph));
    graph->num_vertices = num_vertices_param;
    graph->adj_lists = malloc(sizeof(Node *) * num_vertices_param);
    graph->visited = malloc(sizeof(int) * num_vertices_param);

    for (int i = 0; i < num_vertices_param; i++)
    {
        graph->adj_lists[i] = NULL;
        graph->visited[i] = 0;
    }
    return graph;
}

Stack *create_stack(int stack_capacity) {
    Stack *stack = malloc(sizeof(Stack));
    stack->array = malloc(stack_capacity * sizeof(int));
    stack->top = -1;
    stack->capacity = stack_capacity;
    return stack;
}

void push(int value_to_push, Stack *stack) {
    stack->top = stack->top + 1;
    stack->array[stack->top] = value_to_push;
}

void DFS(Graph *graph, Stack *stack, int start_vertex) {
    Node *adj_list = graph->adj_lists[start_vertex];
    Node *current_neighbor_node = adj_list;
    graph->visited[start_vertex] = 1;
    printf("%d ", start_vertex);
    push(start_vertex, stack);

    while (current_neighbor_node != NULL) {
        int neighbor_vertex = current_neighbor_node->data;
        if (graph->visited[neighbor_vertex] == 0) {
            DFS(graph, stack, neighbor_vertex);
        }
        current_neighbor_node = current_neighbor_node->next;
    }
}

void insert_edges(Graph *graph, int num_edges_to_add, int total_vertices) {
    int source, destination, i;
    printf("adauga %d muchii (nodurile sunt indexate de la 0 la %d)\n", num_edges_to_add, total_vertices - 1);
    for (i = 0; i < num_edges_to_add; i++) {
         printf("Muchia %d: ", i + 1);
        if (scanf("%d%d", &source, &destination) == 2) {
             add_edge(graph, source, destination);
        } else {
             printf("Input invalid. Sarim peste aceasta muchie.\n");
             while(getchar() != '\n');
             i--;
        }
    }
}

void reset_visited_flags(Graph *graph, int num_vertices_local) {
    for (int i = 0; i < num_vertices_local; i++) {
        graph->visited[i] = 0;
    }
}

void check_complex_condition(Graph *graph, int num_vertices_local, Stack *stack1, Stack *stack2) {
    int found_flag = 0;

    for (int i = 0; i < num_vertices_local; i++)
    {
        for (int j = 0; j < 5 && j < num_vertices_local; j++)
        {
            reset_visited_flags(graph, num_vertices_local);
            DFS(graph, stack1, i);

            reset_visited_flags(graph, num_vertices_local);
            DFS(graph, stack2, j);

            for (int k = 0; k < num_vertices_local && !found_flag; k++)
            {
                for (int l = 0; l < num_vertices_local && !found_flag; l++)
                {
                     if (k <= stack2->top && l <= stack1->top) {
                        if ((stack1->array[l] == j) && (stack2->array[k] == i)) {
                            found_flag = 1;
                        }
                     } else {
                         break;
                     }
                }
                 if (k > stack2->top) {
                     break;
                 }
            }
        }
    }
}


int main() {
    int vertex_count;
    int edge_count;
    int main_ans;

    printf("cate noduri are graful? ");
    scanf("%d", &vertex_count);

    printf("cate muchii are graful? ");
    scanf("%d", &edge_count);

    Graph *main_graph = create_graph(vertex_count);

    Stack *main_stack1 = create_stack(2 * vertex_count);
    Stack *main_stack2 = create_stack(2 * vertex_count);

    insert_edges(main_graph, edge_count, vertex_count);

    check_complex_condition(main_graph, vertex_count, main_stack1, main_stack2);

    return 0;
}