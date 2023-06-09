#ifndef SMOKE_GRENADE_H_
#define SMOKE_GRENADE_H_

#include "../states/state.h"
#include "grenade.h"
#include "./grenade_state/grenade_state.h"
#include "./grenade_state/grenade_idle.h"


class GameMap;

class SmokeGrenade : public Grenade{
private:
    const float time_to_throw_grenade = 30;
    std::int16_t radius_range = 3;
    float last_thrown_grenade = 0;
    GrenadeState* grenade_state = new GrenadeIdle;

public:

    void update(float time);

    State* throw_grenade(GameMap& map,
                       std::int16_t x_matrix_explosion,
                       std::int16_t y_matrix_sold,
                       State* current_soldier_state,
                       float time);

    void explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map) override;

    bool time_throw_grenade(float time);
};

#endif //SMOKE_GRENADE_H_
