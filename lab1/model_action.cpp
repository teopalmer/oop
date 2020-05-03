#include "model_action.h"

#include "point_arr.h"
#include "edges.h"

#include "errors.h"
#include <fstream>
#include <stdlib.h>
#include <iostream>
#include "draw_on_scene.h"

int load_model(Model &model, IN_Stream &stream);

Model Init_model() {
    Model model;
    model.vertex = Init_vertex();
    model.edges = Init_edges();
    return model;
}

int Is_init_model(const Model &model) {
    return get_n_vertex(model);
}

int rotate_model(Model &model, const Rotate &act) {
    return Rotate_point_arr(model.vertex, act); //arr
}

int scale_model(Model &model, const Scale &act)
{
    return Scale_point_arr(model.vertex, act);
}

int  move_model(Model &model, const Move &act)
{
    return Move_point_arr(model.vertex, act);
}

int save_model(const Model &model, const Create &act)
{
    OUT_Stream stream;

    int ret = Open_Stream(stream, act.fileName);

    if (ret)
        return ret;

    ret = save_point_arr(model.vertex, stream);

    if (!ret)
        ret = save_edge_arr(model.edges, stream);

    Close_Stream(stream);
    return ret;

}
int load_model(Model &model, IN_Stream &stream)
{
    int ret = load_point_arr(model.vertex, stream); //arr, error

    int n_v = get_n_vertex(model.vertex);

    if(!ret)
        ret = load_edge_arr(model.edges, stream, n_v); //memory error

    return ret;
}

int load_model(Model &model, const Create &act)
{
    IN_Stream stream;

    int ret = Open_Stream(stream, act.fileName);

    if(ret)
        return ret;

    Model buf;

    ret = load_model(buf, stream);

    Close_Stream(stream);

    if(!ret)
        ret = free_model(model);

    if(!ret)
        model = buf;

    return ret;
}

int free_model(Model &model)
{
    free_edge_arr(model.edges);
    free_point_arr(model.vertex);
    return 0;
}


int draw_model(My_Scene &scene, const Model &model)
{
    int N_e = get_n_edges(model);
    if(!Is_init_model(model))
        return MODEL_EMPTY;
    Clean_Scene(scene);

    int ret = 0;
    for(int i = 0; i < N_e && !ret; i++) {
        int start = get_edge_start(model.edges, i);
        int end = get_edge_end(model.edges, i);
        Point p1 = get_point(model.vertex, start);
        Point p2 = get_point(model.vertex, end);
        ret = Draw_line(scene, p1, p2);
    }
    return ret;
}

int get_n_vertex(const Model &model)
{
    return get_n_vertex(model.vertex);
}

int get_n_edges(const Model &model)
{
    return get_n_edges(model.edges);
}

vertex_arr get_vertex_arr(const Model &model)
{
    return model.vertex;
}

edges_arr get_edges_arr(const Model &model)
{
    return model.edges;
}

