#ifndef P90_H_
#define P90_H_

#include "weapon.h"
#include "../air_strike/air_strike.h"

class P90 : public Weapon {
 private:
    std::int16_t bullets = 30;
    const std::int16_t mag_capacity = 30;
    std::int16_t damage = 15;
    AirStrike air_strike;

 public:

void update(float time) override;

void shoot(std::vector<GameObject*>& shooting_objects,
           std::uint16_t y_pos_sold, float time) override;

    State* throw_explosive_grenade(GameMap& map,
                             std::int16_t x_matrix_sold,
                             std::int16_t y_matrix_explosion,
                             State* current_state,
                             float time) override;
    State* throw_smoke_grenade(GameMap& map,
                             std::int16_t x_matrix_sold,
                             std::int16_t y_matrix_explosion,
                             State* current_state,
                             float time) override;

    State* call_air_strike(GameMap& map,
                           std::int16_t x_matrix_explosion,
                           std::int16_t y_matrix_sold,
                           State* current_state,
                           float time) override;

void reload() override;
bool isFullyLoaded() override;
bool empty() override;
std::int16_t get_bullets() override;
};


#endif  // P90_H_
