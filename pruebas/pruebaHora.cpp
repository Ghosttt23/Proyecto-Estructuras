// Prueba de la clase Hora
// Compilar (desde la carpeta principal):
//   g++ -Iinclude pruebas/pruebaHora.cpp src/Hora.cpp -o pruebaHora
#include "Hora.h"

int main() {
    Hora inicio(7, 0);          // constructor (int, int)
    Hora fin("09:00");          // constructor (string)

    Hora limiteEntrada = inicio + 10;   // operator+
    Hora inicioSalida  = fin - 10;      // operator-

    cout << "Franja: " << inicio << " - " << fin << endl;
    cout << "Puede entrar hasta: " << limiteEntrada << endl;
    cout << "Puede salir desde:  " << inicioSalida << endl << endl;

    Hora llegada(7, 8);
    if (llegada >= inicio && llegada <= limiteEntrada)
        cout << llegada << " -> entrada VALIDA" << endl;
    else
        cout << llegada << " -> entrada NO valida" << endl;

    Hora tarde(7, 15);
    if (tarde >= inicio && tarde <= limiteEntrada)
        cout << tarde << " -> entrada VALIDA" << endl;
    else
        cout << tarde << " -> entrada NO valida (llego tarde)" << endl;

    // ---- Validacion de texto: el programa ya no se cae ----
    cout << endl << "=== Validacion de texto ===" << endl;
    string textos[] = { "07:05", "23:59", "24:00", "07:60", "7:05", "ab:cd", "", "0705" };
    for (string t : textos) {
        cout << "\"" << t << "\" -> " << (Hora::esValida(t) ? "valida" : "NO valida")
             << "   Hora creada: " << Hora(t) << endl;
    }

    return 0;
}
