/***********************************************************************
 * Module:  Franja.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class Franja
 ***********************************************************************/

#if !defined(__SistemaRegistro_Franja_h)
#define __SistemaRegistro_Franja_h

#include "Hora.h"

// Representa una clase dictada en una de las 7 franjas de la ESPE (bloques de 2 horas):
// 1) 07-09  2) 09-11  3) 11-13  4) 13-15  5) 15-17  6) 17-19  7) 19-21
// Cada franja guarda su propia materia, porque un profesor puede dar
// materias distintas en horarios distintos.
class Franja {
private:
    int numero;       // 1 a 7 (0 = sin franja)
    string materia;   // materia que se dicta en esa franja
    Hora inicio;      // se calcula a partir del numero
    Hora fin;         // se calcula a partir del numero

public:
    // ---- Constructores sobrecargados ----
    Franja();                                // franja vacia (numero 0)
    Franja(int numero);                      // sin materia
    Franja(int numero, string materia);      // con materia

    // ---- Getters ----
    int getNumero() const;
    string getMateria() const;
    Hora getInicio() const;
    Hora getFin() const;

    // ---- Setters ----
    // No hay setInicio ni setFin: las horas SIEMPRE se calculan con el numero,
    // asi una franja nunca puede quedar con horas incoherentes.
    void setNumero(int numero);   // valida (1 a 7) y recalcula inicio y fin
    bool setMateria(string materia);   // valida con Validacion::esMateria

    // Reglas de los 10 minutos
    bool puedeEntrar(Hora h) const;   // inicio <= h <= inicio + 10
    bool puedeSalir(Hora h) const;    // fin - 10 <= h <= fin

    // ---- Sobrecarga de operadores ----
    bool operator==(const Franja& otra) const;   // iguales si tienen el mismo numero
    friend ostream& operator<<(ostream& os, const Franja& f);
};

#endif
