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

TipoUnidad Casilla::getTipo()
{
    return this->tipo;
}

void Casilla::setTipo(TipoUnidad tipo)
{
    this->tipo = tipo;
}

Coordenada *Casilla::getUbicacion()
{
    return this->ubicacion;
}

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

void Casilla::setTerreno(TipoTerreno terreno)
{
    this->terreno = terreno;
}

void Casilla::desactivar(unsigned int cantidadDeTurnos)
{
    this->turnosInactiva = cantidadDeTurnos;
}

void Casilla::restarTurnoInactividad()
{
    if (turnosInactiva > 0)
    {
        (this->turnosInactiva)--;
    }
}

bool Casilla::esActiva()
{
    if (this->turnosInactiva < 1)
    {
        return true;
    }
    else
    {
        return false;
    }
}

unsigned int Casilla::getIdDuenio(){
    return this->idDuenio;
}

void Casilla::setDuenio(unsigned int id){
    this->idDuenio = id;
}

Casilla::~Casilla()
{
}
