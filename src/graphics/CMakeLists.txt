set(SDL2PP_WITH_IMAGE ON)
set(SDL2PP_WITH_MIXER ON)
set(SDL2PP_WITH_TTF ON)
add_subdirectory(${PROJECT_SOURCE_DIR}/lib/libSDL2pp)

include_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${SDL2PP_INCLUDE_DIRS})