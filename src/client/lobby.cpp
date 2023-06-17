#include "lobby.h"
#include <cstring>
#include "../common/instructionsDTO/create_dto.h"
#include "../common/instructionsDTO/join_dto.h"
#include <sys/socket.h>
#include <utility>
#include <string>
#include <arpa/inet.h>

Lobby::Lobby(char *localhost, char *puerto) : socket(localhost,puerto), queue_sender(1000000), 
            queue_receiver(1000000), keep_talking(true), 
            lobby_sender(&socket,std::ref(keep_talking),&queue_sender), 
            lobby_receiver(&socket,std::ref(keep_talking),&queue_receiver){
    bool was_closed = false;
    socket.recvall(&player_id,sizeof(int),&was_closed);
    player_id = ntohl(player_id);
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
}

void Lobby::exit_lobby() {
    keep_talking = false;
    queue_sender.close();
    lobby_sender.join();
    lobby_receiver.join(); 
}

void Lobby::close() {
    keep_talking = false;
    socket.shutdown(SHUT_RDWR);
    socket.close();
    queue_sender.close();
    lobby_sender.join();
    queue_receiver.close();
    lobby_receiver.join(); 
}

Socket Lobby::move_socket(){
    return std::move(socket);
}

void Lobby::update(){
    int max_instructions = 0;
    InstructionsDTO* instruction_dto;
    //En un futuro tendra que ser asi y no deberia trabarse en un pop. Ahora lo trabamos
    //para que el usuario tenga una respuesta al instante.
    //bool could_pop = queue_receiver.try_pop(instruction_dto);
    bool could_pop = true;
    instruction_dto = queue_receiver.pop();
    while (could_pop && max_instructions < 10){
        switch (instruction_dto->get_instruction()){
            case CREATE:
                get_create(instruction_dto);
                break;
            case JOIN:
                get_join(instruction_dto);
                break;   
            case START:
                get_start(instruction_dto);
                break;             
        }
        delete instruction_dto;
        could_pop = queue_receiver.try_pop(instruction_dto);
        max_instructions++;
    }
}

void Lobby::get_create(InstructionsDTO* instruction_dto) {
    CreateDTO* create_dto = dynamic_cast<CreateDTO*>(instruction_dto);
    if (create_dto->get_game_code() != -1)
        std::cout<<"Partida creada. El codigo es: "<<create_dto->get_game_code()<<std::endl;
    else
        std::cout<<"Error al crear partida"<<std::endl;
}

void Lobby::get_join(InstructionsDTO* instruction_dto) {
    JoinDTO* join_dto = dynamic_cast<JoinDTO*>(instruction_dto);
    if (join_dto->get_could_join())
        std::cout<<"Te has unido a una partida"<<std::endl;
    else{
        std::cout<<"Error al unirse a una partida"<<std::endl;
    }
}

void Lobby::get_start(InstructionsDTO* instruction_dto) {
    StartDTO* start_dto = dynamic_cast<StartDTO*>(instruction_dto);
    if (start_dto->get_could_start()) {
        std::cout<<"Comienza la partida"<<std::endl;
        exit_lobby();
    } else {
        std::cout<<"Error al querer comenzar la partida"<<std::endl;
    }
}

int Lobby::get_player_id(){
    return player_id;
}
