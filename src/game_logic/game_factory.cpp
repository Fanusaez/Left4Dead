#include "game_factory.h"
#include "soldier.h"
#include "weapons/idf.h"
#include "weapons/p90.h"
#include "weapons/scout.h"
#include "map.h"
#include "zombies/infected.h"
#include "zombies/jumper.h"
#include "zombies/witch.h"
#define X_POS 0
#define Y_POS 1

GameFactory::GameFactory(GameMap &map) : map(map) {}

Soldier* GameFactory::get_soldier_with_idf(std::vector<std::int16_t>& soldier_pos) {
    Weapon* idf = new Idf();
    return create_soldier(idf, soldier_pos);
}

Soldier* GameFactory::get_soldier_with_scout(std::vector<std::int16_t>& soldier_pos) {
    Weapon* scout = new Scout();
    return create_soldier(scout, soldier_pos);
}

Soldier* GameFactory::get_soldier_with_p90(std::vector<std::int16_t>& soldier_pos) {
    Weapon* p90 = new P90();
    return create_soldier(p90, soldier_pos);
}

Soldier *GameFactory::create_soldier(Weapon *weapon,std::vector<std::int16_t>& soldier_pos) {
    Soldier* soldier = new Soldier(weapon, map, soldier_pos[X_POS], soldier_pos[Y_POS], id++);
    return soldier;
}

Zombie* GameFactory::create_random_zombie(std::vector<std::int16_t>& zombie_pos) {
    int random_num = std::random_device{}() % 101;
    if (random_num < infected_probability) {
        Zombie* infected = new Infected(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map);
        return infected;
    }
    return nullptr; // para que no tire waning por ahora
}

Zombie* GameFactory::create_infected(std::vector<std::int16_t>& zombie_pos) {
    return new Infected(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map);

}

Zombie* GameFactory::create_jumper(std::vector<std::int16_t>& zombie_pos) {
    return new Jumper(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map);
}

Zombie* GameFactory::create_witch(std::vector<std::int16_t>& zombie_pos) {
    return new Witch(zombie_pos[X_POS], zombie_pos[Y_POS], id++, map);
}
