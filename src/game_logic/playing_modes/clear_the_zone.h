#ifndef CLEAR_THE_ZONE_H_
#define CLEAR_THE_ZONE_H_

#include <random>
#include "map_mode.h"
#include "../soldier.h"
#include "../map.h"
#include "../zombies/infected.h"
#include "../weapons/idf.h"
#include "../weapons/scout.h"
#include "../weapons/p90.h"

class ClearTheZone : public MapMode {

private:
    float start_time;
    GameMap map;
    float time_respawn_zombies;
    std::int16_t quantity_total_zombies;
    std::vector<std::int16_t> infected_prob;
    std::vector<std::int16_t> witch_prob;
    std::vector<std::int16_t> jumper_prob;
    std::vector<std::int16_t> spear_prob;
    std::vector<std::int16_t> venom_prob;
    float last_time_updated = -1;
    bool game_over = false;
    bool level_cleared = false;
    std::vector<Soldier*> players;
    
bool zombies_not_dead();

void respawn_zombies(float time);
void place_obstacles();
bool time_to_respawn_zombies(float time);
void game_state_update();
bool still_in_game();
public:

    ClearTheZone(std::int16_t x_size, std::int16_t y_size, float time);

    void update(float time) override;

    Soldier* get_soldier_with_idf() override;
    Soldier* get_soldier_with_scout() override;
    Soldier* get_soldier_with_p90() override;

    std::vector<Zombie*>* get_zombies() override;

    bool is_game_over() override;

    std::int32_t get_total_zombies_dead() override;


};


#endif //CLEAR_THE_ZONE_H_
