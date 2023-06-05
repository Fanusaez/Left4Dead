#ifndef CLEAR_THE_ZONE_H_
#define CLEAR_THE_ZONE_H_

#include <random>
#include "soldier.h"
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
    std::int16_t walkers_probability = 100;
    float start_time;
    float time_respawn_zombies = 1; // aparece 1 zombi cada 1 segundo
    std::int16_t id = 0;
    bool game_over = false;


    GameMap map;
    std::int16_t x_size;
    std::int16_t y_size;

    std::int16_t object_id = 0;
    std::vector<Zombie*> zombies;
    std::vector<Soldier*> soldiers;


void update_soldiers(float time);
void update_zombies(float time);
void respawn_zombies(float time);
void place_obstacles();
bool time_to_respawn_zombies(float time);
void get_position_for_object(std::vector<std::int16_t>& entire_zombie_pos);
Zombie* create_random_zombie(std::vector<std::int16_t>& zombie_pos);
Soldier* create_and_add_soldier(Weapon* weapon);

public:

    ClearTheZone(std::int16_t x_size, std::int16_t y_size, float time);

    void update(float time);

    Soldier* get_soldier_with_idf();
    Soldier* get_soldier_with_scout();
    Soldier* get_soldier_with_p90();

};


#endif //CLEAR_THE_ZONE_H_
