#ifndef RELOAD_H_
#define RELOAD_H_

#include "idle.h"

class Reloading : public State {
private:
    Weapon* weapon;
    float time_to_reload = 0.5;
    float start_time;
public:
    Reloading(Weapon* weapon, float time);

    State* update(float time) override;
    State* shoot(Weapon* weapon, float time) override;
    State* move() override;
    State* reload(Weapon* weapon, float time) override;
    bool finished(float time);
};


#endif //RELOAD_H_
