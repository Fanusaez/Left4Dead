#ifndef LOBBYDESERIALIZER_H
#define LOBBYDESERIALIZER_H

#include "../common/instructions_dto.h"
#include "../common/socket.h"

#include <vector>
#include <string>

class LobbyDeserializer
{
private:
    Socket *socket;

public:
    LobbyDeserializer(Socket *socket);

    InstructionsDTO obtener_instruccion(bool *was_closed);

    /*----------------------Lobby message--------------------*/

    InstructionsDTO deserialize_create_scenario(bool *was_closed);

    InstructionsDTO deserialize_join_scenario(bool *was_closed);
    
    InstructionsDTO deserialize_game_list(bool *was_closed);

    InstructionsDTO deserialize_start_game(bool *was_closed);
    
};
#endif
