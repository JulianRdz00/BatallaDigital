#ifndef _LISTA_CIRCULAR_H_
#define _LISTA_CIRCULAR_H_

#ifndef NULL
#define NULL 0
#endif /* NULL */
#include "Nodo.hpp"

template <class T>
class ListaCircular
{
private:
    Nodo<T> *primero;
    unsigned int tamanio;
    Nodo<T> *cursor;

public:
    ListaCircular();
    ListaCircular(ListaCircular<T> &otraLista);
    bool vacia() const;
    unsigned int contarElementos() const;
    void add(T elemento);
    void add(T elemento, unsigned int posicion);
    void add(ListaCircular<T> &otraLista);
    T get(unsigned int posicion);
    void asignar(T elemento, unsigned int posicion);
    void remover(unsigned int posicion);
    void reiniciarCursor();
    bool avanzarCursor();
    T getCursor() const;
    ~ListaCircular();

private:
    Nodo<T> *getNodo(unsigned int posicion) const;
};

#endif