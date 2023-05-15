add_executable(main
	main.cpp
	map.cpp
	soldier.cpp
	walker.cpp
	idf.cpp
	scout.cpp
	game_object.h
	weapon.h
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
	add_executable(server_main ./server/server_main.cpp)
	target_link_libraries(server_main PRIVATE acceptor server socket thread resolver)
endif()
