#include <cstdint>
#include <iostream>
#include "map.h"

#define DOWN 1
#define UP -1
#define LEFT 2
#define RIGHT 3

#define X_POS 0
#define Y_POS 1
#define INVALID_POSITION -1

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

void GameMap::get_objects_in_explosion(std::vector<GameObject *> &game_objects,
                            std::uint16_t x_pos_grenade,
                            std::uint16_t y_pos_grenade,
                            std::int16_t radius_explosion) {
    if (x_pos_grenade >= x_size) {
        x_pos_grenade = x_size - 1;
    } else if (x_pos_grenade < 0) {
        x_pos_grenade = 0;
    }
    get_objects_in_radius(x_pos_grenade,
                          y_pos_grenade,
                          radius_explosion,
                          game_objects);
}

void GameMap::get_objects_in_radius(std::int16_t x_grenade_pos,
                                      std::int16_t y_grenade_pos,
                                      std::int16_t radius_explosion,
                                      std::vector<GameObject*>& game_objects) {
    std::int16_t x_start = x_grenade_pos - radius_explosion;
    std::int16_t y_start = y_grenade_pos - radius_explosion;
    validate_position_for_explosion(x_start, y_start);

    std::int16_t x_finish = x_grenade_pos + radius_explosion;
    std::int16_t y_finish = y_grenade_pos + radius_explosion;
    validate_position_for_explosion(x_finish, y_finish);

    for (Zombie* object : zombies){
        if (object->in_range_of_explosion(x_start, x_finish, y_start, y_finish)) {
            game_objects.push_back(dynamic_cast<GameObject*>(object));
        }
    }
    for (GameObject* object : soldiers){
        if (object->in_range_of_explosion(x_start, x_finish, y_start, y_finish)) {
            game_objects.push_back(object);
        }
    }
}

void GameMap::validate_position_for_explosion(std::int16_t& x_pos,
                                std::int16_t& y_pos) {
    if (x_pos > x_size - 1) {
        x_pos = x_size - 1;
    } else if (x_pos < 0) {
        x_pos = 0;
    }
    if (y_pos > y_size - 1) {
        y_pos = y_size - 1;
    } else if (y_pos < 0) {
        y_pos = 0;
    }
}

void GameMap::
collision_with_zombie(std::vector<GameObject*>& game_objects,
                      std::uint16_t x_pos_sold,
                      std::uint16_t y_pos_sold,
                      std::int16_t direction) {

    if (direction == LEFT) {
        collision_going_left(game_objects, x_pos_sold, y_pos_sold);
        return;
    }
    collision_going_right(game_objects, x_pos_sold, y_pos_sold);
}

void GameMap::collision_going_left(std::vector<GameObject*>& game_objects,
                                 std::uint16_t x_pos,
                                 std::uint16_t y_pos) {
    for (int i = x_pos - 1; i >= 0; i--) { // x_pos - 1 para no dispararme
        if (map[y_pos][i] != nullptr) {
            game_objects.push_back(map[y_pos][i]);
        }
    }
}

void GameMap::collision_going_right(std::vector<GameObject*>& game_objects,
                                          std::uint16_t x_pos,
                                          std::uint16_t y_pos) {
    for (int i = x_pos + 1; i < y_size; i++) { // +1 para no autodispararme
        if (map[y_pos][i] != nullptr) {
            game_objects.push_back(map[y_pos][i]);
        }
    }
}

// Visualmente para nosotros es mover a arriba
void GameMap::move_object_up(std::int16_t x_pos,
                              std::int16_t y_pos,
                              std::int16_t& new_y_pos_ref) {
    if (y_pos > 0){
        std::uint16_t new_y_pos = y_pos - 1;
        find_new_y_pos(new_y_pos_ref, new_y_pos, x_pos, y_pos);
        return;
    }
}

void GameMap::move_object_down(std::int16_t x_pos,
                                std::int16_t y_pos,
                                std::int16_t &new_y_pos_ref) {
    if(y_pos < y_size - 1) {
        std::uint16_t new_y_pos = y_pos + 1;
        find_new_y_pos(new_y_pos_ref, new_y_pos, x_pos, y_pos);
    }
}

void GameMap::move_object_right(std::int16_t x_pos,
                                 std::int16_t y_pos,
                                 std::int16_t &new_x_pos_ref) {

    std::uint16_t new_x_pos = x_pos + 1;
    if (check_free_position(new_x_pos, y_pos) && new_x_pos < x_size) {
        map[y_pos][new_x_pos] = map[y_pos][x_pos];
        map[y_pos][x_pos] = nullptr;
        new_x_pos_ref = new_x_pos;
    }
}
void GameMap::move_object_left(std::int16_t x_pos,
                                std::int16_t y_pos,
                                std::int16_t &new_x_pos_ref) {
    std::uint16_t new_x_pos = x_pos - 1;
    if (x_pos > 0 && check_free_position(new_x_pos, y_pos)) {
        map[y_pos][new_x_pos] = map[y_pos][x_pos];
        map[y_pos][x_pos] = nullptr;
        new_x_pos_ref = new_x_pos;
    }
}

void GameMap::find_new_y_pos(std::int16_t &new_y_pos_ref,
                             std::uint16_t possible_new_y_pos,
                             std::uint16_t x_pos,
                             std::uint16_t y_pos) {
    bool first_position = check_free_position(x_pos, possible_new_y_pos);
    if (first_position){
        move_object_y(x_pos, y_pos, possible_new_y_pos);
        new_y_pos_ref = possible_new_y_pos;
    }
}

void GameMap::move_object_y(std::uint16_t x_pos,
                             std::uint16_t y_pos,
                             std::uint16_t y_new_pos) {
    map[y_new_pos][x_pos] = map[y_pos][x_pos];
    map[y_pos][x_pos] = nullptr;
}

bool GameMap::check_free_position(std::int16_t x_pos,
                                  std::int16_t y_pos) {
    if (x_pos < 0 || x_pos >= x_size|| y_pos < 0 || y_pos >= y_size){
        return false;
    }
    return map[y_pos][x_pos] == nullptr; // !map[y_sold_pos][x_sold_pos]
}

void GameMap::chase_soldiers(float time) {
    for (Zombie* zombie : zombies) {
        zombie->chase_closest_soldier(soldiers, time);
    }
}

void GameMap::attack_soldiers(float time) {
    for (Zombie* zombie : zombies) {
        zombie->attack(soldiers, time);
    }
}

void GameMap::get_position_for_object(std::vector<std::int16_t> &valid_pos) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(0, x_size - 2);
    std::uniform_int_distribution<> dis_y(0, y_size - 1);

    for (int i = 0; i < 10; i++) {
        std::int16_t random_x_pos = dis_x(gen);
        std::int16_t random_y_pos = dis_y(gen);
        if (check_free_position(random_x_pos, random_y_pos)) {
            valid_pos.push_back(random_x_pos);
            valid_pos.push_back(random_y_pos);
        }
    }
}

void GameMap::get_position_for_soldier(std::vector<std::int16_t> &valid_pos) {
    while (true) {
        get_position_for_object(valid_pos);
        if (!valid_pos.empty()) return;
    }
}


bool GameMap::valid_object_position(std::int16_t x_pos, std::int16_t y_pos) {
    bool valid_x = false;
    bool valid_y = false;
    if ( x_pos >= 0 && x_pos < x_size) {
        valid_x = true;
    }
    if (y_pos >= 0 && y_pos < y_size){
        valid_y = true;
    }
    return valid_x && valid_y;
}


// Deberia tener solo un add object y listo;

void GameMap::free_position(std::int16_t x_pos, std::int16_t y_pos) {
    map[y_pos][x_pos] = nullptr;
}

// ****************************** Metodos de Testeo ***********************************//

bool GameMap::add_soldier(GameObject* soldier,
                      std::uint16_t x_pos,
                      std::uint16_t y_pos) {

    if (!check_free_position(x_pos, y_pos)) {
        return false;
    }
    map[y_pos][x_pos] = soldier;

    soldiers.push_back(soldier); // ya no necesito
    return true;
}

bool GameMap::add_zombie(GameObject* walker, std::uint16_t x_pos, std::uint16_t y_pos) {
    if (!check_free_position(x_pos, y_pos)) {
        return false;
    }
    zombies.push_back(dynamic_cast<Zombie*>(walker)); // ya no necesito

    map[y_pos][x_pos] = walker;

    return true;
}

void GameMap::add_obstacle(GameObject* obstacle,
                           std::uint16_t x_pos,
                           std::uint16_t y_pos) {
    if (!valid_object_position(x_pos, y_pos)){ // cambiar por validar_gameObject
        return; // excepcion
    }
    map[y_pos][x_pos] = obstacle;
}

bool GameMap::collision(std::int16_t direction, std::uint16_t x_pos, std::uint16_t y_pos) {
    if (!valid_object_position(x_pos, y_pos)) {
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

GameObject* GameMap::get_object(std::uint16_t x_pos, std::uint16_t y_pos) {
    return map[y_pos][x_pos];
}