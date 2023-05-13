#ifndef SOLDIER_H_
#define SOLDIER_H_

#include <cstdint>
#include "weapon.h"
#include "game_object.h"
#include "idf.h"

class Soldier : public GameObject{
 private:
    std::uint16_t health = 100;
    //Weapon* weapon = nullptr; posponemos polimorfismo
    Idf& idf;

 public:
//Soldier(Weapon* weapon); prosponemos polimorfismo
Soldier(Idf& idf);
void get_shot(std::uint16_t damage) override;

};
#endif  // SOLDIER_H_
