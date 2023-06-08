#ifndef _COORDENADA_H_
#define _COORDENADA_H_

class Coordenada
{
private:
    int x;
    int y;
    int z;

public:
    Coordenada(int x,int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    setCoordenada(int x, int y, int z){
        this->x = x;
        this->y = y;
        this->z = z;
    }

    setX(int x){
        this->x = x;
    }
    setY(int y){
        this->y = y;
    }
    setZ(int z){
        this->z = z;
    }

    getX(){
        return this->x;
    }
    getY(){
        return this->y;
    }
    getZ(){
        return this->z;
    }

};

#endif