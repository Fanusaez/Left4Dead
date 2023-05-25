#ifndef SHOOTING_H_
#define SHOOTING_H_

#include "reloading.h"

class Shooting  : public State {
private:
    Soldier& soldier;
    Weapon* weapon;
    float waiting_time_to_shoot = 0.5;
    float start_time;
public:
    Shooting(Soldier& sodlier, Weapon* weapon, float start_time);

    State* update(float time) override;
    State* shoot(Soldier& soldier, Weapon* weapon, float time) override;
    State* move() override;
    State* reload(Weapon* weapon, float start_time) override;

    bool time_to_shoot(float time);
};


#endif   // SHOOTING_H_
