# Left4Dead

## Como ejecutar el juego

Para correr el juego se tiene que ejecutar primero el servidor:
* `./server <puerto>`
El servidor se cierra apretando q

Luego se ejecuta la ccantidad de clientes que se quiera de la siguiente forma:
* `./main_client localhost <puerto>`

Dentro del lobby se podran ejecutar las siguientes instrucciones:
* `create <nombre del escenario>`: para crear una partida
* `join <codigo del escenario>`: para unirse a una partida
* `quit`: para salir del juego
* `start`: para comenzar el juego

Como se esta usando la entrada estandar para recibir estos comandos para obtener la respuesta del servidor cuando hacemos un create o un join tenemos que apretar cualquier tecla

## Testing

Para correr tests, incluir el argumento `-DTESTING=ON` al invocar cmake. Ejemplo: `cmake -DTESTING=ON <PROJECT_ROOT_DIRECTORY> -B <BUILD_DIRECTORY>`

Luego correr `cmake --build <BUILD_DIRECTORY> --target test`

Ver README en **`test/`** para más info.