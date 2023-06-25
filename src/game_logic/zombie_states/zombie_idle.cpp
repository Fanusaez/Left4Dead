#include "zombie_idle.h"
#include "screaming.h"
#include "attacking_long_range.h"
#include "running.h"
#include "jumping.h"
#include "zombie_being_attacked.h"
#include "zombie_dead.h"
#include "stunned.h"


ZombieState *ZombieIdle::update(float time) {
    return nullptr;
}

ZombieState *
ZombieIdle::chase_soldier(Chaser& chaser,
                          std::int16_t x_pos_chase,
                          std::int16_t y_pos_chase,
                          float time) {
    return new Walking(chaser, x_pos_chase, y_pos_chase, time);
}

ZombieState *
ZombieIdle::chase_soldier_running(Chaser& chaser,
                          std::int16_t x_pos_chase,
                          std::int16_t y_pos_chase,
                          float time) {
    return new Running(chaser, x_pos_chase, y_pos_chase, time);
}

ZombieState *
ZombieIdle::chase_soldier_jumping(Chaser& chaser,
                                  std::int16_t x_pos_chase,
                                  std::int16_t y_pos_chase,
                                  float time) {
    return new Jumping(chaser, x_pos_chase, y_pos_chase, time);
}

ZombieState *ZombieIdle::attack_soldier(Soldier* closest_soldier, std::int16_t damage, float time) {
    return new Attacking(closest_soldier, damage, time);
}

ZombieState *ZombieIdle::attack_soldier_long_range(Soldier *closest_soldier, std::int16_t damage, float time) {
    return new AttackingLongRange(closest_soldier, damage, time);
}

ZombieState *ZombieIdle::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

ZombieState *ZombieIdle::die(float time) {
    return new ZombieDead(time);
}

ZombieState *ZombieIdle::get_stunned(float time) {
    return new Stunned(time);
}

ZombieState *ZombieIdle::scream(GameMap &map, std::int16_t zombies_to_create, float time) {
    return new Screaming(map, zombies_to_create, time);
}

void ZombieIdle::set_speed(float speed) {

}


