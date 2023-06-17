#include "Juego.h"

void Juego::preguntarUsoCarta()
{
    bool seUsaCarta = io->preguntarSiUsarCarta(jugadorActivo->getValor());
    if (seUsaCarta)
    {
        unsigned int indiceDeCarta = io->elejirCartaParaJugar(jugadorActivo->getValor());
        usarCarta(mapa, io, jugadorActivo->getValor(), jugadorActivo->getValor()->getMano()->get(indiceDeCarta)->getTipo());
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
    // pendiente
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
        Coordenada *posicion = io->preguntarDondeColocarMina();
        mina = new Unidad(posicion, MINA);

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
    Coordenada *nuevaPosicionUnidad;
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

void Juego::usarCarta(Tablero *tablero, EntradaSalida *io, Jugador *usuario, TipoDeCarta tipo)
{

    if (tipo == ATAQUEQUIMICO)
    {
        jugarAtaqueQuimico(tablero, io, usuario);
    }
    else if (tipo == BARCO)
    {
        jugarBarco(tablero, io, usuario);
    }
    else if (tipo == RADAR)
    {
        jugarRadar(tablero, io);
    }
    else if (tipo == SUPERMINA)
    {
        jugarSuperMina(tablero, io, usuario);
    }
    else if (tipo == DESTRUCTORARMAMENTO)
    {
        jugarDestructorArmamento(usuario);
    }
    else if (tipo == PASARTURNO)
    {
        jugarPasarTurno(usuario);
    }

    throw "No hay carta del tipo solicitado";
}

void Juego::jugarPasarTurno(Jugador *usuario)
{
    /*
        if (!tipo == PASARTURNO)
        {
            throw "El tipo de carta debe ser PASARTURNO";
        }
    */

    if (usuario == NULL)
    {
        throw "El usuario no debe ser nulo";
    }

    usuario->setEstadoSalteado(true);
}

void Juego::jugarDestructorArmamento(Jugador *usuario)
{
    /*
        if (!tipo == DESTRUCTORARMAMENTO)
        {
            throw "El tipo de carta debe ser DESTRUCTORARMAMENTO";
        }
    */

    if (usuario == NULL)
    {
        throw "El usuario no debe ser nulo";
    }

    Lista<Unidad *> *armamentos = usuario->getArmamentos();

    for (size_t i = armamentos->contarElementos(); i > 0; i--)
    {
        armamentos->remover(i);
    }
}

void Juego::jugarSuperMina(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
{
    Coordenada *posicion = io->pedirCoordenada();
    /*
        if (!tipo == SUPERMINA)
        {
            throw "El tipo de carta debe ser SUPERMINA";
        }
    */

    if (!tablero->laUbicacionEsValida(posicion))
    {
        throw "La posicion ingresada debe estar dentro de los limites del tablero";
    }
    Unidad *ataque = new Unidad(posicion, MINA);
    tablero->insertar(ataque);
    atacarAdyacentes(tablero, ataque, MINA);
}

Lista<Coordenada *> *Juego::jugarRadar(Tablero *tablero, EntradaSalida *io)
{
    Coordenada *posicion = io->pedirCoordenada();

    /*
    if (!tipo == RADAR)
    {
        throw "El tipo de carta debe ser RADAR";
    }
    */

    if (!tablero->laUbicacionEsValida(posicion))
    {
        throw "La posicion ingresada debe estar dentro de los limites del tablero";
    }
    if (tablero->obtenerEnPosicion(posicion)->getTerreno() != AIRE)
    {
        throw "Esta carta solo es valida en las regiones con aire";
    }

    return buscarMinas(tablero);
}

void Juego::jugarBarco(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
{
    Coordenada *posicionAtacada = io->pedirCoordenada();
    Coordenada *posicionBarco = io->pedirCoordenada();

    /*
    if (!tipo == BARCO)
    {
        throw "El tipo de carta debe ser BARCO";
    }
    */

    if (!tablero->laUbicacionEsValida(posicionAtacada))
    {
        throw "La posicion ingresada debe estar dentro de los limites del tablero";
    }

    if (!tablero->laUbicacionEsValida(posicionBarco))
    {
        throw "La posicion ingresada debe estar dentro de los limites del tablero";
    }

    if (tablero->obtenerEnPosicion(posicionBarco)->getTerreno() != MAR)
    {
        throw "Esta carta solo es valida en las regiones con agua";
    }

    Unidad *torpedo = new Unidad(posicionAtacada, MINA);
    Unidad *barco = new Unidad(posicionBarco, BARCO);

    tablero->insertar(torpedo);
    tablero->insertar(barco);
}

void Juego::jugarAtaqueQuimico(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
{
    Coordenada *posicion = io->pedirCoordenada();
    /*
        if (!tipo == ATAQUEQUIMICO)
        {
            throw "El tipo de carta debe ser ATAQUEQUIMICO";
        }
    */

    if (!tablero->laUbicacionEsValida(posicion))
    {
        throw "La posicion ingresada debe estar dentro de los limites del tablero";
    }

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; ++j)
        {
            for (int k = 0; k < 5; ++k)
            {

                posicion->getX() - 2 + i;
                posicion->getY() - 2 + j;
                posicion->getZ() - 2 + k;
                Coordenada *posicionAux = NULL;
                posicionAux->setCoordenada(posicion->getX() - 2 + i, posicion->getY() - 2 + j, posicion->getZ() - 2 + k);
                tablero->obtenerEnPosicion(posicionAux)->getUnidad()->setTipo(QUIMICO);
                tablero->insertar(tablero->obtenerEnPosicion(posicionAux)->getUnidad());
                determinarTurnos(tablero, posicion, posicionAux);
            }
        }
    }
}

Lista<Coordenada *> *Juego::buscarMinas(Tablero *tablero)
{
    Lista<Coordenada *> *ocupantes = new Lista<Coordenada *>();

    for (int i = 5; i < tablero->getAltura(); ++i)
    {
        for (int j = 0; j < tablero->getAncho(); ++j)
        {
            for (int k = 0; k < tablero->getLargo(); ++k)
            {
                Coordenada *posicionAux = NULL;
                posicionAux->setCoordenada(i, j, k);
                if (tablero->obtenerEnPosicion(posicionAux)->getUnidad()->getTipo() == MINA)
                {
                    ocupantes->add(tablero->obtenerEnPosicion(posicionAux)->getUnidad()->getUbicacion());
                }
            }
        }
    }

    return ocupantes;
}

void Juego::atacarAdyacentes(Tablero *tablero, Unidad *unidad, TipoUnidad tipo)
{

    if (unidad == NULL)
    {
        throw "unidad no debe ser nula";
    }

    for (int i = 1; i < 3; ++i)
    {
        Lista<Coordenada *> *posiciones = tablero->obtenerAdyacentes(unidad->getUbicacion());

        posiciones->reiniciarCursor();
        while (posiciones->avanzarCursor())
        {
            Coordenada *coordenada = posiciones->getCursor();
            unidad->setTipo(tipo);
        }
    }
}

void Juego::determinarTurnos(Tablero *mapa, Coordenada *posicion, Coordenada *nuevaPosicion)
{

    if (mapa == NULL)
    {
        throw "mapa no debe ser nulo";
    }

    mapa->obtenerAdyacentes(posicion)->reiniciarCursor();

    while (mapa->obtenerAdyacentes(posicion)->avanzarCursor())
    {
        Coordenada *posicionAdyacente = mapa->obtenerAdyacentes(posicion)->getCursor();
        if (nuevaPosicion == posicion)
        {
            mapa->obtenerEnPosicion(posicion)->getUnidad()->desactivar(10);
        }
        else if (nuevaPosicion == posicionAdyacente)
        {
            mapa->obtenerEnPosicion(posicionAdyacente)->getUnidad()->desactivar(8);
        }
        else
        {
            mapa->obtenerEnPosicion(nuevaPosicion)->getUnidad()->desactivar(6);
        }
    }
}