#include "work.h"
#include "model.h"
#include "model_action.h"

int main_controller(My_Scene &scene, const t_action &act, type_action t)
{
    static Model model = Init_model();

    int result = OK;
    switch (t)
    {
    case CREATE:
        result = load_model(model, act.create);
        break;
    case ROTATE:
        result = rotate_model(model, act.rotate);
        break;
    case SCALE:
        result = scale_model(model, act.scale);
        break;
    case MOVE:
        result = move_model(model, act.move);
        break;
    case FREE:
        result = free_model(model);
        break;
    case SAVE:
        result = save_model(model, act.create);
        break;
    case DRAW:
        result = draw_model(scene, model);
        break;
    default:
        result = 4; //
    }
    return result;
}

