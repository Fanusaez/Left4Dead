#include "scout.h"
#define MAG_CAPACITY 20

void Scout::shoot(std::vector<GameObject *> &shooting_objects, std::uint16_t y_pos_sold) {
    if (bullets <= 0) return;
    std::uint16_t variant_damage = damage;
    for (const auto& shooting_object : shooting_objects) {
        shooting_object->receive_damage(variant_damage);
        variant_damage -= damage_reduction_hit;
        if (!variant_damage) return;
    }
    bullets--;
}

void Scout::throw_explosive_grenade(std::vector<GameObject*> &explosive_objects) {
    for (const auto& explosive_object : explosive_objects) {
        explosive_object->receive_damage(grenade_damage);
    }
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