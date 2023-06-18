#include "clear_the_zone.h"
#include "../configuration.h"

#define CONFIGURATION Configuration::getInstance()

#define X_POS 0
#define Y_POS 1
#define NO_EXTRA_HEALTH 0

ClearTheZone::ClearTheZone(std::int16_t x_size,
                           std::int16_t y_size,
                           float time) :    start_time(time),
                                            map(x_size, y_size),
                                            time_respawn_zombies(CONFIGURATION.get_CTZ_time_respawn_zombies()),
                                            quantity_total_zombies(CONFIGURATION.get_CTZ_total_quantity_zombies()),
                                            infected_prob(CONFIGURATION.get_CTZ_infected_prob_to_respawn()),
                                            witch_prob(CONFIGURATION.get_CTZ_witch_prob_to_respawn()),
                                            jumper_prob(CONFIGURATION.get_CTZ_jumper_prob_to_respawn()) {}

Soldier *ClearTheZone::get_soldier_with_idf() {
    Soldier* new_soldier = map.get_soldier_with_idf();
    players.push_back(new_soldier);
    return new_soldier;
}

Soldier *ClearTheZone::get_soldier_with_scout() {
    Soldier* new_soldier = map.get_soldier_with_scout();
    players.push_back(new_soldier);
    return new_soldier;
}

Soldier *ClearTheZone::get_soldier_with_p90() {
    Soldier* new_soldier = map.get_soldier_with_p90();
    players.push_back(new_soldier);
    return new_soldier;
}

void ClearTheZone::update(float time) {
    game_state_update();
    if (time_to_respawn_zombies(time) && quantity_total_zombies > 0 && still_in_game()) {
        respawn_zombies(time);
        last_time_updated = time;
    }
    if (still_in_game()) {
        map.update(time);
    } else {
        game_over = true;
    }
}

void ClearTheZone::respawn_zombies(float time) {
    quantity_total_zombies--;
    int random_num = std::random_device{}() % 101;
    if (random_num >= infected_prob[0] && random_num <= infected_prob[1]) {
       map.add_infected(NO_EXTRA_HEALTH);
    } else if (random_num >= witch_prob[0] && random_num <= witch_prob[1]) {
        map.add_witch(NO_EXTRA_HEALTH);
    } else if (random_num >= jumper_prob[0] && random_num <= jumper_prob[1]) {
        map.add_jumper(NO_EXTRA_HEALTH);
    }
}

std::vector<Zombie*>* ClearTheZone::get_zombies() {
    return map.get_zombies();
}

bool ClearTheZone::time_to_respawn_zombies(float time) {
    return (time - last_time_updated) >= time_respawn_zombies;
}


void ClearTheZone::game_state_update() {
    if (quantity_total_zombies <= 0 && still_in_game()) { // and soldier alive
        level_cleared = true;
        return;
    }
}

bool ClearTheZone::still_in_game() {
    for (Soldier* player : players) {
        if (!player->dead()) return true;
    }
    return false;
}

bool ClearTheZone::is_game_over(){
    return game_over;
}