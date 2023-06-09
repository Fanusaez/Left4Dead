#include "acutest.h"
#include <vector>
#include <string>

#include "../src/server/server_serializer.h"
#include "../src/common/soldier_type.h"
#include "../src/common/game_mode.h"
#include "../src/common/move_type.h"

void testSerializeCreateScenario(void)
{
    ServerSerializer server_serializer;
    int32_t code_scenario = 10;
    std::vector<char> buffer = server_serializer.serialize_create_scenario(&code_scenario);
    //- create: <scenario code>
    TEST_CHECK(buffer.size() == 4);
    TEST_CHECK(buffer.at(0) == 0);
    TEST_CHECK(buffer.at(1) == 0);
    TEST_CHECK(buffer.at(2) == 0);
    TEST_CHECK(buffer.at(3) == 10);
}

void testSerializeJoinScenario(void)
{
    ServerSerializer server_serializer;
    bool join = true;   //Could join?
    std::vector<char> buffer = server_serializer.serialize_join_scenario(&join);
    //- join: <join>
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == 0x01);
}

// Soldier position or infected position
void testSerializeSoldierPosition(void)
{
    ServerSerializer server_serializer;
    int16_t x_pos = 0x10; // int16_t from soldier.h
    int16_t y_pos = 0x0F00; // int16_t from soldier.h
    std::vector<char> buffer = server_serializer.serialize_soldier_position(&x_pos, &y_pos);
    //- position: 0x01 <x_pos> <y_pos>
    TEST_CHECK(buffer.size() == 5);
    TEST_CHECK(buffer.at(0) == 0x01);
    TEST_CHECK(buffer.at(1) == 0x00);
    TEST_CHECK(buffer.at(2) == 0x10);
    TEST_CHECK(buffer.at(3) == 0x0F);
    TEST_CHECK(buffer.at(4) == 0x00);
}

void testSerializeSoldierAmmo(void)
{
    ServerSerializer server_serializer;
    int ammo = 50;
    std::vector<char> buffer = server_serializer.serialize_soldier_ammo(&ammo);
    //- position: 0x02 <msg len> <ammo>
    TEST_CHECK(buffer.size() == 3);
    TEST_CHECK(buffer.at(0) == 0x02);
    TEST_CHECK(buffer.at(1) == 0x01);
    TEST_CHECK(buffer.at(2) == 50);
}

void testSerializeSoldierHealth(void)
{
    ServerSerializer server_serializer;
    int health = 100;
    std::vector<char> buffer = server_serializer.serialize_soldier_health(&health);
    //- position: 0x03 <msg len> <health>
    TEST_CHECK(buffer.size() == 3);
    TEST_CHECK(buffer.at(0) == 0x03);
    TEST_CHECK(buffer.at(1) == 0x01);
    TEST_CHECK(buffer.at(2) == 100);
}

/*-----------------For survival game mode----------------*/

void testGameStats(void)
{
    ServerSerializer server_serializer;
    int infected = 100;
    int16_t ammo = 0x0810; // 2064
    int16_t time = 0x0354; // Segundos totales? ->852 sec
    std::vector<char> buffer = server_serializer.serialize_game_stats(&infected, &ammo, &time);
    //- position: 0x04 <infected> <ammo> <time>
    TEST_CHECK(buffer.size() == 6);
    TEST_CHECK(buffer.at(0) == 0x04);
    TEST_CHECK(buffer.at(1) == 100);
    TEST_CHECK(buffer.at(2) == 0x08);
    TEST_CHECK(buffer.at(3) == 0x10);
    TEST_CHECK(buffer.at(4) == 0x03);
    TEST_CHECK(buffer.at(5) == 0x54);
}

void testListGamesAvailable(void)
{
    ServerSerializer server_serializer;
    int games = 3;
    std::vector<int> codes = {0,1,2}; //codes capaz tiene que ser de int32_t
    std::vector<int> people = {2, 4, 3}; //En la partide de code=0 hay 2 personas
    std::vector<char> buffer = server_serializer.serialize_games_availables(&games, &codes, &people);
    //- list of games: <number of games> <code game i> <number of players in i>
    TEST_CHECK(buffer.size() == 7);
    TEST_CHECK(buffer.at(0) == 0x03);
    TEST_CHECK(buffer.at(1) == 0x00);
    TEST_CHECK(buffer.at(2) == 0x02);
    TEST_CHECK(buffer.at(3) == 0x01);
    TEST_CHECK(buffer.at(4) == 0x04);
    TEST_CHECK(buffer.at(5) == 0x02);
    TEST_CHECK(buffer.at(6) == 0x03);
}


TEST_LIST = {
    {"Testing serialization: create scenario", testSerializeCreateScenario},
    {"Testing serialization: join scenario", testSerializeJoinScenario},
    {"Testing serialization: soldier position", testSerializeSoldierPosition},
    {"Testing serialization: soldier ammo ", testSerializeSoldierAmmo},
    {"Testing serialization: soldier health ", testSerializeSoldierHealth},
    {"Testing serialization: games stats", testGameStats},
    {"Testing serialization: games list", testListGamesAvailable},
    {NULL, NULL}};