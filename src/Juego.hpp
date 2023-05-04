#ifndef _JUEGO_
#define _JUEGO_

#include "Tablero.hpp"
#include "Jugador.hpp"
#include "Array.hpp"
#include "Constantes.hpp"
#include "ListaC.hpp"

class Juego
{
private:
    //  ATRIBUTOS
    Tablero *mapa;
    ListaC<Jugador> jugadores; // Usar una lista circular
    // Jugador &jugadorEnTurno;

    /*
    POS: Añade una Carta aleatoria a la Mano del jugador
    */
    void darCarta(Jugador &jugador);

    /* ____UTILIZAR SOLAMENTE DURANTE EL DESARROLLO___
    Dibuja una capa XY del mapa
    */
    void renderDevCapa(int z)
    {
        for (int y = 0; y < mapa->getLargo(); y++)
        {
            for (int x = 0; x < mapa->getAncho(); x++)
            {
                std::cout << " " << mapa->espacio[y][x][z]->getIcono();
            }
            std::cout << "\n";
        }
    }

public:
    /*
    POS: Inicia un Juego con cantidad de jugadores y dimensiones del terreno por defecto
    */
    Juego()
    {
        mapa = new Tablero();
    }

    /*
    Pre: Los valores deben ser mayores a 0.

    POS: Inicia un Juego con la cantidad de jugadores especificada,
        con la cantidad de soldados por jugador especificada. El terreno de juego es generado
        con las dimensiones dadas.
        Si no hay suficiente espacio para ubicar a los Soldados de todos los jugadores, entonces devuelve un Error
    */
    Juego(int largo, int ancho, int alto, int cantidadJugadores, int soldadosPorJugador);

    /*
    Elimina a los Soldados en casillas inactivas o minadas
    */
    void comprobarColisiones();

    /*
    POS: Cambia el jugador en turno al siguiente en la lista de Jugadores
    */
    void pasarTurno();

    /*
    PRE: Debe haber almenos un jugador en el juego.

    POS: Busca la cantidad de jugadores vivos restantes.
        Dependiendo de la cantidad de jugadores:
            1: El estado cambia a Ganado,
            0: El estado cambia a Empate.
    */
    void buscarGanador();

    /*
    ____Utilizar solo durante el desarrollo_____
    POS: Dibuja en consola todo el mapa por capas.
    */
    void RenderDev()
    {
        for (int z = 0; z < mapa->getAltura(); z++)
        {
            renderDevCapa(z);
            wait(100);
            system("clear");
        }
    }
};

#endif