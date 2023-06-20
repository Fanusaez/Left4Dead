#include "thrown_grenade.h"
#include "exploding.h"
#include "../../configuration.h"

ThrownGrenade::ThrownGrenade(float time,
                             std::int16_t x_explosion,
                             std::int16_t y_explosion,
                             GameMap& map,
                             Grenade* grenade) :
                             map(map),
                             grenade(grenade),
                             x_explosion(x_explosion),
                             y_explosion(y_explosion),
                             start_time(time),
                             _time_to_explode(CONFIGURATION.get_grenadeState_time_thrown_grenade()){}

GrenadeState *ThrownGrenade::update(float time) {
    if (time_to_explode(time)) {
        return new Exploding(time, x_explosion, y_explosion, map, grenade);
    }
    return nullptr;
}

GrenadeState *ThrownGrenade::throw_grenade(float time,
                                           std::int16_t x_explosion,
                                           std::int16_t y_explosion,
                                           GameMap& map,
                                           Grenade* grenade) {
    return nullptr;
}

GrenadeState *ThrownGrenade::explode(float time,
                                     std::int16_t x_explosion,
                                     std::int16_t y_explosion,
                                     GameMap& map,
                                     Grenade* grenade) {
    if (time_to_explode(time)) {
        return new Exploding(time, x_explosion, y_explosion, map, grenade);
    }
    return nullptr;
}

bool ThrownGrenade::time_to_explode(float time) {
    return (time - start_time) >= _time_to_explode;
}

std::int16_t ThrownGrenade::get_x_explosion() {
    return x_explosion;
}

std::int16_t ThrownGrenade::get_y_explosion() {
    return y_explosion;
}