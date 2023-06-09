#include "idf.h"
#include "../game_object.h"

#include <cmath>

#define DISTANCE_LONG_RANGE 5

void Idf::update(float time) {
    explosive_grenade.update(time);
    smoke_grenade.update(time);
}

void Idf::shoot(std::vector<GameObject*>& shooting_objects, std::uint16_t x_sold_pos, float time) {
    bullets--;
    if (shooting_objects.empty()) return;
    std::int16_t x_matrix_enemy_pos = shooting_objects[0]->get_x_matrix_pos();
    if (bullets > 0) {
        if (abs(x_sold_pos - x_matrix_enemy_pos) >= DISTANCE_LONG_RANGE) {
            shooting_objects[0]->receive_damage(long_range_damage, time);
        } else {
            shooting_objects[0]->receive_damage(close_range_damage, time);
        }
    }
}

State* Idf::throw_explosive_grenade(GameMap& map,
                                  std::int16_t x_matrix_explosion,
                                  std::int16_t y_matrix_sold,
                                  State* current_state,
                                  float time) {
    return explosive_grenade.throw_grenade(map, x_matrix_explosion, y_matrix_sold, current_state, time);
}

State* Idf::throw_smoke_grenade(GameMap& map,
                                  std::int16_t x_matrix_explosion,
                                  std::int16_t y_matrix_sold,
                                  State* current_state,
                                  float time) {
    return smoke_grenade.throw_grenade(map, x_matrix_explosion, y_matrix_sold, current_state, time);
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
