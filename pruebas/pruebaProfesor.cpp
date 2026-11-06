// Prueba de Franja y Profesor
// Compilar (desde la carpeta principal):
//   g++ -Iinclude pruebas/pruebaProfesor.cpp src/Profesor.cpp src/Franja.cpp src/Hora.cpp -o pruebaProfesor
#include "Profesor.h"

int main() {
    // ---- Las 7 franjas ----
    cout << "=== Franjas de la ESPE ===" << endl;
    for (int i = 1; i <= 7; i++) {
        Franja f(i);
        cout << f << "  entrada hasta " << f.getInicio() + 10
             << ", salida desde " << f.getFin() - 10 << endl;
    }

    // ---- Validacion de cedula ----
    cout << endl << "=== Validacion de cedula ===" << endl;
    string cedulas[] = { "1710034065", "1710034066", "171003406", "17100340AB", "9910034065", "1790034065" };
    for (string c : cedulas)
        cout << c << " -> " << (Validacion::esCedula(c) ? "valida" : "NO valida") << endl;

    // ---- Profesor con varias clases, cada una con su materia ----
    cout << endl << "=== Profesor con varias clases ===" << endl;
    Profesor p1("1710034065", "Juan", "Perez", 4, "Estructura de Datos");

    cout << "Agregar franja 1 (Programacion): "
         << (p1.agregarFranja(1, "Programacion") ? "OK" : "rechazada") << endl;
    cout << "Agregar franja 6 (objeto):       "
         << (p1.agregarFranja(Franja(6, "Calculo")) ? "OK" : "rechazada") << endl;
    cout << "Agregar franja 4 otra vez:       "
         << (p1.agregarFranja(4, "Fisica") ? "OK" : "rechazada (ya tiene clase a esa hora)") << endl;
    cout << "Agregar franja 9:                "
         << (p1.agregarFranja(9, "Algebra") ? "OK" : "rechazada (no existe)") << endl;
    cout << p1 << endl;

    // ---- Que clase le corresponde segun la hora ----
    cout << endl << "=== Buscar clase segun la hora ===" << endl;
    Hora horas[] = { Hora("07:05"), Hora("13:00"), Hora("13:15"), Hora("14:55"), Hora("18:55") };
    for (Hora h : horas) {
        int e = p1.franjaParaEntrada(h);
        int s = p1.franjaParaSalida(h);
        cout << h << "  entrada -> " << (e ? "franja " + to_string(e) : "ninguna")
             << "   salida -> " << (s ? "franja " + to_string(s) : "ninguna") << endl;
    }

    // ---- Quitar una clase ----
    cout << endl << "=== Quitar franja 4 ===" << endl;
    p1.quitarFranja(4);
    cout << p1 << endl;

    // ---- Getters y setters ----
    cout << endl << "=== Getters y setters ===" << endl;
    p1.setNombre("Juan Carlos");
    cout << "Nombre: " << p1.getNombre() << " | Cedula: " << p1.getCedula()
         << " | Clases: " << p1.getNumFranjas()
         << " | Primera: " << p1.getFranja(0).getMateria() << endl;

    // ---- Los setters validan ----
    cout << endl << "=== Setters con validacion ===" << endl;
    cout << "setNombre(\"Juan2\"):   " << (p1.setNombre("Juan2") ? "aceptado" : "rechazado") << endl;
    cout << "setCedula(\"123\"):     " << (p1.setCedula("123") ? "aceptado" : "rechazado") << endl;
    cout << "agregarFranja(2, \"\"): " << (p1.agregarFranja(2, "") ? "aceptado" : "rechazado (materia vacia)") << endl;
    cout << "El profesor sigue igual: " << p1.getNombre() << " / " << p1.getCedula() << endl;

    // ---- operator== ----
    Profesor p2("1710034065", "Otro", "Nombre");
    Profesor p3("0912345675", "Ana", "Lopez");
    cout << endl << "p1 == p2 (misma cedula): " << (p1 == p2 ? "true" : "false") << endl;
    cout << "p1 == p3 (otra cedula):  " << (p1 == p3 ? "true" : "false") << endl;

    // ---- Memoria dinamica: el arreglo crece solo ----
    cout << endl << "=== Arreglo dinamico ===" << endl;
    Profesor p4("0912345675", "Maria", "Torres");
    for (int n = 1; n <= 7; n++) {
        p4.agregarFranja(n, "Materia " + to_string(n));
        cout << "Clases: " << p4.getNumFranjas() << "   capacidad: " << p4.getCapacidad() << endl;
    }

    // ---- Constructor copia y operator= : cada uno tiene su propio arreglo ----
    cout << endl << "=== Copias independientes ===" << endl;
    Profesor copia(p4);      // constructor copia
    Profesor asignado;
    asignado = p4;           // operator=
    p4.quitarFranja(1);      // se modifica SOLO el original
    cout << "Original: " << p4.getNumFranjas() << " clases" << endl;
    cout << "Copia:    " << copia.getNumFranjas() << " clases" << endl;
    cout << "Asignado: " << asignado.getNumFranjas() << " clases" << endl;

    return 0;
}
