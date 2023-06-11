#ifndef _JUGADOR_
#define _JUGADOR_

#include "Lista.hpp"
#include "Carta.hpp"
#include "Soldado.hpp"
#include "Mina.hpp"
#include "Armamento.hpp"

class Jugador
{
private:
    int id;
    Lista<Carta> *mano;
    Lista<Soldado> *Soldados;
    Lista<Mina> *minas;
    Lista<Armamento> *Armamentos;

public:
    Jugador()
    {
        mano = new Lista<Carta>();
    }

    void agregarCartaAMano(Carta *nuevaCarta)
    {
        mano->add(*nuevaCarta);
    }

    int cantidadDeCartas()
    {
        return mano->contarElementos();
    }

    const Lista<Carta> *getListaDeCartas()
    {
        return mano; // Revisar la encapsulacion
    }

   

        
};

