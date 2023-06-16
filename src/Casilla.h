#ifndef _CASILLA_H_
#define _CASILLA_H_

#include "Constantes.h"
#include "Coordenada.h"
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
    Unidad *getUnidad()
    {
        return this->unidad;
    }

    TipoTerreno getTerreno();
};

#endif