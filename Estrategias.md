
# Estrategias

Para este proyecto decidimos usar las estructuras de **pila**, **lista** y **cola**.

## Utilización de las estructuras en el proyecto [DOCE]:

- **Mazo** (`lista simple`):  
  Se podría pensar inicialmente que el mazo sería mejor representado como una **pila**, pero la mejor opción para desordenarlo (mezclarlo) es usar una **lista simple**.

- **Manos de los jugadores** (`lista simple`):  
  Tanto el jugador como el bot deben poder elegir cualquier carta de su mano. Esto se puede realizar usando una **lista simple**, lo cual permite recorrer (ver cartas en mano), insertar o eliminar en cualquier posición.

- **Registro de jugadas** (`cola`):  
  Como se van guardando en orden, necesitaremos un seguimiento (puntero) para saber el primer registro de jugada y guardarlo en un archivo `.txt`. Para esto, la mejor opción sería una **cola** por su forma de inserción y lectura **FIFO**.

- **Descarte** (`pila`):  
  En el descarte nos interesa saber cuál es la carta que está en el tope. Una **pila** es más que suficiente por ser **LIFO**.
