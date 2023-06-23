#ifndef AIR_STRIKE_STATE_H_
#define AIR_STRIKE_STATE_H_

#include <cstdint>

class GameMap;
class AirStrike;

class AirStrikeState {
public:
    virtual AirStrikeState* update(float time) = 0;
    virtual AirStrikeState* call_air_strike(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap& map, AirStrike* air_strike) = 0;
    virtual AirStrikeState* explode(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap& map, AirStrike* air_strike) = 0;
    virtual bool exploding() = 0;
};

#endif  // AIR_STRIKE_STATE_H_
