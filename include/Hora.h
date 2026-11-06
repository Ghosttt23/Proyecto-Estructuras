/***********************************************************************
 * Module:  Hora.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class Hora
 ***********************************************************************/

#if !defined(__SistemaRegistro_Hora_h)
#define __SistemaRegistro_Hora_h

#include <iostream>
#include <string>
using namespace std;

// Representa una hora del dia (formato 24h): 07:05, 13:50, etc.
class Hora {
private:
    int horas;
    int minutos;

public:
    // ---- Sobrecarga de constructores (funciones sobrecargadas) ----
    Hora();                    // 00:00
    Hora(int h, int m);        // Hora(7, 5)  -> 07:05
    Hora(string texto);        // Hora("07:05"). Si el texto no es valido queda en 00:00

    // Devuelve true si el texto tiene el formato HH:MM (00:00 a 23:59).
    // Es static: se usa sin crear un objeto -> Hora::esValida("07:05")
    // El menu la usa ANTES de crear la hora, para volver a pedirla si esta mal.
    static bool esValida(string texto);

    // ---- Getters y setters ----
    int getHoras() const;
    int getMinutos() const;
    void setHoras(int h);
    void setMinutos(int m);

    // Convierte la hora a minutos totales (07:05 -> 425). Facilita comparar.
    int enMinutos() const;

    // ---- Sobrecarga de operadores ----
    Hora operator+(int mins) const;   // hora + 10  -> 10 minutos despues
    Hora operator-(int mins) const;   // hora - 10  -> 10 minutos antes
    bool operator<(const Hora& otra) const;
    bool operator>(const Hora& otra) const;
    bool operator<=(const Hora& otra) const;
    bool operator>=(const Hora& otra) const;
    bool operator==(const Hora& otra) const;

    // Para poder hacer: cout << hora;
    friend ostream& operator<<(ostream& os, const Hora& h);
};

#endif
