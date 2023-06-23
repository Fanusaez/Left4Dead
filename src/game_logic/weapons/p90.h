#ifndef P90_H_
#define P90_H_

#include "weapon.h"
#include "../air_strike/air_strike.h"

class P90 : public Weapon {
 private:
    AirStrike air_strike;
    std::int16_t bullets;
    const std::int16_t mag_capacity;
    const std::int16_t burst_capacity;
    std::int16_t damage;
    float time_to_shoot = 0.1;
    std::int32_t total_bullets_shot;

 public:

explicit P90(std::int16_t id_air_strike);

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

ExplosiveGrenade* get_explosive_grenade() override;
SmokeGrenade* get_smoke_grenade() override;
void reload() override;
bool isFullyLoaded() override;
bool empty() override;
std::int16_t get_bullets() override;
std::int32_t get_total_bullets_shot() override;
std::int16_t get_time_to_throw_explosive_grenade() override;
std::int16_t get_time_to_throw_smoke_grenade() override;
std::int16_t get_time_to_call_air_strike() override;
float get_time_to_shoot() override;
SoldierType get_type() override;
};


#endif  // P90_H_
