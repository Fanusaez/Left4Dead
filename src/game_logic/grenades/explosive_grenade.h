#ifndef EXPLOSIVE_H_
#define EXPLOSIVE_H_

#include "../map.h"
#include "../states/state.h"

class ExplosiveGrenade {

private:
    const std::int16_t grenade_damage = 40;
    const float time_to_throw_grenade = 30;
    std::int16_t radius_range = 3;
    float last_thrown_grenade = 0;
public:
    void throw_grenade(GameMap& map,
                       std::int16_t x_matrix_explosion,
                       std::int16_t y_matrix_sold,
                       State*& current_state,
                       float time);

    bool time_throw_grenade(float time);
};


#endif //EXPLOSIVE_H_
