#include "chaser.h"
#include "map.h"

#define INVALID_POSITION -1
#define WALLS_LIMITS 0.5
#define MOVEMENTS_PER_CELL 2
#define LEFT 2
#define RIGHT 3


Chaser::Chaser(Zombie *zombie, GameMap& map, std::int16_t& x_pos, std::int16_t& y_pos) :
                x_pos(x_pos),
                y_pos(y_pos),
                zombie(zombie),
                map(map) {}

void Chaser::chase(std::int16_t x_pos_chase, std::int16_t y_pos_chase) {
    bool same_place = true;
    if (y_pos_chase > y_pos && same_place) { // movimiento para abajo
        move_down(same_place);
    } else if (y_pos_chase < y_pos && same_place) { // movimiento para arriba
        move_up(same_place);
    }

    if (x_pos_chase < x_pos && same_place) { // movimiento para izquierda
        move_left(same_place);
    } else if (x_pos_chase > x_pos && same_place) { // movimiento para derecha
        move_right(same_place);
    }

    if (too_close_to_move(x_pos_chase, y_pos_chase)) {
        return;
    }

    if (same_place) { // para escapar de pos bloqueada
        if (y_pos % MOVEMENTS_PER_CELL == 0) {
            move_up(same_place);
        } else {
            move_down(same_place);
        }
        if (x_pos_chase < x_pos) {
            move_left(same_place);
        } else {
            move_right(same_place);
        }
    }
}

void Chaser::move_down(bool &same_place) {
    std::int16_t x_matrix_walker = zombie->get_x_matrix_pos();
    std::int16_t y_matrix_walker = zombie->get_y_matrix_pos();
    std::int16_t y_new_pos = INVALID_POSITION;

    std::int16_t y_new = y_pos + zombie_speed;
    if ((y_new % MOVEMENTS_PER_CELL) != 0) {
        y_pos += zombie_speed;
        same_place = false;
        return;
    }
    map.move_object_down(x_matrix_walker, y_matrix_walker, y_new_pos);
    if (y_new_pos != INVALID_POSITION) {
        y_pos += zombie_speed;
        same_place = false;
    }
}

void Chaser::move_up(bool &same_place) {
    std::int16_t x_matrix_walker = zombie->get_x_matrix_pos();
    std::int16_t y_matrix_walker = zombie->get_y_matrix_pos();
    std::int16_t y_new_pos = INVALID_POSITION;

    if ((y_pos % MOVEMENTS_PER_CELL) != 0) {
        y_pos -= zombie_speed;
        same_place = false;
        return;
    }
    map.move_object_up(x_matrix_walker, y_matrix_walker, y_new_pos);
    if (y_new_pos != INVALID_POSITION) {
        same_place = false;
        y_pos -= zombie_speed;
    }
}

void Chaser::move_right(bool &same_place) {
    std::int16_t x_matrix_walker = zombie->get_x_matrix_pos();
    std::int16_t y_matrix_walker = zombie->get_y_matrix_pos();
    std::int16_t x_new_pos = INVALID_POSITION;

    zombie->set_direction(RIGHT);
    std::int16_t x_new = x_pos + zombie_speed;
    if ((x_new % MOVEMENTS_PER_CELL) != 0) {
        x_pos += zombie_speed;
        same_place = false;
        return;
    }
    map.move_object_right(x_matrix_walker, y_matrix_walker, x_new_pos);
    if (x_new_pos != INVALID_POSITION) {
        same_place = false;
        x_pos += zombie_speed;
    }
}

void Chaser::move_left(bool &same_place) {
    std::int16_t x_matrix_walker = zombie->get_x_matrix_pos();
    std::int16_t y_matrix_walker = zombie->get_y_matrix_pos();
    std::int16_t x_new_pos = INVALID_POSITION;

    zombie->set_direction(LEFT);
    if ((x_pos % MOVEMENTS_PER_CELL) != 0) {
        x_pos -= zombie_speed;
        same_place = false;
        return;
    }
    map.move_object_left(x_matrix_walker, y_matrix_walker, x_new_pos);
    if (x_new_pos != INVALID_POSITION) {
        same_place = false;
        x_pos -= zombie_speed;
    }
}

bool Chaser::too_close_to_move(std::int16_t x_pos_chase, std::int16_t y_pos_chase) {
    if (abs(x_pos_chase - x_pos) <= MOVEMENTS_PER_CELL && abs(y_pos_chase - y_pos) == 0) return true;
    return false;
}