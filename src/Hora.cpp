/***********************************************************************
 * Module:  Hora.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class Hora
 ***********************************************************************/

#include "Hora.h"
#include <iomanip>   // setw y setfill para imprimir 07:05 en vez de 7:5

// ================= Constructores =================

////////////////////////////////////////////////////////////////////////
// Name:       Hora::Hora()
// Purpose:    Implementation of Hora::Hora()
// Return:     
////////////////////////////////////////////////////////////////////////

Hora::Hora() {
    horas = 0;
    minutos = 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       Hora::Hora(int h, int m)
// Purpose:    Implementation of Hora::Hora()
// Parameters:
// - h
// - m
// Return:     
////////////////////////////////////////////////////////////////////////

Hora::Hora(int h, int m) {
    setHoras(h);       // usamos los setters para que validen
    setMinutos(m);
}

////////////////////////////////////////////////////////////////////////
// Name:       Hora::Hora(string texto)
// Purpose:    Implementation of Hora::Hora()
// Parameters:
// - texto
// Return:     
////////////////////////////////////////////////////////////////////////

// Recibe un texto tipo "07:05" y lo separa en horas y minutos.
// Primero lo valida: si tiene letras o esta fuera de rango, la hora queda en 00:00
// en lugar de que el programa se caiga.
Hora::Hora(string texto) {
    horas = 0;
    minutos = 0;
    if (esValida(texto)) {
        // '0' vale 48 en ASCII, asi que restarlo convierte el caracter en numero
        horas   = (texto.at(0) - '0') * 10 + (texto.at(1) - '0');
        minutos = (texto.at(3) - '0') * 10 + (texto.at(4) - '0');
    }
}

// ================= Validacion =================

////////////////////////////////////////////////////////////////////////
// Name:       Hora::esValida(string texto)
// Purpose:    Implementation of Hora::esValida()
// Parameters:
// - texto
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Hora::esValida(string texto) {
    if (texto.length() != 5) return false;   // debe ser exactamente HH:MM
    if (texto.at(2) != ':') return false;

    // Las posiciones 0, 1, 3 y 4 deben ser digitos (la 2 son los dos puntos)
    for (int p = 0; p < 5; p++) {
        if (p == 2) continue;
        if (texto.at(p) < '0' || texto.at(p) > '9') return false;
    }

    int h = (texto.at(0) - '0') * 10 + (texto.at(1) - '0');
    int m = (texto.at(3) - '0') * 10 + (texto.at(4) - '0');
    return h <= 23 && m <= 59;
}

// ================= Getters y setters =================

////////////////////////////////////////////////////////////////////////
// Name:       Hora::getHoras()
// Purpose:    Implementation of Hora::getHoras()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Hora::getHoras() const   { return horas; }

////////////////////////////////////////////////////////////////////////
// Name:       Hora::getMinutos()
// Purpose:    Implementation of Hora::getMinutos()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Hora::getMinutos() const { return minutos; }

////////////////////////////////////////////////////////////////////////
// Name:       Hora::setHoras(int h)
// Purpose:    Implementation of Hora::setHoras()
// Parameters:
// - h
// Return:     void
////////////////////////////////////////////////////////////////////////

void Hora::setHoras(int h) {
    if (h >= 0 && h <= 23) horas = h;
    else horas = 0;           // valor invalido -> se pone en 0
}

////////////////////////////////////////////////////////////////////////
// Name:       Hora::setMinutos(int m)
// Purpose:    Implementation of Hora::setMinutos()
// Parameters:
// - m
// Return:     void
////////////////////////////////////////////////////////////////////////

void Hora::setMinutos(int m) {
    if (m >= 0 && m <= 59) minutos = m;
    else minutos = 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       Hora::enMinutos()
// Purpose:    Implementation of Hora::enMinutos()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Hora::enMinutos() const {
    return horas * 60 + minutos;
}

// ================= Operadores =================

////////////////////////////////////////////////////////////////////////
// Name:       Hora::operator+(int mins)
// Purpose:    Implementation of Hora::operator+()
// Parameters:
// - mins
// Return:     Hora
////////////////////////////////////////////////////////////////////////

// Suma minutos: 08:55 + 10 = 09:05
Hora Hora::operator+(int mins) const {
    int total = (enMinutos() + mins) % (24 * 60);   // % para no pasar de 23:59
    return Hora(total / 60, total % 60);
}

////////////////////////////////////////////////////////////////////////
// Name:       Hora::operator-(int mins)
// Purpose:    Implementation of Hora::operator-()
// Parameters:
// - mins
// Return:     Hora
////////////////////////////////////////////////////////////////////////

// Resta minutos: 09:00 - 10 = 08:50
Hora Hora::operator-(int mins) const {
    int total = enMinutos() - mins;
    if (total < 0) total += 24 * 60;                // por si pasa de medianoche
    return Hora(total / 60, total % 60);
}

////////////////////////////////////////////////////////////////////////
// Name:       Hora::operator<(const Hora& otra)
// Purpose:    Implementation of Hora::operator<()
// Parameters:
// - otra
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Hora::operator<(const Hora& otra) const  { return enMinutos() <  otra.enMinutos(); }

////////////////////////////////////////////////////////////////////////
// Name:       Hora::operator>(const Hora& otra)
// Purpose:    Implementation of Hora::operator>()
// Parameters:
// - otra
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Hora::operator>(const Hora& otra) const  { return enMinutos() >  otra.enMinutos(); }

////////////////////////////////////////////////////////////////////////
// Name:       Hora::operator<=(const Hora& otra)
// Purpose:    Implementation of Hora::operator<=()
// Parameters:
// - otra
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Hora::operator<=(const Hora& otra) const { return enMinutos() <= otra.enMinutos(); }

////////////////////////////////////////////////////////////////////////
// Name:       Hora::operator>=(const Hora& otra)
// Purpose:    Implementation of Hora::operator>=()
// Parameters:
// - otra
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Hora::operator>=(const Hora& otra) const { return enMinutos() >= otra.enMinutos(); }

////////////////////////////////////////////////////////////////////////
// Name:       Hora::operator==(const Hora& otra)
// Purpose:    Implementation of Hora::operator==()
// Parameters:
// - otra
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Hora::operator==(const Hora& otra) const { return enMinutos() == otra.enMinutos(); }

////////////////////////////////////////////////////////////////////////
// Name:       operator<<(ostream& os, const Hora& h)
// Purpose:    Implementation of operator<<()
// Parameters:
// - os
// - h
// Return:     ostream&
////////////////////////////////////////////////////////////////////////

// Imprime con dos digitos: 07:05
ostream& operator<<(ostream& os, const Hora& h) {
    os << setw(2) << setfill('0') << h.horas << ":"
       << setw(2) << setfill('0') << h.minutos;
    return os;
}
