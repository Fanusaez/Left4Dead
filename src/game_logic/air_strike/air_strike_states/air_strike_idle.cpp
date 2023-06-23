#include "air_strike_idle.h"
#include "air_strike_incoming.h"

AirStrikeState *AirStrikeIdle::update(float time) {
    return nullptr;
}

AirStrikeState *AirStrikeIdle::call_air_strike(float time,
                                               std::int16_t x_soldier,
                                               std::int16_t y_soldier,
                                               GameMap &map,
                                               AirStrike *air_strike) {
    return new AirStrikeIncoming(time, x_soldier ,y_soldier, map, air_strike);
}

AirStrikeState *AirStrikeIdle::explode(float time, std::int16_t x_soldier, std::int16_t y_soldier, GameMap &map,
                                       AirStrike *air_strike) {
    return nullptr;
}

bool AirStrikeIdle::exploding() {
    return false;
}


