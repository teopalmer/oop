#ifndef POINT_ARR_H
#define POINT_ARR_H
#include "point.h"

struct vertex_arr {
    Point *arr = NULL;
    int n_v = 0;
};

vertex_arr Init_vertex();
//преобразование массива точек
int Rotate_point_arr(vertex_arr &vert, const Rotate &act);
int Scale_point_arr(vertex_arr &vertex, const Scale &act);
int Move_point_arr(vertex_arr &vertex, const Move &act);

//загрузка массива точек опр. длины из файла
int load_point_arr(vertex_arr &vertex, IN_Stream &stream);

int allocate_point_arr(vertex_arr &vertex);
int free_point_arr(vertex_arr &vertex);

//запись массива точек в файл
int save_point_arr(const vertex_arr &vertex, OUT_Stream &stream);

int get_n_vertex(const vertex_arr &vertex);

Point get_point(const vertex_arr &vertex, int i);

Point* get_vertex_arr(const vertex_arr &vertex);

#endif // POINT_ARR_H
