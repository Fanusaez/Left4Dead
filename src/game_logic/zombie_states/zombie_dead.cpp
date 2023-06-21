#include "zombie_dead.h"

ZombieDead::ZombieDead(float time) {
    zombie_state = DEAD;
}

ZombieState *ZombieDead::update(float time) {
    return nullptr;
}

ZombieState*
ZombieDead::chase_soldier(Chaser& chaser,
                          std::int16_t x_pos_chase,
                          std::int16_t y_pos_chase,
                          float time) {
    return nullptr;
}

ZombieState*
ZombieDead::chase_soldier_running(Chaser& chaser,
                          std::int16_t x_pos_chase,
                          std::int16_t y_pos_chase,
                          float time) {
    return nullptr;
}

ZombieState*
ZombieDead::chase_soldier_jumping(Chaser& chaser,
                                  Soldier* soldier,
                                  std::int16_t damage,
                                  std::int16_t x_pos_chase,
                                  std::int16_t y_pos_chase,
                                  float time) {
    return nullptr;
}

ZombieState* ZombieDead::attack_soldier(Soldier* closest_soldier, std::int16_t damage, float time) {
    return nullptr;
}

ZombieState* ZombieDead::being_attacked(float time) {
    return nullptr;
}

ZombieState *ZombieDead::die(float time) {
    return nullptr;
}

ZombieState *ZombieDead::get_stunned(float time) {
    return nullptr;
}

ZombieState *ZombieDead::scream(GameMap &map, std::int16_t zombies_to_create, float time) { return nullptr;}

void ZombieDead::set_speed(float speed) {

}