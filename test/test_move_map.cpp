#include <cstdint>
#include "acutest.h"
#include "../src/soldier.h"
#include "../src/walker.h"
#include "../src/map.h"
#include "../src/game_object.h"
#include "../src/scout.h"
#include "../src/weapon.h"
#include "idf.h"

#define UP -1
#define DOWN 1
#define MAP_SIZE_X 10
#define MAP_SIZE_Y 10

//**************************************** Move Down *************************************//

void testMoveSoldierDownAndCheckPositions(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    soldier.move_down();

    GameObject* soldier1 = map.get_object(3, 9);
    GameObject* soldier2 = map.get_object(4, 9);

    GameObject* old_pos1= map.get_object(3, 8);
    GameObject* old_pos2 = map.get_object(4, 8);

    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(soldier2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);

}

void testMoveSoldierDownGoesToBeginningCheckPositions() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, MAP_SIZE_Y - 1);
    map.add_soldier(&soldier, 3, MAP_SIZE_Y - 1);

    soldier.move_down();

    GameObject* soldier1 = map.get_object(3, 0);
    GameObject* soldier2 = map.get_object(4, 0);

    GameObject* old_pos1= map.get_object(3, MAP_SIZE_Y - 1);
    GameObject* old_pos2 = map.get_object(4, MAP_SIZE_Y - 1);

    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(soldier2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);

}


void testNotMoveSoldierDownForCompleteCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(3,8);
    map.add_zombie(&walker, 3, 8);

    soldier.move_down();

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* soldier2 = map.get_object(4, 7);

    GameObject* walker1 = map.get_object(3, 8);
    GameObject* walker2 = map.get_object(4, 8);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Soldier*>(soldier2) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker1) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker2) != nullptr);
}


void testNotMoveSoldierDownForPartialCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(4,8);
    map.add_zombie(&walker, 4, 8);

    soldier.move_down();

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* soldier2 = map.get_object(4, 7);

    GameObject* walker1 = map.get_object(4, 8);
    GameObject* walker2 = map.get_object(5, 8);

    GameObject* null_space1 = map.get_object(3, 8);
    GameObject* null_space2 = map.get_object(5, 7);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Soldier*>(soldier2) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker1) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker2) != nullptr);

    TEST_CHECK(null_space1 == nullptr);
    TEST_CHECK(null_space2 == nullptr);
}

void testNotMoveSoldierDownForPartialCollisionWithZombie2(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(2,8);
    map.add_zombie(&walker, 2, 8);

    soldier.move_down();

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* soldier2 = map.get_object(4, 7);

    GameObject* walker1 = map.get_object(2, 8);
    GameObject* walker2 = map.get_object(3, 8);

    GameObject* null_space1 = map.get_object(2, 7);
    GameObject* null_space2 = map.get_object(4, 8);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Soldier*>(soldier2) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker1) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker2) != nullptr);

    TEST_CHECK(null_space1 == nullptr);
    TEST_CHECK(null_space2 == nullptr);
}

//**************************************** Move UP *************************************//

void testMoveSoldierUpAndCheckPositions(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    soldier.move_up();

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* soldier2 = map.get_object(4, 7);

    GameObject* old_pos1= map.get_object(3, 8);
    GameObject* old_pos2 = map.get_object(4, 8);

    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(soldier2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);

}

void testMoveSoldierUpGoesToEndingCheckPositions() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 0);
    map.add_soldier(&soldier, 3, 0);

    soldier.move_up();

    GameObject* soldier1 = map.get_object(3, MAP_SIZE_Y - 1);
    GameObject* soldier2 = map.get_object(4, MAP_SIZE_Y - 1);

    GameObject* old_pos1= map.get_object(3, 0);
    GameObject* old_pos2 = map.get_object(4, 0);

    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(soldier2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
    TEST_CHECK(old_pos2 == nullptr);

}

void testNotMoveSoldierUpForCompleteCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(3,6);
    map.add_zombie(&walker, 3, 6);

    soldier.move_up();

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* soldier2 = map.get_object(4, 7);

    GameObject* walker1 = map.get_object(3, 6);
    GameObject* walker2 = map.get_object(4, 6);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Soldier*>(soldier2) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker1) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker2) != nullptr);
}


void testNotMoveSoldierUpForPartialCollisionWithZombie(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(4,6);
    map.add_zombie(&walker, 4, 6);

    soldier.move_up();

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* soldier2 = map.get_object(4, 7);

    GameObject* walker1 = map.get_object(4, 6);
    GameObject* walker2 = map.get_object(5, 6);

    GameObject* null_space1 = map.get_object(3, 6);
    GameObject* null_space2 = map.get_object(5, 7);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Soldier*>(soldier2) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker1) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker2) != nullptr);

    TEST_CHECK(null_space1 == nullptr);
    TEST_CHECK(null_space2 == nullptr);
}

void testNotMoveSoldierUpForPartialCollisionWithZombie2(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(2,6);
    map.add_zombie(&walker, 2, 6);

    soldier.move_up();

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* soldier2 = map.get_object(4, 7);

    GameObject* walker1 = map.get_object(2, 6);
    GameObject* walker2 = map.get_object(3, 6);

    GameObject* null_space1 = map.get_object(2, 7);
    GameObject* null_space2 = map.get_object(4, 6);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Soldier*>(soldier2) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker1) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker2) != nullptr);

    TEST_CHECK(null_space1 == nullptr);
    TEST_CHECK(null_space2 == nullptr);
}


//************************************** Move Right ************************************************************

void testMoveSoldierRightAndCheckMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    soldier.move_right();

    GameObject* soldier1 = map.get_object(4, 8);
    GameObject* soldier2 = map.get_object(5, 8);

    GameObject* old_pos1= map.get_object(3, 8);

    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(soldier2 != nullptr);
    TEST_CHECK(old_pos1 == nullptr);
}

void testMoveSoldierRightEndOfMapAndCheckMap() {
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, MAP_SIZE_X - 2, 3);
    map.add_soldier(&soldier, MAP_SIZE_X - 2, 3);

    soldier.move_right();

    GameObject* soldier1 = map.get_object(MAP_SIZE_X - 2, 3);
    GameObject* soldier2 = map.get_object(MAP_SIZE_X - 2, 3);


    TEST_CHECK(soldier1 != nullptr);
    TEST_CHECK(soldier2 != nullptr);
}

void testNotMoveSoldierRightForCollisionWithZombieAndCheckMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 7);
    map.add_soldier(&soldier, 3, 7);

    Walker walker(5,7);
    map.add_zombie(&walker, 5, 7);

    soldier.move_right();

    GameObject* soldier1 = map.get_object(3, 7);
    GameObject* soldier2 = map.get_object(4, 7);

    GameObject* walker1 = map.get_object(5, 7);
    GameObject* walker2 = map.get_object(6, 7);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Soldier*>(soldier2) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker1) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker2) != nullptr);
}


void testMoveSoldierRightWithZombieCloseAndCheckMap(){
    GameMap map(MAP_SIZE_X, MAP_SIZE_Y);
    Weapon* scout = new Scout;

    Soldier soldier(scout, map, 3, 8);
    map.add_soldier(&soldier, 3, 8);

    Walker walker(4,9);
    map.add_zombie(&walker, 4, 9);

    soldier.move_right();

    GameObject* soldier1 = map.get_object(4, 8);
    GameObject* soldier2 = map.get_object(5, 8);

    GameObject* walker1 = map.get_object(4, 9);
    GameObject* walker2 = map.get_object(5, 9);

    // Si casteo a a algo que no es, me tira nullptr
    TEST_CHECK(dynamic_cast<Soldier*>(soldier1) != nullptr);
    TEST_CHECK(dynamic_cast<Soldier*>(soldier2) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker1) != nullptr);
    TEST_CHECK(dynamic_cast<Walker*>(walker2) != nullptr);
}

//*********************************** Move Left ******************************************************8

TEST_LIST = {
        {"Move soldier 1 position down and check Map",testMoveSoldierDownAndCheckPositions},
        {"Move soldier 1 position down goes to beginning and check Map",testMoveSoldierDownGoesToBeginningCheckPositions},
        {"Move down stays in same place for complete collision with walker", testNotMoveSoldierDownForCompleteCollisionWithZombie},
        {"Move down stays in same place for partial collision with walker", testNotMoveSoldierDownForPartialCollisionWithZombie},
        {"Move down stays in same place for partial collision with walker 2", testNotMoveSoldierDownForPartialCollisionWithZombie2},

        {"Move soldier 1 position up and check Map",testMoveSoldierUpAndCheckPositions},
        {"Move soldier 1 position up goes to ending position and check Map", testMoveSoldierUpGoesToEndingCheckPositions},
        {"Move up stays in same place for complete collision with walker", testNotMoveSoldierUpForCompleteCollisionWithZombie},
        {"Move up stays in same place for partial collision with walker", testNotMoveSoldierUpForPartialCollisionWithZombie},
        {"Move up stays in same place for partial collision with walker 2", testNotMoveSoldierUpForPartialCollisionWithZombie2},

        {"Move soldier 1 position right",testMoveSoldierRightAndCheckMap},
        {"Try to move soldier 1 position on limit of map, stays in place",testMoveSoldierRightEndOfMapAndCheckMap},
        {"Move soldier 1 position right not possible for walker",testNotMoveSoldierRightForCollisionWithZombieAndCheckMap},
        {"Move soldier 1 position right close to a zombie", testMoveSoldierRightWithZombieCloseAndCheckMap},
        {NULL, NULL},
};



