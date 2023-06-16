#ifndef _JUGADOR_H_
#define _JUGADOR_H_

#include "Constantes.hpp"
#include "Lista.hpp"
#include "Unidad.hpp"
#include "Carta.hpp"
<<<<<<< Updated upstream
#include "Coordenada.hpp"
#include "Constantes.hpp"

=======
<<<<<<< Updated upstream
=======
#include "Coordenada.hpp"
#include "Unidad.hpp"

>>>>>>> Stashed changes
>>>>>>> Stashed changes

class Jugador
{
private:
    unsigned int id;
    Lista<Carta *> *mano;
    Lista<Unidad *> *soldados;
    Lista<Unidad *> *minas;
    Lista<Unidad *> *armamentos;
    EstadoJugador estado;
    bool estaSalteado;

    /*
    Pre:-
    Post: Crea todos los soldados del jugador con las coordenadas default (-1, -1, -1).
    */
    void crearSoldados(int cantidadDeSoldados)
    {
        for (int i = 0; i < cantidadDeSoldados; i++)
        {
            this->soldados->add(new Unidad(Coordenada(), this, SOLDADO));
        }
    }

    /*
    Pre:-
    Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
    */
    void deleteMano()
    {
        mano->reiniciarCursor();
        while (mano->avanzarCursor())
        {
            mano->getCursor()->~Carta();
        }
    }

    /*
    Pre:-
    Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
    */
    void deleteSoldados()
    {
        soldados->reiniciarCursor();
        while (soldados->avanzarCursor())
        {
            soldados->getCursor()->~Unidad();
        }
    }

    /*
    Pre:-
    Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
    */
    void deleteMinas()
    {
        minas->reiniciarCursor();
        while (minas->avanzarCursor())
        {
            minas->getCursor()->~Unidad();
        }
    }

    /*
    Pre:-
    Post: Recorre la lista de cartar para eliminar cada carta de la memoria dinamica
    */
    void deleteArmamentos()
    {
        armamentos->reiniciarCursor();
        while (armamentos->avanzarCursor())
        {
            armamentos->getCursor()->~Unidad();
        }
    }


public:
    /*
    Pre:-
    Post: Crea un de jugador con la cantidad de soldados default
    */
    Jugador()
    {
        mano = new Lista<Carta *>();
        soldados = new Lista<Unidad *>();
        minas = new Lista<Unidad *>();
        armamentos = new Lista<Unidad *>();
        estado = VIVO;
        estaSalteado = false;
        crearSoldados(CANTIDAD_SOLDADOS_DEFAULT);
    }

    /*
    Pre:-
    Post: Crea una instancia de jugador con la cantidad de soldados pasados como argumento
    */
    Jugador(int cantidadDeSoldados)
    {
        mano = new Lista<Carta *>();
        soldados = new Lista<Unidad *>();
        minas = new Lista<Unidad *>();
        armamentos = new Lista<Unidad *>();
        estado = VIVO;
        estaSalteado = false;
        crearSoldados(cantidadDeSoldados);
    }

    /*
    Pre:-
    Post: Devuelve el estado del jugador
    */
    EstadoJugador getEstado()
    {
        return this->estado;
    }

    /*
    Pre: La nueva carta debe existir
    Post: Agrega la carta pasada como argumento a la mano del jugador
    */
    void agregarCartaAMano(Carta *nuevaCarta)
    {
        if (nuevaCarta == NULL)
        {
            throw "La carta no existe";
        }

        mano->add(nuevaCarta);
    }

    /*
    Pre:-
    Post: Devuelve la cantidad de cartas del jugador
    */
    int cantidadDeCartas()
    {
        return this->mano->contarElementos();
    }

    /*
    Pre:-
    Post: Devuelve las cartas que tiene el jugador
    */
    Lista<Carta *> *getMano()
    {
        return this->mano;
    }

    /*
    Pre:-
    Post: Devuelve los soldados que tiene el jugador
    */
    Lista<Unidad *> *getSoldados()
    {
        return this->soldados;
    }

    /*
    Pre:-
    Post: Devuelve las minas que tiene el jugador
    */
    Lista<Unidad *> *getMinas()
    {
        return this->minas;
    }

    /*
    Pre:-
    Post: Devuelve los armamentos que tiene el jugador
    */
    Lista<Unidad *> *getArmamentos()
    {
        return this->armamentos;
    }

    /*
    Pre:-
    Post: Cambia el estado del jugador
    */
    void setEstado(EstadoJugador estado)
    {
        this->estado = estado;
    }

    /*
    Pre:-
    Post: Cambia el estado salteado del jugador
    */
    void setEstadoSalteado(bool estado)
    {
        estaSalteado = estado;
    }

    /*
    Pre:-
    Post: Devuelve true o false en funcion de si el jugador esta salteado o no
    */
    bool estaSaleado()
    {
        return this->estaSalteado;
    }

    /*
    Pre:-
    Post: Devuelve el id del jugador
    */
    unsigned int getId()
    {
        return this->id;
    }

    /*
    Pre:-
    Post: Elimina al jugador con sus cartas, soldados, minas y Armamentos
    */
    virtual ~Jugador()
    {
        deleteMano();
        delete mano;
        deleteSoldados();
        delete soldados;
        deleteMinas();
        delete minas;
        deleteArmamentos();
        delete armamentos;
    }
};

#endif
