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
    int turnosInactiva;
    enum tipoTerreno
    {
        TIERRA,
        MAR,
        AIRE
    };
public:

    Casilla(Coordenada &ubicacion, tipoTerreno terreno)
    {
        Casilla(ubicacion, terreno, NULL, VACIO)
    }
    

    Casilla(Coordenada &ubicacion, tipoTerreno terreno, Jugador* jugadorEnCasilla, tipoOcupante unidad){
        this->ubicacion = coordenada(ubicacion);
        this->jugadorPosicion = jugadorEnCasilla;
        this->tipoOcupante = unidad;
        this->turnosInactiva = 0;
        this->tipoTerreno = terreno;
    }

    //POST: Cambia el jugador que es dueño de la unidad o mina dentro de la casilla .
    void setJugadorCasilla(Jugador *jugador){
        this->jugadorPosicion = jugador;
    }

    //POST: Devuelve el jugador que es dueño de la unidad o mina dentro de la casilla.
    Jugador *getJugadorCasilla(){
        return this->jugadorPosicion;
    }

    //POST: Cambia el tipo del terreno al tipo pasado como argumento.
    void setTipoTerreno(tipoTerreno tipo){
        this->tipoTerreno = tipo;
    }

    //POST: Devuelve el tipo de terreno de la casilla.
    tipoTerreno getTipoTerreno(){
        return this->tipoTerreno;
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
};

#endif