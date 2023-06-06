#include "idf.h"
#include <cmath>
#include <iostream>

#define DISTANCE_LONG_RANGE 5
#define X_POS 0
#define Y_POS 1

void Idf::shoot(std::vector<GameObject*>& shooting_objects, std::uint16_t y_sold_pos, float time) {
    bullets--;
    if (shooting_objects.empty()) return;
    std::int16_t y_matrix_enemy_pos = shooting_objects[0]->get_y_matrix_pos();
    if (bullets > 0) {
        if (abs(y_sold_pos - y_matrix_enemy_pos) >= DISTANCE_LONG_RANGE) {
            shooting_objects[0]->receive_damage(long_range_damage, time);
        } else {
            shooting_objects[0]->receive_damage(close_range_damage, time);
        }
    }
}

void Idf::throw_explosive_grenade(GameMap& map,
                                  std::int16_t x_matrix_sold,
                                  std::int16_t y_matrix_explosion,
                                  State*& current_state,
                                  float time) {
    explosive_grenade.throw_grenade(map, x_matrix_sold, y_matrix_explosion, current_state, time);
}

void Idf::throw_smoke_grenade(GameMap& map,
                                  std::int16_t x_matrix_sold,
                                  std::int16_t y_matrix_explosion,
                                  State*& current_state,
                                  float time) {
    smoke_grenade.throw_grenade(map, x_matrix_sold, y_matrix_explosion, current_state, time);
}

void Idf::reload() {
    bullets = mag_capacity;
}

bool Idf::isFullyLoaded() {
    return bullets == mag_capacity;
}

bool Idf::empty() {
    return bullets <= 0;
}

std::int16_t Idf::get_bullets() {
    return bullets;
}
