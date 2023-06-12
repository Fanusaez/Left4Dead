#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_
#include <vector>
#include <cstdint>

#define MOVEMENTS_PER_CELL 2
#define DOWN 1
#define UP -1
#define LEFT 2
#define RIGHT 3

class GameObject {
 private:

 public:
virtual std::int16_t get_x_matrix_pos() = 0;
virtual std::int16_t get_y_matrix_pos() = 0;
virtual std::int16_t get_x_pos() = 0;
virtual std::int16_t get_y_pos() = 0;
virtual void receive_damage(std::uint16_t damage, float time) = 0;
virtual bool in_range_of_explosion(std::int16_t x_start,
                           std::int16_t x_finish,
                           std::int16_t y_start,
                           std::int16_t y_finish) = 0;
virtual void get_stunned(float time) = 0;

virtual void set_direction(std::int16_t direction) = 0;
virtual std::int16_t get_id() = 0;
};

#endif  // GAME_OBJECT_H_
