#include "idf.h"
#include "../game_object.h"

#include <cmath>

Idf::Idf(std::int16_t id_explosive_grenade,
         std::int16_t id_smoke_grenade) :
         explosive_grenade(id_explosive_grenade),
         smoke_grenade(id_smoke_grenade),
         bullets(CONFIGURATION.get_weaponIdf_mag_capacity()),
         mag_capacity(CONFIGURATION.get_weaponIdf_mag_capacity()),
         burst_capacity(CONFIGURATION.get_weaponIdf_burst_capacity()),
         close_range_damage(CONFIGURATION.get_weaponIdf_close_range_damage()),
         long_range_damage(CONFIGURATION.get_weaponIdf_long_range_damage()),
         distance_to_reduce_damage(CONFIGURATION.get_weaponIdf_matrix_range_to_reduce_damage()),
         rate_of_fire(CONFIGURATION.get_weaponIdf_rate_of_fire()),
         last_time_shot(CONFIGURATION.get_weaponIdf_rate_of_fire() * -1) {}

void Idf::update(float time) {
    explosive_grenade.update(time);
    smoke_grenade.update(time);
}

void Idf::shoot(std::vector<GameObject*>& shooting_objects, std::uint16_t x_sold_pos, float time) {
    last_time_shot = time;
    bullets -= burst_capacity;
    total_bullets_shot++;
    if (shooting_objects.empty()) return;
    std::int16_t x_matrix_enemy_pos = shooting_objects[0]->get_x_matrix_pos();
    if (bullets > 0) {
        if (abs(x_sold_pos - x_matrix_enemy_pos) >= distance_to_reduce_damage) {
            shooting_objects[0]->receive_damage(long_range_damage, time);
        } else {
            shooting_objects[0]->receive_damage(close_range_damage, time);
        }
    }
}

State* Idf::throw_explosive_grenade(GameMap& map,
                                  std::int16_t x_matrix_explosion,
                                  std::int16_t y_matrix_sold,
                                  State* current_state,
                                  float time) {
    return explosive_grenade.throw_grenade(map, x_matrix_explosion, y_matrix_sold, current_state, time);
}

State* Idf::throw_smoke_grenade(GameMap& map,
                                  std::int16_t x_matrix_explosion,
                                  std::int16_t y_matrix_sold,
                                  State* current_state,
                                  float time) {
    return smoke_grenade.throw_grenade(map, x_matrix_explosion, y_matrix_sold, current_state, time);
}


State *
Idf::call_air_strike(GameMap &map,
                     std::int16_t x_soldier,
                     std::int16_t y_soldier,
                     State *current_state,
                     float time) {
    return nullptr;
}

ExplosiveGrenade* Idf::get_explosive_grenade() {
    return &explosive_grenade;
}

SmokeGrenade* Idf::get_smoke_grenade() {
    return &smoke_grenade;
}

AirStrike* Idf::get_air_strike() {
    return nullptr;
}

void Idf::reload() {
    bullets = mag_capacity;
}

bool Idf::isFullyLoaded() {
    return bullets == mag_capacity;
}

bool Idf::empty() {
    return bullets <= 0;
}

std::int16_t Idf::get_bullets() {
    return bullets;
}

std::int32_t Idf::get_total_bullets_shot() {
    return total_bullets_shot * burst_capacity;
}

std::int16_t Idf::get_time_to_throw_explosive_grenade() {
    return explosive_grenade.get_time_to_throw_grenade();
}

std::int16_t Idf::get_time_to_throw_smoke_grenade() {
    return smoke_grenade.get_time_to_throw_grenade();
}

std::int16_t Idf::get_time_to_call_air_strike() {
    return -1;
}

float Idf::get_time_to_shoot() {
    return rate_of_fire;
}

bool Idf::time_to_shoot(float time) {
    return (time - last_time_shot) > rate_of_fire;
}

SoldierType Idf::get_type() {
    return IDF;
}