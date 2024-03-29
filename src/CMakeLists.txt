option(INSTALL "Apply install settings" OFF)
if (INSTALL EQUAL ON)
	message(STATUS "Applying install settings")
	set(CONFIG_FILE "/var/games/l4d/configurations.yaml")
	set(BINDIR "/usr/local/bin")
	set(VARDIR "/var/games/l4d")
else()
	set(CONFIG_FILE "${CMAKE_SOURCE_DIR}/configurations.yaml")
	set(BINDIR ${CMAKE_BINARY_DIR})
	set(VARDIR ${CMAKE_SOURCE_DIR})
endif()
set(LIBDIR "/usr/local/lib")

option(SERVER "Build server" ON)
if(SERVER)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")

	add_executable(l4dserver
		./server/server_main.cpp
		./common/socket.cpp
		./common/resolver.cpp
		./common/game_dto.cpp
		./common/instructionsDTO/instructions_dto.cpp
		./common/instructionsDTO/join_dto.cpp
		./common/instructionsDTO/create_dto.cpp
		./common/instructionsDTO/move_dto.cpp
		./common/instructionsDTO/grenade_dto.cpp
		./common/instructionsDTO/soldier_type_dto.cpp
		./server/acceptor.cpp
		./server/server.cpp
		./server/match_mananger.cpp
		./server/player_receiver.cpp
		./server/player_sender.cpp
		./server/player.cpp
		./server/game.cpp
		./server/protected_outputs_queue.cpp
		./server/protected_game_list.cpp
		./server/server_serializer.cpp
		./server/server_deserializer.cpp
		./server/game_logic.cpp
		./game_logic/states/being_attacked.cpp
		./game_logic/states/calling_air_strike.cpp
		./game_logic/states/dead.cpp
		./game_logic/states/idle.cpp
		./game_logic/states/moving.cpp
		./game_logic/states/reloading.cpp
		./game_logic/states/shooting.cpp
		./game_logic/states/state.h
		./game_logic/states/throwing_explosive_grenade.cpp
		./game_logic/states/throwing_smoke_grenade.cpp
		./game_logic/weapons/idf.cpp
		./game_logic/weapons/scout.cpp
		./game_logic/weapons/p90.cpp
		./game_logic/weapons/weapon.h
		./game_logic/grenades/grenade.h
		./game_logic/grenades/explosive_grenade.cpp
		./game_logic/grenades/smoke_grenade.cpp
		./game_logic/grenades/grenade_state/grenade_idle.cpp
		./game_logic/grenades/grenade_state/exploding.cpp
		./game_logic/grenades/grenade_state/thrown_grenade.cpp
		./game_logic/zombie_states/attacking_long_range.cpp
		./game_logic/zombie_states/attacking.cpp
		./game_logic/zombie_states/running.cpp
		./game_logic/zombie_states/jumping.cpp
		./game_logic/zombie_states/walking.cpp
		./game_logic/zombie_states/zombie_being_attacked.cpp
		./game_logic/zombie_states/zombie_dead.cpp
		./game_logic/zombie_states/stunned.cpp
		./game_logic/zombie_states/screaming.cpp
		./game_logic/zombie_states/chasing_states/chase_walking.cpp
		./game_logic/zombie_states/chasing_states/chase_running.cpp
		./game_logic/zombie_states/chasing_states/chase_jumping.cpp
		./game_logic/zombie_states/zombie_idle.cpp
		./game_logic/zombie_states/zombie_state.h
		./game_logic/chaser.cpp
		./game_logic/map.cpp
		./game_logic/air_strike/air_strike.cpp
		./game_logic/air_strike/air_strike_states/air_strike_exploding.cpp
		./game_logic/air_strike/air_strike_states/air_strike_idle.cpp
		./game_logic/air_strike/air_strike_states/air_strike_incoming.cpp
		./game_logic/obstacle.cpp
		./game_logic/soldier.cpp
		./game_logic/zombies/infected.cpp
		./game_logic/zombies/jumper.cpp
		./game_logic/zombies/witch.cpp
		./game_logic/zombies/zombie.h
		./game_logic/zombies/venom/venom.cpp
		./game_logic/playing_modes/map_mode.h
		./game_logic/playing_modes/clear_the_zone.cpp
		./game_logic/playing_modes/survival.cpp
		./game_logic/zombies/spear.cpp
        ./game_logic/playing_modes/clear_the_zone.cpp
		./game_logic/game_factory.cpp
		./game_logic/configuration.cpp
		./game_logic/zombies/venom/venom_attack/venom_close_range_attack.cpp
		./game_logic/zombies/venom/venom_attack/venom_long_range_attack.cpp
	)
	target_compile_definitions(l4dserver PUBLIC CONFIG_PATH="${CONFIG_FILE}")
	target_link_libraries(l4dserver -lyaml-cpp)
	target_include_directories(l4dserver PUBLIC ${PROJECT_SOURCE_DIR}/src/game_logic)
	set(SERVER_OUTPUT_DIR ${CMAKE_BINARY_DIR})

	set_target_properties(l4dserver
			PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${SERVER_OUTPUT_DIR})
endif()


option(CLIENT "Build client" ON)

if(CLIENT)
	set(SDL2PP_WITH_IMAGE ON)
	set(SDL2PP_WITH_MIXER ON)
	set(SDL2PP_WITH_TTF ON)
	add_subdirectory(${CMAKE_SOURCE_DIR}/lib/libSDL2pp ${CMAKE_SOURCE_DIR}/build/lib/libSDL2pp)

	add_library(gameview
			graphics/gameview.cpp
			graphics/renderable_object.cpp
			graphics/playable.cpp
			graphics/Player.cpp
			graphics/scout.cpp
			graphics/p90_soldier.cpp
			graphics/infected.cpp
			graphics/witch.cpp
			graphics/jumper.cpp
			graphics/lancer.cpp
			graphics/venom.cpp
			graphics/grenade.cpp
			graphics/smoke.cpp
			graphics/venom_grenade.cpp
			graphics/Animation.cpp
			graphics/texture_loader.cpp
			graphics/gameview_configs_loader.cpp
			graphics/scene.cpp
			graphics/object_creator.cpp
			)

	target_include_directories(gameview PUBLIC ${PROJECT_SOURCE_DIR}/lib/libSDL2pp)
	target_include_directories(gameview PRIVATE ${PROJECT_SOURCE_DIR}/src/graphics)
	target_link_libraries(gameview PUBLIC SDL2pp)
	target_compile_definitions(gameview PUBLIC ASSETS_PATH="${VARDIR}/assets/")
	# Find the QtWidgets library
	find_package(Qt5Widgets CONFIG REQUIRED)

	include_directories(${PROJECT_SOURCE_DIR}/src/graphics_lobby)
	qt5_wrap_ui(UIS_HEADERS
				./graphics_lobby/mainwindow.ui
				./graphics_lobby/joinpopup.ui
				./graphics_lobby/createpopup.ui
				./graphics_lobby/playerpick.ui)
	# Instruct CMake to run moc automatically when neededcd
	set(CMAKE_AUTOMOC ON)
	# Create code from a list of Qt designer ui files
	set(CMAKE_AUTORCC ON)

	# Adding directory with the autogenerated headers as include directory
	include_directories(${PROJECT_BINARY_DIR}/src)

	add_executable(l4dclient
		main.cpp
			./client/game.cpp
		./client/client_deserializer.cpp
		./client/client_serializer.cpp
		./client/client_sender.cpp
		./client/client_receiver.cpp
		./client/client.cpp
		./common/socket.cpp
		./common/resolver.cpp
		./common/game_dto.cpp
		./common/instructionsDTO/instructions_dto.cpp
		./common/instructionsDTO/join_dto.cpp
		./common/instructionsDTO/create_dto.cpp
		./common/instructionsDTO/start_dto.cpp
		./common/instructionsDTO/move_dto.cpp
		./common/instructionsDTO/soldier_type_dto.cpp
		./client/lobby.cpp
		./client/lobby_deserializer.cpp
		./client/lobby_serializer.cpp
		./client/lobby_sender.cpp
		./client/lobby_receiver.cpp
		./graphics_lobby/joinpopup.cpp
		./graphics_lobby/mainwindow.cpp
		./graphics_lobby/createpopup.cpp
		./graphics_lobby/playerpick.cpp
		./graphics_lobby/assets/resources.qrc
		${UIS_HEADERS}
	)
				
	# Use the Widgets module from Qt 5.
	target_link_libraries(l4dclient PUBLIC Qt5::Widgets Qt5::Core)
	#add_subdirectory(${PROJECT_SOURCE_DIR}/src/graphics_lobby)
	#target_link_libraries(l4dclient PUBLIC lobby)
	target_link_libraries(l4dclient PUBLIC gameview)
	target_include_directories(l4dclient PRIVATE ${PROJECT_SOURCE_DIR}/src)
	target_include_directories(l4dclient PUBLIC ${PROJECT_SOURCE_DIR}/src/client)
	set(CLIENT_OUTPUT_DIR ${CMAKE_BINARY_DIR})
	set_target_properties(l4dclient
			PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CLIENT_OUTPUT_DIR}
			INSTALL_RPATH ${LIBDIR})
endif()

if(SERVER AND INSTALL)
	install (FILES "${CMAKE_SOURCE_DIR}/configurations.yaml"
			DESTINATION ${VARDIR})
	install(TARGETS l4dserver
			RUNTIME DESTINATION ${BINDIR}
	)
endif()

if(CLIENT AND INSTALL)
	install(TARGETS l4dclient
			RUNTIME DESTINATION ${BINDIR}
			)
	install(TARGETS SDL2pp
			ARCHIVE DESTINATION ${LIBDIR}
			)
	install(DIRECTORY ${CMAKE_SOURCE_DIR}/assets
			DESTINATION ${VARDIR}
			)
endif()
