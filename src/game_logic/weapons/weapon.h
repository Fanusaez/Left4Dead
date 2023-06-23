#ifndef WEAPON_H_
#define WEAPON_H_

#include <vector>
#include <cstdint>
#include "../common/soldier_type.h"

#define CONFIGURATION Configuration::getInstance()

enum SoldierType;
class State;
class GameObject;
class GameMap;
class ExplosiveGrenade;
class SmokeGrenade;

class Weapon {
 private:

 public:

virtual void update(float time) = 0;

virtual void shoot(std::vector<GameObject*>& shooting_objects,
                   std::uint16_t x_pos_sold, float time) = 0;

virtual State* throw_explosive_grenade(GameMap& map,
                                     std::int16_t x_matrix_explosion,
                                     std::int16_t y_matrix_sold,
                                     State* current_state,
                                     float time) = 0;
virtual State* throw_smoke_grenade(GameMap& map,
                                     std::int16_t x_matrix_explosion,
                                     std::int16_t y_matrix_sold,
                                     State* current_state,
                                     float time) = 0;

virtual State* call_air_strike(GameMap& map,
                                   std::int16_t x_soldier,
                                   std::int16_t y_soldier,
                                   State* current_state,
                                   float time) = 0;

virtual void reload() = 0;
virtual bool isFullyLoaded() = 0;
virtual bool empty() = 0;
virtual std::int16_t get_bullets() = 0;
virtual ExplosiveGrenade* get_explosive_grenade() = 0;
virtual SmokeGrenade* get_smoke_grenade() = 0;
virtual std::int32_t get_total_bullets_shot() = 0;
virtual std::int16_t get_time_to_throw_explosive_grenade() = 0;
virtual std::int16_t get_time_to_throw_smoke_grenade() = 0;
virtual std::int16_t get_time_to_call_air_strike() = 0;
virtual float get_time_to_shoot() = 0;
virtual SoldierType get_type() = 0;
virtual bool time_to_shoot(float time) = 0;
virtual ~Weapon() {}
};
#endif  // WEAPON_H_
