#include "Juego.h"

void Juego::preguntarUsoCarta()
{
    if(jugadorActivo == NULL){
        throw("No hay jugador")
    }

    if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){

    bool seUsaCarta = io->preguntarSiUsarCarta(jugadorActivo->getValor());
    if (seUsaCarta)
    {
        unsigned int indiceDeCarta = io->elejirCartaParaJugar(jugadorActivo->getValor());
        usarCarta(jugadorActivo->getValor()->getMano()->get(indiceDeCarta)->getTipo());
        jugadorActivo->getValor()->getMano()->remover(indiceDeCarta);
    }
    else
    {
        std::cout << "No se usa ninguna carta\n";
    }
        }
}

void Juego::pasarTurno()
{
    mapa->disminuirTurnosInactivos();
}

void Juego::darCarta()
{

    if(jugadorActivo == NULL){
        throw("No hay jugador")
    }

        if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){
    jugadorActivo->getValor()->agregarCartaAMano(new Carta());
        }
}

Juego::Juego()
{
    int ancho, largo, alto, cantidadJugadores, soldadosPorJugador;
    io = new EntradaSalida();
    io->inicializarPartida(&ancho, &largo, &alto, &cantidadJugadores, &soldadosPorJugador);

    mapa = new Tablero(ancho, largo, alto);
    jugadores = new ListaCircular<Jugador *>();

    video = new Video();

    for (int i = 0; i < cantidadJugadores; i++)
    {
        jugadores->add(new Jugador(soldadosPorJugador, i + 1)); // !!Completar constructor
    }

    jugadores->reiniciarCursor();

    while (cantidadJugadores > 0 && jugadores->avanzarCursor())
    {
        for (int s = 0; s < soldadosPorJugador; s++)
        {
            mapa->colococarAleatoriamente(jugadores->getCursor(), SOLDADO);
        }
        cantidadJugadores--;
    }

    jugadores->reiniciarCursor();
    jugadorActivo = jugadores->getNodo(1);
}

void Juego::ponerMina(Casilla *objetivo)
{

    if(jugadorActivo == NULL){
        throw("No hay jugador")
    }

    if(objetivo == NULL){
        throw("No hay objetivo")
    }

    TipoUnidad tipo = objetivo->getTipo();
    if (objetivo->esActiva())
    {
        if (tipo == VACIO)
        {
            objetivo->setDuenio(jugadorActivo->getValor()->getId());
            objetivo->setTipo(MINA);
            jugadorActivo->getValor()->agregarUnidad(objetivo);
        }
        else
        {
            Jugador *duenio = getJugadorSegunId(objetivo->getIdDuenio());
            duenio->quitarUnidad(objetivo);
            objetivo->setDuenio(SIN_DUENIO);
            objetivo->setTipo(VACIO);
            objetivo->desactivar(CANTIDAD_TURNOS_INACTIVOS_MINA);
        }
    }
}

void Juego::atacarQuimicamente(Casilla *objetivo, unsgined int duracion)
{

    if(jugadorActivo == NULL){
        throw("No hay jugador")
    }

    if(objetivo == NULL){
        throw("No hay objetivo")
    }

    TipoUnidad tipo = objetivo->getTipo();
    if (objetivo->esActiva())
    {
        if (tipo == VACIO)
        {
            objetivo->desactivar(duracion);
        }
        else
        {
            Jugador *duenio = getJugadorSegunId(objetivo->getIdDuenio());
            duenio->quitarUnidad(objetivo);
            objetivo->setDuenio(SIN_DUENIO);
            objetivo->setTipo(VACIO);
            objetivo->desactivar(duracion);
        }
    }
}

// Cambiar nombre
void Juego::comprobarColisiones(Jugador *jugador, Casilla *anterior, Casilla *nueva)
{
    if(jugador == NULL){
        throw("No hay jugador")
    }
    if(anterior == NULL){
        throw("No hay una casilla anterior")
    }
    if(nueva == NULL){
        throw("No hay una nueva casilla")
    }


        if(!jugador->salteado() &&
        jugador->getEstado() != MUERTO){




    if (nueva->getTipo() == VACIO)
    {
        jugador->quitarUnidad(anterior);
        jugador->agregarUnidad(nueva);

        nueva->setTipo(anterior->getTipo());
        nueva->setDuenio(jugador->getId());

        anterior->setTipo(VACIO);
        anterior->setDuenio(SIN_DUENIO);
    }
    else if (nueva->getTipo() == MINA)
    {
        Jugador *duenioDeMina = getJugadorSegunId(nueva->getIdDuenio());
        duenioDeMina->quitarUnidad(nueva);
        jugador->quitarUnidad(anterior);

        anterior->setTipo(VACIO);
        anterior->setDuenio(SIN_DUENIO);

        nueva->setTipo(VACIO);
        nueva->setDuenio(SIN_DUENIO);
        nueva->desactivar(CANTIDAD_TURNOS_INACTIVOS_MINA);
    }
    else
    {
        Jugador *duenioDeCasillaNueva = getJugadorSegunId(nueva->getIdDuenio());
        Jugador *duenioDeCasillaAnterior = getJugadorSegunId(anterior->getIdDuenio());

        duenioDeCasillaAnterior->quitarUnidad(anterior);
        duenioDeCasillaNueva->quitarUnidad(nueva);

        anterior->setTipo(VACIO);
        anterior->setDuenio(SIN_DUENIO);

        nueva->setTipo(VACIO);
        nueva->setDuenio(SIN_DUENIO);
    }
        }
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
        if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){

    darCartaAJugador();   // OK
    preguntarUsoCarta();  // OK
    preguntarPonerMina(); // OK
    moverUnidad();        // OK
    jugarArmamentos();
        }
    eliminarPerdedores(); // OK
}

void Juego::jugarArmamentos()
{
        if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){

    jugadorActivo->getValor()->getArmamentos()->reiniciarCursor();
    while (jugadorActivo->getValor()->getArmamentos()->avanzarCursor())
    {
        TipoUnidad tipo = jugadorActivo->getValor()->getArmamentos()->getCursor()->getTipo();

        if (tipo == AVION)
        {
            usarRadarEnAvion(jugadorActivo->getValor()->getArmamentos()->getCursor());
        }
        else if (tipo == BARCO)
        {
            ponerMina(mapa->getCasilla(io->preguntarDisparoBarco()));
        }
    }
        }
}

void Juego::preguntarPonerMina() // ok
{
        if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){

    bool valido = false;
    Casilla *objetivo;
    while (!valido)
    {
        Coordenada *posicion = io->preguntarDondeColocarMina();

        if (mapa->laUbicacionEsValida(posicion))
        {
            valido = true;

            objetivo = mapa->getCasilla(posicion);
            TipoUnidad tipo = objetivo->getTipo();
            objetivo = mapa->getCasilla(posicion);

            ponerMina(objetivo);
        }
    }
        }
}

void Juego::moverUnidad()
{
        if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){
    Casilla *actual = io->preguntarUnidadAMover(jugadorActivo->getValor());
    Casilla *nuevaCasilla;

    bool nuevaPosicionInvalida = true;
    Coordenada *nuevaPosicionUnidad;

    while (nuevaPosicionInvalida)
    {
        nuevaPosicionUnidad = io->preguntarDondeMoverUnidad();
        nuevaCasilla = mapa->getCasilla(nuevaPosicionUnidad);
        nuevaPosicionInvalida = mapa->sonVecinas(actual, nuevaCasilla);
    }

    comprobarColisiones(jugadorActivo->getValor(), actual, nuevaCasilla);
        }
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
        if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){
    this->jugadorActivo->getValor()->agregarCartaAMano(new Carta());
        }
}

void Juego::actualizarImagenes()
{

    jugadores->reiniciarCursor();
    int i = jugadores->contarElementos();
    while (i > 0 && jugadores->avanzarCursor())
    {
        video->dibujarTablero(mapa, jugadores->getCursor());
        i--;
    }
}

void Juego::usarCarta(TipoDeCarta tipo)
{
    if(jugadorActivo->getValor() == NULL){

    }

    if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){

    if (tipo == ATAQUEQUIMICO)
    {
        jugarAtaqueQuimico();
    }
    else if (tipo == BARCO)
    {
        jugarBarco();
    }
    else if (tipo == RADAR)
    {
        jugarRadar();
    }
    else if (tipo == SUPERMINA)
    {
        jugarSuperMina();
    }
    else if (tipo == DESTRUCTORARMAMENTO)
    {
        jugarDestructorArmamento();
    }
    else if (tipo == PASARTURNO)
    {
        jugarPasarTurno(); // que busque un objetivo dentro.
    }else{
    throw "No hay carta del tipo solicitado";

    }
        }
}

void Juego::jugarPasarTurno()
{
    /*
que busque un objetivo dentro.
    */

    Jugador *objetivo;
    if (objetivo == NULL)
    {
        throw "El usuario no debe ser nulo";
    }

    objetivo->setEstadoSalteado(true);
}

void Juego::jugarDestructorArmamento() // OKas
{
    if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){
    
    int idJugadorObjetivo = this->io->preguntarEnteroPositivo("Ingrese el ID del Jugador cuyo armamento quieres destruir: ");

    Jugador *objetivo = this->getJugadorSegunId(idJugadorObjetivo);

    if (objetivo == NULL)
    {
        throw "El jugador objetivo no debe ser nulo";
    }

    Lista<Casilla *> *armamentos = objetivo->getArmamentos();

    armamentos->reiniciarCursor();
    while (armamentos->avanzarCursor())
    {
        armamentos->getCursor()->setDuenio(SIN_DUENIO);
        armamentos->getCursor()->setTipo(VACIO);
    }

    for (size_t i = armamentos->contarElementos(); i > 0; i--)
    {
        armamentos->remover(i);
    }
        }
}

void Juego::jugarSuperMina()
{
        if(!jugadorActivo->getValor() == NULL){
        throw("No hay jugador")
    }

    if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){

    bool valido = false;
    Coordenada *posicion;
    while (!valido)
    {
        posicion = io->preguntarDondeColocarMina();

        if (mapa->laUbicacionEsValida(posicion))
        {
            valido = true;
        }
    }

    Casilla *centro = mapa->getCasilla(posicion);
    delete posicion;

    Casilla**** vecinos = centro->getVecinos();

    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                ponerMina(vecinos[i][j][k]);
            }
        }
    }

        }
}

void Juego::jugarRadar()
{
    if(!jugadorActivo->getValor() == NULL){
        throw("No hay jugador")
    }

        if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){

    bool valido = false;
    Coordenada *posicion;
    Casilla *casilla;
    while (!valido)
    {
        posicion = io->pedirCoordenada();

        if (mapa->laUbicacionEsValida(posicion))
        {
            casilla = mapa->getCasilla(posicion);
            if (casilla->esActiva() && casilla->getTipo() == VACIO && casilla->getTerreno() == AIRE)
            {
                valido = true;
            }
        }
        delete posicion;
    }

    casilla->setTipo(AVION);
    casilla->setDuenio(jugadorActivo->getValor()->getId());
        }
}

void Juego::jugarBarco()
{
    if(!jugadorActivo->getValor() == NULL){
        throw("No hay jugador")
    }

        if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){

    bool valido = false;
    Coordenada *posicion;
    Casilla *casilla;
    while (!valido)
    {
        posicion = io->pedirCoordenada();

        if (mapa->laUbicacionEsValida(posicion))
        {
            casilla = mapa->getCasilla(posicion);
            if (casilla->esActiva() && casilla->getTipo() == VACIO && casilla->getTerreno() == MAR)
            {
                valido = true;
            }
        }
        delete posicion;
    }

    casilla->setTipo(BARCO);
    casilla->setDuenio(jugadorActivo->getValor()->getId());

        }
}

void Juego::jugarAtaqueQuimico()
{
    if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){

    bool valido = false;
    Coordenada *posicion;
    Casilla *centro;

    while (!valido)
    {
        posicion = io->preguntarDondeColocarQuimico();

        if (mapa->laUbicacionEsValida(posicion))
        {
            valido = true;
        }
    }

    centro = mapa->getCasilla(posicion);
    delete posicion;

    Casilla ****r2;
    // R3
    for (size_t i = 0; i < 3; i++)
    {
        for (size_t j = 0; j < 3; j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                for (size_t u = 0; u < 3; u++)
                {
                    for (size_t v = 0; v < 3; v++)
                    {
                        for (size_t w = 0; w < 3; w++)
                        {
                            atacarQuimicamente(centro->getVecinos()[i][j][k]->getVecinos()[u][v][w], 6);
                        }
                    }
                }
            }
        }
    }
    // R2
    for (size_t i = 0; i < 3; i++)
    {

        for (size_t j = 0; j < 3; j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                atacarQuimicamente(centro->getVecinos()[i][j][k], 8);
            }
        }
    }

    // R1
    atacarQuimicamente(centro, 10);

        }
}

void Juego::usarRadarEnAvion(Casilla *avion)
{
        if(!jugadorActivo->getValor()->salteado() &&
        jugadorActivo->getValor()->getEstado() != MUERTO){


    Lista<Casilla *> *minasCercanas = new Lista<Casilla *>();

    for (size_t i = 0; i < 3; i++)
    {

        for (size_t j = 0; j < 3; j++)
        {
            for (size_t k = 0; k < 3; k++)
            {
                if (avion->getVecinos()[i][j][k]->getTipo() == MINA)
                {
                    minasCercanas->add(avion->getVecinos()[i][j][k]);
                }
            }
        }
    }

    io->mostrarCoordenadasDeMinas(minasCercanas);

    delete minasCercanas;
        }
}
