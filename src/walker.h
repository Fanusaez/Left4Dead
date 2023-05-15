#ifndef WALKER_H_
#define WALKER_H_

#include <cstdint>
#include "game_object.h"


class Walker : public GameObject {
 private:
    std::uint16_t health = 100;
    std::uint16_t x_pos;
    std::uint16_t y_pos;
    bool dead = false;

 public:
Walker(std::uint16_t x_pos, std::uint16_t y_pos);

void get_shot(std::uint16_t damage) override;
std::uint16_t get_y_position() override;
void move_up() override;
// ************************* Metodos de testeo ************************************************8//
 std::uint16_t get_health();
};

#endif  // WALKER_H_
