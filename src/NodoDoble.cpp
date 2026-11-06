/***********************************************************************
 * Module:  NodoDoble.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class NodoDoble
 ***********************************************************************/

#include "NodoDoble.h"

////////////////////////////////////////////////////////////////////////
// Name:       NodoDoble::NodoDoble(Profesor p)
// Purpose:    Implementation of NodoDoble::NodoDoble()
// Parameters:
// - p
// Return:     
////////////////////////////////////////////////////////////////////////

// Guarda una copia del profesor (usa el constructor copia de Profesor)
// y deja el nodo sin vecinos todavia
NodoDoble::NodoDoble(Profesor p) : dato(p) {
    siguiente = nullptr;
    anterior = nullptr;
}

// ================= Getters =================

////////////////////////////////////////////////////////////////////////
// Name:       NodoDoble::getDato()
// Purpose:    Implementation of NodoDoble::getDato()
// Return:     Profesor*
////////////////////////////////////////////////////////////////////////

// Devuelve la DIRECCION del profesor (&dato), no una copia:
// asi quien lo recibe puede modificar al profesor que esta dentro de la lista
Profesor* NodoDoble::getDato()             { return &dato; }

////////////////////////////////////////////////////////////////////////
// Name:       NodoDoble::getSiguiente()
// Purpose:    Implementation of NodoDoble::getSiguiente()
// Return:     NodoDoble*
////////////////////////////////////////////////////////////////////////

NodoDoble* NodoDoble::getSiguiente() const { return siguiente; }

////////////////////////////////////////////////////////////////////////
// Name:       NodoDoble::getAnterior()
// Purpose:    Implementation of NodoDoble::getAnterior()
// Return:     NodoDoble*
////////////////////////////////////////////////////////////////////////

NodoDoble* NodoDoble::getAnterior() const  { return anterior; }

// ================= Setters =================

////////////////////////////////////////////////////////////////////////
// Name:       NodoDoble::setDato(Profesor p)
// Purpose:    Implementation of NodoDoble::setDato()
// Parameters:
// - p
// Return:     void
////////////////////////////////////////////////////////////////////////

void NodoDoble::setDato(Profesor p)        { dato = p; }   // usa operator= de Profesor

////////////////////////////////////////////////////////////////////////
// Name:       NodoDoble::setSiguiente(NodoDoble* n)
// Purpose:    Implementation of NodoDoble::setSiguiente()
// Parameters:
// - n
// Return:     void
////////////////////////////////////////////////////////////////////////

void NodoDoble::setSiguiente(NodoDoble* n) { siguiente = n; }

////////////////////////////////////////////////////////////////////////
// Name:       NodoDoble::setAnterior(NodoDoble* n)
// Purpose:    Implementation of NodoDoble::setAnterior()
// Parameters:
// - n
// Return:     void
////////////////////////////////////////////////////////////////////////

void NodoDoble::setAnterior(NodoDoble* n)  { anterior = n; }
