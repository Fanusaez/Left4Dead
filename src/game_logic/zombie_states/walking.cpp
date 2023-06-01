#include <cmath>
#include "walking.h"
#define X_POS 0
#define Y_POS 1
#define INVALID_POSITION -1
#define WALLS_LIMITS 0.5
#define ERROR_BOUND 0.2
#define MOVEMENTS_PER_CELL 15

Walking::Walking(Zombie* zombie,
                 std::int16_t &x_pos, std::int16_t &y_pos,
                 std::int16_t &x_new_pos, std::int16_t &y_new_pos,
                 GameObject* closest_soldier, GameMap& map,
                 float time) :
                                x_pos(x_pos), // al dope
                                y_pos(y_pos),
                                start_time(start_time - waiting_time_to_walk) {
    chase_soldier(zombie, x_pos, y_pos, x_new_pos, y_new_pos, closest_soldier, map, time);
}

ZombieState* Walking::chase_soldier(Zombie* zombie, // no ocuopa zombie
                            std::int16_t &x_pos,
                            std::int16_t &y_pos,
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

    //std::int16_t x_matrix_sold = closest_soldier->get_x_matrix_pos();
    //std::int16_t y_matrix_sold = closest_soldier->get_y_matrix_pos();
    std::int16_t x_sold = closest_soldier->get_x_pos();
    std::int16_t y_sold = closest_soldier->get_y_pos();
    std::int16_t x_matrix_walker = zombie->get_x_matrix_pos();
    std::int16_t y_matrix_walker = zombie->get_y_matrix_pos();

    bool same_place = true;
    /*
     * Si utilizo x_matrix_sold y x_matrix_walker va a parar de moverse una vez que coincidan
     * las columnas (aunque los bichos no esten totalmente alineados visualmente)
     * Si utilizo las posiciones en pixeles (sin hacer la division " ... / MOV_PER_CEL ")
     * Se van a alinear totalmente. Esto puede traer problemas al querer estar ajustando
     * el movimiento y pasar a atacar despues (creo). Por ahora pongo que se align totalmente
     */
    if (x_sold < x_pos && same_place) { // movimiento para izquierda
        //if (x_pos <= WALLS_LIMITS) return nullptr; por ahora no hay walls limit
        if ((x_pos % MOVEMENTS_PER_CELL) != 0) {
            x_pos -= walker_speed;
            return nullptr;
        }
        map.move_object_left(x_matrix_walker, y_matrix_walker, x_new_pos);
        if (x_new_pos != INVALID_POSITION) {
            same_place = false;
            x_pos -= walker_speed;
        }
    } else if (x_sold > x_pos && same_place) { // movimiento para derecha
        std::int16_t x_new = x_pos + walker_speed;
        if ((x_new % MOVEMENTS_PER_CELL) != 0) {
            x_pos += walker_speed;
            return nullptr;
        }

        map.move_object_right(x_matrix_walker, y_matrix_walker, x_new_pos);
        if (x_new_pos != INVALID_POSITION) {
            same_place = false;
            x_pos += walker_speed;
        }
    }
    if (y_sold > y_pos && same_place) { // movimiento para abajo
        std::int16_t y_new = y_pos + walker_speed;
        if ((y_new % MOVEMENTS_PER_CELL) != 0) {
            y_pos += walker_speed;
            return nullptr;
        }
        map.move_object_down(x_matrix_walker, y_matrix_walker, y_new_pos);
        if (y_new_pos != INVALID_POSITION) {
            same_place = false;
            y_pos += walker_speed;
        }
    } else if (y_sold < y_pos && same_place) { // movimiento para arriba
        //if (y_pos <= WALLS_LIMITS) return nullptr;
        if ((y_pos % MOVEMENTS_PER_CELL) != 0) {
            y_pos -= walker_speed;
            return nullptr;
        }
        map.move_object_up(x_matrix_walker, y_matrix_walker, y_new_pos);
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

ZombieState* Walking::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState* Walking::die(float time) {
    return new ZombieDead(time);
}

bool Walking::time_to_walk(float time) {
    return (time - start_time) >= waiting_time_to_walk;
}

void Walking::set_speed(float speed) {
    walker_speed = speed;
}
