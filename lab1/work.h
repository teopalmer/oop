#ifndef WORK_H
#define WORK_H

#include "action.h"
#include "my_scene.h"
#include "errors.h"
#include "model.h"

enum type_action { ROTATE, CREATE, MOVE, SCALE, FREE, SAVE, DRAW };

union t_action {
    Rotate rotate;
    Scale scale;
    Create create;
    Move move;
    bool free;
};

int main_controller(My_Scene &scene, const t_action &act, type_action t);

#endif // WORK_H
