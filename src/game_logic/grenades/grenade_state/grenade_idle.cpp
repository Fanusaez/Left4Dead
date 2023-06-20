#include "grenade_idle.h"
#include "thrown_grenade.h"

GrenadeState *GrenadeIdle::update(float time) {
    return nullptr;
}

GrenadeState *GrenadeIdle::throw_grenade(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade) {
    return new ThrownGrenade(time, x_explosion, y_explosion, map, grenade);
}

GrenadeState *GrenadeIdle::explode(float time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade) {
    return nullptr;
}

std::int16_t GrenadeIdle::get_x_explosion() {
    return 0;
}

std::int16_t GrenadeIdle::get_y_explosion() {
    return 0;
}

bool GrenadeIdle::exploting() {
    return false;
}