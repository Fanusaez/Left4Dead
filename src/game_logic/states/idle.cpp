#include "idle.h"

State* Idle::update(float time) {
    return nullptr;
}

State* Idle::shoot(Soldier& soldier, Weapon* weapon, float time) {
    if (weapon->empty()) return nullptr;
    return new Shooting(soldier, weapon, time);
}

State* Idle::move(Soldier& soldier, std::int16_t direction, float time) {
    return new Moving(soldier, direction, time);
}

State* Idle::reload(Weapon* weapon, float start_time) {
    if (weapon->isFullyLoaded()) return nullptr;
    return new Reloading(weapon, start_time);
}