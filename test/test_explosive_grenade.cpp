#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/walker.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/idf.h"
#include "game_logic/weapon.h"
#include "game_logic/scout.h"

#define UP -1
#define DOWN 1
#define GRANADE_DAMAGE 40
#define MAP_SIZE_X 20
#define MAP_SIZE_Y 20
/*
 * La granada se lanza 4 casilleros independientemente de la magnitud del mapa
 * En un Mapa de 20 x 20 (como en este caso), el alcance de dano es de 3 casilleros
 */

void testSoldierThrowsExplosiveGrenadeUpAndDamages5Zombies(void) {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 10, 15);
    map.add_soldier(&soldier, 10, 15);

    soldier.set_direction(UP);

    Walker walker1(10,11); // donde cae la granada
    map.add_zombie(&walker1, 10, 11);

    Walker walker2(7,8);
    map.add_zombie(&walker2, 7, 8);

    Walker walker3(13,8);
    map.add_zombie(&walker3, 8, 8);

    Walker walker4(7,14);
    map.add_zombie(&walker4, 7, 14);

    Walker walker5(13,14);
    map.add_zombie(&walker5, 13, 14);

    soldier.throw_explosive_grenade();

    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    std::uint16_t remaining_health4 = walker4.get_health();
    std::uint16_t remaining_health5 = walker5.get_health();

    TEST_CHECK(remaining_health1 < 100);
    TEST_CHECK(remaining_health2 < 100);
    TEST_CHECK(remaining_health3 < 100);
    TEST_CHECK(remaining_health4 < 100);
    TEST_CHECK(remaining_health5 < 100);
}



TEST_LIST = {
        {"Soldier throws granade and damage 5 zombies ", testSoldierThrowsExplosiveGrenadeUpAndDamages5Zombies},
        {NULL, NULL}
};
