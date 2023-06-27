#include "calling_air_strike.h"
#include "throwing_explosive_grenade.h"
#include "throwing_smoke_grenade.h"
#include "shooting.h"
#include "moving.h"
#include "being_attacked.h"
#include "dead.h"
#include "reloading.h"
#include "idle.h"

CallingAirStrike::CallingAirStrike(float start_time) :
        start_time(start_time),
        time_stop_calling(CONFIGURATION.get_soldierState_time_calling_air_strike())
{
    soldier_state = CALLING_AIR_STRIKE;
}

State *CallingAirStrike::update(float time) {
    if (time_to_stop_calling(time)) {
        return new Idle();
    }
    return nullptr;
}

State *CallingAirStrike::reload(Weapon *weapon, float time) {
    if (time_to_stop_calling(time)) {
        return new Reloading(weapon, time);
    }
    return nullptr;
}

State *CallingAirStrike::shoot(Soldier &soldier, Weapon *weapon, float time) {
    if (time_to_stop_calling(time)) {
        return new Shooting(soldier, weapon, time);
    }
    return nullptr;
}

State *CallingAirStrike::move(Soldier &soldier, std::int16_t direction, float time) {
    if (time_to_stop_calling(time)) {
        return new Moving(soldier, direction, time);
    }
    return nullptr;
}

State *CallingAirStrike::being_attacked(float time) {
    return new BeingAttacked(time);
}

State *CallingAirStrike::die(float time) {
    return new Dead(time);
}

State *CallingAirStrike::revive(float time) {
    return nullptr;
}

State *CallingAirStrike::stop_action() {
    return nullptr;
}

State *CallingAirStrike::throw_explosive_grenade(float time) {
    if (!time_to_stop_calling(time)) return nullptr;
    return new ThrowingExplosiveGrenade(time);
}

State *CallingAirStrike::throw_smoke_grenade(float time) {
    if (!time_to_stop_calling(time)) return nullptr;
    return new ThrowingSmokeGrenade(time);
}

State *CallingAirStrike::call_air_strike(float time) {
    return nullptr;
}

bool CallingAirStrike::time_to_stop_calling(float time) {
    return (time - start_time >= time_stop_calling);
}