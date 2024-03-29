#include "survival.h"
#include "../configuration.h"

#define X_POS 0
#define Y_POS 1
#define CONFIGURATION Configuration::getInstance()

Survival::Survival(std::int16_t x_size,
                           std::int16_t y_size,
                           float time) :    start_time(time),
                                            map(x_size, y_size),
                                            time_respawn_zombies(CONFIGURATION.get_survival_time_respawn_zombies()),
                                            _time_to_power_up_zombie(CONFIGURATION.get_survival_time_zombies_getting_stronger()),
                                            health_power_up(CONFIGURATION.get_survival_health_power_up()),
                                            damage_power_up(CONFIGURATION.get_survival_damage_power_up()),
                                            infected_prob(CONFIGURATION.get_survival_infected_prob_to_respawn()),
                                            witch_prob(CONFIGURATION.get_survival_witch_prob_to_respawn()),
                                            jumper_prob(CONFIGURATION.get_survival_jumper_prob_to_respawn()),
                                            spear_prob(CONFIGURATION.get_survival_spear_prob_to_respawn()),
                                            venom_prob(CONFIGURATION.get_survival_venom_prob_to_respawn()) {}

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
    if (time_to_power_up_zombie(time)) {
        last_time_powerd_up_zombie = time;
        accumulative_extra_health_zombies += health_power_up;
        accumulative_extra_damage_zombies += damage_power_up;
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
        map.add_infected(accumulative_extra_health_zombies, accumulative_extra_damage_zombies);
    } else if (random_num >= witch_prob[0] && random_num <= witch_prob[1]) {
        map.add_witch(accumulative_extra_health_zombies, accumulative_extra_damage_zombies);
    } else if (random_num >= jumper_prob[0] && random_num <= jumper_prob[1]) {
        map.add_spear(accumulative_extra_health_zombies, accumulative_extra_damage_zombies);
    } else if (random_num >= spear_prob[0] && random_num <= spear_prob[1]) {
        map.add_spear(accumulative_extra_health_zombies, accumulative_extra_damage_zombies);
    } else {
        map.add_venom(accumulative_extra_health_zombies, accumulative_extra_damage_zombies);
    }
}

std::vector<Zombie*>* Survival::get_zombies() {
    return map.get_zombies();
}

bool Survival::time_to_respawn_zombies(float time) {
    return (time - last_time_respawned_zombies) >= time_respawn_zombies;
}

bool Survival::time_to_power_up_zombie(float time) {
    return (time - last_time_powerd_up_zombie) >= _time_to_power_up_zombie;
}

bool Survival::still_in_game() {
    for (Soldier* player : players) {
        if (!player->dead()) return true;
    }
    game_over = true;
    return false;
}

bool Survival::is_game_over() {
    return game_over;
}

std::int32_t Survival::get_total_zombies_dead() {
    std::vector<Zombie*>* zombies = map.get_zombies();
    std::int32_t total_zombies_killed = 0;
    for (Zombie* zombie : *zombies) {
        if (zombie->get_health() <= 0) {
            total_zombies_killed++;
        }
    }
    return total_zombies_killed;
}

Survival::~Survival() {}