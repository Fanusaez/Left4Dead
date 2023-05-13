#include "walker.h"


void Walker::get_shot(std::uint16_t damage) {
    health -= damage;
    if (!health) {
        dead = true;
    }
}