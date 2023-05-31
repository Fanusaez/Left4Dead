#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <cstdint>
class GameMap;
class Zombie;
class GameObject;

class ZombieState {
private:
public:

virtual ZombieState* chase_soldier(Zombie* zombie,
                                   std::int16_t& x_pos,
                                   std::int16_t& y_pos,
                                   std::int16_t &x_new_pos,
                                   std::int16_t &y_new_pos,
                                   GameObject* closest_soldier,
                                   GameMap& map,
                                   float time) = 0;

virtual ZombieState* attack_soldier(GameObject* closest_soldier, std::int16_t damage, float time) = 0;

virtual ZombieState* being_attacked(float time) = 0;

virtual ZombieState* die(float time) = 0;

virtual void set_speed(float speed) = 0;
};
#endif  // MOVEMENT_H_
