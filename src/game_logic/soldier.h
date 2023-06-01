#ifndef SOLDIER_H_
#define SOLDIER_H_

#include <cstdint>
#include "game_object.h"
#include "map.h"
#include "weapons/weapon.h"
#include "states/idle.h"

#define MOVEMENTS_PER_CELL 15
#define DOWN 1
#define UP -1

class Soldier : public GameObject {
 private:
    Weapon* weapon = nullptr;
    State* state = new Idle;
    GameMap &map;
    std::int16_t x_pos;
    std::int16_t y_pos;
    std::int16_t direction = UP;
    bool dead = false;
    std::int16_t health = 100;
    const std::int16_t id;

void die(float time);

 public:
    bool facingLeft = false;

Soldier(Weapon* weapon, GameMap& map); // lo dejo por ahora
Soldier(Weapon* weapon, GameMap& map, std::int16_t x_pos, std::int16_t y_pos);
Soldier(Weapon* weapon, GameMap& map, std::int16_t x_pos, std::int16_t y_pos, std::int16_t id);

void update(float time);
void reload(float time);
void shoot(float time);
void throw_explosive_grenade();

void move_up(float time);
void move_down(float time);
void move_right(float time);
void move_left(float time);

void move_up();
void move_down();
void move_right();
void move_left();

void receive_damage(std::uint16_t damage, float time) override;

bool in_range_of_explosion(std::int16_t x_start,
                           std::int16_t x_finish,
                           std::int16_t y_start,
                           std::int16_t y_finish) override;


std::int16_t get_id() override;
std::vector<GameObject*> get_targets();

void set_idle();

std::int16_t get_y_pos() override;
std::int16_t get_x_pos() override;
std::int16_t get_y_matrix_pos() override;
std::int16_t get_x_matrix_pos() override;

~Soldier();

//******************************* Metodos de testeo ***************************************************
void set_direction(std::int16_t direction) override;
std::int16_t get_direction();
std::int16_t get_health();
State* get_state();

};
#endif  // SOLDIER_H_
