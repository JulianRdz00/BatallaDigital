#ifndef CARTA_H
#define CARTA_H

#include "Constantes.h"

class Carta
{
private:
    TipoDeCarta tipo;

public:
    /*Pre: El id debe ser mayor a 0
     *Post: Crea la carta con su tipo e id indicado
     */
    Carta(TipoDeCarta tipo);

    // Instancia una carta de tipo aleatorio.
    Carta();

    /*  Pos: Elimina la carta */
    virtual ~Carta();

    /*  Pos: Devuelve el tipo de la carta */
    TipoDeCarta getTipo();

    /*  Pos: Devuelve el nombre de la carta */
    std::string getNombre();
};

#endif