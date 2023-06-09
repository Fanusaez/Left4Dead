#include <cmath>
#include <iostream>
#include "soldier.h"
#include "map.h"

#define GRANADE_DISTANCE_REACH 4
#define WALLS_LIMITS 0.5

Soldier::Soldier(Weapon* weapon, GameMap& map) : weapon(weapon), map(map), id(map.get_id()){} // lo dejo por ahora

Soldier::Soldier(Weapon* weapon,
                 GameMap& map,
                 std::int16_t x_pos,
                 std::int16_t y_pos) :
        weapon(weapon),
        map(map),
        x_pos(x_pos * MOVEMENTS_PER_CELL),
        y_pos(y_pos * MOVEMENTS_PER_CELL),
        id(map.get_id()) {}

Soldier::Soldier(Weapon* weapon,
                 GameMap& map,
                 std::int16_t x_pos,
                 std::int16_t y_pos,
                 std::int16_t id) :
        weapon(weapon),
        map(map),
        x_pos(x_pos * MOVEMENTS_PER_CELL),
        y_pos(y_pos * MOVEMENTS_PER_CELL),
        id(id) {}

void Soldier::update(float time) {
    State* new_state = state->update(time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
    weapon -> update(time);
}

void Soldier::shoot(float time) {
    State* new_state = state->shoot(*this, weapon, time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

// despues deberia pasar el map a estado y que el se encargue
std::vector<GameObject *> Soldier::get_targets() {
    std::vector<GameObject*> shooting_objects;
    map.shoot(shooting_objects,
              get_x_matrix_pos(),
              get_y_matrix_pos(),
              direction);
    return shooting_objects;
}


void Soldier::reload(float time) {
    State* new_state = state->reload(weapon, time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

void Soldier::throw_explosive_grenade(float time) {
    std::int16_t x_grenade_pos = x_pos / MOVEMENTS_PER_CELL;

    if (direction == LEFT) {
         x_grenade_pos -= GRANADE_DISTANCE_REACH;
    } else {
        x_grenade_pos += GRANADE_DISTANCE_REACH;
    }

    State* new_state = weapon->throw_explosive_grenade(map,
                                                       x_grenade_pos,
                                                       get_y_matrix_pos(),
                                                       state,
                                                       time);
    if (new_state) {
        delete state;
        state = new_state;
    }
}

void Soldier::throw_smoke_grenade(float time) {
    std::int16_t x_grenade_pos = x_pos / MOVEMENTS_PER_CELL;

    if (direction == LEFT) {
        x_grenade_pos -= GRANADE_DISTANCE_REACH;
    } else {
        x_grenade_pos += GRANADE_DISTANCE_REACH;
    }

    State* new_state = weapon->throw_smoke_grenade(map,
                                                   x_grenade_pos,
                                                   get_y_matrix_pos(),
                                                   state,
                                                   time);
    if (new_state) {
        delete state;
        state = new_state;
    }
}

void Soldier::receive_damage(std::uint16_t damage, float time) {
    health -= damage;
    if (health <= 0) {
        die(time);
    } else {
        State *new_state = state->being_attacked(time);
        if (new_state != nullptr) {
            delete state;
            state = new_state;
        }
    }
}

void Soldier::get_stunned(float time) {}

void Soldier::move_up(float time) {
    State* new_state = state->move(*this, UP, time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

void Soldier::move_down(float time) {
    State* new_state = state->move(*this, DOWN, time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

void Soldier::move_right(float time) {
    State* new_state = state->move(*this, RIGHT, time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

void Soldier::move_left(float time) {
    State* new_state = state->move(*this, LEFT, time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

void Soldier::move_up() {
    // ver si con la interfaz si lo saco o no
    if (y_pos <= WALLS_LIMITS) return;

    if ((y_pos % MOVEMENTS_PER_CELL) != 0) {
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
    if ((y_new_pos % MOVEMENTS_PER_CELL) != 0) {
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
    std::cout << "pos matrix soldier: "<< get_x_matrix_pos()<< " " << get_y_matrix_pos() << std::endl;
    direction = RIGHT;
    std::int16_t x_new_pos = x_pos + 1;
    if ((x_new_pos % MOVEMENTS_PER_CELL) != 0) {
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
    //if (x_pos <= WALLS_LIMITS) return;
    if ((x_pos % MOVEMENTS_PER_CELL) != 0) {
        x_pos -= 1;
        return;
    }
    std::int16_t new_x_map_pos = -1;
    map.move_object_left(get_x_matrix_pos(), get_y_matrix_pos(), new_x_map_pos);
    if (new_x_map_pos >= 0) {
        x_pos -= 1;
    }
}

void Soldier::set_direction(std::int16_t new_direction) {
    direction = new_direction;
}

bool Soldier::in_range_of_explosion(std::int16_t x_start,
                                   std::int16_t x_finish,
                                   std::int16_t y_start,
                                   std::int16_t y_finish) {
    std::int16_t x_matrix_pos = x_pos / MOVEMENTS_PER_CELL;
    std::int16_t y_matrix_pos = y_pos / MOVEMENTS_PER_CELL;
    return (x_start <= x_matrix_pos && x_matrix_pos <= x_finish && y_start <= y_matrix_pos && y_matrix_pos <= y_finish);
}

void Soldier::die(float time) {
    dead = true;
    State* new_state = state->die(time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

std::int16_t Soldier::get_id() {
    return id;
}

Soldier::~Soldier(){
    delete weapon;
    delete state;
}

std::int16_t Soldier::get_y_pos() {
    return y_pos;
}

std::int16_t Soldier::get_x_pos() {
    return x_pos;
}

std::int16_t Soldier::get_y_matrix_pos() {
    return y_pos / MOVEMENTS_PER_CELL;
}

std::int16_t Soldier::get_x_matrix_pos() {
    return x_pos / MOVEMENTS_PER_CELL;
}

//************************* Metodo de testeo *********************************************



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