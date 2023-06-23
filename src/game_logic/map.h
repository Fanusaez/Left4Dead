#ifndef MAP_H_
#define MAP_H_
#include <random>
#include <vector>
#include "zombies/zombie.h"
#include "game_factory.h"

class GameMap {
 private:
    std::uint16_t x_size;
    std::uint16_t y_size;
    std::vector<std::vector<GameObject*>> map;
    std::vector<Soldier*> soldiers;
    std::vector<Zombie*> zombies;
    GameFactory factory;
    std::int16_t y_limit_down = 38; // para interfaz

void find_new_y_pos(std::int16_t& new_y_pos_ref,
                    std::uint16_t possible_new_y_pos,
                    std::uint16_t x_pos_sold,
                    std::uint16_t y_pos_sold);

void move_object_y(std::uint16_t x_pos,
                    std::uint16_t y_pos,
                    std::uint16_t y_new_pos);

void get_objects_in_radius(std::int16_t x_grenade_pos,
                             std::int16_t y_grenade_pos,
                             std::int16_t radius_explosion,
                             std::vector<GameObject*>& game_objects);

void get_valid_pos_in_map(std::int16_t& x_pos, std::int16_t& y_pos); // para granada, cambiar nombre, confunde

void collision_with_zombie(std::vector<GameObject*>& game_objects,
                           std::uint16_t x_pos_sold,
                           std::uint16_t y_pos_sold,
                           std::int16_t direction);

void collision_going_right(std::vector<GameObject*>& game_objects,
                           std::uint16_t x_pos,
                           std::uint16_t y_pos);
void collision_going_left(std::vector<GameObject*>& game_objects,
                          std::uint16_t x_pos,
                          std::uint16_t y_pos);

bool valid_object_position(std::int16_t x_pos,
                           std::int16_t y_pos);

public:

GameMap(std::uint16_t x_size, std::uint16_t y_size);

// para tests
GameMap(std::uint16_t x_size, std::uint16_t y_size, std::int16_t y_limit_down);

void get_objects_in_shooting(std::vector<GameObject*>& game_objects,
           std::uint16_t x_pos_sold,
           std::uint16_t y_pos_sold,
           std::int16_t direction);

void get_objects_in_explosion(std::vector<GameObject*>& game_objects,
           std::uint16_t x_pos_grenade,
           std::uint16_t y_pos_grenade,
           std::int16_t radius_explosion);

void get_objects_in_air_strike( std::vector<GameObject*>& game_objects,
                                std::int16_t x_soldier,
                                std::int16_t y_soldier,
                                std::int16_t range_of_safe_space);

void get_positions_of_explosion_air_strike(std::vector<std::vector<int16_t>>& poistions,
                                           std::int16_t x_pos_called,
                                           std::int16_t y_pos_called,
                                           std::int16_t range_safe_space);

void move_object_up(std::int16_t x_pos,
                     std::int16_t y_pos,
                     std::int16_t& new_y_pos_ref);


void move_object_down(std::int16_t x_pos,
                         std::int16_t y_pos,
                         std::int16_t& new_y_pos_ref);

void move_object_right(std::int16_t x_pos,
                       std::int16_t y_pos,
                       std::int16_t& new_x_pos_ref);

void move_object_left(std::int16_t x_pos,
                        std::int16_t y_pos,
                        std::int16_t& new_x_pos_ref);

bool check_free_position(std::int16_t x_pos,
                         std::int16_t y_pos);

void update(float time);
void chase_soldiers(float time);
void attack_soldiers(float time);
Soldier* get_soldier_to_revive(std::int16_t x_pos, std::int16_t y_pos, std::int16_t range);


void get_position_for_object(std::vector<std::int16_t>& valid_pos);
Soldier* get_soldier_with_idf();
Soldier* get_soldier_with_scout();
Soldier* get_soldier_with_p90();
void add_random_zombie();
void add_infected(std::int16_t extra_health, std::int16_t extra_damage);
void add_jumper(std::int16_t extra_health, std::int16_t extra_damage);
void add_witch(std::int16_t extra_health, std::int16_t extra_damage);
void add_spear(std::int16_t extra_health, std::int16_t extra_damage);

void free_position(std::int16_t x_pos, std::int16_t y_pos);

std::vector<Zombie*>* get_zombies();

~GameMap();

// ***************************************** Metodos de testeo **********************************************************//
bool collision(std::int16_t direction, std::uint16_t x_pos, std::uint16_t y_pos);
bool collision_going_up_test(std::uint16_t x_pos, std::uint16_t y_pos);
bool collision_going_down_test(std::uint16_t x_pos, std::uint16_t y_pos);
void add_obstacle(GameObject* obstacle, std::uint16_t x_pos, std::uint16_t y_pos);
GameObject* get_object(std::uint16_t x_pos, std::uint16_t y_pos);
std::int16_t objects_in_map();
void empty_vectors();
bool add_soldier(Soldier* soldier, std::uint16_t x_pos, std::uint16_t y_pos);
bool add_zombie(Zombie* walker, std::uint16_t x_pos, std::uint16_t y_pos);
};
#endif  // MAP_H_
