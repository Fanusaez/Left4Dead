#include "idle.h"
#include "../weapons/weapon.h"
#include "calling_air_strike.h"
#include "shooting.h"
#include "moving.h"
#include "being_attacked.h"
#include "dead.h"
#include "throwing_explosive_grenade.h"
#include "throwing_smoke_grenade.h"
#include "reloading.h"

Idle::Idle() {
    soldier_state = IDLE_SOLDIER;
}

State* Idle::update(float time) {
    return nullptr;
}

State* Idle::shoot(Soldier& soldier, Weapon* weapon, float time) {
    if (weapon->empty() || !weapon->time_to_shoot(time)) return nullptr;
    return new Shooting(soldier, weapon, time);
}

State* Idle::move(Soldier& soldier, std::int16_t direction, float time) {
    return new Moving(soldier, direction, time);
}

State* Idle::reload(Weapon* weapon, float start_time) {
    if (weapon->isFullyLoaded()) return nullptr;
    return new Reloading(weapon, start_time);
}

State *Idle::being_attacked(float time) {
    return new BeingAttacked(time);
}

State *Idle::die(float time) {
    return new Dead(time);
}

State *Idle::revive(float time) {
    return nullptr;
}

State *Idle::throw_explosive_grenade(float time) {
    return new ThrowingExplosiveGrenade(time);
}

State *Idle::throw_smoke_grenade(float time) {
    return new ThrowingSmokeGrenade(time);
}

State *Idle::call_air_strike(float time) {
    return new CallingAirStrike(time);
}

State *Idle::stop_action() {
    return nullptr;
}