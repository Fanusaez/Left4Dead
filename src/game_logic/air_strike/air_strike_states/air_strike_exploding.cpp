#include "air_strike_exploding.h"
#include "air_strike_idle.h"
#include "../air_strike.h"

AirStrikeExploding::AirStrikeExploding(float time, std::int16_t x_soldier,
                                       std::int16_t y_soldier,
                                       GameMap &map,
                                       AirStrike *air_strike) :
                                       start_time(time) {

    explode(time, x_soldier,y_soldier, map, air_strike);
}


AirStrikeState *AirStrikeExploding::update(float time) {
    if (time_to_stop_exploding(time)) {
        return new AirStrikeIdle;
    }
    return nullptr;
}

AirStrikeState *
AirStrikeExploding::call_air_strike(float time,
                                    std::int16_t x_soldier,
                                    std::int16_t y_soldier,
                                    GameMap &map,
                                    AirStrike *air_strike) {
    return nullptr;
}

AirStrikeState *AirStrikeExploding::explode(float time,
                                            std::int16_t x_soldier,
                                            std::int16_t y_soldier,
                                            GameMap &map,
                                            AirStrike *air_strike) {
    air_strike->explode(time, x_soldier, y_soldier, map);
    return nullptr;
}

bool AirStrikeExploding::time_to_stop_exploding(float time) {
    return (time - start_time) >= time_stop_exploding;
}