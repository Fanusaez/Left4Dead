#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <cstdint>
#include "../../common/game_object_state.h"

class GameMap;
class Zombie;
class Soldier;
class Chaser;

#define CONFIGURATION Configuration::getInstance()

class ZombieState {
private:
public:
ZombieObjectState zombie_state = IDLE_ZOMBIE;

virtual ZombieState* update(float time) = 0;

// deberia ser chase_soldier_walking
virtual ZombieState* chase_soldier(Chaser& chaser,
                                   std::int16_t x_pos_chase,
                                   std::int16_t y_pos_chase,
                                   float time) = 0;

virtual ZombieState* chase_soldier_running(Chaser& chaser,
                                           std::int16_t x_pos_chase,
                                           std::int16_t y_pos_chase,
                                           float time) = 0;

virtual ZombieState* chase_soldier_jumping(Chaser& chaser,
                                           Soldier* soldier,
                                           std::int16_t damage,
                                           std::int16_t x_pos_chase,
                                           std::int16_t y_pos_chase,
                                           float time) = 0;

virtual ZombieState* attack_soldier(Soldier* closest_soldier, std::int16_t damage, float time) = 0;

virtual ZombieState* being_attacked(float time) = 0;

virtual ZombieState* die(float time) = 0;

virtual ZombieState* get_stunned(float time) = 0;

virtual ZombieState* scream(GameMap &map, std::int16_t zombies_to_create, float time) = 0;

virtual void set_speed(float speed) = 0;
};
#endif  // MOVEMENT_H_
