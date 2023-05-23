#include <cmath>
#include "walking.h"

#define X_POS 0
#define Y_POS 1
#define INVALID_POSITION -1
#define WALLS_LIMITS 0.5
#define ERROR_BOUND 0.2

Walking::Walking(float &x_pos, float &y_pos) :
    x_pos(x_pos),
    y_pos(y_pos) {}



void Walking::chase_soldier(Zombie* zombie,
                            std::int16_t &x_new_pos,
                            std::int16_t &y_new_pos,
                            GameObject* closest_soldier,
                            GameMap& map) {
    std::vector<float> sold_pos;
    closest_soldier->get_position(sold_pos);
    float x_sold = sold_pos[X_POS];
    float y_sold = sold_pos[Y_POS];

    bool same_place = true;
    /*
    if (x_sold > x_pos && y_sold < y_pos) { // movimiento diagonal derecha arriba
        if (floor(x_pos) == floor(x_pos + walker_speed) && floor(y_pos) == floor(y_pos - walker_speed)) {
            x_pos += walker_speed;
            y_pos -= walker_speed;
            return;
        }
        map.move_diagonally_up_right(floor(x_pos), floor(y_pos), x_new_pos, y_new_pos, same_place);
        if (!same_place) {
            x_pos += walker_speed;
            y_pos -= walker_speed;
        }
    } else if (x_sold < x_pos && y_sold < y_pos) { // movimiento diagonal izquierda arriba
        if (floor(x_pos) == floor(x_pos - walker_speed) && floor(y_pos) == floor(y_pos - walker_speed)) {
            x_pos -= walker_speed;
            y_pos -= walker_speed;
            return;
        }
        map.move_diagonally_up_left(floor(x_pos), floor(y_pos), x_new_pos, y_new_pos, same_place);
        if (!same_place) {
            x_pos -= walker_speed;
            y_pos -= walker_speed;
        }
    } else if (x_sold > x_pos && y_sold > y_pos) { // movimiento diagonal derecha abajo
        if (floor(x_pos) == floor(x_pos + walker_speed) && floor(y_pos) == floor(y_pos + walker_speed)) {
            x_pos += walker_speed;
            y_pos += walker_speed;
            return;
        }
        map.move_diagonally_down_right(floor(x_pos), floor(y_pos), x_new_pos, y_new_pos, same_place);
        if (!same_place) {
            x_pos += walker_speed;
            y_pos += walker_speed;
        }
    } else if (x_sold < x_pos && y_sold > y_pos) { // movimiento diagonal izquierda abajo
        if (floor(x_pos) == floor(x_pos - walker_speed) && floor(y_pos) == floor(y_pos + walker_speed)) {
            x_pos -= walker_speed;
            y_pos += walker_speed;
            return;
        }
        map.move_diagonally_down_left(floor(x_pos), floor(y_pos), x_new_pos, y_new_pos, same_place);
        if (!same_place) {
            x_pos -= walker_speed;
            y_pos += walker_speed;
        }
    }
    */
    if (x_sold < x_pos && (x_pos - x_sold ) >= ERROR_BOUND&& same_place) { // movimiento para izquierda
        if (x_pos <= WALLS_LIMITS) return;
        if (floor(x_pos) == floor(x_pos - walker_speed)) {
            x_pos -= walker_speed;
            return;
        }
        map.move_object_left(floor(x_pos), floor(y_pos), x_new_pos); /// ya no debe llamarse asi
        if (x_new_pos != INVALID_POSITION) {
            same_place = false;
            x_pos -= walker_speed;
        }
    } else if (x_sold > x_pos && (x_sold - x_pos) >= ERROR_BOUND && same_place) { // movimiento para derecha
        if (floor(x_pos) == floor(x_pos + walker_speed)) {
            x_pos += walker_speed;
            return;
        }
        map.move_object_right(floor(x_pos), floor(y_pos), x_new_pos); /// ya no debe llamarse asi
        if (x_new_pos != INVALID_POSITION) {
            same_place = false;
            x_pos += walker_speed;
        }
    }
    if (y_sold > y_pos && (y_sold - y_pos) >= ERROR_BOUND && same_place) { // movimiento para abajo
        if (floor(y_pos) == floor(y_pos + walker_speed)) {
            y_pos += walker_speed;
            return;
        }
        map.move_object_down(floor(x_pos), floor(y_pos), y_new_pos); /// ya no debe llamarse asi
        if (y_new_pos != INVALID_POSITION) {
            same_place = false;
            y_pos += walker_speed;
        }
    } else if (y_sold < y_pos && (y_pos - y_sold) >= ERROR_BOUND && same_place) { // movimiento para arriba
        if (y_pos <= WALLS_LIMITS) return;
        if (floor(y_pos) == floor(y_pos - walker_speed)) {
            y_pos -= walker_speed;
            return;
        }
        map.move_object_up(floor(x_pos), floor(y_pos), y_new_pos); /// ya no debe llamarse asi
        if (y_new_pos != INVALID_POSITION) {
            same_place = false;
            y_pos -= walker_speed;
        }
    }

    if (same_place) { // se quedo trababado por obstaculo, decido que el zombie puede atacar de costado
        //move_soldier_left(floor(x_pos), floor(y_pos), x_new_pos);
    }
}
