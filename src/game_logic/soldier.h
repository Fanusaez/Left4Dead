#ifndef SOLDIER_H_
#define SOLDIER_H_

#include <cstdint>
#include "game_object.h"
#include "weapons/weapon.h"
#include "states/idle.h"

class Soldier : public GameObject {
 private:
    Weapon* weapon = nullptr;
    State* state = new Idle;
    GameMap &map;
    std::int16_t x_pos;
    std::int16_t y_pos;
    std::int16_t direction = RIGHT;
    bool _dead = false;
    std::int16_t health = 100;
    const std::int16_t id;

void die(float time);
void change_state(State* new_state);
void adjust_position_grenade(std::int16_t& x_grenade_pos);

 public:
Soldier(Weapon* weapon, GameMap& map, std::int16_t x_pos, std::int16_t y_pos, std::int16_t id);

void update(float time);
void reload(float time);
void shoot(float time);
void throw_explosive_grenade(float time);
void throw_smoke_grenade(float time);
void call_air_strike(float time);
void move_up(float time);
void move_down(float time);
void move_right(float time);
void move_left(float time);

void move_up();
void move_down();
void move_right();
void move_left();

void receive_damage(std::uint16_t damage, float time) override;
void get_stunned(float time) override;

bool in_range_of_explosion(std::int16_t x_start,
                           std::int16_t x_finish,
                           std::int16_t y_start,
                           std::int16_t y_finish) override;


std::int16_t get_id() override;
std::vector<GameObject*> get_targets();

void stop_action();

Weapon* get_weapon();

std::int16_t get_y_pos() override;
std::int16_t get_x_pos() override;
std::int16_t get_y_matrix_pos() override;
std::int16_t get_x_matrix_pos() override;

bool facing_left();
bool chaseable();
bool dead();
~Soldier();

//******************************* Metodos de testeo ***************************************************
void set_direction(std::int16_t direction) override;
std::int16_t get_direction();
std::int16_t get_health();
State* get_state();

};
#endif  // SOLDIER_H_
