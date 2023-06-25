#include "attacking.h"
#include "../soldier.h"
#include "../configuration.h"
#include "attacking_long_range.h"
#include "zombie_idle.h"
#include "running.h"
#include "jumping.h"
#include "zombie_being_attacked.h"
#include "zombie_dead.h"
#include "stunned.h"
#include "screaming.h"


Attacking::Attacking(Soldier* closest_soldier, std::int16_t damage, float time)  :
                    start_time(time),
                    waiting_time_to_attack(CONFIGURATION.get_zombieState_attacking_time())
{
    zombie_state = ATTACKING;
    closest_soldier->receive_damage(damage, time); // lo ataco de una, despues vemos
}


ZombieState *Attacking::update(float time) {
   if (time_to_attack(time)) {
       return new ZombieIdle;
   }
   return nullptr;
}

ZombieState *
Attacking::chase_soldier(Chaser& chaser,
                         std::int16_t x_pos_chase,
                         std::int16_t y_pos_chase,
                         float time) {
    if (time_to_attack(time)) {
        return new Walking(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *
Attacking::chase_soldier_running(Chaser& chaser,
                         std::int16_t x_pos_chase,
                         std::int16_t y_pos_chase,
                         float time) {
    if (time_to_attack(time)) {
        return new Running(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *
Attacking::chase_soldier_jumping(Chaser& chaser,
                                 std::int16_t x_pos_chase,
                                 std::int16_t y_pos_chase,
                                 float time) {
    if (time_to_attack(time)) {
        return new Jumping(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *Attacking::attack_soldier(Soldier* closest_soldier,
                                       std::int16_t damage,
                                       float time) {
    if (time_to_attack(time)) {
        start_time = time;
        closest_soldier->receive_damage(damage, time);
    }
    return nullptr;
}

ZombieState* Attacking::attack_soldier_long_range(Soldier *closest_soldier, std::int16_t damage, float time) {
    if (time_to_attack(time)) {
       return new AttackingLongRange(closest_soldier, damage, time);
    }
    return nullptr;
}

ZombieState* Attacking::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState *Attacking::die(float time) {
    return new ZombieDead(time);
}

ZombieState *Attacking::get_stunned(float time) {
    return new Stunned(time);
}

ZombieState *Attacking::scream(GameMap &map, std::int16_t zombies_to_create, float time) {
    return new Screaming(map, zombies_to_create, time);
}

bool Attacking::time_to_attack(float time) {
    return (time - start_time) >= waiting_time_to_attack;
}

void Attacking::set_speed(float speed) {
    waiting_time_to_attack = speed;
}
