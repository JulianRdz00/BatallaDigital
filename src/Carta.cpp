#include "Carta.h"

Carta::Carta(TipoDeCarta tipo)
{
    this->tipo = tipo;
}

Carta::Carta()
{
    //this->tipo = TipoDeCarta(getRandom(0, CANTIDAD_TIPOS_DE_CARTAS - 1));
    this->tipo = TipoDeCarta(SUPERMINA);
}

Carta::~Carta()
{
}

TipoDeCarta Carta::getTipo()
{
    return this->tipo;
}

std::string Carta::getNombre()
{
    switch (tipo)
    {
    case SUPERMINA:
        return NOMBRE_CARTA_SUPERMINA;
        break;
    case RADAR:
        return NOMBRE_CARTA_RADAR;
        break;
    case ATAQUEQUIMICO:
        return NOMBRE_CARTA_ATAQUEQUIMICO;
        break;
    case USARBARCO:
        return NOMBRE_CARTA_USARBARCO;
        break;
    case DESTRUCTORARMAMENTO:
        return NOMBRE_CARTA_DESTRUCTORARMAMENTO;
        break;
    case PASARTURNO:
        return NOMBRE_CARTA_PASARTURNO;
        break;
    default:
        break;
    }
}
