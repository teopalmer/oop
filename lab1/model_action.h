#ifndef MODEL_ACTION_H
#define MODEL_ACTION_H

#include "action.h"
#include "model.h"
#include "my_scene.h"

Model Init_model();
int Is_init_model(const Model &model);

int rotate_model(Model &model, const Rotate &act);
int scale_model(Model &model, const Scale &act);
int move_model(Model &model, const Move &act);


int load_model(Model &model, const Create &act);
int save_model(const Model &model, const Create &act);

int free_model(Model &model);

int draw_model(My_Scene &scene, const Model &model);

int get_n_vertex(const Model &model);

int get_n_edges(const Model &model);

vertex_arr get_vertex_arr(const Model &model);
//Point* get_vertex_arr(const Model &model);
edges_arr get_edges_arr(const Model &model);
//t_edge* get_edges_arr(const Model &model);

#endif // MODEL_ACTION_H
