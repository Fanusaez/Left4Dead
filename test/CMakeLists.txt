enable_testing()
add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories("../src")

# Para agregar tests hacer asi
add_executable(testPrueba
        test_prueba.cpp
)
add_executable(testClient
        test_protocol_client.cpp
        ../src/client_translator.cpp
)

add_executable(testCollision
        test_collision.cpp
        ../src/soldier.cpp
        ../src/walker.cpp
        ../src/map.cpp
)
# target_link_libraries(testPrueba PRIVATE myLibrary)

# Despues agregar el target aca y listo
set(testTargets
        testPrueba
        testClient
        testCollision
)

foreach(target ${testTargets})
        add_test(NAME "${target}" COMMAND "${target}")

        add_dependencies(test "${target}")
endforeach()
