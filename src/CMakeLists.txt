add_executable(main
	main.cpp
	map.cpp
	soldier.cpp
	walker.cpp
	idf.cpp
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
	file(COPY ${PROJECT_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})
endif()

#add_library(client_translator 
#	client_translator.cpp
#)

#target_include_directories(client_translator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
