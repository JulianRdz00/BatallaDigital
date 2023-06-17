#include "Carta.h"

Carta::Carta(TipoDeCarta tipo)
{
    this->tipo = tipo;
}

Carta::Carta()
{
    this->tipo = TipoDeCarta(getRandom(0, CANTIDAD_TIPOS_DE_CARTAS - 1));
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
        std::cout << NOMBRE_CARTA_SUPERMINA << std::endl;
        break;
    case RADAR:
        std::cout << NOMBRE_CARTA_RADAR << std::endl;
        break;
    case ATAQUEQUIMICO:
        std::cout << NOMBRE_CARTA_ATAQUEQUIMICO << std::endl;
        break;
    case USARBARCO:
        std::cout << NOMBRE_CARTA_USARBARCO << std::endl;
        break;
    case DESTRUCTORARMAMENTO:
        std::cout << NOMBRE_CARTA_DESTRUCTORARMAMENTO << std::endl;
        break;
    case PASARTURNO:
        std::cout << NOMBRE_CARTA_PASARTURNO << std::endl;
        break;
    }
}
