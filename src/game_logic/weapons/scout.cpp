#include "scout.h"
#include "../game_object.h"

Scout::Scout(std::int16_t id_explosive_grenade,
            std::int16_t id_smoke_grenade) :
            explosive_grenade(id_explosive_grenade),
            smoke_grenade(id_smoke_grenade),
            bullets(CONFIGURATION.get_weaponScout_mag_capacity()),
            mag_capacity(CONFIGURATION.get_weaponScout_mag_capacity()),
            damage(CONFIGURATION.get_weaponScout_damage()),
            damage_reduction_hit(CONFIGURATION.get_weaponScout_reduction_per_hit()) {}

void Scout::update(float time) {
    explosive_grenade.update(time);
    smoke_grenade.update(time);
}

void Scout::shoot(std::vector<GameObject *> &shooting_objects, std::uint16_t x_pos_sold, float time) {
    if (bullets <= 0) return;
    std::uint16_t variant_damage = damage;
    for (const auto& shooting_object : shooting_objects) {
        shooting_object->receive_damage(variant_damage, time);
        variant_damage -= damage_reduction_hit;
        if (!variant_damage) return;
    }
    bullets--;
}

State* Scout::throw_explosive_grenade(GameMap& map,
                                  std::int16_t x_matrix_explosion,
                                  std::int16_t y_matrix_sold,
                                  State* current_state,
                                  float time) {
    return explosive_grenade.throw_grenade(map, x_matrix_explosion, y_matrix_sold, current_state, time);
}

State* Scout::throw_smoke_grenade(GameMap& map,
                                std::int16_t x_matrix_explosion,
                                std::int16_t y_matrix_sold,
                                State* current_state,
                                float time) {
    return smoke_grenade.throw_grenade(map, x_matrix_explosion, y_matrix_sold, current_state, time);
}


State *
Scout::call_air_strike(GameMap &map,
                       std::int16_t x_soldier,
                       std::int16_t y_soldier,
                       State *current_state,
                       float time) {
    return nullptr;
}

ExplosiveGrenade* Scout::get_explosive_grenade() {
    return &explosive_grenade;
}

void Scout::reload() {
    bullets = mag_capacity;
}

bool Scout::isFullyLoaded() {
    return bullets == mag_capacity;
}

bool Scout::empty() {
    return bullets == 0;
}

std::int16_t Scout::get_bullets() {
    return bullets;
}