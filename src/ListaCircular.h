#ifndef _LISTA_CIRCULAR_H_
#define _LISTA_CIRCULAR_H_

#ifndef NULL
#define NULL 0
#endif /* NULL */
#include "Nodo.h"

template <class T>
class ListaC
{
public:
    ListaC( ); 
    ~ListaC( ); 
    void Add(const T &);
    void Remover( ); 
    void Remover(unsigned int posicion); 
    bool Vacia( ) const;
    Nodo<T> *GetNodo(unsigned int posicion) const;
    
private:
    Nodo <T> * principio;
    unsigned int tamanio;

};


#endif