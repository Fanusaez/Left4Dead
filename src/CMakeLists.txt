
option(SERVER "Build server" ON)

if(SERVER)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -pthread")
	add_executable(server
		./server/server_main.cpp
		./common/socket.cpp
		./common/resolver.cpp
		./common/game_dto.cpp
		./common/instructionsDTO/instructions_dto.cpp
		./common/instructionsDTO/join_dto.cpp
		./common/instructionsDTO/create_dto.cpp
		./common/instructionsDTO/move_dto.cpp
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
		./game_logic/clear_the_zone.cpp
		./game_logic/game_factory.cpp

	)

	target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/src/game_logic)
	set(SERVER_OUTPUT_DIR ${CMAKE_BINARY_DIR})
	set_target_properties(server
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
			graphics/Player.cpp
			graphics/infected.cpp
			graphics/witch.cpp
			graphics/jumper.cpp
			graphics/grenade.cpp
			graphics/Animation.cpp
			graphics/texture_loader.cpp
			graphics/gameview_configs_loader.cpp
			graphics/scene.cpp
			graphics/object_creator.cpp
			)

	target_include_directories(gameview PUBLIC ${PROJECT_SOURCE_DIR}/lib/libSDL2pp)
	target_include_directories(gameview PRIVATE ${PROJECT_SOURCE_DIR}/src/graphics)
	target_link_libraries(gameview PUBLIC SDL2pp)
	target_compile_definitions(gameview PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")

	add_executable(l4dclient
		main.cpp
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
		./common/instructionsDTO/move_dto.cpp
		./client/lobby.cpp
		./client/lobby_deserializer.cpp
		./client/lobby_serializer.cpp
		./client/lobby_sender.cpp
		./client/lobby_receiver.cpp
	)
	target_link_libraries(l4dclient PUBLIC gameview)
	target_include_directories(l4dclient PRIVATE ${PROJECT_SOURCE_DIR}/src)
	target_include_directories(l4dclient PUBLIC ${PROJECT_SOURCE_DIR}/src/client)
	set(CLIENT_OUTPUT_DIR ${CMAKE_BINARY_DIR})
	set_target_properties(l4dclient
			PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CLIENT_OUTPUT_DIR})
endif()