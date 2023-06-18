#ifndef AIR_STRIKE_EXPLODING_H_
#define AIR_STRIKE_EXPLODING_H_

#include "air_strike_state.h"

class AirStrikeExploding : public AirStrikeState {
private:
    float start_time;
    float time_stop_exploding;
public:
    AirStrikeExploding(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap& map, AirStrike* air_strike);

    AirStrikeState* update(float time) override;
    AirStrikeState* call_air_strike(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap& map, AirStrike* air_strike) override;
    AirStrikeState* explode(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap& map, AirStrike* air_strike) override;

    bool time_to_stop_exploding(float time);
};


#endif //AIR_STRIKE_EXPLODING_H_
