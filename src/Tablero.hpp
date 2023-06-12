#ifndef _TABLERO_H_
#define _TABLERO_H_

#include "Casilla.hpp"

class Tablero
{
private:
    Lista<Casilla *> *mapa;

    int largoMaximo;
    int anchoMaximo;
    int alturaMaxima;

    // Devuelve true solo si las componentes de la ubicacion dada son positivas y estan dentro del tamaño del tablero.
    bool laUbicacionEsValida(Coordenada &ubicacion)
    {
        if (ubicacion.getX() <= anchoMaximo &&
            ubicacion.getX() > 0 &&
            ubicacion.getY() <= largoMaximo &&
            ubicacion.getY() > 0 &&
            ubicacion.getZ() <= alturaMaxima &&
            ubicacion.getZ() > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    Coordenada obtenerPosicionAleatoria()
    {
        int x = getRandom(1, anchoMaximo);
        int y = getRandom(1, largoMaximo);
        int z = getRandom(1, alturaMaxima);

        return Coordenada(x, y, z);
    }

public:
    // POST: Crea un tablero con las dimensiones dadas como argumento.
    Tablero(int ancho, int largo, int alto)
    {
        mapa = new Lista<Casilla *>();

        this->anchoMaximo = ancho;
        this->largoMaximo = largo;
        this->alturaMaxima = alto;
    }

    // POST: Inserta un soldado en el tablero en la posicion de la casilla dada.
    void insertar(Casilla *elemento)
    {
        if (laUbicacionEsValida(elemento->getCoordenada()))
        {
            mapa->add(elemento);
        }
    }

    // PRE: Existe almenos una casilla vacia.
    // POST: Coloca una unidad soldado en una casilla vacia elejida aleatoriamente.
    void colococarAleatoriamente(Casilla &nuevaCasilla)
    {
        bool buscando = true;
        Coordenada posicionRandom = obtenerPosicionAleatoria();
        while (buscando)
        {
            Lista<Casilla *> *objetosEnPosicion = obtenerEnPosicion(nuevaCasilla.getCoordenada());

            if (objetosEnPosicion->vacia())
            {
                buscando = false;
            }
            else
            {
                posicionRandom = obtenerPosicionAleatoria();
            }
        }
        nuevaCasilla.setCoordenada(posicionRandom);
        insertar(&nuevaCasilla);
    }

    // POST: Devuelve un puntero a una lista con las casillas con la posicion dada.
    Lista<Casilla *> *obtenerEnPosicion(Coordenada &posicion)
    {
        Lista<Casilla *> *resultado = new Lista<Casilla *>();

        if (laUbicacionEsValida(posicion))
        {
            mapa->reiniciarCursor();
            while (mapa->avanzarCursor())
            {
                if (mapa->getCursor()->getCoordenada().esIgualA(posicion))
                {
                    resultado->add(mapa->getCursor());
                }
            }
        }

        return resultado;
    }

    // Devuelve una lista de las casillas adyacentes a una posicion.
    Lista<Coordenada> *obtenerAdyacentes(Coordenada posicion)
    {
        Lista<Coordenada> *adyacentes = new Lista<Coordenada>();

        for (int i = -1; i <= 1; i++)
        {
            for (int j = -1; j <= 1; j++)
            {
                for (int k = -1; k <= 1; k++)
                {
                    Coordenada nuevaCoordenada = Coordenada(posicion);
                    nuevaCoordenada.incrementar(i, j, k);
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
    int getAltura()
    {
        return alturaMaxima;
    }

    // Devuelve el ancho maxima que puede tener una posicion dentro del tablero
    int getAncho()
    {
        return anchoMaximo;
    }

    // Devuelve el largo maxima que puede tener una posicion dentro del tablero
    int getLargo()
    {
        return largoMaximo;
    }
};

#endif