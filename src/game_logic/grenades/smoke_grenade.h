#ifndef SMOKE_GRENADE_H_
#define SMOKE_GRENADE_H_

#include "../states/state.h"
#include "grenade.h"
#include "./grenade_state/grenade_state.h"
#include "./grenade_state/grenade_idle.h"


class GameMap;

class SmokeGrenade : public Grenade{
private:
    const float waiting_time_to_throw_grenade;
    std::int16_t radius_range;
    float last_thrown_grenade = -10;
    std::int16_t left_time_to_throw_grenade;
    GrenadeState* grenade_state = new GrenadeIdle;
    std::int16_t id;

    void update_left_time_to_throw(float time);

public:

    explicit SmokeGrenade(std::int16_t id);

    void update(float time);

    State* throw_grenade(GameMap& map,
                       std::int16_t x_matrix_explosion,
                       std::int16_t y_matrix_sold,
                       State* current_soldier_state,
                       float time);

    void explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map) override;

    bool time_throw_grenade(float time);

    GrenadeState* get_state();

    std::int16_t get_time_to_throw_grenade();

    ~SmokeGrenade();
};

#endif //SMOKE_GRENADE_H_
