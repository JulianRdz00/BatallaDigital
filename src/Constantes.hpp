#ifndef __CONSTANTES__
#define __CONSTANTES__

#include <cstdlib>
#include <iostream>

static const char ICONO_MAR = '~';
static const char ICONO_AIRE = ' ';
static const char ICONO_TIERRA = '#';

enum EstadoPartida {
    EMPATE,
    TERMINADA,
    ENMARCHA
};

enum EstadoJugador {
    VIVO,
    MUERTO,
    SALTEADO,
};

enum TipoDeCarta {
    SUPERMINA,
    RADAR,
    ATAQUEQUIMICO,
    USARBARCO,
    DESTRUCTORARMAMENTO,
    PASARTURNO
};

enum TipoUnidad {
    AVION,
    BARCO,
    MINA,
    SOLDADO,
    QUIMICO,
    VACIO
};

enum TipoTerreno {
    TIERRA,
    MAR,
    AIRE
};

static const int PROFUNDIDAD_TABLERO_DEFAULT = 10;
static const int ANCHO_TABLERO_DEFAULT = 10;
static const int LARGO_TABLERO_DEFAULT = 10;
static const int ALTO_TABLERO_DEFAULT = 10;
static const int TAMANIO_LADO_CASILLA_DEFAULT = 10;
static const int TAMANIO_OCUPANTE_DEFAULT = TAMANIO_LADO_CASILLA_DEFAULT / 2;
static const int CANTIDAD_JUGADORES_DEFAULT = 2;
static const int CANTIDAD_SOLDADOS_DEFAULT = 3;

static const std::string NOMBRE_CARTA_SUPERMINA = "Super mina";
static const std::string NOMBRE_CARTA_RADAR = "Radar";
static const std::string NOMBRE_CARTA_ATAQUEQUIMICO = "Ataque quimico";
static const std::string NOMBRE_CARTA_USARBARCO = "Usar un barco";
static const std::string NOMBRE_CARTA_DESTRUCTORARMAMENTO = "Destruir armamentos";
static const std::string NOMBRE_CARTA_PASARTURNO = " Pasar turno";

static const char ICONO_CASILLA_VACIA = 'X';

static const int CANTIDAD_TIPOS_DE_CARTAS = 6;

// POST: Devuelve un numero aleatorio entre el minimo y maximo dados como argumentos.
int getRandom(int minimo, int maximo)
{
    return minimo + (rand() % (maximo - minimo + 1));
}

#endif
