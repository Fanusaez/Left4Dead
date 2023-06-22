#include <cmath>
#include <iostream>
#include "soldier.h"
#include "map.h"
#include "configuration.h"

#define CONFIGURATION Configuration::getInstance()


Soldier::Soldier(Weapon* weapon,
                 GameMap& map,
                 std::int16_t x_pos,
                 std::int16_t y_pos,
                 std::int16_t id) :
        weapon(weapon),
        map(map),
        movements_per_cell(CONFIGURATION.get_movements_per_cell()),
        x_pos(x_pos * movements_per_cell),
        y_pos(y_pos * movements_per_cell),
        id(id),
        health(CONFIGURATION.get_soldier_health()),
        grenade_distance_reach(CONFIGURATION.get_soldier_grenade_distance_reach()),
        matrix_range_to_revive(CONFIGURATION.get_soldier_matrix_range_to_revive()) {}

void Soldier::update(float time) {
    State* new_state = state->update(time);
    change_state(new_state);
    weapon -> update(time);
}

void Soldier::shoot(float time) {
    State* new_state = state->shoot(*this, weapon, time);
    change_state(new_state);
}

// despues deberia pasar el map a estado y que el se encargue
std::vector<GameObject*> Soldier::get_targets() {
    std::vector<GameObject*> shooting_objects;
    map.get_objects_in_shooting(shooting_objects,
              get_x_matrix_pos(),
              get_y_matrix_pos(),
              direction);
    return shooting_objects;
}


void Soldier::reload(float time) {
    State* new_state = state->reload(weapon, time);
    change_state(new_state);
}

void Soldier::throw_explosive_grenade(float time) {
    std::int16_t x_grenade_pos = get_x_matrix_pos();
    adjust_position_grenade(x_grenade_pos);

    State* new_state = weapon->throw_explosive_grenade(map,
                                                       x_grenade_pos,
                                                       get_y_matrix_pos(),
                                                       state,
                                                       time);
    change_state(new_state);
}

void Soldier::throw_smoke_grenade(float time) {
    std::int16_t x_grenade_pos = get_x_matrix_pos();
    adjust_position_grenade(x_grenade_pos);

    State* new_state = weapon->throw_smoke_grenade(map,
                                                   x_grenade_pos,
                                                   get_y_matrix_pos(),
                                                   state,
                                                   time);
    change_state(new_state);
}

void Soldier::call_air_strike(float time) {
    State* new_state = weapon->call_air_strike(map,
                                               get_x_matrix_pos(),
                                               get_y_matrix_pos(),
                                               state,
                                               time);
    change_state(new_state);
}

void Soldier::receive_damage(std::uint16_t damage, float time) {
    health -= damage;
    if (health <= 0) {
        die(time);
    } else {
        State *new_state = state->being_attacked(time);
        change_state(new_state);
    }
}

void Soldier::get_stunned(float time) {}

void Soldier::move_up(float time) {
    State* new_state = state->move(*this, UP, time);
    change_state(new_state);
}

void Soldier::move_down(float time) {
    State* new_state = state->move(*this, DOWN, time);
    change_state(new_state);
}

void Soldier::move_right(float time) {
    State* new_state = state->move(*this, RIGHT, time);
    change_state(new_state);
}

void Soldier::move_left(float time) {
    State* new_state = state->move(*this, LEFT, time);
    change_state(new_state);
}

void Soldier::move_up() {
    if ((y_pos % movements_per_cell) != 0) {
        y_pos -= 1;
        return;
    }
    std::int16_t new_y_map_pos = -1;
    map.move_object_up(get_x_matrix_pos(), get_y_matrix_pos(), new_y_map_pos);
    if (new_y_map_pos >= 0) {
        y_pos -= 1;
    }
}

void Soldier::move_down() {
    std::int16_t y_new_pos = y_pos + 1;
    if ((y_new_pos % movements_per_cell) != 0) {
        y_pos += 1;
        return;
    }
    std::int16_t new_y_map_pos = -1;
    map.move_object_down(get_x_matrix_pos(), get_y_matrix_pos(), new_y_map_pos);
    if (new_y_map_pos >= 0) {
        y_pos += 1;
    }
}

void Soldier::move_right() {
    direction = RIGHT;
    std::int16_t x_new_pos = x_pos + 1;
    if ((x_new_pos % movements_per_cell) != 0) {
        x_pos += 1;
        return;
    }
    std::int16_t new_x_map_pos = -1;
    map.move_object_right(get_x_matrix_pos(), get_y_matrix_pos(), new_x_map_pos);
    if (new_x_map_pos >= 0) {
        x_pos += 1;
    }
}

void Soldier::move_left() {
    direction = LEFT;
    if ((x_pos % movements_per_cell) != 0) {
        x_pos -= 1;
        return;
    }
    std::int16_t new_x_map_pos = -1;
    map.move_object_left(get_x_matrix_pos(), get_y_matrix_pos(), new_x_map_pos);
    if (new_x_map_pos >= 0) {
        x_pos -= 1;
    }
}

void Soldier::revive_partner(float time) {
    Soldier* soldier_to_revive = map.get_soldier_to_revive(get_x_matrix_pos(), get_y_matrix_pos(), matrix_range_to_revive);
    if (soldier_to_revive) {
        soldier_to_revive->revive(time);
    }
}

void Soldier::revive(float time) {
    State* new_state = state -> revive(time);
    change_state(new_state);
}

void Soldier::set_direction(std::int16_t new_direction) {
    direction = new_direction;
}

bool Soldier::in_range_of_explosion(std::int16_t x_start,
                                   std::int16_t x_finish,
                                   std::int16_t y_start,
                                   std::int16_t y_finish) {
    std::int16_t x_matrix_pos = get_x_matrix_pos();
    std::int16_t y_matrix_pos = get_y_matrix_pos();
    return (x_start <= x_matrix_pos && x_matrix_pos <= x_finish && y_start <= y_matrix_pos && y_matrix_pos <= y_finish);
}

void Soldier::die(float time) {
    _dead = true;
    State* new_state = state->die(time);
    change_state(new_state);
}

bool Soldier::chaseable() {
    return health > 0;
}

std::int16_t Soldier::get_id() {
    return id;
}

std::int16_t Soldier::get_y_pos() {
    return y_pos;
}

std::int16_t Soldier::get_x_pos() {
    return x_pos;
}

std::int16_t Soldier::get_y_matrix_pos() {
    return y_pos / movements_per_cell;
}

std::int16_t Soldier::get_x_matrix_pos() {
    return x_pos / movements_per_cell;
}

bool Soldier::facing_left() {
    return (direction == LEFT);
}

void Soldier::change_state(State *new_state) {
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

void Soldier::adjust_position_grenade(std::int16_t& x_grenade_pos) {
    if (direction == LEFT) {
        x_grenade_pos -= grenade_distance_reach;
    } else {
        x_grenade_pos += grenade_distance_reach;
    }

}

bool Soldier::dead() {
    return _dead;
}

ExplosiveGrenade* Soldier::get_explosive_grenade() {
    return weapon->get_explosive_grenade();
}

SmokeGrenade* Soldier::get_smoke_grenade() {
    return weapon->get_smoke_grenade();
}

std::int32_t Soldier::get_total_bullets_shot() {
    return weapon->get_total_bullets_shot();
}

std::int16_t Soldier::get_time_to_throw_explosive_grenade() {
    return weapon -> get_time_to_throw_explosive_grenade();
}

std::int16_t Soldier::get_time_to_throw_smoke_grenade() {
    return weapon -> get_time_to_throw_smoke_grenade();
}

std::int16_t Soldier::get_time_to_call_air_strike() {
    return weapon -> get_time_to_call_air_strike();
}


Soldier::~Soldier(){
    delete weapon;
    delete state;
}



//************************* Metodo de testeo *********************************************//

std::int16_t Soldier::get_direction() {
    return direction;
}

std::int16_t Soldier::get_health() {
    return health;
}

State* Soldier::get_state() {
    return state;
}

void Soldier::stop_action() {
    State* new_state = state->stop_action();
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

Weapon* Soldier::get_weapon() {
    return weapon;
}