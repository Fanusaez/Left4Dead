#include "zombie_idle.h"

ZombieState *
ZombieIdle::chase_soldier(Chaser& chaser,
                          std::int16_t x_pos_chase,
                          std::int16_t y_pos_chase,
                          float time) {
    return new Walking(chaser, x_pos_chase, y_pos_chase, time);
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

