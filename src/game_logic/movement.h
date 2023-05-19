#ifndef MOVEMENT_H_
#define MOVEMENT_H_

#include <cstdint>
class GameMap;
class Zombie;
class GameObject;

class Movement {
private:
public:
virtual void chase_soldier(Zombie* zombie,
                           std::int16_t& x_new_pos,
                           std::int16_t& y_new_pos,
                           GameObject* closest_soldier,
                           GameMap& map) = 0;
};
#endif  // MOVEMENT_H_
