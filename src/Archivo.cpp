/***********************************************************************
 * Module:  Archivo.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 9:45:00
 * Purpose: Implementation of the class Archivo
 ***********************************************************************/

#include "Archivo.h"
#include "Validacion.h"
#include <fstream>   // ofstream / ifstream: escribir y leer archivos
#include <sstream>   // stringstream: separar una linea por ';'

////////////////////////////////////////////////////////////////////////
// Name:       Archivo::quitarRetorno(string& linea)
// Purpose:    Implementation of Archivo::quitarRetorno()
// Parameters:
// - linea
// Return:     void
////////////////////////////////////////////////////////////////////////

// Si el archivo se edito en Windows, cada linea termina en "\r"; se quita para que no
// quede pegado al ultimo dato (por ejemplo "08:55\r" no seria una hora valida)
void Archivo::quitarRetorno(string& linea) {
    if (!linea.empty() && linea.back() == '\r')
        linea.pop_back();
}

// ================= Profesores =================

////////////////////////////////////////////////////////////////////////
// Name:       Archivo::guardarProfesores(ListaDoble& lista, string ruta)
// Purpose:    Implementation of Archivo::guardarProfesores()
// Parameters:
// - lista
// - ruta
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Archivo::guardarProfesores(ListaDoble& lista, string ruta) {
    ofstream archivo(ruta);              // crea el archivo (o lo sobrescribe)
    if (!archivo.is_open()) return false;

    // Recorre la lista doble desde la cabeza con punteros
    NodoDoble* nodo = lista.getCabeza();
    while (nodo != nullptr) {
        Profesor* p = nodo->getDato();
        archivo << p->getCedula() << ";" << p->getNombre() << ";"
                << p->getApellido() << ";" << p->getNumFranjas() << endl;

        // Debajo del profesor, una linea por cada una de sus clases
        for (int i = 0; i < p->getNumFranjas(); i++) {
            Franja f = p->getFranja(i);
            archivo << f.getNumero() << ";" << f.getMateria() << endl;
        }
        nodo = nodo->getSiguiente();
    }
    archivo.close();
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Archivo::cargarProfesores(ListaDoble& lista, string ruta)
// Purpose:    Implementation of Archivo::cargarProfesores()
// Parameters:
// - lista
// - ruta
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Archivo::cargarProfesores(ListaDoble& lista, string ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return false;   // la primera vez el archivo aun no existe

    string linea;
    while (getline(archivo, linea)) {
        quitarRetorno(linea);
        if (linea == "") continue;

        // Separa la linea por ';' -> cedula;nombre;apellido;numClases
        stringstream ss(linea);
        string ced, nom, ape, num;
        getline(ss, ced, ';');
        getline(ss, nom, ';');
        getline(ss, ape, ';');
        getline(ss, num, ';');
        if (!Validacion::esEnteroEnRango(num, 0, 7)) continue;   // linea danada

        // Los setters del constructor validan cedula, nombre y apellido
        Profesor p(ced, nom, ape);

        // Lee las lineas de sus clases -> numFranja;materia
        int numClases = stoi(num);
        for (int i = 0; i < numClases && getline(archivo, linea); i++) {
            quitarRetorno(linea);
            stringstream ssClase(linea);
            string fr, mat;
            getline(ssClase, fr, ';');
            getline(ssClase, mat);
            if (Validacion::esEnteroEnRango(fr, 1, 7))
                p.agregarFranja(stoi(fr), mat);   // valida materia y franja repetida
        }

        // Solo se agrega si sus datos son validos y la cedula no esta repetida
        bool datosValidos = p.getCedula() != "" && p.getNombre() != "" && p.getApellido() != "";
        if (datosValidos && lista.buscar(p.getCedula()) == nullptr)
            lista.insertarFinal(p);
    }
    archivo.close();
    return true;
}

// ================= Registros =================

////////////////////////////////////////////////////////////////////////
// Name:       Archivo::guardarRegistros(ListaSimple& lista, string ruta)
// Purpose:    Implementation of Archivo::guardarRegistros()
// Parameters:
// - lista
// - ruta
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Archivo::guardarRegistros(ListaSimple& lista, string ruta) {
    ofstream archivo(ruta);
    if (!archivo.is_open()) return false;

    // Recorre la lista simple desde la cabeza con punteros
    NodoSimple* nodo = lista.getCabeza();
    while (nodo != nullptr) {
        Registro* r = nodo->getDato();
        archivo << r->getFecha() << ";" << r->getCedula() << ";" << r->getNumFranja() << ";"
                << r->getHoraEntrada() << ";";
        if (r->getTieneSalida()) archivo << r->getHoraSalida();
        else archivo << "--:--";            // todavia no marca la salida
        archivo << endl;
        nodo = nodo->getSiguiente();
    }
    archivo.close();
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Archivo::cargarRegistros(ListaSimple& lista, string ruta)
// Purpose:    Implementation of Archivo::cargarRegistros()
// Parameters:
// - lista
// - ruta
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Archivo::cargarRegistros(ListaSimple& lista, string ruta) {
    ifstream archivo(ruta);
    if (!archivo.is_open()) return false;

    string linea;
    while (getline(archivo, linea)) {
        quitarRetorno(linea);
        if (linea == "") continue;

        // fecha;cedula;numFranja;horaEntrada;horaSalida
        stringstream ss(linea);
        string fecha, ced, fr, entrada, salida;
        getline(ss, fecha, ';');
        getline(ss, ced, ';');
        getline(ss, fr, ';');
        getline(ss, entrada, ';');
        getline(ss, salida, ';');

        // Si algun dato esta mal, la linea se ignora
        if (!Validacion::esFecha(fecha) || !Validacion::esCedula(ced) ||
            !Validacion::esEnteroEnRango(fr, 1, 7) || !Hora::esValida(entrada))
            continue;

        Registro r(ced, fecha, stoi(fr));
        r.marcarEntrada(Hora(entrada));
        if (Hora::esValida(salida))        // "--:--" no es valida: aun no sale
            r.marcarSalida(Hora(salida));
        lista.insertar(r);
    }
    archivo.close();
    return true;
}
