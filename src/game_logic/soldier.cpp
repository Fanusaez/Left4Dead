#include <cmath>
#include <iostream>
#include "soldier.h"

#define GRANADE_DISTANCE_REACH 4
#define WALLS_LIMITS 0.5
#define MOVEMENTS_PER_CELL 15
#define LEFT 2
#define RIGHT 3



Soldier::Soldier(Weapon* weapon, GameMap& map) : weapon(weapon), map(map){} // lo dejo por ahora

Soldier::Soldier(Weapon* weapon,
                 GameMap& map,
                 std::int16_t x_pos,
                 std::int16_t y_pos) :
        weapon(weapon),
        map(map),
        x_pos(x_pos),
        y_pos(y_pos) {}

void Soldier::update(float time) {
    State* new_state = state->update(time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
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
              x_pos,
              y_pos,
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

void Soldier::throw_explosive_grenade() {
    // deberia verificar que no tenga una p90, pq sino estaria haciendo laburar al programa al pedo
    // me ahorraria una operacion costosa

    std::vector<GameObject*> objects;
    std::int16_t y_granade_pos = y_pos;

    if (direction == UP) {
         y_granade_pos -= GRANADE_DISTANCE_REACH;
    } else {
        y_granade_pos += GRANADE_DISTANCE_REACH;
    }

    map.throw_grenade(objects, x_pos, y_granade_pos);
    weapon->throw_explosive_grenade(objects, 1);
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
    direction = UP;
    // ver si con la interfaz si lo saco o no
    if (y_pos <= WALLS_LIMITS) return;

    //std::int16_t y_new_pos = y_pos - 1;
    if ((y_pos % MOVEMENTS_PER_CELL) != 0) {
        y_pos -= 1;
        return;
    }
    std::int16_t x_matrix_pos = x_pos / MOVEMENTS_PER_CELL;
    std::int16_t y_matrix_pos = y_pos / MOVEMENTS_PER_CELL;
    std::int16_t new_y_map_pos = -1;
    map.move_object_up(x_matrix_pos, y_matrix_pos, new_y_map_pos);
    if (new_y_map_pos >= 0) {
        y_pos -= 1;
    }
}

void Soldier::move_down() {
    direction = DOWN;
    std::int16_t y_new_pos = y_pos + 1;
    if ((y_new_pos % MOVEMENTS_PER_CELL) != 0) {
        y_pos += 1;
        return;
    }
    std::int16_t x_matrix_pos = x_pos / MOVEMENTS_PER_CELL;
    std::int16_t y_matrix_pos = y_pos / MOVEMENTS_PER_CELL;
    std::int16_t new_y_map_pos = -1;
    map.move_object_down(x_matrix_pos, y_matrix_pos, new_y_map_pos);
    if (new_y_map_pos >= 0) {
        y_pos += 1;
    }
}

void Soldier::move_right() {
    std::int16_t x_new_pos = x_pos + 1;
    if ((x_new_pos % MOVEMENTS_PER_CELL) != 0) {
        x_pos += 1;
        return;
    }
    std::int16_t x_matrix_pos = x_pos / MOVEMENTS_PER_CELL;
    std::int16_t y_matrix_pos = y_pos / MOVEMENTS_PER_CELL;
    std::int16_t new_x_map_pos = -1;
    map.move_object_right(x_matrix_pos, y_matrix_pos, new_x_map_pos);
    if (new_x_map_pos >= 0) {
        x_pos += 1;
    }
}

void Soldier::move_left() {
    //if (x_pos <= WALLS_LIMITS) return;
    if ((x_pos % MOVEMENTS_PER_CELL) != 0) {
        x_pos -= 1;
        return;
    }
    std::int16_t new_x_map_pos = -1;
    std::int16_t x_matrix_pos = x_pos / MOVEMENTS_PER_CELL;
    std::int16_t y_matrix_pos = y_pos / MOVEMENTS_PER_CELL;
    map.move_object_left(x_matrix_pos, y_matrix_pos, new_x_map_pos);

    if (new_x_map_pos >= 0) {
        x_pos -= 1;
    }
}

void Soldier::set_direction(std::int16_t new_direction) {
    if (new_direction == 1){
        direction = DOWN;
    } else if (new_direction == -1) {
        direction = UP;
    }
}

bool Soldier::in_range_of_explosion(std::int16_t x_start,
                                   std::int16_t x_finish,
                                   std::int16_t y_start,
                                   std::int16_t y_finish) {
    return (x_start <= x_pos && x_pos <= x_finish && y_start <= y_pos && y_pos <= y_finish);
}

void Soldier::get_position(std::vector<float> &pos) {
    pos.push_back(x_pos);
    pos.push_back(y_pos);
}

void Soldier::die(float time) {
    dead = true;
    State* new_state = state->die(time);
    if (new_state != nullptr) {
        delete state;
        state = new_state;
    }
}

Soldier::~Soldier(){
    delete weapon;
    delete state;
}
//************************* Metodo de testeo *********************************************

std::int16_t Soldier::get_y_position() {
    return y_pos;
}

std::int16_t Soldier::get_x_position() {
    return x_pos;
}

std::int16_t Soldier::get_direction() {
    return direction;
}

std::int16_t Soldier::get_health() {
    return health;
}

State* Soldier::get_state() {
    return state;
}

void Soldier::set_idle() {
    delete state;
    state = new Idle;
}