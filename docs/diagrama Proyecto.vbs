' =====================================================================
'  Diagrama de clases - Sistema de Registro de Profesores
'  Ejecutar en PowerDesigner:  Tools > Execute Commands > Edit/Run Script
'  (o Ctrl+Shift+X), pegar este codigo y presionar Run (F5).
' =====================================================================
Option Explicit

' Si al ejecutar ves los rombos de composicion del lado equivocado
' (en la parte en vez del todo), cambia esto a True y vuelve a ejecutar.
Const INVERTIR = False

Dim mdl, diag
Set mdl = CreateModel(PdOOM.cls_Model, "|Language=Analysis|Diagram=ClassDiagram")
mdl.Name = "SistemaRegistro"
mdl.Code = "SistemaRegistro"
Set diag = mdl.DefaultDiagram

' ---------------------------------------------------------------------
' Funciones auxiliares
' ---------------------------------------------------------------------

' Crea una clase con su nombre
Function Clase(nombre)
   Dim c
   Set c = mdl.Classes.CreateNew()
   c.Name = nombre
   c.Code = nombre
   Set Clase = c
End Function

' Crea un atributo. vis: "+" publico, "-" privado. Si termina en "$" es estatico
Sub Atr(c, vis, tipo, nombre, inicial)
   Dim a
   Set a = c.Attributes.CreateNew()
   a.Name = nombre
   a.Code = nombre
   a.DataType = tipo
   a.Visibility = Left(vis, 1)
   If Right(vis, 1) = "$" Then a.Static = True
   If inicial <> "" Then a.InitialValue = inicial
End Sub

' Crea un metodo. ret = "" para constructores/destructor.
' params: "string ced, int fr, string mat"
Dim contador
contador = 0

Sub Op(c, vis, ret, nombre, params)
   Dim o
   contador = contador + 1
   Set o = c.Operations.CreateNew()
   ' Nombre temporal unico; el real se pone despues de los parametros
   o.Name = "tmp_op_" & contador
   o.Code = "tmp_op_" & contador
   o.ReturnType = ret
   o.Visibility = Left(vis, 1)
   If Right(vis, 1) = "$" Then o.Static = True
   AgregarParams o, params
   PonerNombre o, nombre
End Sub

' Pone el nombre al metodo; si ya existe (sobrecarga) agrega _2, _3...
Sub PonerNombre(o, nombre)
   Dim n
   On Error Resume Next
   n = 1
   Do
      Err.Clear
      If n = 1 Then o.Name = nombre Else o.Name = nombre & "_" & n
      If Err.Number = 0 Then Exit Do
      n = n + 1
   Loop While n < 20
   n = 1
   Do
      Err.Clear
      If n = 1 Then o.Code = nombre Else o.Code = nombre & "_" & n
      If Err.Number = 0 Then Exit Do
      n = n + 1
   Loop While n < 20
   Err.Clear
   On Error GoTo 0
End Sub

' Separa la lista de parametros y los agrega al metodo
Sub AgregarParams(o, lista)
   Dim partes, i, txt, pos, p
   If Trim(lista) = "" Then Exit Sub
   partes = Split(lista, ",")
   For i = 0 To UBound(partes)
      txt = Trim(partes(i))
      pos = InStrRev(txt, " ")
      Set p = o.Parameters.CreateNew()
      p.Name = Mid(txt, pos + 1)
      p.Code = p.Name
      p.DataType = Trim(Left(txt, pos - 1))
   Next
End Sub

' Asigna los extremos de una relacion
Sub Extremos(lnk, obj1, obj2)
   On Error Resume Next
   Set lnk.Object1 = obj1
   If Err.Number <> 0 Then
      Err.Clear
      lnk.Object1 = obj1
   End If
   Set lnk.Object2 = obj2
   If Err.Number <> 0 Then
      Err.Clear
      lnk.Object2 = obj2
   End If
   On Error GoTo 0
End Sub

' Composicion: "todo" contiene a "parte" con multiplicidad mult
Sub Compone(todo, parte, mult)
   Dim a
   Set a = mdl.Associations.CreateNew()
   If Not INVERTIR Then
      Extremos a, todo, parte
      a.RoleAIndicator = "C"
      a.RoleAMultiplicity = "1"
      a.RoleBMultiplicity = mult
   Else
      Extremos a, parte, todo
      a.RoleBIndicator = "C"
      a.RoleBMultiplicity = "1"
      a.RoleAMultiplicity = mult
   End If
End Sub

' Dependencia "usa": cliente depende de proveedor
Sub Usa(cliente, proveedor)
   Dim d
   Set d = mdl.Dependencies.CreateNew()
   Extremos d, cliente, proveedor
   d.Name = "usa"
   d.Code = "usa"
   d.Stereotype = "usa"
End Sub

' ---------------------------------------------------------------------
' Clases
' ---------------------------------------------------------------------
Dim cMenu, cSis, cLD, cND, cLS, cNS, cProf, cReg, cFra, cHora, cVal

' ---- Menu ----
Set cMenu = Clase("Menu")
Atr cMenu, "-", "SistemaRegistro", "sistema", ""
Op  cMenu, "+", "void", "iniciar", ""

' ---- SistemaRegistro ----
Set cSis = Clase("SistemaRegistro")
Atr cSis, "-", "ListaDoble", "profesores", ""
Atr cSis, "-", "ListaSimple", "registros", ""
Op  cSis, "+", "ListaDoble", "getProfesores", ""
Op  cSis, "+", "ListaSimple", "getRegistros", ""
Op  cSis, "+", "bool", "registrarProfesor", "Profesor p"
Op  cSis, "+", "bool", "agregarClase", "string ced, int fr, string mat"
Op  cSis, "+", "bool", "eliminarProfesor", "string cedula"
Op  cSis, "+", "bool", "marcarEntrada", "string cedula, string fecha, Hora h"
Op  cSis, "+", "bool", "marcarSalida", "string cedula, string fecha, Hora h"
Op  cSis, "+", "void", "mostrarProfesores", ""
Op  cSis, "+", "void", "mostrarRegistros", ""

' ---- ListaDoble ----
Set cLD = Clase("ListaDoble")
Atr cLD, "-", "NodoDoble*", "cabeza", ""
Atr cLD, "-", "NodoDoble*", "cola", ""
Atr cLD, "-", "int", "tamanio", ""
Op  cLD, "+", "NodoDoble*", "getCabeza", ""
Op  cLD, "+", "NodoDoble*", "getCola", ""
Op  cLD, "+", "int", "getTamanio", ""
Op  cLD, "+", "void", "insertarFinal", "Profesor p"
Op  cLD, "+", "Profesor*", "buscar", "string cedula"
Op  cLD, "+", "bool", "eliminar", "string cedula"
Op  cLD, "+", "void", "mostrarAdelante", ""
Op  cLD, "+", "void", "mostrarAtras", ""
Op  cLD, "+", "bool", "estaVacia", ""

' ---- NodoDoble ----
Set cND = Clase("NodoDoble")
Atr cND, "-", "Profesor", "dato", ""
Atr cND, "-", "NodoDoble*", "siguiente", ""
Atr cND, "-", "NodoDoble*", "anterior", ""
Op  cND, "+", "", "NodoDoble", "Profesor p"
Op  cND, "+", "Profesor*", "getDato", ""
Op  cND, "+", "NodoDoble*", "getSiguiente", ""
Op  cND, "+", "NodoDoble*", "getAnterior", ""
Op  cND, "+", "void", "setDato", "Profesor p"
Op  cND, "+", "void", "setSiguiente", "NodoDoble* n"
Op  cND, "+", "void", "setAnterior", "NodoDoble* n"

' ---- ListaSimple ----
Set cLS = Clase("ListaSimple")
Atr cLS, "-", "NodoSimple*", "cabeza", ""
Atr cLS, "-", "int", "tamanio", ""
Op  cLS, "+", "NodoSimple*", "getCabeza", ""
Op  cLS, "+", "int", "getTamanio", ""
Op  cLS, "+", "void", "insertar", "Registro r"
Op  cLS, "+", "Registro*", "buscar", "string cedula, string fecha, int numFranja"
Op  cLS, "+", "void", "mostrar", ""
Op  cLS, "+", "void", "mostrarPorProfesor", "string cedula"
Op  cLS, "+", "bool", "estaVacia", ""

' ---- NodoSimple ----
Set cNS = Clase("NodoSimple")
Atr cNS, "-", "Registro", "dato", ""
Atr cNS, "-", "NodoSimple*", "siguiente", ""
Op  cNS, "+", "", "NodoSimple", "Registro r"
Op  cNS, "+", "Registro*", "getDato", ""
Op  cNS, "+", "NodoSimple*", "getSiguiente", ""
Op  cNS, "+", "void", "setDato", "Registro r"
Op  cNS, "+", "void", "setSiguiente", "NodoSimple* n"

' ---- Profesor ----
Set cProf = Clase("Profesor")
Atr cProf, "-", "int", "MAX_FRANJAS", "7"
Atr cProf, "-", "int", "CAPACIDAD_INICIAL", "2"
Atr cProf, "-", "string", "cedula", ""
Atr cProf, "-", "string", "nombre", ""
Atr cProf, "-", "string", "apellido", ""
Atr cProf, "-", "Franja*", "franjas", ""
Atr cProf, "-", "int", "numFranjas", ""
Atr cProf, "-", "int", "capacidad", ""
Op  cProf, "+", "", "Profesor", ""
Op  cProf, "+", "", "Profesor", "string ced, string nom, string ape"
Op  cProf, "+", "", "Profesor", "string ced, string nom, string ape, int fr, string mat"
Op  cProf, "+", "", "Profesor", "Profesor otro"
Op  cProf, "+", "Profesor", "operator=", "Profesor otro"
Op  cProf, "+", "", "~Profesor", ""
Op  cProf, "-", "void", "crecer", ""
Op  cProf, "+", "string", "getCedula", ""
Op  cProf, "+", "string", "getNombre", ""
Op  cProf, "+", "string", "getApellido", ""
Op  cProf, "+", "int", "getNumFranjas", ""
Op  cProf, "+", "int", "getCapacidad", ""
Op  cProf, "+", "Franja", "getFranja", "int indice"
Op  cProf, "+", "bool", "setCedula", "string ced"
Op  cProf, "+", "bool", "setNombre", "string nom"
Op  cProf, "+", "bool", "setApellido", "string ape"
Op  cProf, "+", "bool", "agregarFranja", "int numFranja, string materia"
Op  cProf, "+", "bool", "agregarFranja", "Franja f"
Op  cProf, "+", "bool", "quitarFranja", "int numFranja"
Op  cProf, "+", "bool", "tieneFranja", "int numFranja"
Op  cProf, "+", "int", "franjaParaEntrada", "Hora h"
Op  cProf, "+", "int", "franjaParaSalida", "Hora h"
Op  cProf, "+", "bool", "operator==", "Profesor otro"
Op  cProf, "+", "ostream", "operator<<", "ostream os, Profesor p"

' ---- Registro ----
Set cReg = Clase("Registro")
Atr cReg, "-", "string", "cedula", ""
Atr cReg, "-", "string", "fecha", ""
Atr cReg, "-", "int", "numFranja", ""
Atr cReg, "-", "Hora", "horaEntrada", ""
Atr cReg, "-", "Hora", "horaSalida", ""
Atr cReg, "-", "bool", "tieneEntrada", ""
Atr cReg, "-", "bool", "tieneSalida", ""
Op  cReg, "+", "", "Registro", ""
Op  cReg, "+", "", "Registro", "string cedula, string fecha, int numFranja"
Op  cReg, "+", "string", "getCedula", ""
Op  cReg, "+", "string", "getFecha", ""
Op  cReg, "+", "int", "getNumFranja", ""
Op  cReg, "+", "Hora", "getHoraEntrada", ""
Op  cReg, "+", "Hora", "getHoraSalida", ""
Op  cReg, "+", "bool", "getTieneEntrada", ""
Op  cReg, "+", "bool", "getTieneSalida", ""
Op  cReg, "+", "void", "setCedula", "string ced"
Op  cReg, "+", "void", "setFecha", "string fec"
Op  cReg, "+", "void", "setNumFranja", "int fr"
Op  cReg, "+", "void", "marcarEntrada", "Hora h"
Op  cReg, "+", "void", "marcarSalida", "Hora h"
Op  cReg, "+", "ostream", "operator<<", "ostream os, Registro r"

' ---- Franja ----
Set cFra = Clase("Franja")
Atr cFra, "-", "int", "numero", ""
Atr cFra, "-", "string", "materia", ""
Atr cFra, "-", "Hora", "inicio", ""
Atr cFra, "-", "Hora", "fin", ""
Op  cFra, "+", "", "Franja", ""
Op  cFra, "+", "", "Franja", "int numero"
Op  cFra, "+", "", "Franja", "int numero, string materia"
Op  cFra, "+", "int", "getNumero", ""
Op  cFra, "+", "string", "getMateria", ""
Op  cFra, "+", "Hora", "getInicio", ""
Op  cFra, "+", "Hora", "getFin", ""
Op  cFra, "+", "void", "setNumero", "int numero"
Op  cFra, "+", "bool", "setMateria", "string materia"
Op  cFra, "+", "bool", "puedeEntrar", "Hora h"
Op  cFra, "+", "bool", "puedeSalir", "Hora h"
Op  cFra, "+", "bool", "operator==", "Franja otra"
Op  cFra, "+", "ostream", "operator<<", "ostream os, Franja f"

' ---- Hora ----
Set cHora = Clase("Hora")
Atr cHora, "-", "int", "horas", ""
Atr cHora, "-", "int", "minutos", ""
Op  cHora, "+", "", "Hora", ""
Op  cHora, "+", "", "Hora", "int h, int m"
Op  cHora, "+", "", "Hora", "string texto"
Op  cHora, "+", "int", "getHoras", ""
Op  cHora, "+", "int", "getMinutos", ""
Op  cHora, "+", "void", "setHoras", "int h"
Op  cHora, "+", "void", "setMinutos", "int m"
Op  cHora, "+", "int", "enMinutos", ""
Op  cHora, "+$", "bool", "esValida", "string texto"
Op  cHora, "+", "Hora", "operator+", "int mins"
Op  cHora, "+", "Hora", "operator-", "int mins"
Op  cHora, "+", "bool", "operator<", "Hora otra"
Op  cHora, "+", "bool", "operator>", "Hora otra"
Op  cHora, "+", "bool", "operator<=", "Hora otra"
Op  cHora, "+", "bool", "operator>=", "Hora otra"
Op  cHora, "+", "bool", "operator==", "Hora otra"
Op  cHora, "+", "ostream", "operator<<", "ostream os, Hora h"

' ---- Validacion (todo estatico) ----
Set cVal = Clase("Validacion")
Op  cVal, "-$", "bool", "esLetra", "char c"
Op  cVal, "-$", "bool", "esDigito", "char c"
Op  cVal, "-$", "int", "diasDelMes", "int mes, int anio"
Op  cVal, "-$", "bool", "esBisiesto", "int anio"
Op  cVal, "+$", "bool", "esCedula", "string ced"
Op  cVal, "+$", "bool", "esNombre", "string nom"
Op  cVal, "+$", "bool", "esMateria", "string mat"
Op  cVal, "+$", "bool", "esFecha", "string fecha"
Op  cVal, "+$", "int", "diaDeLaSemana", "string fecha"
Op  cVal, "+$", "string", "nombreDia", "string fecha"
Op  cVal, "+$", "bool", "esDiaLaborable", "string fecha"
Op  cVal, "+$", "bool", "esHora", "string hora"
Op  cVal, "+$", "bool", "esEntero", "string texto"
Op  cVal, "+$", "bool", "esEnteroEnRango", "string texto, int min, int max"
Op  cVal, "+$", "string", "leerTexto", "string mensaje"
Op  cVal, "+$", "string", "leerCedula", "string mensaje"
Op  cVal, "+$", "string", "leerNombre", "string mensaje"
Op  cVal, "+$", "string", "leerMateria", "string mensaje"
Op  cVal, "+$", "string", "leerFecha", "string mensaje"
Op  cVal, "+$", "Hora", "leerHora", "string mensaje"
Op  cVal, "+$", "int", "leerEntero", "string mensaje, int min, int max"

' ---------------------------------------------------------------------
' Relaciones
' ---------------------------------------------------------------------
Compone cMenu, cSis,  "1"
Compone cSis,  cLD,   "1"
Compone cSis,  cLS,   "1"
Compone cLD,   cND,   "0..*"
Compone cND,   cProf, "1"
Compone cLS,   cNS,   "0..*"
Compone cNS,   cReg,  "1"
Compone cProf, cFra,  "0..7"
Compone cReg,  cHora, "2"
Compone cFra,  cHora, "2"

Usa cMenu, cVal
Usa cProf, cVal
Usa cFra,  cVal

' ---------------------------------------------------------------------
' Dibujar en el diagrama
' ---------------------------------------------------------------------
Dim c
For Each c In mdl.Classes
   diag.AttachObject c
Next
diag.CompleteLinks

Output "Listo: " & mdl.Classes.Count & " clases creadas. Usa Symbol > Auto-Layout para ordenarlas."
