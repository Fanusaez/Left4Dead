#ifndef SCOUT_H_
#define SCOUT_H_


#include <cstdint>
#include "weapon.h"

class Scout : public Weapon {
 private:
    std::uint16_t bullets = 20;
    std::uint16_t damage = 40;
    std::uint16_t damage_reduction_hit = 10;
 public:
void shoot(std::vector<GameObject*>& shooting_objects,
           std::uint16_t y_pos_sold) override;
void reload();
};

#endif  // SCOUT_H_
