#ifndef CONSTANTES_H
#define CONSTANTES_H

#include <cstdlib>
#include <iostream>

enum EstadoPartida
{
    EMPATE,
    TERMINADA,
    ENMARCHA
};

enum EstadoJugador
{
    VIVO,
    MUERTO,
    SALTEADO,
};

enum TipoDeCarta
{
    SUPERMINA,
    RADAR,
    ATAQUEQUIMICO,
    USARBARCO,
    DESTRUCTORARMAMENTO,
    PASARTURNO
};

enum TipoUnidad
{
    AVION,
    BARCO,
    MINA,
    SOLDADO,
    VACIO,
};

enum TipoTerreno
{
    TIERRA,
    MAR,
    AIRE
};

static const int SIN_DUENIO = 314;

static const int PROFUNDIDAD_TABLERO_DEFAULT = 10;
static const int ANCHO_TABLERO_DEFAULT = 10;
static const int LARGO_TABLERO_DEFAULT = 10;
static const int ALTO_TABLERO_DEFAULT = 10;

static const int TAMANIO_LADO_CASILLA_DEFAULT = 64;
static const int TAMANIO_OCUPANTE_DEFAULT = TAMANIO_LADO_CASILLA_DEFAULT / 2;
static const int OFFSET_OCUPANTE_Y_CASILLA = TAMANIO_OCUPANTE_DEFAULT / 2;

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

static const int CANTIDAD_TURNOS_INACTIVOS_MINA = 6;

// POST: Devuelve un numero aleatorio entre el minimo y maximo dados como argumentos.
int getRandom(int minimo, int maximo);

#endif
