# Left 4 Dead - Gráficos

En este documento se va a explicar un poco como se implementaron los graficos del juego en si.

Se usó la biblioteca SDL2 (con los modulos de image, mixer y ttf). Ademas para la parte de gráficos se utilizo
la biblioteca libsdl2pp, que es un wrapper RAII de SDL2.

La vista del juego se maneja principalmente con un objeto `Gameview`. Este encapsula todo lo referente a graficos
de SDL2/libsdl2pp y provee una interfaz simple. Lleva una referencia a todos los objetos `RenderableObject` a renderizar y opcionalmente
un objeto `Scene`, que viene a ser el background. Todo esto se renderiza mediante el método `render()`.

Internamente, solo cabe destacar a la camara. Se decidio no tener un objeto camara en si, sino usar una implementacion
mas sencilla. Al gameview se le puede especificar un main object mediante el método `assignMainObject()`. Luego la vista renderizará todos los
objetos siempre centrando en la pantalla a este objeto principal.

Para los objetos, simplemente se calcula la distancia al objeto principal, y si entran en la pantalla, se los
renderiza transformando las distancias a pixeles.

Para mover el background y que se de la ilusion de movimiento se calcula un offset. Este offset es cuanto se
movio el objeto principal y se actualiza cada vez que se llama a render(). A partir de este offset las componentes
del background se renderizan corridas.