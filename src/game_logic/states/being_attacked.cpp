#include "being_attacked.h"

BeingAttacked::BeingAttacked(float start_time) : start_time(start_time) {}

State *BeingAttacked::update(float time) {
    return being_attacked(time);
}

State *BeingAttacked::reload(Weapon *weapon, float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Reloading(weapon, time);
    }
    return nullptr;
}

State *BeingAttacked::shoot(Soldier &soldier, Weapon *weapon, float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Shooting(soldier, weapon, time);
    }
    return nullptr;
}

State *BeingAttacked::move(Soldier &soldier, std::int16_t direction, float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Moving(soldier, direction, time);
    }
    return nullptr;
}

State *BeingAttacked::being_attacked(float time) {
    return nullptr;
}

State *BeingAttacked::die(float time) {
    return new Dead(time);
}

State *BeingAttacked::revive(float time) {
    return nullptr;
}

bool BeingAttacked::time_to_stop_being_attacked(float time) {
    return (time - start_time >= time_stop_being_attacked);
}