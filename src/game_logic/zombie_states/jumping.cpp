#include "jumping.h"
#include "../soldier.h"
#include "../configuration.h"
#include "attacking_long_range.h"
#include "zombie_idle.h"
#include "../chaser.h"
#include "running.h"
#include "zombie_being_attacked.h"
#include "zombie_dead.h"
#include "stunned.h"
#include "screaming.h"


Jumping::Jumping(Chaser& chaser,
                 std::int16_t x_pos_chase,
                 std::int16_t y_pos_chase,
                 float time) : waiting_time_to_jump(CONFIGURATION.get_zombieState_jumping_time()) {
    zombie_state = JUMPING;
    chase_soldier_jumping(chaser, x_pos_chase, y_pos_chase, time);
}

ZombieState *Jumping::update(float time) {
    return nullptr;
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
Jumping::chase_soldier_jumping(Chaser& chaser,
                               std::int16_t x_pos_chase,
                               std::int16_t y_pos_chase,
                               float time) {
    if (time_to_move(time)) {
        last_time_jumped = time;
        chaser.chase(x_pos_chase, y_pos_chase);
    }
    return nullptr;
}

ZombieState* Jumping::attack_soldier(Soldier* closest_soldier, std::int16_t damage, float time) {
    if (!time_to_move(time)) return nullptr;
    return new Attacking(closest_soldier, damage, time);
}

ZombieState* Jumping::attack_soldier_long_range(Soldier* closest_soldier, std::int16_t damage, float time) {
    if (!time_to_move(time)) return nullptr;
    return new AttackingLongRange(closest_soldier, damage, time);
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

ZombieState* Jumping::scream(GameMap &map, std::int16_t zombies_to_create, float time) {
    return new Screaming(map, zombies_to_create, time);
}

bool Jumping::time_to_move(float time) {
    return (time - last_time_jumped) >= waiting_time_to_jump;
}

void Jumping::set_speed(float speed) {
    waiting_time_to_jump = speed;
}
