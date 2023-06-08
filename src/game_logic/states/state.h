#ifndef STATE_H_
#define STATE_H_


#include <cstdint>
#include "../../common/game_object_state.h"

class Weapon;
class Soldier;

class State {

public:
    virtual State* update(float time) = 0;
    virtual State* shoot(Soldier& soldier, Weapon* weapon, float time) = 0;
    virtual State* move(Soldier& soldier, std::int16_t direction, float time) = 0;
    virtual State* reload(Weapon* weapon, float time) = 0;
    virtual State* being_attacked(float time) = 0;
    virtual State* die(float time) = 0;
    virtual State* revive(float time) = 0;
    virtual State* throw_explosive_grenade(float time) = 0;
    virtual State* stop_action() = 0;
    SoldierObjectState soldier_state = IDLE_SOLDIER;
};


#endif   // STATE_H_
