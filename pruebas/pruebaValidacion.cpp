// Prueba de la clase Validacion
// Compilar (desde la carpeta principal):
//   g++ -Iinclude pruebas/pruebaValidacion.cpp src/Validacion.cpp src/Hora.cpp -o pruebaValidacion
#include "Validacion.h"

// Muestra si un texto es valido segun la funcion recibida
void probar(string nombre, string texto, bool resultado) {
    cout << nombre << "(\"" << texto << "\") -> " << (resultado ? "valido" : "NO valido") << endl;
}

int main() {
    cout << "=== Nombres ===" << endl;
    probar("esNombre", "Juan Carlos", Validacion::esNombre("Juan Carlos"));
    probar("esNombre", "Martín Peña", Validacion::esNombre("Martín Peña"));
    probar("esNombre", "Juan2", Validacion::esNombre("Juan2"));
    probar("esNombre", "Juan  Carlos", Validacion::esNombre("Juan  Carlos"));
    probar("esNombre", " Juan", Validacion::esNombre(" Juan"));
    probar("esNombre", "", Validacion::esNombre(""));

    cout << endl << "=== Materias ===" << endl;
    probar("esMateria", "Quimica 1", Validacion::esMateria("Quimica 1"));
    probar("esMateria", "Estructura de Datos", Validacion::esMateria("Estructura de Datos"));
    probar("esMateria", "123", Validacion::esMateria("123"));
    probar("esMateria", "Calculo@", Validacion::esMateria("Calculo@"));

    cout << endl << "=== Fechas ===" << endl;
    probar("esFecha", "2026-11-06", Validacion::esFecha("2026-11-06"));
    probar("esFecha", "2028-02-29", Validacion::esFecha("2028-02-29"));
    probar("esFecha", "2026-02-29", Validacion::esFecha("2026-02-29"));
    probar("esFecha", "2026-04-31", Validacion::esFecha("2026-04-31"));
    probar("esFecha", "2026-13-01", Validacion::esFecha("2026-13-01"));
    probar("esFecha", "06/11/2026", Validacion::esFecha("06/11/2026"));

    cout << endl << "=== Dias de la semana ===" << endl;
    string fechas[] = { "2026-11-02", "2026-11-05", "2026-11-06", "2026-11-07", "2026-11-08", "2024-02-29", "2000-01-01" };
    for (string f : fechas)
        cout << f << " -> " << Validacion::nombreDia(f)
             << (Validacion::esDiaLaborable(f) ? "  (hay clases)" : "  (NO hay clases)") << endl;

    cout << endl << "=== Opciones de menu (1 a 7) ===" << endl;
    probar("esEnteroEnRango", "3", Validacion::esEnteroEnRango("3", 1, 7));
    probar("esEnteroEnRango", "8", Validacion::esEnteroEnRango("8", 1, 7));
    probar("esEnteroEnRango", "a", Validacion::esEnteroEnRango("a", 1, 7));
    probar("esEnteroEnRango", "-1", Validacion::esEnteroEnRango("-1", 1, 7));
    probar("esEnteroEnRango", "", Validacion::esEnteroEnRango("", 1, 7));

    // ---- Lectura: si el dato esta mal, se vuelve a pedir ----
    cout << endl << "=== Lectura desde teclado ===" << endl;
    string ced = Validacion::leerCedula("Cedula: ");
    string nom = Validacion::leerNombre("Nombre: ");
    int fr = Validacion::leerEntero("Franja (1-7): ", 1, 7);
    Hora h = Validacion::leerHora("Hora (HH:MM): ");
    string fecha = Validacion::leerFecha("Fecha (AAAA-MM-DD): ");

    cout << endl << "Datos leidos: " << ced << " | " << nom << " | franja " << fr
         << " | " << h << " | " << fecha << endl;
    return 0;
}
