#include <cstdint>
#include <iostream>

#include "map.h"
#include "game_object.h"
#include "soldier.h"

#define X_POS 0
#define Y_POS 1
#define DOWN 1
#define UP -1
#define LEFT 2
#define RIGHT 3
#define INVALID_POSITION -1

GameMap::GameMap(std::uint16_t x_size, std::uint16_t y_size) :
        x_size(x_size),
        y_size(y_size),
        map(y_size, std::vector<GameObject*>(x_size, nullptr)),
        factory(*this) {}

GameMap::GameMap(std::uint16_t x_size, std::uint16_t y_size, std::int16_t y_limit_down) :
        x_size(x_size),
        y_size(y_size),
        map(y_size, std::vector<GameObject*>(x_size, nullptr)),
        factory(*this),
        y_limit_down(y_limit_down){}

void GameMap::update(float time) {
    std::vector<Zombie*> zombies_copy = zombies;
    for (Zombie* zombie : zombies_copy) {
        zombie->update(soldiers, time);
    }
}

void GameMap::get_objects_in_shooting(std::vector<GameObject*>& game_objects,
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
    get_valid_pos_in_map(x_start, y_start);

    std::int16_t x_finish = x_grenade_pos + radius_explosion;
    std::int16_t y_finish = y_grenade_pos + radius_explosion;
    get_valid_pos_in_map(x_finish, y_finish);

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

void GameMap::get_objects_in_air_strike(std::vector<GameObject *> &game_objects_in_air_strike,
                                        std::int16_t x_soldier,
                                        std::int16_t y_soldier,
                                        std::int16_t range_of_safe_space) {

    std::int16_t x_start = x_soldier - range_of_safe_space;
    std::int16_t y_start = y_soldier - range_of_safe_space;
    get_valid_pos_in_map(x_start, y_start);

    std::int16_t x_finish = x_soldier + range_of_safe_space;
    std::int16_t y_finish = y_soldier + range_of_safe_space;
    get_valid_pos_in_map(x_finish, y_finish);

    for (Zombie* object : zombies) {
        if (!object->in_range_of_explosion(x_start, x_finish, y_start, y_finish)) {
            game_objects_in_air_strike.push_back(dynamic_cast<GameObject*>(object));
        }
    }
    for (Soldier* object : soldiers){
        if (!object->in_range_of_explosion(x_start, x_finish, y_start, y_finish)) {
            game_objects_in_air_strike.push_back(object);
        }
    }
}

void GameMap::get_positions_of_explosion_air_strike(std::vector<std::vector<int16_t>>& positions,
                                                    std::int16_t x_pos_called,
                                                    std::int16_t y_pos_called,
                                                    std::int16_t range_safe_space) {
    for (int j = y_limit_down; j < y_size; j+=(y_size-y_limit_down)) {
        for (int i = x_pos_called - 40; i < x_pos_called + 40; i+=10) {
            double distance = std::sqrt(std::pow(i - x_pos_called, 2) + std::pow(j - y_pos_called, 2));
            if (distance > range_safe_space) {
                std::vector<std::int16_t> pos;
                pos.push_back(i);
                pos.push_back(j);
                positions.push_back(pos);
            }
        }
    }

}

void GameMap::get_valid_pos_in_map(  std::int16_t& x_pos,
                                     std::int16_t& y_pos) {
    if (x_pos > x_size - 1) {
        x_pos = x_size - 1;
    } else if (x_pos < 0) {
        x_pos = 0;
    }
    if (y_pos > y_size - 1) {
        y_pos = y_size - 1;
    } else if (y_pos < 0) {
        y_pos = y_limit_down;
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
    for (int i = x_pos + 1; i < x_size; i++) { // +1 para no autodispararme
        if (map[y_pos][i] != nullptr) {
            game_objects.push_back(map[y_pos][i]);
        }
    }
}

// Visualmente para nosotros es mover a arriba
void GameMap::move_object_up(std::int16_t x_pos,
                              std::int16_t y_pos,
                              std::int16_t& new_y_pos_ref) {
    if (y_pos > y_limit_down){ //PQ CHEQUEO ESTO>
        std::uint16_t new_y_pos = y_pos - 1;
        find_new_y_pos(new_y_pos_ref, new_y_pos, x_pos, y_pos);
        return;
    }
}

void GameMap::move_object_down(std::int16_t x_pos,
                                std::int16_t y_pos,
                                std::int16_t &new_y_pos_ref) {
    if(y_pos < y_size) {
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

Soldier* GameMap::get_soldier_to_revive(std::int16_t x_pos, std::int16_t y_pos, std::int16_t range) {
    std::int16_t x_start = x_pos - range;
    std::int16_t y_start = y_pos - range;
    std::int16_t x_finish = x_pos + range;
    std::int16_t y_finish = y_pos + range;

    get_valid_pos_in_map(x_start, y_start); // ya no seria para explosion
    get_valid_pos_in_map(x_finish, y_finish);

    for (Soldier* soldier : soldiers) {
        if (soldier->in_range_of_explosion(x_start, x_finish, y_start, y_finish) && soldier->dead()) {
            return soldier;
        }
    }
    return nullptr;
}

Soldier* GameMap::get_soldier_with_idf() {
    std::vector<std::int16_t> soldier_pos;
    get_position_for_object(soldier_pos);
    Soldier* soldier = factory.get_soldier_with_idf(soldier_pos);
    soldiers.push_back(soldier);

    std::int16_t x_pos = soldier_pos[X_POS];
    std::int16_t y_pos = soldier_pos[Y_POS];
    map[y_pos][x_pos] = soldier;
    return soldier;
}

Soldier* GameMap::get_soldier_with_p90() {
    std::vector<std::int16_t> soldier_pos;
    get_position_for_object(soldier_pos);
    Soldier* soldier = factory.get_soldier_with_p90(soldier_pos);
    soldiers.push_back(soldier);

    std::int16_t x_pos = soldier_pos[X_POS];
    std::int16_t y_pos = soldier_pos[Y_POS];
    map[y_pos][x_pos] = soldier;
    return soldier;
}

Soldier* GameMap::get_soldier_with_scout() {
    std::vector<std::int16_t> soldier_pos;
    get_position_for_object(soldier_pos);
    Soldier* soldier = factory.get_soldier_with_scout(soldier_pos);
    soldiers.push_back(soldier);

    std::int16_t x_pos = soldier_pos[X_POS];
    std::int16_t y_pos = soldier_pos[Y_POS];
    map[y_pos][x_pos] = soldier;
    return soldier;
}

void GameMap::add_random_zombie() {
    std::vector<std::int16_t> zombie_pos;
    get_position_for_object(zombie_pos);
    Zombie* zombie = factory.create_random_zombie(zombie_pos);
    zombies.push_back(zombie);

    std::int16_t x_pos = zombie_pos[X_POS];
    std::int16_t y_pos = zombie_pos[Y_POS];
    map[y_pos][x_pos] = dynamic_cast<GameObject*>(zombie);
}

void GameMap::add_infected(std::int16_t extra_health, std::int16_t extra_damage) {
    std::vector<std::int16_t> zombie_pos;
    get_position_for_object(zombie_pos);
    Zombie* zombie = factory.create_infected(zombie_pos,  extra_health, extra_damage);
    zombies.push_back(zombie);

    std::int16_t x_pos = zombie_pos[X_POS];
    std::int16_t y_pos = zombie_pos[Y_POS];
    map[y_pos][x_pos] = dynamic_cast<GameObject*>(zombie);
}

void GameMap::add_jumper(std::int16_t extra_health, std::int16_t extra_damage) {
    std::vector<std::int16_t> zombie_pos;
    get_position_for_object(zombie_pos);
    Zombie* zombie = factory.create_jumper(zombie_pos, extra_health, extra_damage);
    zombies.push_back(zombie);

    std::int16_t x_pos = zombie_pos[X_POS];
    std::int16_t y_pos = zombie_pos[Y_POS];
    map[y_pos][x_pos] = dynamic_cast<GameObject*>(zombie);
}

void GameMap::add_witch(std::int16_t extra_health, std::int16_t extra_damage) {
    std::vector<std::int16_t> zombie_pos;
    get_position_for_object(zombie_pos);
    Zombie* zombie = factory.create_witch(zombie_pos, extra_health, extra_damage);
    zombies.push_back(zombie);

    std::int16_t x_pos = zombie_pos[X_POS];
    std::int16_t y_pos = zombie_pos[Y_POS];
    map[y_pos][x_pos] = dynamic_cast<GameObject*>(zombie);
}

void GameMap::add_spear(std::int16_t extra_health, std::int16_t extra_damage) {
    std::vector<std::int16_t> zombie_pos;
    get_position_for_object(zombie_pos);
    Zombie* zombie = factory.create_spear(zombie_pos, extra_health, extra_damage);
    zombies.push_back(zombie);

    std::int16_t x_pos = zombie_pos[X_POS];
    std::int16_t y_pos = zombie_pos[Y_POS];
    map[y_pos][x_pos] = dynamic_cast<GameObject*>(zombie);
}

void GameMap::get_position_for_object(std::vector<std::int16_t> &valid_pos) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis_x(0, x_size - 1);
    std::uniform_int_distribution<> dis_y(y_limit_down, y_size);

    while (true) {
        std::int16_t random_x_pos = dis_x(gen);
        std::int16_t random_y_pos = dis_y(gen);
        if (check_free_position(random_x_pos, random_y_pos) && valid_object_position(random_x_pos, random_y_pos)) {
            valid_pos.push_back(random_x_pos);
            valid_pos.push_back(random_y_pos);
            return;
        }
    }
}


bool GameMap::valid_object_position(std::int16_t x_pos, std::int16_t y_pos) {
    bool valid_x = false;
    bool valid_y = false;
    if ( x_pos >= 0 && x_pos < x_size) {
        valid_x = true;
    }
    if (y_pos >= y_limit_down && y_pos < y_size){
        valid_y = true;
    }
    return valid_x && valid_y;
}


// Deberia tener solo un add object y listo;

void GameMap::free_position(std::int16_t x_pos, std::int16_t y_pos) {
    map[y_pos][x_pos] = nullptr;
}

std::vector<Zombie*>* GameMap::get_zombies() {
    return &zombies;
}

GameMap::~GameMap() {
    for (auto* zombie : zombies) {
        delete zombie;
    }
    zombies.clear();
    for (auto* soldier : soldiers) {
        delete soldier;
    }
    soldiers.clear();
    for(auto fila: map){
        fila.clear();    
    }
    map.clear();
}

// ****************************** Metodos de Testeo ***********************************//

//solo tests
void GameMap::chase_soldiers(float time) {
    for (Zombie* zombie : zombies) {
        zombie->chase_closest_soldier(soldiers, time);
    }
}
//solo tests
void GameMap::attack_soldiers(float time) {
    for (Zombie* zombie : zombies) {
        zombie->attack(soldiers, time);
    }
}

bool GameMap::add_soldier(Soldier* soldier,
                      std::uint16_t x_pos,
                      std::uint16_t y_pos) {

    if (!check_free_position(x_pos, y_pos)) {
        return false;
    }
    map[y_pos][x_pos] = soldier;

    soldiers.push_back(soldier);
    return true;
}

bool GameMap::add_zombie(Zombie* walker, std::uint16_t x_pos, std::uint16_t y_pos) {
    if (!check_free_position(x_pos, y_pos)) {
        return false;
    }
    zombies.push_back(walker);

    map[y_pos][x_pos] = dynamic_cast<GameObject*>(walker);

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

std::int16_t GameMap::objects_in_map() {
    int contador = 0;
    for (int j = 0; j < y_size; j++) {
        for (int i = 0; i < x_size; i++) {
            if (map[j][i] != nullptr) {
                std::cout << "pos elem encontrado : "<< i << ", " << j << std::endl;
                contador++;
            }
        }
    }
    std::cout << "cant elem map: "<<contador << std::endl;
    return contador;
}

void GameMap::empty_vectors() {
    zombies.clear();
    soldiers.clear();
    for(auto fila: map){
        fila.clear();
    }
    map.clear();
}
