#include "Unidad.h"

    /*
    Pre:-
    Post: Crea una unidad con coordenadas default (-1, -1, -1), sin duenio y de tipo VACIO
    */
    Unidad::Unidad()
    {
        this->setUbicacion(new Coordenada());
        this->setDuenio(NULL);
        this->setTipo(VACIO);
        this->setActiva();
    }

    /*
    Pre:-
    Post: Crea una unidad con coordenadas segun las pasadas como argumento, sin duenio y de tipo VACIO
    */
    Unidad::Unidad(Coordenada *ubicacion)
    {
        this->setUbicacion(ubicacion);
        this->setDuenio(NULL);
        this->setTipo(VACIO);
        this->setActiva();
    }

    /*
    Pre:-
    Post: Crea una unidad con coordenadas, duenio y tipo segun lo pasado como argumento
    */
    Unidad::Unidad(Coordenada *ubicacion, Jugador *duenio, TipoUnidad tipoDeUnidad)
    {
        this->setUbicacion(ubicacion);
        this->setDuenio(duenio);
        this->setTipo(tipo);
        this->setActiva();
    }

    /*
    Pre:-
    Post: Elimina la unidad y la coordenada asignada
    */
    Unidad::~Unidad()
    {
        this->ubicacion->~Coordenada();
    }

    /*
    Pre:-
    Post: Activa la unidad
    */
    Unidad::void setActiva()
    {
        this->turnosInactiva = 0;
    }

    /*
    Pre:-
    Post: Desactiva la unidad por la cantidad de turnos pasados como argumento
    */
    Unidad::void desactivar(int turnos)
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

    /*
    Pre:-
    Post: Resta 1 a la cantidad de turnos para la casilla inactiva
    */
    Unidad::void restarTurnoInactiva()
    {
        this->turnosInactiva--;
    }

    /*
    Pre:-
    Post: devuelve true o false en funcion si la casilla esta activa o no
    */
    Unidad::bool esActiva()
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

    /*
    Pre:-
    Post: Cambia el jugador que es dueño de la unidad o mina dentro de la casilla
    */
    Unidad::void setDuenio(Jugador *jugador)
    {
        this->jugadorPosicion = jugador;
    }

    /*
    Pre:-
    Post: Devuelve el jugador que es dueño de la unidad o mina dentro de la casilla
    */
    Unidad::Jugador *getDuenio()
    {
        return this->jugadorPosicion;
    }

    /*
    Pre:-
    Post: Cambia el tipo de la unidad
    */
    Unidad::void setTipo(TipoUnidad tipo)
    {
        this->tipo = tipo;
    }

    /*
    Pre:-
    Post: Devuelve el tipo de la unidad
    */
    Unidad::TipoUnidad getTipo()
    {
        return this->tipo;
    }

    /*
    Pre:-
    Post: Cambia la ubicacion de la unidad segun la coordenada pasada como argumento
    */
    Unidad::void setUbicacion(Coordenada *nuevaPosicion)
    {
        this->ubicacion = new Coordenada(nuevaPosicion);
    }

    /*
    Pre:-
    Post: Devuelve la ubicacion de la unidad
    */
    Unidad::Coordenada *getUbicacion()
    {
        return this->ubicacion;
    }

#endif
