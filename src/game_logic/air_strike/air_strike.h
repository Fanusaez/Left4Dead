#ifndef AIR_STRIKE_H
#define AIR_STRIKE_H

#include <cstdint>
#include <vector>

#include "air_strike_states/air_strike_idle.h"

class State;
class GameMap;

class AirStrike {
private:
    AirStrikeState* air_strike_state = new AirStrikeIdle;
    std::int16_t range_of_safe_space = 2;
    const std::int16_t damage_air_strike = 30;
    const float _time_to_call_air_strike = 120;
    float last_called_air_strike = - 120;

public:
    void update(float time);

    State* call_air_strike(GameMap& map,
                         std::int16_t x_matrix_soldier,
                         std::int16_t y_matrix_soldier,
                         State* current_state,
                         float time);

    void explode(float time, std::int16_t x_matrix_soldier, std::int16_t y_matrix_soldier, GameMap& map);

    bool time_to_call_air_strike(float time);

    //AirAttackState* get_state();
};


#endif //AIR_STRIKE_H
