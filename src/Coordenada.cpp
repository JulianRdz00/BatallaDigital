#include "Coordenada.h"


Coordenada::Coordenada()
{
    this->setCoordenada(-1, -1, -1);
}

Coordenada::Coordenada(int x, int y, int z)
{
    this->setX(x);
    this->setY(y);
    this->setZ(z);
}

Coordenada::Coordenada(Coordenada *original)
{
    this->setX(original->getX());
    this->setZ(original->getY());
    this->setY(original->getZ());
}

Coordenada::~Coordenada()
{

}

bool Coordenada::esIgualA(Coordenada *otraCoordenada)
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

void Coordenada::setCoordenada(int x, int y, int z)
{
    this->x = x;
    this->y = y;
    this->z = z;
}

void Coordenada::incrementar(int x, int y, int z)
{
    this->x = this->x + x;
    this->y = this->x + y;
    this->z = this->x + z;
}

void Coordenada::incrementar(Coordenada *offset)
{
    this->setX(this->x + offset->getX());
    this->setY(this->x + offset->getY());
    this->setZ(this->x + offset->getZ());
}

void Coordenada::incrementarX(int x)
{
    this->setX(this->x + x);
}

void Coordenada::setX(int x)
{
    this->x = x;
}

void Coordenada::setY(int y)
{
    this->y = y;
}

void Coordenada::setZ(int z)
{
    this->z = z;
}

int Coordenada::getX()
{
    return this->x;
}

int Coordenada::getY()
{
    return this->y;
}

int Coordenada::getZ()
{
    return this->z;
}
