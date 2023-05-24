#include "reloading.h"

Reloading::Reloading(Weapon *weapon, float start_time) :
            weapon(weapon),
            start_time(start_time) {}


State* Reloading::update(float time) {
    if (weapon->isFullyLoaded()) return new Idle;

    if (finished(time)) {
        weapon -> reload();
        return new Idle;
    } else {
        return nullptr;
    }
}

State* Reloading::shoot(Weapon* weapon, float time) {
    return nullptr;
}

State* Reloading::move() {
    // if (time - start_time >= time_to_reload) {
    // weapon -> reload()
    //}
    return this;
}

State* Reloading::reload(Weapon* weapon, float time) {
    return update(time);
}

bool Reloading::finished(float time) {
    return (time - start_time >= time_to_reload);
}