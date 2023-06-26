#include "../acutest.h"
#include <vector>
#include <string>

#include "server/server_serializer.h"
#include "common/game_dto.h"

void testSerializeCreateScenario(void)
{
    ServerSerializer server_serializer;
    int32_t code_scenario = 10;
    std::vector<char> buffer = server_serializer.serialize_create_scenario(code_scenario);
    //- create: <scenario code>
    TEST_CHECK(buffer.size() == 5);
    TEST_CHECK(buffer.at(0) == CREATE);
    TEST_CHECK(buffer.at(1) == 0);
    TEST_CHECK(buffer.at(2) == 0);
    TEST_CHECK(buffer.at(3) == 0);
    TEST_CHECK(buffer.at(4) == 10);
}

void testSerializeErrorCreate(void)
{
    ServerSerializer server_serializer;
    std::vector<char> buffer = server_serializer.serialize_error_create();
    //- create: <scenario code>
    TEST_CHECK(buffer.size() == 5);
    TEST_CHECK(buffer.at(0) == CREATE);
    TEST_CHECK(buffer.at(4) == -1);
}

void testSerializeJoinScenario(void)
{
    ServerSerializer server_serializer;
    bool join = true;   //Could join?
    std::vector<char> buffer = server_serializer.serialize_join_scenario(join);
    //- join: <join>
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == JOIN);
    TEST_CHECK(buffer.at(1) == 0x01);
}

void testSerializeStart(void)
{
    ServerSerializer server_serializer;
    std::vector<char> buffer = server_serializer.serialize_start_game(true);
    //- start: <start> <could_start>
    TEST_CHECK(buffer.size() == 2);
    TEST_CHECK(buffer.at(0) == START);
    TEST_CHECK(buffer.at(1) == 1);
}

void testSerializePlayerId(void)
{
    ServerSerializer server_serializer;
    int32_t player_id = 10;
    std::vector<char> buffer = server_serializer.serialize_player_id(player_id);
    //- join: <join>
    TEST_CHECK(buffer.size() == 4);
    TEST_CHECK(buffer.at(0) == 0x00);
    TEST_CHECK(buffer.at(1) == 0x00);
    TEST_CHECK(buffer.at(2) == 0x00);
    TEST_CHECK(buffer.at(3) == 10);
}

// Soldier position or infected position
void testSerializeGameDTO(void)
{
    ServerSerializer server_serializer;
    SoldierObjectDTO soldierObjectDTO(10, 1, 100, 10, 15, 30, 10, 20, 30, MOVING, IDF, false);
    ZombieObjectDTO zombieObjectDTO(2, 100, 20, 15, RUNNING, INFECTED, false);
    GameDTO gameDTO;
    gameDTO.add_soldier(soldierObjectDTO);
    gameDTO.add_zombie(zombieObjectDTO);
    std::vector<char> buffer = server_serializer.serialize_game(gameDTO);
    
    TEST_CHECK(buffer.size() == 42);
    TEST_CHECK(buffer.at(0) == 0x01);
    TEST_CHECK(buffer.at(1) == 0x01);
    TEST_CHECK(buffer.at(2) == 0x00);
    TEST_CHECK(buffer.at(3) == 0x00);

    TEST_CHECK(buffer.at(4) == 0x00);
    TEST_CHECK(buffer.at(5) == 0x00);
    TEST_CHECK(buffer.at(6) == 0x00);
    TEST_CHECK(buffer.at(7) == 10);

    TEST_CHECK(buffer.at(8) == 0x00);
    TEST_CHECK(buffer.at(9) == 0x01);

    TEST_CHECK(buffer.at(10) == MOVING);

    TEST_CHECK(buffer.at(11) == IDF);

    TEST_CHECK(buffer.at(12) == 0x00);
    TEST_CHECK(buffer.at(13) == 10);

    TEST_CHECK(buffer.at(14) == 0x00);
    TEST_CHECK(buffer.at(15) == 15);

    TEST_CHECK(buffer.at(16) == 0x00);

    TEST_CHECK(buffer.at(17) == 0x00);
    TEST_CHECK(buffer.at(18) == 30);

    TEST_CHECK(buffer.at(19) == 0x00);
    TEST_CHECK(buffer.at(20) == 100);

    TEST_CHECK(buffer.at(21) == 0x00);
    TEST_CHECK(buffer.at(22) == 10);

    TEST_CHECK(buffer.at(23) == 0x00);
    TEST_CHECK(buffer.at(24) == 20);

    TEST_CHECK(buffer.at(25) == 0x00);
    TEST_CHECK(buffer.at(26) == 30);

    TEST_CHECK(buffer.at(27) == 0x00);
    TEST_CHECK(buffer.at(28) == 0x02);

    TEST_CHECK(buffer.at(29) == 0x00);
    TEST_CHECK(buffer.at(30) == 100);

    TEST_CHECK(buffer.at(31) == RUNNING);

    TEST_CHECK(buffer.at(32) == INFECTED);

    TEST_CHECK(buffer.at(33) == 0x00);
    TEST_CHECK(buffer.at(34) == 20);

    TEST_CHECK(buffer.at(35) == 0x00);
    TEST_CHECK(buffer.at(36) == 15);

    TEST_CHECK(buffer.at(37) == 0x00);

    TEST_CHECK(buffer.at(38) == 0x00);
    TEST_CHECK(buffer.at(39) == 0x00);

    TEST_CHECK(buffer.at(40) == 0x00);
    TEST_CHECK(buffer.at(41) == 0x00);
}



TEST_LIST = {
    {"Testing serialization: create scenario", testSerializeCreateScenario},
    {"Testing serialization: error create escenario", testSerializeErrorCreate},
    {"Testing serialization: join scenario", testSerializeJoinScenario},
    {"Testing serialization: start game", testSerializeStart},
    {"Testing serialization: send player_id ", testSerializePlayerId},
    {"Testing serialization: send gameDTO ", testSerializeGameDTO},
    {NULL, NULL}};