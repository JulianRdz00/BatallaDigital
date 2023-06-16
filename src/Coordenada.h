#ifndef COORDENADA_H
#define COORDENADA_H


class Coordenada
{
private:
    int x;
    int y;
    int z;

public:

    /*
    Pre:-
    Post: Crea una coordenada con todas las posiciones en -1
    */
    Coordenada();

    /*
    Pre:-
    Post: Crea una coordenada con los valores x,y,z pasados como arguemento
    */
    Coordenada(int x, int y, int z);

    /*
    Pre:-
    Post: Crea una coordenada identica a la pasada como argumento.
    */
    Coordenada(Coordenada *original);

    ~Coordenada();

    /*
    Pre:-
    Post: Devuelve true o false en funcion de si la coordenada actual y la pasada como argumento son iguales
    */
    bool esIgualA(Coordenada *otraCoordenada);

    /*
    Pre:-
    Post: Cambia los valores x,y,z de la coordenada a los valores pasados como argumento
    */
    void setCoordenada(int x, int y, int z);

    /*
    Pre:-
    Post: suma los valores x,y,z de la coordenada con los valores pasados como argumento.
    */
    void incrementar(int x, int y, int z);

    /*
    Pre:-
    Post: Incrementa los valores (x, y, z) de la coordenada con los valores (x, y, z) de la coordenada pasada como argumento
    */
    void incrementar(Coordenada *offset);

    /*
    Pre:-
    Post: Incrementa el valor X de la coordenada
    */
    void incrementarX(int x);

    /*
    Pre:-
    Post: Cambia el valor de la componente (x) de la coordenada por la pasada como argumento
    */
    void setX(int x);

    /*
    Pre:-
    Post: Cambia el valor de la componente (y) de la coordenada por la pasada como argumento
    */
    void setY(int y);

    /*
    Pre:-
    Post: Cambia el valor de la componente (z) de la coordenada por la pasada como argumento
    */
    void setZ(int z);

    /*
    Pre:-
    Post: Devuelve el valor de la componente (x) de la coordenada
    */
    int getX();

    /*
    Pre:-
    Post: Devuelve el valor de la componente (y) de la coordenada
    */
    int getY();

    /*
    Pre:-
    Post: Devuelve el valor de la componente (z) de la coordenada
    */
    int getZ();
};

#endif