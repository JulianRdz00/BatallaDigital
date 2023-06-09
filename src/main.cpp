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



    return 0;
}