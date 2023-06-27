# Lobby - Graficos

La parte gráfica del lobby fue diseñada con Qt5 (Qt version 5.15.3). Esto se decidió de esta forma ya que nos daba mas facilidades a la hora de crear el lobby que haciendolo con SDL ya que no involucraba animaciones.

Para la implementación del mismo se uso QtCreator que nos permitia diseñar las ventanas mediante un drag & drop. 

Se impelemento una ventana principal, MainWindow que aloja todas las opciones disponibles como puede ser:
* Crear una partida
* Unirse a una partida
* Salir del juego
* Comenzar una partida

Al iniciar el juego vemos que el el boton de Start es encuentra deshabilitado ya que no nos encontramos en ninguna partida.

Dentro de las opciones para crear un escenario o unirse a uno ya creado se implemento un QDialog que funcionara como una ventana PopUp donde cada una tendra sus campos correspondientes para realizar la operación que se desee, ya sea crear una partida o unirse a una. Dentro de la misma la opcion de seleccionar un soldado se encuentra deshabilitada hasta que uno no se una a una partida. Una vez que uno este asociado a una partida podra pasar a la siguiente ventana que es otro QDialog donde podrá seleccionar con que arma quiere jugar. A partir de aca como ya esta asociada una partida el comportamiento por defecto es que usará un arma IDF. Caso contrario puede elegir entre las 3 armas que se proporciona. 

Algo a aclarar es que una vez que se haya unido a una partida el usuario no podra unirse a otra. Si desea crear una partida o unirse a otra el lobby le mostrara un cartel indicandole que no puede unirse a otra partida. Si lo desea deberá cerrar el lobby e iniciar nuevamente. Esto es así por motivos de implementación del lado del servidor.
