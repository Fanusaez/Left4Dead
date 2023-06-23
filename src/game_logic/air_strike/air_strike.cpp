#include "air_strike.h"
#include "../game_object.h"
#include "../map.h"
#include "../states/state.h"
#include "../configuration.h"

#define CONFIGURATION Configuration::getInstance()


AirStrike::AirStrike(std::int16_t id) :
    id(id),
    range_of_safe_space(CONFIGURATION.get_air_strike_radius_range_safe_space()),
    damage_air_strike(CONFIGURATION.get_air_strike_damage()),
    _time_to_call_air_strike(CONFIGURATION.get_air_strike_time_reCall()),
    movements_per_cell(CONFIGURATION.get_movements_per_cell()) {}

void AirStrike::update(float time) {
    AirStrikeState* state = air_strike_state -> update(time);
    if (state) {
        delete air_strike_state ;
        air_strike_state = state;
    }
    update_left_time_to_call(time);
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
    AirStrikeState* new_state = air_strike_state -> call_air_strike(time, x_matrix_soldier, y_matrix_soldier, map, this);
    if (new_state) {
        delete air_strike_state ;
        air_strike_state = new_state;
    }
    matrix_positions_of_explosion.clear(); // despues de terminar, limpio el vector de pos para la proxima llamada
    map.get_positions_of_explosion_air_strike(matrix_positions_of_explosion, x_matrix_soldier, y_matrix_soldier,range_of_safe_space);
    for (auto& vector_pos : matrix_positions_of_explosion) {
        for (auto& pos : vector_pos) {
            pos *= movements_per_cell;
        }
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

std::vector<std::vector<int16_t>> AirStrike::get_positions_for_explosion() {
    return matrix_positions_of_explosion;
}

void AirStrike::update_left_time_to_call(float time) {
    std::int16_t time_since_last_called = time - last_called_air_strike;
    if (time_since_last_called > _time_to_call_air_strike) {
        left_time_to_call = 0;
    } else {
        left_time_to_call = _time_to_call_air_strike - time_since_last_called;
    }
}

std::int16_t AirStrike::get_time_to_call_air_strike() {
    return left_time_to_call;
}

bool AirStrike::exploding() {
    return air_strike_state -> exploding();
}

AirStrike::~AirStrike() {
    delete air_strike_state;
}

AirStrikeState *AirStrike::get_state() {
    return air_strike_state;
}