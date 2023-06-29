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

    EstadoPartida resultado = batallaDigital->obtenerResultado();

    switch (resultado)
    {
    case EMPATE:
        std::cout << "Hubo un empate\n";
        break;
    case TERMINADA:
        std::cout << "Hay un ganador!\n";
        break;
    }

    return 0;
}