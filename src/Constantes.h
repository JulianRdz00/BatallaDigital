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

static const int CANTIDAD_TIPOS_DE_CARTAS = 6;

static const int CANTIDAD_TURNOS_INACTIVOS_MINA = 6;

static const int COLOR_AGUA_R =0;
static const int COLOR_AGUA_G =180;
static const int COLOR_AGUA_B =255;

static const int COLOR_TIERRA_R =210;
static const int COLOR_TIERRA_G =180;
static const int COLOR_TIERRA_B =110;

static const int COLOR_AIRE_R =240;
static const int COLOR_AIRE_G =240;
static const int COLOR_AIRE_B =240;

static const int COLOR_MINA_R =255;
static const int COLOR_MINA_G =55;
static const int COLOR_MINA_B =20;

static const int COLOR_INACTIVA_R =55;
static const int COLOR_INACTIVA_G =255;
static const int COLOR_INACTIVA_B =100;

static const int COLOR_BARCO_R =255;
static const int COLOR_BARCO_G =255;
static const int COLOR_BARCO_B =255;

static const int COLOR_AVION_R =0;
static const int COLOR_AVION_G =0;
static const int COLOR_AVION_B =0;

static const int COLOR_BORDES_R =220;
static const int COLOR_BORDES_G =220;
static const int COLOR_BORDES_B =220;


// POST: Devuelve un numero aleatorio entre el minimo y maximo dados como argumentos.
int getRandom(int minimo, int maximo);

#endif
