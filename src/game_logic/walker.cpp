#include "walker.h"
#define INVALID_POSITION -1
#define UP -1
#define DOWN 1
#define MAX_DISTANCE 10000

Walker::Walker(std::uint16_t x_pos, std::uint16_t y_pos) :
                x_pos(x_pos),
                y_pos(y_pos) {}

void Walker::receive_damage(std::uint16_t damage) {
    health -= damage;
    if (health <= 0) {
        dead = true;
    }
}

bool Walker::in_range_of_explosion(std::int16_t x_start,
                                   std::int16_t x_finish,
                                   std::int16_t y_start,
                                   std::int16_t y_finish) {
    return (x_start <= x_pos && x_pos <= x_finish && y_start <= y_pos && y_pos <= y_finish);
}

std::uint16_t Walker::get_y_position() {
    return y_pos;
}

void Walker::chase_closest_soldier(GameMap& map, std::vector<GameObject*> soldiers) {
    GameObject* closest_soldier = get_closest_soldier(soldiers);
    std::int16_t x_new_pos = - 1;
    std::int16_t y_new_pos = - 1;
    movement->chase_soldier(this, x_new_pos, y_new_pos, closest_soldier, map);
    //map.chase_soldier_walking(this, x_new_pos, y_new_pos, closest_soldier);
    if (x_new_pos != INVALID_POSITION) {
        x_pos = x_new_pos;
    }
    if (y_new_pos != INVALID_POSITION) {
        if (y_new_pos > y_pos) {
            direction = DOWN;
        } else if (y_new_pos < y_pos) {
            direction = UP;
        }
        y_pos = y_new_pos;
    }
}

GameObject* Walker::get_closest_soldier(std::vector<GameObject*> soldiers) {
    GameObject* closest_soldier = nullptr;
    std::int16_t min_distance = MAX_DISTANCE;

    for (GameObject* soldier : soldiers) {
        std::int16_t new_distance = get_distance_to_soldier(soldier);
        if (new_distance < min_distance) {
            min_distance = new_distance;
            closest_soldier = soldier;
        }
    }
    return closest_soldier;
}

std::int16_t Walker::get_distance_to_soldier(GameObject* soldier) {
    std::vector<std::int16_t> sold_pos;
    soldier->get_position(sold_pos);
    std::int16_t x_distance = sold_pos[0] - x_pos;
    std::int16_t y_distance = sold_pos[1] - y_pos;
    return std::sqrt(x_distance * x_distance + y_distance * y_distance);
}

void Walker::get_position(std::vector<std::int16_t>& pos) {
    pos.push_back(x_pos);
    pos.push_back(y_pos);
}

void Walker::set_direction(std::int16_t direction_to_set) {
    if (direction_to_set == UP){
        direction = UP;
    } else if (direction_to_set == DOWN ){
        direction = DOWN;
    } else {
        // lanzo error
    }
}

void Walker::attack(GameMap &map, std::vector<GameObject *> soldiers) {
    GameObject* closest_soldier = get_closest_soldier(soldiers);
    std::int16_t distance = get_distance_to_soldier(closest_soldier);
    if (distance > 1) return;
    closest_soldier->receive_damage(damage_attack);
}

Walker::~Walker() {
    delete movement;
}

// ************************* Metodos de testeo ************************************************8//

std::int16_t Walker::get_health() {
    return health;
}

std::int16_t Walker::get_x() {
    return x_pos;
}
std::int16_t Walker::get_y() {
    return y_pos;
}