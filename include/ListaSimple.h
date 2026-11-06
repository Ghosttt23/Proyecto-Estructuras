/***********************************************************************
 * Module:  ListaSimple.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class ListaSimple
 ***********************************************************************/

#if !defined(__SistemaRegistro_ListaSimple_h)
#define __SistemaRegistro_ListaSimple_h

#include "NodoSimple.h"

// Lista simplemente enlazada con el historial de registros (entradas y salidas).
// Cada nodo solo conoce al siguiente; se recorre de la cabeza hacia el final.
class ListaSimple {
private:
    NodoSimple* cabeza;   // primer nodo (nullptr si esta vacia)
    int tamanio;

public:
    ListaSimple();
    ~ListaSimple();   // libera todos los nodos

    // Copia bloqueada (mismo motivo que en ListaDoble)
    ListaSimple(const ListaSimple&) = delete;
    ListaSimple& operator=(const ListaSimple&) = delete;

    // ---- Getters ----
    NodoSimple* getCabeza() const;
    int getTamanio() const;

    // ---- Operaciones ----
    void insertar(Registro r);   // agrega al final (orden en que ocurrieron)
    Registro* buscar(string cedula, string fecha, int numFranja) const;   // nullptr si no existe
    void mostrar() const;
    void mostrarPorProfesor(string cedula) const;
    bool estaVacia() const;
};

#endif
