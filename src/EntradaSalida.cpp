#include "EntradaSalida.h"

Coordenada *EntradaSalida::pedirCoordenada()
{
    int x, y, z;
    std::cout << "Ingrese la coordenada x" << std::endl;
    std::cin >> x;
    std::cout << "Ingrese la coordenada y" << std::endl;
    std::cin >> y;
    std::cout << "Ingrese la coordenada z" << std::endl;
    std::cin >> z;
    std::cout << std::endl;

    return new Coordenada(x, y, z);
}

EntradaSalida::EntradaSalida()
{

}

Coordenada *EntradaSalida::coordenadaSoldadoExistente()
{
    std::cout << "Que soldado desea mover? " << std::endl;

    return pedirCoordenada();
}

Coordenada *EntradaSalida::preguntarDondeMoverUnidad()
{
    std::cout << "Ingrese una nueva posicion para la unidad";
    return pedirCoordenada();
}

Coordenada *EntradaSalida::preguntarUnidadAMover(Jugador *jugador)
{
    bool buscando = true;
    Coordenada *posicion;
    std::cout << "Escriba las coordenadas del soldado o armamento a mover";
    while (buscando)
    {
        posicion = pedirCoordenada();
        jugador->getSoldados()->reiniciarCursor();
        while (jugador->getSoldados()->avanzarCursor())
        {
            if (jugador->getSoldados()->getCursor()->getUbicacion()->esIgualA(posicion))
            {
                posicion = false;
            }
        }
        jugador->getArmamentos()->reiniciarCursor();
        while (jugador->getArmamentos()->avanzarCursor())
        {
            if (jugador->getArmamentos()->getCursor()->getUbicacion()->esIgualA(posicion))
            {
                buscando = false;
            }
        }
    }
}

Coordenada *EntradaSalida::preguntarDondeColocarMina()
{
    std::cout << "Donde quiere colocar una mina? " << std::endl;
    return pedirCoordenada();
}

bool EntradaSalida::preguntarSiUsarCarta(Jugador *jugador)
{
    char respuesta = 'X';
    bool respuestaInvalida = true;
    bool seUsaCarta = false;
    std::cout << "Queres usar una carta?" << std::endl;
    std::cout << "[S]Si [N]No" << std::endl;
    std::cin >> respuesta;
    std::cout << std::endl;

    while (respuestaInvalida)
    {
        if (respuesta == 'S')
        {
            std::cout << "Se decidio utilizar una carta" << std::endl;
            seUsaCarta = true;
            respuestaInvalida = false;
        }
        else if (respuesta == 'N')
        {
            std::cout << "Se decidio no utilizar ninguna carta" << std::endl;
            seUsaCarta = false;
            respuestaInvalida = false;
        }
    }

    return 0;
}

void EntradaSalida::listarCartas(Jugador *jugador)
{
    Lista<Carta *> *cartas = jugador->getMano();
    cartas->reiniciarCursor();
    int i = 1;
    while (cartas->avanzarCursor())
    {
        std::cout << "[" << i << "] :" << cartas->getCursor()->getNombre() << std::endl;
        i++;
    }
}

unsigned int EntradaSalida::elejirCartaParaJugar(Jugador *jugador)
{

    TipoDeCarta cartaElejida;
    bool respuestaInvalida = true;

    unsigned int indice = 0;
    Lista<Carta *> *cartas = jugador->getMano();
    while (respuestaInvalida)
    {
        std::cout << "Elije una carta valida [X]:\n";
        std::cin >> indice;
        if ((indice > 0) & (indice < cartas->contarElementos()))
        {
            respuestaInvalida = false;
        }
    }

    return indice;
}

int EntradaSalida::preguntarEnteroPositivo(std::string pregunta)
{
    int variable = 0;
    while (variable < 1)
    {
        std::cout << pregunta << std::endl;
        std::cout << "Debe ser un numero positivo" << std::endl;
        std::cin >> variable;
    }
    return variable;
}

void EntradaSalida::inicializarPartida(int &ancho, int &largo, int &alto, int &cantidadJugadores, int &soldadosPorJugador)
{
    bool invalido = true;
    while (invalido)
    {

        int ancho = preguntarEnteroPositivo("ingrese el Ancho del tablero.");
        int largo = preguntarEnteroPositivo("ingrese el Ancho del tablero.");
        int alto = preguntarEnteroPositivo("ingrese el Ancho del tablero.");

        int cantidadJugadores = preguntarEnteroPositivo("ingrese la cantidad de jugadores.");
        int cantidadSoldadosPorJugador = preguntarEnteroPositivo("ingrese la cantidad de soldados iniciales para cada jugador.");

        int espaciosNecesarios = cantidadJugadores * cantidadSoldadosPorJugador;
        int espaciosTotales = ancho * largo * alto;

        if (espaciosNecesarios * 2 < espaciosTotales)
        {
            std::cout << "El tamanio del tablero no cumple los requisitos de tamanio para la cantidad de jugadores y soldados. \n";
        }
        else
        {
            std::cout << "Datos correctos.\n";
            invalido = false;
        }
    }
}

EntradaSalida::~EntradaSalida()
{

}
