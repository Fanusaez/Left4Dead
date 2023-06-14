#ifndef CLEAR_THE_ZONE_H_
#define CLEAR_THE_ZONE_H_

#include <random>
#include "soldier.h"
#include "map.h"
#include "zombies/infected.h"
#include "weapons/idf.h"
#include "weapons/scout.h"
#include "weapons/p90.h"

class ClearTheZone {

private:
    std::int16_t quantity_total_zombies = 50;
    /*
     * Cada tipo de zombi tiene una probabilidad
     * Suma de todas las probabilidades tiene que ser 100;
     */
    std::vector<std::int16_t> infected_prob = {0, 40};
    std::vector<std::int16_t> witch_prob = {40, 70};
    std::vector<std::int16_t> jumper_prob = {70, 100};
    float start_time;
    float last_time_updated = -1;
    float time_respawn_zombies = 5; // aparece 1 zombi cada 1 segundo
    bool game_over = false;
    GameMap map;
    std::int16_t x_size;
    std::int16_t y_size;


void respawn_zombies(float time);
void place_obstacles();
bool time_to_respawn_zombies(float time);

public:

    ClearTheZone(std::int16_t x_size, std::int16_t y_size, float time);

    void update(float time);

    Soldier* get_soldier_with_idf();
    Soldier* get_soldier_with_scout();
    Soldier* get_soldier_with_p90();

    std::vector<Zombie*>* get_zombies();

};


#endif //CLEAR_THE_ZONE_H_
