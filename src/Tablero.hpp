#ifndef _TABLERO_H_
#define _TABLERO_H_

#include "Lista.hpp"
#include "Casilla.h"
#include "Jugador.h"

class Tablero
{
private:
    Lista<Lista<Lista<Casilla *> *> *> *mapa;

    int ancho;
    int largo;
    int alto;

    /*PRE: El ancho, largo y alto ya estan definidos*/
    Casilla ****buscarVecinos(Coordenada *posicion)
    {
        Casilla ****vecinos = new Casilla ***[3];
        for (size_t u = 0; u < 3; u++)
        {
            vecinos[u] = new Casilla **[3];
            for (size_t v = 0; v < 3; v++)
            {
                vecinos[u][v] = new Casilla *[3];

                for (size_t w = 0; w < 3; w++)
                {
                    int x = posicion->getX() + (u - 1);
                    int y = posicion->getY() + (v - 1);
                    int z = posicion->getZ() + (w - 1);

                    if (x < 1)
                    {
                        x = this->ancho;
                    }
                    if (x > this->ancho)
                    {
                        x = 1;
                    }

                    if (y < 1)
                    {
                        y = this->largo;
                    }
                    if (y > this->largo)
                    {
                        y = 1;
                    }

                    if (z < 1)
                    {
                        z = this->alto;
                    }
                    if (z > this->alto)
                    {
                        z = 1;
                    }

                    vecinos[u][v][w] = this->mapa->get(z)->get(y)->get(x);
                }
            }
        }

        return vecinos;
    }

public:
    // POST: Crea un tablero con las dimensiones dadas como argumento.
    Tablero(int ancho, int largo, int alto) // OK
    {
        this->ancho = ancho;
        this->largo = largo;
        this->alto = alto;

        mapa = new Lista<Lista<Lista<Casilla *> *> *>();

        for (int i = 1; i <= alto; i++)
        {
            Lista<Lista<Casilla *> *> *capa = new Lista<Lista<Casilla *> *>();

            for (int j = 1; j <= largo; j++)
            {
                Lista<Casilla *> *eje = new Lista<Casilla *>();
                for (int k = 1; k <= ancho; k++)
                {
                    TipoTerreno terreno;
                    if (i < 2)
                    {
                        terreno = TIERRA;
                    }
                    else if (i > 1 && i < 6)
                    {
                        terreno = MAR;
                    }
                    else
                    {
                        terreno = AIRE;
                    }
                    eje->add(new Casilla(terreno, new Coordenada(k, j, i)));
                }
                capa->add(eje);
            }
            this->mapa->add(capa);
        }

        for (int i = 1; i <= alto; i++)
        {
            for (int j = 1; j <= largo; j++)
            {
                for (int k = 1; k <= ancho; k++)
                {
                    Coordenada *posicion = new Coordenada(k, j, i);
                    this->mapa->get(i)->get(j)->get(k)->setVecinos(buscarVecinos(posicion));
                    delete posicion;
                }
            }
        }
    }

    // PRE:  El tablero ya esta definido y poblado por casillas.
    // POST: Recorre el tablero, restandole un turno de inactividad a todas las casillas inactivas.
    void disminuirTurnosInactivos()
    {
        mapa->reiniciarCursor();
        while (this->mapa->avanzarCursor())
        {
            mapa->getCursor()->reiniciarCursor();
            while (mapa->getCursor()->avanzarCursor())
            {
                mapa->getCursor()->getCursor()->reiniciarCursor();
                while (mapa->getCursor()->getCursor()->avanzarCursor())
                {
                    if (!mapa->getCursor()->getCursor()->getCursor()->esActiva())
                    {
                        mapa->getCursor()->getCursor()->getCursor()->restarTurnoInactividad();
                    }
                }
            }
        }
    }

    Coordenada *getPosicionAleatoria() // OK
    {
        int x = getRandom(1, this->ancho);
        int y = getRandom(1, this->largo);
        int z = getRandom(1, this->alto);

        return new Coordenada(x, y, z);
    }

    Casilla *getCasillaAleatoriaVacia() // OK
    {
        Coordenada *ubicacionVacia = NULL;
        Casilla *resultado;
        while (ubicacionVacia == NULL)
        {
            Coordenada *posicionRandom = getPosicionAleatoria();
            resultado = getCasilla(posicionRandom);
            if (resultado->getTipo() == VACIO)
            {
                ubicacionVacia = posicionRandom;
            }
            else
            {
                delete posicionRandom;
            }
        }
        return resultado;
    }

    // Devuelve true solo si las componentes de la ubicacion dada son positivas y estan dentro del tamaño del tablero.
    bool laUbicacionEsValida(Coordenada *ubicacion) // OK
    {
        if (ubicacion->getX() <= this->ancho &&
            ubicacion->getX() > 0 &&
            ubicacion->getY() <= this->largo &&
            ubicacion->getY() > 0 &&
            ubicacion->getZ() <= this->alto &&
            ubicacion->getZ() > 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // POST: Devuelve un puntero a un con la posicion dada.//revisar
    Casilla *getCasilla(Coordenada *posicion)
    {
        return this->mapa->get(posicion->getZ())->get(posicion->getY())->get(posicion->getX());
    }

    // Devuelve la altura maxima que puede tener una posicion dentro del tablero
    int getAltura()
    {
        return this->alto;
    }

    // Devuelve el ancho maxima que puede tener una posicion dentro del tablero
    int getAncho()
    {
        return this->ancho;
    }

    // Devuelve el largo maxima que puede tener una posicion dentro del tablero
    int getLargo()
    {
        return this->largo;
    }

    ~Tablero() // Reemplazar fors por whiles, para ahorrar lecturas.
    {
        for (int i = ancho; i >= 1; i--)
        {
            for (int j = ancho; j >= 1; j--)
            {
                for (int k = ancho; k >= 1; k--)
                {
                    delete this->mapa->get(i)->get(j)->get(k);
                }
                delete this->mapa->get(i)->get(j);
            }

            delete this->mapa->get(i);
        }
        delete this->mapa;
    }

    bool sonVecinas(Casilla *a, Casilla *b)
    {
        bool sonVecinas = false;
        int i, j, k = 0;

        Casilla ****vecinosDeA = a->getVecinos();

        while (!sonVecinas && i < 3)
        {
            while (!sonVecinas && j < 3)
            {
                while (!sonVecinas && k < 3)
                {
                    if (vecinosDeA[i][j][k]->getUbicacion()->esIgualA(b->getUbicacion()) &&
                        vecinosDeA[i][j][k]->esActiva())
                    {
                        sonVecinas = true;
                    }
                }
            }
        }
    }

    void colococarAleatoriamente(Jugador *jugador, TipoUnidad tipo)
    {
        Casilla *casilla = getCasillaAleatoriaVacia();

        casilla->setDuenio(jugador->getId());
        casilla->setTipo(tipo);

        jugador->agregarUnidad(casilla);
    }

    Lista<Lista<Lista<Casilla *> *> *> *getTablero() const
    {
        return this->mapa;
    }
};

#endif