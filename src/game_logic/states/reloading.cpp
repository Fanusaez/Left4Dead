#include "reloading.h"
#include "../soldier.h"
Reloading::Reloading(Weapon *weapon, float start_time) :
            weapon(weapon),
            start_time(start_time) {}


State* Reloading::update(float time) {
    return reload(weapon, time);
}

State* Reloading::shoot(Soldier& soldier, Weapon* weapon, float time) {
    // no se puede pasar de reloading a Shooting, charlable
    return reload(weapon, time);
}

State* Reloading::move() {
    // if (time - start_time >= time_to_reload) {
    // weapon -> reload()
    //}
    return this;
}

State* Reloading::reload(Weapon* weapon, float time) {
    if (weapon->isFullyLoaded()) return new Idle;

    if (finished(time)) {
        weapon -> reload();
        return new Idle;
    }
    return nullptr;
}

bool Reloading::finished(float time) {
    return (time - start_time >= time_to_reload);
}