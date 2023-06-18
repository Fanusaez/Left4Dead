#include "reloading.h"
#include "../soldier.h"
#include "calling_air_strike.h"
#include "throwing_smoke_grenade.h"
#include "throwing_explosive_grenade.h"
#include "dead.h"
#include "being_attacked.h"
#include "moving.h"
#include "shooting.h"

Reloading::Reloading(Weapon *weapon, float start_time) :
            weapon(weapon),
            start_time(start_time),
            waiting_time_to_reload(CONFIGURATION.get_soldierState_time_reloading()) {
    soldier_state = RELOADING;
}


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

State *Reloading::throw_explosive_grenade(float time) {
    if (time_to_relaod(time)) {
        return new ThrowingExplosiveGrenade(time);
    }
    return nullptr;
}

State *Reloading::throw_smoke_grenade(float time) {
    if (time_to_relaod(time)) {
        return new ThrowingSmokeGrenade(time);
    }
    return nullptr;
}

State *Reloading::call_air_strike(float time) {
    if (time_to_relaod(time)) {
        return new CallingAirStrike(time);
    }
    return nullptr;
}

State *Reloading::stop_action() {
    return nullptr;
}

bool Reloading::time_to_relaod(float time) { // se deberia llamar de otra forma
    return (time - start_time >= waiting_time_to_reload);
}