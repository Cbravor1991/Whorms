#include <iostream>
#include <fstream>
#include <vector>
#include <netinet/in.h>
#include <sstream>
#include <algorithm>
#include "client_protocol.h"
#include "client.h"
#include <tuple>
#include <thread>

Cliente::Cliente(const std::string &hostname,
                 const std::string &servname) : hostname(hostname),
                                                servname(servname),
                                                protocolo(hostname, servname)

{
}

void Cliente::run()
{
    ClienteLanzador cliente_lanzador(protocolo, queue_sender, queue_receiver);
    cliente_lanzador.start();
    while (protocolo.check_en_conexion())
    {
        StateGame estado = queue_receiver.pop();
        int tipo_mensaje = estado.obtener_tipo_mensaje();
        
        if(tipo_mensaje == TIPO_TURNO ) {
            
            if(estado.obtener_turno() ){
                 std::cout << "ES TU TURNO" << '\n';

            }
            else{
                std::cout << "NO ES TU TURNO " << std::endl;
            } 
            
                   cliente_lanzador.autorizar_turno(estado.obtener_turno());
        }

        if(tipo_mensaje== TIPO_JUGADOR){
             std::vector<JugadorDTO> jugadores_dto = estado.obtener_jugador();

               for ( JugadorDTO& jugador_dto : jugadores_dto) {
         std::cout << "Jugador " << jugador_dto.obtener_id() << " en coordenadas"
                      << " X: " << jugador_dto.obtener_posicion_x() << " Y: " << jugador_dto.obtener_posicion_y() << std::endl;
    }
            
            
        }

        if(tipo_mensaje == TIPO_VIGA){
            std::vector<VigasDTO> vigas = estado.obtener_viga();

    for ( VigasDTO& viga : vigas) {
        std::cout << "Viga " << viga.obtener_tipo() << " en coordenadas"
                  << " X: " << viga.obtener_posicion_x() << " Y: " << viga.obtener_posicion_y() << std::endl;
    }
        }
        

            
         
        
    }
    // std::this_thread::sleep_for(std::chrono::seconds(5));
    cliente_lanzador.join();
}

void Cliente::cargar_id_jugador(uint8_t id)
{
    id = id;
}
uint8_t Cliente::obtener_id_jugador()
{
    return id;
};



