#include <iostream>
#include <random>

#include "Constantes.hpp"
#include "Juego.hpp"

int main()
{

    srand((unsigned)time(NULL));
    Juego *batallaDigital = new Juego();
    reiniciarCursor();
    while (avanzarCursor())//lista de jugadores
    {
        Jugador* jugador = getNodo();//lista de jugadores
        ejecutarTurno(jugador);
    }

    // lista con un solo nodo que tiene el jugador ganador
    Judagor* jugadorGanador = getNodo();//lista de jugadores

    //cout mensaje del ganador

    return 0;
}