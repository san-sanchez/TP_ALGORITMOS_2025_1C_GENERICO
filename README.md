# DoCe - Juego de Cartas
![logoDoCe.png](https://i.postimg.cc/R02mvScD/logoDoCe.png)

DoCe es un juego de cartas simple pero estratégico, pensado para ser jugado entre una persona y una inteligencia artificial. El objetivo es ser el primer jugador en alcanzar 12 puntos usando cartas con distintos efectos. 
 - ---
## ❓ Cómo jugar
Al iniciar el programa, se mostrará un menú:

```---- DoCe ----```

```[A] Jugar```

```[B] Ver ranking```

```[C] Salir```


### 🕹️Iniciar partida
1. Elige la opcion [A] Jugar

2. Ingresá tu nombre.

3. Elegí el nivel de dificultad de la IA:

    - **Fácil**: juega al azar.

    - **Medio**: evita jugadas inútiles.

    - **Difícil**: analiza el estado del juego para jugar estratégicamente.

## 📄 Reglas del juego
 - Ambos jugadores comienzan con 0 puntos y 3 cartas en la mano.

 - El juego se juega por turnos.

#### En cada turno:

 - Jugás una carta de tu mano.

 - Robás una nueva carta del mazo (si hay disponible).

 - Gana quien llegue primero a 12 puntos.

 - Los puntos no pueden ser negativos.

 - Si el mazo se termina, se mezcla el descarte para formar un nuevo mazo.

## 🃏 Tipos de cartas
Carta|Efecto
:-----:|:-----:
+1  |Suma 1 punto al jugador
+2	|Suma 2 puntos al jugador
-1	|Resta 1 punto al oponente (si tiene)
-2	|Resta 2 puntos al oponente (si tiene)
Repetir	|El jugador juega inmediatamente otro turno
Espejo	|Anula un efecto negativo anterior y lo refleja

## 🏁 Fin del juego
Cuando un jugador alcanza 12 puntos:

- El juego finaliza.

- Se guarda un informe con:

    - Nombre del jugador
    - Cartas jugadas
    - Puntos de cada uno
    - Quién ganó
----
## ⚙️ Configuración del juego
Para cambiar la configuración de juego o la dificultad de la IA, se pueden modificar algunas macros del codigo fuente. Estas macros se encuentran en `funciones.h`

- **`PUNTOS_MAX`**: Define la cantidad de puntos necesarios para ganar la partida.

- **`CERCA_GANAR`**: Establece la cantidad de puntos que se consideran para estar “cerca de ganar”. 
    -	En la **dificultad media**, la IA prioriza cartas que suman puntos si alcanza esa cantidad de puntos.
    -	En la **dificultad difícil**, la IA prioriza cartas que restan puntos si el jugador alcanza esa cantidad de puntos.
  
 - **`CARTAS_BUENAS`**: Establece la cantidad de cartas buenas que debe tener la IA en la dificultad difícil para priorizar la cata **repetir turno**.

Se pueden modificar dichos valores para que la experiencia de juego sea más desafiante o más relajada según prefieras.
