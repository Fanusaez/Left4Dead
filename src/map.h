#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include "soldier.h"
#include "walker.h"

class Map {
 private:
    std::uint16_t x_size;
    std::uint16_t y_size;
    std::vector<std::vector<void*>> map;
 public:

Map(std::uint16_t x_size, std::uint16_t y_size);

// ***************************************** Metodos de testeo **********************************************************//
bool collision(std::uint16_t direccion);
void add_soldier(Soldier* soldier, std::uint16_t x_pos, std::uint16_t y_pos);
void add_zombie(Walker* walker, std::uint16_t x_pos, std::uint16_t y_pos);
};
#endif  // MAP_H_
