#include "running.h"

Running::Running(Chaser& chaser,
                 std::int16_t x_pos_chase,
                 std::int16_t y_pos_chase,
                 float time) : start_time(start_time - waiting_time_to_walk) {

    chase_soldier(chaser, x_pos_chase, y_pos_chase, time);
}

ZombieState* Running::chase_soldier(Chaser& chaser,
                                    std::int16_t x_pos_chase,
                                    std::int16_t y_pos_chase,
                                    float time) {

    if (time_to_walk(time)) {
        return new Walking(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState* Running::chase_soldier_running(Chaser& chaser,
                                    std::int16_t x_pos_chase,
                                    std::int16_t y_pos_chase,
                                    float time) {

    if (time_to_walk(time)) {
        start_time = time;
    } else {
        return nullptr;
    }
    chaser.chase(x_pos_chase, y_pos_chase);
    return nullptr;
}

ZombieState* Running::attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) {
    if (!time_to_walk(time)) return nullptr;
    return new Attacking(closest_soldier, damage, time);
}

ZombieState* Running::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState* Running::die(float time) {
    return new ZombieDead(time);
}

bool Running::time_to_walk(float time) {
    return (time - start_time) >= waiting_time_to_walk;
}

void Running::set_speed(float speed) {
     waiting_time_to_walk = speed;
}
