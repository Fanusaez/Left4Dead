#include "walker.h"

Walker::Walker(std::uint16_t x_pos, std::uint16_t y_pos) :
                x_pos(x_pos),
                y_pos(y_pos) {}

void Walker::get_shot(Weapon* weapon) {
    health -= weapon->shoot(y_pos);
    if (health <= 0) {
        dead = true;
    }
}

// ************************* Metodos de testeo ************************************************8//

std::uint16_t Walker::get_health() {
    return health;
}