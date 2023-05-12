enable_testing()
add_custom_target(test COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure)

include_directories("../src")

# Para agregar tests hacer asi
add_executable(testPrueba
        test_prueba.cpp
)
# target_link_libraries(testPrueba PRIVATE myLibrary)

# Despues agregar el target aca y listo
set(testTargets
        testPrueba
)

foreach(target ${testTargets})
        add_test(NAME "${target}" COMMAND "${target}")

        add_dependencies(test "${target}")
endforeach()
