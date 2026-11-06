/***********************************************************************
 * Module:  Registro.h
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Declaration of the class Registro
 ***********************************************************************/

#if !defined(__SistemaRegistro_Registro_h)
#define __SistemaRegistro_Registro_h

#include <string>
#include "Hora.h"
using namespace std;

// Registro de asistencia de un profesor en UNA clase (franja) de UNA fecha:
// guarda la hora de entrada y la de salida.
class Registro {
private:
    string cedula;      // profesor al que pertenece
    string fecha;       // AAAA-MM-DD
    int numFranja;      // franja (clase) a la que corresponde
    Hora horaEntrada;
    Hora horaSalida;
    bool tieneEntrada;  // true cuando ya se marco la entrada
    bool tieneSalida;   // true cuando ya se marco la salida

public:
    // ---- Constructores sobrecargados ----
    Registro();
    Registro(string cedula, string fecha, int numFranja);

    // ---- Getters ----
    string getCedula() const;
    string getFecha() const;
    int getNumFranja() const;
    Hora getHoraEntrada() const;
    Hora getHoraSalida() const;
    bool getTieneEntrada() const;
    bool getTieneSalida() const;

    // ---- Setters ----
    void setCedula(string ced);
    void setFecha(string fec);
    void setNumFranja(int fr);

    // Guardan la hora y marcan que ya se registro
    void marcarEntrada(Hora h);
    void marcarSalida(Hora h);

    // Imprime: 2026-11-06 | 1710034065 | Franja 1 | Entrada 07:05 | Salida 08:55
    friend ostream& operator<<(ostream& os, const Registro& r);
};

#endif
