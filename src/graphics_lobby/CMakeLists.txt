project(qt5-demo)
cmake_minimum_required(VERSION 3.8)
# Find the QtWidgets library
find_package(Qt5Widgets)

message("[INFO] La raiz del proyecto es ${PROJECT_SOURCE_DIR}")

# Agrego ej4/src a la lista de directorios de includes
include_directories(${PROJECT_SOURCE_DIR})

# Esta macro toma cada uno los parámetros y ejecuta *uic* sobre ellos
# La aplicacion uic genera headers con la definición de los widgets
# a partir de un archivo .ui
# Los nombres de los headers generados se guardan en la variable pasada
# como primer parámetro.
# No, no los genera con la carpeta como prefijo.
qt5_wrap_ui(UIS_HEADERS
        mainwindow.ui
)

# Habilito el automoc para poder hacer autoconnect de señales
set(CMAKE_AUTOMOC on)
# Habilito autorcc para manejar automaticamente los QResources
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC ON)


# Agrego la carpeta con los headers autogenerados a los includes
message("Agregando '${PROJECT_BINARY_DIR}' como directorio de includes")
include_directories(${PROJECT_BINARY_DIR})

message("Headers generados: ${UIS_HEADERS}")

add_executable(lobby
  mainwindow.cpp
  mainwindow.h
  main.cpp
  resources.qrc
  ../client/client_deserializer.cpp
  ../client/client_serializer.cpp
  ../client/client_sender.cpp
  ../client/client_receiver.cpp
  ../client/client.cpp
  ../common/socket.cpp
  ../common/resolver.cpp
  ../common/game_dto.cpp
  ../common/instructionsDTO/instructions_dto.cpp
  ../common/instructionsDTO/join_dto.cpp
  ../common/instructionsDTO/create_dto.cpp
  ../common/instructionsDTO/start_dto.cpp
  ../common/instructionsDTO/move_dto.cpp
  ../client/lobby.cpp
  ../client/lobby_deserializer.cpp
  ../client/lobby_serializer.cpp
  ../client/lobby_sender.cpp
  ../client/lobby_receiver.cpp
  ${UIS_HEADERS})

# Use the Widgets module from Qt 5.
target_link_libraries(lobby Qt5::Widgets Qt5::Core)
