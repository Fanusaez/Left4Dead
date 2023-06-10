#ifndef GAMEFACTORY_H_
#define GAMEFACTORY_H_

#include <cstdint>
#include <vector>

class Soldier;
class Zombie;
class Weapon;
class GameMap;

class GameFactory {
private:
    GameMap& map;
    std::int16_t infected_probability = 100;
    std::int16_t id = 0;

    Soldier* create_soldier(Weapon* weapon, std::vector<std::int16_t>& soldier_pos);

public:
    GameFactory(GameMap& map);

    Soldier* get_soldier_with_idf(std::vector<std::int16_t>& soldier_pos);
    Soldier* get_soldier_with_scout(std::vector<std::int16_t>& soldier_pos);
    Soldier* get_soldier_with_p90(std::vector<std::int16_t>& soldier_pos);
    Zombie* create_random_zombie(std::vector<std::int16_t>& zombie_pos);
    Zombie* create_infected(std::vector<std::int16_t>& zombie_pos);
    Zombie* create_jumper(std::vector<std::int16_t>& zombie_pos);
    Zombie* create_witch(std::vector<std::int16_t>& zombie_pos);
    void create_obstacles(std::vector<std::int16_t>& obstacle_pos);
};


#endif   // GAMEFACTORY_H_
