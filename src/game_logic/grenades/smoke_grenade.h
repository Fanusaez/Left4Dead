#ifndef SMOKE_GRENADE_H_
#define SMOKE_GRENADE_H_
#include "../map.h"
#include "../states/state.h"

class SmokeGrenade {
private:
    const float time_to_throw_grenade = 30;
    float last_thrown_grenade = 0;
public:
    void throw_grenade(GameMap& map,
                       std::int16_t x_matrix_sold,
                       std::int16_t y_matrix_explosion,
                       State*& current_state,
                       float time);

    bool time_throw_grenade(float time);
};

#endif //SMOKE_GRENADE_H_
