#include "explosive_grenade.h"

void ExplosiveGrenade::throw_grenade(GameMap& map,
                                  std::int16_t x_matrix_sold,
                                  std::int16_t y_matrix_explosion,
                                  State*& current_state,
                                  float time) {
    if (!time_throw_grenade(time)) return;
    last_thrown_grenade = time;

    std::vector<GameObject*> objects;
    map.get_objects_in_explosion(objects, x_matrix_sold, y_matrix_explosion);
    State* new_state = current_state->throw_explosive_grenade(time);
    if (new_state == nullptr) return;
    delete current_state;
    current_state = new_state;
    for (const auto& explosive_object : objects) {
        explosive_object->receive_damage(grenade_damage, time);
    }
}

bool ExplosiveGrenade::time_throw_grenade(float time) {
    return (time - last_thrown_grenade) >= time_to_throw_grenade;
}