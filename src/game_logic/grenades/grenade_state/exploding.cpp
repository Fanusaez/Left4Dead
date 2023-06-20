#include "exploding.h"
#include "grenade_idle.h"
#include "../grenade.h"
#include "../../configuration.h"

Exploding::Exploding(float start_time,
                     std::int16_t x_explosion,
                     std::int16_t y_explosion,
                     GameMap &map,
                     Grenade* grenade) :    start_time(start_time),
                                            x_matrix_explosion(x_explosion),
                                            y_matrix_explosion(y_explosion),
                                            time_to_stop_exploding(CONFIGURATION.get_grenadeState_time_exploding()),
                                            movements_per_cell(CONFIGURATION.get_movements_per_cell()) {
    explode(start_time, x_explosion, y_explosion, map, grenade);
}

GrenadeState *Exploding::update(float time) {
    if (time_stop_explosion(time)) {
        return new GrenadeIdle();
    }
    return nullptr;
}

GrenadeState *Exploding::throw_grenade(float time,
                                       std::int16_t x_explosion,
                                       std::int16_t y_explosion,
                                       GameMap& map,
                                       Grenade* greande) {
    return nullptr;
}

GrenadeState* Exploding::explode(float time,
                                 std::int16_t x_explosion,
                                 std::int16_t y_explosion,
                                 GameMap& map,
                                 Grenade* grenade) {
    grenade->explode(time, x_explosion, y_explosion, map);
    return nullptr;
}


bool Exploding::time_stop_explosion(float time) {
    return (time - start_time) >= time_to_stop_exploding;
}

std::int16_t Exploding::get_x_explosion() {
    return x_matrix_explosion * movements_per_cell;
}

std::int16_t Exploding::get_y_explosion() {
    return y_matrix_explosion * movements_per_cell;
}

bool Exploding::exploting() {
    return true;
}