cmake_minimum_required(VERSION 3.16)

project(Worms
    DESCRIPTION "TP de Taller de Programación 1 2c2023 FIUBA"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)

find_package(Qt5Widgets CONFIG REQUIRED)

find_package(yaml-cpp REQUIRED)

include_directories(${PROJECT_SOURCE_DIR}/client_src/graphics_lobby)
qt5_wrap_ui(UIS_HEADERS
            ./graphics_editor/mainwindow.ui
            ./graphics_editor/createpopup.ui
            ./graphics_editor/joinpopup.ui
         
         )
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)




add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")
add_definitions(-DMAPA_PATH="${PROJECT_SOURCE_DIR}/mapas")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L -pthread")

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/box2d-2.4.0 ${CMAKE_SOURCE_DIR}/build/libs/box2d-2.4.0)

    set(SDL2PP_WITH_IMAGE ON)
    set(SDL2PP_WITH_MIXER ON)
    set(SDL2PP_WITH_TTF ON)
    add_subdirectory(${CMAKE_SOURCE_DIR}/libs/SDL2pp ${CMAKE_SOURCE_DIR}/build/libs/SDL2pp)
    add_executable(client 
                ./client_src/client_main.cpp 
                ./client_src/game.cpp
                ./client_src/graphics/view.cpp
                ./client_src/graphics/whorms.cpp
                ./client_src/graphics/path_loader.cpp
                ./client_src/graphics/texture_manager.cpp
                ./client_src/DTO/common_objeto.cpp
                ./graphics_editor/mainwindow.cpp
	            ./graphics_editor/assets/resources.qrc
                ./graphics_editor/assets/resources.qrc
                ./graphics_editor/createpopup.cpp
                ./graphics_editor/joinpopup.cpp
                ./client_src/client_editor.cpp
                ./client_src/configuracion_mapa.cpp
  
                ${UIS_HEADERS}

         
                
    )

    target_include_directories(client PUBLIC
    ${PROJECT_SOURCE_DIR}/libs/SDL2pp
    ${PROJECT_SOURCE_DIR}/libs/yaml-cpp
)    


target_link_libraries(client PUBLIC
    Qt5::Widgets
    Qt5::Core
    SDL2pp
    yaml-cpp
)

    find_package(Qt5 COMPONENTS Widgets REQUIRED)
  
    