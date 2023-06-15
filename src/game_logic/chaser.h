#ifndef CHASER_H
#define CHASER_H

#include <cstdint>
#include "zombies/zombie.h"
class GameMap;


class Chaser {
private:
    std::int16_t& x_pos;
    std::int16_t& y_pos;
    Zombie* zombie;
    GameMap& map;
    const std::int16_t zombie_speed = 1;

    void move_right(bool& same_place);
    void move_left(bool& same_place);
    void move_up(bool& same_place);
    void move_down(bool& same_place);
    bool too_close_to_move(std::int16_t x_pos_chase, std::int16_t y_pos_chase);
public:

    Chaser(Zombie* zombie, GameMap& map, std::int16_t& x_pos, std::int16_t& y_pos);

    void chase(std::int16_t x_pos_chase, std::int16_t y_pos_chase);
};


#endif  // CHASER_H
