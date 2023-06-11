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

public:

    EntradaSalida();

    /*POS: devuelve el valor de la coordenada ingresada por consola*/

    int pedirCordenada(string nombreCoordenada){

        int coordenada;

        cout << endl << "Ingrese la coordenada " << nombreCoordenada << ": ";
        cin >> coordenada;
        cout << endl;

        return coordenada;
    }

    /*POS: devuelve un string con el nombre de la carta a jugar y en caso de no jugar carta devuelve 0
    
    REVISAR lista de cartas mano (const)
    */

    string pedirCarta(Jugador *jugador){
      
        char respuesta;
        cout << endl << "Queres usar una carta?" << endl;
        cout << "[S]Si [N]No" << endl;
        cin >> respuesta;

        if (respuesta == 'S')
        {
            const Lista<Carta> *mano = jugador->getListaDeCartas();

            mano->reiniciarCursor();
            while(mano->avanzarCursor()){
                string nombreCarta = mano->getCursor().getNombre();

                cout << endl << "Desea jugar la carta: " << nombreCarta << endl;
                cout << "[S]Si [N]No" << endl;
                cin >> respuesta;

                if(respuesta == "S"){
                    return nombreCarta;
                }

            }
            
        }

        cout << endl << "Se decidio no utilizar ninguna carta" << endl;
        return 0;
    }

    ~EntradaSalida();

};

#endif