option(GAMEUI "Build game user interface" OFF)

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

if(GAMEUI)
	# Graphics library
	set(SDL2PP_WITH_IMAGE ON)
	set(SDL2PP_WITH_MIXER ON)
	set(SDL2PP_WITH_TTF ON)
	add_subdirectory(${CMAKE_SOURCE_DIR}/lib/libSDL2pp ${CMAKE_SOURCE_DIR}/build/lib/libSDL2pp)

	add_executable(gameview
			client_main.cpp
			graphics/gameview.cpp
			graphics/renderable_object.cpp
			graphics/Player.cpp
			graphics/Animation.cpp
			graphics/texture_loader.cpp
			graphics/scene.cpp
	)

	target_include_directories(gameview PRIVATE ${PROJECT_SOURCE_DIR}/lib/libSDL2pp)
	target_include_directories(gameview PRIVATE ${PROJECT_SOURCE_DIR}/src/graphics)
	target_link_libraries(gameview PRIVATE SDL2pp)
	set(CLIENT_OUTPUT_DIR ${CMAKE_BINARY_DIR}/src/client)
	set_target_properties(gameview
			PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CLIENT_OUTPUT_DIR})
	#file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CLIENT_OUTPUT_DIR})
	target_compile_definitions(gameview PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")

endif()

option(GAMEUI2 "Test user interface" OFF)


if(GAMEUI2)
	# Graphics library
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
			graphics/scene.cpp
	)

	target_include_directories(gameview PUBLIC ${PROJECT_SOURCE_DIR}/lib/libSDL2pp)
	target_include_directories(gameview PUBLIC ${PROJECT_SOURCE_DIR}/src/graphics)
	target_link_libraries(gameview PUBLIC SDL2pp)
	#file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CLIENT_OUTPUT_DIR})
	target_compile_definitions(gameview PUBLIC ASSETS_PATH="${CMAKE_SOURCE_DIR}/assets/")

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
		game_logic/map.cpp
        game_logic/soldier.cpp
        game_logic/walker.cpp
		game_logic/weapons/idf.cpp
		game_logic/weapons/scout.cpp
        game_logic/game_object.h
		game_logic/weapons/weapon.h
		game_logic/zombie.h
		game_logic/obstacle.cpp
		game_logic/movement.h
		game_logic/walking.cpp
		game_logic/states/state.h
		game_logic/states/being_attacked.cpp
		game_logic/states/idle.cpp
		game_logic/states/reloading.cpp
		game_logic/states/shooting.cpp
		game_logic/states/moving.cpp
		game_logic/zombie_states/zombie_dead.cpp
		game_logic/zombie_states/zombie_state.h
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
endif()