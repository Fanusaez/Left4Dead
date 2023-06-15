#include <cstdint>
#include "../acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/p90.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/scout.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/air_strike/air_strike_states/air_strike_incoming.h"
#include "game_logic/air_strike/air_strike_states/air_strike_exploding.h"

#define UP -1
#define DOWN 1
#define AIR_DAMAGE 40
#define REACH_SAFE_AREA 2
#define MAP_SIZE_X 20
#define MAP_SIZE_Y 20

void testAirStrikeStateIdle(void) {

    AirStrike air_strike(0);
    AirStrikeIdle* state = dynamic_cast<AirStrikeIdle*>(air_strike.get_state());

    TEST_CHECK(state != nullptr);
}

void testAirStrikeAndStateChangesToIncoming(void) {
    GameMap map(10, 10, 0);
    State* idle= new Idle;

    AirStrike air_strike(0);
    air_strike.call_air_strike(map, 0, 0, idle, 0);
    AirStrikeIncoming* state = dynamic_cast<AirStrikeIncoming*>(air_strike.get_state());

    TEST_CHECK(state != nullptr);
    delete idle;
     map.empty_vectors();
}

void testAirStrikeAndStateChangesToExploding(void) {
    GameMap map(10, 10, 0);
    State* idle = new Idle;
    AirStrike air_strike(0);
    air_strike.call_air_strike(map, 0, 0, idle, 0);
    air_strike.update(10);
    AirStrikeExploding* state = dynamic_cast<AirStrikeExploding*>(air_strike.get_state());

    TEST_CHECK(state != nullptr);

    delete idle;
     map.empty_vectors();
}

void testAirStrikeAndStateChangesToIdle(void) {
    GameMap map(10, 10, 0);
    State* idle= new Idle;
    AirStrike air_strike(0);
    air_strike.call_air_strike(map, 0, 0, idle, 0);
    air_strike.update(10);
    air_strike.update(20);
    AirStrikeIdle* state = dynamic_cast<AirStrikeIdle*>(air_strike.get_state());

    TEST_CHECK(state != nullptr);
    delete idle;
     map.empty_vectors();
}

TEST_LIST = {
        {"Air strike starts with idle state", testAirStrikeStateIdle},
        {"Air strike changes to Incoming", testAirStrikeAndStateChangesToIncoming},
        {"Air strike changes to Exploding",testAirStrikeAndStateChangesToExploding},
        {"Air strike goes back to state Idle", testAirStrikeAndStateChangesToIdle},
        {NULL, NULL},
};