#include "running.h"
#include "../configuration.h"


Running::Running(Chaser& chaser,
                 std::int16_t x_pos_chase,
                 std::int16_t y_pos_chase,
                 float time) : waiting_time_to_run(CONFIGURATION.get_zombieState_running_time()) {
    zombie_state = RUNNING;
    chase_soldier_running(chaser, x_pos_chase, y_pos_chase, time);
}

ZombieState *Running::update(float time) {
    if (time_to_move(time)) {
        return new ZombieIdle;
    }
    return nullptr;
}

ZombieState* Running::chase_soldier(Chaser& chaser,
                                    std::int16_t x_pos_chase,
                                    std::int16_t y_pos_chase,
                                    float time) {

    if (time_to_move(time)) {
        return new Walking(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState* Running::chase_soldier_running(Chaser& chaser,
                                    std::int16_t x_pos_chase,
                                    std::int16_t y_pos_chase,
                                    float time) {

    if (time_to_move(time)) {
        last_time_run = time;
        chaser.chase(x_pos_chase, y_pos_chase);
    }
    return nullptr;
}

ZombieState* Running::chase_soldier_jumping(Chaser& chaser,
                                            Soldier* soldier,
                                            std::int16_t damage,
                                            std::int16_t x_pos_chase,
                                            std::int16_t y_pos_chase,
                                            float time) {

    if (time_to_move(time)) {
        return new Jumping(chaser, soldier, damage, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState* Running::attack_soldier(Soldier* closest_soldier, std::int16_t damage, float time) {
    if (!time_to_move(time)) return nullptr;
    return new Attacking(closest_soldier, damage, time);
}

ZombieState* Running::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState* Running::die(float time) {
    return new ZombieDead(time);
}

ZombieState* Running::get_stunned(float time) {
    return new Stunned(time);
}

ZombieState *Running::scream(GameMap &map, std::int16_t zombies_to_create, float time) {
    return new Screaming(map, zombies_to_create, time);
}

bool Running::time_to_move(float time) {
    return (time - last_time_run) >= waiting_time_to_run;
}

void Running::set_speed(float speed) {
     waiting_time_to_run = speed;
}

void Running::set_long_range() {}