#ifndef  IDF_H_
#define  IDF_H_

#include <cstdint>
#include "weapon.h"
#include "../map.h"
#include "../states/state.h"

class Idf : public Weapon {
 private:
    std::int16_t bullets = 50;
    const std::int16_t mag_capacity = 50;
    const std::int16_t close_range_damage = 30;
    const std::int16_t long_range_damage = 15;
    const std::int16_t grenade_damage = 40;
    float time_to_throw_grenade = 30;
    float last_thrown_grenade = 0;


 public:

void shoot(std::vector<GameObject*>& shooting_objects,
           std::uint16_t y_pos_sold, float time) override;

void throw_explosive_grenade(GameMap& map,
                             std::int16_t x_matrix_sold,
                             std::int16_t y_matrix_explosion,
                             State*& current_state,
                             float time) override;

void reload() override;
bool isFullyLoaded() override;
bool empty() override;
std::int16_t get_bullets() override;
bool time_throw_grenade(float time);
};
#endif // IDF_H_
