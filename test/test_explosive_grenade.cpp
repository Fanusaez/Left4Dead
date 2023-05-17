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

#define DISTANCE_THROWN 4
#define REACH_EXPLOSIVE_DAMAGE 3


void testSoldierThrowsExplosiveGrenadeUpAndDamages5Zombies(void) {

    std::int16_t  x_throwing_place = 10;
    std::int16_t  y_throwing_place = 15;

    std::int16_t  x_explosion = x_throwing_place;
    std::int16_t  y_explosion= y_throwing_place - DISTANCE_THROWN;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(UP);

    Walker walker1(x_explosion,y_explosion); // donde cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Walker walker2(x_limit_damage_left,y_limit_damage_up);
    map.add_zombie(&walker2, x_limit_damage_left,y_limit_damage_up);

    Walker walker3(x_limit_damage_right,y_limit_damage_up);
    map.add_zombie(&walker3, x_limit_damage_right,y_limit_damage_up);

    Walker walker4(x_limit_damage_left,y_limit_damage_down);
    map.add_zombie(&walker4, x_limit_damage_left,y_limit_damage_down);

    Walker walker5(x_limit_damage_right,y_limit_damage_down);
    map.add_zombie(&walker5, x_limit_damage_right,y_limit_damage_down);

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

void testSoldierThrowsExplosiveGrenadeUpAndDamages1Zombies(void) {

    /*
     * los muevo a la izquierda/derecha para que los 4 que estaban
     * en los limites, no sufran dano.
     * Acordarse que donde se crea el objeto, tiene una posicion extra en x lado derecho para simular las colisiones
     * debido a esto, si el zombie esta completamente adentro (dos posiciones en zona de dano de granada)
     * se le va a aplicar un damage doble. Esto se podria evitar (creo) con un poco mas de logica en map,
     * teniendo un vector de los zombies en el mapa y preguntrle a uno por uno si esta en el rango de damage. ver despues
     */

    std::int16_t  x_throwing_place = 10;
    std::int16_t  y_throwing_place = 15;

    std::int16_t  x_explosion = x_throwing_place;
    std::int16_t  y_explosion= y_throwing_place - DISTANCE_THROWN;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(UP);

    Walker walker1(x_explosion,y_explosion); // donde cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Walker walker2(x_limit_damage_left - 2,y_limit_damage_up); //falla
    map.add_zombie(&walker2, x_limit_damage_left - 2,y_limit_damage_up);

    Walker walker3(x_limit_damage_right + 1,y_limit_damage_up);
    map.add_zombie(&walker3, x_limit_damage_right + 1,y_limit_damage_up);

    Walker walker4(x_limit_damage_left - 2,y_limit_damage_down); // falla
    map.add_zombie(&walker4, x_limit_damage_left - 2,y_limit_damage_down);

    Walker walker5(x_limit_damage_right + 1,y_limit_damage_down);
    map.add_zombie(&walker5, x_limit_damage_right + 1,y_limit_damage_down);

    soldier.throw_explosive_grenade();

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
}

void testSoldierThrowsExplosiveGrenadeUpAndDamages1Zombies2(void) {

    /*
     * los muevo arriba/abajo para que los 4 que estaban
     * en los limites, no sufran dano
     */

    std::int16_t  x_throwing_place = 10;
    std::int16_t  y_throwing_place = 15;

    std::int16_t  x_explosion = x_throwing_place;
    std::int16_t  y_explosion= y_throwing_place - DISTANCE_THROWN;

    std::int16_t  x_limit_damage_left = x_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  x_limit_damage_right = x_explosion + REACH_EXPLOSIVE_DAMAGE;

    std::int16_t  y_limit_damage_up = y_explosion - REACH_EXPLOSIVE_DAMAGE;
    std::int16_t  y_limit_damage_down = y_explosion + REACH_EXPLOSIVE_DAMAGE;

    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, x_throwing_place, y_throwing_place);
    map.add_soldier(&soldier, x_throwing_place, y_throwing_place);

    soldier.set_direction(UP);

    Walker walker1(x_explosion,y_explosion); // donde cae la granada
    map.add_zombie(&walker1, x_explosion,y_explosion);

    Walker walker2(x_limit_damage_left,y_limit_damage_up - 1);
    map.add_zombie(&walker2, x_limit_damage_left,y_limit_damage_up - 1);

    Walker walker3(x_limit_damage_right,y_limit_damage_up - 1);
    map.add_zombie(&walker3, x_limit_damage_right,y_limit_damage_up - 1);

    Walker walker4(x_limit_damage_left,y_limit_damage_down + 1);
    map.add_zombie(&walker4, x_limit_damage_left,y_limit_damage_down + 1);

    Walker walker5(x_limit_damage_right,y_limit_damage_down + 1);
    map.add_zombie(&walker5, x_limit_damage_right,y_limit_damage_down + 1);

    soldier.throw_explosive_grenade();

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
}


TEST_LIST = {
        {"Soldier throws granade and damage 5 zombies", testSoldierThrowsExplosiveGrenadeUpAndDamages5Zombies},
        {"Soldier throws granade and damage 1 zombie", testSoldierThrowsExplosiveGrenadeUpAndDamages1Zombies},
        {"Soldier throws granade and damage 1 zombie", testSoldierThrowsExplosiveGrenadeUpAndDamages1Zombies2},
        {NULL, NULL}
};
