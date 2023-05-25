#ifndef STATE_H_
#define STATE_H_


#include "game_logic/weapons/weapon.h"
class Soldier;

class State {

public:
    virtual State* update(float time) = 0;
    virtual State* shoot(Soldier& soldier, Weapon* weapon, float start_time) = 0;
    virtual State* move() = 0;
    virtual State* reload(Weapon* weapon, float start_time) = 0;
    // throwgranade etc

};


#endif   // STATE_H_
