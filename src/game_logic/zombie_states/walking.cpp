#include <cmath>
#include "walking.h"

#define X_POS 0
#define Y_POS 1
#define INVALID_POSITION -1
#define WALLS_LIMITS 0.5
#define ERROR_BOUND 0.2

Walking::Walking(Zombie* zombie,
                 float &x_pos, float &y_pos,
                 std::int16_t &x_new_pos, std::int16_t &y_new_pos,
                 GameObject* closest_soldier, GameMap& map,
                 float time) :
                                x_pos(x_pos),
                                y_pos(y_pos),
                                start_time(start_time) {
    chase_soldier(zombie, x_pos, y_pos, x_new_pos, y_new_pos, closest_soldier, map, time + waiting_time_to_walk);
    // esto esta mal, al otro llamado el tiempo va a estar adelantado, buscar la manera de mover el walker sin ahcer esto
}

ZombieState* Walking::chase_soldier(Zombie* zombie,
                            float &x_pos,
                            float &y_pos,
                            std::int16_t &x_new_pos,
                            std::int16_t &y_new_pos,
                            GameObject* closest_soldier,
                            GameMap& map,
                            float time) {

    if (time_to_walk(time)) {
        start_time = time;
    } else {
        return nullptr;
    }

    std::vector<float> sold_pos;
    closest_soldier->get_position(sold_pos);
    float x_sold = sold_pos[X_POS];
    float y_sold = sold_pos[Y_POS];

    bool same_place = true;

    if (x_sold < x_pos && (x_pos - x_sold ) >= ERROR_BOUND && same_place) { // movimiento para izquierda
        if (x_pos <= WALLS_LIMITS) return nullptr;
        if (floor(x_pos) == floor(x_pos - walker_speed)) {
            x_pos -= walker_speed;
            return nullptr;
        }
        map.move_object_left(floor(x_pos), floor(y_pos), x_new_pos); /// ya no debe llamarse asi
        if (x_new_pos != INVALID_POSITION) {
            same_place = false;
            x_pos -= walker_speed;
        }
    } else if (x_sold > x_pos && (x_sold - x_pos) >= ERROR_BOUND && same_place) { // movimiento para derecha
        if (floor(x_pos) == floor(x_pos + walker_speed)) {
            x_pos += walker_speed;
            return nullptr;
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
            return nullptr;
        }
        map.move_object_down(floor(x_pos), floor(y_pos), y_new_pos); /// ya no debe llamarse asi
        if (y_new_pos != INVALID_POSITION) {
            same_place = false;
            y_pos += walker_speed;
        }
    } else if (y_sold < y_pos && (y_pos - y_sold) >= ERROR_BOUND && same_place) { // movimiento para arriba
        if (y_pos <= WALLS_LIMITS) return nullptr;
        if (floor(y_pos) == floor(y_pos - walker_speed)) {
            y_pos -= walker_speed;
            return nullptr;
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
    return nullptr;
}

ZombieState* Walking::attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) {
    if (!time_to_walk(time)) return nullptr;
    return new Attacking(closest_soldier, damage, time);
}

bool Walking::time_to_walk(float time) {
    return (time - start_time) >= waiting_time_to_walk;
}

void Walking::set_speed(float speed) {
    walker_speed = speed;
}
