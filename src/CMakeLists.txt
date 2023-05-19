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
)

option(GAMEUI "Build game user interface" OFF)

if(GAMEUI)
	# Graphics library
	set(SDL2PP_WITH_IMAGE ON)
	set(SDL2PP_WITH_MIXER ON)
	set(SDL2PP_WITH_TTF ON)
	add_subdirectory(${CMAKE_SOURCE_DIR}/lib/libSDL2pp ${CMAKE_SOURCE_DIR}/build/lib/libSDL2pp)

	add_executable(client
			client_main.cpp
			graphics/Player.cpp
			graphics/Animation.cpp
			graphics/texture_loader.cpp
			graphics/background.cpp
	)

	target_include_directories(client PRIVATE ${PROJECT_SOURCE_DIR}/lib/libSDL2pp)
	target_include_directories(client PRIVATE ${PROJECT_SOURCE_DIR}/src/graphics)
	target_link_libraries(client PRIVATE SDL2pp)
	set(CLIENT_OUTPUT_DIR ${CMAKE_BINARY_DIR}/src/client)
	set_target_properties(client
			PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${CLIENT_OUTPUT_DIR})
	file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${CLIENT_OUTPUT_DIR})
	target_compile_definitions(client PUBLIC ASSETS_PATH="${CLIENT_OUTPUT_DIR}/assets/")

endif()

option(SERVER "Build server" OFF)

if(SERVER)
	add_library(socket OBJECT ./common/socket.cpp ./common/socket.h)
	add_library(resolver OBJECT ./common/resolver.cpp ./common/resolver.h)
	add_library(thread OBJECT ./common/thread.h)
	add_library(acceptor OBJECT ./server/acceptor.cpp ./server/acceptor.h)
	add_library(server OBJECT ./server/server.cpp ./server/server.h)
	add_library(match_mananger OBJECT ./server/match_mananger.cpp ./server/match_mananger.h)
	add_library(player_receiver OBJECT ./server/player_receiver.cpp ./server/player_receiver.h)
	add_library(player_sender OBJECT ./server/player_sender.cpp ./server/player_sender.h)
	add_library(player OBJECT ./server/player.cpp ./server/player.h)
	add_library(game OBJECT ./server/game.cpp ./server/game.h)
	add_executable(server_main ./server/server_main.cpp)
	target_link_libraries(server_main PRIVATE acceptor server socket thread resolver match_mananger player_receiver player_sender player game)
endif()
