#include "idf.h"

void Idf::shoot(Walker &walker) {
    if (bullets){
        walker.get_shot(close_range_damage);
    }
}
void Idf::reload() {
    bullets = 50;
}
