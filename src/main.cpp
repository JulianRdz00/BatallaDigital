#include "Constantes.h"
#include "Juego.h"


int main()
{

    srand((unsigned)time(NULL));

    Juego *batallaDigital = new Juego();

    
    do{
        batallaDigital->actualizarImagenes();
        batallaDigital->ejecutarTurno();
    }while (batallaDigital->avanzarTurno()); // lista de jugadores

    batallaDigital->avanzarTurno();

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