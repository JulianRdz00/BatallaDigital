#include "Tablero.h"

Coordenada *Tablero::obtenerPosicionAleatoria()
{
    int x = getRandom(1, anchoMaximo);
    int y = getRandom(1, largoMaximo);
    int z = getRandom(1, alturaMaxima);

    return new Coordenada(x, y, z);
}

TipoTerreno Tablero::getTerreno(Coordenada *ubicacion)
{
    if (laUbicacionEsValida(ubicacion))
    {
        if (ubicacion->getZ() == 1)
        {
            return TIERRA;
        }
        else if (ubicacion->getZ() == 2)
        {
            return MAR;
        }
        else
        {
            return AIRE;
        }
    }
}

// Devuelve true solo si las componentes de la ubicacion dada son positivas y estan dentro del tamaño del tablero.
bool Tablero::laUbicacionEsValida(Coordenada *ubicacion)
{
    if (ubicacion->getX() <= anchoMaximo &&
        ubicacion->getX() > 0 &&
        ubicacion->getY() <= largoMaximo &&
        ubicacion->getY() > 0 &&
        ubicacion->getZ() <= alturaMaxima &&
        ubicacion->getZ() > 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// POST: Crea un tablero con las dimensiones dadas como argumento.
Tablero::Tablero(int ancho, int largo, int alto)
{
    mapa = new Lista<Unidad *>();

    this->anchoMaximo = ancho;
    this->largoMaximo = largo;
    this->alturaMaxima = alto;
}

// POST: Inserta un soldado en el tablero en la posicion de la Unidad dada.
void Tablero::insertar(Unidad *elemento)
{
    if (laUbicacionEsValida(elemento->getUbicacion()))
    {
        mapa->add(elemento);
    }
}

// PRE: Existe almenos una Unidad vacia.
// POST: Coloca una unidad soldado en una Unidad vacia elejida aleatoriamente.
void Tablero::colococarAleatoriamente(Unidad *nuevaUnidad)
{
    bool buscando = true;
    Coordenada *posicionRandom = obtenerPosicionAleatoria();
    while (buscando)
    {
        if (obtenerEnPosicion(nuevaUnidad->getUbicacion())->getUnidad()->getTipo() == VACIO)
        {
            buscando = false;
        }
        else
        {
            posicionRandom = obtenerPosicionAleatoria();
        }
    }
    
    nuevaUnidad->setUbicacion(posicionRandom);
    insertar(nuevaUnidad);
}

// POST: Devuelve un puntero a una lista con las Unidads con la posicion dada.
Casilla *Tablero::obtenerEnPosicion(Coordenada *posicion)
{
    if (laUbicacionEsValida(posicion))
    {
        Unidad *auxUnidad;
        bool sinEncontrar = true;
        mapa->reiniciarCursor();
        while (sinEncontrar && mapa->avanzarCursor())
        {
            if (mapa->getCursor()->getUbicacion()->esIgualA(posicion))
            {
                auxUnidad = mapa->getCursor();
            }
        }

        if (sinEncontrar)
        {
            auxUnidad = new Unidad(posicion, VACIO);
        }

        return new Casilla(auxUnidad, getTerreno(posicion));
    }
}

// Devuelve una lista de las Unidads adyacentes a una posicion.
Lista<Coordenada *> *Tablero::obtenerAdyacentes(Coordenada *posicion)
{
    Lista<Coordenada *> *adyacentes = new Lista<Coordenada *>();

    for (int i = -1; i <= 1; i++)
    {
        for (int j = -1; j <= 1; j++)
        {
            for (int k = -1; k <= 1; k++)
            {
                Coordenada *nuevaCoordenada = new Coordenada(posicion);
                nuevaCoordenada->incrementar(i, j, k);
                if (laUbicacionEsValida(nuevaCoordenada))
                {
                    adyacentes->add(nuevaCoordenada);
                }
            }
        }
    }

    return adyacentes;
}

// Devuelve la altura maxima que puede tener una posicion dentro del tablero
int Tablero::getAltura()
{
    return alturaMaxima;
}

// Devuelve el ancho maxima que puede tener una posicion dentro del tablero
int Tablero::getAncho()
{
    return anchoMaximo;
}

// Devuelve el largo maxima que puede tener una posicion dentro del tablero
int Tablero::getLargo()
{
    return largoMaximo;
}