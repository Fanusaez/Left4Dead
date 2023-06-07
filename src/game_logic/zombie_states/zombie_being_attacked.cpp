#include "zombie_being_attacked.h"

ZombieBeingAttacked::ZombieBeingAttacked(float time) : start_time(time) {}

ZombieState *ZombieBeingAttacked::being_attacked(float time) {
    start_time = time;
    return nullptr;
}

ZombieState *ZombieBeingAttacked::attack_soldier(GameObject *closest_soldier,
                                                 std::int16_t damage,
                                                 float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Attacking(closest_soldier, damage, time);
    }
    return nullptr;
}

ZombieState *ZombieBeingAttacked::chase_soldier(Chaser& chaser,
                                                std::int16_t x_pos_chase,
                                                std::int16_t y_pos_chase,
                                                float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Walking(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *ZombieBeingAttacked::chase_soldier_running(Chaser& chaser,
                                                std::int16_t x_pos_chase,
                                                std::int16_t y_pos_chase,
                                                float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Running(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *ZombieBeingAttacked::chase_soldier_jumping(Chaser& chaser,
                                                        std::int16_t x_pos_chase,
                                                        std::int16_t y_pos_chase,
                                                        float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Jumping(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *ZombieBeingAttacked::die(float time) {
    return new ZombieDead(time);
}

ZombieState *ZombieBeingAttacked::get_stunned(float time) {
    return new Stunned(time);
}

ZombieState *ZombieBeingAttacked::scream(GameMap &map, std::int16_t zombies_to_create, float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Screaming(map,zombies_to_create, time);
    }
    return nullptr;
}

bool ZombieBeingAttacked::time_to_stop_being_attacked(float time) {
    return (time - start_time >= time_stop_being_attacked);
}

void ZombieBeingAttacked::set_speed(float speed) {}