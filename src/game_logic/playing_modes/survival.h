#ifndef SURVIVAL_H_
#define SURVIVAL_H_

#include <random>
#include "../soldier.h"
#include "../map.h"
#include "../zombies/infected.h"
#include "../weapons/idf.h"
#include "../weapons/scout.h"
#include "../weapons/p90.h"

class Survival {
private:
    float start_time;
    GameMap map;
    std::int16_t time_respawn_zombies;
    std::int16_t time_increase_zombie_life;
    std::int16_t health_power_up;
    std::vector<std::int16_t> infected_prob;
    std::vector<std::int16_t> witch_prob;
    std::vector<std::int16_t> jumper_prob;
    std::int16_t accumulative_extra_health_zombies = 0;
    float last_time_respawned_zombies = -1;
    float last_time_increase_zombies_life = -1;
    bool game_over = false;
    std::vector<Soldier*> players;

    void respawn_zombies(float time);
    void place_obstacles();
    bool time_to_respawn_zombies(float time);
    bool time_to_increase_zombie_life(float time);
    bool still_in_game();
public:

    Survival(std::int16_t x_size, std::int16_t y_size, float time);

    void update(float time);

    Soldier* get_soldier_with_idf();
    Soldier* get_soldier_with_scout();
    Soldier* get_soldier_with_p90();

    std::vector<Zombie*>* get_zombies();

    bool is_game_over();
};


#endif //SURVIVAL_H_