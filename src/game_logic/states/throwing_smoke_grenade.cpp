#include "throwing_smoke_grenade.h"
#include "../game_object.h"
#include "../weapons/weapon.h"
#include "calling_air_strike.h"
#include "throwing_explosive_grenade.h"
#include "dead.h"
#include "being_attacked.h"
#include "reloading.h"
#include "moving.h"
#include "shooting.h"
#include "idle.h"

ThrowingSmokeGrenade::ThrowingSmokeGrenade(float time)  :
start_time(time),
duration_of_throwing_granade(CONFIGURATION.get_soldierState_time_throwing_smoke_grenade()) {}

State* ThrowingSmokeGrenade::update(float time) {
    if (time_stop_throwing(time)) {
        return new Idle();
    }
    return nullptr;
}

State* ThrowingSmokeGrenade::shoot(Soldier& soldier, Weapon* weapon, float time) {
    if (weapon->empty() && time_stop_throwing(time)) return nullptr;
    return new Shooting(soldier, weapon, time);
}

State* ThrowingSmokeGrenade::move(Soldier& soldier, std::int16_t direction, float time) {
    if (!time_stop_throwing(time)) return nullptr;
    return new Moving(soldier, direction, time);
}

State* ThrowingSmokeGrenade::reload(Weapon* weapon, float time) {
    if (weapon->isFullyLoaded() || !time_stop_throwing(time)) return nullptr;
    return new Reloading(weapon, time);
}

State *ThrowingSmokeGrenade::being_attacked(float time) {
    return new BeingAttacked(time);
}

State *ThrowingSmokeGrenade::die(float time) {
    return new Dead(time);
}

State *ThrowingSmokeGrenade::revive(float time) {
    return nullptr;
}

State *ThrowingSmokeGrenade::throw_explosive_grenade(float time) {
    if (time_stop_throwing(time)) {
        return new ThrowingExplosiveGrenade(time);
    }
    return nullptr;
}

State *ThrowingSmokeGrenade::throw_smoke_grenade(float time) {
    start_time = time;
    return nullptr;
}

State *ThrowingSmokeGrenade::call_air_strike(float time) {
    if (time_stop_throwing(time)) {
        return new CallingAirStrike(time);
    }
    return nullptr;
}

State *ThrowingSmokeGrenade::stop_action() {
    return nullptr;
}

bool ThrowingSmokeGrenade::time_stop_throwing(float time) {
    return (time - start_time) >= duration_of_throwing_granade;
}
