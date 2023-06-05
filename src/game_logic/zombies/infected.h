#ifndef WALKER_H_
#define WALKER_H_

#include <complex>
#include <cstdint>
#include "../map.h"
#include "zombie.h"
#include "../zombie_states/zombie_idle.h"
#include "../chaser.h"
#include "../zombie_states/chasing_states/chase_walking.h"
#include "../zombie_states/chasing_states/chase_running.h"
#define MOVEMENTS_PER_CELL 15

class Infected : public GameObject, public Zombie {
 private:
    std::int16_t health = 100;
    std::int16_t damage_attack = 20;
    std::int16_t x_pos;
    std::int16_t y_pos;
    bool dead = false;
    std::int16_t direction = -1;
    ZombieState* state = new ZombieIdle;

    // se debera recibir por parametro, para que corra camine o salte
    ChaseState* chase_state = new ChaseWalking;
    const std::int16_t id;
    GameMap& map;
    Chaser chaser;


GameObject* get_closest_soldier(std::vector<GameObject*> soldiers);
std::int16_t get_distance_to_soldier(GameObject* soldier);

 public:
Infected(std::int16_t x_pos, std::int16_t y_pos, GameMap& map);
Infected(std::int16_t x_pos, std::int16_t y_pos, std::int16_t id, GameMap& map);

void update(float time) override;

void receive_damage(std::uint16_t damage, float time) override;

bool in_range_of_explosion(std::int16_t x_start,
                           std::int16_t x_finish,
                           std::int16_t y_start,
                           std::int16_t y_finish) override;

void chase_closest_soldier(std::vector<GameObject*> soldiers, float time) override;
void set_direction(std::int16_t direction) override;
void attack(std::vector<GameObject*> soldiers, float time) override;
void get_stunned(float time) override;
void die(float time);

std::int16_t get_id() override;

std::int16_t get_y_pos() override;
std::int16_t get_x_pos() override;
std::int16_t get_y_matrix_pos() override;
std::int16_t get_x_matrix_pos() override;

~Infected();

// ************************* Metodos de testeo ************************************************8//
std::int16_t get_health();
ZombieState* get_state() override;
void change_chase_state_to_running();
ChaseState* get_chasing_state();
};

#endif  // WALKER_H_