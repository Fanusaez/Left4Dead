#ifndef EXPLODING_H_
#define EXPLODING_H_

#include "grenade_state.h"

class Exploding : public GrenadeState {
private:
    std::int16_t x_explosion;
    std::int16_t y_explosion;
    float start_time;
    float time_to_stop_exploding = 0.08; // lo que dure la animacion

public:
    Exploding(float start_time, std::int16_t x_explosion, std::int16_t y_explosion, GameMap& map, Grenade* grenade);

    GrenadeState* update(float time) override;

    GrenadeState* throw_grenade(float time,
                                std::int16_t x_explosion,
                                std::int16_t y_explosion,
                                GameMap& map,
                                Grenade* grenade) override;

    GrenadeState* explode(float time,
                          std::int16_t x_explosion,
                          std::int16_t y_explosion,
                          GameMap& map,
                          Grenade* grenade) override;

    bool time_stop_explosion(float time);
};


#endif //EXPLODING_H_
