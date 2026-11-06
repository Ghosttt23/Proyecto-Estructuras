/***********************************************************************
 * Module:  Validacion.cpp
 * Author:  Usuario-PC
 * Modified: viernes, 6 de noviembre de 2026 0:41:36
 * Purpose: Implementation of the class Validacion
 ***********************************************************************/

#include "Validacion.h"
#include <cstdlib>   // exit

// ===================== Auxiliares privadas =====================

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esDigito(char c)
// Purpose:    Implementation of Validacion::esDigito()
// Parameters:
// - c
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validacion::esDigito(char c) {
    return c >= '0' && c <= '9';
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esLetra(char c)
// Purpose:    Implementation of Validacion::esLetra()
// Parameters:
// - c
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Letras sin tilde (a-z, A-Z) o cualquier caracter especial del alfabeto
// (á, é, í, ó, ú, ñ, ü...). Esos caracteres tienen un codigo mayor que 127,
// por eso se revisa (unsigned char)c >= 128.
bool Validacion::esLetra(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (unsigned char)c >= 128;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esBisiesto(int anio)
// Purpose:    Implementation of Validacion::esBisiesto()
// Parameters:
// - anio
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Un anio es bisiesto si es divisible para 4, excepto los divisibles para 100
// que no lo son para 400 (1900 no fue bisiesto, 2000 si)
bool Validacion::esBisiesto(int anio) {
    return (anio % 4 == 0 && anio % 100 != 0) || anio % 400 == 0;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::diasDelMes(int mes, int anio)
// Purpose:    Implementation of Validacion::diasDelMes()
// Parameters:
// - mes
// - anio
// Return:     int
////////////////////////////////////////////////////////////////////////

int Validacion::diasDelMes(int mes, int anio) {
    if (mes == 2) return esBisiesto(anio) ? 29 : 28;
    if (mes == 4 || mes == 6 || mes == 9 || mes == 11) return 30;
    return 31;
}

// ===================== Revisar un texto =====================

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esCedula(string ced)
// Purpose:    Implementation of Validacion::esCedula()
// Parameters:
// - ced
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validacion::esCedula(string ced) {
    // 1) Exactamente 10 digitos
    if (ced.length() != 10) return false;
    for (char c : ced) {
        if (!esDigito(c)) return false;
    }

    // 2) Los dos primeros digitos son la provincia: 01 a 24, o 30 (ecuatorianos en el exterior)
    int provincia = (ced.at(0) - '0') * 10 + (ced.at(1) - '0');
    if (!((provincia >= 1 && provincia <= 24) || provincia == 30)) return false;

    // 3) El tercer digito debe ser menor que 6 (persona natural)
    if (ced.at(2) - '0' >= 6) return false;

    // 4) Digito verificador (algoritmo modulo 10):
    //    los 9 primeros digitos se multiplican por 2,1,2,1,2,1,2,1,2;
    //    si un producto pasa de 9 se le resta 9; luego se suman todos.
    int suma = 0;
    for (int i = 0; i < 9; i++) {
        int digito = ced.at(i) - '0';
        int producto = (i % 2 == 0) ? digito * 2 : digito;
        if (producto > 9) producto -= 9;
        suma += producto;
    }
    int verificador = (10 - suma % 10) % 10;   // lo que falta para llegar a la decena
    return verificador == ced.at(9) - '0';
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esNombre(string nom)
// Purpose:    Implementation of Validacion::esNombre()
// Parameters:
// - nom
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Solo letras y espacios. No puede empezar ni terminar con espacio
// ni tener dos espacios seguidos. Ej: "Juan Carlos" valido, " Juan", "Juan2" no.
bool Validacion::esNombre(string nom) {
    if (nom.length() < 2 || nom.length() > 40) return false;
    if (nom.at(0) == ' ' || nom.at(nom.length() - 1) == ' ') return false;

    for (int i = 0; i < (int)nom.length(); i++) {
        char c = nom.at(i);
        if (c == ' ') {
            if (nom.at(i - 1) == ' ') return false;   // dos espacios seguidos
        } else if (!esLetra(c)) {
            return false;                              // numero o simbolo
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esMateria(string mat)
// Purpose:    Implementation of Validacion::esMateria()
// Parameters:
// - mat
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Como el nombre, pero tambien acepta numeros: "Quimica 1", "Calculo 2"
bool Validacion::esMateria(string mat) {
    if (mat.length() < 2 || mat.length() > 40) return false;
    if (mat.at(0) == ' ' || mat.at(mat.length() - 1) == ' ') return false;

    bool tieneLetra = false;
    for (int i = 0; i < (int)mat.length(); i++) {
        char c = mat.at(i);
        if (c == ' ') {
            if (mat.at(i - 1) == ' ') return false;
        } else if (esLetra(c)) {
            tieneLetra = true;
        } else if (!esDigito(c)) {
            return false;
        }
    }
    return tieneLetra;   // "123" no es una materia
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esFecha(string fecha)
// Purpose:    Implementation of Validacion::esFecha()
// Parameters:
// - fecha
// Return:     bool
////////////////////////////////////////////////////////////////////////

// Formato AAAA-MM-DD. Ej: "2026-11-06" valido; "2026-02-30" no (febrero no tiene 30)
bool Validacion::esFecha(string fecha) {
    if (fecha.length() != 10) return false;
    if (fecha.at(4) != '-' || fecha.at(7) != '-') return false;
    for (int i = 0; i < 10; i++) {
        if (i == 4 || i == 7) continue;
        if (!esDigito(fecha.at(i))) return false;
    }

    int anio = stoi(fecha.substr(0, 4));   // seguro: ya sabemos que son digitos
    int mes  = stoi(fecha.substr(5, 2));
    int dia  = stoi(fecha.substr(8, 2));

    if (anio < 2000 || anio > 2100) return false;
    if (mes < 1 || mes > 12) return false;
    if (dia < 1 || dia > diasDelMes(mes, anio)) return false;
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::diaDeLaSemana(string fecha)
// Purpose:    Implementation of Validacion::diaDeLaSemana()
// Parameters:
// - fecha
// Return:     int
////////////////////////////////////////////////////////////////////////

// Calcula el dia de la semana con la formula de Zeller.
// En la formula, enero y febrero se cuentan como los meses 13 y 14 del anio anterior.
// Zeller devuelve 0 = sabado, 1 = domingo, 2 = lunes ... 6 = viernes;
// al final se convierte a 1 = lunes ... 7 = domingo, que es mas facil de leer.
// La fecha debe ser valida (revisar antes con esFecha).
int Validacion::diaDeLaSemana(string fecha) {
    int anio = stoi(fecha.substr(0, 4));
    int mes  = stoi(fecha.substr(5, 2));
    int dia  = stoi(fecha.substr(8, 2));

    if (mes < 3) {        // enero y febrero
        mes += 12;
        anio -= 1;
    }
    int K = anio % 100;   // anio dentro del siglo
    int J = anio / 100;   // siglo
    int h = (dia + 13 * (mes + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

    return ((h + 5) % 7) + 1;   // 0 (sabado) -> 6, 1 (domingo) -> 7, 2 (lunes) -> 1 ...
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::nombreDia(string fecha)
// Purpose:    Implementation of Validacion::nombreDia()
// Parameters:
// - fecha
// Return:     string
////////////////////////////////////////////////////////////////////////

string Validacion::nombreDia(string fecha) {
    if (!esFecha(fecha)) return "";
    switch (diaDeLaSemana(fecha)) {
        case 1: return "Lunes";
        case 2: return "Martes";
        case 3: return "Miercoles";
        case 4: return "Jueves";
        case 5: return "Viernes";
        case 6: return "Sabado";
        default: return "Domingo";
    }
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esDiaLaborable(string fecha)
// Purpose:    Implementation of Validacion::esDiaLaborable()
// Parameters:
// - fecha
// Return:     bool
////////////////////////////////////////////////////////////////////////

// No hay clases sabados ni domingos
bool Validacion::esDiaLaborable(string fecha) {
    if (!esFecha(fecha)) return false;
    return diaDeLaSemana(fecha) <= 5;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esHora(string hora)
// Purpose:    Implementation of Validacion::esHora()
// Parameters:
// - hora
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validacion::esHora(string hora) {
    return Hora::esValida(hora);
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esEntero(string texto)
// Purpose:    Implementation of Validacion::esEntero()
// Parameters:
// - texto
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validacion::esEntero(string texto) {
    if (texto.length() == 0 || texto.length() > 9) return false;   // 9 digitos: no se desborda un int
    for (char c : texto) {
        if (!esDigito(c)) return false;
    }
    return true;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::esEnteroEnRango(string texto, int min, int max)
// Purpose:    Implementation of Validacion::esEnteroEnRango()
// Parameters:
// - texto
// - min
// - max
// Return:     bool
////////////////////////////////////////////////////////////////////////

bool Validacion::esEnteroEnRango(string texto, int min, int max) {
    if (!esEntero(texto)) return false;
    int n = stoi(texto);
    return n >= min && n <= max;
}

// ===================== Leer del teclado =====================

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::leerTexto(string mensaje)
// Purpose:    Implementation of Validacion::leerTexto()
// Parameters:
// - mensaje
// Return:     string
////////////////////////////////////////////////////////////////////////

// Lee la linea completa que escribe el usuario hasta el Enter.
// Se usa getline (y no cin >>) porque getline acepta cualquier cosa sin romperse;
// despues cada funcion revisa si lo leido es valido.
string Validacion::leerTexto(string mensaje) {
    cout << mensaje;
    string linea;
    if (!getline(cin, linea)) {
        // Se termino la entrada (por ejemplo, Ctrl+Z en Windows): se cierra el programa
        cout << endl << "Entrada finalizada." << endl;
        exit(0);
    }
    // Quita el '\r' que deja Windows al final de la linea
    if (linea.length() > 0 && linea.at(linea.length() - 1) == '\r')
        linea.erase(linea.length() - 1);
    return linea;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::leerCedula(string mensaje)
// Purpose:    Implementation of Validacion::leerCedula()
// Parameters:
// - mensaje
// Return:     string
////////////////////////////////////////////////////////////////////////

string Validacion::leerCedula(string mensaje) {
    string ced = leerTexto(mensaje);
    while (!esCedula(ced)) {
        cout << "   Cedula invalida: deben ser 10 digitos de una cedula ecuatoriana real." << endl;
        ced = leerTexto(mensaje);
    }
    return ced;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::leerNombre(string mensaje)
// Purpose:    Implementation of Validacion::leerNombre()
// Parameters:
// - mensaje
// Return:     string
////////////////////////////////////////////////////////////////////////

string Validacion::leerNombre(string mensaje) {
    string nom = leerTexto(mensaje);
    while (!esNombre(nom)) {
        cout << "   Dato invalido: solo letras y espacios (2 a 40 caracteres)." << endl;
        nom = leerTexto(mensaje);
    }
    return nom;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::leerMateria(string mensaje)
// Purpose:    Implementation of Validacion::leerMateria()
// Parameters:
// - mensaje
// Return:     string
////////////////////////////////////////////////////////////////////////

string Validacion::leerMateria(string mensaje) {
    string mat = leerTexto(mensaje);
    while (!esMateria(mat)) {
        cout << "   Materia invalida: letras, numeros y espacios (2 a 40 caracteres)." << endl;
        mat = leerTexto(mensaje);
    }
    return mat;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::leerFecha(string mensaje)
// Purpose:    Implementation of Validacion::leerFecha()
// Parameters:
// - mensaje
// Return:     string
////////////////////////////////////////////////////////////////////////

// Pide la fecha hasta que tenga el formato correcto Y sea de lunes a viernes
string Validacion::leerFecha(string mensaje) {
    string fecha = leerTexto(mensaje);
    while (!esDiaLaborable(fecha)) {
        if (!esFecha(fecha))
            cout << "   Fecha invalida: use el formato AAAA-MM-DD (ej. 2026-11-06)." << endl;
        else
            cout << "   El " << fecha << " es " << nombreDia(fecha)
                 << ": no hay clases sabados ni domingos." << endl;
        fecha = leerTexto(mensaje);
    }
    return fecha;
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::leerHora(string mensaje)
// Purpose:    Implementation of Validacion::leerHora()
// Parameters:
// - mensaje
// Return:     Hora
////////////////////////////////////////////////////////////////////////

Hora Validacion::leerHora(string mensaje) {
    string texto = leerTexto(mensaje);
    while (!esHora(texto)) {
        cout << "   Hora invalida: use el formato HH:MM de 24 horas (ej. 07:05)." << endl;
        texto = leerTexto(mensaje);
    }
    return Hora(texto);
}

////////////////////////////////////////////////////////////////////////
// Name:       Validacion::leerEntero(string mensaje, int min, int max)
// Purpose:    Implementation of Validacion::leerEntero()
// Parameters:
// - mensaje
// - min
// - max
// Return:     int
////////////////////////////////////////////////////////////////////////

int Validacion::leerEntero(string mensaje, int min, int max) {
    string texto = leerTexto(mensaje);
    while (!esEnteroEnRango(texto, min, max)) {
        cout << "   Opcion invalida: ingrese un numero entre " << min << " y " << max << "." << endl;
        texto = leerTexto(mensaje);
    }
    return stoi(texto);
}
