#include <cmath>
#include "walking.h"
#include "../chaser.h"
#include "../configuration.h"
#include "attacking_long_range.h"
#include "attacking_long_range.h"
#include "zombie_idle.h"
#include "running.h"
#include "jumping.h"
#include "zombie_being_attacked.h"
#include "zombie_dead.h"
#include "stunned.h"
#include "screaming.h"


Walking::Walking(Chaser& chaser,
                 std::int16_t x_pos_chase,
                 std::int16_t y_pos_chase,
                 float time) : waiting_time_to_walk(CONFIGURATION.get_zombieState_walking_time()) {
    zombie_state = WALKING;
    chase_soldier(chaser, x_pos_chase, y_pos_chase, time);
}

ZombieState *Walking::update(float time) {
    if (time_to_move(time)) {
        return new ZombieIdle;
    }
    return nullptr;
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

ZombieState* Walking::chase_soldier_jumping(Chaser& chaser,
                                            std::int16_t x_pos_chase,
                                            std::int16_t y_pos_chase,
                                            float time) {
    if (time_to_move(time)) {
        return new Jumping(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState* Walking::attack_soldier(Soldier* closest_soldier, std::int16_t damage, float time) {
    return new Attacking(closest_soldier, damage, time);
}

ZombieState* Walking::attack_soldier_long_range(Soldier* closest_soldier, std::int16_t damage, float time) {
    if (!time_to_move(time)) return nullptr;
    return new AttackingLongRange(closest_soldier, damage, time);
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

ZombieState* Walking::scream(GameMap &map, std::int16_t zombies_to_create, float time) {
    return new Screaming(map, zombies_to_create, time);
}

bool Walking::time_to_move(float time) {
    return (time - last_time_moved) >= waiting_time_to_walk;
}

void Walking::set_speed(float speed) {
    waiting_time_to_walk = speed;
}
