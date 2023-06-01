#include "scout.h"
#define MAG_CAPACITY 20

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
                                  State* current_state,
                                  float time) {
    if (!time_throw_grenade(time)) return;
    last_thrown_grenade = time;

    std::vector<GameObject*> objects;
    map.throw_grenade(objects, x_matrix_sold, y_matrix_explosion);
    //State* new_state = current_state->throw_exposive_granade(time);
    //if (new_state != nullptr) {
    // delete current_state;
    // current_state = new_state;
    //   }
    for (const auto& explosive_object : objects) {
        explosive_object->receive_damage(grenade_damage, time);
    }
}

bool Scout::time_throw_grenade(float time) {
    return (time - last_thrown_grenade) >= time_to_throw_grenade;
}

void Scout::reload() {
    bullets = MAG_CAPACITY;
}

bool Scout::isFullyLoaded() {
    return bullets == MAG_CAPACITY;
}

bool Scout::empty() {
    return bullets == 0;
}

std::int16_t Scout::get_bullets() {
    return bullets;
}