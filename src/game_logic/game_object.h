#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_
#include <vector>

class GameObject {
 private:

 public:
virtual void get_position(std::vector<float>& pos) = 0;
virtual void receive_damage(std::uint16_t damage) = 0;
virtual bool in_range_of_explosion(std::int16_t x_start,
                           std::int16_t x_finish,
                           std::int16_t y_start,
                           std::int16_t y_finish) = 0;

virtual void set_direction(std::int16_t direction) = 0;

};

#endif  // GAME_OBJECT_H_
