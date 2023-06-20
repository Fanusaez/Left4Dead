#ifndef  IDF_H_
#define  IDF_H_

#include <cstdint>
#include "weapon.h"
#include "../grenades/explosive_grenade.h"
#include "../grenades/smoke_grenade.h"

class Idf : public Weapon {
 private:
    std::int16_t bullets;
    const std::int16_t mag_capacity;
    const std::int16_t close_range_damage;
    const std::int16_t long_range_damage;
    ExplosiveGrenade explosive_grenade;
    SmokeGrenade smoke_grenade;


 public:

Idf(std::int16_t id_explosive_grenade, std::int16_t id_smoke_grenade);

void update(float time) override;

void shoot(std::vector<GameObject*>& shooting_objects,
           std::uint16_t y_pos_sold, float time) override;

State* throw_explosive_grenade(GameMap& map,
                         std::int16_t x_matrix_explosion,
                         std::int16_t y_matrix_sold,
                         State* current_state,
                         float time) override;
State* throw_smoke_grenade(GameMap& map,
                         std::int16_t x_matrix_explosion,
                         std::int16_t y_matrix_sold,
                         State* current_state,
                         float time) override;

State* call_air_strike(GameMap& map,
                           std::int16_t x_matrix_explosion,
                           std::int16_t y_matrix_sold,
                           State* current_state,
                           float time) override;

ExplosiveGrenade* get_explosive_grenade() override;
void reload() override;
bool isFullyLoaded() override;
bool empty() override;
std::int16_t get_bullets() override;
};
#endif // IDF_H_
