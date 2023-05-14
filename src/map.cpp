#include <cstdint>
#include <iostream>
#include "map.h"

#define UP -1
#define DOWN 1
#define X_POS 0
#define Y_POS 1

GameMap::GameMap(std::uint16_t x_size, std::uint16_t y_size) :
        x_size(x_size),
        y_size(y_size),
        map(y_size, std::vector<GameObject*>(x_size, nullptr)) {}


void GameMap::shoot(Weapon* weapon,
                    std::uint16_t x_pos_sold,
                    std::uint16_t y_pos_sold,
                    std::int16_t direction) {
    GameObject* game_object = collision_with_zombie(direction,
                                                               x_pos_sold,
                                                               y_pos_sold);
    if (game_object == nullptr) return;
    game_object->get_shot(weapon);
}

GameObject* GameMap::
collision_with_zombie(std::int16_t direction,
                      std::uint16_t x_pos_sold,
                      std::uint16_t y_pos_sold) {
    // las 3 columnas a revisar
    std::vector<signed int> pos_soldier = {x_pos_sold, x_pos_sold - 1, x_pos_sold + 1};

    if (direction == UP) {
        for (signed int i = 0; i < pos_soldier.size(); i++) {
            GameObject* game_object = collision_going_up(pos_soldier[i], y_pos_sold);
            if (game_object != nullptr){
                return game_object;
            }
        }
        return nullptr;
    }
    for (signed int i = 0; i < pos_soldier.size(); i++) {
        GameObject* game_object = collision_going_down(pos_soldier[i], y_pos_sold);
        if (game_object != nullptr){
            return game_object;
        }
    }
    return nullptr;
}

GameObject* GameMap::collision_going_down(std::uint16_t x_pos, std::uint16_t y_pos) {
    for (int j = y_pos + 1; j < y_size; j++) { // +1 para no autodispararme jeej
        if (map[j][x_pos] != nullptr) {
            return map[j][x_pos];
        }
    }
    return nullptr;
}

GameObject* GameMap::collision_going_up(std::uint16_t x_pos, std::uint16_t y_pos) {
    for (int j = y_pos - 1; j >= 0; j--) {
        if (map[j][x_pos] != nullptr) {
            return map[j][x_pos];
        }
    }
    return nullptr;
}



// ****************************** Metodos de Testeo ***********************************//

void GameMap::add_soldier(GameObject* soldier,
                      std::uint16_t x_pos,
                      std::uint16_t y_pos) {
    if (!valid_entire_soldier_position(x_pos, y_pos)){
        return; // excepcion
    }
    map[y_pos][x_pos] = soldier;
    map[y_pos][x_pos - 1] = soldier;
    map[y_pos][x_pos + 1] = soldier;

}

void GameMap::add_zombie(GameObject *walker, std::uint16_t x_pos, std::uint16_t y_pos) {
        map[y_pos][x_pos] = walker;
}

bool GameMap::collision(std::int16_t direction, std::uint16_t x_pos, std::uint16_t y_pos) {
    if (!valid_entire_soldier_position(x_pos, y_pos)) {
        return false; // deberia levantar error.
    }

    std::vector<signed int> pos_soldier = {x_pos, x_pos - 1, x_pos + 1};

    if (direction == UP) {
        for (signed int i = 0; i < pos_soldier.size(); i++) {
           if (collision_going_up_test(pos_soldier[i], y_pos)){
               return true;
           }
        }
        return false;
    }
    for (signed int i = 0; i < pos_soldier.size(); i++) {
        if (collision_going_down_test(pos_soldier[i], y_pos)){
            return true;
        }
    }
    return false;
}

bool GameMap::collision_going_down_test(std::uint16_t x_pos, std::uint16_t y_pos) {
    for (int i = y_pos; i < y_size; i++) {
        if (map[i][x_pos] != nullptr) {
            return true;
        }
    }
    return false;
}

bool GameMap::collision_going_up_test(std::uint16_t x_pos, std::uint16_t y_pos) {
    for (int j = y_pos; j >= 0; j--) {
        if (map[j][x_pos] != nullptr) {
            return true;
        }
    }
    return false;
}

bool GameMap::valid_entire_soldier_position(std::int16_t x_pos, std::int16_t y_pos) {
    bool valid_x = false;
    bool valid_y = false;
    if ( (x_pos - 1) >= 0 && (x_pos + 1) <= x_size - 1) {
        valid_x = true;
    }
    if (y_pos >= 0 && y_pos <= y_size - 1){
        valid_y = true;
    }
    return valid_x && valid_y;
}