#include "Juego.h"


void preguntarUsoCarta()
{
    bool seUsaCarta = io->preguntarSiUsarCarta(jugadorActivo->getValor());
    if (seUsaCarta)
    {
        unsigned int indiceDeCarta = io->elejirCartaParaJugar(jugadorActivo->getValor());
        jugadorActivo->getValor()->getMano()->get(indiceDeCarta)->usar(mapa, io, jugadorActivo->getValor());
        jugadorActivo->getValor()->getMano()->remover(indiceDeCarta);
    }
    else
    {
        std::cout << "No se usa ninguna carta\n";
    }
}

void pasarTurno()
{

}
