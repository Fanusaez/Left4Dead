#ifndef VENOM_H_
#define VENOM_H_

#include <complex>
#include <cstdint>
#include "zombie.h"
#include "../game_object.h"
#include "../zombie_states/zombie_idle.h"
#include "../zombie_states/chasing_states/chase_walking.h"
#include "../zombies_attack/venom_close_range_attack.h"
#include "../zombies_attack/venom_long_range_attack.h"

class Venom : public GameObject, public Zombie {
private:
    std::int16_t movements_per_cell = 2;
    std::int16_t health = 100;
    std::int16_t damage_attack = 20;
    std::int16_t x_pos;
    std::int16_t y_pos;
    bool dead = false;
    std::int16_t direction = -1;
    ZombieState* state = new ZombieIdle;
    ChaseState* chase_state;
    const std::int16_t id;
    GameMap& map;
    Chaser chaser;
    VenomCloseRange close_attack;
    VenomLongRange long_attack;
    Soldier* get_closest_soldier(std::vector<Soldier*> soldiers);
    std::int16_t get_distance_to_soldier(Soldier* soldier);
    void change_state(ZombieState* new_state);
    void random_chase_state();

public:
    Venom(std::int16_t x_pos, std::int16_t y_pos, std::int16_t id, GameMap& map);

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
    ~Venom();

// ************************* Metodos de testeo ************************************************8//

    ZombieState* get_state() override;
    void change_chase_state_to_running();
    ChaseState* get_chasing_state();
};


#endif //VENOM_H_
