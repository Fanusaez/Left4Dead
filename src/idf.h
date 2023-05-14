#ifndef  IDF_H_
#define  IDF_H_

#include <cstdint>
#include "weapon.h"

class Idf : public Weapon {
 private:
    std::uint16_t bullets = 50;
    std::uint16_t close_range_damage = 30;
    std::uint16_t long_range_damage = 15;
void reload();

 public:

std::uint16_t shoot(std::uint16_t zomb_y_pos) override;

};
#endif // IDF_H_
