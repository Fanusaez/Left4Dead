#include "shooting.h"

Shooting::Shooting(Weapon *weapon, float start_time) :
                    weapon(weapon),
                    start_time(start_time) {
    //weapon->shoot();
}

State *Shooting::update(float time) {

    if (time_to_shoot(time) && !weapon->empty()) {
        start_time = time; // actalizo ultimo disparo
        //weapon->shoot() tengo que ver como resolver esto
        return nullptr;
    } else if (time_to_shoot(time) && weapon->empty()) {
        return new Idle();
    }
    return nullptr;
}

State *Shooting::shoot(Weapon *weapon, float time) {
    return update(time);
}

State* Shooting::move() {
    return nullptr;
}

State *Shooting::reload(Weapon *weapon, float start_time) {
    if (weapon->isFullyLoaded()) return nullptr;
    return new Reloading(weapon, start_time);
}

bool Shooting::time_to_shoot(float time) {
    return (time - start_time) > waiting_time_to_shoot;
}
