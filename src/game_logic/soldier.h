#ifndef SOLDIER_H_
#define SOLDIER_H_

#include <cstdint>
#include "game_object.h"
#include "map.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/states/idle.h"

#define DOWN 1
#define UP -1

class Soldier : public GameObject {
 private:
    Weapon* weapon = nullptr;
    State* state = new Idle;
    GameMap &map;
    double x_pos;
    double y_pos;
    std::int16_t direction = UP;
    bool dead = false;
    std::int16_t health = 100;
    double soldier_speed = 0.2;

 public:
Soldier(Weapon* weapon, GameMap& map); // lo dejo por ahora
Soldier(Weapon* weapon, GameMap& map, std::uint16_t x_pos, std::uint16_t y_pos);
Soldier(Weapon* weapon, GameMap& map, std::uint16_t x_pos, std::uint16_t y_pos, float speed);

void shoot();
void throw_explosive_grenade();
void receive_damage(std::uint16_t damage) override;


bool in_range_of_explosion(std::int16_t x_start,
                           std::int16_t x_finish,
                           std::int16_t y_start,
                           std::int16_t y_finish) override;

void get_position(std::vector<float>& pos) override;

void move_up();
void move_down();
void move_right();
void move_left();

void reload(float time);
void shoot(float time);

~Soldier();

//******************************* Metodos de testeo ***************************************************
void set_direction(std::int16_t direction) override;
std::int16_t get_direction();
float get_y_position();
float get_x_position();
std::int16_t get_health();
State* get_state();

};
#endif  // SOLDIER_H_
