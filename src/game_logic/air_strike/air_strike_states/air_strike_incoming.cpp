#include "air_strike_incoming.h"
#include "air_strike_exploding.h"
#include "../../configuration.h"

#define CONFIGURATION Configuration::getInstance()

AirStrikeIncoming::AirStrikeIncoming(float time,
                                     std::int16_t x_soldier,
                                     std::int16_t y_soldier,
                                     GameMap &map,
                                     AirStrike *air_strike) :
                                     _time_to_explode(CONFIGURATION.get_air_strike_state_time_incoming()),
                                     start_time(time),
                                     x_soldier(x_soldier),
                                     y_soldier(y_soldier),
                                     map(map),
                                     air_strike(air_strike) {}


AirStrikeState *AirStrikeIncoming::update(float time) {
    if (time_to_explode(time)) {
        return explode(time, x_soldier, y_soldier, map, air_strike);
    }
    return nullptr;
}

AirStrikeState *
AirStrikeIncoming::call_air_strike(float time,
                                   std::int16_t x_soldier,
                                   std::int16_t y_soldier,
                                   GameMap &map,
                                   AirStrike *air_strike) {
    return nullptr;
}

AirStrikeState *AirStrikeIncoming::explode(float time,
                                           std::int16_t x_soldier,
                                           std::int16_t y_soldier,
                                           GameMap &map,
                                           AirStrike *air_strike) {
    return new AirStrikeExploding(time, x_soldier, y_soldier, map, air_strike);
}

bool AirStrikeIncoming::exploding() {
    return false;
}

bool AirStrikeIncoming::time_to_explode(float time) {
    return (time - start_time) >= _time_to_explode;
}