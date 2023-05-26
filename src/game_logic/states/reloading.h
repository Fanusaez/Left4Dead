#ifndef RELOAD_H_
#define RELOAD_H_

#include "idle.h"

class Reloading : public State {
private:
    Weapon* weapon;
    float waiting_time_to_reload = 0.5;
    float start_time;
public:
    Reloading(Weapon* weapon, float time);

    State* update(float time) override;
    State* shoot(Soldier& soldier, Weapon* weapon, float time) override;
    State* move(Soldier& soldier, std::int16_t direction, float time) override;
    State* reload(Weapon* weapon, float time) override;
    bool time_to_relaod(float time);
};


#endif //RELOAD_H_