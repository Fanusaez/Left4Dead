#include "acutest.h"
#include <vector>
#include <string>

#include "../src/client_serializer.h"
#include "../src/game_mode.h"
#include "../src/soldier_type.h"
#include "../src/move.h"
/*----------------------Lobby message--------------------*/
void testSerializeCreateScenario(void)
{
    ClientSerializer client_transaltor;
    std::string scenario_name = "Map1";
    std::vector<char> buffer = client_transaltor.translate_create_scenario(&scenario_name);
    //- create: 0x01 <scenario len> <scenario name>
    TEST_CHECK(buffer.size() == 6);
    TEST_CHECK(buffer.at(0) == 0x01);
    TEST_CHECK(buffer.at(1) == 0x04);
    TEST_CHECK(buffer.at(2) == 'M');
    TEST_CHECK(buffer.at(3) == 'a');
    TEST_CHECK(buffer.at(4) == 'p');
    TEST_CHECK(buffer.at(5) == '1');
}

void testSerializeJoinScenario(void)
{
    ClientSerializer client_transaltor;
    int32_t scenario_code = 10;
    std::vector<char> buffer = client_transaltor.translate_join_scenario(&scenario_code);
    //- join: 0x02 <code>
    TEST_CHECK(buffer.size() == 5);
    TEST_CHECK(buffer.at(0) == 0x02);
    TEST_CHECK(buffer.at(1) == 0);
    TEST_CHECK(buffer.at(2) == 0);
    TEST_CHECK(buffer.at(3) == 0);
    TEST_CHECK(buffer.at(4) == 10);
}

void testSerializeGameMode(void)
{
    ClientSerializer client_transaltor;
    GameMode game_mode = SURVIVAL;  //Utilizo enums para una mejor descripccion
    std::vector<char> buffer = client_transaltor.translate_game_mode(&game_mode);
    //- mode: 0x03 <msg len> <code>: 0x00 Clear the zone
    //                               0x01 Survivial                                    
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == 0x03);
    TEST_CHECK(buffer.at(1) == 0x01);
}

void testSerializeSoldier(void)
{
    ClientSerializer client_transaltor;
    SoldierType soldier_type = SCOUT; // Utilizo enums para una mejor descripccion
    std::vector<char> buffer = client_transaltor.translate_soldier(&soldier_type);
    //- soldier: 0x04 <code>:   0x00 IDF
    //                          0x01 P90
    //                          0x02 SCOUT
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == 0x04);
    TEST_CHECK(buffer.at(1) == 0x02);
}

void testRequestGamesList(void){
    ClientSerializer client_transaltor;
    std::vector<char> buffer = client_transaltor.translate_request_game_list();
    // -game list: 0x05
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == 0x05);
}

//Sala de chat?

/*----------------------Game message--------------------*/

void testMovingSoldier(void)
{
    ClientSerializer client_transaltor;
    Move move = UP;
    std::vector<char> buffer = client_transaltor.translate_move(&move);
    //- mode: 0x06 <code>: 0x00 RIGHT
    //                               0x01 LEFT
    //                               0x02 UP
    //                               0x03 DOWN
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == 0x06);
    TEST_CHECK(buffer.at(1) == 0x02);
}

void testReloadingGun(void)
{
    ClientSerializer client_transaltor;
    std::vector<char> buffer = client_transaltor.translate_reloading();
    //- reloading: 0x07
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == 0x07);
}

void testShootingGun(void){
    ClientSerializer client_transaltor;
    std::vector<char> buffer = client_transaltor.translate_shooting();
    //- shooting: 0x08
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == 0x08);
}

void testThrowGrenede(void){
    ClientSerializer client_transaltor;
    int time = 5; //Time in seconds
    std::vector<char> buffer = client_transaltor.translate_throw_grenede(&time);
    //- shooting: 0x09
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == 0x09);
    TEST_CHECK(buffer.at(1) == 0x05);
}

TEST_LIST = {
    {"Testing serialization: create scenario", testSerializeCreateScenario},
    {"Testing serialization: join scenario", testSerializeJoinScenario},
    {"Testing serialization: game mode", testSerializeGameMode},
    {"Testing serialization: pick soldier", testSerializeSoldier},
    {"Testing serialization: request list of games", testRequestGamesList},
    {"Testing serialization: move soldier", testMovingSoldier},
    {"Testing serialization: reloading gun", testReloadingGun},
    {"Testing serialization: shooting gun", testShootingGun},
    {NULL, NULL}};