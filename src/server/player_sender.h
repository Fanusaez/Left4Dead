#ifndef PLAYERESENDER_H
#define PLAYERESENDER_H

#include "../common/thread.h"
#include "../common/socket.h"
#include "../common/queue.h"

#include "player_receiver.h"
#include "server_deserializer.h"
#include "server_serializer.h"
#include "../common/instructions_type.h"

#include <atomic>
#include <vector>

class PlayerSender : public Thread{
private:
    ServerSerializer server_serializer;

    //Usamos esto para que el hilo sender serialize los mensajes que recibe en la parte sincronica
    //y para mandar los screen del juego.
    ServerDeserializer server_deserializer;
    
    //Con esta variable manejamos el ciclo while de los hilos
    std::atomic<bool>& keep_talking;

    //Usamos esta variable para el manejo del sockets
    bool was_closed = false;

    // Queue de la cual vamos a sacar mensajes a senviarle a nuestro cliente
    Queue<GameDTO> queue_sender;

    // Hilo receiver
    PlayerReceiver player_receiver;

    // Referencia a la queue que tendra el hilo de Game al cual le cargamos todo.
    Queue<InstructionsDTO*> *queue_receiver;

    //Esta referencia es unicamente para el proceso inicial de create/join
    MatchMananger *match_mananger;

    int *player_id;

public:
    PlayerSender(Socket *socket, std::atomic<bool> &keep_talking, MatchMananger *matchMananger, int *player_id);

    void run() override;

    void join_player_receiver();

    void init_player_receiver();

    void close_queue();

};
#endif
