#include "air_strike.h"
#include "../game_object.h"
#include "../map.h"
#include "../states/state.h"

void AirStrike::update(float time) {
    AirStrikeState* state = air_strike_state -> update(time);
    if (state) {
        delete air_strike_state ;
        air_strike_state = state;
    }
}

State* AirStrike::call_air_strike(GameMap& map,
                                       std::int16_t x_matrix_soldier,
                                       std::int16_t y_matrix_soldier,
                                       State* current_soldier_state,
                                       float time) {
    if (!time_to_call_air_strike(time)) {
        return nullptr;
    }
    last_called_air_strike = time;
    AirStrikeState* new_state = air_strike_state  -> call_air_strike(time, x_matrix_soldier, y_matrix_soldier, map, this);
    if (new_state) {
        delete air_strike_state ;
        air_strike_state = new_state;
    }
    return current_soldier_state->call_air_strike(time);
}

void AirStrike::explode(float time, std::int16_t x_matrix_soldier, std::int16_t y_matrix_soldier, GameMap& map) {
    std::vector<GameObject*> objects;
    map.get_objects_in_air_strike(objects, x_matrix_soldier, y_matrix_soldier, range_of_safe_space);
    for (const auto& explosive_object : objects) {
        explosive_object->receive_damage(damage_air_strike, time);
    }
}

bool AirStrike::time_to_call_air_strike(float time) {
    return (time - last_called_air_strike) >= _time_to_call_air_strike;
}

AirStrikeState *AirStrike::get_state() {
    return air_strike_state;
}