#include "dead.h"

Dead::Dead(float time_of_death) : start_time(time_of_death) {}


State *Dead::update(float time) {
    return nullptr;
}

State* Dead::being_attacked(float time) {
    return nullptr;
}

State* Dead::move(Soldier &soldier, std::int16_t direction, float time) {
    return nullptr;
}

State* Dead::reload(Weapon *weapon, float time) {
    return nullptr;
}

State* Dead::shoot(Soldier &soldier, Weapon *weapon, float time) {
    return nullptr;
}

State* Dead::die(float time) {
    return nullptr;
}

State* Dead::revive(float time) {
    if (able_to_revive(time)) {
        return new Idle();
    }
    return nullptr;
}

bool Dead::able_to_revive(float time) {
    return time < time_to_revive + start_time;
}