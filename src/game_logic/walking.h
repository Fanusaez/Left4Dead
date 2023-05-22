#ifndef WALKING_H_
#define WALKING_H_

#include "movement.h"
#include "map.h"
class Walking : public Movement {

private:
    float walker_speed = 0.3;
    float& x_pos;
    float& y_pos;
public:
Walking(float& x_pos, float& y_pos);

void chase_soldier(Zombie* zombie,
                    std::int16_t& x_new_pos,
                    std::int16_t& y_new_pos,
                    GameObject* closest_soldier,
                    GameMap& map) override;
};

#endif  // WALKING_H_
