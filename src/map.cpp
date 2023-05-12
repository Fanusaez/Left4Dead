#include "map.h"


Map::Map(std::uint16_t x_size, std::uint16_t y_size) :
        x_size(x_size),
        y_size(y_size),
        map(y_size, std::vector<void*>(x_size, 0)) {}




/*
 * Metodos de testeo
 */
void Map::add_soldier(Soldier* soldier,
                      std::uint16_t x_pos,
                      std::uint16_t y_pos) {
    map[y_pos][x_pos] = soldier;
}

void Map::add_zombie(Walker *walker, std::uint16_t x_pos, std::uint16_t y_pos) {
        map[y_pos][x_pos] = walker;
}