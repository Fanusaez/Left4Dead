#include "acutest.h"
#include <vector>
#include <string>

#include "../src/server_translator.h"
#include "../src/game_mode.h"
#include "../src/soldier_type.h"
#include "../src/move.h"



void testSerializeCreateScenario(void)
{
    ServerTranslator server_translator;
    int32_t code_scenario = 10;
    std::vector<char> buffer = server_translator.translate_create_scenario(&code_scenario);
    //- create: <scenario code>
    TEST_CHECK(buffer.size() == 4);
    TEST_CHECK(buffer.at(0) == 0);
    TEST_CHECK(buffer.at(1) == 0);
    TEST_CHECK(buffer.at(2) == 0);
    TEST_CHECK(buffer.at(3) == 10);
}

void testSerializeJoinScenario(void)
{
    ServerTranslator server_translator;
    bool join = true;   //Could join?
    std::vector<char> buffer = server_translator.translate_join_scenario(&join);
    //- join: <join>
    TEST_CHECK(buffer.size() == 1);
    TEST_CHECK(buffer.at(0) == 0x01);
}

// Soldier position or infected position
void testSerializeSoldierPosition(void)
{
    ServerTranslator server_translator;
    int16_t x_pos = 0x10; // int16_t from soldier.h
    int16_t y_pos = 0x0F00; // int16_t from soldier.h
    std::vector<char> buffer = server_translator.translate_soldier_position(&x_pos, &y_pos);
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
    ServerTranslator server_translator;
    int ammo = 50;
    std::vector<char> buffer = server_translator.translate_soldier_ammo(&ammo);
    //- position: 0x02 <msg len> <ammo>
    TEST_CHECK(buffer.size() == 3);
    TEST_CHECK(buffer.at(0) == 0x02);
    TEST_CHECK(buffer.at(1) == 0x01);
    TEST_CHECK(buffer.at(2) == 50);
}

void testSerializeSoldierHealth(void)
{
    ServerTranslator server_translator;
    int health = 100; 
    std::vector<char> buffer = server_translator.translate_soldier_health(&health);
    //- position: 0x03 <msg len> <health>
    TEST_CHECK(buffer.size() == 3);
    TEST_CHECK(buffer.at(0) == 0x03);
    TEST_CHECK(buffer.at(1) == 0x01);
    TEST_CHECK(buffer.at(2) == 100);
}

/*-----------------For survival game mode----------------*/

void testGameStats(void)
{
    ServerTranslator server_translator;
    int infected = 100;
    int ammo = 1000;
    int time = 900; //Segundos totales?
    std::vector<char> buffer = server_translator.translate_game_stats(&infected, &ammo, &time);
    //- position: 0x04 <infected> <ammo> <time>
    TEST_CHECK(buffer.size() == 4);
    TEST_CHECK(buffer.at(0) == 0x04);
    TEST_CHECK(buffer.at(1) == 100);
    TEST_CHECK(buffer.at(2) == 1000);
    TEST_CHECK(buffer.at(3) == 900);
}

/* void testListGamesAvailable(void)
{
    ServerTranslator server_translator;


    std::vector<char> buffer = server_translator.translate_games_availables();
    //- list of games: <number of games> <code game i> <number of players in i> 
} */

TEST_LIST = {
    {"Testing serialization: create scenario", testSerializeCreateScenario},
    {"Testing serialization: join scenario", testSerializeJoinScenario},
    {"Testing serialization: soldier position", testSerializeSoldierPosition},
    {"Testing serialization: soldier ammo ", testSerializeSoldierAmmo},
    {"Testing serialization: soldier health ", testSerializeSoldierHealth},
    //{"Testing serialization: games list", testListGamesAvailable},
    {NULL, NULL}
};