#ifndef  IDF_H_
#define  IDF_H_

#include <cstdint>
#include "weapon.h"

class Idf : public Weapon {
 private:
    std::uint16_t bullets = 50;
    std::uint16_t close_range_damage = 30;
    std::uint16_t long_range_damage = 15;
    std::int16_t grenade_damage = 40;

 public:

void shoot(std::vector<GameObject*>& shooting_objects,
           std::uint16_t y_pos_sold) override;

void throw_explosive_grenade(std::vector<GameObject*>& shooting_objects) override;

void reload();
};
#endif // IDF_H_
