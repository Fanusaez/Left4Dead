#ifndef LOBBYDESERIALIZER_H
#define LOBBYDESERIALIZER_H

#include "../common/instructionsDTO/instructions_dto.h"
#include "../common/instructionsDTO/create_dto.h"
#include "../common/instructionsDTO/join_dto.h"
#include "../common/instructionsDTO/start_dto.h"
#include "../common/socket.h"

#include <vector>
#include <string>

class LobbyDeserializer
{
private:
    Socket *socket;

public:
    explicit LobbyDeserializer(Socket *socket);

    InstructionsDTO* obtener_instruccion(bool *was_closed);

    /*----------------------Lobby message--------------------*/

    CreateDTO* deserialize_create_scenario(bool *was_closed);

    JoinDTO* deserialize_join_scenario(bool *was_closed);
    
    InstructionsDTO* deserialize_game_list(bool *was_closed);

    StartDTO* deserialize_start_game(bool *was_closed);    
};
#endif
