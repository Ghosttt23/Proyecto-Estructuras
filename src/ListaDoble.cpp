/***********************************************************************
 * Module:  ListaDoble.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class ListaDoble
 ***********************************************************************/

#include "ListaDoble.h"

// ================= Constructor y destructor =================

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::ListaDoble()
// Purpose:    Implementation of ListaDoble::ListaDoble()
// Return:     
////////////////////////////////////////////////////////////////////////

ListaDoble::ListaDoble() {
    cabeza = nullptr;
    cola = nullptr;
    tamanio = 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::~ListaDoble()
// Purpose:    Implementation of ListaDoble::~ListaDoble()
// Return:     
////////////////////////////////////////////////////////////////////////

// Recorre la lista liberando cada nodo
ListaDoble::~ListaDoble() {
    NodoDoble* actual = cabeza;
    while (actual != nullptr) {
        // Se guarda el siguiente ANTES de borrar: despues del delete ya no se puede leer
        NodoDoble* siguiente = actual->getSiguiente();
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cola = nullptr;
    tamanio = 0;
}

// ================= Getters =================

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::getCabeza()
// Purpose:    Implementation of ListaDoble::getCabeza()
// Return:     NodoDoble*
////////////////////////////////////////////////////////////////////////

NodoDoble* ListaDoble::getCabeza() const { return cabeza; }

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::getCola()
// Purpose:    Implementation of ListaDoble::getCola()
// Return:     NodoDoble*
////////////////////////////////////////////////////////////////////////

NodoDoble* ListaDoble::getCola() const   { return cola; }

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::getTamanio()
// Purpose:    Implementation of ListaDoble::getTamanio()
// Return:     int
////////////////////////////////////////////////////////////////////////

int ListaDoble::getTamanio() const       { return tamanio; }

// ================= Operaciones =================

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::estaVacia()
// Purpose:    Implementation of ListaDoble::estaVacia()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool ListaDoble::estaVacia() const {
    return cabeza == nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::insertarFinal(Profesor p)
// Purpose:    Implementation of ListaDoble::insertarFinal()
// Parameters:
// - p
// Return:     void
////////////////////////////////////////////////////////////////////////

// Agrega un nodo nuevo al final de la lista
void ListaDoble::insertarFinal(Profesor p) {
    NodoDoble* nuevo = new NodoDoble(p);   // memoria dinamica

    if (estaVacia()) {
        // Lista vacia: el nuevo nodo es el primero y el ultimo a la vez
        cabeza = nuevo;
        cola = nuevo;
    } else {
        // Se engancha despues de la cola actual
        cola->setSiguiente(nuevo);   // cola -> nuevo
        nuevo->setAnterior(cola);    // cola <- nuevo
        cola = nuevo;                // el nuevo pasa a ser el ultimo
    }
    tamanio++;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::buscar(string cedula)
// Purpose:    Implementation of ListaDoble::buscar()
// Parameters:
// - cedula
// Return:     Profesor*
////////////////////////////////////////////////////////////////////////

// Recorre desde la cabeza comparando la cedula de cada profesor
Profesor* ListaDoble::buscar(string cedula) const {
    NodoDoble* actual = cabeza;
    while (actual != nullptr) {
        if (actual->getDato()->getCedula() == cedula)
            return actual->getDato();
        actual = actual->getSiguiente();
    }
    return nullptr;   // no se encontro
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::eliminar(string cedula)
// Purpose:    Implementation of ListaDoble::eliminar()
// Parameters:
// - cedula
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Busca el nodo y lo desenlaza segun donde este
bool ListaDoble::eliminar(string cedula) {
    NodoDoble* actual = cabeza;
    while (actual != nullptr && actual->getDato()->getCedula() != cedula)
        actual = actual->getSiguiente();

    if (actual == nullptr) return false;   // no existe

    NodoDoble* previo = actual->getAnterior();
    NodoDoble* posterior = actual->getSiguiente();

    // Si tiene nodo anterior, este ahora apunta al posterior; si no, era la cabeza
    if (previo != nullptr)
        previo->setSiguiente(posterior);
    else
        cabeza = posterior;

    // Si tiene nodo posterior, este ahora apunta al previo; si no, era la cola
    if (posterior != nullptr)
        posterior->setAnterior(previo);
    else
        cola = previo;

    delete actual;   // libera el nodo (y con el, el arreglo de clases del profesor)
    tamanio--;
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::mostrarAdelante()
// Purpose:    Implementation of ListaDoble::mostrarAdelante()
// Return:     void
////////////////////////////////////////////////////////////////////////

void ListaDoble::mostrarAdelante() const {
    NodoDoble* actual = cabeza;
    int i = 1;
    while (actual != nullptr) {
        cout << i << ". " << *(actual->getDato()) << endl;   // usa operator<< de Profesor
        actual = actual->getSiguiente();
        i++;
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaDoble::mostrarAtras()
// Purpose:    Implementation of ListaDoble::mostrarAtras()
// Return:     void
////////////////////////////////////////////////////////////////////////

// Igual que mostrarAdelante, pero empieza en la cola y avanza con getAnterior()
void ListaDoble::mostrarAtras() const {
    NodoDoble* actual = cola;
    int i = tamanio;
    while (actual != nullptr) {
        cout << i << ". " << *(actual->getDato()) << endl;
        actual = actual->getAnterior();
        i--;
    }
}
