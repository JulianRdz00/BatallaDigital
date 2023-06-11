#ifndef __CONSTANTES__
#define __CONSTANTES__

#include <cstdlib>

static const char ICONO_MAR = '~';
static const char ICONO_AIRE = ' ';
static const char ICONO_TIERRA = '#';






static const char ICONO_CASILLA_VACIA = 'X';


static const int EMPATE = 98;
static const int UNGANADOR = 99;

int getRandom(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

#endif
