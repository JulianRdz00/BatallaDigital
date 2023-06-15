#ifndef __CONSTANTES__
#define __CONSTANTES__

#include <cstdlib>
#include <iostream>


static const char ICONO_MAR = '~';
static const char ICONO_AIRE = ' ';
static const char ICONO_TIERRA = '#';
const enum tipoTerreno
{
    TIERRA,
    AGUA,
    AIRE
};

enum tipoOcupante
{
    AVION,
    BARCO,
    MINA,
    SOLDADO,
    VACIO
};

enum EstadoJugador
{
    VIVO,
    MUERTO,
    SALTEADO,
};

static const int PROFUNDIDAD_TABLERO_DEFAULT = 10;
static const int LARGO_TABLERO_DEFAULT = 10;
static const int ALTO_TABLERO_DEFAULT = 10;
static const int TAMANIO_LADO_CASILLA_DEFAULT = 10;
static const int TAMANIO_OCUPANTE_DEFAULT = TAMANIO_LADO_CASILLA_DEFAULT / 2;
static const int CANTIDAD_JUGADORES_DEFAULT = 2;
static const int CANTIDAD_SOLDADOS_DEFAULT = 3;

static const char ICONO_CASILLA_VACIA = 'X';

static const int EMPATE = 98;
static const int UNGANADOR = 99;

static const int CANTIDAD_TIPOS_DE_CARTAS = 6;

static enum TipoDeCarta
{
	SUPERMINA,
	RADAR,
	ATAQUEQUIMICO,
	BARCO,
	DESTRUCTORARMAMENTO,
	PASARTURNO
};

static enum TipoUnidad {
    AVION,
    BARCO,
    MINA,
    SOLDADO,
    QUIMICO,
    VACIO
};

static enum TipoTerreno {
    TIERRA,
    MAR,
    AIRE
};

// POST: Devuelve un numero aleatorio entre el minimo y maximo dados como argumentos.
int getRandom(int minimo, int maximo)
{
    return minimo + (rand() % (maximo - minimo + 1));
}

#endif
