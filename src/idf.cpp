#include "idf.h"

std::uint16_t Idf::shoot(std::uint16_t zomb_y_pos) {
    if (bullets > 0){
        return close_range_damage;
    }
    return 0;
}

void Idf::reload() {
    bullets = 50;
}
