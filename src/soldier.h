#ifndef SOLDIER_H_
#define SOLDIER_H_

#include <cstdint>
#include "weapon.h"
#include "game_object.h"
#include "idf.h"

class Soldier : public GameObject{
 private:
    std::uint16_t health = 100;
    Weapon* weapon = nullptr;
    std::uint16_t x_pos;
    std::uint16_t y_pos;
 public:
Soldier(Weapon* weapon);
void get_shot(std::uint16_t damage) override;
~Soldier();
};
#endif  // SOLDIER_H_
