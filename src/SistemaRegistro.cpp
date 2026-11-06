/***********************************************************************
 * Module:  SistemaRegistro.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class SistemaRegistro
 ***********************************************************************/

#include "SistemaRegistro.h"
#include "Validacion.h"

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::SistemaRegistro()
// Purpose:    Implementation of SistemaRegistro::SistemaRegistro()
// Return:     
////////////////////////////////////////////////////////////////////////

SistemaRegistro::SistemaRegistro() {
    mensaje = "";
    // las listas se crean vacias con sus propios constructores
}

// ================= Getters =================

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::getProfesores()
// Purpose:    Implementation of SistemaRegistro::getProfesores()
// Return:     ListaDoble&
////////////////////////////////////////////////////////////////////////

ListaDoble& SistemaRegistro::getProfesores() { return profesores; }

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::getRegistros()
// Purpose:    Implementation of SistemaRegistro::getRegistros()
// Return:     ListaSimple&
////////////////////////////////////////////////////////////////////////

ListaSimple& SistemaRegistro::getRegistros() { return registros; }

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::getMensaje()
// Purpose:    Implementation of SistemaRegistro::getMensaje()
// Return:     string
////////////////////////////////////////////////////////////////////////

string SistemaRegistro::getMensaje() const   { return mensaje; }

// ================= Profesores =================

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::registrarProfesor(Profesor p)
// Purpose:    Implementation of SistemaRegistro::registrarProfesor()
// Parameters:
// - p
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool SistemaRegistro::registrarProfesor(Profesor p) {
    // Si algun dato era invalido, el setter lo dejo vacio
    if (p.getCedula() == "" || p.getNombre() == "" || p.getApellido() == "") {
        mensaje = "Datos del profesor invalidos.";
        return false;
    }
    if (profesores.buscar(p.getCedula()) != nullptr) {
        mensaje = "Ya existe un profesor con la cedula " + p.getCedula() + ".";
        return false;
    }
    profesores.insertarFinal(p);
    mensaje = "Profesor registrado correctamente.";
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::agregarClase(string ced, int fr, string mat)
// Purpose:    Implementation of SistemaRegistro::agregarClase()
// Parameters:
// - ced
// - fr
// - mat
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool SistemaRegistro::agregarClase(string ced, int fr, string mat) {
    Profesor* p = profesores.buscar(ced);   // puntero al profesor DENTRO de la lista
    if (p == nullptr) {
        mensaje = "No existe un profesor con esa cedula.";
        return false;
    }
    if (p->tieneFranja(fr)) {
        mensaje = "El profesor ya tiene una clase en la franja " + to_string(fr) + ".";
        return false;
    }
    if (!p->agregarFranja(fr, mat)) {
        mensaje = "No se pudo agregar la clase (franja o materia invalida).";
        return false;
    }
    mensaje = "Clase agregada correctamente.";
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::eliminarProfesor(string cedula)
// Purpose:    Implementation of SistemaRegistro::eliminarProfesor()
// Parameters:
// - cedula
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool SistemaRegistro::eliminarProfesor(string cedula) {
    if (!profesores.eliminar(cedula)) {
        mensaje = "No existe un profesor con esa cedula.";
        return false;
    }
    mensaje = "Profesor eliminado.";
    return true;
}

// ================= Asistencia =================

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::marcarEntrada(string cedula, string fecha, Hora h)
// Purpose:    Implementation of SistemaRegistro::marcarEntrada()
// Parameters:
// - cedula
// - fecha
// - h
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool SistemaRegistro::marcarEntrada(string cedula, string fecha, Hora h) {
    Profesor* p = profesores.buscar(cedula);
    if (p == nullptr) {
        mensaje = "No existe un profesor con esa cedula.";
        return false;
    }
    if (!Validacion::esDiaLaborable(fecha)) {
        mensaje = "No hay clases ese dia (solo de lunes a viernes).";
        return false;
    }

    // Busca cual de sus clases tiene la entrada abierta a esa hora
    int fr = p->franjaParaEntrada(h);
    if (fr == 0) {
        mensaje = "Entrada rechazada: ninguna de sus clases inicia a esa hora "
                  "(solo se puede entrar hasta 10 minutos despues del inicio).";
        return false;
    }

    // No se puede marcar dos veces la entrada de la misma clase el mismo dia
    if (registros.buscar(cedula, fecha, fr) != nullptr) {
        mensaje = "Ya se registro la entrada de la franja " + to_string(fr) + " en esa fecha.";
        return false;
    }

    Registro r(cedula, fecha, fr);
    r.marcarEntrada(h);
    registros.insertar(r);
    mensaje = "Entrada registrada en la franja " + to_string(fr) + " (" + p->getNombre() + " " + p->getApellido() + ").";
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::marcarSalida(string cedula, string fecha, Hora h)
// Purpose:    Implementation of SistemaRegistro::marcarSalida()
// Parameters:
// - cedula
// - fecha
// - h
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool SistemaRegistro::marcarSalida(string cedula, string fecha, Hora h) {
    Profesor* p = profesores.buscar(cedula);
    if (p == nullptr) {
        mensaje = "No existe un profesor con esa cedula.";
        return false;
    }
    if (!Validacion::esDiaLaborable(fecha)) {
        mensaje = "No hay clases ese dia (solo de lunes a viernes).";
        return false;
    }

    // Busca cual de sus clases tiene la salida abierta a esa hora
    int fr = p->franjaParaSalida(h);
    if (fr == 0) {
        mensaje = "Salida rechazada: solo se puede salir desde 10 minutos antes del fin de una de sus clases.";
        return false;
    }

    // Debe existir la entrada de esa clase en esa fecha
    Registro* r = registros.buscar(cedula, fecha, fr);
    if (r == nullptr || !r->getTieneEntrada()) {
        mensaje = "Salida rechazada: no se registro la entrada de la franja " + to_string(fr) + ".";
        return false;
    }
    if (r->getTieneSalida()) {
        mensaje = "Ya se registro la salida de la franja " + to_string(fr) + " en esa fecha.";
        return false;
    }

    r->marcarSalida(h);   // se modifica el registro que esta DENTRO de la lista
    mensaje = "Salida registrada en la franja " + to_string(fr) + ".";
    return true;
}

// ================= Mostrar =================

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::mostrarProfesores()
// Purpose:    Implementation of SistemaRegistro::mostrarProfesores()
// Return:     void
////////////////////////////////////////////////////////////////////////

void SistemaRegistro::mostrarProfesores() const {
    if (profesores.estaVacia()) cout << "No hay profesores registrados." << endl;
    else profesores.mostrarAdelante();
}

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::mostrarProfesoresAlReves()
// Purpose:    Implementation of SistemaRegistro::mostrarProfesoresAlReves()
// Return:     void
////////////////////////////////////////////////////////////////////////

void SistemaRegistro::mostrarProfesoresAlReves() const {
    if (profesores.estaVacia()) cout << "No hay profesores registrados." << endl;
    else profesores.mostrarAtras();
}

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::mostrarRegistros()
// Purpose:    Implementation of SistemaRegistro::mostrarRegistros()
// Return:     void
////////////////////////////////////////////////////////////////////////

void SistemaRegistro::mostrarRegistros() const {
    if (registros.estaVacia()) cout << "No hay registros de asistencia." << endl;
    else registros.mostrar();
}

////////////////////////////////////////////////////////////////////////
// Name:       SistemaRegistro::mostrarRegistrosProfesor(string cedula)
// Purpose:    Implementation of SistemaRegistro::mostrarRegistrosProfesor()
// Parameters:
// - cedula
// Return:     void
////////////////////////////////////////////////////////////////////////

void SistemaRegistro::mostrarRegistrosProfesor(string cedula) const {
    if (profesores.buscar(cedula) == nullptr) cout << "No existe un profesor con esa cedula." << endl;
    else registros.mostrarPorProfesor(cedula);
}
