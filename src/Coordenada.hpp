#ifndef _COORDENADA_H_
#define _COORDENADA_H_

class Coordenada
{
private:
    int x;
    int y;
    int z;

public:
    Coordenada()
    {
        this->setCoordenada(-1, -1, -1);
    }

    // POST: Crea una coordenada con los valores x,y,z pasados como arguemento.
    Coordenada(int x, int y, int z)
    {
        this->setX(x);
        this->setY(y);
        this->setZ(z);
    }

    // POST:Crea una coordenada identica a la pasada como argumento.
    Coordenada(Coordenada &original)
    {
        this->setX(original.getX());
        this->setY(original.getX());
        this->setZ(original.getX());
    }

    // Devuelve True si la otraCoordenada es igual.
    bool esIgualA(Coordenada &otraCoordenada)
    {
        if (this->x == otraCoordenada.x &&
            this->y == otraCoordenada.y &&
            this->z == otraCoordenada.z)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    // POST: cambia los valores x,y,z de la coordenada a los valores pasados como argumento.
    void setCoordenada(int x, int y, int z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    // POST: suma los valores x,y,z de la coordenada con los valores pasados como argumento.
    void incrementar(int x, int y, int z)
    {
        this->x = this->x + x;
        this->y = this->x + y;
        this->z = this->x + z;
    }

    // POST: Incrementa los valores x,y,z de la coordenada con los valores x,y,z de la coordenada pasada como offset.
    void incrementar(Coordenada &offset)
    {
        this->setX(this->x + offset.getX());
        this->setY(this->x + offset.getY());
        this->setZ(this->x + offset.getZ());
    }

    // Post: Incrementa el valor X de la coordenada.
    void incrementarX(int x)
    {
        this->setX(this->x + x);
    }

    // POST: Da el valor de X a la componente X de la coordenada.
    void setX(int x)
    {
        this->x = x;
    }

    // POST: Da el valor de Y a la componente Y de la coordenada.
    void setY(int y)
    {
        this->y = y;
    }

    // POST: Da el valor de Y a la componente Y de la coordenada.
    void setZ(int z)
    {
        this->z = z;
    }

    // POST: Devuelve el valor de la componente X de la coordenada.
    int getX()
    {
        return this->x;
    }

    // POST: Devuelve el valor de la componente Y de la coordenada.
    int getY()
    {
        return this->y;
    }

    // POST: Devuelve el valor de la componente Z de la coordenada.
    int getZ()
    {
        return this->z;
    }
};

#endif