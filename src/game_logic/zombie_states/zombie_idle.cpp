#include "zombie_idle.h"

ZombieState *
ZombieIdle::chase_soldier(Zombie *zombie, std::int16_t &x_pos, std::int16_t &y_pos, std::int16_t &x_new_pos, std::int16_t &y_new_pos,
                          GameObject *closest_soldier, GameMap &map, float time) {
    return new Walking(zombie, x_pos, y_pos, x_new_pos, y_new_pos, closest_soldier, map, time);
}

ZombieState *ZombieIdle::attack_soldier(GameObject *closest_soldier, std::int16_t damage, float time) {
    return new Attacking(closest_soldier, damage, time);
}

ZombieState *ZombieIdle::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState *ZombieIdle::die(float time) {
    return new ZombieDead(time);
}

void ZombieIdle::set_speed(float speed) {

}

