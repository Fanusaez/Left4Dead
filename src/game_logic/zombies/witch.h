#ifndef WITCH_H_
#define WITCH_H_

#include "zombie.h"
#include "../game_object.h"
#include "../zombie_states/zombie_idle.h"
#include "../zombie_states/chasing_states/chase_walking.h"
#include "../soldier.h"


class GameMap;

class Witch : public GameObject, public Zombie {

private:
    std::int16_t movements_per_cell;
    std::int16_t x_pos;
    std::int16_t y_pos;
    const std::int16_t id;
    GameMap& map;
    ChaseState* chase_state = new ChaseWalking;
    std::int16_t health;
    std::int16_t damage_attack;
    std::int16_t probability_to_scream = 1;
    std::int16_t zombies_created_for_screaming = 2;
    bool dead = false;
    std::int16_t direction = LEFT;
    ZombieState* state = new ZombieIdle;

    // se debera recibir por parametro, para que corra camine o salte




    Chaser chaser;

    Soldier* get_closest_soldier(std::vector<Soldier*> soldiers);
    std::int16_t get_distance_to_soldier(Soldier* soldier);
    std::int16_t get_random_number();
public:
    Witch(std::int16_t x_pos, std::int16_t y_pos, std::int16_t id, GameMap& map);
    Witch(std::int16_t x_pos, std::int16_t y_pos, std::int16_t id, GameMap& map, std::int16_t extra_health);

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
    void scream(float time);

    std::int16_t get_id() override;

    std::int16_t get_y_pos() override;
    std::int16_t get_x_pos() override;
    std::int16_t get_y_matrix_pos() override;
    std::int16_t get_x_matrix_pos() override;

    bool facing_left() override;
    ZombieType get_type() override;

    ~Witch();

// ************************* Metodos de testeo ************************************************8//
    std::int16_t get_health();
    ZombieState* get_state() override;
    void change_chase_state_to_running();
    ChaseState* get_chasing_state();
};


#endif //WITCH_H_
