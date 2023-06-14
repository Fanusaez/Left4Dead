#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/p90.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/scout.h"
#include "game_logic/weapons/idf.h"

#define UP -1
#define DOWN 1
#define AIR_DAMAGE 30
#define REACH_SAFE_AREA 2
#define MAP_SIZE_X 20
#define MAP_SIZE_Y 20

void testSoldierCallsAirStrikeAndDamages4Zombies(void) {

    std::int16_t  x_called_place = 10;
    std::int16_t  y_called_place = 10;

    std::int16_t  x_limit_safe_left = x_called_place - REACH_SAFE_AREA;
    std::int16_t  x_limit_safe_right = x_called_place + REACH_SAFE_AREA;

    std::int16_t  y_limit_safe_up = y_called_place - REACH_SAFE_AREA;
    std::int16_t  y_limit_safe_down = y_called_place + REACH_SAFE_AREA;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* p90 = new P90(0);

    Soldier soldier(p90, map, x_called_place, y_called_place);
    map.add_soldier(&soldier, x_called_place, y_called_place);

    Infected walker1(x_limit_safe_left - 1,y_limit_safe_up, map); // donde cae la granada
    map.add_zombie(&walker1, x_limit_safe_left - 1,y_limit_safe_up);

    Infected walker2(x_limit_safe_right + 1,y_limit_safe_up, map);
    map.add_zombie(&walker2, x_limit_safe_right + 1,y_limit_safe_up);

    Infected walker3(x_limit_safe_left - 1,y_limit_safe_down, map);
    map.add_zombie(&walker3, x_limit_safe_left - 1,y_limit_safe_down);

    Infected walker4(x_limit_safe_right + 1,y_limit_safe_down,map);
    map.add_zombie(&walker4, x_limit_safe_right + 1,y_limit_safe_down);

    soldier.call_air_strike(100);
    soldier.update(200);

    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    std::uint16_t remaining_health4 = walker4.get_health();

    TEST_CHECK(remaining_health1 < 100);
    TEST_CHECK(remaining_health2 < 100);
    TEST_CHECK(remaining_health3 < 100);
    TEST_CHECK(remaining_health4 < 100);
}

void testSoldierCallsAirStrikeAndDamages4Zombies2(void) {

    std::int16_t  x_called_place = 10;
    std::int16_t  y_called_place = 10;

    std::int16_t  x_limit_safe_left = x_called_place - REACH_SAFE_AREA;
    std::int16_t  x_limit_safe_right = x_called_place + REACH_SAFE_AREA;

    std::int16_t  y_limit_safe_up = y_called_place - REACH_SAFE_AREA;
    std::int16_t  y_limit_safe_down = y_called_place + REACH_SAFE_AREA;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* p90 = new P90(0);

    Soldier soldier(p90, map, x_called_place, y_called_place);
    map.add_soldier(&soldier, x_called_place, y_called_place);

    Infected walker1(MAP_SIZE_X - 1,MAP_SIZE_Y - 1, map); // donde cae la granada
    map.add_zombie(&walker1, MAP_SIZE_X - 1,MAP_SIZE_Y - 1);

    Infected walker2(0,0, map);
    map.add_zombie(&walker2, 0,0);

    Infected walker3(0,MAP_SIZE_Y - 1, map);
    map.add_zombie(&walker3, 0,MAP_SIZE_Y - 1);

    Infected walker4(MAP_SIZE_X - 1,0,map);
    map.add_zombie(&walker4, MAP_SIZE_X - 1,0);

    soldier.call_air_strike(100);
    soldier.update(200);

    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    std::uint16_t remaining_health4 = walker4.get_health();

    TEST_CHECK(remaining_health1 < 100);
    TEST_CHECK(remaining_health2 < 100);
    TEST_CHECK(remaining_health3 < 100);
    TEST_CHECK(remaining_health4 < 100);
}

void testSoldierCallsAirStrikeWith2ExtraSoldiersByHisSideAndDamages4Zombies(void) {

    std::int16_t  x_called_place = 10;
    std::int16_t  y_called_place = 10;

    std::int16_t  x_limit_safe_left = x_called_place - REACH_SAFE_AREA;
    std::int16_t  x_limit_safe_right = x_called_place + REACH_SAFE_AREA;

    std::int16_t  y_limit_safe_up = y_called_place - REACH_SAFE_AREA;
    std::int16_t  y_limit_safe_down = y_called_place + REACH_SAFE_AREA;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* p90 = new P90(0);
    Weapon* idf = new Idf(0, 0);
    Weapon* idf2 = new Idf(0, 0);

    Soldier soldier1(p90, map, x_called_place, y_called_place);
    map.add_soldier(&soldier1, x_called_place, y_called_place);

    Soldier soldier2(idf, map, x_limit_safe_right, y_limit_safe_up);
    map.add_soldier(&soldier2, x_limit_safe_right, y_limit_safe_up);

    Soldier soldier3(idf2, map, x_limit_safe_left, y_limit_safe_down);
    map.add_soldier(&soldier3, x_limit_safe_left, y_limit_safe_down);

    Infected walker1(MAP_SIZE_X - 1,MAP_SIZE_Y - 1, map); // donde cae la granada
    map.add_zombie(&walker1, MAP_SIZE_X - 1,MAP_SIZE_Y - 1);

    Infected walker2(0,0, map);
    map.add_zombie(&walker2, 0,0);

    Infected walker3(0,MAP_SIZE_Y - 1, map);
    map.add_zombie(&walker3, 0,MAP_SIZE_Y - 1);

    Infected walker4(MAP_SIZE_X - 1,0,map);
    map.add_zombie(&walker4, MAP_SIZE_X - 1,0);

    soldier1.call_air_strike(100);
    soldier1.update(200);

    std::int16_t health_soldier1 = soldier1.get_health();
    std::int16_t health_soldier2 = soldier1.get_health();
    std::int16_t health_soldier3 = soldier1.get_health();

    TEST_CHECK(health_soldier1 == 100);
    TEST_CHECK(health_soldier2 == 100);
    TEST_CHECK(health_soldier3 == 100);

    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    std::uint16_t remaining_health4 = walker4.get_health();

    TEST_CHECK(remaining_health1 < 100);
    TEST_CHECK(remaining_health2 < 100);
    TEST_CHECK(remaining_health3 < 100);
    TEST_CHECK(remaining_health4 < 100);
}

void testSoldierCallsAirStrikeWithIDFButNothingHappen(void) {

    std::int16_t  x_called_place = 10;
    std::int16_t  y_called_place = 10;

    std::int16_t  x_limit_safe_left = x_called_place - REACH_SAFE_AREA;
    std::int16_t  x_limit_safe_right = x_called_place + REACH_SAFE_AREA;

    std::int16_t  y_limit_safe_up = y_called_place - REACH_SAFE_AREA;
    std::int16_t  y_limit_safe_down = y_called_place + REACH_SAFE_AREA;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* idf = new Idf(0, 0);

    Soldier soldier(idf, map, x_called_place, y_called_place);
    map.add_soldier(&soldier, x_called_place, y_called_place);

    Infected walker1(x_limit_safe_left - 1,y_limit_safe_up, map); // donde cae la granada
    map.add_zombie(&walker1, x_limit_safe_left - 1,y_limit_safe_up);

    Infected walker2(x_limit_safe_right + 1,y_limit_safe_up, map);
    map.add_zombie(&walker2, x_limit_safe_right + 1,y_limit_safe_up);

    Infected walker3(x_limit_safe_left - 1,y_limit_safe_down, map);
    map.add_zombie(&walker3, x_limit_safe_left - 1,y_limit_safe_down);

    Infected walker4(x_limit_safe_right + 1,y_limit_safe_down,map);
    map.add_zombie(&walker4, x_limit_safe_right + 1,y_limit_safe_down);

    soldier.call_air_strike(100);
    soldier.update(200);

    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    std::uint16_t remaining_health4 = walker4.get_health();

    TEST_CHECK(remaining_health1 == 100);
    TEST_CHECK(remaining_health2 == 100);
    TEST_CHECK(remaining_health3 == 100);
    TEST_CHECK(remaining_health4 == 100);
}

void testSoldierCallsAirStrikeWithScoutButNothingHappen(void) {

    std::int16_t  x_called_place = 10;
    std::int16_t  y_called_place = 10;

    std::int16_t  x_limit_safe_left = x_called_place - REACH_SAFE_AREA;
    std::int16_t  x_limit_safe_right = x_called_place + REACH_SAFE_AREA;

    std::int16_t  y_limit_safe_up = y_called_place - REACH_SAFE_AREA;
    std::int16_t  y_limit_safe_down = y_called_place + REACH_SAFE_AREA;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, x_called_place, y_called_place);
    map.add_soldier(&soldier, x_called_place, y_called_place);

    Infected walker1(x_limit_safe_left - 1,y_limit_safe_up, map); // donde cae la granada
    map.add_zombie(&walker1, x_limit_safe_left - 1,y_limit_safe_up);

    Infected walker2(x_limit_safe_right + 1,y_limit_safe_up, map);
    map.add_zombie(&walker2, x_limit_safe_right + 1,y_limit_safe_up);

    Infected walker3(x_limit_safe_left - 1,y_limit_safe_down, map);
    map.add_zombie(&walker3, x_limit_safe_left - 1,y_limit_safe_down);

    Infected walker4(x_limit_safe_right + 1,y_limit_safe_down,map);
    map.add_zombie(&walker4, x_limit_safe_right + 1,y_limit_safe_down);

    soldier.call_air_strike(100);
    soldier.update(200);

    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    std::uint16_t remaining_health4 = walker4.get_health();

    TEST_CHECK(remaining_health1 == 100);
    TEST_CHECK(remaining_health2 == 100);
    TEST_CHECK(remaining_health3 == 100);
    TEST_CHECK(remaining_health4 == 100);
}

void testSoldierCalls2AirStrikeOnlyCallsOne(void) {

    std::int16_t  x_called_place = 10;
    std::int16_t  y_called_place = 10;

    std::int16_t  x_limit_safe_left = x_called_place - REACH_SAFE_AREA;
    std::int16_t  x_limit_safe_right = x_called_place + REACH_SAFE_AREA;

    std::int16_t  y_limit_safe_up = y_called_place - REACH_SAFE_AREA;
    std::int16_t  y_limit_safe_down = y_called_place + REACH_SAFE_AREA;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* p90 = new P90(0);

    Soldier soldier(p90, map, x_called_place, y_called_place);
    map.add_soldier(&soldier, x_called_place, y_called_place);

    Infected walker1(x_limit_safe_left - 1,y_limit_safe_up, map); // donde cae la granada
    map.add_zombie(&walker1, x_limit_safe_left - 1,y_limit_safe_up);

    Infected walker2(x_limit_safe_right + 1,y_limit_safe_up, map);
    map.add_zombie(&walker2, x_limit_safe_right + 1,y_limit_safe_up);

    Infected walker3(x_limit_safe_left - 1,y_limit_safe_down, map);
    map.add_zombie(&walker3, x_limit_safe_left - 1,y_limit_safe_down);

    Infected walker4(x_limit_safe_right + 1,y_limit_safe_down,map);
    map.add_zombie(&walker4, x_limit_safe_right + 1,y_limit_safe_down);

    soldier.call_air_strike(100);
    soldier.update(110);

    soldier.call_air_strike(120);
    soldier.update(130);

    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    std::uint16_t remaining_health4 = walker4.get_health();

    TEST_CHECK(remaining_health1 == 100 - AIR_DAMAGE);
    TEST_CHECK(remaining_health2 == 100 - AIR_DAMAGE);
    TEST_CHECK(remaining_health3 == 100 - AIR_DAMAGE);
    TEST_CHECK(remaining_health4 == 100 - AIR_DAMAGE);
}


TEST_LIST = {
        {"Soldier with p90 calls an airstrike and damages 4 zombies", testSoldierCallsAirStrikeAndDamages4Zombies},
        {"Soldier with p90 calls an airstrike and damages 4 zombies", testSoldierCallsAirStrikeAndDamages4Zombies2},
        {"Soldier call airstrike and damages zombies but no his friends", testSoldierCallsAirStrikeWith2ExtraSoldiersByHisSideAndDamages4Zombies},
        {"Soldier with idf calls an airstrike and nothing happen", testSoldierCallsAirStrikeWithIDFButNothingHappen},
        {"Soldier with scout calls an airstrike and nothing happen", testSoldierCallsAirStrikeWithScoutButNothingHappen},
        {"Soldier calls 2 airstrikes too fast", testSoldierCalls2AirStrikeOnlyCallsOne},
        {NULL, NULL},
};