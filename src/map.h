#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include "soldier.h"
#include "walker.h"

class GameMap {
 private:
    std::uint16_t x_size;
    std::uint16_t y_size;
    std::vector<std::vector<GameObject*>> map;

 public:
GameMap(std::uint16_t x_size, std::uint16_t y_size);

// ***************************************** Metodos de testeo **********************************************************//
bool collision(std::int16_t direction, std::uint16_t x_pos, std::uint16_t y_pos);
bool collision_going_up(std::uint16_t x_pos, std::uint16_t y_pos);
bool collision_going_down(std::uint16_t x_pos, std::uint16_t y_pos);
void add_soldier(Soldier* soldier, std::uint16_t x_pos, std::uint16_t y_pos);
void add_zombie(Walker* walker, std::uint16_t x_pos, std::uint16_t y_pos);
bool valid_entire_soldier_position(std::int16_t x_pos, std::int16_t y_pos);
};
#endif  // MAP_H_
