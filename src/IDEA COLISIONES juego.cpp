#include "Juego.h"


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

void pasarTurno()
{

}

void darCarta()
{
    jugadorActivo->getValor()->agregarCartaAMano(new Carta());
}

Juego()
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


void recorrerJugador(Jugador* jugador){


    jugador->getSoldados()-reiniciarCursor();
    while(jugador->getSoldado()->avanzarCursor()){
        Unidad* Soldado1 = jugador->getSoldado()->getCursor();
        Unidad* Soldado2 = obtenerSoldado(jugadores, )
    }

}

void comprobarSoldados(){
    jugadores->reiniciarCursor();
    while(jugadores->avanzarCursor()){
        Jugador* jugador1 = jugadores->getCursor();

        recorrerJugador(jugador1);
        
    }

}


/*
void comprobarColisiones()
{
   //idea 
}
*/
bool haySoldado(Jugador* jugador, Coordenada* posicion){
    jugador->getSoldados()->reiniciarCursor();
    while(jugador->getSoldados()->avanzarCursor()){
        Unidad* unidad = jugador->getSoldados()->getCursor();
        if (unidad->getUbicacion() == posicion){
            bool true;
        }
    }
}

bool hayArmamento(Jugador* jugador, Coordenada* posicion){
    jugador->getArmamentos()->reiniciarCursor();
    while(jugador->getArmamentos()->avanzarCursor()){
        Unidad* unidad = jugador->getArmamentos()->getCursor();
        if (unidad->getUbicacion() == posicion){
            bool true;
        }
    }
}

bool hayColision(Jugador* jugador, Coordenada* posicion){

    if(haySoldado(jugador, posicion))
    {
        return true;
    }else if (hayArmamento(jugador, posicion))
    {
        return true;
       
    }

    return false;

}

Jugador *obtenerGanador()
{
    return jugadores->get(1);
}

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

void ejecutarTurno()
{
    darCartaAJugador();     // OK
    preguntarUsoCarta();    // OK
    preguntarPonerMina();   // OK
    preguntarMoverUnidad(); // OK

    comprobarColisiones(); // HACER
    eliminarPerdedores();  // OK
}




void preguntarPonerMina()
{
    bool invalido = true;
    Unidad *mina;
    while (invalido)
    {
        Coordenada* posicion = io->preguntarDondeColocarMina();
        mina = new Unidad(posicion, this->jugadorActivo->getValor(), MINA);

        if(hayColision(this->jugadorActivo->getValor(), posicion)){
            mapa->obtenerEnPosicion(posicion)->getUnidad()->desactivar(5);
            if(mapa->obtenerEnPosicion(posicion)->getUnidad().tipoOcupante() == SOLDADO){
                this->jugadorActivo->getValor()->eliminarSoldado(posicion);
            }else if(mapa->obtenerEnPosicion(posicion)->getUnidad().tipoOcupante() == BARCO || 
                mapa->obtenerEnPosicion(posicion)->getUnidad().tipoOcupante() == AVION){
                this->jugadorActivo->getValor()->eliminarArmamento(posicion);
            }
        }

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
