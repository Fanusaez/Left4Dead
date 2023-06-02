#ifndef CHASER_H
#define CHASER_H

//#include "zombie.h"
#include "map.h"

class Chaser {
private:
    std::int16_t& x_pos;
    std::int16_t& y_pos;
    Zombie* zombie;
    GameMap& map;
    const std::int16_t walker_speed = 1;

public:

    Chaser(Zombie* zombie, GameMap& map, std::int16_t& x_pos, std::int16_t& y_pos);

    void chase(std::int16_t x_pos_chase, std::int16_t y_pos_chase);
};


#endif  // CHASER_H
