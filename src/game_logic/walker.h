#ifndef WALKER_H_
#define WALKER_H_

#include <complex>
#include <cstdint>
#include "map.h"
#include "zombie.h"
#include "walking.h"

class Walker : public GameObject, public Zombie {
 private:
    std::int16_t health = 100;
    std::int16_t damage_attack = 20;
    float x_pos;
    float y_pos;
    bool dead = false;
    std::int16_t direction = -1;
    Movement* movement = new Walking(x_pos, y_pos);

GameObject* get_closest_soldier(std::vector<GameObject*> soldiers);
std::int16_t get_distance_to_soldier(GameObject* soldier);
 public:
Walker(std::uint16_t x_pos, std::uint16_t y_pos);

void receive_damage(std::uint16_t damage) override;

bool in_range_of_explosion(std::int16_t x_start,
                           std::int16_t x_finish,
                           std::int16_t y_start,
                           std::int16_t y_finish) override;

void chase_closest_soldier(GameMap& map, std::vector<GameObject*> soldiers) override;
void set_direction(std::int16_t direction) override;
void get_position(std::vector<float>& pos) override;
void attack(GameMap& map, std::vector<GameObject*> soldiers) override;

~Walker();

// ************************* Metodos de testeo ************************************************8//
std::int16_t get_health();
float get_x();
float get_y();
};

#endif  // WALKER_H_
