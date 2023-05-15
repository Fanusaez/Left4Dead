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


void GameMap::shoot(std::vector<GameObject*>& game_objects,
                    std::uint16_t x_pos_sold,
                    std::uint16_t y_pos_sold,
                    std::int16_t direction) {
    collision_with_zombie(game_objects,
                          x_pos_sold,
                          y_pos_sold,
                          direction);
}

void GameMap::
collision_with_zombie(std::vector<GameObject*>& game_objects,
                      std::uint16_t x_pos_sold,
                      std::uint16_t y_pos_sold,
                      std::int16_t direction) {
    // las 3 columnas a revisar
    std::vector<signed int> pos_soldier = {x_pos_sold, x_pos_sold + 1};

    if (direction == UP) {
        for (signed int i = 0; i < pos_soldier.size(); i++) {
            collision_going_up(game_objects,pos_soldier[i], y_pos_sold);
            if (!game_objects.empty()) {
                return;
            }
        }
        return;
    }
    for (signed int i = 0; i < pos_soldier.size(); i++) {
        collision_going_down(game_objects,pos_soldier[i], y_pos_sold);
        if (!game_objects.empty()){
            return;
        }
    }
}

void GameMap::collision_going_up(std::vector<GameObject*>& game_objects,
                                 std::uint16_t x_pos,
                                 std::uint16_t y_pos) {
    for (int j = y_pos - 1; j >= 0; j--) { // y_pos - 1 para no dispararme
        if (map[j][x_pos] != nullptr) {
            game_objects.push_back(map[j][x_pos]);
        }
    }
}


void GameMap::collision_going_down(std::vector<GameObject*>& game_objects,
                                          std::uint16_t x_pos,
                                          std::uint16_t y_pos) {
    for (int j = y_pos + 1; j < y_size; j++) { // +1 para no autodispararme jeej
        if (map[j][x_pos] != nullptr) {
            game_objects.push_back(map[j][x_pos]);
        }
    }
}

// Visualmente para nosotros es mover a la izquierda
void GameMap::move_soldier_up(std::uint16_t x_pos,
                              std::uint16_t y_pos,
                              std::int16_t& new_y_pos_ref) {
    if (y_pos > 0){
        std::uint16_t new_y_pos = y_pos - 1;
        find_new_y_pos(new_y_pos_ref, new_y_pos, x_pos, y_pos);
        return;
    }
    if(y_pos == 0) {
        std::uint16_t new_y_pos = y_size - 1;
        find_new_y_pos(new_y_pos_ref, new_y_pos, x_pos, y_pos);
    }
}

void GameMap::find_new_y_pos(std::int16_t &new_y_pos_ref,
                             std::uint16_t possible_new_y_pos,
                             std::uint16_t x_pos,
                             std::uint16_t y_pos) {
    bool first_position = check_free_position(x_pos, possible_new_y_pos);
    bool sec_position = check_free_position(x_pos + 1, possible_new_y_pos);
    if (first_position && sec_position){
        move_object_to(x_pos, y_pos, x_pos, possible_new_y_pos);
        new_y_pos_ref = possible_new_y_pos;
    }
}

void GameMap::move_object_to(std::uint16_t x_pos,
                             std::uint16_t y_pos,
                             std::uint16_t x_new_pos,
                             std::uint16_t y_new_pos) {
    map[y_new_pos][x_new_pos] = map[y_pos][x_pos];
    map[y_pos][x_pos] = nullptr;

    map[y_new_pos][x_new_pos + 1] = map[y_pos][x_pos + 1];
    map[y_pos][x_pos + 1] = nullptr;
}

bool GameMap::check_free_position(std::uint16_t x_sold_pos,
                                  std::uint16_t y_sold_pos) {
    return map[y_sold_pos][x_sold_pos] == nullptr; // !map[y_sold_pos][x_sold_pos]
}
// ****************************** Metodos de Testeo ***********************************//

void GameMap::add_soldier(GameObject* soldier,
                      std::uint16_t x_pos,
                      std::uint16_t y_pos) {
    if (!valid_entire_object_position(x_pos, y_pos)){
        return; // excepcion
    }
    map[y_pos][x_pos] = soldier;
    map[y_pos][x_pos + 1] = soldier;

}

void GameMap::add_zombie(GameObject *walker, std::uint16_t x_pos, std::uint16_t y_pos) {
    if (!valid_entire_object_position(x_pos, y_pos)){ // cambiar por validar_gameObject
        return; // excepcion
    }
    map[y_pos][x_pos] = walker;
    map[y_pos][x_pos + 1] = walker;
}

bool GameMap::collision(std::int16_t direction, std::uint16_t x_pos, std::uint16_t y_pos) {
    if (!valid_entire_object_position(x_pos, y_pos)) {
        return false; // deberia levantar error.
    }

    std::vector<signed int> pos_soldier = {x_pos, x_pos + 1};

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

bool GameMap::valid_entire_object_position(std::int16_t x_pos, std::int16_t y_pos) {
    bool valid_x = false;
    bool valid_y = false;
    if ( x_pos >= 0 && x_pos + 1 < x_size) { // +1 dado que en x tenemos un slot mas
        valid_x = true;
    }
    if (y_pos >= 0 && y_pos < y_size){
        valid_y = true;
    }
    return valid_x && valid_y;
}