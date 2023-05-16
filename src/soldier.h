#ifndef SOLDIER_H_
#define SOLDIER_H_

#include <cstdint>
#include "game_object.h"
#include "map.h"
#include "weapon.h"
#define DOWN 1
#define UP -1

class Soldier : public GameObject {
 private:
    Weapon* weapon = nullptr;
    GameMap &map;
    std::uint16_t x_pos = 0;
    std::uint16_t y_pos = 0;
    std::int16_t direction = UP;
    bool dead = false;
    std::uint16_t health = 100;

 public:
Soldier(Weapon* weapon, GameMap& map); // lo dejo por ahora
Soldier(Weapon* weapon, GameMap& map, std::uint16_t x_pos, std::uint16_t y_pos);

void shoot();
void set_direction(std::int16_t direction);
void get_shot(std::uint16_t damage) override;
std::uint16_t get_y_position() override;
std::uint16_t get_x_position();
void move_up() override;
void move_down();
void move_right();
~Soldier();

};
#endif  // SOLDIER_H_
