#include "Casilla.h"

Casilla::Casilla()
{
    this->terreno = AIRE;
    this->tipo = VACIO;
    this->vecinos = NULL;
    this->turnosInactiva = 0;
    this->ubicacion = NULL;
}

Casilla::Casilla(TipoTerreno terreno, Coordenada *posicion)
{
    this->terreno = terreno;
    this->tipo = VACIO;
    this->vecinos = NULL;
    this->turnosInactiva = 0;
    this->ubicacion = posicion;
}

TipoUnidad Casilla::getUnidad()
{
    return this->tipo;
}

/*PRE:  x,y,z son valores en el intervalo [-1, 1] y no pueden ser todos 0.*/
/*Post: Devuelve la casilla en una posicion relativa a si misma*/
Casilla ****Casilla::getVecinos()
{
    return this->vecinos;
}

void Casilla::setVecinos(Casilla ****vecinos)
{
    this->vecinos = vecinos;
}

TipoTerreno Casilla::getTerreno()
{
    return this->terreno;
}
