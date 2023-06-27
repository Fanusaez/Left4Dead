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
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == MOVE);
    TEST_CHECK(buffer.at(1) == UP);
}

void testReloadingGun(void)
{
    ClientSerializer client_serializer;
    std::vector<char> buffer = client_serializer.serialize_reloading();
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == RELOAD);
}

void testShootingGun(void){
    ClientSerializer client_serializer;
    std::vector<char> buffer = client_serializer.serialize_shooting();
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == SHOOT);
}

void testThrowingGrenade(void){
    ClientSerializer client_serializer;
    std::vector<char> buffer = client_serializer.serialize_throw_explosive_grenede(2);
    //- shooting: 0x09
    TEST_CHECK(buffer.size() == 5);
    TEST_CHECK(buffer.at(0) == THROW_EXPLOSIVE_GRENADE);
    TEST_CHECK(buffer.at(1) == 0);
    TEST_CHECK(buffer.at(2) == 0);
    TEST_CHECK(buffer.at(3) == 0);
    TEST_CHECK(buffer.at(4) == 2);
}

TEST_LIST = {
    {"Testing serialization: move soldier", testMovingSoldier},
    {"Testing serialization: reloading gun", testReloadingGun},
    {"Testing serialization: shooting gun", testShootingGun},
    {"Testing serialization: throwing grenade ", testThrowingGrenade},
    {NULL, NULL}};