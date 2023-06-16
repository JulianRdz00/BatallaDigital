#ifndef _JUEGO_H_
#define _JUEGO_H_

#include "Constantes.hpp"
#include "Tablero.hpp"
#include "Jugador.hpp"
#include "ListaCircular.hpp"
#include "EntradaSalida.hpp"
#include "Nodo.hpp"

class Juego
{
private:
    Tablero *mapa;
    ListaCircular<Jugador *> *jugadores;
    Nodo<Jugador *> *jugadorActivo;
    EntradaSalida *io;

    void preguntarUsoCarta();

    /*
    POS: Cambia el jugador en turno al siguiente en la lista de Jugadores
    */
    void pasarTurno();

    /*
    POS: Añade una Carta aleatoria a la Mano del jugador
    */
    void darCarta();

public:
    /*  Pre: Los valores deben ser mayores a 0.
            La cantidad de soldados por jugador * la cantidad de jugadores debe ser menor a la cantidad de casillas del tablero
            es decir, ancho * largo * alto

        POST: Inicia un Juego con la cantidad de jugadores especificada,
            con la cantidad de soldados por jugador especificada. El terreno de juego es generado
            con las dimensiones dadas.
            Si no hay suficiente espacio para ubicar a los Soldados de todos los jugadores, entonces devuelve un Error */
    Juego();

    /*  POST: Elimina a los Soldados en casillas inactivas o minadas */
    void comprobarColisiones();
    

    /*  PRE: Debe haber almenos un jugador en el juego. */
    Jugador *obtenerGanador();

    /*  POST: Devuelve EMPATE si no hay ningun jugador vivo, devuelve TERMINADO si hay un solo jugador, sino devuelve En Marcha */
    EstadoPartida obtenerResultado();

    /*  POST: Eliminamos jugadores que perdieron al finalizar la ejecucion del turno */
    void eliminarPerdedores();

    /*  PRE:
        POST: Le da al jugador una nueva carta, le pregunta al jugador que acciones va a realizar,
            ejecuta las reglas del juego y luego pasa de turno al siguiente jugador. */
    void ejecutarTurno();

    /*  POST: */
    void preguntarPonerMina();

    void preguntarMoverUnidad();

    // POST: avanza el turno al siguiente jugador correspondiente, devuelve false cuando hay un ganador o un empate, sino, devuelve true.
    bool avanzarTurno();

    void darCartaAJugador();

    void actualizarImagenes();
};

#endif