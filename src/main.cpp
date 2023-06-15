#include <iostream>
#include <random>

#include "Constantes.hpp"
#include "Juego.hpp"


int main()
{

    srand((unsigned)time(NULL));

    Juego *batallaDigital = new Juego();

    while (batallaDigital->avanzarTurno()) // lista de jugadores
    {
        batallaDigital->actualizarImagenes();
        batallaDigital->ejecutarTurno();
    }

    EstadoPartida resultado = batallaDigital->obtenerResultado();

    switch (resultado)
    {
    case EMPATE:
        std::cout << "Hubo un empate\n";
    case TERMINADA:
    std:
        std::cout << "Hay un ganador!\n";
    }

    return 0;
}