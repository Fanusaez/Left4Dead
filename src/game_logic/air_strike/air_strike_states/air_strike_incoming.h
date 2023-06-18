#ifndef AIR_STRIKE_INCOMING_H_
#define AIR_STRIKE_INCOMING_H_

#include "air_strike_state.h"

class AirStrikeIncoming : public AirStrikeState {
private:
    float _time_to_explode;
    float start_time;
    std::int16_t x_soldier;
    std::int16_t y_soldier;
    GameMap& map;
    AirStrike* air_strike;

public:

    AirStrikeIncoming(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap& map, AirStrike* air_strike);

    AirStrikeState* update(float time) override;
    AirStrikeState* call_air_strike(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap& map, AirStrike* air_strike) override;
    AirStrikeState* explode(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap& map, AirStrike* air_strike) override;

    bool time_to_explode(float time);
};


#endif //AIR_STRIKE_INCOMING_H_
