# Left4Dead

## Compilación

### Dependencias

* SDL2 (desarrollado con la version 2.26.5)
* SDL2_image, SDL2_mixer y SDL2_ttf
* Qt5 (desarrollado con la version 5.15.3)

### Comandos

Desde el root del proyecto:

`mkdir build`

`cd build`

`cmake .. & make`

Esto generará dos binarios: el cliente y el servidor.

### Instalación

Para instalar los programas localmente, correr el script installer.sh y seguir las instrucciones.

`bash installer.sh`

Este instalará los binarios en _/usr/local/bin_, las bibliotecas en _/usr/local/lib_ 
y los assets en _/var/games/l4d_.

También se puede desinstalar mediante este mismo script.

[Instalador de referencia](https://github.com/brunograssano/SuperMarioBros-Honguitos/blob/master/Instalador.sh)

## Ejecución

Para correr el juego se tiene que ejecutar primero el servidor:
* `./l4dserver <puerto>`
El servidor se cierra apretando q

Luego se ejecuta la ccantidad de clientes que se quiera de la siguiente forma:
* `./l4dclient localhost <puerto>`

Dentro del lobby se podran ejecutar las siguientes instrucciones:
* Create Game: para crear una partida
* Join Game: para unirse a una partida
* Exit

Dentro del create game se nos pedira una cantidad maxima de jugadores para la partida. Esta cantidad será un numero entre 1 y 4. Por otro lado también se nos pedirá que ingresemos un modo de juego de los disponibles, entre ellos tenemos: modo survival o clear the zone. Por último se pide que ingresemos un nombre con el que identificaremos el mapa creado 

Una vez hecha una alguna petición de estas el servidor nos responderá con indicando si se pudo crear o no una partida o si se pudo o no unir a la misma. Al crear una partida el servidor nos dirá el codigo con el que se creo para que los demas jugadores se puedan unir. Una vez seguido todos estos pasos se aprieta el boton *crear*. Si es posible la creación del mapa se nos indicará que se pudo crear y cual es el código de la partida para que lo podamos compartir y que las personas se puedan unir a nuestra partida. Cuando se crea la partida veremos como se habilita el boton de seleccionar soldado.

En esta etapa seleccionaremos con que soldado (o arma) queremos jugar. Una vez seleccionado el soldado y apretado el boton *seleccionar* volveremos a la pantalla principal donde ya se nos habilito el boton para *start* para comenzar a jugar. En el caso de que estemos nosotros en la partida el juego comenzara. Si hay mas integrantes en la partida pero todavía no pusieron start vamos a tener que esperar que los demas pongan *start* para comenzar a jugar.

La logica a la hora de unirnos a un juego es bastante similar. Al presionar *join game* se nos abrirá una ventana muy parecida a la de create donde se nos pedirá que ingresemos un código de partida (ese que se comparte cuando creas la partida!). Si la partida se encuentra se nos indicará que nos pudimos unir exitosamente a la partida y podemos pasar a seleccionar el soldado como comentamos anteriormente.

Una vez que finaliza el juego ya sea por muerte (en modo survival) o por que ganaron se nos presentará una pantalla de estadisticas. Si quisieramos volver a jugar habría que cerrar el juego y volver a iniciarlo.

Para cerrar el servidor hay que ingresar la letra `q` y para salir del juego alcanza con cerrar la ventana del juego.

![lobby](https://github.com/Fanusaez/Left4Dead/assets/79915723/892d6dd3-6d2b-466f-afbc-95df2e6bba83)

### Ejemplo de ejecucion
Jugador 1:
```
>  ./l4dclient localhost 8080
```

Jugador 2:
```
>  ./l4dclient localhost 8080
```

Servidor:
```
>  ./servidor 8080
```
https://github.com/Fanusaez/Left4Dead/assets/79915723/7fb519e6-87a2-4e8c-a66b-25731ecae496

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
