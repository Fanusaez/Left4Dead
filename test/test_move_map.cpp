#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/infected.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/scout.h"
#include "game_logic/weapons/weapon.h"
#include "game_logic/weapons/idf.h"

#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10
#define MOVEMENTS_PER_CELL 2
#define MOV_NEEDED_TO_WALK_ALL_CELL 1
#define SOLDIER_SPEED 1
//**************************************** Move Down *************************************//

void testMoveSoldierDownAndCheckPositions(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 8, 0);
    map.add_soldier(&soldier, 3, 8);

    for (float i = 0; i < MOVEMENTS_PER_CELL; i++){
        soldier.move_down();
    }

    GameObject* soldier1 = map.get_object(3, 9);
    GameObject* old_pos1= map.get_object(3, 8);

    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);

}

void testMoveSoldierDownAtTheEndStaysInPlace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, (MAP_SIZE_Y - 1), 0);
    map.add_soldier(&soldier, 3, MAP_SIZE_Y - 1);

    for (float i = 0; i < MOVEMENTS_PER_CELL; i++){
        soldier.move_down();
    }

    GameObject* soldier1= map.get_object(3, MAP_SIZE_Y - 1);

    TEST_CHECK(soldier1 != nullptr);
}


void testNotMoveSoldierDownForCompleteCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 7, 0);
    map.add_soldier(&soldier, 3, 7);

    Infected walker(3,  8,0,  map);
    map.add_zombie(&walker, 3, 8);

    for (float i = 0; i < MOVEMENTS_PER_CELL; i++){
        soldier.move_down();
    }

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* walker1 = map.get_object(3, 8);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Infected*>(walker1) != nullptr);
}


void testNotMoveSoldierDownForPartialCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 4, 7, 0);
    map.add_soldier(&soldier, 4, 7);

    soldier.move_right();

    Infected walker(4, 8, 0, map);
    map.add_zombie(&walker, 4, 8);

    for (float i = 0; i < 30; i++){
        soldier.move_down();
    }

    GameObject* soldier1 = map.get_object(4, 7);
    GameObject* walker1 = map.get_object(4, 8);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Infected*>(walker1) != nullptr);

}

void testNotMoveSoldierDownForPartialCollisionWithZombie2(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 7, 0);
    map.add_soldier(&soldier, 3, 7);

    soldier.move_left();

    Infected walker(2, 8, 0, map);
    map.add_zombie(&walker, 2, 8);

    for (float i = 0; i < 30; i++){
        soldier.move_down();
    }

    GameObject* soldier1 = map.get_object(2, 7);
    GameObject* soldier_old = map.get_object(3, 7);

    GameObject* walker1 = map.get_object(2, 8);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Soldier*>(soldier_old) == nullptr);
    TEST_CHECK(dynamic_cast<Infected*>(walker1) != nullptr);
}

//**************************************** Move UP *************************************//

void testMoveSoldierUpAndCheckPositions(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 8, 0);
    map.add_soldier(&soldier, 3, 8);

    for (float i = 0; i < 1; i++){
        soldier.move_up();
    }

    GameObject* soldier1 = map.get_object(3, 7);

    GameObject* old_pos1= map.get_object(3, 8);

    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);

}

void testMoveSoldierUpAtTheBeginningStaysInPlace() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 0, 0);
    map.add_soldier(&soldier, 3, 0);

    for (float i = 0; i < 3; i++){
        soldier.move_up();
    }

    GameObject* soldier1 = map.get_object(3, 0);

    TEST_CHECK(soldier1 != nullptr);

}

void testNotMoveSoldierUpForCompleteCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3 , 7, 0);
    map.add_soldier(&soldier, 3, 7);

    Infected walker(3, 6, 0, map);
    map.add_zombie(&walker, 3, 6);

    for (float i = 0; i < MOVEMENTS_PER_CELL + 10; i++){
        soldier.move_up();
    }

    GameObject* soldier1 = map.get_object(3, 7);

    GameObject* walker1 = map.get_object(3, 6);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Infected*>(walker1) != nullptr);
}


void testNotMoveSoldierUpForPartialCollisionWithZombie() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon *scout = new Scout(0, 0);

    Soldier soldier(scout, map, 4, 7, 0);
    map.add_soldier(&soldier, 4, 7);

    soldier.move_right();

    Infected walker(4,  6,0,  map);
    map.add_zombie(&walker, 4, 6);

    for (float i = 0; i < MOVEMENTS_PER_CELL; i++) {
        soldier.move_up();
    }

    GameObject *soldier1 = map.get_object(4, 7);

    GameObject *walker1 = map.get_object(4, 6);


    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier *>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Infected *>(walker1) != nullptr);

}

void testNotMoveSoldierUpForPartialCollisionWithZombie2(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 7, 0);
    map.add_soldier(&soldier, 3, 7);

    soldier.move_left();

    Infected walker(2, 6, 0, map);
    map.add_zombie(&walker, 2, 6);

    for (float i = 0; i < 20; i++){
        soldier.move_up();
    }

    GameObject* soldier1 = map.get_object(2, 7);
    GameObject* soldier_old = map.get_object(3, 7);

    GameObject* walker1 = map.get_object(2, 6);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Infected*>(walker1) != nullptr);

    TEST_CHECK(soldier_old == nullptr);
}


//************************************** Move Right ************************************************************

void testMoveSoldierRightAndCheckMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 8, 0);
    map.add_soldier(&soldier, 3, 8);

    /*
     * Deberia alcanzar con 4, al parecer hay porblemas en el if (floor(x) == floor(x + speed)))
     */
    for (float i = 0; i <  MOVEMENTS_PER_CELL; i++){
        soldier.move_right();
    }

    GameObject* soldier1 = map.get_object(4, 8);
    GameObject* old_pos1= map.get_object(3, 8);

    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
}

void testMoveSoldierRightEndOfMapAndCheckMap() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, (MAP_SIZE_X - 2), 3, 0);
    map.add_soldier(&soldier, MAP_SIZE_X - 2, 3);

    for (float i = 0; i < 30; i++){
        soldier.move_right();
    }

    GameObject* soldier1 = map.get_object(MAP_SIZE_X - 1, 3);
    GameObject* soldier1_old = map.get_object(MAP_SIZE_X - 2, 3);

    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(soldier1_old == nullptr);
}

void testNotMoveSoldierRightForCollisionWithZombieAndCheckMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 7, 0);
    map.add_soldier(&soldier, 3, 7);

    Infected walker(4, 7, 0, map);
    map.add_zombie(&walker, 4, 7);

    for (float i = 0; i <  MOVEMENTS_PER_CELL + 5; i++){
        soldier.move_right();
    }

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* walker1 = map.get_object(4, 7);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Infected*>(walker1) != nullptr);
}


void testMoveSoldierRightWithZombieCloseAndCheckMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 8, 0);
    map.add_soldier(&soldier, 3, 8);

    Infected walker(4, 9, 0, map);
    map.add_zombie(&walker, 4, 9);

    for (float i = 0; i < MOVEMENTS_PER_CELL; i++){
        soldier.move_right();
    }

    GameObject* soldier1 = map.get_object(4, 8);
    GameObject* walker1 = map.get_object(4, 9);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Infected*>(walker1) != nullptr);
}

//*********************************** Move Left ******************************************************8

void testMoveSoldierLeftAndCheckMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 8, 0);
    map.add_soldier(&soldier, 3, 8);

    for (float i = 0; i < 1; i++){
        soldier.move_left();
    }

    GameObject* soldier1 = map.get_object(2, 8);
    GameObject* old_pos1= map.get_object(3, 8);

    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
}

void testMoveSoldierLeftBeginningOfMapAndCheckMap() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 0, 3, 0);
    map.add_soldier(&soldier, 0, 3);

    for (float i = 0; i < 3; i++){
        soldier.move_left();
    }

    GameObject* soldier1 = map.get_object(0, 3);

    TEST_CHECK(soldier1 != nullptr);

}

void testNotMoveSoldierLeftForCollisionWithZombieAndCheckMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 3, 7, 0);
    map.add_soldier(&soldier, 3, 7);

    Infected walker(2, 7, 0, map);
    map.add_zombie(&walker, 2, 7);

    for (float i = 0; i < 3; i++){
        soldier.move_left();
    }

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* walker1 = map.get_object(2, 7);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Infected*>(walker1) != nullptr);
}


void testMoveSoldierLeftWithZombieCloseAndCheckMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y, 0);
    Weapon* scout = new Scout(0, 0);

    Soldier soldier(scout, map, 6, 8, 0);
    map.add_soldier(&soldier, 6, 8);

    Infected walker(4, 9, 0, map);
    map.add_zombie(&walker, 4, 9);

    for (float i = 0; i < MOVEMENTS_PER_CELL; i++){
        soldier.move_left();
    }

    GameObject* soldier1 = map.get_object(5, 8);

    GameObject* walker1 = map.get_object(4, 9);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Infected*>(walker1) != nullptr);
}




TEST_LIST = {
        {"Move soldier 1 position down and check Map",testMoveSoldierDownAndCheckPositions},
        {"Move soldier 1 position at the end stays in place and check Map",testMoveSoldierDownAtTheEndStaysInPlace},
        {"Move down stays in same place for complete collision with walker", testNotMoveSoldierDownForCompleteCollisionWithZombie},
        {"Move down stays in same place for partial collision with walker", testNotMoveSoldierDownForPartialCollisionWithZombie},
        {"Move down stays in same place for partial collision with walker 2", testNotMoveSoldierDownForPartialCollisionWithZombie2},

        {"Move soldier 1 position up and check Map",testMoveSoldierUpAndCheckPositions},
        {"Move soldier 1 position up at the beginning stays in place check Map", testMoveSoldierUpAtTheBeginningStaysInPlace},
        {"Move up stays in same place for complete collision with walker", testNotMoveSoldierUpForCompleteCollisionWithZombie},
        {"Move up stays in same place for partial collision with walker", testNotMoveSoldierUpForPartialCollisionWithZombie},
        {"Move up stays in same place for partial collision with walker 2", testNotMoveSoldierUpForPartialCollisionWithZombie2},

        {"Move soldier 1 position right",testMoveSoldierRightAndCheckMap},
        {"Try to move soldier 1 position on limit of map, stays in place",testMoveSoldierRightEndOfMapAndCheckMap},
        {"Move soldier 1 position right not possible for walker",testNotMoveSoldierRightForCollisionWithZombieAndCheckMap},
        {"Move soldier 1 position right close to a zombie", testMoveSoldierRightWithZombieCloseAndCheckMap},

        {"Move soldier 1 position Left",testMoveSoldierLeftAndCheckMap},
        {"Move soldier 1 position on limit of map",testMoveSoldierLeftBeginningOfMapAndCheckMap},
        {"Move soldier 1 position Left not possible for walker",testNotMoveSoldierLeftForCollisionWithZombieAndCheckMap},
        {"Move soldier 1 position Left close to a zombie", testMoveSoldierLeftWithZombieCloseAndCheckMap},

        {NULL, NULL},
};



