#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <cstdint>
#include "game_object.h"

class Obstacle : public GameObject{
private:
    std::int16_t x_pos;
    std::int16_t y_pos;
    const std::int16_t id;

public:

Obstacle(std::int16_t x_pos, std::int16_t y_pos, std::int16_t id);

void receive_damage(std::uint16_t damage, float time) override;
bool in_range_of_explosion(std::int16_t x_start,
                                       std::int16_t x_finish,
                                       std::int16_t y_start,
                                       std::int16_t y_finish) override;

void set_direction(std::int16_t direction) override;

std::int16_t get_y_pos() override;
std::int16_t get_x_pos() override;
std::int16_t get_y_matrix_pos() override;
std::int16_t get_x_matrix_pos() override;


std::int16_t get_id() override;
};

#endif //OBSTACLE_H_
