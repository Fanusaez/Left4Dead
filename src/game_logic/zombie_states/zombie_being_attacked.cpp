#include "zombie_being_attacked.h"
#include "../configuration.h"
#include "attacking_long_range.h"
#include "zombie_idle.h"
#include "running.h"
#include "jumping.h"
#include "zombie_dead.h"
#include "stunned.h"
#include "screaming.h"


ZombieBeingAttacked::ZombieBeingAttacked(float time) :
                        start_time(time),
                        time_stop_being_attacked(CONFIGURATION.get_zombieState_being_attacked_time())
{
    zombie_state = BEING_ATTACKED;
}

ZombieState *ZombieBeingAttacked::update(float time) {
   if (time_to_stop_being_attacked(time)) {
       return new ZombieIdle;
   }
    return nullptr;
}

ZombieState *ZombieBeingAttacked::being_attacked(float time) {
    start_time = time;
    return nullptr;
}

ZombieState *ZombieBeingAttacked::attack_soldier(Soldier* closest_soldier,
                                                 std::int16_t damage,
                                                 float time) {
    if (time_to_stop_being_attacked(time)) {
        return new Attacking(closest_soldier, damage, time);
    }
    return nullptr;
}

ZombieState *ZombieBeingAttacked::attack_soldier_long_range(Soldier* closest_soldier,
                                                 std::int16_t damage,
                                                 float time) {
    if (time_to_stop_being_attacked(time)) {
        return new AttackingLongRange(closest_soldier, damage, time);
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
