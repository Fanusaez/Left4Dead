#include <cstdint>
#include <iostream>
#include "map.h"

#define UP -1
#define DOWN 1
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

void GameMap::throw_grenade(std::vector<GameObject *> &game_objects,
                            std::uint16_t x_pos_grenade,
                            std::uint16_t y_pos_grenade) {
    if (y_pos_grenade >= y_size) {
        y_pos_grenade = y_size - 1;
    } else if (y_pos_grenade < 0) {
        y_pos_grenade = 0;
    }
    get_objects_in_distance(x_pos_grenade,
                            y_pos_grenade,
                            game_objects);
}

void GameMap::get_objects_in_distance(std::int16_t x_grenade_pos,
                                      std::int16_t y_grenade_pos,
                                      std::vector<GameObject*>& game_objects) {
    std::int16_t x_start = x_grenade_pos - radius_damage_grenade;
    std::int16_t y_start = y_grenade_pos - radius_damage_grenade;
    validate_position(x_start, y_start);

    std::int16_t x_finish = x_grenade_pos + radius_damage_grenade;
    std::int16_t y_finish = y_grenade_pos + radius_damage_grenade;
    validate_position(x_finish, y_finish);

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

void GameMap::validate_position(std::int16_t& x_pos,
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
    if(y_pos == 0) { // no hace falta if
        std::uint16_t new_y_pos = y_size - 1;
        find_new_y_pos(new_y_pos_ref, new_y_pos, x_pos, y_pos);
    }
}

void GameMap::move_soldier_down(std::uint16_t x_pos,
                                std::uint16_t y_pos,
                                std::int16_t &new_y_pos_ref) {
    if (y_pos == y_size - 1){
        std::uint16_t new_y_pos = 0;
        find_new_y_pos(new_y_pos_ref, new_y_pos, x_pos, y_pos);
        return;
    }
    if(y_pos < y_size - 1) { // no hace falta if
        std::uint16_t new_y_pos = y_pos + 1;
        find_new_y_pos(new_y_pos_ref, new_y_pos, x_pos, y_pos);
    }
}

void GameMap::move_soldier_right(std::uint16_t x_pos,
                                 std::uint16_t y_pos,
                                 std::int16_t &new_x_pos_ref) {

    std::uint16_t new_x_pos = x_pos + 2;
    if (check_free_position(new_x_pos, y_pos) && new_x_pos < x_size) {
        map[y_pos][new_x_pos] = map[y_pos][x_pos];
        map[y_pos][x_pos] = nullptr;
        new_x_pos_ref = new_x_pos - 1;
    }
}
void GameMap::move_soldier_left(std::uint16_t x_pos,
                                std::uint16_t y_pos,
                                std::int16_t &new_x_pos_ref) {
    std::uint16_t new_x_pos = x_pos - 1;
    if (x_pos > 0 && check_free_position(new_x_pos, y_pos)) {
        map[y_pos][new_x_pos] = map[y_pos][x_pos];
        map[y_pos][x_pos + 1] = nullptr;
        new_x_pos_ref = new_x_pos;
    }
}

void GameMap::find_new_y_pos(std::int16_t &new_y_pos_ref,
                             std::uint16_t possible_new_y_pos,
                             std::uint16_t x_pos,
                             std::uint16_t y_pos) {
    bool first_position = check_free_position(x_pos, possible_new_y_pos);
    bool sec_position = check_free_position(x_pos + 1, possible_new_y_pos);
    if (first_position && sec_position){
        move_object_y(x_pos, y_pos, possible_new_y_pos);
        new_y_pos_ref = possible_new_y_pos;
    }
}

void GameMap::move_object_y(std::uint16_t x_pos,
                             std::uint16_t y_pos,
                             std::uint16_t y_new_pos) {
    map[y_new_pos][x_pos] = map[y_pos][x_pos];
    map[y_pos][x_pos] = nullptr;

    map[y_new_pos][x_pos + 1] = map[y_pos][x_pos + 1];
    map[y_pos][x_pos + 1] = nullptr;
}

bool GameMap::check_free_position(std::int16_t x_pos,
                                  std::int16_t y_pos) {
    if (x_pos < 0 || x_pos >= x_size|| y_pos < 0 || x_pos >= y_size){
        return false;
    }
    return map[y_pos][x_pos] == nullptr; // !map[y_sold_pos][x_sold_pos]
}

void GameMap::chase_soldier_walking(Zombie* walker,
                                    std::int16_t &x_new_pos,
                                    std::int16_t &y_new_pos,
                                    GameObject *soldier) {
    std::vector<std::int16_t> sold_pos;
    soldier->get_position(sold_pos);
    std::int16_t x_sold = sold_pos[X_POS];
    std::int16_t y_sold = sold_pos[Y_POS];

    std::vector<std::int16_t> walker_pos;
    walker->get_position(walker_pos);
    std::int16_t x_walker = walker_pos[X_POS];
    std::int16_t y_walker = walker_pos[Y_POS];

    bool same_place = true;

    if (x_sold > x_walker && y_sold < y_walker) { // movimiento diagonal derecha arriba
        bool cond1 = check_free_position(x_walker + 1, y_walker - 1); // primera pos
        bool cond2 = check_free_position(x_walker + 2, y_walker - 1); // seg pos
        if (cond1 && cond2) {
            x_new_pos = x_walker + 1;
            y_new_pos = y_walker - 1;
            move_object_diagonally(x_walker, y_walker, x_new_pos, y_new_pos);
            same_place = false;
        }
    } else if (x_sold < x_walker && y_sold < y_walker) { // movimiento diagonal izquierda arriba
        bool cond1 = check_free_position(x_walker - 1, y_walker - 1); // primera pos
        bool cond2 = check_free_position(x_walker, y_walker - 1); // seg pos
        if (cond1 && cond2) {
            x_new_pos = x_walker - 1;
            y_new_pos = y_walker - 1;
            move_object_diagonally(x_walker, y_walker, x_new_pos, y_new_pos);
            same_place = false;
        }
    } else if (x_sold > x_walker && y_sold > y_walker) { // movimiento diagonal derecha abajo
        bool cond1 = check_free_position(x_walker + 1, y_walker + 1); // primera pos
        bool cond2 = check_free_position(x_walker + 2, y_walker + 1); // seg pos
        if (cond1 && cond2) {
            // muevo pos de walker diagonalmente
            x_new_pos = x_walker + 1;
            y_new_pos = y_walker + 1;
            move_object_diagonally(x_walker, y_walker, x_new_pos, y_new_pos);
            same_place = false;
        }

    } else if (x_sold < x_walker && y_sold > y_walker) { // movimiento diagonal izquierda abajo
        bool cond1 = check_free_position(x_walker + 1, y_walker + 1); // primera pos
        bool cond2 = check_free_position(x_walker, y_walker + 1); // seg pos
        if (cond1 && cond2) {
            // muevo pos de walker diagonalmente
            x_new_pos = x_walker - 1;
            y_new_pos = y_walker + 1;
            move_object_diagonally(x_walker, y_walker, x_new_pos, y_new_pos);
            same_place = false;
        }
    }
    if (y_sold > y_walker && same_place) { // movimiento para abajo
        move_soldier_down(x_walker, y_walker, y_new_pos); /// ya no debe llamarse asi
        if (y_new_pos != INVALID_POSITION) same_place = false;
    } else if (y_sold < y_walker && same_place) { // movimiento para arriba
        move_soldier_up(x_walker, y_walker, y_new_pos); /// ya no debe llamarse asi
        if (y_new_pos != INVALID_POSITION) same_place = false;
    } else if (x_sold < x_walker && same_place) { // movimiento para izquierda
        move_soldier_left(x_walker, y_walker, x_new_pos); /// ya no debe llamarse asi
        if (x_new_pos != INVALID_POSITION) same_place = false;
    } else if (x_sold > x_walker && same_place) { // movimiento para derecha
        move_soldier_right(x_walker, y_walker, x_new_pos); /// ya no debe llamarse asi
    } else { } // no te pudiste mover para ningun lado, caso obstaculo o estas al lado del soldado o enfrente
}

void GameMap::move_object_diagonally(std::int16_t& x_old_pos,
                                     std::int16_t& y_old_pos,
                                     std::int16_t& x_new_pos,
                                     std::int16_t& y_new_pos) {
    map[y_new_pos][x_new_pos] = map[y_old_pos][x_old_pos];
    map[y_new_pos][x_new_pos + 1] = map[y_old_pos][x_old_pos];
    map[y_old_pos][x_old_pos] = nullptr;
    map[y_old_pos][x_old_pos + 1] = nullptr;
}

void GameMap::chase_soldiers() {
    for (Zombie* zombie : zombies) {
        zombie->chase_closest_soldier(*this, soldiers);
    }
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

    soldiers.push_back(soldier);
}

void GameMap::add_zombie(GameObject* walker, std::uint16_t x_pos, std::uint16_t y_pos) {
    if (!valid_entire_object_position(x_pos, y_pos)){ // cambiar por validar_gameObject
        return; // excepcion
    }
    zombies.push_back(dynamic_cast<Zombie*>(walker));

    map[y_pos][x_pos] = walker;
    map[y_pos][x_pos + 1] = walker;
    //zombies_object.push_back(walker);
}

void GameMap::add_obstacle(GameObject* obstacle,
                           std::uint16_t x_pos,
                           std::uint16_t y_pos) {
    if (!valid_entire_object_position(x_pos, y_pos)){ // cambiar por validar_gameObject
        return; // excepcion
    }
    map[y_pos][x_pos] = obstacle;
    map[y_pos][x_pos + 1] = obstacle;
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

GameObject* GameMap::get_object(std::uint16_t x_pos, std::uint16_t y_pos) {
    return map[y_pos][x_pos];
}