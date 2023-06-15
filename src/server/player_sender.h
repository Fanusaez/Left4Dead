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
    //Tendra un serializador para envier mensajes al cliente.
    //El serializador tendra el socket y enviara los datos.
    ServerSerializer server_serializer;

    //El hilo sender tiene que deserializar los mensajes que recibe en la parte sincronica.
    ServerDeserializer server_deserializer;
    
    //Referencia del booleano que se encuentra dentro de Player.
    std::atomic<bool>& keep_talking;

    //Usamos esta variable para el manejo del socket
    bool was_closed = false;

    // Queue de la cual vamos a sacar mensajes a enviarle a nuestro cliente
    Queue<GameDTO> queue_sender;

    // Hilo receiver. Lo tiene e PlayerSender ya que este se encargara de lanzarlo y manejarlo
    // debido a que en principio tenemos una parte sincronica.
    PlayerReceiver player_receiver;

    // Referencia a la queue que tendra el hilo Game al cual le mandamos todas las instrucciones.
    Queue<InstructionsDTO*> *queue_receiver;

    //Esta referencia es unicamente para el proceso inicial de create/join.
    MatchMananger *match_mananger;

    //Necesito del id para la creacion o union de partidas.
    int32_t player_id;

public:
    PlayerSender(Socket *socket, std::atomic<bool> &keep_talking, 
                    MatchMananger *matchMananger, int32_t& player_id);

    void run() override;

    void join_player_receiver();

    void init_player_receiver();

    void close_queue();
};
#endif
