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

Una vez hecha una alguna petición de estas el servidor nos responderá con indicando si se pudo crear o no una partida o si se pudo o no unir a la misma. Al crear una partida el servidor nos dirá el codigo con el que se creo para que los demas jugadores se puedan unir.

Cuando se quiera inciar el juego se ejecuta `start` y es necesario que el usuario este asociado a alguna partida, sino nos lanzará error. Una vez que ejecutamos `start` veremos que se inicializa el mapa pero el servidor esperara a que todos los usuarios en esa partida manden `start` para comenzar el juego. 

Para cerrar el servidor hay que ingresar la letra `q` y para salir del juego alcanza con cerrar la ventana del juego.

![lobby](https://github.com/Fanusaez/Left4Dead/assets/79915723/892d6dd3-6d2b-466f-afbc-95df2e6bba83)

### Ejemplo de ejecucion
Jugador 1:
```
>  ./l4dclient localhost 8080
>  create map
>  Partida creada. El codigo es: 0
>  start
>  start playing
```

Jugador 2:
```
>  ./l4dclient localhost 8080
>  join 0
>  Te has unido a una partida
>  start
>  start playing
```

Servidor:
```
>  ./servidor 8080
>  Nuevo jugador
>  Nuevo jugador
```

## Instrucciones de juego

Los comandos para jugar al juego son los siguientes:

* Flecha `→`: mueve el jugador hacia la derecha
* Flecha `↑`: mueve el jugador hacia arriba
* Flecha `↓`: mueve el jugador hacia abajo
* Flecha `←`: mueve el jugador hacia la izquierda 
* Letra `S`: para disparar
* Letra `R`: para recargar
* Letra `Q`: para tirar granada explosiva
* Letra `W`: para tirar granada de humo
* Letra `A`: para llamar ataque aereo
* Letra `E`: para revivir un compañero
* Letra `P`: para pausar la musica
* Letra `O`: para renaudar la musica
* Tecla `-`: para bajar el volumen
* Tecla `+`: para subir el volumen 

## Testing

Para correr tests, incluir el argumento `-DTESTING=ON` al invocar cmake. Ejemplo: `cmake -DTESTING=ON <PROJECT_ROOT_DIRECTORY> -B <BUILD_DIRECTORY>`

Luego correr `cmake --build <BUILD_DIRECTORY> --target test`

Ver README en **`test/`** para más info.
