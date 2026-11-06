/***********************************************************************
 * Module:  Profesor.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class Profesor
 ***********************************************************************/

#include "Profesor.h"

// ================= Constructores =================

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::Profesor()
// Purpose:    Implementation of Profesor::Profesor()
// Return:     
////////////////////////////////////////////////////////////////////////

Profesor::Profesor() {
    cedula = "";
    nombre = "";
    apellido = "";
    numFranjas = 0;
    capacidad = CAPACIDAD_INICIAL;
    franjas = new Franja[capacidad];   // reserva memoria dinamica para 2 clases
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::Profesor(string ced, string nom, string ape)
// Purpose:    Implementation of Profesor::Profesor()
// Parameters:
// - ced
// - nom
// - ape
// Return:     
////////////////////////////////////////////////////////////////////////

Profesor::Profesor(string ced, string nom, string ape) {
    cedula = "";
    nombre = "";
    apellido = "";
    setCedula(ced);      // los setters validan; si el dato esta mal, queda vacio
    setNombre(nom);
    setApellido(ape);
    numFranjas = 0;
    capacidad = CAPACIDAD_INICIAL;
    franjas = new Franja[capacidad];
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::Profesor(string ced, string nom, string ape, int numFranja, string materia)
// Purpose:    Implementation of Profesor::Profesor()
// Parameters:
// - ced
// - nom
// - ape
// - numFranja
// - materia
// Return:     
////////////////////////////////////////////////////////////////////////

Profesor::Profesor(string ced, string nom, string ape, int numFranja, string materia) {
    cedula = "";
    nombre = "";
    apellido = "";
    setCedula(ced);
    setNombre(nom);
    setApellido(ape);
    numFranjas = 0;
    capacidad = CAPACIDAD_INICIAL;
    franjas = new Franja[capacidad];
    agregarFranja(numFranja, materia);   // si el numero no es valido, no se agrega
}

// ================= Memoria dinamica =================

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::Profesor(const Profesor& otro)
// Purpose:    Implementation of Profesor::Profesor()
// Parameters:
// - otro
// Return:     
////////////////////////////////////////////////////////////////////////

// Constructor copia: se usa cuando se crea un Profesor a partir de otro
// (por ejemplo, al guardarlo dentro de un nodo de la lista).
// Si solo se copiara el puntero, los dos profesores compartirian el MISMO arreglo,
// y al destruirse ambos se haria delete dos veces de la misma memoria (error).
// Por eso se reserva un arreglo nuevo y se copian las clases una por una.
Profesor::Profesor(const Profesor& otro) {
    cedula = otro.cedula;
    nombre = otro.nombre;
    apellido = otro.apellido;
    numFranjas = otro.numFranjas;
    capacidad = otro.capacidad;
    franjas = new Franja[capacidad];
    for (int i = 0; i < numFranjas; i++)
        *(franjas + i) = *(otro.franjas + i);
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::operator=(const Profesor& otro)
// Purpose:    Implementation of Profesor::operator=()
// Parameters:
// - otro
// Return:     Profesor&
////////////////////////////////////////////////////////////////////////

// Asignacion: p1 = p2. Igual que el constructor copia, pero p1 ya tenia
// su propio arreglo, asi que primero hay que liberarlo.
Profesor& Profesor::operator=(const Profesor& otro) {
    if (this == &otro) return *this;   // p1 = p1 -> no hacer nada

    delete[] franjas;                  // libera el arreglo viejo

    cedula = otro.cedula;
    nombre = otro.nombre;
    apellido = otro.apellido;
    numFranjas = otro.numFranjas;
    capacidad = otro.capacidad;
    franjas = new Franja[capacidad];
    for (int i = 0; i < numFranjas; i++)
        *(franjas + i) = *(otro.franjas + i);

    return *this;
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::~Profesor()
// Purpose:    Implementation of Profesor::~Profesor()
// Return:     
////////////////////////////////////////////////////////////////////////

// Destructor: libera la memoria del arreglo cuando el profesor deja de existir
Profesor::~Profesor() {
    delete[] franjas;
    franjas = nullptr;
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::crecer()
// Purpose:    Implementation of Profesor::crecer()
// Return:     void
////////////////////////////////////////////////////////////////////////

// Duplica la capacidad (sin pasar de 7): crea un arreglo nuevo,
// copia las clases y libera el anterior
void Profesor::crecer() {
    int nuevaCapacidad = capacidad * 2;
    if (nuevaCapacidad > MAX_FRANJAS) nuevaCapacidad = MAX_FRANJAS;

    Franja* nuevo = new Franja[nuevaCapacidad];
    for (int i = 0; i < numFranjas; i++)
        *(nuevo + i) = *(franjas + i);

    delete[] franjas;     // se libera el arreglo viejo
    franjas = nuevo;      // el puntero ahora apunta al arreglo nuevo
    capacidad = nuevaCapacidad;
}

// ================= Getters =================

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::getCedula()
// Purpose:    Implementation of Profesor::getCedula()
// Return:     string
////////////////////////////////////////////////////////////////////////

string Profesor::getCedula() const   { return cedula; }

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::getNombre()
// Purpose:    Implementation of Profesor::getNombre()
// Return:     string
////////////////////////////////////////////////////////////////////////

string Profesor::getNombre() const   { return nombre; }

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::getApellido()
// Purpose:    Implementation of Profesor::getApellido()
// Return:     string
////////////////////////////////////////////////////////////////////////

string Profesor::getApellido() const { return apellido; }

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::getNumFranjas()
// Purpose:    Implementation of Profesor::getNumFranjas()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Profesor::getNumFranjas() const  { return numFranjas; }

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::getCapacidad()
// Purpose:    Implementation of Profesor::getCapacidad()
// Return:     int
////////////////////////////////////////////////////////////////////////

int Profesor::getCapacidad() const   { return capacidad; }

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::getFranja(int indice)
// Purpose:    Implementation of Profesor::getFranja()
// Parameters:
// - indice
// Return:     Franja
////////////////////////////////////////////////////////////////////////

Franja Profesor::getFranja(int indice) const {
    if (indice >= 0 && indice < numFranjas)
        return *(franjas + indice);
    return Franja();   // indice fuera de rango -> franja vacia
}

// ================= Setters =================

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::setCedula(string ced)
// Purpose:    Implementation of Profesor::setCedula()
// Parameters:
// - ced
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Profesor::setCedula(string ced) {
    if (!Validacion::esCedula(ced)) return false;
    cedula = ced;
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::setNombre(string nom)
// Purpose:    Implementation of Profesor::setNombre()
// Parameters:
// - nom
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Profesor::setNombre(string nom) {
    if (!Validacion::esNombre(nom)) return false;
    nombre = nom;
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::setApellido(string ape)
// Purpose:    Implementation of Profesor::setApellido()
// Parameters:
// - ape
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Profesor::setApellido(string ape) {
    if (!Validacion::esNombre(ape)) return false;
    apellido = ape;
    return true;
}

// ================= Manejo de franjas =================

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::tieneFranja(int numFranja)
// Purpose:    Implementation of Profesor::tieneFranja()
// Parameters:
// - numFranja
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Profesor::tieneFranja(int numFranja) const {
    for (int i = 0; i < numFranjas; i++) {
        if ((franjas + i)->getNumero() == numFranja)
            return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::agregarFranja(Franja f)
// Purpose:    Implementation of Profesor::agregarFranja()
// Parameters:
// - f
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Profesor::agregarFranja(Franja f) {
    if (f.getNumero() == 0) return false;            // franja invalida
    if (!Validacion::esMateria(f.getMateria())) return false;   // materia vacia o invalida
    if (numFranjas >= MAX_FRANJAS) return false;     // ya tiene las 7
    if (tieneFranja(f.getNumero())) return false;    // ya tiene clase a esa hora

    if (numFranjas == capacidad) crecer();           // arreglo lleno -> se agranda

    // Se inserta ordenada por numero para que se muestren en orden de horario
    int pos = numFranjas;
    while (pos > 0 && (franjas + pos - 1)->getNumero() > f.getNumero()) {
        *(franjas + pos) = *(franjas + pos - 1);   // corre una posicion a la derecha
        pos--;
    }
    *(franjas + pos) = f;
    numFranjas++;
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::agregarFranja(int numFranja, string materia)
// Purpose:    Implementation of Profesor::agregarFranja()
// Parameters:
// - numFranja
// - materia
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Version sobrecargada: crea la franja y reutiliza la otra version
bool Profesor::agregarFranja(int numFranja, string materia) {
    return agregarFranja(Franja(numFranja, materia));
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::quitarFranja(int numFranja)
// Purpose:    Implementation of Profesor::quitarFranja()
// Parameters:
// - numFranja
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Profesor::quitarFranja(int numFranja) {
    for (int i = 0; i < numFranjas; i++) {
        if ((franjas + i)->getNumero() == numFranja) {
            // Se recorren las siguientes una posicion a la izquierda
            for (int j = i; j < numFranjas - 1; j++)
                *(franjas + j) = *(franjas + j + 1);
            numFranjas--;
            return true;
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::franjaParaEntrada(Hora h)
// Purpose:    Implementation of Profesor::franjaParaEntrada()
// Parameters:
// - h
// Return:     int
////////////////////////////////////////////////////////////////////////

// Recorre las clases del profesor y devuelve la que tenga la entrada abierta a esa hora
int Profesor::franjaParaEntrada(Hora h) const {
    for (int i = 0; i < numFranjas; i++) {
        if ((franjas + i)->puedeEntrar(h))
            return (franjas + i)->getNumero();
    }
    return 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::franjaParaSalida(Hora h)
// Purpose:    Implementation of Profesor::franjaParaSalida()
// Parameters:
// - h
// Return:     int
////////////////////////////////////////////////////////////////////////

int Profesor::franjaParaSalida(Hora h) const {
    for (int i = 0; i < numFranjas; i++) {
        if ((franjas + i)->puedeSalir(h))
            return (franjas + i)->getNumero();
    }
    return 0;
}

// ================= Operadores =================

////////////////////////////////////////////////////////////////////////
// Name:       Profesor::operator==(const Profesor& otro)
// Purpose:    Implementation of Profesor::operator==()
// Parameters:
// - otro
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Dos profesores son el mismo si tienen la misma cedula
bool Profesor::operator==(const Profesor& otro) const {
    return cedula == otro.cedula;
}

////////////////////////////////////////////////////////////////////////
// Name:       operator<<(ostream& os, const Profesor& p)
// Purpose:    Implementation of operator<<()
// Parameters:
// - os
// - p
// Return:     ostream&
////////////////////////////////////////////////////////////////////////

// Imprime los datos y debajo cada una de sus clases
ostream& operator<<(ostream& os, const Profesor& p) {
    os << p.cedula << " | " << p.nombre << " " << p.apellido;
    if (p.numFranjas == 0) {
        os << endl << "   Sin clases asignadas";
    } else {
        for (int i = 0; i < p.numFranjas; i++)
            os << endl << "   " << *(p.franjas + i);
    }
    return os;
}
