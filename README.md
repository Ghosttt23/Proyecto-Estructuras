# Sistema de Registro de Profesores - ESPE

Proyecto de Estructura de Datos en C++. Registra la asistencia (entrada y salida) de los profesores en las franjas horarias de la ESPE.

## Reglas

- Franjas de 2 horas: 1) 07-09, 2) 09-11, 3) 11-13, 4) 13-15, 5) 15-17, 6) 17-19, 7) 19-21.
- Un profesor puede tener varias clases, pero en franjas distintas (cada una con su materia).
- **Entrada**: desde la hora de inicio hasta 10 minutos después (ej. 07:00 a 07:10).
- **Salida**: desde 10 minutos antes del fin hasta el fin (ej. 08:50 a 09:00).
- No se puede marcar la salida sin haber marcado la entrada.
- No hay clases sábados ni domingos.
- No se repiten cédulas, y la cédula debe ser ecuatoriana válida.

## Temas aplicados

| Tema | Dónde |
|---|---|
| Lista doble | `ListaDoble` / `NodoDoble`: profesores (se muestran de inicio a fin y de fin a inicio) |
| Lista simple | `ListaSimple` / `NodoSimple`: historial de registros |
| Getters y setters | Todas las clases (los setters de `Profesor` y `Franja` validan) |
| Sobrecarga de operadores | `Hora`: `+ - < > <= >= == <<` · `Franja`, `Profesor`: `== <<` · `Profesor`: `operator=` |
| Funciones sobrecargadas | Constructores de `Hora`, `Franja`, `Profesor`, `Registro`; `agregarFranja` |
| Punteros y memoria dinámica | Nodos con `new`/`delete`; arreglo dinámico de clases en `Profesor` (`crecer()`, constructor copia, destructor) recorrido con `*(franjas + i)` |

## Estructura

```
include/   archivos .h
src/       archivos .cpp y main.cpp
pruebas/   pruebas de cada clase y datos para la demostración
docs/      diagrama de clases
```

## Compilar y ejecutar

Desde la carpeta principal del proyecto:

```
g++ -Iinclude src/main.cpp src/Menu.cpp src/SistemaRegistro.cpp src/ListaDoble.cpp src/NodoDoble.cpp src/ListaSimple.cpp src/NodoSimple.cpp src/Registro.cpp src/Profesor.cpp src/Franja.cpp src/Hora.cpp src/Validacion.cpp -o sistema
```

Windows: `.\sistema.exe` — Linux/Mac: `./sistema`

### Demostración automática

`pruebas/datos_demo.txt` tiene una demostración completa (datos correctos e incorrectos):

```
.\sistema.exe < pruebas\datos_demo.txt
```

### Pruebas por clase

```
g++ -Iinclude pruebas/pruebaHora.cpp src/Hora.cpp -o pruebaHora
g++ -Iinclude pruebas/pruebaValidacion.cpp src/Validacion.cpp src/Hora.cpp -o pruebaValidacion
g++ -Iinclude pruebas/pruebaProfesor.cpp src/Profesor.cpp src/Franja.cpp src/Hora.cpp src/Validacion.cpp -o pruebaProfesor
```

## Datos para probar

- Cédulas válidas: `1710034065`, `0912345675`
- Cédula inválida: `1234567890`
- Viernes: `2026-11-06` — Sábado: `2026-11-07`
