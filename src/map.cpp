#include <cstdint>
#include <iostream>
#include "map.h"

#define UP -1
#define DOWN 1

GameMap::GameMap(std::uint16_t x_size, std::uint16_t y_size) :
        x_size(x_size),
        y_size(y_size),
        map(y_size, std::vector<GameObject*>(x_size, nullptr)) {}


/*
 * Metodos de testeo
 */

void GameMap::add_soldier(Soldier* soldier,
                      std::uint16_t x_pos,
                      std::uint16_t y_pos) {
    map[y_pos][x_pos] = soldier;
}

void GameMap::add_zombie(Walker *walker, std::uint16_t x_pos, std::uint16_t y_pos) {
        map[y_pos][x_pos] = walker;
}

bool GameMap::collision(std::int16_t direction, std::uint16_t x_pos, std::uint16_t y_pos) {
    if (direction == UP) {
        return collision_going_up(x_pos, y_pos);
    }
    return collision_going_down(x_pos, y_pos);
}

bool GameMap::collision_going_down(std::uint16_t x_pos, std::uint16_t y_pos) {
    for (int i = y_pos; i < y_size; i++) {
        if (map[i][x_pos] != nullptr) {
            return true;
        }
    }
    return false;
}

bool GameMap::collision_going_up(std::uint16_t x_pos, std::uint16_t y_pos) {
    for (int j = y_pos; j >= 0; j--) {
        if (map[j][x_pos] != nullptr) {
            return true;
        }
    }
    return false;
}