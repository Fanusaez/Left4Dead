#include "zombie_dead.h"

ZombieDead::ZombieDead(float time) : start_time(time) {}

ZombieState*
ZombieDead::chase_soldier(Zombie *zombie, float &x_pos, float &y_pos, std::int16_t &x_new_pos, std::int16_t &y_new_pos,
                          GameObject *closest_soldier, GameMap &map, float time) {
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