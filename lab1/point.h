#ifndef POINT_H
#define POINT_H

#include "action.h"
#include "my_scene.h"
#include "my_stream.h"
#define BUFF_SIZE 100

#include <math.h>
#include <fstream>
#define  N_DIM 4

struct Point {
    double x;
    double y;
    double z;
};

typedef double t_matrix[N_DIM][N_DIM];

typedef double t_vect[N_DIM];

void get_result_matrix(t_matrix a, const Rotate &act);
void get_result_matrix(t_matrix a, const Scale &act);
void get_result_matrix(t_matrix a, const Move &act);

int convert_vec_to_Point(Point &p, const t_vect &vec);
int convert_point_to_vec(t_vect &vec, const Point &p);

int Change_one_point(Point &p, const t_matrix &m_rotate);

int Load_point(Point& p, IN_Stream &stream);

int Save_point(const Point& p, OUT_Stream &stream);

int Draw_line(My_Scene &scene, const Point &a, const Point &b);
#endif // POINT_H
