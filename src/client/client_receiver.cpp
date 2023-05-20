#include "client_receiver.h"

#include <iostream>
#include <vector>
#include <string>

#include <arpa/inet.h>

ClientReceiver::ClientReceiver(Socket *socket, std::atomic<bool> &keep_talking,Queue<GameDTO> *queue_receiver) : 
    socket(socket), keep_talking(keep_talking), queue_receiver(queue_receiver){}

void ClientReceiver::run() {
    bool was_closed = false;
    std::vector<char> bytes;
    GameDTO game_dto;
    while (!was_closed && keep_talking) {
        int size_game_dto;
        socket->recvall(&size_game_dto, 1, &was_closed);
        uint16_t position_x;   // Coordenada X de la posición
        uint16_t position_y;   // Coordenada Y de la posición
        GameObjectState state; // Estado del objeto
        for(int i = 0; i < size_game_dto ; i++){
            socket->recvall(&state, 1, &was_closed);
            socket->recvall(&position_x, 2, &was_closed);
            socket->recvall(&position_y, 2, &was_closed);
            game_dto.add_object(GameObjectDTO(1,position_x,position_y,state));
        }
        // deserializar a game_dto
        queue_receiver->push(game_dto); //Podemos pasarle los bytes o generar una estructura
    }
}