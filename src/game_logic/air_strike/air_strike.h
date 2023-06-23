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
    std::int16_t range_of_safe_space;
    const std::int16_t damage_air_strike;
    const float _time_to_call_air_strike;
    std::int16_t movements_per_cell;
    float last_called_air_strike = - 120;
    std::int16_t left_time_to_call = 0;
    std::vector<std::vector<std::int16_t>> matrix_positions_of_explosion;

public:
    std::int16_t id;

    explicit AirStrike(std::int16_t id);

    void update(float time);

    State* call_air_strike(GameMap& map,
                         std::int16_t x_matrix_soldier,
                         std::int16_t y_matrix_soldier,
                         State* current_state,
                         float time);

    void explode(float time, std::int16_t x_matrix_soldier, std::int16_t y_matrix_soldier, GameMap& map);

    bool time_to_call_air_strike(float time);

    AirStrikeState* get_state();

    std::vector<std::vector<int16_t>> get_positions_for_explosion();

    void update_left_time_to_call(float time);
    std::int16_t get_time_to_call_air_strike();
    bool exploding();
    ~AirStrike();


};


#endif //AIR_STRIKE_H
