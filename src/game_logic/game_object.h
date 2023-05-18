#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class GameObject {
 private:

 public:
virtual void receive_damage(std::uint16_t damage) = 0;
virtual void move_up() = 0;
virtual std::uint16_t get_y_position() = 0;
virtual bool in_range_of_explosion(std::int16_t x_start,
                           std::int16_t x_finish,
                           std::int16_t y_start,
                           std::int16_t y_finish) = 0;
};

#endif  // GAME_OBJECT_H_
