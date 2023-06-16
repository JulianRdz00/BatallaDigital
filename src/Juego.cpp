#include "Juego.h"


void Juego::preguntarUsoCarta()
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

void Juego::pasarTurno()
{

}

void Juego::darCarta()
{
    jugadorActivo->getValor()->agregarCartaAMano(new Carta());
}

Juego::Juego()
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

void Juego::comprobarColisiones()
{
    //pendiente
}

Jugador *Juego::obtenerGanador()
{
    return jugadores->get(1);
}

EstadoPartida Juego::obtenerResultado()
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

void Juego::eliminarPerdedores()
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

void Juego::ejecutarTurno()
{
    darCartaAJugador();     // OK
    preguntarUsoCarta();    // OK
    preguntarPonerMina();   // OK
    preguntarMoverUnidad(); // OK

    comprobarColisiones(); // HACER
    eliminarPerdedores();  // OK
}

void Juego::preguntarPonerMina()
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

void Juego::preguntarMoverUnidad()
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

bool Juego::avanzarTurno()
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

void Juego::darCartaAJugador()
{
    this->jugadores->getCursor()->agregarCartaAMano(new Carta());
}

void Juego::actualizarImagenes()
{
    // Hacer
}
