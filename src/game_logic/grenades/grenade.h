#ifndef GRENADE_H_
#define GRENADE_H_

#include <cstdint>
#define CONFIGURATION Configuration::getInstance()

class GameMap;

class Grenade {
public:
    virtual void explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map) = 0;
    virtual ~Grenade() {}
};

#endif //GRENADE_H_
