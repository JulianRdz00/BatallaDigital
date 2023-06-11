#include <iostream>
#include <random>

#include "Constantes.hpp"
#include "Juego.hpp"

int main()
{

    srand((unsigned)time(NULL));
    Coordenada puntoMasLejano = Coordenada(10, 10, 10);

    Juego *batallaDigital = new Juego();

    while (batallaDigital->partidaEnCurso()) // lista de jugadores
    {
        batallaDigital->

                Jugador *jugador = getNodo(); // lista de jugadores
        ejecutarTurno(jugador);
    }

    // lista con un solo nodo que tiene el jugador ganador
    Judagor *jugadorGanador = getNodo(); // lista de jugadores

    // cout mensaje del ganador

    return 0;
}