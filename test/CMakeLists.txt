enable_testing()
add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories("../src")

# Para agregar tests hacer asi
add_executable(testPrueba
        test_prueba.cpp
)

add_executable(testProtocolClient
        test_protocol_client.cpp
        ../src/client/client_serializer.cpp
)

add_executable(testProtocolServer
        test_protocol_server.cpp
        ../src/server/server_serializer.cpp
        ../src/common/game_dto.cpp
        ../src/common/socket.cpp
        ../src/common/resolver.cpp
)

add_executable(testCollision
        test_collision.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/idf.cpp
        ../src/game_logic/walking.cpp
)

add_executable(testShooting
        test_shoot_walker.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/idf.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testShootingIdf
        test_shooting_idf.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/idf.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testShootingScout
        test_shooting_scout.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testMovingUpSoldier
        test_moving_soldier_up.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testMovingSoldierDown
        test_moving_soldier_down.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testMovingSoldierRight
        test_moving_soldier_right.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testMoveSoldierLeft
        test_moving_soldier_left.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/walking.cpp
        )
add_executable(testMoveMap
        test_move_map.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testExplosiveGrenade
        test_explosive_grenade.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testChaseSoldierWalking
        test_chase_soldier_walker.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testMapChaseSoldierWalking
        test_map_chase_soldier_walker.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testChaseSoldierWalkingObstacles
        test_chase_soldier_walker_obstacles.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/obstacle.cpp
        ../src/game_logic/walking.cpp
        )

add_executable(testWalkerAttackSoldier
        test_walker_attack_soldier.cpp
        ../src/game_logic/soldier.cpp
        ../src/game_logic/walker.cpp
        ../src/game_logic/map.cpp
        ../src/game_logic/scout.cpp
        ../src/game_logic/obstacle.cpp
        ../src/game_logic/walking.cpp
        )
# target_link_libraries(testPrueba PRIVATE myLibrary)

# Despues agregar el target aca y listo
set(testTargets
        testPrueba
        testProtocolClient
        testProtocolServer
        testCollision
        testShooting
        testShootingIdf
        testShootingScout
        testMovingUpSoldier
        testMovingSoldierDown
        testMovingSoldierRight
        testMoveSoldierLeft
        testMoveMap
        testExplosiveGrenade
        testChaseSoldierWalking
        #testMapChaseSoldierWalking
        #testChaseSoldierWalkingObstacles
)

foreach(target ${testTargets})
        add_test(NAME "${target}" COMMAND "${target}")

        add_dependencies(test "${target}")
endforeach()
