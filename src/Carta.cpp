#include "Carta.h"

void Carta::determinarTurnos(Tablero *mapa, Coordenada *posicion, Coordenada *nuevaPosicion)
{

    if (mapa == NULL)
    {
        throw "mapa no debe ser nulo";
    }

    mapa->obtenerAdyacentes(posicion)->reiniciarCursor();

    while (mapa.obtenerAdyacentes(posicion)->avanzarCursor())
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

void Carta::atacarAdyacentes(Tablero *tablero, Unidad *unidad, TipoUnidad tipo)
{

    if (unidad == NULL)
    {
        throw "unidad no debe ser nula";
    }

    for (int i = 1; i < 3; ++i)
    {
        Lista<Coordenada> *posiciones = tablero->obtenerAdyacentes(unidad->getUbicacion());

        posiciones->reiniciarCursor();
        while (posiciones->avanzarCursor())
        {
            Coordenada coordenada = posiciones->getCursor();
            unidad->setTipo(tipo);
        }
    }
}

Lista<Coordenada *> *Carta::buscarMinas(Tablero *tablero)
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

Carta::Carta(TipoDeCarta tipo)
{
    this->tipo = tipo;
}

Carta::Carta()
{
    this->tipo = TipoDeCarta(getRandom(0, CANTIDAD_TIPOS_DE_CARTAS - 1));
}

void Carta::jugarAtaqueQuimico(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
{
    Coordenada *posicion = io->pedirCoordenada();

    if (!tipo == ATAQUEQUIMICO)
    {
        throw "El tipo de carta debe ser ATAQUEQUIMICO";
    }

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

void Carta::jugarBarco(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
{
    Coordenada *posicionAtacada = io->pedirCoordenada();
    Coordenada *posicionBarco = io->pedirCoordenada();

    if (!tipo == BARCO)
    {
        throw "El tipo de carta debe ser BARCO";
    }

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

    Unidad *torpedo = new Unidad(posicionAtacada, usuario, MINA);
    Unidad *barco = new Unidad(posicionBarco, usuario, BARCO);

    tablero->insertar(torpedo);
    tablero->insertar(barco);
}

Lista<Coordenada *> *Carta::jugarRadar(Tablero *tablero, EntradaSalida *io)
{
    Coordenada *posicion = io->pedirCoordenada();

    if (!tipo == RADAR)
    {
        throw "El tipo de carta debe ser RADAR";
    }

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

void Carta::jugarSuperMina(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
{
    Coordenada *posicion = io->pedirCoordenada();

    if (!tipo == SUPERMINA)
    {
        throw "El tipo de carta debe ser SUPERMINA";
    }

    if (!tablero->laUbicacionEsValida(posicion))
    {
        throw "La posicion ingresada debe estar dentro de los limites del tablero";
    }
    Unidad *ataque = new Unidad(posicion, usuario, MINA);
    tablero->insertar(ataque);
    atacarAdyacentes(tablero, ataque, MINA);
}

void Carta::jugarDestructorArmamento(Jugador *usuario)
{

    if (!tipo == DESTRUCTORARMAMENTO)
    {
        throw "El tipo de carta debe ser DESTRUCTORARMAMENTO";
    }

    if (usuario == NULL)
    {
        throw "El usuario no debe ser nulo";
    }

    Lista<Unidad *> *armamentos = usuario->getListaDeArmamentos();

    for (size_t i = armamentos->contarElementos(); i > 0; i--)
    {
        armamentos->remover(i);
    }
}

void Carta::jugarPasarTurno(Jugador *usuario)
{

    if (!tipo == PASARTURNO)
    {
        throw "El tipo de carta debe ser PASARTURNO";
    }

    if (usuario == NULL)
    {
        throw "El usuario no debe ser nulo";
    }

    usuario->setEstadoSalteado(true);
}

virtual Carta::~Carta()
{

}

TipoDeCarta Carta::getTipo()
{
    return this->tipo;
}

std::string Carta::getNombre()
{
    switch (tipo)
    {
    case SUPERMINA:
        std::cout << NOMBRE_CARTA_SUPERMINA << std::endl;
        break;
    case RADAR:
        std::cout << NOMBRE_CARTA_RADAR << std::endl;
        break;
    case ATAQUEQUIMICO:
        std::cout << NOMBRE_CARTA_ATAQUEQUIMICO << std::endl;
        break;
    case USARBARCO:
        std::cout << NOMBRE_CARTA_USARBARCO << std::endl;
        break;
    case DESTRUCTORARMAMENTO:
        std::cout << NOMBRE_CARTA_DESTRUCTORARMAMENTO << std::endl;
        break;
    case PASARTURNO:
        std::cout << NOMBRE_CARTA_PASARTURNO << std::endl;
        break;
    }
}

void Carta::usar(Tablero *tablero, EntradaSalida *io, Jugador *usuario)
{

    if (this->tipo == ATAQUEQUIMICO)
    {
        jugarAtaqueQuimico(tablero, io, usuario);
    }
    else if (this->tipo == BARCO)
    {
        jugarBarco(tablero, io, usuario);
    }
    else if (this->tipo == RADAR)
    {
        jugarRadar(tablero, io);
    }
    else if (this->tipo == SUPERMINA)
    {
        jugarSuperMina(tablero, io, usuario);
    }
    else if (this->tipo == DESTRUCTORARMAMENTO)
    {
        jugarDestructorArmamento(usuario);
    }
    else if (this->tipo == PASARTURNO)
    {
        jugarPasarTurno(usuario);
    }

    throw "No hay carta del tipo solicitado";
}
