#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include "zombie.h"
//#include "walker.h"
class GameMap {
 private:
    std::uint16_t x_size;
    std::uint16_t y_size;
    std::uint16_t radius_damage_grenade = 3 ; // y_size / 6;
    std::vector<std::vector<GameObject*>> map;

    //std::vector<GameObject*> zombies_object;
    std::vector<GameObject*> soldiers;
    std::vector<Zombie*> zombies;

void find_new_y_pos(std::int16_t& new_y_pos_ref,
                    std::uint16_t possible_new_y_pos,
                    std::uint16_t x_pos_sold,
                    std::uint16_t y_pos_sold);

void move_object_y(std::uint16_t x_pos,
                    std::uint16_t y_pos,
                    std::uint16_t y_new_pos);

void get_objects_in_distance(std::int16_t x_grenade_pos,
                             std::int16_t y_grenade_pos,
                             std::vector<GameObject*>& game_objects);

void validate_position(std::int16_t& x_pos, std::int16_t& y_pos);
 public:
GameMap(std::uint16_t x_size, std::uint16_t y_size);

void shoot(std::vector<GameObject*>& game_objects,
           std::uint16_t x_pos_sold,
           std::uint16_t y_pos_sold,
           std::int16_t direction);

void throw_grenade(std::vector<GameObject*>& game_objects,
           std::uint16_t x_pos_grenade,
           std::uint16_t y_pos_grenade);

void collision_with_zombie(std::vector<GameObject*>& game_objects,
                           std::uint16_t x_pos_sold,
                           std::uint16_t y_pos_sold,
                           std::int16_t direction);

void collision_going_down(std::vector<GameObject*>& game_objects,
                                              std::uint16_t x_pos,
                                              std::uint16_t y_pos);
void collision_going_up(std::vector<GameObject*>& game_objects,
                                            std::uint16_t x_pos,
                                            std::uint16_t y_pos);

bool valid_entire_object_position(std::int16_t x_pos,
                                  std::int16_t y_pos);

void move_soldier_up(std::uint16_t x_sold_pos,
                     std::uint16_t y_sold_pos,
                     std::int16_t& new_y_pos_ref);


void move_soldier_down(std::uint16_t x_sold_pos,
                         std::uint16_t y_sold_pos,
                         std::int16_t& new_y_pos_ref);

void move_soldier_right(std::uint16_t x_sold_pos,
                       std::uint16_t y_sold_pos,
                       std::int16_t& new_x_pos_ref);

void move_soldier_left(std::uint16_t x_sold_pos,
                        std::uint16_t y_sold_pos,
                        std::int16_t& new_x_pos_ref);

bool check_free_position(std::int16_t x_pos,
                         std::int16_t y_sold_pos);

void chase_soldier_walking(Zombie* zombie,
                           std::int16_t& x_new_pos,
                           std::int16_t& y_new_pos,
                           GameObject* closest_soldier);

void move_diagonally_up_right(std::int16_t x_zombie,
                              std::int16_t y_zombie,
                              std::int16_t& x_new_zombie,
                              std::int16_t& y_new_zombie,
                              bool& same_place);

void move_diagonally_up_left(std::int16_t x_zombie,
                             std::int16_t y_zombie,
                             std::int16_t& x_new_zombie,
                             std::int16_t& y_new_zombie,
                             bool& same_place);

void move_diagonally_down_right(std::int16_t x_zombie,
                                std::int16_t y_zombie,
                                std::int16_t& x_new_zombie,
                                std::int16_t& y_new_zombie,
                                bool& same_place);

void move_diagonally_down_left(std::int16_t x_zombie,
                               std::int16_t y_zombie,
                               std::int16_t& x_new_zombie,
                               std::int16_t& y_new_zombie,
                               bool& same_place);

/*
 * Asume que le pasas la posicon verdadera (la del x menor), como siempre
*/
void move_object_diagonally(std::int16_t& x_old_pos,
                            std::int16_t& y_old_pos,
                            std::int16_t& x_new_pos,
                            std::int16_t& y_new_pos);

void chase_soldiers();
void attack_soldiers();


    // ***************************************** Metodos de testeo **********************************************************//
bool collision(std::int16_t direction, std::uint16_t x_pos, std::uint16_t y_pos);
bool collision_going_up_test(std::uint16_t x_pos, std::uint16_t y_pos);
bool collision_going_down_test(std::uint16_t x_pos, std::uint16_t y_pos);
void add_soldier(GameObject* soldier, std::uint16_t x_pos, std::uint16_t y_pos);
void add_zombie(GameObject* walker, std::uint16_t x_pos, std::uint16_t y_pos);
void add_obstacle(GameObject* obstacle, std::uint16_t x_pos, std::uint16_t y_pos);
GameObject* get_object(std::uint16_t x_pos, std::uint16_t y_pos);
};
#endif  // MAP_H_
