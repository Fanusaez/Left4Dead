enable_testing()
add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories("../src")

# Para agregar tests hacer asi
add_executable(testPrueba
        test_prueba.cpp
)

add_executable(testProtocolClient
        test_protocol_client.cpp
        ../src/client_serializer.cpp
)

add_executable(testProtocolServer
        test_protocol_server.cpp
        ../src/server_serializer.cpp
)

add_executable(testCollision
        test_collision.cpp
        ../src/soldier.cpp
        ../src/walker.cpp
        ../src/map.cpp
        ../src/idf.cpp
)

add_executable(testShooting
        test_shoot_walker.cpp
        ../src/soldier.cpp
        ../src/walker.cpp
        ../src/map.cpp
        ../src/idf.cpp
        )

add_executable(testShootingIdf
        test_shooting_idf.cpp
        ../src/soldier.cpp
        ../src/walker.cpp
        ../src/map.cpp
        ../src/idf.cpp
        )

add_executable(testShootingScout
        test_shooting_scout.cpp
        ../src/soldier.cpp
        ../src/walker.cpp
        ../src/map.cpp
        ../src/scout.cpp
        )

add_executable(testMovingUpSoldier
        test_moving_soldier_up.cpp
        ../src/soldier.cpp
        ../src/walker.cpp
        ../src/map.cpp
        ../src/scout.cpp
        )

add_executable(testMovingSoldierDown
        test_moving_soldier_down.cpp
        ../src/soldier.cpp
        ../src/walker.cpp
        ../src/map.cpp
        ../src/scout.cpp
        )

add_executable(testMovingSoldierRight
        test_moving_soldier_right.cpp
        ../src/soldier.cpp
        ../src/walker.cpp
        ../src/map.cpp
        ../src/scout.cpp
        )

add_executable(testMoveSoldierLeft
        test_moving_soldier_left.cpp
        ../src/soldier.cpp
        ../src/walker.cpp
        ../src/map.cpp
        ../src/scout.cpp
        )
add_executable(testMoveMap
        test_move_map.cpp
        ../src/soldier.cpp
        ../src/walker.cpp
        ../src/map.cpp
        ../src/scout.cpp
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
)

foreach(target ${testTargets})
        add_test(NAME "${target}" COMMAND "${target}")

        add_dependencies(test "${target}")
endforeach()
