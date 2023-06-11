#ifndef _CASILLA_
#define _CASILLA_

#include "Coordenada.hpp"
#include "Unidad.hpp"
#include "Constantes.hpp"

class Casilla
{
private:
    Coordenada ubicacion;
    int tipo;
    enum tipoTerreno
    {
        TIERRA,
        MAR,
        AIRE
    };
    bool esActiva;

public:
    Casilla(Coordenada &ubicacion)
    {
        this->ubicacion = ubicacion;
        tipo = getRandom(0, 2);
        esActiva = true;
    }

    void setCoordenada(Coordenada &nuevaPosicion)
    {
        this->ubicacion = Coordenada(nuevaPosicion);
    }

    Coordenada getCoordenada()
    {
        return this->ubicacion;
    }

    char getIcono()
    {
        char icono;
        switch (tipo)
        {
        case AIRE:
            return ICONO_AIRE;
            break;
        case MAR:
            return ICONO_MAR;
            break;

        default:
            return ICONO_TIERRA;
            break;
        }
    }
};

#endif