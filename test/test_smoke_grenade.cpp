#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/scout.h"

#define UP -1
#define DOWN 1
#define GRANADE_DAMAGE 40
#define MAP_SIZE_X 20
#define MAP_SIZE_Y 20

/*
 * La granada se lanza 4 casilleros independientemente de la magnitud del mapa
 * En un Mapa de 20 x 20 (como en este caso), el alcance de dano es de 3 casilleros
 */

#define DISTANCE_THROWN 4
#define REACH_EXPLOSIVE_DAMAGE 3


void testSoldierThrowsSmokeGrenadeLeftAndDamages5Zombies(void) {

    std::int16_t  x_throwing_place = 15;
    std::int16_t  y_throwing_place = 10;

    std::int16_t  x_explosion = x_throwing_place - DISTANCE_THROWN;
    std::int16_t  y_explosion= y_throwing_place;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(LEFT);

    Infected walker1(x_explosion,y_explosion, map); // donde cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Infected walker2(x_limit_damage_left,y_limit_damage_up, map);
    map.add_zombie(&walker2, x_limit_damage_left,y_limit_damage_up);

    Infected walker3(x_limit_damage_right,y_limit_damage_up, map);
    map.add_zombie(&walker3, x_limit_damage_right,y_limit_damage_up);

    Infected walker4(x_limit_damage_left,y_limit_damage_down,map);
    map.add_zombie(&walker4, x_limit_damage_left,y_limit_damage_down);

    Infected walker5(x_limit_damage_right,y_limit_damage_down, map);
    map.add_zombie(&walker5, x_limit_damage_right,y_limit_damage_down);

    soldier.throw_smoke_grenade(100);
    soldier.update(200);

    std::uint16_t remaining_health1 = walker1.get_health();
    std::uint16_t remaining_health2 = walker2.get_health();
    std::uint16_t remaining_health3 = walker3.get_health();
    std::uint16_t remaining_health4 = walker4.get_health();
    std::uint16_t remaining_health5 = walker5.get_health();

    TEST_CHECK(remaining_health1 == 100);
    TEST_CHECK(remaining_health2 == 100);
    TEST_CHECK(remaining_health3 == 100);
    TEST_CHECK(remaining_health4 == 100);
    TEST_CHECK(remaining_health5 == 100);

    Stunned* zombie_state1 = dynamic_cast<Stunned*>(walker1.get_state());
    Stunned* zombie_state2 = dynamic_cast<Stunned*>(walker2.get_state());
    Stunned* zombie_state3 = dynamic_cast<Stunned*>(walker3.get_state());
    Stunned* zombie_state4 = dynamic_cast<Stunned*>(walker4.get_state());
    Stunned* zombie_state5 = dynamic_cast<Stunned*>(walker5.get_state());

    TEST_CHECK(zombie_state1 != nullptr);
    TEST_CHECK(zombie_state2 != nullptr);
    TEST_CHECK(zombie_state3 != nullptr);
    TEST_CHECK(zombie_state4 != nullptr);
    TEST_CHECK(zombie_state5 != nullptr);
}

void testSoldierThrowsSmokeGrenadeLeftAndDamages1Zombies(void) {

    std::int16_t  x_throwing_place = 15;
    std::int16_t  y_throwing_place = 10;

    std::int16_t  x_explosion = x_throwing_place - DISTANCE_THROWN;
    std::int16_t  y_explosion= y_throwing_place;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(LEFT);

    Infected walker1(x_explosion,y_explosion, map); // donde cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Infected walker2(x_limit_damage_left - 1,y_limit_damage_up, map); //falla
    map.add_zombie(&walker2, x_limit_damage_left - 2,y_limit_damage_up);

    Infected walker3(x_limit_damage_right + 1,y_limit_damage_up, map);
    map.add_zombie(&walker3, x_limit_damage_right + 1,y_limit_damage_up);

    Infected walker4(x_limit_damage_left - 1,y_limit_damage_down, map); // falla
    map.add_zombie(&walker4, x_limit_damage_left - 1,y_limit_damage_down);

    Infected walker5(x_limit_damage_right + 1,y_limit_damage_down, map);
    map.add_zombie(&walker5, x_limit_damage_right + 1,y_limit_damage_down);

    soldier.throw_smoke_grenade(100);
    soldier.update(200);

    Stunned* zombie_state1 = dynamic_cast<Stunned*>(walker1.get_state());
    Stunned* zombie_state2 = dynamic_cast<Stunned*>(walker2.get_state());
    Stunned* zombie_state3 = dynamic_cast<Stunned*>(walker3.get_state());
    Stunned* zombie_state4 = dynamic_cast<Stunned*>(walker4.get_state());
    Stunned* zombie_state5 = dynamic_cast<Stunned*>(walker5.get_state());

    TEST_CHECK(zombie_state1 != nullptr);
    TEST_CHECK(zombie_state2 == nullptr);
    TEST_CHECK(zombie_state3 == nullptr);
    TEST_CHECK(zombie_state4 == nullptr);
    TEST_CHECK(zombie_state5 == nullptr);
}

void testSoldierThrowsSmokeGrenadeLeftAndDamages1Zombies2(void) {

    /*
     * los muevo arriba/abajo para que los 4 que estaban
     * en los limites, no sufran dano
     */

    std::int16_t  x_throwing_place = 15;
    std::int16_t  y_throwing_place = 10;

    std::int16_t  x_explosion = x_throwing_place - DISTANCE_THROWN;
    std::int16_t  y_explosion= y_throwing_place;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(LEFT);

    Infected walker1(x_explosion,y_explosion, map); // donde cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Infected walker2(x_limit_damage_left,y_limit_damage_up - 1, map);
    map.add_zombie(&walker2, x_limit_damage_left,y_limit_damage_up - 1);

    Infected walker3(x_limit_damage_right,y_limit_damage_up - 1, map);
    map.add_zombie(&walker3, x_limit_damage_right,y_limit_damage_up - 1);

    Infected walker4(x_limit_damage_left,y_limit_damage_down + 1, map);
    map.add_zombie(&walker4, x_limit_damage_left,y_limit_damage_down + 1);

    Infected walker5(x_limit_damage_right,y_limit_damage_down + 1, map);
    map.add_zombie(&walker5, x_limit_damage_right,y_limit_damage_down + 1);

    soldier.throw_smoke_grenade(100);
    soldier.update(200);

    Stunned* zombie_state1 = dynamic_cast<Stunned*>(walker1.get_state());
    Stunned* zombie_state2 = dynamic_cast<Stunned*>(walker2.get_state());
    Stunned* zombie_state3 = dynamic_cast<Stunned*>(walker3.get_state());
    Stunned* zombie_state4 = dynamic_cast<Stunned*>(walker4.get_state());
    Stunned* zombie_state5 = dynamic_cast<Stunned*>(walker5.get_state());

    TEST_CHECK(zombie_state1 != nullptr);
    TEST_CHECK(zombie_state2 == nullptr);
    TEST_CHECK(zombie_state3 == nullptr);
    TEST_CHECK(zombie_state4 == nullptr);
    TEST_CHECK(zombie_state5 == nullptr);
}


void testSoldierThrowsSmokeGrenadeToOtherSoldier(void) {

    std::int16_t  x_throwing_place = 15;
    std::int16_t  y_throwing_place = 10;

    std::int16_t  x_explosion = x_throwing_place - DISTANCE_THROWN;
    std::int16_t  y_explosion= y_throwing_place;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout1 = new Scout(0, 0);
    Weapon* scout2 = new Scout(0, 0);

    Soldier soldier1(scout1, map, x_throwing_place, y_throwing_place);
    map.add_soldier(&soldier1, x_throwing_place, y_throwing_place);

    Soldier soldier2(scout2, map, x_explosion,y_explosion); // donde cae la granada
    map.add_soldier(&soldier2, x_explosion,y_explosion);

    soldier1.set_direction(LEFT);
    soldier1.throw_smoke_grenade(100);
    soldier1.update(200);

    Idle* soldier2_state = dynamic_cast<Idle*>(soldier2.get_state());

    TEST_CHECK(soldier2_state != nullptr);
}

void testSoldierThrowsSmokeGrenadeRightAndDamages5Zombies(void) {

    std::int16_t  x_throwing_place = 10;
    std::int16_t  y_throwing_place = 5;

    std::int16_t  x_explosion = x_throwing_place + DISTANCE_THROWN;
    std::int16_t  y_explosion= y_throwing_place;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(RIGHT);

    Infected walker1(x_explosion,y_explosion, map); // donde cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Infected walker2(x_limit_damage_left,y_limit_damage_up, map);
    map.add_zombie(&walker2, x_limit_damage_left,y_limit_damage_up);

    Infected walker3(x_limit_damage_right,y_limit_damage_up, map);
    map.add_zombie(&walker3, x_limit_damage_right,y_limit_damage_up);

    Infected walker4(x_limit_damage_left,y_limit_damage_down, map);
    map.add_zombie(&walker4, x_limit_damage_left,y_limit_damage_down);

    Infected walker5(x_limit_damage_right,y_limit_damage_down, map);
    map.add_zombie(&walker5, x_limit_damage_right,y_limit_damage_down);

    soldier.throw_smoke_grenade(100);
    soldier.update(200);

    Stunned* zombie_state1 = dynamic_cast<Stunned*>(walker1.get_state());
    Stunned* zombie_state2 = dynamic_cast<Stunned*>(walker2.get_state());
    Stunned* zombie_state3 = dynamic_cast<Stunned*>(walker3.get_state());
    Stunned* zombie_state4 = dynamic_cast<Stunned*>(walker4.get_state());
    Stunned* zombie_state5 = dynamic_cast<Stunned*>(walker5.get_state());

    TEST_CHECK(zombie_state1 != nullptr);
    TEST_CHECK(zombie_state2 != nullptr);
    TEST_CHECK(zombie_state3 != nullptr);
    TEST_CHECK(zombie_state4 != nullptr);
    TEST_CHECK(zombie_state5 != nullptr);
}


TEST_LIST = {
        {"Soldier throws granade up and damage 5 zombies", testSoldierThrowsSmokeGrenadeLeftAndDamages5Zombies},
        {"Soldier throws granade up and damage 1 zombie", testSoldierThrowsSmokeGrenadeLeftAndDamages1Zombies},
        {"Soldier throws granade up and damage 1 zombie", testSoldierThrowsSmokeGrenadeLeftAndDamages1Zombies2},
        {"Soldier throws granade up and damages other soldier", testSoldierThrowsSmokeGrenadeToOtherSoldier},
        {"Soldier throws granade Down and damage 5 zombies",testSoldierThrowsSmokeGrenadeRightAndDamages5Zombies},
        {NULL, NULL}
};
