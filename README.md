# Left4Dead

## Instalación

### Dependencias

* SDL2 (desarrollado con la version 2.26.5)
* SDL2_image y SDL2_mixer

### Comandos

Desde el root del proyecto:

`mkdir build`

`cd build`

`cmake .. & make`

Esto generará dos binarios: el cliente y el servidor.

## Ejecución

Para correr el juego se tiene que ejecutar primero el servidor:
* `./server <puerto>`
El servidor se cierra apretando q

Luego se ejecuta la ccantidad de clientes que se quiera de la siguiente forma:
* `./l4dclient localhost <puerto>`

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