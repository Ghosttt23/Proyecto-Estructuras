/***********************************************************************
 * Module:  Registro.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class Registro
 ***********************************************************************/

#include "Registro.h"

// ================= Constructores =================

////////////////////////////////////////////////////////////////////////
// Name:       Registro::Registro()
// Purpose:    Implementation of Registro::Registro()
// Return:     
////////////////////////////////////////////////////////////////////////

Registro::Registro() {
    cedula = "";
    fecha = "";
    numFranja = 0;
    tieneEntrada = false;
    tieneSalida = false;
    // horaEntrada y horaSalida empiezan en 00:00 con Hora()
}

////////////////////////////////////////////////////////////////////////
// Name:       Registro::Registro(string cedula, string fecha, int numFranja)
// Purpose:    Implementation of Registro::Registro()
// Parameters:
// - cedula
// - fecha
// - numFranja
// Return:     
////////////////////////////////////////////////////////////////////////

Registro::Registro(string cedula, string fecha, int numFranja) {
    this->cedula = cedula;       // this-> distingue el atributo del parametro
    this->fecha = fecha;
    this->numFranja = numFranja;
    tieneEntrada = false;
    tieneSalida = false;
}

// ================= Getters =================

////////////////////////////////////////////////////////////////////////
// Name:       Registro::getCedula()
// Purpose:    Implementation of Registro::getCedula()
// Return:     string
////////////////////////////////////////////////////////////////////////

string Registro::getCedula() const     { return cedula; }

////////////////////////////////////////////////////////////////////////
// Name:       Registro::getFecha()
// Purpose:    Implementation of Registro::getFecha()
// Return:     string
////////////////////////////////////////////////////////////////////////

string Registro::getFecha() const      { return fecha; }

////////////////////////////////////////////////////////////////////////
// Name:       Registro::getNumFranja()
// Purpose:    Implementation of Registro::getNumFranja()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Registro::getNumFranja() const     { return numFranja; }

////////////////////////////////////////////////////////////////////////
// Name:       Registro::getHoraEntrada()
// Purpose:    Implementation of Registro::getHoraEntrada()
// Return:     Hora
////////////////////////////////////////////////////////////////////////

Hora Registro::getHoraEntrada() const  { return horaEntrada; }

////////////////////////////////////////////////////////////////////////
// Name:       Registro::getHoraSalida()
// Purpose:    Implementation of Registro::getHoraSalida()
// Return:     Hora
////////////////////////////////////////////////////////////////////////

Hora Registro::getHoraSalida() const   { return horaSalida; }

////////////////////////////////////////////////////////////////////////
// Name:       Registro::getTieneEntrada()
// Purpose:    Implementation of Registro::getTieneEntrada()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Registro::getTieneEntrada() const { return tieneEntrada; }

////////////////////////////////////////////////////////////////////////
// Name:       Registro::getTieneSalida()
// Purpose:    Implementation of Registro::getTieneSalida()
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Registro::getTieneSalida() const  { return tieneSalida; }

// ================= Setters =================

////////////////////////////////////////////////////////////////////////
// Name:       Registro::setCedula(string ced)
// Purpose:    Implementation of Registro::setCedula()
// Parameters:
// - ced
// Return:     void
////////////////////////////////////////////////////////////////////////

void Registro::setCedula(string ced) { cedula = ced; }

////////////////////////////////////////////////////////////////////////
// Name:       Registro::setFecha(string fec)
// Purpose:    Implementation of Registro::setFecha()
// Parameters:
// - fec
// Return:     void
////////////////////////////////////////////////////////////////////////

void Registro::setFecha(string fec)  { fecha = fec; }

////////////////////////////////////////////////////////////////////////
// Name:       Registro::setNumFranja(int fr)
// Purpose:    Implementation of Registro::setNumFranja()
// Parameters:
// - fr
// Return:     void
////////////////////////////////////////////////////////////////////////

void Registro::setNumFranja(int fr)  { numFranja = fr; }

////////////////////////////////////////////////////////////////////////
// Name:       Registro::marcarEntrada(Hora h)
// Purpose:    Implementation of Registro::marcarEntrada()
// Parameters:
// - h
// Return:     void
////////////////////////////////////////////////////////////////////////

void Registro::marcarEntrada(Hora h) {
    horaEntrada = h;
    tieneEntrada = true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Registro::marcarSalida(Hora h)
// Purpose:    Implementation of Registro::marcarSalida()
// Parameters:
// - h
// Return:     void
////////////////////////////////////////////////////////////////////////

void Registro::marcarSalida(Hora h) {
    horaSalida = h;
    tieneSalida = true;
}

// ================= Operador << =================

////////////////////////////////////////////////////////////////////////
// Name:       operator<<(ostream& os, const Registro& r)
// Purpose:    Implementation of operator<<()
// Parameters:
// - os
// - r
// Return:     ostream&
////////////////////////////////////////////////////////////////////////

ostream& operator<<(ostream& os, const Registro& r) {
    os << r.fecha << " | " << r.cedula << " | Franja " << r.numFranja << " | Entrada ";
    if (r.tieneEntrada) os << r.horaEntrada; else os << "--:--";
    os << " | Salida ";
    if (r.tieneSalida) os << r.horaSalida; else os << "--:--";
    os << (r.tieneSalida ? " | Completa" : " | Pendiente salida");
    return os;
}
