#ifndef IDLE_H_
#define IDLE_H_

#include "state.h"
#include "reloading.h"
#include "shooting.h"
#include "moving.h"
class Idle : public State {

public:
    State* update(float time) override;
    State* shoot(Soldier& soldier, Weapon* weapon, float time) override;
    State* move(Soldier& soldier, std::int16_t direction, float time) override;
    State* reload(Weapon* weapon, float start_time) override;

};

#endif  // IDLE_H_