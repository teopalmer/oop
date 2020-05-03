#ifndef EDGES_H
#define EDGES_H
#include "my_stream.h"

typedef int t_edge[2];

struct edges_arr {
    t_edge *arr = NULL;
    int N_e = 0;
};

edges_arr Init_edges();

int load_edge_arr(edges_arr &edges, IN_Stream &stream, int max_vertex);
int Load_edge(t_edge& p, IN_Stream &stream, int max_vertex);
int allocate_edge_arr(edges_arr &edges);
int free_edge_arr(edges_arr &edges);

int save_edge_arr(const edges_arr &edges, OUT_Stream &stream);
int Save_edge(const t_edge& p, OUT_Stream &stream);

int get_n_edges(const edges_arr & edges);

int get_edge_start(const edges_arr &edges, int i);
int get_edge_end(const edges_arr &edges, int i);

t_edge* get_edges_arr(const edges_arr &edges);

#endif // EDGES_H
