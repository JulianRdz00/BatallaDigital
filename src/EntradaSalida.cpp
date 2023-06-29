#include "EntradaSalida.h"

Coordenada *EntradaSalida::pedirCoordenada()
{
    int x, y, z;
    std::cout << "Ingrese la coordenada x: ";
    std::cin >> x;
    std::cout << "Ingrese la coordenada y: ";
    std::cin >> y;
    std::cout << "Ingrese la coordenada z: ";
    std::cin >> z;
    std::cout << std::endl;

    return new Coordenada(x, y, z);
}

EntradaSalida::EntradaSalida()
{
}

void EntradaSalida::anunciarJugador(Jugador *jugador)
{
    system("clear");
    std::cout << "TURNO DEL JUGADOR: " << jugador->getId() << "\n\n";
}

Coordenada *EntradaSalida::coordenadaSoldadoExistente()
{
    std::cout << "Que soldado desea mover? " << std::endl;

    return pedirCoordenada();
}

Coordenada *EntradaSalida::preguntarDondeMoverUnidad()
{
    std::cout << "Ingrese una nueva posicion para la unidad" << std::endl;
    return pedirCoordenada();
}

Casilla *EntradaSalida::preguntarUnidadAMover(Jugador *jugador) // OK
{
    bool buscando = true;
    Casilla *casilla;
    Coordenada *posicion;
    std::cout << "Escriba las coordenadas del soldado o armamento a mover" << std::endl;
    while (buscando)
    {
        posicion = pedirCoordenada();

        jugador->getSoldados()->reiniciarCursor();
        while (buscando && jugador->getSoldados()->avanzarCursor())
        {
            if (jugador->getSoldados()->getCursor()->getUbicacion()->esIgualA(posicion))
            {
                buscando = false;
                casilla = jugador->getSoldados()->getCursor();
            }
        }

        jugador->getArmamentos()->reiniciarCursor();
        while (buscando && jugador->getArmamentos()->avanzarCursor())
        {
            if (jugador->getArmamentos()->getCursor()->getUbicacion()->esIgualA(posicion))
            {
                buscando = false;
                casilla = jugador->getArmamentos()->getCursor();
            }
        }

        if (buscando)
        {
            delete posicion;
        }
    }
    return casilla;
}

Coordenada *EntradaSalida::preguntarDondeColocarMina()
{
    std::cout << "Donde quiere colocar una mina?" << std::endl;
    return pedirCoordenada();
}

void EntradaSalida::mostrarCoordenadasDeMinas(Lista<Casilla *> *minas)
{
    std::cout << "Hay Minas en las siguiente posicion\n";

    minas->reiniciarCursor();
    while (minas->avanzarCursor())
    {
        std::cout << "[" << minas->getCursor()->getUbicacion()->getX();
        std::cout << ";" << minas->getCursor()->getUbicacion()->getY();
        std::cout << ";" << minas->getCursor()->getUbicacion()->getZ() << "]\n";
    }
}

Coordenada *EntradaSalida::preguntarDondeColocarQuimico()
{
    std::cout << "Donde quiere iniciar el ataque quimico?\n"
              << std::endl;
    return pedirCoordenada();
}

bool EntradaSalida::preguntarSiUsarCarta(Jugador *jugador)
{
    char respuesta = 'X';
    bool respuestaInvalida = true;
    bool seUsaCarta = false;
    std::cout << "Queres usar una carta?" << std::endl;
    std::cout << "[S]Si [N]No:" << std::endl;
    while (respuestaInvalida)
    {
        std::cin >> respuesta;
        if (respuesta == 'S')
        {
            std::cout << "Se decidio utilizar una carta" << std::endl;
            seUsaCarta = true;
            respuestaInvalida = false;
            seUsaCarta = true;
            return seUsaCarta;
        }
        else if (respuesta == 'N')
        {
            std::cout << "Se decidio no utilizar ninguna carta" << std::endl;
            seUsaCarta = false;
            respuestaInvalida = false;
            seUsaCarta = false;
            return seUsaCarta;
        }
        else
        {
            std::cout << "Respuesta invalida, debe ser [S] o [N]\n";
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
    Lista<Carta *> *cartas = jugador->getMano();
    unsigned int indice = 0;
    int i = 1;
    while (respuestaInvalida)
    {
        i = 1;
        std::cout << "\nElije una carta valida [X]:\n";

        std::cin >> indice;
        if ((indice > 0) & (indice <= cartas->contarElementos()))
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

void EntradaSalida::inicializarPartida(int *ancho, int *largo, int *alto, int *cantidadJugadores, int *soldadosPorJugador)
{
    bool invalido = true;
    while (invalido)
    {

        *ancho = preguntarEnteroPositivo("ingrese el Ancho del tablero.");
        *largo = preguntarEnteroPositivo("ingrese el Largo del tablero.");
        *alto = preguntarEnteroPositivo("ingrese el Alto del tablero.");

        *cantidadJugadores = preguntarEnteroPositivo("ingrese la cantidad de jugadores.");
        *soldadosPorJugador = preguntarEnteroPositivo("ingrese la cantidad de soldados iniciales para cada jugador.");

        int espaciosNecesarios = (*cantidadJugadores) * (*soldadosPorJugador);
        int espaciosTotales = (*ancho) * (*largo) * (*alto);

        if (espaciosNecesarios * 2 > espaciosTotales)
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

Coordenada *EntradaSalida::preguntarDisparoBarco()
{
    std::cout << "Donde queres disparar el torpedo?" << std::endl;
    return pedirCoordenada();
}

EntradaSalida::~EntradaSalida()
{
}
