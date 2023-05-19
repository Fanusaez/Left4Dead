#ifndef WALKER_H_
#define WALKER_H_

#include <complex>
#include <cstdint>
#include "map.h"
#include "zombie.h"

class Walker : public GameObject, public Zombie {
 private:
    std::int16_t health = 100;
    std::uint16_t x_pos;
    std::uint16_t y_pos;
    bool dead = false;
    std::int16_t direction = -1;

 public:
Walker(std::uint16_t x_pos, std::uint16_t y_pos);

void receive_damage(std::uint16_t damage) override;
std::uint16_t get_y_position() override;

bool in_range_of_explosion(std::int16_t x_start,
                           std::int16_t x_finish,
                           std::int16_t y_start,
                           std::int16_t y_finish) override;

void chase_closest_soldier(GameMap& map, std::vector<GameObject*> soldiers) override;
void set_direction(std::int16_t direction) override;
void get_position(std::vector<std::int16_t>& pos) override;
GameObject* get_closest_soldier(std::vector<GameObject*> soldiers);
std::int16_t get_distance_to_soldier(GameObject* soldier);

// ************************* Metodos de testeo ************************************************8//
 std::int16_t get_health();
 std::int16_t get_x();
    std::int16_t get_y();
};

#endif  // WALKER_H_
