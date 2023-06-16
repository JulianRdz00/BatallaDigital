/* MATEO Intento 1*/

#ifndef _ENTRADASALIDA_H_
#define _ENTRADASALIDA_H_

#include "Constantes.hpp"
#include "Lista.hpp"
#include "Carta.hpp"
#include "Jugador.hpp"

class EntradaSalida
{
public:
    /*  POS: devuelve el valor de la coordenada ingresada por consola */
    Coordenada *pedirCoordenada()
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
    /*  POS: */
    EntradaSalida();

    /* POS: pregunta que soldado se desea mover y devuelve la coordenada cuyo nombre es nombreCoordenada
    int coordenadaSoldadoExistente(string nombreCoordenada)
    {
        cout << "Que soldado desea mover? " << endl;

        return pedirCoordenada(nombreCoordenada);
    }*/

    Coordenada *preguntarDondeMoverUnidad()
    {
        std::cout << "Ingrese una nueva posicion para la unidad";
        return pedirCoordenada();
    }

    /*  POS: pregunta a donde quiere mover su soldado y devuelve la coordenada cuyo nombre es nombreCoordenada */
    Coordenada *coordenadaNuevoLugar()
    {
        std::cout << "Donde quiere mover su soldado? " << std::endl;
        return pedirCoordenada();
    }

    Coordenada *preguntarUnidadAMover(Jugador *jugador)
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
                if (jugador->getSoldados()->getCursor()->getUbicacion().esIgualA(*posicion))
                {
                    posicion = false;
                }
            }
            jugador->getArmamentos()->reiniciarCursor();
            while (jugador->getArmamentos()->avanzarCursor())
            {
                if (jugador->getArmamentos()->getCursor()->getUbicacion().esIgualA(*posicion))
                {
                    buscando = false;
                }
            }
        }
    }

    /*  POS: pregunta a donde quiere colocar una mina y devuelve la coordenada cuyo nombre es nombreCoordenada*/
    Coordenada *preguntarDondeColocarMina()
    {
        std::cout << "Donde quiere colocar una mina? " << std::endl;
        return pedirCoordenada();
    }

    /*  POS: devuelve un string con el nombre de la carta a jugar y en caso de no jugar carta devuelve 0
    REVISAR lista de cartas mano (const) */
    bool preguntarSiUsarCarta(Jugador *jugador)
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

    void listarCartas(Jugador *jugador)
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

    /*  POS: Devuelve el indice de la carta a jugar. */
    unsigned int elejirCartaParaJugar(Jugador *jugador)
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

    /*  PRE: La respuesta introducida por consola debe ser un numero.
        POS: Pregunta por consola que se introduzca un numero entero positivo, continuara preguntando hasta que la respuesta sea valida */
    int preguntarEnteroPositivo(std::string pregunta)
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

    /*  POS: devuelve un puntero a un Juego con unos parametros elejidos por el usuario. */
    void inicializarPartida(int &ancho, int &largo, int &alto, int &cantidadJugadores, int &soldadosPorJugador)
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

    ~EntradaSalida();
};

#endif