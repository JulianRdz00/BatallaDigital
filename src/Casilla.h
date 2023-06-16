#ifndef CASILLA_H
#define CASILLA_H

#include "Unidad.h"

class Casilla
{
private:
    Unidad* unidad;
    TipoTerreno terreno;

public:
    Casilla();

    Casilla(Unidad *unidad, TipoTerreno terreno);

    Unidad *getUnidad();

    TipoTerreno getTerreno();
};

#endif