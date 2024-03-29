#include <cstdint>
#include "../acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/scout.h"

#define UP -1
#define DOWN 1
#define GRANADE_DAMAGE 50
#define MAP_SIZE_X 150
#define MAP_SIZE_Y 150


#define DISTANCE_THROWN 40
#define REACH_EXPLOSIVE_DAMAGE 8
#define TIME_PRESSED_MAX_REACH 2000

void testSoldierThrowsExplosiveGrenadeLeftAndDamages5Zombies(void) {

    std::int16_t  x_throwing_place = 80;
    std::int16_t  y_throwing_place = 75;

    std::int16_t  x_explosion = x_throwing_place - DISTANCE_THROWN;
    std::int16_t  y_explosion= y_throwing_place;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place, 0);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(LEFT);

    Infected walker1(x_explosion,y_explosion, 0, map, 0, 0); // donde0, cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Infected walker2(x_limit_damage_left,y_limit_damage_up, 0,map, 0, 0);
    map.add_zombie(&walker2, x_limit_damage_left,y_limit_damage_up);

    Infected walker3(x_limit_damage_right,y_limit_damage_up,0, map, 0, 0);
    map.add_zombie(&walker3, x_limit_damage_right,y_limit_damage_up);

    Infected walker4(x_limit_damage_left, y_limit_damage_down, 0, map, 0, 0);
    map.add_zombie(&walker4, x_limit_damage_left,y_limit_damage_down);

    Infected walker5(x_limit_damage_right,y_limit_damage_down, 0, map, 0, 0);
    map.add_zombie(&walker5, x_limit_damage_right,y_limit_damage_down);

    soldier.throw_explosive_grenade(100, TIME_PRESSED_MAX_REACH);
    soldier.update(200);

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
     map.empty_vectors();
}

void testSoldierThrowsExplosiveGrenadeLeftAndDamages1Zombies(void) {

    std::int16_t  x_throwing_place = 80;
    std::int16_t  y_throwing_place = 75;

    std::int16_t  x_explosion = x_throwing_place - DISTANCE_THROWN;
    std::int16_t  y_explosion= y_throwing_place;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place, 0);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(LEFT);

    Infected walker1(x_explosion, y_explosion, 0, map, 0, 0); // donde0, cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Infected walker2(x_limit_damage_left - 1, y_limit_damage_up, 0, map, 0, 0);
    map.add_zombie(&walker2, x_limit_damage_left - 1,y_limit_damage_up);

    Infected walker3(x_limit_damage_right + 1, y_limit_damage_up, 0, map, 0, 0);
    map.add_zombie(&walker3, x_limit_damage_right + 1 ,y_limit_damage_up);

    Infected walker4(x_limit_damage_left, y_limit_damage_down + 1, 0, map, 0, 0);
    map.add_zombie(&walker4, x_limit_damage_left,y_limit_damage_down + 1);

    Infected walker5(x_limit_damage_right, y_limit_damage_down + 1, 0, map, 0, 0);
    map.add_zombie(&walker5, x_limit_damage_right,y_limit_damage_down + 1);

    soldier.throw_explosive_grenade(100, TIME_PRESSED_MAX_REACH);
    soldier.update(200);

    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    std::uint16_t remaining_health4 = walker4.get_health();
    std::uint16_t remaining_health5 = walker5.get_health();

    TEST_CHECK(remaining_health1 < 100);
    TEST_CHECK(remaining_health2 == 100);
    TEST_CHECK(remaining_health3 == 100);
    TEST_CHECK(remaining_health4 == 100);
    TEST_CHECK(remaining_health5 == 100);
     map.empty_vectors();
}

void testSoldierThrowsExplosiveGrenadeLeftAndDamages1Zombies2(void) {

    /*
     * los muevo arriba/abajo para que los 4 que estaban
     * en los limites, no sufran dano
     */

    std::int16_t  x_throwing_place = 80;
    std::int16_t  y_throwing_place = 75;

    std::int16_t  x_explosion = x_throwing_place - DISTANCE_THROWN;
    std::int16_t  y_explosion= y_throwing_place;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place, 0);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(LEFT);

    Infected walker1(x_explosion,y_explosion, 0, map, 0, 0); // donde0, cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Infected walker2(x_limit_damage_left,y_limit_damage_up - 1, 0, map, 0, 0);
    map.add_zombie(&walker2, x_limit_damage_left,y_limit_damage_up - 1);

    Infected walker3(x_limit_damage_right,y_limit_damage_up - 1, 0, map, 0, 0);
    map.add_zombie(&walker3, x_limit_damage_right,y_limit_damage_up - 1);

    Infected walker4(x_limit_damage_left,y_limit_damage_down + 1, 0, map, 0, 0);
    map.add_zombie(&walker4, x_limit_damage_left,y_limit_damage_down + 1);

    Infected walker5(x_limit_damage_right,y_limit_damage_down + 1, 0, map, 0, 0);
    map.add_zombie(&walker5, x_limit_damage_right,y_limit_damage_down + 1);

    soldier.throw_explosive_grenade(100, TIME_PRESSED_MAX_REACH);
    soldier.update(200);

    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    std::uint16_t remaining_health4 = walker4.get_health();
    std::uint16_t remaining_health5 = walker5.get_health();

    TEST_CHECK(remaining_health1 < 100);
    TEST_CHECK(remaining_health2 == 100);
    TEST_CHECK(remaining_health3 == 100);
    TEST_CHECK(remaining_health4 == 100);
    TEST_CHECK(remaining_health5 == 100);
     map.empty_vectors();
}


void testSoldierThrowsExplosiveGrenadeToOtherSoldier(void) {

    std::int16_t  x_throwing_place = 80;
    std::int16_t  y_throwing_place = 75;

    std::int16_t  x_explosion = x_throwing_place - DISTANCE_THROWN;
    std::int16_t  y_explosion= y_throwing_place;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout1 = new Scout(0, 0);
    Weapon* scout2 = new Scout(0, 0);

    Soldier soldier1(scout1, map, x_throwing_place, y_throwing_place, 0);
    map.add_soldier(&soldier1, x_throwing_place, y_throwing_place);

    Soldier soldier2(scout2, map, x_explosion,y_explosion, 0); // donde cae la granada
    map.add_soldier(&soldier2, x_explosion,y_explosion);

    soldier1.set_direction(LEFT);
    soldier1.throw_explosive_grenade(100, TIME_PRESSED_MAX_REACH);
    soldier1.update(200);

    std::int16_t remaining_health1 = soldier1.get_health();
    std::int16_t remaining_health2 = soldier2.get_health();

    TEST_CHECK(remaining_health1 == 100);
    TEST_CHECK(remaining_health2 != 100);
     map.empty_vectors();
}

void testSoldierThrowsExplosiveGrenadeRightAndDamages5Zombies(void) {

    std::int16_t  x_throwing_place = 80;
    std::int16_t  y_throwing_place = 75;

    std::int16_t  x_explosion = x_throwing_place + DISTANCE_THROWN;
    std::int16_t  y_explosion= y_throwing_place;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place, 0);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(RIGHT);

    Infected walker1(x_explosion,y_explosion, 0, map, 0, 0); // donde0, cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Infected walker2(x_limit_damage_left,y_limit_damage_up, 0,map, 0, 0);
    map.add_zombie(&walker2, x_limit_damage_left,y_limit_damage_up);

    Infected walker3(x_limit_damage_right, y_limit_damage_up, 0, map, 0, 0);
    map.add_zombie(&walker3, x_limit_damage_right, y_limit_damage_up);

    Infected walker4(x_limit_damage_left,y_limit_damage_down, 0,map, 0, 0);
    map.add_zombie(&walker4, x_limit_damage_left,y_limit_damage_down);

    Infected walker5(x_limit_damage_right, y_limit_damage_down, 0, map, 0, 0);
    map.add_zombie(&walker5, x_limit_damage_right,y_limit_damage_down);

    soldier.throw_explosive_grenade(100, TIME_PRESSED_MAX_REACH);
    soldier.update(200);

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
     map.empty_vectors();
}


TEST_LIST = {
        {"Soldier throws granade up and damage 5 zombies", testSoldierThrowsExplosiveGrenadeLeftAndDamages5Zombies},
        {"Soldier throws granade up and damage 1 zombie", testSoldierThrowsExplosiveGrenadeLeftAndDamages1Zombies},
        {"Soldier throws granade up and damage 1 zombie", testSoldierThrowsExplosiveGrenadeLeftAndDamages1Zombies2},
        {"Soldier throws granade up and damages other soldier", testSoldierThrowsExplosiveGrenadeToOtherSoldier},
        {"Soldier throws granade Down and damage 5 zombies",testSoldierThrowsExplosiveGrenadeRightAndDamages5Zombies},
        {NULL, NULL}
};
