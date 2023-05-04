#ifndef __CONSTANTES__
#define __CONSTANTES__

#include <unistd.h>
#include <cstdlib>

static const char ICONO_MAR = '~';
static const char ICONO_AIRE = ' ';
static const char ICONO_TIERRA = '#';

int getRandom(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

void wait(int milisegundos)
{
    usleep(milisegundos * 1000); // sleeps for 3 second
}

#endif
