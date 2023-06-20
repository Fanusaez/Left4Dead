#include "game_factory.h"
#include "soldier.h"
#include "weapons/idf.h"
#include "weapons/p90.h"
#include "weapons/scout.h"
#include "map.h"
#include "zombies/infected.h"
#include "zombies/jumper.h"
#include "zombies/witch.h"
#include "zombies/spear.h"
#include "configuration.h"
#define X_POS 0
#define Y_POS 1

#define CONFIGURATION Configuration::getInstance()

GameFactory::GameFactory(GameMap &map) :
    map(map),
    infected_prob(CONFIGURATION.get_GF_infected_prob_to_respawn()),
    witch_prob(CONFIGURATION.get_GF_witch_prob_to_respawn()),
    jumper_prob(CONFIGURATION.get_GF_jumper_prob_to_respawn()) {}

Soldier* GameFactory::get_soldier_with_idf(std::vector<std::int16_t>& soldier_pos) {
    Weapon* idf = new Idf(id++, id++);
    return create_soldier(idf, soldier_pos);
}

Soldier* GameFactory::get_soldier_with_scout(std::vector<std::int16_t>& soldier_pos) {
    Weapon* scout = new Scout(id++, id++);
    return create_soldier(scout, soldier_pos);
}

Soldier* GameFactory::get_soldier_with_p90(std::vector<std::int16_t>& soldier_pos) {
    Weapon* p90 = new P90(id++);
    return create_soldier(p90, soldier_pos);
}

Soldier *GameFactory::create_soldier(Weapon *weapon,std::vector<std::int16_t>& soldier_pos) {
    Soldier* soldier = new Soldier(weapon, map, soldier_pos[X_POS], soldier_pos[Y_POS], id++);
    return soldier;
}

Zombie* GameFactory::create_random_zombie(std::vector<std::int16_t>& zombie_pos) {
    int random_num = std::rand() % 101;
    if (random_num >= infected_prob[0] && random_num <= infected_prob[1]) {
        return new Infected(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map);
    } else if (random_num >= witch_prob[0] && random_num <= witch_prob[1]) {
         return new Witch(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map);
    } else if (random_num >= jumper_prob[0] && random_num <= jumper_prob[1]) {
        return new Jumper(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map);
    }
    return new Infected(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map); // porlas
}

Zombie* GameFactory::create_infected(std::vector<std::int16_t>& zombie_pos, std::int16_t extra_health, std::int16_t extra_damage) {
    return new Infected(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map, extra_health, extra_damage);
}

Zombie* GameFactory::create_jumper(std::vector<std::int16_t>& zombie_pos, std::int16_t extra_health, std::int16_t extra_damage) {
    return new Jumper(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map, extra_health, extra_damage);
}

Zombie* GameFactory::create_witch(std::vector<std::int16_t>& zombie_pos, std::int16_t extra_health, std::int16_t extra_damage) {
    return new Witch(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map, extra_health, extra_damage);
}

Zombie* GameFactory::create_spear(std::vector<std::int16_t>& zombie_pos, std::int16_t extra_health, std::int16_t extra_damage) {
    return new Spear(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map, extra_health, extra_damage);
}