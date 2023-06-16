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

    void preguntarUsoCarta()
    {
        bool seUsaCarta = io->preguntarSiUsarCarta(jugadorActivo->getValor());
        if (seUsaCarta)
        {
            unsigned int indiceDeCarta = io->elejirCartaParaJugar(jugadorActivo->getValor());
            jugadorActivo->getValor()->getMano()->get(indiceDeCarta)->usar(mapa, io, jugadorActivo->getValor());
            jugadorActivo->getValor()->getMano()->remover(indiceDeCarta);
        }
        else
        {
            std::cout << "No se usa ninguna carta\n";
        }
    }

    /*
    POS: Cambia el jugador en turno al siguiente en la lista de Jugadores
    */
    void pasarTurno()
    {

    }

    /*
    POS: Añade una Carta aleatoria a la Mano del jugador
    */
    void darCarta()
    {
        jugadorActivo->getValor()->agregarCartaAMano(new Carta());
    }

public:
    /*  Pre: Los valores deben ser mayores a 0.
            La cantidad de soldados por jugador * la cantidad de jugadores debe ser menor a la cantidad de casillas del tablero
            es decir, ancho * largo * alto

        POST: Inicia un Juego con la cantidad de jugadores especificada,
            con la cantidad de soldados por jugador especificada. El terreno de juego es generado
            con las dimensiones dadas.
            Si no hay suficiente espacio para ubicar a los Soldados de todos los jugadores, entonces devuelve un Error */
    Juego() // ok
    {
        int ancho, largo, alto, cantidadJugadores, soldadosPorJugador;
        io = new EntradaSalida();
        io->inicializarPartida(ancho, largo, alto, cantidadJugadores, soldadosPorJugador);

        // TODO
        mapa = new Tablero(ancho, largo, alto);

        for (int i = 0; i < cantidadJugadores; i++)
        {
            jugadores->add(new Jugador()); // !!Completar constructor
        }

        jugadores->reiniciarCursor();
        while (jugadores->avanzarCursor())
        {
            Lista<Unidad *> *soldadosJugador = jugadores->getCursor()->getSoldados();

            soldadosJugador->reiniciarCursor();
            while (soldadosJugador->avanzarCursor())
            {
                mapa->colococarAleatoriamente(soldadosJugador->getCursor());
            }
        }
    }

    /*  POST: Elimina a los Soldados en casillas inactivas o minadas */
    void comprobarColisiones()
    {
        // PENDIENTE
    }

    /*  PRE: Debe haber almenos un jugador en el juego. */
    Jugador *obtenerGanador()
    {
        return jugadores->get(1);
    }

    /*  POST: Devuelve EMPATE si no hay ningun jugador vivo, devuelve TERMINADO si hay un solo jugador, sino devuelve En Marcha */
    EstadoPartida obtenerResultado()
    {
        if (jugadores->contarElementos() == 0)
        {
            return EMPATE;
        }
        else if (jugadores->contarElementos() == 1)
        {
            return TERMINADA;
        }
        else
        {
            return ENMARCHA;
        }
    }

    /*  POST: Eliminamos jugadores que perdieron al finalizar la ejecucion del turno */
    void eliminarPerdedores()
    {

        bool hayPerdedores = true;
        bool buscando = true;
        while (hayPerdedores)
        {
            int i = 1;
            jugadores->reiniciarCursor();
            while (buscando && jugadores->avanzarCursor())
            {

                if (jugadores->getCursor()->getEstado() == MUERTO)
                {
                    buscando = false;
                    jugadores->remover(i);
                }
                else
                {
                    i++;
                }

                if (i == jugadores->contarElementos() + 1)
                {
                    hayPerdedores = false;
                }
            }
        }
    }

    /*  PRE:
        POST: Le da al jugador una nueva carta, le pregunta al jugador que acciones va a realizar,
            ejecuta las reglas del juego y luego pasa de turno al siguiente jugador. */
    void ejecutarTurno()
    {
        darCartaAJugador();     // OK
        preguntarUsoCarta();    // OK
        preguntarPonerMina();   // OK
        preguntarMoverUnidad(); // OK

        comprobarColisiones(); // HACER
        eliminarPerdedores();  // OK
    }

    /*  POST: */
    void preguntarPonerMina()
    {
        bool invalido = true;
        Unidad *mina;
        while (invalido)
        {
            Coordenada* posicion = io->preguntarDondeColocarMina();
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

    void preguntarMoverUnidad()
    {
        Coordenada *posicionUnidadAMover = io->preguntarUnidadAMover(jugadorActivo->getValor());
        bool posicionInvalida = true;
        Coordenada* nuevaPosicionUnidad;
        while (posicionInvalida)
        {
            nuevaPosicionUnidad = io->preguntarDondeMoverUnidad();
            mapa->obtenerAdyacentes(posicionUnidadAMover)->reiniciarCursor();
            while (mapa->obtenerAdyacentes(posicionUnidadAMover)->avanzarCursor())
            {
                if (
                    (mapa->obtenerEnPosicion(mapa->obtenerAdyacentes(posicionUnidadAMover)->getCursor())->getUnidad()->esActiva()) &&
                    (mapa->obtenerAdyacentes(posicionUnidadAMover)->getCursor()->esIgualA(nuevaPosicionUnidad)))
                {
                    posicionInvalida = false;
                }
            }
        }
        mapa->obtenerEnPosicion(posicionUnidadAMover)->getUnidad()->setUbicacion(nuevaPosicionUnidad);
    }

    // POST: avanza el turno al siguiente jugador correspondiente, devuelve false cuando hay un ganador o un empate, sino, devuelve true.
    bool avanzarTurno()
    {
        this->jugadorActivo = this->jugadorActivo->getSiguiente();

        if (obtenerResultado() == ENMARCHA)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void darCartaAJugador()
    {
        this->jugadores->getCursor()->agregarCartaAMano(new Carta());
    }

    void actualizarImagenes()
    {
        // Hacer
    }
};

#endif