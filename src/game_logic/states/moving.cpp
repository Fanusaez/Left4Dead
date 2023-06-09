#include "moving.h"
#include "../soldier.h"


#define DOWN 1
#define UP -1
#define LEFT 2
#define RIGHT 3

Moving::Moving(Soldier &soldier, std::int16_t direction, float start_time) :
                soldier(soldier),
                direction(direction) {
    soldier_state = MOVING;
    move(soldier, direction, start_time);
}

State *Moving::update(float time) {
    return move(soldier, direction, time);
}

State *Moving::reload(Weapon *weapon, float start_time) {
    if (!time_to_move(start_time)) return nullptr;
    if (weapon->isFullyLoaded()) return new Idle();
    return new Reloading(weapon, start_time);
}

State *Moving::shoot(Soldier &soldier, Weapon *weapon, float time) {
    if (!time_to_move(time)) return nullptr;
    if (weapon->empty()) return new Idle();
    return new Shooting(soldier, weapon, time);
}

State* Moving::move(Soldier& soldier, std::int16_t direction, float time) {
    if (direction == UP) soldier.move_up();
    else if (direction == DOWN) soldier.move_down();
    else if (direction == RIGHT) soldier.move_right();
    else if (direction == LEFT) soldier.move_left();
    return nullptr;
}

State *Moving::being_attacked(float time) {
    return new BeingAttacked(time);
}

State *Moving::die(float time) {
    return new Dead(time);
}

State *Moving::revive(float time) {
    return nullptr;
}

State *Moving::throw_explosive_grenade(float time) {
    if (time_to_move(time)) {
        return new ThrowingExplosiveGrenade(time);
    }
    return nullptr;
}

State *Moving::throw_smoke_grenade(float time) {
    if (time_to_move(time)) {
        return new ThrowingSmokeGrenade(time);
    }
    return nullptr;
}

State *Moving::stop_action() {
    return new Idle();
}

bool Moving::time_to_move(float time) {
    return (time - last_time_moved) >= waiting_time_to_move;
}