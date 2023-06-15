#ifndef _CASILLA_H_
#define _CASILLA_H_

<<<<<<< HEAD
#include "Coordenada.hpp"
=======
#include "Unidad.hpp"
>>>>>>> 88958a0ef9b45bc82e636766c0068c5fb73f3eae
#include "Constantes.hpp"


class Casilla
{
private:
<<<<<<< HEAD
    Coordenada ubicacion;
    Jugador *jugadorPosicion;
    tipoOcupante ocupante;
    int turnosInactiva;
    tipoTerreno terreno;
=======
    Unidad *unidad;
    TipoTerreno terreno;

>>>>>>> 88958a0ef9b45bc82e636766c0068c5fb73f3eae
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