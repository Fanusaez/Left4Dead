# Código (4/5)
## Cliente
* **(P2)** La función main del cliente denota una falta de encapsulamiento. Hay mucho codigo suelto ahí.
* **(P1)** En el hilo sender y receiver del cliente hay unos bloques try-catch que catchean la cola cerrada, pero no abortan la ejecución. Por como estás operando hoy en día en el client (que primero hacés un shutdown del socket), no pasaría nada. Pero si en algún refactor cambiás el orden de operaciones, podrías llegar a mandar mensajes al server con un estado indefinido (en realidad, enviarías el último mensaje varias veces). Para evitar esto, en el hilo sender y receiver podrías hacer lo siguiente

```cpp
void ClientSender::run() {
    bool was_closed = false;
    std::vector<char> bytes;
    try {
    	while (!was_closed  && keep_talking){
            bytes = queue_sender->pop();   
        	socket->sendall(bytes.data(), bytes.size(), &was_closed);
    	}
    } catch (const ClosedQueue& e){
        std::cout<<"Se cerro la cola correctamente"<<std::endl;
    }
    keep_talking = false;
}
```
* **(P4)** En vez de tener un hilo para lobby sender y lobby receiver y luego otros dos hilos para enviar y recibir en el juego, podrías haber tenido 2 hilos y que envien y reciban en función de un booleano atomico que diga en qué estado está. 
* **(P4)** Hay un par de pasajes por copias de vectores que podrían degradarte la performance (no le daría importancia porque lo probé bastante al cliente y no detecté un gran consumo de CPU)


## Server
* **(P2)** El hilo main del server no tiene un bloque try catch que te pueda salvar ante excepciones que se puedan lanzar (por ejemplo en el shutdown del socket).

# Documentación (2/5)
* El manual de usuario es correcto (le podrían agregar imagenes para hacerlo mas amigable al usuario). Faltaría el manual de proyecto y tecnico.

# UX/Jugabilidad (4/5)
* **(P1)** Si un zombie te ataca, tenés una muerte asegurada. No podés salir de la cadena de golpes del zombie. Podrían ajustarle el tiempo entre ataques al zombie para que el jugador pueda moverse y salir del ataque.
* **(P2)** Se adjunta una captura donde se puede ver un frame del juego en el que se renderiza a unos zombies en el aire. Esto puede deberse a variables no inicializadas en el cliente.


# Robustez / Valgrind (todo prioridad P0) (3/5)
* Abro dos clientes, juego un rato en la partida y matan a los dos personajes. Si dejo la partida correr un tiempo, de repente
uno de los clientes se vuelve loco y spawnea 2 soldados en estado disparar infinito. Creo esto se debe a la cantidad de zombies que habia en el mapa, podría haber un overflow en algún contenedor.

* arranco una partida, dejo que mueran el/los clientes. Si quiero joinearme a esa partida nuevamente, el cliente que se joinea, se queda colgado después del start.

* Se corrió valgrind con el server y no se detectó ningún leak o invalid read, buen trabajo!
* En el cliente se encontraron un par de invalid reads y algunos leaks de memoria corriendo valgrind. Se adjunta un log en la carpeta `valgrind_logs` con la trazada de valgrind. Este valgrind se corrió usando un archivo de supresión para quitar ruido de falsos positivos (y aun así sigue reportando falsos positivos). Mirar la traza y corregir los errores que son de codigo de ustedes.

Para generar un archivo de supresión (que dependerá del hardware de cada uno), se puede usar el ejemplo del [ejecutable sdlpp-events de este branch](https://github.com/Taller-de-Programacion/clases/tree/valgrind_supp_file_example/bibliotecas-gui/sdlpp). Para hacer un archivo de supresión, se debe correr el programa de SDL con valgrind, con los flags `--gen-suppressions=all --log-file=supp.txt` además de los clásicos `--leak-check=full --leak-resolution=high --show-leak-kinds=all --show-reachable=yes --track-fds=yes --track-origins=yes`

Una vez armado el archivo de supresión, queda eliminarle el ruido, para eso correr este script 

```python
#!/usr/bin/python3

# quick&dirty script para sacar los pids del log de valgrind
# para generar un file de supresiones

import sys
import re
import fileinput

try:
    if len(sys.argv) != 2:
        raise ValueError(f"Usage: {sys.argv[0]} <Filepath>")

    filename = sys.argv[1]
    for line in fileinput.input(filename, inplace = True):
       if not re.search('==[0-9]+==.*', line):
          print(line, end="")
except Exception as e:
    print(f"Error: {e}")
    print("Input a valid valgrind log file")
```
Es **importantisimo** que el archivo de supresión se genere usando un programa que sabés no leakea, ya que sino vas a silenciar leaks verdaderos. Por eso recomiendo que uses el ejecutable del branch mencionado, que renderiza texto, reproduce música y carga texturas).



# Performance (5/5)
Buen trabajo en la performance!!

# Instalación (3/5)
- El juego se puede compilar sin ningún problema
- [ ] **(P3)** No hay instalador. Los paths a los assets debería ser variable en función de si estás ejecutandoló en modo desarrollo (paths locales) o si estás en producción (`/usr/bin/` para los ejecutables, `/var/left4dead/` para las configuraciones). Pueden usar CMake Para definir una macro de compilación (ver `add_compile_definitions`) y en donde quieran
cargar assets (o archivo de configuración) hacer concatenar strings

```cpp
std::string filepath = CONFIG_BASE_PATH "/server/config.yaml"
```

# Features (2/5)
## Zombies
### Infectados
- [ ] Caminan o permanecen quietos si no son molestados
	* **(P3)** Me da la impresión que desde que spawnean te persiguen no importa lo lejos que estés. Se le podría agregar un rango de visión
- [x] Cuando el jugador esté en el rango de vision los persigue 
- [x] golpe con mordidas o golpes

### Jumper
- [ ] Salta sobre sus victimas
	* **(P1)** No pareciera que salten al jugador. Los vi correr, y la animación previa al salto la usaron para cuando recibe daño.

- [ ] produce daño cuando cae sobre las victimas
	* **(P1)** No se pudo probar
- [ ] salto tiene animación previa de aviso
	* **(P1)** La animación la usaron para cuando recibe daño parece

### Witch
- [ ] **(P0)** ocasionalmente grita para atraer infectados

### Spear
- [ ] **(P2)** usan armas como lanzas

### Venom
- [ ] **(P1)** ataque a distancia
- [ ] **(P1)** daña a todo jugador que esté en contacto con el ataque

## Jugador
- [x] Munición infinita
- [x] Tiempo de recarga 
- [ ] **(P1)** Todos salvo P90 pueden lanzar granadas explosivas y de humo


### IDF
- [ ] **(P2)** rafaga de 20 balas 
	* La rafaga es infinita, no hay tiempo muerto entre rafagas si mantengo apretado la tecla disparar
- [ ] **(P1)** daño a corta distancia alto
	* no pudo apreciarse este feature dado que no hay una barra de vida en los zombies. Capaz el feature está implementado
	pero no se puede ver

- [ ] daño menor a larga distancia
	* No se pudo notar el feature
- [x] Recarga cada 50 rafagas

### P90

- [ ] **(P2)** rafagas de 10 balas
- [ ] **(P0)** daño no reducido a largas distancias
- [ ] **(P0)** recarga cada 30 rafagas

### Scout
- [ ] **(P0)** Rifle de 1 bala
- [ ] **(P0)** Atraviesa infectados
- [ ] **(P1)** Daño se reduce por cada impacto entre infectados
- [ ] **(P0)** recarga cada 20 bbalas


## Granadas
- [ ] **(P0)** Son infinitas
- [ ] **(P0)** hay un tiempo de espera entre lanzamientos
- [ ] **(P0)** explosiva: daña enemigos en la zona. Daña a jugadores aliados también
- [ ] **(P2)** humo: no producen daño. Los infectados quedan aturdidos y dejan de correr y saltar, siguen caminando

## Bombardeo aereo
- [ ] **(P1)** Solo P90 puede invocarlo
- [ ] **(P1)** caen granadas por todo el escenario salvo la zona cercana al jugador
- [ ] **(P1)** tiempo de espera entre bombardeos mayor

## Vida
- [x] Los jugadores tienen vida.
- [ ] Los zombies tienen vida.
	* **(P0)** El feature está claramente, pero faltaría mostrarlo. Agregandolé una barra de vida por encima del zombie ayudaría a probar el tema de los daños a larga y corta distancia, y el futuro daño en area de las explosiones
- [ ] **(P3)** Cuando llega a cero son derribados
	* No pareciera estar el concepto de "derribo", cuando el jugador llega a vida 0, muere instantaneamente
- [ ] **(P3)** Los jugadores derribados pueden recibir asistencia por otro jugador y seguir jugando
- [ ] **(P3)** el jugador recuperado se levanta con mitad de vida
- [ ] **(P3)** a los 3 derribos muere inmediatamente.
- [x] Si jugador derribado no es asistido, muere

## Ataque y colisiones
- [x] soldados y zombies pueden colisionar
- [x] hay un hitbox para detectar zombies en el eje y


## Escenario
- [ ] **(P4)** los crateres son zona por la que no podés caminar
	* se puede caminar por sobre los cráteres
- [x] hay una camara que sigue al jugador
- [x] Te podés mover a los costados
- [x] Hay una ilusion de paralaje

## Modos de juego
### Clear the zone
- [ ] **(P0)** cantidad fija de zombies. Jugador gana cuando elimina a todos

### Survival
- [x] Cantidad infinita de zombies.
- [ ] **(P2)** cada vez se hacen mas fuertes, resistentes y veloces
	* No se puede apreciar el feature
- [ ] **(P0)** termina cuando jugadores mueren
	* Falta pantalla de finalización de partida

## Fin de partida
- [ ] **(P0)** se muestra estadisticas de juego (cantidad de eliminados, balas disparadas, tiempo de partida)
- [ ] **(P1)** En modo survival las estadisticas se guardan y se muestra un ranking historico (1 ranking por cada estadistica) que se muestra al final del modo

## Interfaz gráfica
- [x] Se muestra la vida de cada soldado
- [x] Se muestra las rafagas restantes antes de recargar
- [ ] **(P1)**Se muestra tiempo restante para lanzar granada
- [ ] **(P3)** Se muestra balas disparadas
- [ ] **(P1)** Se muestra infectados eliminados
- [ ] **(P0)** Se muestra tiempo transcurrido
## Controles
- [x] se controla via teclado
- [ ] **(P1)** Recarga automatica (cuando te quedás sin balas)
- [x] Recarga manual (mediante botón de recarga)
- [ ] **(P1)** distancia de lanzado de granada depende de cuanto tiempo se mantiene presionado la tecla
- [ ] **(P1)** Si mantenés mucho tiempo presionado la tecla de lanzar granada, explota en la mano


## sonidos
- [x] cuando hay disparo
- [ ] cuando hay expĺosion

## Musica
- [x] Buen groove de la musica
## Animaciones
- [x] Muy buenas animaciones!!

## Configuraciones
- [ ] **(P0)** No veo configuraciones en ningún lado
## Cheat
- [ ] **(P4)** No hay cheats

## Tests
- [x] Muy buena cobertura de tests!!

# Cliente - Servidor (5/5)

# Extras
No hay