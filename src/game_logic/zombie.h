#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include <vector>
#include "game_object.h"

class GameMap;


class Zombie {

public:
virtual void chase_closest_soldier(GameMap& map, std::vector<GameObject*> soldiers) = 0;
virtual bool in_range_of_explosion(std::int16_t x_start,
                                   std::int16_t x_finish,
                                   std::int16_t y_start,
                                   std::int16_t y_finish) = 0;
virtual void get_position(std::vector<std::int16_t>& pos) = 0;
virtual void set_direction(std::int16_t direction) = 0;
virtual void attack(GameMap& map, std::vector<GameObject*> soldiers) = 0;
};
#endif   // ZOMBIE_H_
