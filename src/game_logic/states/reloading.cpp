#include "reloading.h"
#include "../soldier.h"
Reloading::Reloading(Weapon *weapon, float start_time) :
            weapon(weapon),
            start_time(start_time) {}


State* Reloading::update(float time) {
    return reload(weapon, time);
}

State* Reloading::shoot(Soldier& soldier, Weapon* weapon, float time) {
    if (time_to_relaod(time)) {
        weapon->reload();
        return new Shooting(soldier, weapon, time);
    }
    return reload(weapon, time);
}

State* Reloading::move(Soldier& soldier, std::int16_t direction, float time) {
    if (time_to_relaod(time)) {
        weapon->reload();
        return new Moving(soldier, direction, time);
    }
    return nullptr;
}

State* Reloading::reload(Weapon* weapon, float time) {
    if (weapon->isFullyLoaded()) return new Idle;
    if (time_to_relaod(time)) {
        weapon -> reload();
        return new Idle;
    }
    return nullptr;
}

State *Reloading::being_attacked(float time) {
    return new BeingAttacked(time);
}

State *Reloading::die(float time) {
    return new Dead(time);
}

State *Reloading::revive(float time) {
    return nullptr;
}

bool Reloading::time_to_relaod(float time) {
    return (time - start_time >= waiting_time_to_reload);
}