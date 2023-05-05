#ifndef _ARRAY_
#define _ARRAY_

#include "Constantes.hpp"

template <class T>
class Array
{
public:
    Array();
    Array(const Array<T> &);
    ~Array();
    int getSize();
    Array<T> &operator=(const Array<T> &);
    bool operator==(const Array<T> &);
    T &operator[](int);
    void add(T item);

private:
    int size;
    T *ptr;
};

template <class T>
Array<T>::Array()
{
    ptr = new T[10];
    size = 10;
}

template <class T>
Array<T>::Array(const Array<T> &init)
{
    size = init.size;
    ptr = new T[size];
    for (int i = 0; i < size; i++)
        ptr[i] = init.ptr[i]; // debe existir el = para la clase T !
}

template <class T>
void Array<T>::add(T item)
{
    size = init.size;
    ptr = new T[size];
    for (int i = 0; i < size; i++)
        ptr[i] = init.ptr[i]; // debe existir el = para la clase T !
}

template <class T>
Array<T>::~Array()
{
    if (ptr)
        delete[] ptr;
}

template <class T>
int Array<T>::getSize()
{
    return size;
}

template <class T>
Array<T> &Array<T>::operator=(const Array<T> &rigth)
{
    if (&rigth != this)
    {
        if (size != rigth.size)
        {
            T *aux;
            aux = new T[rigth.size];
            delete[] ptr;
            size = rigth.size;
            ptr = aux;
            for (int i = 0; i < size; i++)
            {
                ptr[i] = rigth.ptr[i];
            }
            return *this;
        }
        else
        {
            for (int i = 0; i < size; i++)
                ptr[i] = rigth.ptr[i];
            return *this;
        }
    }
    return *this;
}

template <class T>
bool Array<T>::operator==(const Array<T> &rigth)
{
    if (size != rigth.size)
        return false;
    else
        for (int i = 0; i < size; i++)
            if (ptr[i] != rigth.ptr[i])
                return false;
            else
                return true;
}

template <class T>
T &Array<T>::operator[](int subscript)
{
    return ptr[subscript];
}
#endif