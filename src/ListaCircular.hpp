#ifndef _LISTACIRCULAR_
#define _LISTACIRCULAR_

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
    void add(Lista<T> &otraLista);
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

/*	IMPLEMENTATION	*/

/* PUBLIC: */

/* POST: Lista vacia */
template <class T>
ListaCircular<T>::ListaCircular()
{
    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
}

/* POST: Lista igual a una lista referencia */
template <class T>
ListaCircular<T>::ListaCircular(ListaCircular<T> &otraLista)
{
    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
    this->add(otraLista);
}

/* POST: Tells whether the list has any element. */
template <class T>
bool ListaCircular<T>::vacia() const
{
    return (this->tamanio == 0);
}

/* POST: Returns the amount of elements in the list. */
template <class T>
unsigned int ListaCircular<T>::contarElementos() const
{
    return (this->tamanio);
}

/* POST: Adds element at the end of the list (position countElements() + 1). */
template <class T>
void ListaCircular<T>::add(T elemento)
{
    this->add(elemento, this->tamanio + 1);
}

/* PRE: Position is between [1 , countElements() + 1].
 * POST: Adds the element in passed position. */
template <class T>
void ListaCircular<T>::add(T elemento, unsigned int posicion)
{
    if ((posicion > 0) && (posicion <= this->tamanio + 1))
    { /* posición válida */
        Nodo<T> *nuevoNodo = new Nodo<T>(elemento);
        if (posicion == 1)
        {
            nuevoNodo->setSiguiente(this->primero);
            this->primero = nuevoNodo;
        }
        else
        {
            Nodo<T> *nodoAnterior = this->getNodo(posicion - 1);
            nuevoNodo->setSiguiente(nodoAnterior->getSiguiente());
            nodoAnterior->setSiguiente(nuevoNodo);
        }
        this->tamanio++;
        this->reiniciarCursor();
    }
}

/* PRE: Position is between [1 , countElements()].
 * POST: Returns the element in that position. */
template <class T>
T ListaCircular<T>::get(unsigned int posicion)
{
    if ((posicion <= 0) || (posicion > this->tamanio))
    {
        throw "POSICION INVALIDA";
    }
    return (this->getNodo(posicion)->getValor());
}

/* PRE: Position is between [1 , countElements()].
 * POST: Changes element in that position to passed element. */
template <class T>
void ListaCircular<T>::asignar(T elemento, unsigned int posicion)
{
    if ((posicion > 0) && (posicion <= this->tamanio))
    {
        this->getNodo(posicion)->setValor(elemento);
    }
}

/* PRE: Position is between [1 , countElements()].
 * POST: Removes element in that position from the list. */
template <class T>
void ListaCircular<T>::remover(unsigned int posicion)
{
    if ((posicion > 0) && (posicion <= this->tamanio))
    {
        Nodo<T> *nodoRemovido;
        if (posicion == 1)
        {
            nodoRemovido = this->primero;
            this->primero = this->primero->getSiguiente();
        }
        else
        {
            Nodo<T> *nodoAnterior = this->getNodo(posicion - 1);
            nodoRemovido = nodoAnterior->getSiguiente();
            nodoAnterior->setSiguiente(nodoRemovido->getSiguiente());
        }
        delete nodoRemovido;
        this->tamanio--;
        this->reiniciarCursor();
    }
}

/* POST: Leaves cursor ready for new iteration. */
template <class T>
void ListaCircular<T>::reiniciarCursor()
{
    this->cursor = NULL;
}

/* Allows to move the cursor from a node to the next one.
 * PRE: Iteration has been initiated (by method resetCursor()),
 *  and no elements have been added or removed since then.
 * POST: Moves cursor to the next element in the iteration.
 *  Return value tells whether cursor now stands on and element or not,
 *  (in case the list is empty or there aren't any more elements). */
template <class T>
bool ListaCircular<T>::avanzarCursor()
{
    if (this->cursor == NULL)
    {
        this->cursor = this->primero;
    }
    else
    {
        this->cursor = this->cursor->getSiguiente();
    }
    return (this->cursor != NULL);
}

/* PRE: Cursor is standing on an element of the list,
 *  (method advanceCursor() was called and returned "true").
 * POST: Returns element in the cursor's position. */
template <class T>
T ListaCircular<T>::getCursor() const
{
    if (this->cursor == NULL)
    {
        throw "CURSOR ESTA NULL";
    }
    return (this->cursor->getValor());
}

/* POST: Liberates resources associated to the list. */
template <class T>
ListaCircular<T>::~ListaCircular()
{
    while (this->primero != NULL)
    {
        Nodo<T> *nodoRemovido = this->primero;
        this->primero = this->primero->getSiguiente();
        delete nodoRemovido;
    }
}

/* PRIVATE: */

/* PRE: Position is between [1 , countElements()].
 * POST: Returns the node in that position (pointer). */
template <class T>
Nodo<T> *ListaCircular<T>::getNodo(unsigned int posicion) const
{
    Nodo<T> *nodoActual = this->primero;
    for (unsigned int i = 1; i < posicion; i++)
    {
        nodoActual = nodoActual->getSiguiente();
    }
    return nodoActual;
}

#endif