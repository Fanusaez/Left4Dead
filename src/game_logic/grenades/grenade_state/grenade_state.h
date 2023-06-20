#ifndef GRENADE_STATE_H_
#define GRENADE_STATE_H_

#include <cstdint>
#define CONFIGURATION Configuration::getInstance()

class Grenade;
class GameMap;

class GrenadeState {

public:
    virtual GrenadeState* update(float time) = 0;
    virtual GrenadeState* throw_grenade(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade) = 0;
    virtual GrenadeState* explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade) = 0;
    virtual std::int16_t get_x_explosion() = 0;
    virtual std::int16_t get_y_explosion() = 0;

    virtual bool exploting() = 0;
};

#endif  // GRENADE_STATE_H_
