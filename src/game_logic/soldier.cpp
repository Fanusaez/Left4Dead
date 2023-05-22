#include <cmath>
#include <iostream>
#include "soldier.h"

#define GRANADE_DISTANCE_REACH 4
#define WALLS_LIMITS 0.5

Soldier::Soldier(Weapon* weapon, GameMap& map) : weapon(weapon), map(map){} // lo dejo por ahora

Soldier::Soldier(Weapon* weapon,
                 GameMap& map,
                 std::uint16_t x_pos,
                 std::uint16_t y_pos) :
        weapon(weapon),
        map(map),
        x_pos(x_pos),
        y_pos(y_pos) {}

Soldier::Soldier(Weapon *weapon,
                 GameMap &map,
                 std::uint16_t x_pos,
                 std::uint16_t y_pos,
                 float speed) :
        weapon(weapon),
        map(map),
        x_pos(x_pos),
        y_pos(y_pos),
        soldier_speed(speed){}


void Soldier::shoot() {
    std::vector<GameObject*> shooting_objects;
    map.shoot(shooting_objects,
              x_pos,
              y_pos,
              direction);
    weapon->shoot(shooting_objects, y_pos);
}

void Soldier::throw_explosive_grenade() {
    // deberia verificar que no tenga una p90, pq sino estaria haciendo laburar al programa al pedo
    // me ahorraria una operacion costosa

    std::vector<GameObject*> objects;
    std::int16_t y_granade_pos = y_pos;

    if (direction == UP) {
         y_granade_pos -= GRANADE_DISTANCE_REACH;
    } else {
        y_granade_pos += GRANADE_DISTANCE_REACH;
    }

    map.throw_grenade(objects, x_pos, y_granade_pos);
    weapon->throw_explosive_grenade(objects);
}

void Soldier::receive_damage(std::uint16_t damage) {
    health -= damage;
    if (health <= 0) {
        dead = true;
    }
}

void Soldier::move_up() {
    direction = UP;
    // ver si con la interfaz si lo saco o no
    if (y_pos <= WALLS_LIMITS) return;
    // Si no va a cambiar la pos de la matriz, no sigo
    if (floor(y_pos) == floor(y_pos - soldier_speed)) {
        y_pos -= soldier_speed;
        return;
    }
    std::int16_t new_y_pos = -1;
    map.move_soldier_up(floor(x_pos), floor(y_pos), new_y_pos);
    if (new_y_pos >= 0) { // si fue exitoso
        y_pos -= soldier_speed;
    }
}

void Soldier::move_down() {
    direction = DOWN;
    if (static_cast<int16_t>(floor(y_pos)) == static_cast<int16_t>(floor(y_pos + 0.21))) { // con speed_soldier se me va a 10 cuando bajo todo
        y_pos += soldier_speed;
        return;
    }
    std::int16_t new_y_pos = -1;
    map.move_soldier_down(floor(x_pos), floor(y_pos), new_y_pos);
    if(new_y_pos >= 0){
        y_pos += soldier_speed;
    }
}

void Soldier::move_right() {
    double new_x_pos = x_pos + soldier_speed;
    if (std::floor(x_pos) != std::floor(new_x_pos)) {
        //std::cout << "entre\n";
        std::int16_t new_x_pos = -1;
        map.move_soldier_right(floor(x_pos), floor(y_pos), new_x_pos);
        if(new_x_pos >= 0){
            x_pos += soldier_speed;
        }
    } else {
        x_pos += soldier_speed;
    }
}

void Soldier::move_left() {
    if (x_pos <= WALLS_LIMITS) return;
    if (floor(x_pos) == floor(x_pos - soldier_speed)) {
        x_pos -= soldier_speed;
        return;
    }
    std::int16_t new_x_pos = -1;
    map.move_soldier_left(floor(x_pos), floor(y_pos), new_x_pos);
    if(new_x_pos >= 0){
        x_pos -= soldier_speed;
    }
}



void Soldier::set_direction(std::int16_t new_direction) {
    if (new_direction == 1){
        direction = DOWN;
    } else if (new_direction == -1) {
        direction = UP;
    }
}

bool Soldier::in_range_of_explosion(std::int16_t x_start,
                                   std::int16_t x_finish,
                                   std::int16_t y_start,
                                   std::int16_t y_finish) {
    return (x_start <= x_pos && x_pos <= x_finish && y_start <= y_pos && y_pos <= y_finish);
}

Soldier::~Soldier(){
    delete weapon;
}

void Soldier::get_position(std::vector<float> &pos) {
    pos.push_back(x_pos);
    pos.push_back(y_pos);
}

//************************* Metodo de testeo *********************************************

float Soldier::get_y_position() {
    return y_pos;
}

float Soldier::get_x_position() {
    return x_pos;
}


std::int16_t Soldier::get_health() {
    return health;
}