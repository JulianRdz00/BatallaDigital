#include "Tablero.h"

    Casilla ****Tablero::buscarVecinos(Coordenada *posicion)
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

    Tablero::Tablero(int ancho, int largo, int alto)
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

    void Tablero::disminuirTurnosInactivos()
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

    Coordenada *Tablero::getPosicionAleatoria()
    {
        int x = getRandom(1, this->ancho);
        int y = getRandom(1, this->largo);
        int z = getRandom(1, this->alto);

        return new Coordenada(x, y, z);
    }

    Casilla *Tablero::getCasillaAleatoriaVacia()
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

    bool Tablero::laUbicacionEsValida(Coordenada *ubicacion)
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

    Casilla *Tablero::getCasilla(Coordenada *posicion)
    {
        return this->mapa->get(posicion->getZ())->get(posicion->getY())->get(posicion->getX());
    }

    int Tablero::getAltura()
    {
        return this->alto;
    }

    int Tablero::getAncho()
    {
        return this->ancho;
    }

    int Tablero::getLargo()
    {
        return this->largo;
    }

    Tablero::~Tablero()
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

    bool Tablero::sonVecinas(Casilla *a, Casilla *b)
    {
        bool sonVecinas = false;
        int i = 0;
        int j = 0;
        int k = 0;

        Casilla ****vecinosDeA = a->getVecinos();

        while (!sonVecinas && i < 3)
        {
            j=0;
            while (!sonVecinas && j < 3)
            {
                k=0;
                while (!sonVecinas && k < 3)
                {
                    if (vecinosDeA[i][j][k]->getUbicacion()->esIgualA(b->getUbicacion()) &&
                        vecinosDeA[i][j][k]->esActiva())
                    {
                        sonVecinas = true;
                    }
                    k++;
                }
                j++;
            }
            i++;
        }
        return sonVecinas;
    }

    void Tablero::colococarAleatoriamente(Jugador *jugador, TipoUnidad tipo)
    {
        Casilla *casilla = getCasillaAleatoriaVacia();

        casilla->setDuenio(jugador->getId());
        casilla->setTipo(tipo);

        jugador->agregarUnidad(casilla);
    }

    Lista<Lista<Lista<Casilla *> *> *> * Tablero::getTablero()
    {
        return this->mapa;
    }
