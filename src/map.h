#ifndef MAP_H_
#define MAP_H_

#include <vector>
#include "game_object.h"

class GameMap {
 private:
    std::uint16_t x_size;
    std::uint16_t y_size;
    std::vector<std::vector<GameObject*>> map;

 public:
GameMap(std::uint16_t x_size, std::uint16_t y_size);

void shoot(std::vector<GameObject*>& game_objects,
           std::uint16_t x_pos_sold,
           std::uint16_t y_pos_sold,
           std::int16_t direction);

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
    // ***************************************** Metodos de testeo **********************************************************//
bool collision(std::int16_t direction, std::uint16_t x_pos, std::uint16_t y_pos);
bool collision_going_up_test(std::uint16_t x_pos, std::uint16_t y_pos);
bool collision_going_down_test(std::uint16_t x_pos, std::uint16_t y_pos);
void add_soldier(GameObject* soldier, std::uint16_t x_pos, std::uint16_t y_pos);
void add_zombie(GameObject* walker, std::uint16_t x_pos, std::uint16_t y_pos);
bool valid_entire_soldier_position(std::int16_t x_pos, std::int16_t y_pos);
};
#endif  // MAP_H_
