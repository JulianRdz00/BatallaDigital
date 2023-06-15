#include <iostream>
#include <random>

#include "Constantes.hpp"
#include "Juego.hpp"
// PRE: La respuesta introducida por consola debe ser un numero.
// POST: Pregunta por consola que se introduzca un numero entero positivo, continuara preguntando hasta que la respuesta sea valida
int preguntarEnteroPositivo(std::string pregunta)
{
    int variable = 0;
    while (variable < 1)
    {
        std::cout << pregunta << std::endl;
        std::cout << "Debe ser un numero positivo" << std::endl;
        std::cin << variable;
    }
    return variable;
}

// Post devuelve un puntero a un Juego con unos parametros elejidos por el usuario.
Juego *inicializarPartida()
{
    int ancho, largo, alto, cantidadJugadores, cantidadSoldadosPorJugador;
    bool invalido = true;
    while (invalido)
    {

        int ancho = preguntarEnteroPositivo("ingrese el Ancho del tablero.");
        int largo = preguntarEnteroPositivo("ingrese el Ancho del tablero.");
        int alto = preguntarEnteroPositivo("ingrese el Ancho del tablero.");

        int cantidadJugadores = preguntarEnteroPositivo("ingrese la cantidad de jugadores.");
        int cantidadSoldadosPorJugador = preguntarEnteroPositivo("ingrese la cantidad de soldados iniciales para cada jugador.");

        int espaciosNecesarios = cantidadJugadores * cantidadSoldadosPorJugador;
        int espaciosTotales = ancho * largo * alto;

        if (espaciosNecesarios * 2 < espaciosTotales)
        {
            std::cout << "El tamanio del tablero no cumple los requisitos de tamanio para la cantidad de jugadores y soldados. \n";
        }
        else
        {
            std::cout << "Datos correctos.\n";
            invalido = false;
        }
    }
    return new Juego(ancho, largo, alto, cantidadJugadores, cantidadSoldadosPorJugador);
}

int main()
{

    srand((unsigned)time(NULL));

    Juego *batallaDigital = inicializarPartida();

    while (batallaDigital->avanzarTurno()) // lista de jugadores
    {
        batallaDigital->actualizarImagenes();
        batallaDigital->ejecutarTurno();
    }

    resultado = batallaDigital->obtenerResultado();

    switch (resultado)
    {
    case EMPATE:
        std::cout << "Hubo un empate\n";
    case GANADOR:
    std:
        cout << "Hay un ganador!\n";
    }

    return 0;
}