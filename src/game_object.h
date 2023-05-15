#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class GameObject {
 private:

 public:
virtual void get_shot(std::uint16_t damage) = 0;
virtual void move_up() = 0;
virtual std::uint16_t get_y_position() = 0;
};

#endif  // GAME_OBJECT_H_
