#include "throwing_explosive_grenade.h"
#include "../game_object.h"
#include "../weapons/weapon.h"

ThrowingExplosiveGrenade::ThrowingExplosiveGrenade(float time)  : start_time(time){}

State* ThrowingExplosiveGrenade::update(float time) {
    if (time_stop_throwing(time)) {
        return new Idle();
    }
    return nullptr;
}

State* ThrowingExplosiveGrenade::shoot(Soldier& soldier, Weapon* weapon, float time) {
    if (weapon->empty() && time_stop_throwing(time)) return nullptr;
    return new Shooting(soldier, weapon, time);
}

State* ThrowingExplosiveGrenade::move(Soldier& soldier, std::int16_t direction, float time) {
    if (!time_stop_throwing(time)) return nullptr;
    return new Moving(soldier, direction, time);
}

State* ThrowingExplosiveGrenade::reload(Weapon* weapon, float time) {
    if (weapon->isFullyLoaded() || !time_stop_throwing(time)) return nullptr;
    return new Reloading(weapon, time);
}

State *ThrowingExplosiveGrenade::being_attacked(float time) {
    return new BeingAttacked(time);
}

State *ThrowingExplosiveGrenade::die(float time) {
    return new Dead(time);
}

State *ThrowingExplosiveGrenade::revive(float time) {
    return nullptr;
}

State *ThrowingExplosiveGrenade::throw_explosive_grenade(float time) {
    return nullptr;
}

State *ThrowingExplosiveGrenade::stop_action() {
    return nullptr;
}

bool ThrowingExplosiveGrenade::time_stop_throwing(float time) {
    return (time - start_time) >= duration_of_throwing_granade;
}




