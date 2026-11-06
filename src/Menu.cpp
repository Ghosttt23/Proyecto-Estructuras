/***********************************************************************
 * Module:  Menu.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class Menu
 ***********************************************************************/

#include "Menu.h"
#include "Validacion.h"

// ================= Menu principal =================

////////////////////////////////////////////////////////////////////////
// Name:       Menu::iniciar()
// Purpose:    Implementation of Menu::iniciar()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::iniciar() {
    int opcion = -1;
    while (opcion != 0) {
        cout << endl;
        cout << "==============================================" << endl;
        cout << "   SISTEMA DE REGISTRO DE PROFESORES - ESPE" << endl;
        cout << "==============================================" << endl;
        cout << " 1. Registrar profesor" << endl;
        cout << " 2. Agregar clase a un profesor" << endl;
        cout << " 3. Marcar entrada" << endl;
        cout << " 4. Marcar salida" << endl;
        cout << " 5. Buscar profesor" << endl;
        cout << " 6. Mostrar profesores (inicio -> fin)" << endl;
        cout << " 7. Mostrar profesores (fin -> inicio)" << endl;
        cout << " 8. Eliminar profesor" << endl;
        cout << " 9. Ver historial de registros" << endl;
        cout << "10. Ver historial de un profesor" << endl;
        cout << " 0. Salir" << endl;

        opcion = Validacion::leerEntero("Opcion: ", 0, 10);
        cout << endl;

        switch (opcion) {
            case 1:  opcionRegistrarProfesor(); break;
            case 2:  opcionAgregarClase(); break;
            case 3:  opcionMarcarEntrada(); break;
            case 4:  opcionMarcarSalida(); break;
            case 5:  opcionBuscarProfesor(); break;
            case 6:  sistema.mostrarProfesores(); break;
            case 7:  sistema.mostrarProfesoresAlReves(); break;
            case 8:  opcionEliminarProfesor(); break;
            case 9:  sistema.mostrarRegistros(); break;
            case 10: opcionHistorialProfesor(); break;
            case 0:  cout << "Hasta luego." << endl; break;
        }
        if (opcion != 0) pausa();
    }
}

// ================= Opciones =================

////////////////////////////////////////////////////////////////////////
// Name:       Menu::mostrarFranjas()
// Purpose:    Implementation of Menu::mostrarFranjas()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::mostrarFranjas() {
    cout << "Franjas disponibles:" << endl;
    for (int i = 1; i <= 7; i++)
        cout << "   " << Franja(i) << endl;
}

////////////////////////////////////////////////////////////////////////
// Name:       Menu::opcionRegistrarProfesor()
// Purpose:    Implementation of Menu::opcionRegistrarProfesor()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::opcionRegistrarProfesor() {
    cout << "--- Registrar profesor ---" << endl;
    string ced = Validacion::leerCedula("Cedula: ");
    if (sistema.getProfesores().buscar(ced) != nullptr) {
        cout << "Ya existe un profesor con esa cedula." << endl;
        return;
    }
    string nom = Validacion::leerNombre("Nombre: ");
    string ape = Validacion::leerNombre("Apellido: ");

    sistema.registrarProfesor(Profesor(ced, nom, ape));
    cout << sistema.getMensaje() << endl;

    // Se le agregan sus clases (al menos una)
    int otra = 1;
    while (otra == 1) {
        cout << endl;
        mostrarFranjas();
        int fr = Validacion::leerEntero("Numero de franja (1-7): ", 1, 7);
        string mat = Validacion::leerMateria("Materia: ");
        sistema.agregarClase(ced, fr, mat);
        cout << sistema.getMensaje() << endl;
        otra = Validacion::leerEntero("Agregar otra clase? (1 = Si, 2 = No): ", 1, 2);
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       Menu::opcionAgregarClase()
// Purpose:    Implementation of Menu::opcionAgregarClase()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::opcionAgregarClase() {
    cout << "--- Agregar clase ---" << endl;
    string ced = Validacion::leerCedula("Cedula del profesor: ");
    Profesor* p = sistema.getProfesores().buscar(ced);
    if (p == nullptr) {
        cout << "No existe un profesor con esa cedula." << endl;
        return;
    }
    cout << "Clases actuales:" << endl << *p << endl << endl;
    mostrarFranjas();
    int fr = Validacion::leerEntero("Numero de franja (1-7): ", 1, 7);
    string mat = Validacion::leerMateria("Materia: ");
    sistema.agregarClase(ced, fr, mat);
    cout << sistema.getMensaje() << endl;
}

////////////////////////////////////////////////////////////////////////
// Name:       Menu::opcionMarcarEntrada()
// Purpose:    Implementation of Menu::opcionMarcarEntrada()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::opcionMarcarEntrada() {
    cout << "--- Marcar entrada ---" << endl;
    string ced = Validacion::leerCedula("Cedula: ");
    string fecha = Validacion::leerFecha("Fecha (AAAA-MM-DD): ");
    Hora h = Validacion::leerHora("Hora (HH:MM): ");
    sistema.marcarEntrada(ced, fecha, h);
    cout << sistema.getMensaje() << endl;
}

////////////////////////////////////////////////////////////////////////
// Name:       Menu::opcionMarcarSalida()
// Purpose:    Implementation of Menu::opcionMarcarSalida()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::opcionMarcarSalida() {
    cout << "--- Marcar salida ---" << endl;
    string ced = Validacion::leerCedula("Cedula: ");
    string fecha = Validacion::leerFecha("Fecha (AAAA-MM-DD): ");
    Hora h = Validacion::leerHora("Hora (HH:MM): ");
    sistema.marcarSalida(ced, fecha, h);
    cout << sistema.getMensaje() << endl;
}

////////////////////////////////////////////////////////////////////////
// Name:       Menu::opcionBuscarProfesor()
// Purpose:    Implementation of Menu::opcionBuscarProfesor()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::opcionBuscarProfesor() {
    cout << "--- Buscar profesor ---" << endl;
    string ced = Validacion::leerCedula("Cedula: ");
    Profesor* p = sistema.getProfesores().buscar(ced);
    if (p == nullptr) cout << "No existe un profesor con esa cedula." << endl;
    else cout << *p << endl;
}

////////////////////////////////////////////////////////////////////////
// Name:       Menu::opcionEliminarProfesor()
// Purpose:    Implementation of Menu::opcionEliminarProfesor()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::opcionEliminarProfesor() {
    cout << "--- Eliminar profesor ---" << endl;
    string ced = Validacion::leerCedula("Cedula: ");
    Profesor* p = sistema.getProfesores().buscar(ced);
    if (p == nullptr) {
        cout << "No existe un profesor con esa cedula." << endl;
        return;
    }
    cout << *p << endl;
    int ok = Validacion::leerEntero("Seguro que desea eliminarlo? (1 = Si, 2 = No): ", 1, 2);
    if (ok == 1) {
        sistema.eliminarProfesor(ced);
        cout << sistema.getMensaje() << endl;
    } else {
        cout << "Operacion cancelada." << endl;
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       Menu::opcionHistorialProfesor()
// Purpose:    Implementation of Menu::opcionHistorialProfesor()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::opcionHistorialProfesor() {
    cout << "--- Historial de un profesor ---" << endl;
    string ced = Validacion::leerCedula("Cedula: ");
    sistema.mostrarRegistrosProfesor(ced);
}

////////////////////////////////////////////////////////////////////////
// Name:       Menu::pausa()
// Purpose:    Implementation of Menu::pausa()
// Return:     void
////////////////////////////////////////////////////////////////////////

void Menu::pausa() {
    Validacion::leerTexto("\nPresione Enter para continuar...");
}
