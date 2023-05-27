#ifndef DEAD_H_
#define DEAD_H_

#include "idle.h"

class Dead : public State {

private:
    float time_to_revive = 10;
    float start_time;

public:

    Dead(float time_of_death);

    virtual State* update(float time) override;
    virtual State* shoot(Soldier& soldier, Weapon* weapon, float time) override;
    virtual State* move(Soldier& soldier, std::int16_t direction, float time) override;
    virtual State* reload(Weapon* weapon, float time) override;
    virtual State* being_attacked(float time) override;
    virtual State* die(float time) override;
    virtual State* revive(float time) override;


    bool able_to_revive(float time);

};


#endif //DEAD_H_
