#include "walker.h"

Walker::Walker(std::uint16_t x_pos, std::uint16_t y_pos) :
                x_pos(x_pos),
                y_pos(y_pos) {}

void Walker::receive_damage(std::uint16_t damage) {
    health -= damage;
    if (health <= 0) {
        dead = true;
    }
}

void Walker::move_up() {

}

bool Walker::in_range_of_explosion(std::int16_t x_start,
                                   std::int16_t x_finish,
                                   std::int16_t y_start,
                                   std::int16_t y_finish) {
    return (x_start <= x_pos && x_pos <= x_finish && y_start <= y_pos && y_pos <= y_finish);
}

std::uint16_t Walker::get_y_position() {
    return y_pos;
}

// ************************* Metodos de testeo ************************************************8//

std::int16_t Walker::get_health() {
    return health;
}