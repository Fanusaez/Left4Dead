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
 public:
void shoot(std::vector<GameObject*>& shooting_objects,
           std::uint16_t y_pos_sold) override;

void throw_explosive_grenade(std::vector<GameObject*>& shooting_objects) override;

void reload() override;
bool isFullyLoaded() override;
bool empty() override;
std::int16_t get_bullets() override;

};

#endif  // SCOUT_H_
