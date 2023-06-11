#include "shooting.h"
#include "../soldier.h"
#include "calling_air_strike.h"
#include "throwing_smoke_grenade.h"
#include "throwing_explosive_grenade.h"
#include "dead.h"
#include "being_attacked.h"
#include "reloading.h"
#include "moving.h"

Shooting::Shooting(Soldier& soldier, Weapon *weapon, float start_time) :
                    soldier(soldier),
                    weapon(weapon){
    soldier_state = SHOOTING;
    shoot(soldier, weapon, start_time);
}

State *Shooting::update(float time) {
    return shoot(soldier, weapon, time);
}

State* Shooting::shoot(Soldier& soldier, Weapon* weapon, float time) {
    if (time_to_shoot(time) && !weapon->empty()) {
        start_time = time; // actalizo ultimo disparo
        std::vector<GameObject*> targets = soldier.get_targets();
        std::int16_t x_pos = soldier.get_x_matrix_pos();
        weapon->shoot(targets, x_pos, time);
    } else if (weapon->empty()) {
        return new Idle();
    }
    return nullptr;
}

State* Shooting::move(Soldier& soldier, std::int16_t direction, float time) {
    return new Moving(soldier, direction, time);
}

State *Shooting::reload(Weapon *weapon, float time) {
    if (weapon->isFullyLoaded()) return nullptr;
    return new Reloading(weapon, time);
}

State *Shooting::being_attacked(float time) {
    return new BeingAttacked(time);
}

State *Shooting::die(float time) {
    return new Dead(time);
}

State *Shooting::revive(float time) {
    return nullptr;
}

State *Shooting::throw_explosive_grenade(float time) {
    if (time_to_shoot(time)) {
        return new ThrowingExplosiveGrenade(time);
    }
    return nullptr;
}

State *Shooting::throw_smoke_grenade(float time) {
    if (time_to_shoot(time)) {
        return new ThrowingSmokeGrenade(time);
    }
    return nullptr;
}

State *Shooting::call_air_strike(float time) {
    if (time_to_shoot(time)) {
        return new CallingAirStrike(time);;
    }
    return nullptr;
}

State *Shooting::stop_action() {
    return new Idle();
}

bool Shooting::time_to_shoot(float time) {
    return (time - start_time) > waiting_time_to_shoot;
}
