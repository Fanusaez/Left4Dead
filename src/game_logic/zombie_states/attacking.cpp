#include "attacking.h"

Attacking::Attacking(GameObject *closest_soldier, std::int16_t damage, float time)  : start_time(time) {
    /*
     * Me parece que al atacar no deberia inmediatamente atacar, sino esperar
     * a que pas el tiempo, y recien ahi danar al soldado
     */
    //attack_soldier(closest_soldier, damage, time);
    closest_soldier->receive_damage(damage, time); // lo ataco de una, despues vemos
}

ZombieState *
Attacking::chase_soldier(Chaser& chaser,
                         std::int16_t x_pos_chase,
                         std::int16_t y_pos_chase,
                         float time) {
    if (time_to_attack(time)) {
        return new Walking(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *
Attacking::chase_soldier_running(Chaser& chaser,
                         std::int16_t x_pos_chase,
                         std::int16_t y_pos_chase,
                         float time) {
    if (time_to_attack(time)) {
        return new Running(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *Attacking::attack_soldier(GameObject *closest_soldier,
                                       std::int16_t damage,
                                       float time) {
    if (time_to_attack(time)) {
        start_time = time;
        closest_soldier->receive_damage(damage, time);
    }
    return nullptr;
}

ZombieState* Attacking::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState *Attacking::die(float time) {
    return new ZombieDead(time);
}

bool Attacking::time_to_attack(float time) {
    return (time - start_time) >= waiting_time_to_attack;
}

void Attacking::set_speed(float speed) {
    attack_speed = speed;
}