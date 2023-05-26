#include "attacking.h"

Attacking::Attacking(GameObject *closest_soldier, std::int16_t damage, float time) {
    attack_soldier(closest_soldier, damage, time);
}

ZombieState *
Attacking::chase_soldier(Zombie *zombie,
                         float &x_pos,
                         float &y_pos,
                         std::int16_t &x_new_pos,
                         std::int16_t &y_new_pos,
                         GameObject *closest_soldier,
                         GameMap &map, float time) {
    if (time_to_attack(time)) {
        return new Walking(zombie, x_pos, y_pos, x_new_pos, y_new_pos, closest_soldier, map, time);
    }
    return nullptr;
}

ZombieState *Attacking::attack_soldier(GameObject *closest_soldier,
                                       std::int16_t damage,
                                       float time) {
    if (time_to_attack(time)) {
        start_time = time;
        closest_soldier->receive_damage(damage);
    }
    return nullptr;
}

bool Attacking::time_to_attack(float time) {
    return (time - start_time) >= waiting_time_to_attack;
}

void Attacking::set_speed(float speed) {
    attack_speed = speed;
}