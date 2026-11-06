/***********************************************************************
 * Module:  NodoSimple.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class NodoSimple
 ***********************************************************************/

#include "NodoSimple.h"

////////////////////////////////////////////////////////////////////////
// Name:       NodoSimple::NodoSimple(Registro r)
// Purpose:    Implementation of NodoSimple::NodoSimple()
// Parameters:
// - r
// Return:     
////////////////////////////////////////////////////////////////////////

NodoSimple::NodoSimple(Registro r) : dato(r) {
    siguiente = nullptr;
}

// ================= Getters =================

////////////////////////////////////////////////////////////////////////
// Name:       NodoSimple::getDato()
// Purpose:    Implementation of NodoSimple::getDato()
// Return:     Registro*
////////////////////////////////////////////////////////////////////////

// Devuelve la direccion del registro para poder marcar la salida sobre el mismo objeto
Registro* NodoSimple::getDato()             { return &dato; }

////////////////////////////////////////////////////////////////////////
// Name:       NodoSimple::getSiguiente()
// Purpose:    Implementation of NodoSimple::getSiguiente()
// Return:     NodoSimple*
////////////////////////////////////////////////////////////////////////

NodoSimple* NodoSimple::getSiguiente() const { return siguiente; }

// ================= Setters =================

////////////////////////////////////////////////////////////////////////
// Name:       NodoSimple::setDato(Registro r)
// Purpose:    Implementation of NodoSimple::setDato()
// Parameters:
// - r
// Return:     void
////////////////////////////////////////////////////////////////////////

void NodoSimple::setDato(Registro r)         { dato = r; }

////////////////////////////////////////////////////////////////////////
// Name:       NodoSimple::setSiguiente(NodoSimple* n)
// Purpose:    Implementation of NodoSimple::setSiguiente()
// Parameters:
// - n
// Return:     void
////////////////////////////////////////////////////////////////////////

void NodoSimple::setSiguiente(NodoSimple* n) { siguiente = n; }
