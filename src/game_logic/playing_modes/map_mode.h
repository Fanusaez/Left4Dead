#ifndef MAP_MODE_H_
#define MAP_MODE_H_

#include <cstdint>
#include <vector>

class Soldier;
class Zombie;

class MapMode {
public:
    virtual void update(float time) = 0;

    virtual Soldier* get_soldier_with_idf() = 0;
    virtual Soldier* get_soldier_with_scout() = 0;
    virtual Soldier* get_soldier_with_p90() = 0;

    virtual std::vector<Zombie*>* get_zombies() = 0;

    virtual bool is_game_over() = 0;

    virtual std::int32_t get_total_zombies_dead() = 0;
};

#endif  // MAP_MODE_H_
