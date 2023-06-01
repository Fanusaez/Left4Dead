#ifndef WALKER_H_
#define WALKER_H_

#include <complex>
#include <cstdint>
#include "map.h"
#include "zombie.h"
#include "zombie_states/zombie_idle.h"

#define MOVEMENTS_PER_CELL 15

class Walker : public GameObject, public Zombie {
 private:
    std::int16_t health = 100;
    std::int16_t damage_attack = 20;
    std::int16_t x_pos;
    std::int16_t y_pos;
    bool dead = false;
    std::int16_t direction = -1;
    ZombieState* state = new ZombieIdle;
    const std::int16_t id;
    GameMap& map;

GameObject* get_closest_soldier(std::vector<GameObject*> soldiers);
std::int16_t get_distance_to_soldier(GameObject* soldier);
 public:
Walker(std::int16_t x_pos, std::int16_t y_pos, GameMap& map);
Walker(std::int16_t x_pos, std::int16_t y_pos, std::int16_t id, GameMap& map);

void receive_damage(std::uint16_t damage, float time) override;

bool in_range_of_explosion(std::int16_t x_start,
                           std::int16_t x_finish,
                           std::int16_t y_start,
                           std::int16_t y_finish) override;

void chase_closest_soldier(std::vector<GameObject*> soldiers, float time) override;
void set_direction(std::int16_t direction) override;
void get_position(std::vector<float>& pos) override;
void attack(std::vector<GameObject*> soldiers, float time) override;

bool in_range_of_attack(GameObject* object);

void die(float time);

std::int16_t get_id() override;
~Walker();

// ************************* Metodos de testeo ************************************************8//
std::int16_t get_health();
float get_x();
float get_y();
ZombieState* get_state() override;
};

#endif  // WALKER_H_
