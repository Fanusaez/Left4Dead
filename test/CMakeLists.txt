enable_testing()
add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories("../src")

# Para agregar tests hacer asi
add_executable(testPrueba
        test_prueba.cpp
)

add_executable(testProtocolClient
        test_protocol_client.cpp
        ../src/client_translator.cpp
)

add_executable(testProtocolServer
        test_protocol_server.cpp
        ../src/server_translator.cpp
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
# target_link_libraries(testPrueba PRIVATE myLibrary)

# Despues agregar el target aca y listo
set(testTargets
        testPrueba
        testProtocolClient
        testProtocolServer
        testCollision
        testShooting
        testShootingIdf
)

foreach(target ${testTargets})
        add_test(NAME "${target}" COMMAND "${target}")

        add_dependencies(test "${target}")
endforeach()
