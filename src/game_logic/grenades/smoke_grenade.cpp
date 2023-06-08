#include "smoke_grenade.h"
#include "../map.h"
#include "../game_object.h"
void SmokeGrenade::throw_grenade(GameMap& map,
                                     std::int16_t x_matrix_explosion,
                                     std::int16_t y_matrix_sold,
                                     State*& current_state,
                                     float time) {
    if (!time_throw_grenade(time)) return;
    last_thrown_grenade = time;

    std::vector<GameObject*> objects;
    map.get_objects_in_explosion(objects, x_matrix_explosion, y_matrix_sold, radius_range);
    State* new_state = current_state->throw_smoke_grenade(time);
    if (new_state != nullptr) {
        delete current_state;
        current_state = new_state;
    }
    for (const auto& explosive_object : objects) {
        explosive_object->get_stunned(time);
    }
}

bool SmokeGrenade::time_throw_grenade(float time) {
    return (time - last_thrown_grenade) >= time_to_throw_grenade;
}
