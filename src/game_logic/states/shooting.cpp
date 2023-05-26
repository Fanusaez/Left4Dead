#include "shooting.h"
#include "../soldier.h"

Shooting::Shooting(Soldier& soldier, Weapon *weapon, float start_time) :
                    soldier(soldier),
                    weapon(weapon),
                    start_time(start_time) {
    soldier.shoot();
}

State *Shooting::update(float time) {
    /*
     * aca se tiene que decidir si update es para parar de disparar, o para seguir disparando.
     */
    if (time_to_shoot(time)) {
        return new Idle;
    }
    return nullptr;
}

State* Shooting::shoot(Soldier& soldier, Weapon* weapon, float time) {
    if (time_to_shoot(time) && !weapon->empty()) {
        start_time = time; // actalizo ultimo disparo
        soldier.shoot();
    } else if (weapon->empty()) {
        return new Idle();
    }
    return nullptr;
}

State* Shooting::move(Soldier& soldier, std::int16_t direction, float time) {
    return new Moving(soldier, direction, time);
}

State *Shooting::reload(Weapon *weapon, float start_time) {
    if (weapon->isFullyLoaded()) return nullptr;
    return new Reloading(weapon, start_time);
}

bool Shooting::time_to_shoot(float time) {
    return (time - start_time) > waiting_time_to_shoot;
}
