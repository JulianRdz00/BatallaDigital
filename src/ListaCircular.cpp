#include "ListaCircular.h"


template <class T>
ListaC <T>::ListaC(){
    this->principio=NULL;
    this->tamanio=0;
}

template <class T>
ListaC<T>::~ListaC(){

    if(principio){
        if (this->principio->getSiguiente == this->principio){

            delete this->principio;}
            
        else{
            Nodo <T> *aux1, *aux2;
            aux1 = principio->getSiguiente;
            principio->setSiguiente(NULL);
            while(aux1!=NULL){
                aux2=aux1;
                aux1=aux1->getSiguiente;
                delete aux2;
               }
           }
       }
}

/*Agrega al principio*/

template <class T>
void ListaC <T> :: Add (const T & v){

    Nodo<T> *nuevo = new Nodo <T>(v), *aux;
    if(Vacia()){
        principio = nuevo;
        nuevo->setSiguiente(nuevo);
    }

    else{
        nuevo->setSiguiente(principio);
        aux = principio;
        while (aux->getSiguiente != principio){
            aux=aux->getSiguiente;
            }
        aux->setSiguiente(nuevo);
        principio = nuevo;
    }
    this->tamanio++;
}

/*Borra al principio*/

template <class T>
void ListaC <T> :: Remover(){

    Nodo<T> *aux1, *aux2;
    if (!Vacia()){

        if (principio->getSiguiente==principio){
            
            delete _principio;
            principio=0;
        }
        else{

            aux1=principio;
            aux2=aux1->getSiguiente;
            while (aux2->getSiguiente!=principio){
                aux2=aux2->getSiguiente;
                }
            aux2->setSiguiente=aux1->getSiguiente;
            principio = principio->getSiguiente;
            delete aux1;
        }
        this->tamanio--;
    }
}


template <class T>
void ListaC <T> :: Remover(unsigned int posicion){
    
    Nodo<T> *aux1, *aux2;
    aux1=principio;

    if (!Vacia() && posicion<=tamanio){
        for (int i=1; i<posicion; i++){
            aux1=principio->getSiguiente;
        }

        delete aux1;
        this->tamanio--;    
    }
    
}

template <class T>
    bool ListaC <T> :: Vacia () const{
        return (tamanio==0);
}

template <class T>
Nodo<T> *ListaC<T>::GetNodo(unsigned int posicion) const
{
    Nodo<T> *nodoActual = this->primero;
    
    for (unsigned int i = 1; i < posicion; i++)
    {
        nodoActual = nodoActual->getSiguiente();
    }
    return nodoActual;
}