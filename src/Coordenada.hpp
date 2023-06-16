#ifndef _COORDENADA_H_
#define _COORDENADA_H_

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
    Coordenada()
    {
        this->setCoordenada(-1, -1, -1);
    }

    /*
    Pre:-
    Post: Crea una coordenada con los valores x,y,z pasados como arguemento
    */
    Coordenada(int x, int y, int z)
    {
        this->setX(x);
        this->setY(y);
        this->setZ(z);
    }

    /*
    Pre:-
    Post: Crea una coordenada identica a la pasada como argumento.
    */
    Coordenada(Coordenada *original)
    {
        this->setX(original->getX());
        this->setZ(original->getY());
        this->setY(original->getZ());
    }

    ~Coordenada()
    {}

    /*
    Pre:-
    Post: Devuelve true o false en funcion de si la coordenada actual y la pasada como argumento son iguales
    */
    bool esIgualA(Coordenada *otraCoordenada)
    {
        if (this->x == otraCoordenada->x &&
            this->y == otraCoordenada->y &&
            this->z == otraCoordenada->z)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    /*
    Pre:-
    Post: Cambia los valores x,y,z de la coordenada a los valores pasados como argumento
    */
    void setCoordenada(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    /*
    Pre:-
    Post: suma los valores x,y,z de la coordenada con los valores pasados como argumento.
    */
    void incrementar(int x, int y, int z)
    {
        this->x = this->x + x;
        this->y = this->x + y;
        this->z = this->x + z;
    }

    /*
    Pre:-
    Post: Incrementa los valores (x, y, z) de la coordenada con los valores (x, y, z) de la coordenada pasada como argumento
    */
    void incrementar(Coordenada *offset)
    {
        this->setX(this->x + offset->getX());
        this->setY(this->x + offset->getY());
        this->setZ(this->x + offset->getZ());
    }

    /*
    Pre:-
    Post: Incrementa el valor X de la coordenada
    */
    void incrementarX(int x)
    {
        this->setX(this->x + x);
    }

    /*
    Pre:-
    Post: Cambia el valor de la componente (x) de la coordenada por la pasada como argumento
    */
    void setX(int x)
    {
        this->x = x;
    }

    /*
    Pre:-
    Post: Cambia el valor de la componente (y) de la coordenada por la pasada como argumento
    */
    void setY(int y)
    {
        this->y = y;
    }

    /*
    Pre:-
    Post: Cambia el valor de la componente (z) de la coordenada por la pasada como argumento
    */
    void setZ(int z)
    {
        this->z = z;
    }

    /*
    Pre:-
    Post: Devuelve el valor de la componente (x) de la coordenada
    */
    int getX()
    {
        return this->x;
    }

    /*
    Pre:-
    Post: Devuelve el valor de la componente (y) de la coordenada
    */
    int getY()
    {
        return this->y;
    }

    /*
    Pre:-
    Post: Devuelve el valor de la componente (z) de la coordenada
    */
    int getZ()
    {
        return this->z;
    }
};

#endif