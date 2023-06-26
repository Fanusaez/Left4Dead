# Left 4 Dead - Logica de Juego

## Estructura 

El juego está diseñado en base de una matriz de NxM en donde cada objeto del juego utiliza una posición en dicha matriz
La clase que representa esta matriz y la utiliza es la clase *GameMap*

Esta clase es responsable de:
* Detectar colisiones entre objetos, por ejemplo al momento en donde un soldado dispara, lanza una granada o simplemente camina.
* Proveer posiciones libres en donde un objeto nuevo pueda ser colocado
* Eliminar objetos obsoletos una vez se requiera

![img.png](img.png)

## Soldado

Los Soldados se diferencian en base a que arma utilizan, estos también poseen estados en los cuales se encuentran y determinan la acción que están llevando a cabo

![img_9.png](img_9.png)

Cada estado tiene su tiempo de acción, que es en lo que demora en cambiar a otro estado o permanecer en el mismo.
Los unicos estados que carecen de lo recien mencionado son *Dead* e *Idle* los cuales pueden permanecer por un tiempo indefinido en dichos estados

## Weapons

Las armas poseen diferentes características entre ellas. También se diferencian en si pueden utilizar granadas o ataques aéreos.

![img_10.png](img_10.png)

## Grenades

Las granadas explosivas y de humo poseen estados. Estos estados representan en que momento de su vida estan. 
Las mismas tienen diferentes características y efectos sobre los objetos del juego.

![img_3.png](img_3.png)

Por otra parte los estados de las granadas son circulares. Y al igual que los estados anteriores, estos tienen un tiempo en el cual se manteiene el mismo estado. Para despues pasar al siguiente.

![img_4.png](img_4.png)

## AirStrike

![img_7.png](img_7.png)

Los estados del ataque aéreo también son circulares

![img_6.png](img_6.png)

## Zombies 

En cuanto a los zombies, tenemos una variedad de 5 tipos cada uno con sus características individuales.


![img_8.png](img_8.png)


Los zombies al igual que el soldado poseen estados. Que varía según en qué situación se encuentre.


![img_11.png](img_11.png)










