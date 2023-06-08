#include "screaming.h"


Screaming::Screaming(GameMap &map, std::int16_t zombies_to_create, float time) {
    zombie_state = SCREAMING;    
    scream(map, zombies_to_create, time);
}


ZombieState *Screaming::being_attacked(float time) {
    return new ZombieBeingAttacked(time);
}

// atacara la witcher?
ZombieState *Screaming::attack_soldier(GameObject *closest_soldier,
                                                 std::int16_t damage,
                                                 float time) {
    if (time_stop_screaming(time)) {
        return new Attacking(closest_soldier, damage, time);
    }
    return nullptr;
}

ZombieState *Screaming::chase_soldier(Chaser& chaser,
                                                std::int16_t x_pos_chase,
                                                std::int16_t y_pos_chase,
                                                float time) {
    if (time_stop_screaming(time)) {
        return new Walking(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *Screaming::chase_soldier_running(Chaser& chaser,
                                              std::int16_t x_pos_chase,
                                              std::int16_t y_pos_chase,
                                              float time) {
    if (time_stop_screaming(time)) {
        return new Running(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *Screaming::chase_soldier_jumping(Chaser& chaser,
                                              std::int16_t x_pos_chase,
                                              std::int16_t y_pos_chase,
                                              float time) {
    if (time_stop_screaming(time)) {
        return new Jumping(chaser, x_pos_chase, y_pos_chase, time);
    }
    return nullptr;
}

ZombieState *Screaming::die(float time) {
    return new ZombieDead(time);
}

ZombieState *Screaming::get_stunned(float time) {
    return new Stunned(time);
}

ZombieState *Screaming::scream(GameMap &map, std::int16_t zombies_to_create, float time) {
    // map.create_zombies(numero)
    return nullptr;
}

bool Screaming::time_stop_screaming(float time) {
    return (time - last_time_screamed >= waiting_time_to_stop_screaming);
}

void Screaming::set_speed(float speed) {}