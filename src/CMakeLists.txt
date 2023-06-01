

#add_executable(main
	#	main.cpp
		#game_logic/map.cpp
		#game_logic/soldier.cpp
		#game_logic/walker.cpp
		#game_logic/weapons/idf.cpp
		#game_logic/weapons/scout.cpp
		#game_logic/#game_object.h
		#game_logic/weapons/weapon.h
		#game_logic/zombie.h
		#game_logic/obstacle.cpp
		#game_logic/zombie_states/walking.cpp
		#game_logic/states/state.h
		#game_logic/states/idle.cpp
		#game_logic/states/reloading.cpp
		#game_logic/states/shooting.cpp
		#game_logic/states/moving.cpp
		#game_logic/states/being_attacked.cpp
		#game_logic/states/dead.cpp
		#game_logic/zombie_states/zombie_dead.cpp
		#game_logic/zombie_states/zombie_state.h
		#)

set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory(${CMAKE_SOURCE_DIR}/lib/libSDL2pp ${CMAKE_SOURCE_DIR}/build/lib/libSDL2pp)

add_library(gameview
		graphics/gameview.cpp
		graphics/renderable_object.cpp
		graphics/Player.cpp
		graphics/Animation.cpp
		graphics/texture_loader.cpp
		graphics/gameview_configs_loader.cpp
		graphics/scene.cpp
		)

target_include_directories(gameview PUBLIC ${PROJECT_SOURCE_DIR}/lib/libSDL2pp)
target_include_directories(gameview PUBLIC ${PROJECT_SOURCE_DIR}/src/graphics)
target_link_libraries(gameview PUBLIC SDL2pp)
target_compile_definitions(gameview PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")

option(VIEWTEST "Test game user interface" OFF)
if (VIEWTEST)
	add_executable(viewtest
			client_main.cpp)
	target_link_libraries(viewtest PRIVATE gameview)
	set(VIEWTEST_OUTPUT_DIR ${CMAKE_BINARY_DIR}/src/client)
	set_target_properties(viewtest
			PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${VIEWTEST_OUTPUT_DIR})
endif()

option(SERVER "Build server" OFF)

if(SERVER)
	add_executable(server
		./server/server_main.cpp
		./common/socket.cpp
		./common/resolver.cpp
		./common/game_dto.cpp
		./common/instructions_dto.cpp
		./server/acceptor.cpp
		./server/server.cpp
		./server/match_mananger.cpp
		./server/player_receiver.cpp
		./server/player_sender.cpp
		./server/player.cpp
		./server/game.cpp
		./server/server_serializer.cpp
		./server/server_deserializer.cpp
		./server/game_logic.cpp
		./game_logic/states/being_attacked.cpp
		./game_logic/states/dead.cpp
		./game_logic/states/idle.cpp
		./game_logic/states/moving.cpp
		./game_logic/states/reloading.cpp
		./game_logic/states/shooting.cpp
		./game_logic/states/state.h
		./game_logic/states/throwing_explosive_grenade.cpp
		./game_logic/weapons/idf.cpp
		./game_logic/weapons/scout.cpp
		./game_logic/weapons/weapon.h
		./game_logic/zombie_states/attacking.cpp
		./game_logic/zombie_states/walking.cpp
		./game_logic/zombie_states/zombie_being_attacked.cpp
		./game_logic/zombie_states/zombie_dead.cpp
		./game_logic/zombie_states/zombie_idle.cpp
		./game_logic/zombie_states/zombie_state.h
		./game_logic/map.cpp
		./game_logic/obstacle.cpp
		./game_logic/soldier.cpp
		./game_logic/walker.cpp
		./game_logic/walking.h
		./game_logic/zombie.h
		./game_logic/clear_the_zone.cpp


	)

	target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/src/game_logic)
	
endif()

option(CLIENT "Build client" OFF)

if(CLIENT)
	add_executable(main_client
		main.cpp
		./client/client_deserializer.cpp
		./client/client_serializer.cpp
		./client/client_sender.cpp
		./client/client_receiver.cpp
		./client/client.cpp
		./common/socket.cpp
		./common/resolver.cpp
		./common/game_dto.cpp
		./common/instructions_dto.cpp
	)
	target_link_libraries(main_client PUBLIC gameview)
	target_include_directories(main_client PUBLIC ${PROJECT_SOURCE_DIR}/src/client)
	set(CLIENT_OUTPUT_DIR ${CMAKE_BINARY_DIR}/src/client)
	set_target_properties(main_client
			PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CLIENT_OUTPUT_DIR})
endif()