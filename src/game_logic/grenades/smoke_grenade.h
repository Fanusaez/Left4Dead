#ifndef SMOKE_GRENADE_H_
#define SMOKE_GRENADE_H_

#include "../states/state.h"

class GameMap;

class SmokeGrenade {
private:
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

#endif //SMOKE_GRENADE_H_
