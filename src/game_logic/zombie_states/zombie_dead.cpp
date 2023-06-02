#include "zombie_dead.h"

ZombieDead::ZombieDead(float time) : start_time(time) {}

ZombieState*
ZombieDead::chase_soldier(Chaser& chaser,
                          std::int16_t x_pos_chase,
                          std::int16_t y_pos_chase,
                          float time) {
    return nullptr;
}

ZombieState* ZombieDead::attack_soldier(GameObject *closest_soldier, std::int16_t damage, float time) {
    return nullptr;
}

ZombieState* ZombieDead::being_attacked(float time) {
    return nullptr;
}

ZombieState *ZombieDead::die(float time) {
    return nullptr;
}

void ZombieDead::set_speed(float speed) {

}