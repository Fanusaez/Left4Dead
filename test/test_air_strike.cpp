#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/p90.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/scout.h"

#define UP -1
#define DOWN 1
#define AIR_DAMAGE 40
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

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* p90 = new P90;

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

TEST_LIST = {
        {"Soldier with p90 calls an airstrike and damages 4 zombies", testSoldierCallsAirStrikeAndDamages4Zombies},
        {NULL, NULL},
};