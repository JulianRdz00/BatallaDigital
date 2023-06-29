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
        std::cout << "El ganador de la partida es el jugador: " << batallaDigital->obtenerGanador()->getId() << std::endl;
        break;
    }

    delete batallaDigital;

    return 0;
}