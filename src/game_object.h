#ifndef GAME_OBJECT_H_
#define GAME_OBJECT_H_

class GameObject {
 private:

 public:
virtual void get_shot(std::uint16_t damage) = 0;

};

#endif  // GAME_OBJECT_H_
