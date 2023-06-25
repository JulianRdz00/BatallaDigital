#ifndef CASILLA_H
#define CASILLA_H

#include "Unidad.h"

class Casilla
{
private:
    TipoTerreno terreno;
    Casilla ****vecinos;
    Coordenada *ubicacion;
    TipoUnidad tipo;
    unsigned int idDuenio;
    int turnosInactiva;

public:
    Casilla();

    Casilla(TipoTerreno terreno, Coordenada *ubicacion);

    TipoUnidad getTipo();

    Coordenada* getUbicacion();

    /*PRE:  x,y,z son valores en el intervalo [-1, 1] y no pueden ser todos 0.*/
    /*Post: Devuelve la casilla en una posicion relativa a si misma*/
    Casilla ****getVecinos();

    void setVecinos(Casilla ****vecinos);

    TipoTerreno getTerreno();

    void setTipo(TipoUnidad tipo);

    void desactivar(int cantidadDeTurnos);

    bool esActiva();

};

#endif