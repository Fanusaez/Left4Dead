#include "zombie_being_attacked.h"

ZombieBeingAttacked::ZombieBeingAttacked(float time) : start_time(time) {}

ZombieState *ZombieBeingAttacked::being_attacked(float time) {
    start_time = time;
    return nullptr;
}

ZombieState *ZombieBeingAttacked::attack_soldier(GameObject *closest_soldier,
                                                 std::int16_t damage,
                                                 float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Attacking(closest_soldier, damage, time);
    }
    return nullptr;
}

ZombieState *ZombieBeingAttacked::chase_soldier(Zombie *zombie, std::int16_t &x_pos, std::int16_t &y_pos, std::int16_t &x_new_pos,
                                                std::int16_t &y_new_pos, GameObject *closest_soldier, GameMap &map,
                                                float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Walking(zombie, x_pos, y_pos, x_new_pos, y_new_pos, closest_soldier, map, time);
    }
    return nullptr;
}

ZombieState *ZombieBeingAttacked::die(float time) {
    return new ZombieDead(time);
}

bool ZombieBeingAttacked::time_to_stop_being_attacked(float time) {
    return (time - start_time >= time_stop_being_attacked);
}

void ZombieBeingAttacked::set_speed(float speed) {}