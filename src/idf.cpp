#include "idf.h"

void Idf::shoot(std::vector<GameObject*>& shooting_objects) {
    if (shooting_objects.empty()) return;
    if (bullets > 0){
        shooting_objects[0]->get_shot(close_range_damage);
    }
}

void Idf::reload() {
    bullets = 50;
}
