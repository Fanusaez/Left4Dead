#include <cmath>
#include "walking.h"

Walking::Walking(Chaser& chaser,
                 std::int16_t x_pos_chase,
                 std::int16_t y_pos_chase,
                 float time) {

    chase_soldier(chaser, x_pos_chase, y_pos_chase, time);
}

ZombieState* Walking::chase_soldier(Chaser& chaser,
                                    std::int16_t x_pos_chase,
                                    std::int16_t y_pos_chase,
                                    float time) {

    if (time_to_move(time)) {
        last_time_moved = time;
        chaser.chase(x_pos_chase, y_pos_chase);
    }
    return nullptr;
}

ZombieState* Walking::chase_soldier_running(Chaser& chaser,
                                    std::int16_t x_pos_chase,
                                    std::int16_t y_pos_chase,
                                    float time) {
    if (time_to_move(time)) {
        return new Running(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState* Walking::attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) {
    if (!time_to_move(time)) return nullptr;
    return new Attacking(closest_soldier, damage, time);
}

ZombieState* Walking::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState* Walking::die(float time) {
    return new ZombieDead(time);
}

ZombieState* Walking::get_stunned(float time) {
    return new Stunned(time);
}

bool Walking::time_to_move(float time) {
    return (time - last_time_moved) >= waiting_time_to_walk;
}

void Walking::set_speed(float speed) {
    walker_speed = speed;
    // se puede usar para setear que tan frecuentemente se puede mover
    // de otra manera no sirve
}
