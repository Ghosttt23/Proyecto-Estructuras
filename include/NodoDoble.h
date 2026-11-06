/***********************************************************************
 * Module:  NodoDoble.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class NodoDoble
 ***********************************************************************/

#if !defined(__SistemaRegistro_NodoDoble_h)
#define __SistemaRegistro_NodoDoble_h

#include "Profesor.h"

// Nodo de la lista doble: guarda un Profesor y dos punteros,
// uno al nodo siguiente y otro al nodo anterior.
class NodoDoble {
private:
    Profesor dato;
    NodoDoble* siguiente;   // nullptr si es el ultimo
    NodoDoble* anterior;    // nullptr si es el primero

public:
    NodoDoble(Profesor p);   // crea el nodo suelto (sin vecinos)

    // ---- Getters ----
    Profesor* getDato();            // puntero al profesor guardado (para poder modificarlo)
    NodoDoble* getSiguiente() const;
    NodoDoble* getAnterior() const;

    // ---- Setters ----
    void setDato(Profesor p);
    void setSiguiente(NodoDoble* n);
    void setAnterior(NodoDoble* n);
};

#endif
