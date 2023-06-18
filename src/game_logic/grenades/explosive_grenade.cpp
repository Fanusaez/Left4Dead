#include "explosive_grenade.h"
#include "../map.h"
#include "../game_object.h"


ExplosiveGrenade::ExplosiveGrenade(std::int16_t id) :
    id(id),
    grenade_damage(CONFIGURATION.get_explosiveGrenade_damage()),
    time_to_throw_grenade(CONFIGURATION.get_explosiveGrenade_time_to_reThrow()),
    radius_range(CONFIGURATION.get_explosiveGrenade_radius_range()) {}

void ExplosiveGrenade::update(float time) {
    GrenadeState* state = grenade_state -> update(time);
    if (state) {
        delete grenade_state;
        grenade_state = state;
    }
}

State* ExplosiveGrenade::throw_grenade(GameMap& map,
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

    return current_soldier_state->throw_explosive_grenade(time);
}

void ExplosiveGrenade::explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map) {
    std::vector<GameObject*> objects;
    map.get_objects_in_explosion(objects, x_explosion, y_explosion, radius_range);
    for (const auto& explosive_object : objects) {
        explosive_object->receive_damage(grenade_damage, time);
    }
}

bool ExplosiveGrenade::time_throw_grenade(float time) {
    return (time - last_thrown_grenade) >= time_to_throw_grenade;
}

ExplosiveGrenade::~ExplosiveGrenade() {
    delete grenade_state;
}

GrenadeState *ExplosiveGrenade::get_state() {
    return grenade_state;
}