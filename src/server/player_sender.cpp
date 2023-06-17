#include "player_sender.h"
#include "../common/instructionsDTO/create_dto.h"
#include "../common/instructionsDTO/join_dto.h"
#include <string>

PlayerSender::PlayerSender(Socket *socket, std::atomic<bool> &stay_in_match,  
    std::atomic<bool> &keep_playing, MatchMananger *match_mananger, int32_t& player_id) : 
    stay_in_match(stay_in_match), keep_playing(keep_playing), queue_sender(10000), 
    player_receiver(socket,stay_in_match, keep_playing, player_id),match_mananger(match_mananger),
    server_deserializer(socket), server_serializer(socket), player_id(player_id) {
    queue_receiver = nullptr;   //Al inicio es un nullptr ya que no tiene ninguna partida asociada.
    stay_in_match = true;
}

void PlayerSender::run() {
    //Le mando al cliente cual es su player_id. Esto es usa para el view main object
    server_serializer.send_player_id(player_id, &was_closed);
    while (keep_playing) {
        //Aca vamos a inicializar el receiver. Comunicación sincronico para metodos join y create.
        init_player_receiver();
        //Empezamos el loop en el que estaremos enviando los GameDTO.
        //A partir de aca el usuario ya tiene asociada una partida.
        //was_closed chequea que el socket no se haya cerrado y stay_in_match se maneja desdes Player.
        try {
            while (stay_in_match && was_closed == false) {
                GameDTO game_dto = queue_sender.pop();
                server_serializer.send_game(game_dto, &was_closed);
            }
        } catch (const ClosedQueue& e) {
            std::cout<<"Se cerro la cola correctamente"<<std::endl;
        }
        stay_in_match = false;   //En el caso de que se haya cerrado el socket pongo stay_in_match=false.
        //Si esta asociada a una partida lo elimino de la partida
        if (queue_receiver != nullptr)
            match_mananger->delete_player(player_id); //Elimino al jugador de la partida en la que estaba
    }
}

void PlayerSender::join_player_receiver(){
    //Si esta asociado a una partida es porque se lanzo el thread.
    if (queue_receiver != nullptr){
        player_receiver.join();
    }
}

void PlayerSender::close_queue() {
    queue_sender.close();
}

void PlayerSender::init_player_receiver(){
    int32_t game_code;
    // Mientras no se le asigne partida y el player quiere que siga conectado
    while (keep_playing) {
        //Usamos este try catch para chequear que no se haya perdido la conexión.
        try {
            InstructionsDTO* instruction = server_deserializer.obtener_instruccion(&was_closed,
                                                                                player_id);
            if (instruction->get_instruction() == CREATE) {
                //Casteo a un CreateDTO para obtener el nombre del escenario
                CreateDTO* create_dto = dynamic_cast<CreateDTO*>(instruction);
                std::string game_name = create_dto->get_scenario_name();
                //Le digo al match_mananger que quiero crear una partida con ese nombre.
                queue_receiver = match_mananger->create_game(&queue_sender, game_name, 
                                                                player_id, game_code);
                //Si me devuelve un puntero nulo significa que no se pudo crear la partida
                if (queue_receiver == nullptr)
                    server_serializer.send_error_create(&was_closed);
                else
                    server_serializer.send_create_scenario(game_code, &was_closed);
            } else if (instruction->get_instruction() == JOIN){
                //Casteo a un JoinDTO para obtener el codigo del escenario
                JoinDTO* join_dto = dynamic_cast<JoinDTO*>(instruction);
                game_code = join_dto->get_game_code();
                queue_receiver = match_mananger->join(&queue_sender, game_code, player_id);
                //No hace falta ejecutar un if ya que es la misma instruccion pero cambia un byte
                server_serializer.send_join_scenario((queue_receiver != nullptr), &was_closed);
            } else if (instruction->get_instruction() == START){
                //Espero a que el cliente le de start para comenzar a jugar y salir del loop
                //Le envio al cliente si puede salir del lobby.
                server_serializer.send_start_game(queue_receiver != nullptr,&was_closed);
                if (queue_receiver != nullptr) {
                    delete instruction;
                    stay_in_match = true;
                    break;
                }
            }
            delete instruction;
        }
        catch (const std::runtime_error& e) {   //Se cerro el socket
            std::cout<< e.what() << std::endl;
            stay_in_match = false;  //Si me desconecto no sigo en la partida.
            keep_playing = false;   //Y tampoco sigo en el server.
            return;
        }
    }
    //Le digo al player receiver la queueu que tiene que usar
    player_receiver.setQueueReceiver(queue_receiver);
    // Una vez que se pudo unir a una partida lanzo el player_receiver
    player_receiver.start();
}
