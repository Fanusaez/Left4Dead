#ifndef JUMPER_H_
#define JUMPER_H_

#include <complex>
#include <cstdint>

#include "zombie.h"
#include "../game_object.h"
#include "../zombie_states/zombie_idle.h"
#include "../zombie_states/chasing_states/chase_walking.h"
#include "../zombie_states/chasing_states/chase_running.h"
#include "../chaser.h"


class Jumper : public GameObject, public Zombie {

private:
    std::int16_t movements_per_cell;
    std::int16_t x_pos;
    std::int16_t y_pos;
    const std::int16_t id;
    GameMap& map;
    Chaser chaser;
    std::int16_t health;
    std::int16_t damage_attack;
    std::int16_t damage_attack_by_jump;
    std::int16_t distance_to_hit;
    std::int16_t distance_to_hit_by_jump;
    std::int16_t sight_distance;
    std::int16_t sight_distance_after_being_hit;
    std::vector<std::int16_t> prob_to_walk;
    std::vector<std::int16_t> prob_to_run;
    std::vector<std::int16_t> prob_to_jump;
    ChaseState* chase_state;
    bool dead = false;
    std::int16_t direction = -1;
    ZombieState* state = new ZombieIdle;

    Soldier* get_closest_soldier(std::vector<Soldier*> soldiers);
    std::int16_t get_distance_to_soldier(Soldier* soldier);
    void change_state(ZombieState* new_state);
    void check_damage_by_jump(Soldier* soldier, float time);

public:
    Jumper(std::int16_t x_pos_wal,
           std::int16_t y_pos_wal,
           std::int16_t id,
           GameMap& map,
           std::int16_t extra_health,
           std::int16_t extra_damage);

    void update(std::vector<Soldier*> soldiers, float time) override;

    void receive_damage(std::uint16_t damage, float time) override;

    bool in_range_of_explosion(std::int16_t x_start,
                               std::int16_t x_finish,
                               std::int16_t y_start,
                               std::int16_t y_finish) override;

    void chase_closest_soldier(std::vector<Soldier*> soldiers, float time) override;
    void set_direction(std::int16_t direction) override;
    void attack(std::vector<Soldier*> soldiers, float time) override;
    void get_stunned(float time) override;
    void die(float time);

    std::int16_t get_id() override;

    std::int16_t get_y_pos() override;
    std::int16_t get_x_pos() override;
    std::int16_t get_y_matrix_pos() override;
    std::int16_t get_x_matrix_pos() override;

    bool facing_left() override;
    ZombieType get_type() override;
    std::int16_t get_health() override;
    void random_chase_state();
    ~Jumper();

// ************************* Metodos de testeo ************************************************8//

    ZombieState* get_state() override;
};


#endif  // JUMPER_H_
