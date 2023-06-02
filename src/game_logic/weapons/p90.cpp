#include "p90.h"

#define FIRST_ENEMY 0

void P90::shoot(std::vector<GameObject*>& shooting_objects, std::uint16_t y_sold_pos, float time) {
    if (shooting_objects.empty()) return;
    if (bullets > 0) {
        shooting_objects[FIRST_ENEMY]->receive_damage(damage, time);
        bullets--;
    }
}

void P90::throw_explosive_grenade(GameMap& map,
                                  std::int16_t x_matrix_sold,
                                  std::int16_t y_matrix_explosion,
                                  State*& current_state,
                                  float time) {}

void P90::reload() {
    bullets = mag_capacity;
}

bool P90::isFullyLoaded() {
    return bullets == mag_capacity;
}

bool P90::empty() {
    return bullets <= 0;
}

std::int16_t P90::get_bullets() {
    return bullets;
}
