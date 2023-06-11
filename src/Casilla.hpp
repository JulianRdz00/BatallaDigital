#ifndef _CASILLA_
#define _CASILLA_

#include "Coordenada.hpp"
#include "Unidad.hpp"
#include "Constantes.hpp"

template <class T>
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
    T *contenido;

public:
    Casilla(Coordenada &ubicacion)
    {
        this->ubicacion = ubicacion;
        tipo = getRandom(0, 2);
        esActiva = true;
        contenido = NULL;
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