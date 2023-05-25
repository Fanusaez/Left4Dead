#include "idle.h"

State* Idle::update(float time) {
    return nullptr;
}

State* Idle::shoot(Weapon* weapon, float time) {
    if (weapon->empty()) return nullptr;
    return new Shooting(weapon, time);
}

State* Idle::move() {
    return this; // no va
}

State* Idle::reload(Weapon* weapon, float start_time) {
    if (weapon->isFullyLoaded()) return nullptr;
    return new Reloading(weapon, start_time);
}