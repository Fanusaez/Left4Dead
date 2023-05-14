#include "idf.h"
#include <cmath>
#define DISTANCE_LONG_RANGE 5

void Idf::shoot(std::vector<GameObject*>& shooting_objects, std::uint16_t y_sold_pos) {
    if (shooting_objects.empty()) return;
    if (bullets > 0) {
        if (abs(y_sold_pos - shooting_objects[0]->get_y_position()) >= DISTANCE_LONG_RANGE) {
            shooting_objects[0]->get_shot(long_range_damage);
        } else {
            shooting_objects[0]->get_shot(close_range_damage);
        }
        bullets--;
    }
}

void Idf::reload() {
    bullets = 50;
}
