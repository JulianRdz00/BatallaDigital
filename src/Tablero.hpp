#ifndef _TABLERO_H_
#define _TABLERO_H_

#include "Casilla.hpp"

class Tablero
{
private:
    Lista<Casilla<Mina *> *> *minas;
    Lista<Casilla<Soldado *> *> *soldados;
    Lista<Casilla<Armamento *> *> *armamentos;

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

public:
    // POST: Crea un tablero con las dimensiones dadas como argumento.
    Tablero(int ancho, int largo, int alto)
    {
        minas = new Lista<Casilla<Mina *> *>;
        soldados = new Lista<Casilla<Soldado *> *>;
        armamentos = new Lista<Casilla<Armamento *> *>;

        this->anchoMaximo = ancho;
        this->largoMaximo = largo;
        this->alturaMaxima = alto;
    }

    // POST: Inserta un soldado en el tablero en la posicion de la casilla dada.
    void insertar(Casilla<Soldado *> *elemento)
    {
        if (laUbicacionEsValida(elemento->getCoordenada()))
        {
            soldados->add(elemento);
        }
    }

    // POST: Inserta un mina en el tablero en la posicion de la casilla dada.
    void insertar(Casilla<Mina *> *elemento)
    {
        if (laUbicacionEsValida(elemento->getCoordenada()))
        {
            minas->add(elemento);
        }
    }

    // POST: Inserta un mina en el tablero en la posicion de la casilla dada.
    void insertar(Casilla<Armamento *> *elemento)
    {
        if (laUbicacionEsValida(elemento->getCoordenada()))
        {
            armamentos->add(elemento);
        }
    }

    // Devuelve el icono de lo que haya en una casilla en una posicion dada, si esta vacia devuelve ICONO_CASILLA_VACIA
    char obtenerIcono(Coordenada posicion)
    {
        char icono = 'X';
        bool buscando = true;
        soldados->reiniciarCursor();
        while (buscando && soldados->avanzarCursor())
        {
            if (soldados->getCursor()->getCoordenada().esIgualA(posicion))
            {
                icono = soldados->getCursor()->getIcono();
                buscando = false;
            }
        }
        minas->reiniciarCursor();
        while (buscando && minas->avanzarCursor())
        {
            if (minas->getCursor()->getCoordenada().esIgualA(posicion))
            {
                icono = minas->getCursor()->getIcono();
                buscando = false;
            }
        }
        armamentos->reiniciarCursor();
        while (buscando && minas->avanzarCursor())
        {
            if (minas->getCursor()->getCoordenada().esIgualA(posicion))
            {
                icono = minas->getCursor()->getIcono();
                buscando = false;
            }
        }
        return icono;
    }

    // POST: Devuelve la casilla con un soldado en una posicion dada.
    Casilla<Soldado *> *ObtenerSoldado(Coordenada &posicion)
    {
        Casilla<Soldado *> *resultado = NULL;

        if (laUbicacionEsValida(posicion))
        {
            bool buscando = true;
            soldados->reiniciarCursor();
            while (buscando && soldados->avanzarCursor())
            {
                if (soldados->getCursor()->getCoordenada().esIgualA(posicion))
                {
                    resultado = soldados->getCursor();
                    buscando = false;
                }
            }
        }

        return resultado;
    }

    // POST: Devuelve la casilla con una mina en una posicion dada.
    Casilla<Mina *> *obtenerMina(Coordenada &posicion)
    {
        Casilla<Mina *> *resultado = NULL;

        if (laUbicacionEsValida(posicion))
        {
            bool buscando = true;
            minas->reiniciarCursor();
            while (buscando && minas->avanzarCursor())
            {
                if (minas->getCursor()->getCoordenada().esIgualA(posicion))
                {
                    resultado = minas->getCursor();
                    buscando = false;
                }
            }
        }

        return resultado;
    }

    // POST: Devuelve la casilla con una armamento en una posicion dada.
    Casilla<Armamento *> *obtenerArmamento(Coordenada &posicion)
    {
        Casilla<Armamento *> *resultado = NULL;

        if (laUbicacionEsValida(posicion))
        {
            bool buscando = true;
            armamentos->reiniciarCursor();
            while (buscando && armamentos->avanzarCursor())
            {
                if (armamentos->getCursor()->getCoordenada().esIgualA(posicion))
                {
                    resultado = armamentos->getCursor();
                    buscando = false;
                }
            }
        }

        return resultado;
    }

    // Devuelve una lista de las casillas adyacentes a una posicion.
    Lista<Coordenada> *obtenerAdyacentes(Coordenada posicion)
    {
        Lista<Coordenada> *adyacentes = new Lista<Coordenada>();
        int x = 0;
        int y = 0;
        int z = 0;

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