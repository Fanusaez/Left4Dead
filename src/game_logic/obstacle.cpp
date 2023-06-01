#include "obstacle.h"

#define MOVEMENTS_PER_CELL 15

Obstacle::Obstacle(std::int16_t x_pos, std::int16_t y_pos, std::int16_t id) :
        x_pos(x_pos * MOVEMENTS_PER_CELL),
        y_pos(y_pos * MOVEMENTS_PER_CELL),
        id(id) {}


void Obstacle::set_direction(std::int16_t direction) {}



void Obstacle::receive_damage(std::uint16_t damage, float time) {

}

bool Obstacle::in_range_of_explosion(std::int16_t x_start,
                                     std::int16_t x_finish,
                                     std::int16_t y_start,
                                     std::int16_t y_finish) {

}

std::int16_t Obstacle::get_id() {
    return id;
}

std::int16_t Obstacle::get_y_pos() {
    return y_pos;
}

std::int16_t Obstacle::get_x_pos() {
    return x_pos;
}

std::int16_t Obstacle::get_y_matrix_pos() {
    return y_pos / MOVEMENTS_PER_CELL;
}

std::int16_t Obstacle::get_x_matrix_pos() {
    return x_pos / MOVEMENTS_PER_CELL;
}