#ifndef ZOMBIE_H_
#define ZOMBIE_H_

#include <vector>
#include "../game_object.h"

class ZombieState;

class Zombie {

public:
virtual void chase_closest_soldier(std::vector<GameObject*> soldiers, float time) = 0;
virtual bool in_range_of_explosion(std::int16_t x_start,
                                   std::int16_t x_finish,
                                   std::int16_t y_start,
                                   std::int16_t y_finish) = 0;
virtual void set_direction(std::int16_t direction) = 0;
virtual void attack(std::vector<GameObject*> soldiers, float time) = 0;
virtual void get_stunned(float time) = 0;
virtual ZombieState* get_state() = 0;
virtual std::int16_t get_x_matrix_pos() = 0;
virtual std::int16_t get_y_matrix_pos() = 0;
virtual std::int16_t get_x_pos() = 0;
virtual std::int16_t get_y_pos() = 0;


};
#endif   // ZOMBIE_H_