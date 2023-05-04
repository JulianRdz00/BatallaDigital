#ifndef _JUGADOR_
#define _JUGADOR_

#include "Array.hpp"
#include "Carta.hpp"
#include "Soldado.hpp"
#include "Mina.hpp"
#include "Armamento.hpp"

class Jugador
{
private:
    int id;
    Array<Carta> mano;
    Array<Soldado> Soldados;
    Array<Mina> minas;
    Array<Armamento> Armamentos;
    

public:

};

#endif