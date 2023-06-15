/* MATEO Intento 1*/

#ifndef _ENTRADASALIDA_
#define _ENTRADASALIDA_

#include <iostream>
#include "Lista.hpp"
#include "Carta.hpp"
#include "Jugador.hpp"

class EntradaSalida
{
private:
    /*POS: devuelve el valor de la coordenada ingresada por consola */

    Coordenada pedirCordenada()
    {
        int x, y, z;
        std::cout << "Ingrese la coordenada x" << std::endl;
        std::cin >> x;
        std::cout << "Ingrese la coordenada y" << std::endl;
        std::cin >> y;
        std::cout << "Ingrese la coordenada z" << std::endl;
        std::cin >> z;
        std::cout << std::endl;

        return Coordenada(x, y, z);
    }

public:
    EntradaSalida();

    /*POS: pregunta que soldado se desea mover y devuelve la coordenada cuyo nombre es nombreCoordenada */

    int coordenadaSoldadoExistente(string nombreCoordenada)
    {

        cout << "Que soldado desea mover? " << endl;

        return pedirCordenada(nombreCoordenada);
    }

    /*POS: pregunta a donde quiere mover su soldado y devuelve la coordenada cuyo nombre es nombreCoordenada */

    int coordenadaNuevoLugar(string nombreCoordenada)
    {

        cout << "Donde quiere mover su soldado? " << endl;

        return pedirCordenada(nombreCoordenada);
    }

    /*POS: pregunta a donde quiere colocar una mina y devuelve la coordenada cuyo nombre es nombreCoordenada*/

    Coordenada preguntarDondeColocarMina()
    {
        std::cout << "Donde quiere colocar una mina? " << std::endl;
        return pedirCordenada();
    }

    /*POS: devuelve un string con el nombre de la carta a jugar y en caso de no jugar carta devuelve 0
    REVISAR lista de cartas mano (const)
    */
    bool preguntarSiUsarCarta(Jugador &jugador)
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

    void listarCartas(Jugador &jugador)
    {
        Lista<Carta *> *cartas = jugador.getListaDeCartas();
        cartas->reiniciarCursor();
        int i = 1;
        while (cartas->avanzarCursor())
        {
            std::cout << "[" << i << "] :" << cartas->getCursor()->getNombre() << std::endl;
            i++;
        }
    }

    //Devuelve el indice de la carta a jugar.
    unsigned int elejirCartaParaJugar(Jugador &jugador)
    {

        TipoDeCarta cartaElejida;
        bool respuestaInvalida = true;

        unsigned int indice = 0;
        Lista<Carta *> *cartas = jugador.getListaDeCartas();
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

    ~EntradaSalida();
};

#endif