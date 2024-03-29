#include "smoke_grenade.h"
#include "../map.h"
#include "../game_object.h"


SmokeGrenade::SmokeGrenade(std::int16_t id) :
    id(id),
    waiting_time_to_throw_grenade(CONFIGURATION.get_smokeGrenade_time_to_reThrow()),
    radius_range(CONFIGURATION.get_smokeGrenade_radius_range()),
    last_thrown_grenade(CONFIGURATION.get_smokeGrenade_time_to_reThrow() * -1) {}

void SmokeGrenade::update(float time) {
    GrenadeState* state = grenade_state -> update(time);
    if (state) {
        delete grenade_state;
        grenade_state = state;
    }
    update_left_time_to_throw(time);
}

State* SmokeGrenade::throw_grenade(GameMap& map,
                                     std::int16_t x_matrix_explosion,
                                     std::int16_t y_matrix_sold,
                                     State* current_soldier_state,
                                     float time) {
    if (!time_throw_grenade(time)) {
        return nullptr;
    }
    last_thrown_grenade = time;
    GrenadeState* new_grenade_state = grenade_state -> throw_grenade(time, x_matrix_explosion, y_matrix_sold, map, this);
    if (new_grenade_state) {
        delete grenade_state;
        grenade_state = new_grenade_state;
    }
    return current_soldier_state->throw_smoke_grenade(time);
}

void SmokeGrenade::explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap &map) {
    std::vector<GameObject*> objects;
    map.get_objects_in_explosion(objects, x_explosion, y_explosion, radius_range);
    for (const auto& explosive_object : objects) {
        explosive_object->get_stunned(time);
    }
}

bool SmokeGrenade::time_throw_grenade(float time) {
    return (time - last_thrown_grenade) >= waiting_time_to_throw_grenade;
}

GrenadeState *SmokeGrenade::get_state() {
    return grenade_state;
}

std::int16_t SmokeGrenade::get_time_to_throw_grenade() {
    return left_time_to_throw_grenade;
}

void SmokeGrenade::update_left_time_to_throw(float time) {
    std::int16_t time_since_last_thrown = time - last_thrown_grenade;
    if (time_since_last_thrown > waiting_time_to_throw_grenade) {
        left_time_to_throw_grenade = 0;
    } else {
        left_time_to_throw_grenade = waiting_time_to_throw_grenade - time_since_last_thrown;
    }
}

SmokeGrenade::~SmokeGrenade() {
    delete grenade_state;
}

