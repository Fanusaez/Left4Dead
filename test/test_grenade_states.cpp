#include "acutest.h"
#include "game_logic/grenades/explosive_grenade.h"
#include "game_logic/map.h"
#include "game_logic/grenades/grenade_state/thrown_grenade.h"
#include "game_logic/states/idle.h"

void testExplosiveGrenadeInitialStateIdle(void) {
    ExplosiveGrenade grenade;
    GrenadeIdle* grenade_state = dynamic_cast<GrenadeIdle*>(grenade.get_state());
    TEST_CHECK(grenade_state != nullptr);
}

void testExplisiveGrenadeIsThrownStateChanges(void) {
    GameMap map(10,10);
    ExplosiveGrenade grenade;
    Idle idle;
    grenade.throw_grenade(map, 0, 0, &idle, 100);
    ThrownGrenade* grenade_state = dynamic_cast<ThrownGrenade*>(grenade.get_state());
    TEST_CHECK(grenade_state != nullptr);
}


TEST_LIST = {
        {"Explosive grenade starts with Idle state", testExplosiveGrenadeInitialStateIdle},
        {"Explosive grenade is thrown, state changes", testExplisiveGrenadeIsThrownStateChanges},
        {NULL, NULL}
};