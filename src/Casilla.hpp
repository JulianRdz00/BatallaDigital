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
    Unidad *ocupante;

public:
    Casilla()
    {
        tipo = getRandom(0,2);
        esActiva = true;
        ocupante = NULL;
    }

    char getIcono(){
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