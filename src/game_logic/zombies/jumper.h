#ifndef JUMPER_H_
#define JUMPER_H_

#include <complex>
#include <cstdint>

#include "zombie.h"
#include "../game_object.h"
#include "../zombie_states/zombie_idle.h"
#include "../zombie_states/chasing_states/chase_jumping.h"



class Jumper : public GameObject, public Zombie {

private:
    std::int16_t health = 100;
    std::int16_t damage_attack = 20;
    std::int16_t x_pos;
    std::int16_t y_pos;
    bool dead = false;
    std::int16_t direction = -1;
    ZombieState* state = new ZombieIdle;
    ChaseState* chase_state = new ChaseJumping;
    const std::int16_t id;
    GameMap& map;
    Chaser chaser;

    Soldier* get_closest_soldier(std::vector<Soldier*> soldiers);
    std::int16_t get_distance_to_soldier(Soldier* soldier);

public:

    Jumper(std::int16_t x_pos_wal, std::int16_t y_pos_wal, std::int16_t id, GameMap& map);

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

    ~Jumper();

// ************************* Metodos de testeo ************************************************8//
    std::int16_t get_health();
    ZombieState* get_state() override;
};


#endif  // JUMPER_H_
