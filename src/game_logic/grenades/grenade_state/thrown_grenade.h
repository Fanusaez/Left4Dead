#ifndef THROWN_GRENADE_H_
#define THROWN_GRENADE_H_

#include "grenade_state.h"

class ThrownGrenade : public GrenadeState {

private:
    GameMap& map;
    Grenade* grenade;
    std::int16_t x_explosion;
    std::int16_t y_explosion;
    float start_time;
    float _time_to_explode;

public:
    ThrownGrenade(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade);

    GrenadeState* update(float time) override;
    GrenadeState* throw_grenade(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade) override;
    GrenadeState* explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade) override;

    bool time_to_explode(float time);
};


#endif //THROWN_GRENADE_H_
