#include "Unidad.h"

Unidad::Unidad()
{
    this->setUbicacion(new Coordenada());
    //this->setDuenio(NULL);
    this->setTipo(VACIO);
    this->setActiva();
}

Unidad::Unidad(Coordenada *ubicacion)
{
    this->setUbicacion(ubicacion);
    //this->setDuenio(NULL);
    this->setTipo(VACIO);
    this->setActiva();
}

Unidad::Unidad(Coordenada *ubicacion, TipoUnidad tipoDeUnidad)
{
    this->setUbicacion(ubicacion);
    this->setTipo(tipo);
    this->setActiva();
}

Unidad::~Unidad()
{
    this->ubicacion->~Coordenada();
}

void Unidad::setActiva()
{
    this->turnosInactiva = 0;
}

void Unidad::desactivar(int turnos)
{
    if (turnos > 0)
    {
        this->turnosInactiva = turnos;
    }
    else
    {
        this->turnosInactiva = 1;
    }
}

void Unidad::restarTurnoInactiva()
{
    this->turnosInactiva--;
}

bool Unidad::esActiva()
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

void Unidad::setTipo(TipoUnidad tipo)
{
    this->tipo = tipo;
}

TipoUnidad Unidad::getTipo()
{
    return this->tipo;
}

void Unidad::setUbicacion(Coordenada *nuevaPosicion)
{
    this->ubicacion = new Coordenada(nuevaPosicion);
}

Coordenada *Unidad::getUbicacion()
{
    return this->ubicacion;
}
