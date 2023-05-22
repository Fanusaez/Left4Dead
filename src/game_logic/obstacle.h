#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <cstdint>
#include "game_object.h"

class Obstacle : public GameObject{
private:
    std::int16_t x_pos;
    std::int16_t y_pos;

public:
void get_position(std::vector<float>& pos) override;
void receive_damage(std::uint16_t damage) override;
float get_y_position() override;
bool in_range_of_explosion(std::int16_t x_start,
                                       std::int16_t x_finish,
                                       std::int16_t y_start,
                                       std::int16_t y_finish) override;

void set_direction(std::int16_t direction) override;
};

#endif //OBSTACLE_H_
