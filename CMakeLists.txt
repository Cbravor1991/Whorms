cmake_minimum_required(VERSION 3.16)

project(Worms
    DESCRIPTION "TP de Taller de Programación 1 2c2023 FIUBA"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED YES)


add_definitions(-DDATA_PATH="${PROJECT_SOURCE_DIR}/data")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -pedantic-errors -O0 -ggdb -DDEBUG -fno-inline -D _POSIX_C_SOURCE=200809L -pthread")

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/box2d-2.4.0 ${CMAKE_SOURCE_DIR}/build/libs/box2d-2.4.0)

	add_executable(server 
                ./server_src/server.cpp
                ./server_src/escenario.cpp 
                ./server_src/lobby.cpp 
                ./server_src/monitor_jugador.cpp 
                ./server_src/partida.cpp 
                ./server_src/server_acceptor.cpp 
                ./server_src/server_jugador.cpp 
                ./server_src/server_lobby.cpp 
                ./server_src/server_main.cpp 
                ./server_src/server_protocol.cpp 
                ./server_src/server_receiver.cpp 
                ./server_src/server_sender.cpp 
                ./server_src/turno.cpp
                ./server_src/objeto/mundo.cpp
                ./server_src/objeto/objeto.cpp
                ./server_src/objeto/arma.cpp
                ./server_src/objeto/gusano.cpp
                ./server_src/objeto/teletransportacion.cpp
                ./server_src/objeto/ataque_aereo.cpp
                ./server_src/objeto/misil_aereo.cpp
                ./common_src/common_liberror.cpp
                ./common_src/common_resolver.cpp 
                ./common_src/common_resolvererror.cpp 
                ./common_src/common_socket.cpp 
    )

    target_include_directories(server PUBLIC ${PROJECT_SOURCE_DIR}/libs/box2d)
    target_link_libraries(server box2d)

	set(SERVER_OUTPUT_DIR ${CMAKE_BINARY_DIR})

	set_target_properties(server
			PROPERTIES
			RUNTIME_OUTPUT_DIRECTORY ${SERVER_OUTPUT_DIR})


    set(SDL2PP_WITH_IMAGE ON)
    set(SDL2PP_WITH_MIXER ON)
    set(SDL2PP_WITH_TTF ON)
    add_subdirectory(${CMAKE_SOURCE_DIR}/libs/SDL2pp ${CMAKE_SOURCE_DIR}/build/libs/SDL2pp)
    add_executable(client 
                ./client_src/client_main.cpp 
                ./client_src/client_protocol.cpp 
                ./client_src/client_receiver.cpp 
                ./client_src/client_sender.cpp 
                ./client_src/client.cpp 
                ./client_src/game.cpp
                ./client_src/graphics/view.cpp
                ./client_src/graphics/whorms.cpp
                ./client_src/graphics/path_loader.cpp
                ./client_src/graphics/texture_manager.cpp
                ./common_src/common_liberror.cpp
                ./common_src/common_resolver.cpp 
                ./common_src/common_resolvererror.cpp 
                ./common_src/common_socket.cpp 
                ./client_src/DTO/common_vigaDTO.cpp
                ./client_src/DTO/common_jugadorDTO.cpp
                ./client_src/DTO/common_objetoDTO.cpp
                ./client_src/DTO/common_escenarioDTO.cpp
                ./client_src/DTO/common_paqueteDTO.cpp
                ./client_src/DTO/common_turnoDTO.cpp
                ./client_src/DTO/common_segundosDTO.cpp
                ./client_src/DTO/common_armaDTO.cpp
    )
    target_include_directories(client PUBLIC ${PROJECT_SOURCE_DIR}/libs/SDL2pp)
    target_link_libraries(client SDL2pp)



