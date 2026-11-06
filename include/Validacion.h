/***********************************************************************
 * Module:  Validacion.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class Validacion
 ***********************************************************************/

#if !defined(__SistemaRegistro_Validacion_h)
#define __SistemaRegistro_Validacion_h

#include <string>
#include "Hora.h"
using namespace std;

// Centraliza TODAS las validaciones del sistema.
// Todos sus metodos son static: se usan sin crear un objeto -> Validacion::esCedula("...")
//
// Tiene dos grupos de funciones:
//  - esXxx(texto):     solo revisan si un texto es valido (devuelven true / false).
//  - leerXxx(mensaje): muestran el mensaje, leen lo que escribe el usuario despues del Enter
//                      y, si esta mal, muestran el error y lo vuelven a pedir hasta que sea valido.
//                      Usan getline, asi el programa no se rompe si escriben letras donde van numeros.
class Validacion {
private:
    static bool esLetra(char c);           // a-z, A-Z o caracter con tilde / ñ
    static bool esDigito(char c);          // 0-9
    static int diasDelMes(int mes, int anio);
    static bool esBisiesto(int anio);

public:
    // ---- Revisar un texto ----
    static bool esCedula(string ced);      // cedula ecuatoriana real (10 digitos + verificador)
    static bool esNombre(string nom);      // solo letras y espacios simples, 2 a 40 caracteres
    static bool esMateria(string mat);     // letras, numeros y espacios, 2 a 40 caracteres
    static bool esFecha(string fecha);     // AAAA-MM-DD, con dias segun el mes y bisiestos
    static int diaDeLaSemana(string fecha);       // 1 = lunes ... 6 = sabado, 7 = domingo
    static string nombreDia(string fecha);        // "Lunes", "Martes", ...
    static bool esDiaLaborable(string fecha);     // fecha valida y de lunes a viernes
    static bool esHora(string hora);       // HH:MM (usa Hora::esValida)
    static bool esEntero(string texto);    // solo digitos (sin signo, sin espacios)
    static bool esEnteroEnRango(string texto, int min, int max);

    // ---- Leer del teclado hasta que el dato sea valido ----
    static string leerTexto(string mensaje);                 // lee una linea completa
    static string leerCedula(string mensaje);
    static string leerNombre(string mensaje);
    static string leerMateria(string mensaje);
    static string leerFecha(string mensaje);       // solo acepta dias de lunes a viernes
    static Hora leerHora(string mensaje);
    static int leerEntero(string mensaje, int min, int max);
};

#endif
