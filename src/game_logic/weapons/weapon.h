#ifndef WEAPON_H_
#define WEAPON_H_

#include <vector>
#include <cstdint>
class State;
class GameObject;
class GameMap;

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
virtual ~Weapon() {}
};
#endif  // WEAPON_H_
