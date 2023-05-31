#include "obstacle.h"

Obstacle::Obstacle(std::int16_t x_pos, std::int16_t y_pos, std::int16_t id) :
        x_pos(x_pos),
        y_pos(y_pos),
        id(id) {}

void Obstacle::get_position(std::vector<float> &pos) {
    pos.push_back(x_pos);
    pos.push_back(y_pos);
}

void Obstacle::set_direction(std::int16_t direction) {}

float Obstacle::get_y_position() {
    return y_pos;
}

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
