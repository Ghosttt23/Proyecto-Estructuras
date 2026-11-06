/***********************************************************************
 * Module:  NodoSimple.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class NodoSimple
 ***********************************************************************/

#if !defined(__SistemaRegistro_NodoSimple_h)
#define __SistemaRegistro_NodoSimple_h

#include "Registro.h"

// Nodo de la lista simple: guarda un Registro y un puntero al nodo siguiente
class NodoSimple {
private:
    Registro dato;
    NodoSimple* siguiente;   // nullptr si es el ultimo

public:
    NodoSimple(Registro r);

    // ---- Getters ----
    Registro* getDato();     // puntero al registro guardado (para poder modificarlo)
    NodoSimple* getSiguiente() const;

    // ---- Setters ----
    void setDato(Registro r);
    void setSiguiente(NodoSimple* n);
};

#endif
