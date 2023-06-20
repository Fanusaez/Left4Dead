#ifndef EXPLOSIVE_H_
#define EXPLOSIVE_H_

#include "../states/state.h"
#include "grenade.h"
#include "grenade_state/grenade_idle.h"

class GameMap;

class ExplosiveGrenade : public Grenade {

private:
    const std::int16_t grenade_damage;
    const float time_to_throw_grenade;
    std::int16_t radius_range;
    float last_thrown_grenade = -10;
    GrenadeState* grenade_state = new GrenadeIdle;

public:
    std::int16_t id;

    explicit ExplosiveGrenade(std::int16_t id);

    void update(float time);

    State* throw_grenade(GameMap& map,
                       std::int16_t x_matrix_explosion,
                       std::int16_t y_matrix_sold,
                       State* current_state,
                       float time);

    void explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map);

    bool time_throw_grenade(float time);

    ~ExplosiveGrenade();

    GrenadeState* get_state();
};


#endif //EXPLOSIVE_H_
