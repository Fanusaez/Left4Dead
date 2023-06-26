#include <iostream>
#include "venom.h"
#include "../../map.h"
#include "../../chaser.h"
#include "../../zombie_states/chasing_states/chase_running.h"
#include "../../soldier.h"
#include "venom_attack/venom_long_range_attack.h"

#define INVALID_POSITION -1

Venom::Venom(std::int16_t x_pos_wal, std::int16_t y_pos_wal, std::int16_t id, GameMap& map,  std::int16_t extra_health, std::int16_t extra_damage) :
        movements_per_cell(CONFIGURATION.get_movements_per_cell()),
        x_pos(x_pos_wal * movements_per_cell),
        y_pos(y_pos_wal * movements_per_cell),
        id(id),
        map(map),
        chaser(this, map, x_pos, y_pos),
        health(CONFIGURATION.get_venom_health()),
        distance_to_hit_close(CONFIGURATION.get_venom_distance_to_hit_close_range()),
        distance_to_hit_long(CONFIGURATION.get_venom_distance_to_hit_long_range()),
        sight_distance(CONFIGURATION.get_venom_sight_distance()),
        prob_to_walk(CONFIGURATION.get_venom_prob_to_walk()),
        prob_to_run(CONFIGURATION.get_venom_prob_to_run()),
        prob_to_jump(CONFIGURATION.get_venom_prob_to_jump()){
    random_chase_state();
    health += extra_health;
}

void Venom::update(std::vector<Soldier*> soldiers, float time) {
    ZombieState* new_state = state->update(time);
    change_state(new_state);
    attack(soldiers, time);
    chase_closest_soldier(soldiers, time);
}

void Venom::receive_damage(std::uint16_t damage, float time) {
    health -= damage;
    if (health <= 0) {
        die(time);
        return;
    }
    ZombieState* new_state = state->being_attacked(time);
    change_state(new_state);
}

void Venom::get_stunned(float time) {
    ZombieState* new_state = state->get_stunned(time);
    change_state(new_state);
}

bool Venom::in_range_of_explosion(std::int16_t x_start,
                                     std::int16_t x_finish,
                                     std::int16_t y_start,
                                     std::int16_t y_finish) {
    std::int16_t x_matrix_pos = x_pos / movements_per_cell;
    std::int16_t y_matrix_pos = y_pos / movements_per_cell;
    return (x_start <= x_matrix_pos && x_matrix_pos <= x_finish && y_start <= y_matrix_pos && y_matrix_pos <= y_finish);
}

void Venom::chase_closest_soldier(std::vector<Soldier*> soldiers, float time) {
    Soldier* closest_soldier = get_closest_soldier(soldiers);
    if (!closest_soldier) return;
    std::int16_t x_sold_pos = closest_soldier->get_x_pos();
    std::int16_t y_sold_pos = closest_soldier->get_y_pos();

    ZombieState* new_state = chase_state->chase(state, chaser, x_sold_pos, y_sold_pos, time);
    change_state(new_state);
}

Soldier* Venom::get_closest_soldier(std::vector<Soldier*> soldiers) {
    Soldier* closest_soldier = nullptr;
    std::int16_t min_distance = MAX_DISTANCE;

    for (Soldier* soldier : soldiers) {
        std::int16_t new_distance = get_distance_to_soldier(soldier);
        if (new_distance < min_distance && soldier->chaseable()) {
            min_distance = new_distance;
            closest_soldier = soldier;
        }
    }
    return closest_soldier;
}

std::int16_t Venom::get_distance_to_soldier(Soldier* soldier) {

    std::int16_t x_distance = get_distance_to_soldier_x(soldier);
    std::int16_t y_distance = get_distance_to_soldier_y(soldier);
    return std::sqrt(x_distance * x_distance + y_distance * y_distance);
}

std::int16_t Venom::get_distance_to_soldier_x(Soldier* soldier) {

    std::int16_t x_matrix_sold = soldier->get_x_matrix_pos();
    std::int16_t x_matrix_walker = get_x_matrix_pos();

    return abs(x_matrix_sold - x_matrix_walker);
}

std::int16_t Venom::get_distance_to_soldier_y(Soldier* soldier) {

    std::int16_t y_matrix_sold = soldier->get_y_matrix_pos();
    std::int16_t y_matrix_walker = get_y_matrix_pos();

    return abs(y_matrix_sold - y_matrix_walker);
}

void Venom::set_direction(std::int16_t direction_to_set) {
    if (direction_to_set == LEFT){
        direction = LEFT;
    } else if (direction_to_set == RIGHT){
        direction = RIGHT;
    } else {
        // lanzo error
    }
}

void Venom::attack(std::vector<Soldier*> soldiers, float time) {
    Soldier* closest_soldier = get_closest_soldier(soldiers);
    if (!closest_soldier) return;
    std::int16_t distance_x = get_distance_to_soldier_x(closest_soldier);
    std::int16_t distance_y = get_distance_to_soldier_y(closest_soldier);
    if (distance_x > distance_to_hit_long) return;
    if (distance_x > distance_to_hit_close && distance_y == distance_to_hit_y) {
        ZombieState* new_state = attack_long_range.attack(state, closest_soldier, time);
        change_state(new_state);
    } else if (distance_y == distance_to_hit_y){
        ZombieState* new_state = attack_close_range.attack(state, closest_soldier, time);
        change_state(new_state);
    }

}

void Venom::die(float time) {
    dead = true;
    map.free_position(get_x_matrix_pos(), get_y_matrix_pos());
    ZombieState* new_state = state->die(time);
    change_state(new_state);
}

std::int16_t Venom::get_y_pos() {
    return y_pos;
}

std::int16_t Venom::get_x_pos() {
    return x_pos;
}

std::int16_t Venom::get_y_matrix_pos() {
    return y_pos / movements_per_cell;
}

std::int16_t Venom::get_x_matrix_pos() {
    return x_pos / movements_per_cell;
}

bool Venom::facing_left() {
    return (direction == LEFT);
}

std::int16_t Venom::get_id() {
    return id;
}

ZombieType Venom::get_type(){
    return VENOM;
}

void Venom::change_state(ZombieState *new_state) {
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

void Venom::random_chase_state() {
    int random_num = std::rand() % 101;
    if (random_num >= prob_to_walk[0] && random_num <= prob_to_walk[1]) {
        chase_state = new ChaseWalking;
    } else if (random_num >= prob_to_run[0] && random_num <= prob_to_run[1]) {
        chase_state = new ChaseRunning;
    } else {
        chase_state = new ChaseWalking;
    }
}

std::vector<std::int16_t> Venom::get_pos_of_explosion_long_range() {
    return attack_long_range.get_pos_explosion();
}

Venom::~Venom() {
    delete state;
    delete chase_state;
}
// ************************* Metodos de testeo ************************************************8//

std::int16_t Venom::get_health() {
    return health;
}

ZombieState* Venom::get_state() {
    return state;
}

void Venom::change_chase_state_to_running() {
    delete chase_state;
    chase_state = new ChaseRunning;
}

ChaseState* Venom::get_chasing_state() {
    return chase_state;
}