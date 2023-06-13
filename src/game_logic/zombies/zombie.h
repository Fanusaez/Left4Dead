#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include <vector>
#include <cstdint>
#include "../../common/zombie_type.h"

#define MAX_DISTANCE 10000

class ZombieState;
class GameObject;
class Soldier;
class Zombie {

public:
virtual void update(std::vector<Soldier*> soldiers, float time) = 0; // puede recibir los soldados tambien
virtual void chase_closest_soldier(std::vector<Soldier*> soldiers, float time) = 0;
virtual bool in_range_of_explosion(std::int16_t x_start,
                                   std::int16_t x_finish,
                                   std::int16_t y_start,
                                   std::int16_t y_finish) = 0;
virtual void set_direction(std::int16_t direction) = 0;
virtual void attack(std::vector<Soldier*> soldiers, float time) = 0;
virtual void get_stunned(float time) = 0;
virtual ZombieState* get_state() = 0;
virtual std::int16_t get_x_matrix_pos() = 0;
virtual std::int16_t get_y_matrix_pos() = 0;
virtual std::int16_t get_x_pos() = 0;
virtual std::int16_t get_y_pos() = 0;
virtual bool facing_left() = 0;
virtual std::int16_t get_id() = 0;
virtual ZombieType get_type() = 0;
virtual ~Zombie() {};

};
#endif   // ZOMBIE_H_
