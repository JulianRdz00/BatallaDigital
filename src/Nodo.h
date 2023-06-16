#ifndef NODO_H
#define NODO_H

#ifndef NULL
#define NULL 0
#endif /* NULL */

template <class T>
class Nodo
{
private:
    Nodo<T> *anterior;
    T dato;
    Nodo<T> *siguiente;

public:
    Nodo(T valor);
    bool haySiguiente();
    Nodo<T> *getSiguiente();
    void setSiguiente(Nodo<T> *nuevoSig);
    T getValor();
    void setValor(T nuevoValor);
    ~Nodo();
};

#endif