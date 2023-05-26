#include "idf.h"
#include <cmath>
#define DISTANCE_LONG_RANGE 5
#define MAG_CAPACITY 50
#define X_POS 0
#define Y_POS 1

void Idf::shoot(std::vector<GameObject*>& shooting_objects, std::uint16_t y_sold_pos) {
    if (shooting_objects.empty()) return;
    std::vector<float> enemy_pos;
    shooting_objects[0]->get_position(enemy_pos);
    if (bullets > 0) {
        if (abs(y_sold_pos - enemy_pos[Y_POS]) >= DISTANCE_LONG_RANGE) {
            shooting_objects[0]->receive_damage(long_range_damage);
        } else {
            shooting_objects[0]->receive_damage(close_range_damage);
        }
        bullets--;
    }
}

void Idf::throw_explosive_grenade(std::vector<GameObject*> &explosive_objects) {
    for (const auto& explosive_object : explosive_objects) {
        explosive_object->receive_damage(grenade_damage);
    }
}

void Idf::reload() {
    bullets = 50;
}

bool Idf::isFullyLoaded() {
    return bullets == MAG_CAPACITY;
}

bool Idf::empty() {
    return bullets <= 0;
}

std::int16_t Idf::get_bullets() {
    return bullets;
}