/***********************************************************************
 * Module:  Franja.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class Franja
 ***********************************************************************/

#include "Franja.h"
#include "Validacion.h"

// ================= Constructores =================

////////////////////////////////////////////////////////////////////////
// Name:       Franja::Franja()
// Purpose:    Implementation of Franja::Franja()
// Return:     
////////////////////////////////////////////////////////////////////////

Franja::Franja() {
    numero = 0;            // 0 significa "sin franja asignada"
    materia = "";
    inicio = Hora(0, 0);
    fin = Hora(0, 0);
}

////////////////////////////////////////////////////////////////////////
// Name:       Franja::Franja(int numero)
// Purpose:    Implementation of Franja::Franja()
// Parameters:
// - numero
// Return:     
////////////////////////////////////////////////////////////////////////

Franja::Franja(int numero) {
    materia = "";
    setNumero(numero);     // reutilizamos el setter, que valida y calcula las horas
}

////////////////////////////////////////////////////////////////////////
// Name:       Franja::Franja(int numero, string materia)
// Purpose:    Implementation of Franja::Franja()
// Parameters:
// - numero
// - materia
// Return:     
////////////////////////////////////////////////////////////////////////

Franja::Franja(int numero, string materia) {
    setMateria(materia);
    setNumero(numero);
}

// ================= Getters =================

////////////////////////////////////////////////////////////////////////
// Name:       Franja::getNumero()
// Purpose:    Implementation of Franja::getNumero()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Franja::getNumero() const     { return numero; }

////////////////////////////////////////////////////////////////////////
// Name:       Franja::getMateria()
// Purpose:    Implementation of Franja::getMateria()
// Return:     string
////////////////////////////////////////////////////////////////////////

string Franja::getMateria() const { return materia; }

////////////////////////////////////////////////////////////////////////
// Name:       Franja::getInicio()
// Purpose:    Implementation of Franja::getInicio()
// Return:     Hora
////////////////////////////////////////////////////////////////////////

Hora Franja::getInicio() const    { return inicio; }

////////////////////////////////////////////////////////////////////////
// Name:       Franja::getFin()
// Purpose:    Implementation of Franja::getFin()
// Return:     Hora
////////////////////////////////////////////////////////////////////////

Hora Franja::getFin() const       { return fin; }

// ================= Setters =================

////////////////////////////////////////////////////////////////////////
// Name:       Franja::setNumero(int n)
// Purpose:    Implementation of Franja::setNumero()
// Parameters:
// - n
// Return:     void
////////////////////////////////////////////////////////////////////////

// Recibe el numero de franja y calcula sus horas:
// franja 1 empieza a las 7, y cada franja siguiente empieza 2 horas despues.
void Franja::setNumero(int n) {
    if (n >= 1 && n <= 7) {
        numero = n;
        int horaInicio = 7 + (n - 1) * 2;   // 1->7, 2->9, 3->11 ... 7->19
        inicio = Hora(horaInicio, 0);
        fin = inicio + 120;                 // operator+ de Hora: 2 horas = 120 min
    } else {
        numero = 0;                         // numero invalido -> sin franja
        inicio = Hora(0, 0);
        fin = Hora(0, 0);
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       Franja::setMateria(string m)
// Purpose:    Implementation of Franja::setMateria()
// Parameters:
// - m
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Si la materia no es valida no se cambia y devuelve false
bool Franja::setMateria(string m) {
    if (!Validacion::esMateria(m)) return false;
    materia = m;
    return true;
}

// ================= Reglas de los 10 minutos =================

////////////////////////////////////////////////////////////////////////
// Name:       Franja::puedeEntrar(Hora h)
// Purpose:    Implementation of Franja::puedeEntrar()
// Parameters:
// - h
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Entrada valida: desde la hora de inicio hasta 10 minutos despues
bool Franja::puedeEntrar(Hora h) const {
    if (numero == 0) return false;               // sin franja no hay entrada
    return h >= inicio && h <= inicio + 10;
}

////////////////////////////////////////////////////////////////////////
// Name:       Franja::puedeSalir(Hora h)
// Purpose:    Implementation of Franja::puedeSalir()
// Parameters:
// - h
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Salida valida: desde 10 minutos antes del fin hasta la hora de fin
bool Franja::puedeSalir(Hora h) const {
    if (numero == 0) return false;
    return h >= fin - 10 && h <= fin;
}

// ================= Operadores =================

////////////////////////////////////////////////////////////////////////
// Name:       Franja::operator==(const Franja& otra)
// Purpose:    Implementation of Franja::operator==()
// Parameters:
// - otra
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Dos franjas son iguales si tienen el mismo numero (el mismo horario)
bool Franja::operator==(const Franja& otra) const {
    return numero == otra.numero;
}

////////////////////////////////////////////////////////////////////////
// Name:       operator<<(ostream& os, const Franja& f)
// Purpose:    Implementation of operator<<()
// Parameters:
// - os
// - f
// Return:     ostream&
////////////////////////////////////////////////////////////////////////

// Imprime: Franja 1 (07:00 - 09:00) Estructura de Datos
ostream& operator<<(ostream& os, const Franja& f) {
    if (f.numero == 0) {
        os << "Sin franja";
    } else {
        os << "Franja " << f.numero << " (" << f.inicio << " - " << f.fin << ")";
        if (f.materia != "") os << " " << f.materia;
    }
    return os;
}
