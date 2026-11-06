/***********************************************************************
 * Module:  Archivo.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 9:45:00
 * Purpose: Declaration of the class Archivo
 ***********************************************************************/

#if !defined(__SistemaRegistro_Archivo_h)
#define __SistemaRegistro_Archivo_h

#include "ListaDoble.h"
#include "ListaSimple.h"

// Se encarga SOLO de leer y escribir los archivos de texto.
// No guarda datos, por eso todos sus metodos son static:
// se usan sin crear un objeto -> Archivo::guardarProfesores(lista, "profesores.txt")
//
// Formato de los archivos (se usa ';' como separador porque ningun dato valido lo contiene):
//   profesores.txt -> cedula;nombre;apellido;numClases
//                     y debajo una linea por clase: numFranja;materia
//   registros.txt  -> fecha;cedula;numFranja;horaEntrada;horaSalida   (--:-- si aun no sale)
class Archivo {
private:
    static void quitarRetorno(string& linea);   // quita el '\r' que deja Windows al final

public:
    // Guardar: recorren la lista con punteros y escriben una linea por dato.
    // Devuelven false si no se pudo abrir el archivo.
    static bool guardarProfesores(ListaDoble& lista, string ruta);
    static bool guardarRegistros(ListaSimple& lista, string ruta);

    // Cargar: leen el archivo (si existe), validan cada dato otra vez y llenan la lista.
    // Las lineas danadas o repetidas se ignoran. Devuelven false si el archivo no existe.
    static bool cargarProfesores(ListaDoble& lista, string ruta);
    static bool cargarRegistros(ListaSimple& lista, string ruta);
};

#endif
