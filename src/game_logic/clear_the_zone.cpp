#include "clear_the_zone.h"

#define X_POS 0
#define Y_POS 1

ClearTheZone::ClearTheZone(std::int16_t x_size,
                           std::int16_t y_size,
                           float time) :    start_time(time),
                                            map(x_size, y_size),
                                            x_size(x_size),
                                            y_size(y_size) {}

Soldier *ClearTheZone::get_soldier_with_idf() {
    return map.get_soldier_with_idf();
}

Soldier *ClearTheZone::get_soldier_with_scout() {
    return map.get_soldier_with_scout();
}

Soldier *ClearTheZone::get_soldier_with_p90() {
    return map.get_soldier_with_p90();
}

void ClearTheZone::update(float time) {
    if (time_to_respawn_zombies(time)) {
        respawn_zombies(time);
        last_time_updated = time;
    }
    map.update(time);
}

void ClearTheZone::respawn_zombies(float time) {
    int random_num = std::random_device{}() % 101;
    if (random_num >= infected_prob[0] && random_num <= infected_prob[1]) {
       map.add_infected();
    } else if (random_num >= witch_prob[0] && random_num <= witch_prob[1]) {
        map.add_witch();
    } else if (random_num >= jumper_prob[0] && random_num <= jumper_prob[1]) {
        map.add_jumper();
    }
}

std::vector<Zombie*>* ClearTheZone::get_zombies() {
    return map.get_zombies();
}

bool ClearTheZone::time_to_respawn_zombies(float time) {
    return (time - last_time_updated) >= time_respawn_zombies;
}
