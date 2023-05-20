#ifndef WALKING_H_
#define WALKING_H_

#include "movement.h"
#include "map.h"
class Walking : public Movement {

private:

public:
void chase_soldier(Zombie* zombie,
                    std::int16_t& x_new_pos,
                    std::int16_t& y_new_pos,
                    GameObject* closest_soldier,
                    GameMap& map) override;
};

#endif  // WALKING_H_
