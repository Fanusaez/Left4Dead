#include "stunned.h"

Stunned::Stunned(float time) : start_time(time) {}

ZombieState* Stunned::chase_soldier(Chaser& chaser,
                                    std::int16_t x_pos_chase,
                                    std::int16_t y_pos_chase,
                                    float time) {

    if (time_to_walk(time) && time_stop_being_stunned(time)) {
        return new Walking(chaser, x_pos_chase, y_pos_chase, time);
    } else if (time_to_walk(time)) {
        last_time_moved = time;
        chaser.chase(x_pos_chase, y_pos_chase);
    }
    return nullptr;
}

ZombieState* Stunned::chase_soldier_running(Chaser& chaser,
                                            std::int16_t x_pos_chase,
                                            std::int16_t y_pos_chase,
                                            float time) {

    if (time_to_walk(time) && time_stop_being_stunned(time)) {
        return new Running(chaser, x_pos_chase, y_pos_chase, time);
    } else if (time_to_walk(time)) {
        last_time_moved = time;
        chaser.chase(x_pos_chase, y_pos_chase);
    }
    return nullptr;
}

ZombieState* Stunned::chase_soldier_jumping(Chaser& chaser,
                                            std::int16_t x_pos_chase,
                                            std::int16_t y_pos_chase,
                                            float time) {

    if (time_to_walk(time) && time_stop_being_stunned(time)) {
        return new Jumping(chaser, x_pos_chase, y_pos_chase, time);
    } else if (time_to_walk(time)) {
        last_time_moved = time;
        chaser.chase(x_pos_chase, y_pos_chase);
    }
    return nullptr;
}

ZombieState* Stunned::attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) {
    if (!time_to_walk(time)) return nullptr;
    return new Attacking(closest_soldier, damage, time);
}

ZombieState* Stunned::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState* Stunned::die(float time) {
    return new ZombieDead(time);
}

ZombieState *Stunned::get_stunned(float time) {
    start_time = time;
    return nullptr;
}

bool Stunned::time_to_walk(float time) {
    return (time - last_time_moved) >= waiting_time_to_walk;
}

bool Stunned::time_stop_being_stunned(float time) {
    return (time - start_time) >= waiting_time_to_normal;
}

void Stunned::set_speed(float speed) {
    waiting_time_to_walk = speed;
}

