#include "scout.h"


void Scout::shoot(std::vector<GameObject *> &shooting_objects, std::uint16_t y_pos_sold) {
    if (bullets <= 0) return;
    std::uint16_t variant_damage = damage;
    for (const auto& shooting_object : shooting_objects) {
        shooting_object->get_shot(variant_damage);
        variant_damage -= damage_reduction_hit;
        if (!variant_damage) return;
    }
    bullets--;
}

void Scout::reload() {
    bullets = 20;
}