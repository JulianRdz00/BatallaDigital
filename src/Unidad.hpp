#ifndef _UNIDAD_H_
#define _UNIDAD_H_

#include "Coordenada.hpp"
#include "Constantes.hpp"

class Unidad
{
private:
    Coordenada ubicacion;
    TipoUnidad tipo;
    Jugador *jugadorPosicion;
    int turnosInactiva;

public:
    Unidad()
    {
        this->setUbicacion(Coordenada());
        this->setDuenio(NULL);
        this->setTipo(VACIO);
        this->setActiva();
    }

    Unidad(Coordenada &ubicacion)
    {
        this->setUbicacion(ubicacion);
        this->setDuenio(NULL);
        this->setTipo(VACIO);
        this->setActiva();
    }

    Unidad(Coordenada &ubicacion, Jugador *duenio, TipoUnidad tipoDeUnidad)
    {
        this->setUbicacion(ubicacion);
        this->setDuenio(duenio);
        this->setTipo(tipo);
        this->setActiva();
    }

    void setActiva()
    {
        this->turnosInactiva = 0;
    }

    void desactivar(int turnos)
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

    bool esActiva()
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

    // POST: Cambia el jugador que es dueño de la unidad o mina dentro de la casilla .
    void setDuenio(Jugador *jugador)
    {
        this->jugadorPosicion = jugador;
    }

    // POST: Devuelve el jugador que es dueño de la unidad o mina dentro de la casilla.
    Jugador *getDuenio()
    {
        return this->jugadorPosicion;
    }

    void setTipo(TipoUnidad tipo)
    {
        this->tipo = tipo;
    }

    TipoUnidad getTipo()
    {
        return this->tipo;
    }

    void setUbicacion(Coordenada &nuevaPosicion)
    {
        this->ubicacion = Coordenada(nuevaPosicion);
    }

    Coordenada getUbicacion()
    {
        return this->ubicacion;
    }
};

#endif
