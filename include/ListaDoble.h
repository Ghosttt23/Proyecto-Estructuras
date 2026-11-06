/***********************************************************************
 * Module:  ListaDoble.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class ListaDoble
 ***********************************************************************/

#if !defined(__SistemaRegistro_ListaDoble_h)
#define __SistemaRegistro_ListaDoble_h

#include "NodoDoble.h"

// Lista doblemente enlazada de profesores.
// Cada nodo apunta al siguiente y al anterior, por eso se puede recorrer
// en los dos sentidos (mostrarAdelante y mostrarAtras).
// Los nodos se crean con new y se liberan con delete (memoria dinamica).
class ListaDoble {
private:
    NodoDoble* cabeza;   // primer nodo (nullptr si la lista esta vacia)
    NodoDoble* cola;     // ultimo nodo (nullptr si la lista esta vacia)
    int tamanio;         // cantidad de nodos

public:
    ListaDoble();
    ~ListaDoble();   // libera todos los nodos

    // Copia bloqueada: una copia compartiria los mismos nodos
    // y al destruirse las dos se haria delete dos veces de la misma memoria
    ListaDoble(const ListaDoble&) = delete;
    ListaDoble& operator=(const ListaDoble&) = delete;

    // ---- Getters ----
    NodoDoble* getCabeza() const;
    NodoDoble* getCola() const;
    int getTamanio() const;

    // ---- Operaciones ----
    void insertarFinal(Profesor p);
    Profesor* buscar(string cedula) const;   // nullptr si no existe
    bool eliminar(string cedula);            // false si no existe
    void mostrarAdelante() const;            // de la cabeza a la cola
    void mostrarAtras() const;               // de la cola a la cabeza
    bool estaVacia() const;
};

#endif
