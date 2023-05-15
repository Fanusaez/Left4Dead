#include "walker.h"

Walker::Walker(std::uint16_t x_pos, std::uint16_t y_pos) :
                x_pos(x_pos),
                y_pos(y_pos) {}

void Walker::get_shot(std::uint16_t damage) {
    health -= damage;
    if (health <= 0) {
        dead = true;
    }
}

void Walker::move_up() {

}

std::uint16_t Walker::get_y_position() {
    return y_pos;
}

// ************************* Metodos de testeo ************************************************8//

std::uint16_t Walker::get_health() {
    return health;
}