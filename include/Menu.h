/***********************************************************************
 * Module:  Menu.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class Menu
 ***********************************************************************/

#if !defined(__SistemaRegistro_Menu_h)
#define __SistemaRegistro_Menu_h

#include "SistemaRegistro.h"

// Interfaz en consola: muestra las opciones, pide los datos con Validacion
// (que los vuelve a pedir si estan mal) y llama al SistemaRegistro.
class Menu {
private:
    SistemaRegistro sistema;

    void mostrarFranjas();          // tabla con las 7 franjas de la ESPE
    void opcionRegistrarProfesor();
    void opcionAgregarClase();
    void opcionMarcarEntrada();
    void opcionMarcarSalida();
    void opcionBuscarProfesor();
    void opcionEliminarProfesor();
    void opcionHistorialProfesor();
    void pausa();

public:
    void iniciar();
};

#endif
