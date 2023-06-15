#ifndef _JUEGO_
#define _JUEGO_

#include "Tablero.hpp"
#include "Jugador.hpp"
#include "Constantes.hpp"
#include "ListaCircular.hpp"
#include "EntradaSalida.hpp"

class Juego
{
private:
    //  ATRIBUTOS
    Tablero *mapa;
    ListaCircular<Jugador *> *jugadores;
    Nodo<Jugador *> *jugadorActivo;
    EntradaSalida *io;

    void preguntarUsoCarta()
    {
        bool seUsaCarta = io->preguntarSiUsarCarta(*(jugadorActivo->getValor()));
        if (seUsaCarta)
        {
            unsigned int indiceDeCarta = io->elejirCartaParaJugar(*(jugadorActivo->getValor()));
            jugadorActivo->getValor()->getListaDeCartas()->get(indiceDeCarta)->usar();//Pushear
            jugadorActivo->getValor()->getListaDeCartas()->remover(indiceDeCarta);
        }
        else
        {
            std::cout << "No se usa ninguna carta\n";
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
        jugadorActivo->getValor()->agregarCartaAMano(new Carta());
    }

    /* ____UTILIZAR SOLAMENTE DURANTE EL DESARROLLO___
    Dibuja una capa XY del mapa
    */
    void renderDevCapa(int z)
    {
        /*
        for (int y = 0; y < mapa->getLargo(); y++)
        {
            for (int x = 0; x < mapa->getAncho(); x++)
            {
                std::cout << " " << mapa->espacio[y][x][z]->getIcono();
            }
            std::cout << "\n";
        }
        */
    }

public:
    /*
    POS: Inicia un Juego con cantidad de jugadores y dimensiones del terreno por defecto
    */
    Juego()
    {
    }

    /*
    Pre: Los valores deben ser mayores a 0.
        La cantidad de soldados por jugador * la cantidad de jugadores debe ser menor a la cantidad de casillas del tablero
        es decir, ancho * largo * alto

    POS: Inicia un Juego con la cantidad de jugadores especificada,
        con la cantidad de soldados por jugador especificada. El terreno de juego es generado
        con las dimensiones dadas.
        Si no hay suficiente espacio para ubicar a los Soldados de todos los jugadores, entonces devuelve un Error
    */
    Juego(int ancho, int largo, int alto, int cantidadJugadores, int soldadosPorJugador) // ok
    {
        mapa = new Tablero(ancho, largo, alto);
        io = new EntradaSalida();

        for (int i = 0; i < cantidadJugadores; i++)
        {
            jugadores->add(new Jugador()); // !!Completar constructor
        }

        jugadores->reiniciarCursor();
        while (jugadores->avanzarCursor())
        {
            Lista<Unidad *> *soldadosJugador = jugadores->getCursor()->getListaDeSoldados();

            soldadosJugador->reiniciarCursor();
            while (soldadosJugador->avanzarCursor())
            {
                mapa->colococarAleatoriamente(*(soldadosJugador->getCursor()));
            }
        }
    }

    /*
    Elimina a los Soldados en casillas inactivas o minadas
    */
    void comprobarColisiones();

    /*
    PRE: Debe haber almenos un jugador en el juego.
    */
    bool hayGanador();

    /*
    PRE:
    POST: Le da al jugador una nueva carta, le pregunta al jugador que acciones va a realizar,
        ejecuta las reglas del juego y luego pasa de turno al siguiente jugador.
    */
    void ejecutarTurno(Jugador *jugador)
    {
        darCartaAJugador();     // OK
        preguntarUsoCarta();    //
        preguntarPonerMina();   // OK
        preguntarMoverUnidad(); // Hacer

        comprobarColisiones();
        hayGanador();
    }

    void preguntarPonerMina()
    {
        bool invalido = true;
        Unidad *mina;
        while (invalido)
        {
            Coordenada posicion = io->preguntarDondeColocarMina();
            mina = new Unidad(posicion, this->jugadorActivo->getValor(), MINA);

            if (mapa->laUbicacionEsValida(posicion))
            {
                invalido = false;
            }
            else
            {
                delete mina;
            }
        }
    }

    void preguntarMoverUnidad();

    // POST: avanza el turno al siguiente jugador correspondiente, devuelve false cuando hay un ganador o un empate, sino, devuelve true.
    bool avanzarTurno()
    {

        this->jugadorActivo = this->jugadorActivo->getSiguiente();

        return hayGanador();
    }

    void darCartaAJugador()
    {
        this->jugadores->getCursor()->agregarCartaAMano(new Carta())
    }
};

#endif