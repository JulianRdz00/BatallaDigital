#include "Lista.h"

template <class T>
Lista<T>::Lista()
{
    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
}

template <class T>
Lista<T>::Lista(Lista<T> &otraLista)
{
    this->primero = NULL;
    this->tamanio = 0;
    this->cursor = NULL;
    this->add(otraLista);
}

template <class T>
bool Lista<T>::vacia() const
{
    return (this->tamanio == 0);
}

template <class T>
unsigned int Lista<T>::contarElementos() const
{
    return (this->tamanio);
}

template <class T>
void Lista<T>::add(T elemento)
{
    this->add(elemento, this->tamanio + 1);
}

template <class T>
void Lista<T>::add(T elemento, unsigned int posicion)
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

template <class T>
void Lista<T>::add(Lista<T> &otraLista)
{
    otraLista.reiniciarCursor();
    while (otraLista.avanzarCursor())
    {
        this->add(otraLista.getCursor());
    }
}

template <class T>
T Lista<T>::get(unsigned int posicion)
{
    if ((posicion <= 0) || (posicion > this->tamanio))
    {
        throw "POSICION INVALIDA";
    }
    return (this->getNodo(posicion)->getValor());
}

template <class T>
void Lista<T>::asignar(T elemento, unsigned int posicion)
{
    if ((posicion > 0) && (posicion <= this->tamanio))
    {
        this->getNodo(posicion)->setValor(elemento);
    }
}

template <class T>
void Lista<T>::remover(unsigned int posicion)
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

template <class T>
void Lista<T>::reiniciarCursor()
{
    this->cursor = NULL;
}

template <class T>
bool Lista<T>::avanzarCursor()
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

template <class T>
T Lista<T>::getCursor() const
{
    if (this->cursor == NULL)
    {
        throw "CURSOR ESTA NULL";
    }
    return (this->cursor->getValor());
}

template <class T>
Lista<T>::~Lista()
{
    while (this->primero != NULL)
    {
        Nodo<T> *nodoRemovido = this->primero;
        this->primero = this->primero->getSiguiente();
        delete nodoRemovido;
    }
}

Nodo<T> *Lista<T>::getNodo(unsigned int posicion) const
{
    Nodo<T> *nodoActual = this->primero;
    for (unsigned int i = 1; i < posicion; i++)
    {
        nodoActual = nodoActual->getSiguiente();
    }
    return nodoActual;
}

#endif
