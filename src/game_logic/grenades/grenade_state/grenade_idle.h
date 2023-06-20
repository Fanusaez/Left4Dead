#ifndef GRENADE_IDLE_H_
#define GRENADE_IDLE_H_

#include "grenade_state.h"


class GrenadeIdle : public GrenadeState {

private:

public:

    GrenadeState* update(float time) override;
    GrenadeState* throw_grenade(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade) override;
    GrenadeState* explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade) override;
    std::int16_t get_x_explosion() override;
    std::int16_t get_y_explosion() override;
};


#endif //GRENADE_IDLE_H_
