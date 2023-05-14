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
    map.shoot(weapon,
              x_pos,
              y_pos,
              direction);
}

void Soldier::get_shot(Weapon* weapon) {
    health -= weapon -> shoot(y_pos);
    if (health <= 0) {
        dead = true;
    }
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