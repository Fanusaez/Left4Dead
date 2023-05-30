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
    Weapon* idf = new Idf();
    return create_and_add_soldier(idf);
}

Soldier *ClearTheZone::get_soldier_with_scout() {
    Weapon* scout = new Scout();
    return create_and_add_soldier(scout);
}

Soldier *ClearTheZone::create_and_add_soldier(Weapon *weapon) {
    std::vector<std::int16_t> sold_pos;
    map.get_position_for_soldier(sold_pos);

    Soldier* soldier = new Soldier(weapon, map, sold_pos[X_POS], sold_pos[Y_POS]);
    bool added = map.add_soldier(soldier,sold_pos[X_POS], sold_pos[Y_POS]);
    if (!added) {
        // throw error
        delete soldier;
        return nullptr;
    }
    soldiers.push_back(soldier);
    return soldier;
}

void ClearTheZone::update(float time) {
    update_soldiers(time);
    update_zombies(time);
    respawn_zombies(time);
    start_time = time;
}

void ClearTheZone::update_soldiers(float time) {
    for (Soldier* soldier : soldiers) {
        soldier->update(time);
    }
}

void ClearTheZone::update_zombies(float time) {
    /*for (Zombie* zombie : zombies) {
        zombie->chase_closest_soldier(map, soldiers, time);
    }*/
}

void ClearTheZone::respawn_zombies(float time) {
    if (time_to_respawn_zombies(time)) {
        std::vector<std::int16_t> zomb_pos;
        map.get_position_for_object(zomb_pos);
        if (zomb_pos.empty()) return; // muy lleno el mapa
        Zombie* zombie = create_random_zombie(zomb_pos);

        bool added = map.add_zombie(dynamic_cast<GameObject*>(zombie), zomb_pos[X_POS], zomb_pos[Y_POS]);
        if (!added) { // en caso de que falle por x motivo, no deberia...
            delete zombie;
            return;
        }
        zombies.push_back(zombie);
    }
}

bool ClearTheZone::time_to_respawn_zombies(float time) {
    return (time - start_time) >= time_respawn_zombies;
}

Zombie* ClearTheZone::create_random_zombie(std::vector<std::int16_t>& zombie_pos) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 100);

    int random_num = dis(gen);
    if (random_num < walkers_probability) {
        Zombie* walker = new Walker(zombie_pos[X_POS], zombie_pos[Y_POS]);
        return walker;
    }

}

