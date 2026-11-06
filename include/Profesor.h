/***********************************************************************
 * Module:  Profesor.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class Profesor
 ***********************************************************************/

#if !defined(__SistemaRegistro_Profesor_h)
#define __SistemaRegistro_Profesor_h

#include <string>
#include "Franja.h"
#include "Validacion.h"
using namespace std;

// Representa a un profesor. Puede tener VARIAS clases, pero en franjas distintas
// (no puede tener dos clases a la misma hora). Cada clase (Franja) tiene su materia.
//
// Las clases se guardan en un ARREGLO DINAMICO (memoria dinamica con new/delete):
// empieza con espacio para 2 clases y, cuando se llena, crece al doble.
// Como solo existen 7 franjas, nunca tendra mas de 7 clases.
// Los elementos se recorren con aritmetica de punteros: *(franjas + i)
class Profesor {
private:
    static const int MAX_FRANJAS = 7;
    static const int CAPACIDAD_INICIAL = 2;

    string cedula;      // identifica al profesor (no se repite)
    string nombre;
    string apellido;
    Franja* franjas;    // puntero al arreglo dinamico de clases (ordenadas por horario)
    int numFranjas;     // cuantas clases tiene asignadas
    int capacidad;      // cuantas clases caben en el arreglo actual

    // Crea un arreglo mas grande, copia las clases y libera el anterior
    void crecer();

public:
    // ---- Constructores sobrecargados ----
    // Usan los setters: si un dato es invalido, ese campo queda vacio ("").
    Profesor();
    Profesor(string ced, string nom, string ape);                                  // sin clases
    Profesor(string ced, string nom, string ape, int numFranja, string materia);   // con una clase

    // ---- Manejo de memoria dinamica ----
    Profesor(const Profesor& otro);              // constructor copia (copia el arreglo, no el puntero)
    Profesor& operator=(const Profesor& otro);   // asignacion (libera lo viejo y copia lo nuevo)
    ~Profesor();                                 // destructor (libera el arreglo con delete[])

    // ---- Getters ----
    string getCedula() const;
    string getNombre() const;
    string getApellido() const;
    int getNumFranjas() const;
    int getCapacidad() const;
    Franja getFranja(int indice) const;   // clase en la posicion indice (0 .. numFranjas-1)

    // ---- Setters ----
    // Validan el dato con la clase Validacion: si es invalido NO lo cambian y devuelven false.
    bool setCedula(string ced);
    bool setNombre(string nom);
    bool setApellido(string ape);

    // ---- Manejo de clases (franjas) ----
    // Funcion sobrecargada: se puede agregar por numero + materia o por objeto Franja.
    // Devuelve false si la franja no es valida, si la materia no es valida,
    // si ya tiene clase a esa hora o si ya tiene 7.
    bool agregarFranja(int numFranja, string materia);
    bool agregarFranja(Franja f);
    bool quitarFranja(int numFranja);       // false si no la tenia
    bool tieneFranja(int numFranja) const;

    // Devuelven el numero de la franja que acepta esa hora, o 0 si ninguna
    int franjaParaEntrada(Hora h) const;
    int franjaParaSalida(Hora h) const;

    // ---- Sobrecarga de operadores ----
    bool operator==(const Profesor& otro) const;   // iguales si tienen la misma cedula
    friend ostream& operator<<(ostream& os, const Profesor& p);
};

#endif
