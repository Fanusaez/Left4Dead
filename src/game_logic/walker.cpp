#include "walker.h"
#define INVALID_POSITION -1
#define UP -1
#define DOWN 1
#define MAX_DISTANCE 10000

Walker::Walker(std::int16_t x_pos, std::int16_t y_pos) :
                x_pos(x_pos),
                y_pos(y_pos) {}

Walker::Walker(std::int16_t x_pos, std::int16_t y_pos, float walker_speed) :
        x_pos(x_pos),
        y_pos(y_pos) {
    state->set_speed(walker_speed);
}

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

void Walker::chase_closest_soldier(GameMap& map, std::vector<GameObject*> soldiers, float time) {
    GameObject* closest_soldier = get_closest_soldier(soldiers);
    std::int16_t x_new_pos = - 1;
    std::int16_t y_new_pos = - 1;
    ZombieState* new_state = state->chase_soldier(this, x_pos, y_pos,x_new_pos, y_new_pos, closest_soldier, map, time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
    if (y_new_pos != INVALID_POSITION) {
        if (y_new_pos > y_pos) {
            direction = DOWN;
        } else if (y_new_pos < y_pos) {
            direction = UP;
        }
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
    std::vector<float> sold_pos;
    soldier->get_position(sold_pos);
    std::int16_t x_distance = floor(sold_pos[0]) - floor(x_pos);
    std::int16_t y_distance = floor(sold_pos[1]) - floor(y_pos);
    return std::sqrt(x_distance * x_distance + y_distance * y_distance);
}

void Walker::get_position(std::vector<float>& pos) {
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

void Walker::attack(GameMap &map, std::vector<GameObject *> soldiers, float time) {
    GameObject* closest_soldier = get_closest_soldier(soldiers);
    std::int16_t distance = get_distance_to_soldier(closest_soldier);
    if (distance > 1) return;
    ZombieState* new_state = state->attack_soldier(closest_soldier, damage_attack, time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

// creo que no sirve
bool Walker::in_range_of_attack(GameObject *object) {
    std::vector<float> sold_pos;
    object->get_position(sold_pos);
    std::int16_t y_dist = abs(floor(sold_pos[1]) - floor(y_pos));
    std::int16_t x_dist = abs(floor(sold_pos[0]) - floor(x_pos));
    return (x_dist <= 1 && y_dist == 1);
}

Walker::~Walker() {
    delete state;
}

// ************************* Metodos de testeo ************************************************8//

std::int16_t Walker::get_health() {
    return health;
}

float Walker::get_x() {
    return x_pos;
}
float Walker::get_y() {
    return y_pos;
}

ZombieState* Walker::get_state() {
    return state;
}