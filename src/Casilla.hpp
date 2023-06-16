#ifndef _CASILLA_H_
#define _CASILLA_H_

<<<<<<< Updated upstream
=======
#include "Constantes.hpp"
>>>>>>> Stashed changes
#include "Coordenada.hpp"
#include "Constantes.hpp"
#include "Unidad.hpp"


class Casilla
{
private:
    Unidad* unidad;
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