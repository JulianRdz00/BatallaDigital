#ifndef _LISTAC_
#define _LISTAC_

#include "Nodo.hpp"

template <class T>
class ListaC
{
    /* JULIAN + libreria */
public:
    ListaC(); // constructor
    // Escribir el constructor copia como ej
    ~ListaC();                // destructor
    void AltaPrin(const T &); // alta al principio
    // void AltaFin (const T &); //alta al final Escribirla
    void BajaPrin(); // borra primer nodo
    // void BajaFin( ); //borra ultimo nodo Escribirlo
    bool Vacia() const;  // retorna true si lista vacia
    void Emitir() const; // emite la lista
private:
    Nodo<T> *_principio;
};

template <class T>
ListaC<T>::ListaC() : _principio(0) {}

template <class T>
ListaC<T>::~ListaC()
{
    if (_principio)
    {
        if (_principio->getSiguiente() == _principio)
            delete _principio;
        else
        {
            Nodo<T> *_aux1, *_aux2;
            _aux1 = _principio->getSiguiente();
            _principio->setSiguiente(0);
            while (_aux1 != 0)
            {
                _aux2 = _aux1;
                _aux1 = _aux1->getSiguiente();
                delete _aux2;
            }
        }
    }
}
template <class T>
void ListaC<T>::AltaPrin(const T &_v)
{
    Nodo<T> *_nuevo = new Nodo<T>(_v), *_aux;
    if (Vacia())
    {
        _principio = _nuevo;
        _nuevo->setSiguiente(_nuevo);
    }
    else
    {
        _nuevo->setSiguiente(_principio);
        _aux = _principio;
        while (_aux->_sig != _principio)
            _aux = _aux->getSiguiente();
        _aux->setSiguiente(_nuevo);
        _principio = _nuevo;
    }
}

template <class T>
void ListaC<T>::BajaPrin()
{
    Nodo<T> *_aux1, *_aux2;
    if (!Vacia())
    {
        if (_principio->getSiguiente() == _principio)
        {
            delete _principio;
            _principio = 0;
        }
        else
        {
            _aux1 = _principio;
            _aux2 = _aux1->getSiguiente();
            while (_aux2->getSiguiente() != _principio)
                _aux2 = _aux2->getSiguiente();
            _aux2->_sig = _aux1->getSiguiente();
            _principio = _principio->getSiguiente();
            delete _aux1;
        }
    }
}

template <class T>
void ListaC<T>::Emitir() const
{
    Nodo<T> *_aux = _principio;
    if (!Vacia())
    {
        do
        {
            std::cout << _aux->getValor();
            _aux = _aux->getSiguiente();
        } while (_aux != _principio);
    }
}
template <class T>
bool ListaC<T>::Vacia() const
{
    return (_principio == 0);
}

#endif