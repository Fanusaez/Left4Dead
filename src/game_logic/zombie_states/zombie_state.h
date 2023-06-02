#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <cstdint>
class GameMap;
class Zombie;
class GameObject;
class Chaser;

class ZombieState {
private:
public:
// deberia ser chase_soldier_walking
virtual ZombieState* chase_soldier(Chaser& chaser,
                                   std::int16_t x_pos_chase,
                                   std::int16_t y_pos_chase,
                                   float time) = 0;

virtual ZombieState* chase_soldier_running(Chaser& chaser,
                                           std::int16_t x_pos_chase,
                                           std::int16_t y_pos_chase,
                                           float time) = 0;

virtual ZombieState* attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) = 0;

virtual ZombieState* being_attacked(float time) = 0;

virtual ZombieState* die(float time) = 0;

virtual void set_speed(float speed) = 0;
};
#endif  // MOVEMENT_H_
