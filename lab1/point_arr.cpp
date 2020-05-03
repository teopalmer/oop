#include "point_arr.h"
#include "errors.h"

vertex_arr Init_vertex() {
    vertex_arr vertex;
    vertex.arr = NULL;
    vertex.n_v = 0;
    return vertex;
}

int load_point_arr(vertex_arr &vertex, IN_Stream &stream)
{
    int N;
    int ret = Read_Stream(N, stream);
    if(ret) {
        return ret;
    }
    vertex.n_v = N;
    ret = allocate_point_arr(vertex); // n in

    for(int i = 0; i < N && !ret; i++) {
        ret = Load_point(vertex.arr[i], stream);
    }
    if(ret) {
        free_point_arr(vertex);
    }
    return ret;
}

int allocate_point_arr(vertex_arr &vertex) {
    vertex.arr = new Point [vertex.n_v];
    if(!(vertex.arr))
        return MEMORY_ERROR;
    return 0;
}
int free_point_arr(vertex_arr &vertex) {
    if (vertex.arr)
        delete[] vertex.arr;
    vertex.arr = NULL;
    vertex.n_v = 0;
    return 0;
}
int save_point_arr(const vertex_arr &vertex, OUT_Stream &stream)
{
    char buff[BUFF_SIZE];
    snprintf(buff, BUFF_SIZE, "%d\n", vertex.n_v);
    int ret = Print_Stream(stream, buff);

    for(int i = 0; i < vertex.n_v && !ret; i++)
    {
        ret = Save_point(vertex.arr[i], stream);
    }
    return ret;
}

int Rotate_point_arr(vertex_arr &vertex, const Rotate &act)
{
    if (!vertex.arr)
        return MODEL_EMPTY;

    t_matrix m;
    get_result_matrix(m, act);

    int ret = 0;
    for (int i = 0; i < vertex.n_v && !ret; ++i)
    {
        ret = Change_one_point(vertex.arr[i], m);
    }
   return ret;
}
int Scale_point_arr(vertex_arr &vertex, const Scale &act)
{
    if (!vertex.arr)
        return MODEL_EMPTY;

    t_matrix m;
    get_result_matrix(m, act);
    int ret = 0;

    for (int i = 0; i < vertex.n_v && !ret; ++i)
    {
        ret = Change_one_point(vertex.arr[i], m);
    }
    return ret;
}

int Move_point_arr(vertex_arr &vertex, const Move &act)
{
    if (!vertex.arr)
        return MODEL_EMPTY;

    t_matrix m;
    get_result_matrix(m, act);
    int ret = 0;

    for (int i = 0; i < vertex.n_v && !ret; ++i)
    {
        ret = Change_one_point(vertex.arr[i], m);
    }
    return ret;
}

int get_n_vertex(const vertex_arr &vertex) {
    return vertex.n_v;
}

Point get_point(const vertex_arr &vertex, int i) {
    return vertex.arr[i];
}
Point* get_vertex_arr(const vertex_arr &vertex) {
    return vertex.arr;
}

