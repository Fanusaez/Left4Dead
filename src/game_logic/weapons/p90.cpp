#include "p90.h"
#include "../game_object.h"
#include "../configuration.h"

#define FIRST_ENEMY 0

P90::P90(std::int16_t id_air_strike) :
air_strike(id_air_strike),
bullets(CONFIGURATION.get_weaponP90_mag_capacity()),
mag_capacity(CONFIGURATION.get_weaponP90_mag_capacity()),
damage(CONFIGURATION.get_weaponP90_damage()) {}

void P90::update(float time) {
    air_strike.update(time);
}

void P90::shoot(std::vector<GameObject*>& shooting_objects, std::uint16_t x_sold_pos, float time) {
    if (shooting_objects.empty()) return;
    if (bullets > 0) {
        shooting_objects[FIRST_ENEMY]->receive_damage(damage, time);
        bullets--;
    }
}

State* P90::throw_explosive_grenade(GameMap& map,
                                  std::int16_t x_matrix_sold,
                                  std::int16_t y_matrix_explosion,
                                  State* current_state,
                                  float time) {
    return nullptr;
}

State* P90::throw_smoke_grenade(GameMap& map,
                                  std::int16_t x_matrix_sold,
                                  std::int16_t y_matrix_explosion,
                                  State* current_state,
                                  float time) {
    return nullptr;
}

State *
P90::call_air_strike(GameMap &map,
                     std::int16_t x_soldier,
                     std::int16_t y_soldier,
                     State *current_state,
                     float time) {
    return air_strike.call_air_strike(map, x_soldier, y_soldier, current_state, time);
}

ExplosiveGrenade* P90::get_explosive_grenade() {
    return nullptr;
}

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
