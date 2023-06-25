#include "screaming.h"
#include "../map.h"
#include "../configuration.h"
#include "attacking_long_range.h"
#include "zombie_idle.h"
#include "running.h"
#include "jumping.h"
#include "zombie_being_attacked.h"
#include "zombie_dead.h"
#include "stunned.h"


Screaming::Screaming(GameMap &map, std::int16_t zombies_to_create, float time) :
    waiting_time_to_stop_screaming(CONFIGURATION.get_zombieState_screaming_time())
{
    zombie_state = SCREAMING;    
    scream(map, zombies_to_create, time);
}


ZombieState *Screaming::update(float time) {
    if (time_stop_screaming(time)) {
        return new ZombieIdle;
    }
    return nullptr;
}

ZombieState *Screaming::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

// atacara la witcher?
ZombieState *Screaming::attack_soldier(Soldier *closest_soldier,
                                                 std::int16_t damage,
                                                 float time) {
    if (time_stop_screaming(time)) {
        return new Attacking(closest_soldier, damage, time);
    }
    return nullptr;
}

ZombieState *Screaming::attack_soldier_long_range(Soldier *closest_soldier,
                                       std::int16_t damage,
                                       float time) {
    if (time_stop_screaming(time)) {
        return new AttackingLongRange(closest_soldier, damage, time);
    }
    return nullptr;
}

ZombieState *Screaming::chase_soldier(Chaser& chaser,
                                                std::int16_t x_pos_chase,
                                                std::int16_t y_pos_chase,
                                                float time) {
    if (time_stop_screaming(time)) {
        return new Walking(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *Screaming::chase_soldier_running(Chaser& chaser,
                                              std::int16_t x_pos_chase,
                                              std::int16_t y_pos_chase,
                                              float time) {
    if (time_stop_screaming(time)) {
        return new Running(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *Screaming::chase_soldier_jumping(Chaser& chaser,
                                              std::int16_t x_pos_chase,
                                              std::int16_t y_pos_chase,
                                              float time) {
    if (time_stop_screaming(time)) {
        return new Jumping(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *Screaming::die(float time) {
    return new ZombieDead(time);
}

ZombieState *Screaming::get_stunned(float time) {
    return new Stunned(time);
}

ZombieState *Screaming::scream(GameMap &map, std::int16_t zombies_to_create, float time) {
   if (!time_stop_screaming(time)) return nullptr;
   last_time_screamed = time;
   for(int i = 0; i < zombies_to_create; i++) {
       map.add_random_zombie();
   }
    return nullptr;
}

bool Screaming::time_stop_screaming(float time) {
    return (time - last_time_screamed) >= waiting_time_to_stop_screaming;
}

void Screaming::set_speed(float speed) {}
