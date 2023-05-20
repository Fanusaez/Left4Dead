#include "walking.h"

void Walking::chase_soldier(Zombie* zombie,
                            std::int16_t &x_new_pos,
                            std::int16_t &y_new_pos,
                            GameObject* closest_soldier,
                            GameMap& map) {
    map.chase_soldier_walking(zombie, x_new_pos, y_new_pos, closest_soldier);
}