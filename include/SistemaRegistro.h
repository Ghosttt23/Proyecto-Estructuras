/***********************************************************************
 * Module:  SistemaRegistro.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class SistemaRegistro
 ***********************************************************************/

#if !defined(__SistemaRegistro_SistemaRegistro_h)
#define __SistemaRegistro_SistemaRegistro_h

#include "ListaDoble.h"
#include "ListaSimple.h"

// Controla el sistema: guarda los profesores (lista doble) y el historial
// de registros (lista simple), y aplica las reglas de negocio:
//  - no se repiten cedulas
//  - la entrada solo se marca dentro de la ventana de 10 minutos de una clase del profesor
//  - la salida solo se marca si hubo entrada, y dentro de su ventana de 10 minutos
//  - no se marca dos veces la entrada ni la salida de la misma clase el mismo dia
// Cada operacion devuelve true/false y deja una explicacion en "mensaje".
class SistemaRegistro {
private:
    ListaDoble profesores;
    ListaSimple registros;
    string mensaje;   // resultado de la ultima operacion (para mostrarlo en el menu)

public:
    SistemaRegistro();

    // ---- Getters ----
    ListaDoble& getProfesores();
    ListaSimple& getRegistros();
    string getMensaje() const;

    // ---- Operaciones ----
    bool registrarProfesor(Profesor p);
    bool agregarClase(string ced, int fr, string mat);
    bool eliminarProfesor(string cedula);
    bool marcarEntrada(string cedula, string fecha, Hora h);
    bool marcarSalida(string cedula, string fecha, Hora h);

    void mostrarProfesores() const;
    void mostrarProfesoresAlReves() const;
    void mostrarRegistros() const;
    void mostrarRegistrosProfesor(string cedula) const;

    // ---- Archivos de texto (usan la clase Archivo) ----
    bool guardarDatos();   // guarda las dos listas en profesores.txt y registros.txt
    bool cargarDatos();    // llena las listas con los archivos, si existen
};

#endif
