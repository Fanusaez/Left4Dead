#ifndef AIR_STRIKE_IDLE_H_
#define AIR_STRIKE_IDLE_H_

#include "air_strike_state.h"

class AirStrikeIdle : public AirStrikeState {

public:
    AirStrikeState* update(float time) override;
    AirStrikeState* call_air_strike(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap& map, AirStrike* air_strike) override;
    AirStrikeState* explode(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap& map, AirStrike* air_strike) override;
};



#endif //AIR_STRIKE_IDLE_H_
