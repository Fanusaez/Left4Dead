#include "scout.h"

void Scout::shoot(std::vector<GameObject *> &shooting_objects, std::uint16_t y_pos_sold, float time) {
    if (bullets <= 0) return;
    std::uint16_t variant_damage = damage;
    for (const auto& shooting_object : shooting_objects) {
        shooting_object->receive_damage(variant_damage, time);
        variant_damage -= damage_reduction_hit;
        if (!variant_damage) return;
    }
    bullets--;
}

void Scout::throw_explosive_grenade(GameMap& map,
                                  std::int16_t x_matrix_sold,
                                  std::int16_t y_matrix_explosion,
                                  State*& current_state,
                                  float time) {
    explosive_grenade.throw_grenade(map, x_matrix_sold, y_matrix_explosion, current_state, time);
}

void Scout::throw_smoke_grenade(GameMap& map,
                                    std::int16_t x_matrix_sold,
                                    std::int16_t y_matrix_explosion,
                                    State*& current_state,
                                    float time) {
    smoke_grenade.throw_grenade(map, x_matrix_sold, y_matrix_explosion, current_state, time);
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