#include "lobby.h"
#include <cstring>
#include <sys/socket.h>

Lobby::Lobby(char *localhost, char *puerto) : socket(localhost,puerto), queue_sender(1000000), queue_receiver(1000000), keep_talking(true),
    lobby_sender(&socket,std::ref(keep_talking),&queue_sender), lobby_receiver(&socket,std::ref(keep_talking),&queue_receiver){
    bool was_closed = false;
    socket.recvall(&player_id,sizeof(int),&was_closed);
    lobby_sender.start();
    lobby_receiver.start();
}

bool Lobby::running(){
    return keep_talking;
}

bool Lobby::create_scenario(const std::string& scenario_name){
    return (queue_sender.try_push(lobby_seializer.serialize_create_scenario(scenario_name)));
}

bool Lobby::join_scenario(const int32_t& scenario_code) {
    return (queue_sender.try_push(lobby_seializer.serialize_join_scenario(scenario_code)));
}

void Lobby::start() {
    queue_sender.try_push(lobby_seializer.serialize_start_playing());
    keep_talking = false;
    queue_sender.close(); // Es correcto hacer eso?
    lobby_sender.join();
    lobby_receiver.join(); 
}

void Lobby::close() {
    keep_talking = false;
    socket.shutdown(SHUT_RDWR);
    socket.close();
    queue_sender.close(); // Es correcto hacer eso?
    lobby_sender.join();
    queue_receiver.close(); // Es correcto hacer eso?
    lobby_receiver.join(); 
}

Socket Lobby::move_socket(){
    return std::move(socket);
}

void Lobby::update(){
    int max_instructions = 0;
    InstructionsDTO instruction;
    bool could_pop = queue_receiver.try_pop(instruction);
    while (could_pop && max_instructions < 10){
        switch(instruction.get_instruction()){
            case CREATE:
                int32_t code;
                memcpy(&code, instruction.get_parameters().data(), sizeof(int32_t));
                if(code != -1)
                    std::cout<<"Partida creada con exito: "<<code<<std::endl;
                else
                    std::cout<<"Error al crear partida"<<std::endl;
                break;
            case JOIN:
                if(static_cast<bool>(instruction.get_parameters().front()))
                    std::cout<<"Te has unido a una partida"<<std::endl;
                else
                    std::cout<<"Error al unirse a una partida"<<std::endl;
                break;
                
        }
        could_pop = queue_receiver.try_pop(instruction);
        max_instructions++;
    }
}

int Lobby::get_player_id(){
    return player_id;
}