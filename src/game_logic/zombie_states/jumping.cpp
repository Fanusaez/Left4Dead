#include "jumping.h"


Jumping::Jumping(Chaser& chaser,
                 std::int16_t x_pos_chase,
                 std::int16_t y_pos_chase,
                 float time)  {

    chase_soldier_jumping(chaser, x_pos_chase, y_pos_chase, time);
}

ZombieState* Jumping::chase_soldier(Chaser& chaser,
                                    std::int16_t x_pos_chase,
                                    std::int16_t y_pos_chase,
                                    float time) {

    if (time_to_move(time)) {
        return new Walking(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState* Jumping::chase_soldier_running(Chaser& chaser,
                                            std::int16_t x_pos_chase,
                                            std::int16_t y_pos_chase,
                                            float time) {

    if (time_to_move(time)) {
        return new Running(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *
Jumping::chase_soldier_jumping(Chaser &chaser,
                               std::int16_t x_pos_chase,
                               std::int16_t y_pos_chase,
                               float time) {
    if (time_to_move(time)) {
        last_time_moved = time;
        chase_soldier_jumping(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState* Jumping::attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) {
    if (!time_to_move(time)) return nullptr;
    return new Attacking(closest_soldier, damage, time);
}

ZombieState* Jumping::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState* Jumping::die(float time) {
    return new ZombieDead(time);
}

ZombieState* Jumping::get_stunned(float time) {
    return new Stunned(time);
}

bool Jumping::time_to_move(float time) {
    return (time - last_time_moved) >= waiting_time_to_move;
}

void Jumping::set_speed(float speed) {
    waiting_time_to_move = speed;
}

