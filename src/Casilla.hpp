#ifndef _CASILLA_H_
#define _CASILLA_H_

#include "Unidad.hpp"
#include "Constantes.hpp"

class Casilla
{
private:
    Unidad *unidad;
    TipoTerreno terreno;

public:
    Casilla()
    {
        this->unidad = NULL;
        this->terreno = AIRE;
    }

    Casilla(Unidad *unidad, TipoTerreno terreno)
    {
        this->unidad = unidad;
        this->terreno = terreno;
    }

    Unidad *getUnidad()
    {
        return this->unidad;
    }

    TipoTerreno getTerreno()
    {
        return this->terreno;
    }
};

#endif