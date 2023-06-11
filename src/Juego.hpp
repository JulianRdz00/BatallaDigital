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
    Jugador *jugadorActivo = new Jugador();

    void preguntarUsoCarta()
    {
        char respuesta;
        std::cout << "Queres usar una carta?\n";
        std::cout << "[S]Si [N]No\n";
        std::cin >> respuesta;

        if (respuesta == 'S')
        {

            std::cout << "Tus cartas disponibles:\n";

            const Lista<Carta> * = jugadorActivo->getListaDeCartas();

            for (size_t i = 0; i < jugadorActivo->cantidadDeCarta(); i++)
            {
                std::cout <<
            }
        }
    }

    /*
    POS: Cambia el jugador en turno al siguiente en la lista de Jugadores
    */
    void pasarTurno();

    /*
    POS: Añade una Carta aleatoria a la Mano del jugador
    */
    void darCarta()
    {
        jugadorActivo->agregarCartaAMano(new Carta());
    }

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
            wait(300);
            system("clear");
        }
    }

    /*
    PRE:
    POST: Le da al jugador una nueva carta, le pregunta al jugador que acciones va a realizar,
        ejecuta las reglas del juego y luego pasa de turno al siguiente jugador.
    */
    void ejecutarTurno()
    {
        darCarta();
        preguntarUsoCarta();
        preguntarDondePonerMina();
        preguntarMovimiento();

        pasarTurno();
    }
};

#endif