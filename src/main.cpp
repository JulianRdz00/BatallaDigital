#include <iostream>
#include <random>

#include "Constantes.hpp"
#include "Juego.hpp"
// PRE: La respuesta introducida por consola debe ser un numero.
// POST: Pregunta por consola que se introduzca un numero entero positivo, continuara preguntando hasta que la respuesta sea valida
int preguntarEnteroPositivo(std::string pregunta){
    int variable=0;
    while(variable < 1){
        std::cout << pregunta << std::endl;
        std::cout << "Debe ser un numero positivo" << std::endl;
        std::cin << variable;
    }
    return variable;
}


//Post devuelve un puntero a un Juego con unos parametros elejidos por el usuario.
Juego* inicializarPartida(){
    int ancho = preguntarEnteroPositivo("ingrese el Ancho del tablero.");
    int largo = preguntarEnteroPositivo("ingrese el Ancho del tablero.");
    int alto = preguntarEnteroPositivo("ingrese el Ancho del tablero.");

    int cantidadJugadores = preguntarEnteroPositivo("ingrese la cantidad de jugadores.");
    int cantidadSoldadosPorJugador = preguntarEnteroPositivo("ingrese la cantidad de soldados iniciales para cada jugador.");

    Juego* partida = new Juego(ancho, largo, alto, cantidadJugadores, cantidadSoldadosPorJugador);
}


int main()
{

    srand((unsigned)time(NULL));




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