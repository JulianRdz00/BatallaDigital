#include "Constantes.h"


int getRandom(int minimo, int maximo)
{
    return minimo + (rand() % (maximo - minimo + 1));
}
