#include "Casilla.h"


Casilla::Casilla()
{
    this->unidad = NULL;
    this->terreno = AIRE;
}

Casilla::Casilla(Unidad *unidad, TipoTerreno terreno)
{
    this->unidad = unidad;
    this->terreno = terreno;
}

Unidad *Casilla::getUnidad()
{
    return this->unidad;
}

TipoTerreno Casilla::getTerreno()
{
    return this->terreno;
}
