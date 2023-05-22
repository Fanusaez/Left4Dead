#include "obstacle.h"

void Obstacle::get_position(std::vector<std::int16_t> &pos) {
    pos.push_back(x_pos);
    pos.push_back(y_pos);
}

void Obstacle::set_direction(std::int16_t direction) {}

float Obstacle::get_y_position() {
    return y_pos;
}

void Obstacle::receive_damage(std::uint16_t damage) {

}

bool Obstacle::in_range_of_explosion(std::int16_t x_start,
                                     std::int16_t x_finish,
                                     std::int16_t y_start,
                                     std::int16_t y_finish) {

}


