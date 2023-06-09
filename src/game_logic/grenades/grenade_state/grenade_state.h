#ifndef GRENADE_STATE_H_
#define GRENADE_STATE_H_

#include <cstdint>

class Grenade;
class GameMap;

class GrenadeState {

public:
    virtual GrenadeState* update(float time) = 0;
    virtual GrenadeState* throw_grenade(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade) = 0;
    virtual GrenadeState* explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade) = 0;
};

#endif  // GRENADE_STATE_H_
