#include <cstdint>
#include "acutest.h"
#include "game_logic/soldier.h"
#include "game_logic/zombies/witch.h"
#include "game_logic/map.h"
#include "game_logic/game_object.h"
#include "game_logic/weapons/idf.h"
#include "game_logic/weapons/weapon.h"

void testWitcherScreamsAndAttractsZombies(void) {
    GameMap map(10, 10);

    Witch witch(1,8, 0, map);
    witch.scream(1);
    std::int16_t objects_in_map = map.objects_in_map();
    TEST_CHECK(objects_in_map > 0);
}

TEST_LIST = {
        {"Witcher screams and attracts other zombies into the map", testWitcherScreamsAndAttractsZombies},
        {NULL, NULL}
};

