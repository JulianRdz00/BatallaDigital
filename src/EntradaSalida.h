#ifndef ENTRADASALIDA_H
#define ENTRADASALIDA_H

#include <iostream>
#include "Jugador.h"

class EntradaSalida
{
public:
    /*  POS: devuelve el valor de la coordenada ingresada por consola */
    Coordenada *pedirCoordenada();

    /*  POS: */
    EntradaSalida();

    //POS: pregunta que soldado se desea mover y devuelve la coordenada cuyo nombre es nombreCoordenada
    Coordenada *coordenadaSoldadoExistente();

    Coordenada *preguntarDondeMoverUnidad();

    Coordenada *preguntarUnidadAMover(Jugador *jugador);

    /*  POS: pregunta a donde quiere colocar una mina y devuelve la coordenada cuyo nombre es nombreCoordenada*/
    Coordenada *preguntarDondeColocarMina();

    /*  POS: devuelve un string con el nombre de la carta a jugar y en caso de no jugar carta devuelve 0
    REVISAR lista de cartas mano (const) */
    bool preguntarSiUsarCarta(Jugador *jugador);

    void listarCartas(Jugador *jugador);

    /*  POS: Devuelve el indice de la carta a jugar. */
    unsigned int elejirCartaParaJugar(Jugador *jugador);

    /*  PRE: La respuesta introducida por consola debe ser un numero.
        POS: Pregunta por consola que se introduzca un numero entero positivo, continuara preguntando hasta que la respuesta sea valida */
    int preguntarEnteroPositivo(std::string pregunta);

    /*  POS: devuelve un puntero a un Juego con unos parametros elejidos por el usuario. */
    void inicializarPartida(int &ancho, int &largo, int &alto, int &cantidadJugadores, int &soldadosPorJugador);

    ~EntradaSalida();
};

#endif