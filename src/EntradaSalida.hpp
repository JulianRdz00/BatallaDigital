/* MATEO Intento 1*/

#ifndef _ENTRADASALIDA_
#define _ENTRADASALIDA_

#include <iostream>
#include "Lista.hpp"
#include "Carta.hpp"
#include "Jugador.hpp"

using namespace std;

class EntradaSalida
{
private:
   
    /*POS: devuelve el valor de la coordenada ingresada por consola */

    int pedirCordenada(string nombreCoordenada){

        int coordenada;

        cout << "Ingrese la coordenada " << nombreCoordenada << ": " << endl;
        cin >> coordenada;
        cout << endl;

        return coordenada;
    }

public:

    EntradaSalida();

    /*POS: pregunta que soldado se desea mover y devuelve la coordenada cuyo nombre es nombreCoordenada */

    int coordenadaSoldadoExistente(string nombreCoordenada){

        cout << "Que soldado desea mover? " << endl;
        
        return pedirCordenada(nombreCoordenada);
    }

    /*POS: pregunta a donde quiere mover su soldado y devuelve la coordenada cuyo nombre es nombreCoordenada */

    int coordenadaNuevoLugar(string nombreCoordenada){
        
        cout << "Donde quiere mover su soldado? " << endl;

        return pedirCordenada(nombreCoordenada);
    }

    /*POS: pregunta a donde quiere colocar una mina y devuelve la coordenada cuyo nombre es nombreCoordenada*/

    int coordenadaColocarMina(string nombreCoordenada){

        cout << "Donde quiere colocar una mina? " << endl;

        return pedirCordenada(nombreCoordenada);
    }

    /*POS: devuelve un string con el nombre de la carta a jugar y en caso de no jugar carta devuelve 0
    REVISAR lista de cartas mano (const)
    */

    string pedirCarta(Jugador *jugador){
      
        char respuesta;
        cout << "Queres usar una carta?" << endl;
        cout << "[S]Si [N]No" << endl;
        cin >> respuesta;
        cout << endl;

        if (respuesta == 'S')
        {
            const Lista<Carta> *mano = jugador->getListaDeCartas();

            mano->reiniciarCursor();
            while(mano->avanzarCursor()){
                string nombreCarta = mano->getCursor().getNombre();

                cout << "Desea jugar la carta: " << nombreCarta << endl;
                cout << "[S]Si [N]No" << endl;
                cin >> respuesta;
                cout << endl;

                if(respuesta == "S"){
                    return nombreCarta;
                }

            }
            
        }

        cout << "Se decidio no utilizar ninguna carta" << endl;
        return 0;
    }

    TipoDeCarta elejirCarta(Jugador &jugador){

        char respuesta;
        bool respuestaInvalida = true;

        while(respuestaInvalida){

        std::cout << "Queres usar una carta?\n";
        std::cout << "[S]Si [N]No\n";
        std::cin >> respuesta;

        if (respuesta == 'S')
        {
            std::cout << "Tus cartas disponibles:\n";
            int i = 1;
            Lista<Carta*>* cartas = jugador.getListaDeCartas();
            cartas.reiniciarCursor();
            while(cartas.avanzarCursor){
                cartas.getCursor().




                i++;
            }

            respuestaInvalida = false;
        }else if(respuesta == 'N'){
            std::cout << "Ingrese una respuesta valida.\n";
        }

        }
    }

    ~EntradaSalida();

};

#endif