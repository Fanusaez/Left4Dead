#include "acutest.h"
#include "game_logic/grenades/explosive_grenade.h"
#include "game_logic/map.h"
#include "game_logic/grenades/grenade_state/thrown_grenade.h"
#include "game_logic/states/idle.h"
#include "game_logic/grenades/grenade_state/exploding.h"
#include "game_logic/grenades/smoke_grenade.h"

void testExplosiveGrenadeInitialStateIdle(void) {
    ExplosiveGrenade grenade(0);
    GrenadeIdle* grenade_state = dynamic_cast<GrenadeIdle*>(grenade.get_state());
    TEST_CHECK(grenade_state != nullptr);
}

void testExplosiveGrenadeIsThrownStateChanges(void) {
    GameMap map(10,10);
    ExplosiveGrenade grenade(0);
    Idle idle;
    grenade.throw_grenade(map, 0, 0, &idle, 100);
    ThrownGrenade* grenade_state = dynamic_cast<ThrownGrenade*>(grenade.get_state());
    TEST_CHECK(grenade_state != nullptr);
}

void testExplosiveGrenadeExplodeStateChanges(void) {
    GameMap map(10,10);
    ExplosiveGrenade grenade(0);
    Idle idle;
    grenade.throw_grenade(map, 0, 0, &idle, 100);
    grenade.update(110);
    Exploding* grenade_state = dynamic_cast<Exploding*>(grenade.get_state());
    TEST_CHECK(grenade_state != nullptr);
}

void testSmokeGrenadeInitialStateIdle(void) {
    SmokeGrenade grenade(0);
    GrenadeIdle* grenade_state = dynamic_cast<GrenadeIdle*>(grenade.get_state());
    TEST_CHECK(grenade_state != nullptr);
}

void testSmokeGrenadeIsThrownStateChanges(void) {
    GameMap map(10,10);
    SmokeGrenade grenade(0);
    Idle idle;
    grenade.throw_grenade(map, 0, 0, &idle, 100);
    ThrownGrenade* grenade_state = dynamic_cast<ThrownGrenade*>(grenade.get_state());
    TEST_CHECK(grenade_state != nullptr);
}

void testSmokeGrenadeExplodeStateChanges(void) {
    GameMap map(10,10);
    SmokeGrenade grenade(0);
    Idle idle;
    grenade.throw_grenade(map, 0, 0, &idle, 100);
    grenade.update(110);
    Exploding* grenade_state = dynamic_cast<Exploding*>(grenade.get_state());
    TEST_CHECK(grenade_state != nullptr);
}
TEST_LIST = {
        {"Explosive grenade starts with Idle state", testExplosiveGrenadeInitialStateIdle},
        {"Explosive grenade is thrown, state changes", testExplosiveGrenadeIsThrownStateChanges},
        {"Explosive grenade explodes", testExplosiveGrenadeExplodeStateChanges},
        {"Smoke grenade starts with Idle state", testSmokeGrenadeInitialStateIdle},
        {"Smoke grenade is thrown, state changes", testSmokeGrenadeIsThrownStateChanges},
        {"Smoke grenade explodes", testSmokeGrenadeExplodeStateChanges},
        {NULL, NULL}
};