#ifndef _CASILLA_
#define _CASILLA_

#include "Coordenada.hpp"
#include "Unidad.hpp"
#include "Constantes.hpp"

class Casilla
{
private:
    Coordenada ubicacion;
    Jugador *jugadorPosicion;
    enum tipoOcupante
    {
        AVION,
        BARCO,
        MINA,
        SOLDADO,
        VACIO
    };
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
        this->tipoOcupante = VACIO;
        esActiva = true;
        this->jugadorPosicion = NULL;
    }

    void setJugadorCasilla(Jugador *jugador){
        this->jugadorPosicion = jugador;
    }

    Jugador *getJugadorCasilla(){
        return this->jugadorPosicion;
    }

    void setTipoOcupante(std::string ocupante)
    {
        this->tipoOcupante = ocupante;   
    }

    std::string getTipoOcupante(){
        return this->tipoOcupante;
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
        switch (tipoOcupante)
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