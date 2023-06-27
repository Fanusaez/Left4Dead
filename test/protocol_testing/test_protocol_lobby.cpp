#include "../acutest.h"
#include <vector>
#include <string>

#include "client/lobby_serializer.h"
#include "common/game_mode.h"
#include "common/soldier_type.h"
#include "common/move_type.h"
#include "common/instructions_type.h"

/*----------------------Lobby message--------------------*/
void testSerializeCreateScenario(void)
{
    LobbySerializer lobby_serializer;
    std::string scenario_name = "Map1";
    std::vector<char> buffer = lobby_serializer.serialize_create_scenario(scenario_name,SURVIVAL,2);
    TEST_CHECK(buffer.size() == 8);
    TEST_CHECK(buffer.at(0) == CREATE);
    TEST_CHECK(buffer.at(1) == 0x04);
    TEST_CHECK(buffer.at(2) == 'M');
    TEST_CHECK(buffer.at(3) == 'a');
    TEST_CHECK(buffer.at(4) == 'p');
    TEST_CHECK(buffer.at(5) == '1');
    TEST_CHECK(buffer.at(6) == SURVIVAL);
    TEST_CHECK(buffer.at(7) == 2);
}

void testSerializeJoinScenario(void)
{
    LobbySerializer lobby_serializer;
    int32_t scenario_code = 10;
    std::vector<char> buffer = lobby_serializer.serialize_join_scenario(scenario_code);
    TEST_CHECK(buffer.size() == 5);
    TEST_CHECK(buffer.at(0) == JOIN);
    TEST_CHECK(buffer.at(1) == 0);
    TEST_CHECK(buffer.at(2) == 0);
    TEST_CHECK(buffer.at(3) == 0);
    TEST_CHECK(buffer.at(4) == 10);
}

void testSerializeGameMode(void)
{
    LobbySerializer lobby_serializer;
    GameMode game_mode = SURVIVAL;  //Utilizo enums para una mejor descripccion
    std::vector<char> buffer = lobby_serializer.serialize_game_mode(game_mode);
    //- mode: 0x03 <code>:  0x00 Clear the zone
    //                      0x01 Survivial                                    
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == GAME_MODE);
    TEST_CHECK(buffer.at(1) == 0x01);
}

void testSerializeSoldier(void)
{
    LobbySerializer lobby_serializer;
    SoldierType soldier_type = SCOUT; // Utilizo enums para una mejor descripccion
    std::vector<char> buffer = lobby_serializer.serialize_soldier(soldier_type);
    //- soldier: 0x04 <code>:   0x00 IDF
    //                          0x01 P90
    //                          0x02 SCOUT
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == SOLDIER_TYPE);
    TEST_CHECK(buffer.at(1) == 0x02);
}

void testSerializeStart(void)
{
    LobbySerializer lobby_serializer;
    std::vector<char> buffer = lobby_serializer.serialize_start_playing();
    //- start: 0x06
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == START);
}

//Sala de chat?

TEST_LIST = {
    {"Testing serialization: create scenario", testSerializeCreateScenario},
    {"Testing serialization: join scenario", testSerializeJoinScenario},
    {"Testing serialization: game mode", testSerializeGameMode},
    {"Testing serialization: pick soldier", testSerializeSoldier},
    {NULL, NULL}};