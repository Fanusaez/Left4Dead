#ifndef CLIENTDESERIALIZER_H
#define CLIENTDESERIALIZER_H

#include "../common/instructions_type.h"
#include "../common/game_dto.h"
#include "../common/socket.h"

#include <vector>
#include <string>

class ClientDeserializer
{
private:
    Socket *socket;

public:
    explicit ClientDeserializer(Socket *socket);

    /*----------------------Game message--------------------*/

    GameDTO deserialize_game_dto(bool *was_closed);
};
#endif
