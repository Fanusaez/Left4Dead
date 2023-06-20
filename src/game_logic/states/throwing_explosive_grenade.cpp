#include "throwing_explosive_grenade.h"
#include "../game_object.h"
#include "../weapons/weapon.h"
#include "calling_air_strike.h"
#include "throwing_smoke_grenade.h"
#include "dead.h"
#include "being_attacked.h"
#include "reloading.h"
#include "moving.h"
#include "shooting.h"
#include "idle.h"

ThrowingExplosiveGrenade::ThrowingExplosiveGrenade(float time)  :
start_time(time),
duration_of_throwing_granade(CONFIGURATION.get_soldierState_time_throwing_explosive_grenade()) {
    soldier_state = THROWING_GRENADE;
}

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
    start_time = time;
    return nullptr;
}

State *ThrowingExplosiveGrenade::throw_smoke_grenade(float time) {
   if (time_stop_throwing(time)) {
       return new ThrowingSmokeGrenade(time);
   }
    return nullptr;
}

State *ThrowingExplosiveGrenade::call_air_strike(float time) {
    if (time_stop_throwing(time)) {
        return new CallingAirStrike(time);
    }
    return nullptr;
}

State *ThrowingExplosiveGrenade::stop_action() {
    return nullptr;
}

bool ThrowingExplosiveGrenade::time_stop_throwing(float time) {
    return (time - start_time) >= duration_of_throwing_granade;
}




