add_executable(main
	main.cpp
        game_logic/map.cpp
        game_logic/soldier.cpp
        game_logic/walker.cpp
        game_logic/idf.cpp
        game_logic/scout.cpp
        game_logic/game_object.h
        game_logic/weapon.h
		game_logic/zombie.h
		game_logic/obstacle.cpp
		game_logic/movement.h
		game_logic/walking.cpp
)

option(GAMEUI "Build game user interface" OFF)

if(GAMEUI)
	# Graphics library
	set(SDL2PP_WITH_IMAGE ON)
	set(SDL2PP_WITH_MIXER ON)
	set(SDL2PP_WITH_TTF ON)
	add_subdirectory(${CMAKE_SOURCE_DIR}/lib/libSDL2pp ${CMAKE_SOURCE_DIR}/build/lib/libSDL2pp)

	add_executable(gameview
			client_main.cpp
			graphics/Player.cpp
			graphics/Animation.cpp
			graphics/texture_loader.cpp
            graphics/stage.cpp
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
	)
endif()

option(CLIENT "Build client" OFF)

if(CLIENT)
	add_executable(client
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
endif()