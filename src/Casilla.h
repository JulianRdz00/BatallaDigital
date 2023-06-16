#ifndef _CASILLA_H_
#define _CASILLA_H_

#include "Constantes.hpp"
#include "Coordenada.hpp"
#include "Unidad.hpp"


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