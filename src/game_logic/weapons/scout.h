#ifndef SCOUT_H_
#define SCOUT_H_


#include <cstdint>
#include "weapon.h"

class Scout : public Weapon {
 private:
    std::uint16_t bullets = 20;
    std::uint16_t damage = 40;
    std::uint16_t damage_reduction_hit = 10;
    std::int16_t grenade_damage = 40;
    float time_to_throw_grenade = 30;
    float last_thrown_grenade = 0;

 public:
void shoot(std::vector<GameObject*>& shooting_objects,
           std::uint16_t y_pos_sold, float time) override;

void throw_explosive_grenade(GameMap& map,
                             std::int16_t x_matrix_sold,
                             std::int16_t y_matrix_explosion,
                             State* current_state,
                             float time) override;

void reload() override;
bool isFullyLoaded() override;
bool empty() override;
std::int16_t get_bullets() override;
bool time_throw_grenade(float time);
};

#endif  // SCOUT_H_
