#ifndef CLIENTDESERIALIZER_H
#define CLIENTDESERIALIZER_H

#include "../common/instructions.h"
#include "../common/game_dto.h"
#include "../common/socket.h"

#include <vector>
#include <string>

class ClientDeserializer
{
private:
    Socket *socket;

public:
    ClientDeserializer(Socket *socket);

    Instructions obtener_instruccion(bool *was_closed);

    /*----------------------Lobby message--------------------*/

    int32_t deserialize_create_scenario(bool *was_closed);

    bool deserialize_join_scenario(bool *was_closed);

    /*----------------------Game message--------------------*/

    GameDTO deserialize_game_dto(bool *was_closed);
};
#endif
