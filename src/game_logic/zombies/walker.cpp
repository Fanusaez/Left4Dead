#include "walker.h"
#define INVALID_POSITION -1
#define UP -1
#define DOWN 1
#define MAX_DISTANCE 10000
#define MOVEMENTS_PER_CELL 15

Walker::Walker(std::int16_t x_pos_wal, std::int16_t y_pos_wal, GameMap& map) :
                x_pos(x_pos_wal * MOVEMENTS_PER_CELL),
                y_pos(y_pos_wal * MOVEMENTS_PER_CELL),
                id(0),
                map(map),
                chaser(this, map, x_pos, y_pos) {}

Walker::Walker(std::int16_t x_pos_wal, std::int16_t y_pos_wal, std::int16_t id, GameMap& map) :
        x_pos(x_pos_wal * MOVEMENTS_PER_CELL),
        y_pos(y_pos_wal * MOVEMENTS_PER_CELL),
        id(id),
        map(map),
        chaser(this, map, x_pos, y_pos) {}

void Walker::receive_damage(std::uint16_t damage, float time) {
    health -= damage;
    if (health <= 0) {
        die(time);
        return;
    }
    ZombieState* new_state = state->being_attacked(time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

void Walker::get_stunned(float time) {
    ZombieState* new_state = state->get_stunned(time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

bool Walker::in_range_of_explosion(std::int16_t x_start,
                                   std::int16_t x_finish,
                                   std::int16_t y_start,
                                   std::int16_t y_finish) {
    std::int16_t x_matrix_pos = x_pos / MOVEMENTS_PER_CELL;
    std::int16_t y_matrix_pos = y_pos / MOVEMENTS_PER_CELL;
    return (x_start <= x_matrix_pos && x_matrix_pos <= x_finish && y_start <= y_matrix_pos && y_matrix_pos <= y_finish);
}

void Walker::chase_closest_soldier(std::vector<GameObject*> soldiers, float time) {
    GameObject* closest_soldier = get_closest_soldier(soldiers);
    std::int16_t x_sold_pos = closest_soldier->get_x_pos();
    std::int16_t y_sold_pos = closest_soldier->get_y_pos();

    ZombieState* new_state = chase_state->chase(state, chaser, x_sold_pos, y_sold_pos, time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
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

    std::int16_t x_matrix_sold = soldier->get_x_matrix_pos();
    std::int16_t y_matrix_sold = soldier->get_y_matrix_pos();
    std::int16_t x_matrix_walker = get_x_matrix_pos();
    std::int16_t y_matrix_walker = get_y_matrix_pos();

    std::int16_t x_distance = x_matrix_sold - x_matrix_walker;
    std::int16_t y_distance = y_matrix_sold - y_matrix_walker;
    return std::sqrt(x_distance * x_distance + y_distance * y_distance);
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

void Walker::attack(std::vector<GameObject *> soldiers, float time) {
    GameObject* closest_soldier = get_closest_soldier(soldiers);
    std::int16_t distance = get_distance_to_soldier(closest_soldier);
    if (distance > 1) return;
    ZombieState* new_state = state->attack_soldier(closest_soldier, damage_attack, time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

void Walker::die(float time) {
    dead = true;
    map.free_entire_position(get_x_matrix_pos(), get_y_matrix_pos());
    ZombieState* new_state = state->die(time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

std::int16_t Walker::get_id() {
    return id;
}

std::int16_t Walker::get_y_pos() {
    return y_pos;
}

std::int16_t Walker::get_x_pos() {
    return x_pos;
}

std::int16_t Walker::get_y_matrix_pos() {
    return y_pos / MOVEMENTS_PER_CELL;
}

std::int16_t Walker::get_x_matrix_pos() {
    return x_pos / MOVEMENTS_PER_CELL;
}

Walker::~Walker() {
    delete state;
    delete chase_state;
}

// ************************* Metodos de testeo ************************************************8//

std::int16_t Walker::get_health() {
    return health;
}

ZombieState* Walker::get_state() {
    return state;
}

void Walker::change_chase_state_to_running() {
    delete chase_state;
    chase_state = new ChaseRunning;
}

ChaseState* Walker::get_chasing_state() {
    return chase_state;
}