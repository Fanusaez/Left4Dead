#include "soldier.h"

Soldier::Soldier(Weapon* weapon) : weapon(weapon){}

void Soldier::get_shot(std::uint16_t damage) {
    health -= damage;
}


Soldier::~Soldier(){
    delete weapon;
}