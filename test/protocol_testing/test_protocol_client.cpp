#include "../acutest.h"
#include <vector>
#include <string>

#include "client/client_serializer.h"
#include "common/game_mode.h"
#include "common/soldier_type.h"
#include "common/move_type.h"
#include "common/instructions_type.h"

/*----------------------Game message--------------------*/

void testMovingSoldier(void)
{
    ClientSerializer client_serializer;
    MoveType move_type = UP;
    std::vector<char> buffer = client_serializer.serialize_move(move_type);
    //- mode: 0x07 <code>: 0x00 RIGHT
    //                     0x01 LEFT
    //                     0x02 UP
    //                     0x03 DOWN
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == MOVE);
    TEST_CHECK(buffer.at(1) == UP);
}

void testReloadingGun(void)
{
    ClientSerializer client_serializer;
    std::vector<char> buffer = client_serializer.serialize_reloading();
    //- reloading: 0x08
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == RELOAD);
}

void testShootingGun(void){
    ClientSerializer client_serializer;
    std::vector<char> buffer = client_serializer.serialize_shooting();
    //- shooting: 0x09
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == SHOOT);
}

void testThrowingGrenade(void){
    ClientSerializer client_serializer;
    std::vector<char> buffer = client_serializer.serialize_throw_grenede(2);
    //- shooting: 0x09
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == GRENADE);
    TEST_CHECK(buffer.at(1) == 2);
}

TEST_LIST = {
    {"Testing serialization: move soldier", testMovingSoldier},
    {"Testing serialization: reloading gun", testReloadingGun},
    {"Testing serialization: shooting gun", testShootingGun},
    {"Testing serialization: shooting gun", testThrowingGrenade},
    {NULL, NULL}};