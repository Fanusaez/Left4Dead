#include "soldier.h"

Soldier::Soldier(Weapon* weapon, GameMap& map) : weapon(weapon), map(map){} // lo dejo por ahora

Soldier::Soldier(Weapon* weapon,
                 GameMap& map,
                 std::uint16_t x_pos,
                 std::uint16_t y_pos) :
        weapon(weapon),
        map(map),
        x_pos(x_pos),
        y_pos(y_pos) {}

void Soldier::shoot() {
    std::vector<GameObject*> shooting_objects;
    map.shoot(shooting_objects,
              x_pos,
              y_pos,
              direction);
    weapon->shoot(shooting_objects, y_pos);
}

void Soldier::get_shot(std::uint16_t damage) {
    health -= damage;
    if (health <= 0) {
        dead = true;
    }
}

void Soldier::move_up() {
    direction = UP;
    std::int16_t new_y_pos = -1;
    map.move_soldier_up(x_pos, y_pos, new_y_pos);
    if(new_y_pos >= 0){
        y_pos = new_y_pos;
    }
}

void Soldier::move_down() {
    direction = DOWN;
    std::int16_t new_y_pos = -1;
    map.move_soldier_down(x_pos, y_pos, new_y_pos);
    if(new_y_pos >= 0){
        y_pos = new_y_pos;
    }
}

std::uint16_t Soldier::get_y_position() {
    return y_pos;
}

std::uint16_t Soldier::get_x_position() {
    return x_pos;
}

void Soldier::set_direction(std::int16_t new_direction) {
    if (new_direction == 1){
        direction = DOWN;
    } else if (new_direction == -1) {
        direction = UP;
    }

}

Soldier::~Soldier(){
    delete weapon;
}