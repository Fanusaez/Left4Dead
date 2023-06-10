#ifndef CALLING_AIR_STRIKE_H_
#define CALLING_AIR_STRIKE_H_

#include "state.h"
#include "idle.h"
class CallingAirStrike : public State{
private:
    float time_stop_calling = 0.3; // cuanto tiempo dura la animacion
    float start_time;
public:
    CallingAirStrike(float start_time);

    State* update(float time) override;
    State* shoot(Soldier& soldier, Weapon* weapon, float time) override;
    State* move(Soldier& soldier, std::int16_t direction, float time) override;
    State* reload(Weapon* weapon, float time) override;
    State* being_attacked(float time) override;
    State* die(float time) override;
    State* revive(float time) override;
    State* throw_explosive_grenade(float time) override;
    State* throw_smoke_grenade(float time) override;
    State* call_air_strike(float time) override;
    State* stop_action() override;
    bool time_to_stop_calling(float time);
};


#endif //CALLING_AIR_STRIKE_H_
