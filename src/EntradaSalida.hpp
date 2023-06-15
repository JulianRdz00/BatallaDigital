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

    string pedirCarta(Jugador *jugador)
    {

        char respuesta;
        cout << "Queres usar una carta?" << endl;
        cout << "[S]Si [N]No" << endl;
        cin >> respuesta;
        cout << endl;

        if (respuesta == 'S')
        {
            const Lista<Carta> *mano = jugador->getListaDeCartas();

            mano->reiniciarCursor();
            while (mano->avanzarCursor())
            {
                string nombreCarta = mano->getCursor().getNombre();

                cout << "Desea jugar la carta: " << nombreCarta << endl;
                cout << "[S]Si [N]No" << endl;
                cin >> respuesta;
                cout << endl;

                if (respuesta == "S")
                {
                    return nombreCarta;
                }
            }
        }

        cout << "Se decidio no utilizar ninguna carta" << endl;
        return 0;
    }

    TipoDeCarta elejirCarta(Jugador &jugador)
    {

        TipoDeCarta cartaElejida;
        bool respuestaInvalida = true;

        std::cout << "Tus cartas disponibles:\n";
        int i = 1;
        Lista<Carta *> *cartas = jugador.getListaDeCartas();
        cartas.reiniciarCursor();
        while (cartas.avanzarCursor)
        {
            std::cout << "[" << i << "] " << cartas.getCursor().getNombre();
            << "\n";
            i++;
        }
        std::cout << "Elija una carta []\n" int indice;
        while (respuestaInvalida)
        {
            std::cin >> indice;
            if ((indice > 0) & (indice < cartas.getLargo()))
            {
                respuestaInvalida = false;
            }
        }

        return respuesta;
    }

    ~EntradaSalida();
};

#endif