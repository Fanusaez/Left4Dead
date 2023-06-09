#ifndef SCOUT_H_
#define SCOUT_H_

#include "weapon.h"
#include "../grenades/explosive_grenade.h"
#include "../grenades/smoke_grenade.h"

class Scout : public Weapon {
 private:
    std::uint16_t bullets = 20;
    const std::uint16_t mag_capacity = 20;
    const std::uint16_t damage = 40;
    const std::uint16_t damage_reduction_hit = 10;
    ExplosiveGrenade explosive_grenade;
    SmokeGrenade smoke_grenade;

 public:

void update(float time) override;

void shoot(std::vector<GameObject*>& shooting_objects,
           std::uint16_t x_pos_sold, float time) override;

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

void reload() override;
bool isFullyLoaded() override;
bool empty() override;
std::int16_t get_bullets() override;
};

#endif  // SCOUT_H_
