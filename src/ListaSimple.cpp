/***********************************************************************
 * Module:  ListaSimple.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class ListaSimple
 ***********************************************************************/

#include "ListaSimple.h"

// ================= Constructor y destructor =================

////////////////////////////////////////////////////////////////////////
// Name:       ListaSimple::ListaSimple()
// Purpose:    Implementation of ListaSimple::ListaSimple()
// Return:     
////////////////////////////////////////////////////////////////////////

ListaSimple::ListaSimple() {
    cabeza = nullptr;
    tamanio = 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaSimple::~ListaSimple()
// Purpose:    Implementation of ListaSimple::~ListaSimple()
// Return:     
////////////////////////////////////////////////////////////////////////

ListaSimple::~ListaSimple() {
    NodoSimple* actual = cabeza;
    while (actual != nullptr) {
        NodoSimple* siguiente = actual->getSiguiente();   // se guarda antes de borrar
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    tamanio = 0;
}

// ================= Getters =================

////////////////////////////////////////////////////////////////////////
// Name:       ListaSimple::getCabeza()
// Purpose:    Implementation of ListaSimple::getCabeza()
// Return:     NodoSimple*
////////////////////////////////////////////////////////////////////////

NodoSimple* ListaSimple::getCabeza() const { return cabeza; }

////////////////////////////////////////////////////////////////////////
// Name:       ListaSimple::getTamanio()
// Purpose:    Implementation of ListaSimple::getTamanio()
// Return:     int
////////////////////////////////////////////////////////////////////////

int ListaSimple::getTamanio() const        { return tamanio; }

// ================= Operaciones =================

////////////////////////////////////////////////////////////////////////
// Name:       ListaSimple::estaVacia()
// Purpose:    Implementation of ListaSimple::estaVacia()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool ListaSimple::estaVacia() const {
    return cabeza == nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaSimple::insertar(Registro r)
// Purpose:    Implementation of ListaSimple::insertar()
// Parameters:
// - r
// Return:     void
////////////////////////////////////////////////////////////////////////

// Agrega al final: como la lista simple no guarda la cola,
// hay que recorrerla hasta el ultimo nodo
void ListaSimple::insertar(Registro r) {
    NodoSimple* nuevo = new NodoSimple(r);

    if (estaVacia()) {
        cabeza = nuevo;
    } else {
        NodoSimple* actual = cabeza;
        while (actual->getSiguiente() != nullptr)   // avanza hasta el ultimo
            actual = actual->getSiguiente();
        actual->setSiguiente(nuevo);
    }
    tamanio++;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaSimple::buscar(string cedula, string fecha, int numFranja)
// Purpose:    Implementation of ListaSimple::buscar()
// Parameters:
// - cedula
// - fecha
// - numFranja
// Return:     Registro*
////////////////////////////////////////////////////////////////////////

// Busca el registro de un profesor en una fecha y franja
Registro* ListaSimple::buscar(string cedula, string fecha, int numFranja) const {
    NodoSimple* actual = cabeza;
    while (actual != nullptr) {
        Registro* r = actual->getDato();
        if (r->getCedula() == cedula && r->getFecha() == fecha && r->getNumFranja() == numFranja)
            return r;
        actual = actual->getSiguiente();
    }
    return nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaSimple::mostrar()
// Purpose:    Implementation of ListaSimple::mostrar()
// Return:     void
////////////////////////////////////////////////////////////////////////

void ListaSimple::mostrar() const {
    NodoSimple* actual = cabeza;
    while (actual != nullptr) {
        cout << *(actual->getDato()) << endl;   // usa operator<< de Registro
        actual = actual->getSiguiente();
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       ListaSimple::mostrarPorProfesor(string cedula)
// Purpose:    Implementation of ListaSimple::mostrarPorProfesor()
// Parameters:
// - cedula
// Return:     void
////////////////////////////////////////////////////////////////////////

void ListaSimple::mostrarPorProfesor(string cedula) const {
    NodoSimple* actual = cabeza;
    bool encontrado = false;
    while (actual != nullptr) {
        if (actual->getDato()->getCedula() == cedula) {
            cout << *(actual->getDato()) << endl;
            encontrado = true;
        }
        actual = actual->getSiguiente();
    }
    if (!encontrado)
        cout << "Este profesor no tiene registros." << endl;
}
