#include "survival.h"

#define X_POS 0
#define Y_POS 1
#define HEALTH_POWER_UP 10


Survival::Survival(std::int16_t x_size,
                           std::int16_t y_size,
                           float time) :    start_time(time),
                                            map(x_size, y_size) {}

Soldier *Survival::get_soldier_with_idf() {
    Soldier* new_soldier = map.get_soldier_with_idf();
    players.push_back(new_soldier);
    return new_soldier;
}

Soldier *Survival::get_soldier_with_scout() {
    Soldier* new_soldier = map.get_soldier_with_scout();
    players.push_back(new_soldier);
    return new_soldier;
}

Soldier *Survival::get_soldier_with_p90() {
    Soldier* new_soldier = map.get_soldier_with_p90();
    players.push_back(new_soldier);
    return new_soldier;
}

void Survival::update(float time) {
    if (time_to_increase_zombie_life(time)) {
        last_time_increase_zombies_life = time;
        extra_life_zombies += HEALTH_POWER_UP;
    }
    if (time_to_respawn_zombies(time) && still_in_game()) {
        respawn_zombies(time);
        last_time_respawned_zombies = time;
    }
    if (still_in_game()) {
        map.update(time);
    }
}

void Survival::respawn_zombies(float time) {
    int random_num = std::random_device{}() % 101;
    if (random_num >= infected_prob[0] && random_num <= infected_prob[1]) {
        map.add_infected(extra_life_zombies);
    } else if (random_num >= witch_prob[0] && random_num <= witch_prob[1]) {
        map.add_witch(extra_life_zombies);
    } else if (random_num >= jumper_prob[0] && random_num <= jumper_prob[1]) {
        map.add_jumper(extra_life_zombies);
    }
}

std::vector<Zombie*>* Survival::get_zombies() {
    return map.get_zombies();
}

bool Survival::time_to_respawn_zombies(float time) {
    return (time - last_time_respawned_zombies) >= time_respawn_zombies;
}

bool Survival::time_to_increase_zombie_life(float time) {
    return (time - last_time_increase_zombies_life) >= time_increase_zombie_life;
}

bool Survival::still_in_game() {
    for (Soldier* player : players) {
        if (!player->dead()) return true;
    }
    game_over = true;
    return false;
}