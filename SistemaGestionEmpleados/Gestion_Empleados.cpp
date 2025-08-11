#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>                                                     // Para mostrar los datos en formato de tabla
#include <windows.h>                                                   // Para caracteres UTF-8 en Windows
#include <cstring>

using namespace std;

//Se crea una clase Empleado para manejar los datos de los empleados
class Empleado {
public:
//Se definen los atributos de la clase Empleado
    char codigo[10];
    char nombre[50];
    char dui[12];
    char departamento[30];
    char cargo[30];
    bool estado;

    // Constructor por defecto que inicializa los atributos a cero
    Empleado() { memset(this, 0, sizeof(Empleado)); }

    // Métodos estáticos para cargar y guardar empleados desde/para un archivo binario
    static vector<Empleado> cargarEmpleados() {
        vector<Empleado> empleados;
        ifstream archivo("empleados.dat", ios::binary);
        Empleado emp;
        while (archivo.read((char*)&emp, sizeof(Empleado))) {
            empleados.push_back(emp);
        }
        return empleados;
    }
    // Método estático para guardar empleados en un archivo binario
    static void guardarEmpleados(const vector<Empleado>& empleados) {
        ofstream archivo("empleados.dat", ios::binary | ios::trunc);
        for (const auto& emp : empleados) {
            archivo.write((char*)&emp, sizeof(Empleado));
        }
    }
};

// Se crea una clase Marcacion para manejar los datos de las marcaciones de asistencia
class Marcacion {
public:
    // Se definen los atributos de la clase Marcacion
    char codigoEmpleado[10];
    char fecha[11];
    char horaEntrada[6];
    char horaSalida[6];
    double horasExtra;
    bool permiso;
    char motivoPermiso[50];
    char observaciones[100];

    // Constructor por defecto que inicializa los atributos a cero
    Marcacion() { memset(this, 0, sizeof(Marcacion)); }

    // Métodos estáticos para cargar y guardar marcaciones desde/para un archivo binario
    static vector<Marcacion> cargarMarcaciones() {
        vector<Marcacion> marcaciones;
        ifstream archivo("marcaciones.dat", ios::binary);
        Marcacion marc;
        while (archivo.read((char*)&marc, sizeof(Marcacion))) {
            marcaciones.push_back(marc);
        }
        return marcaciones;
    }

    // Método estático para guardar marcaciones en un archivo binario
    static void guardarMarcaciones(const vector<Marcacion>& marcaciones) {
        ofstream archivo("marcaciones.dat", ios::binary | ios::trunc);
        for (const auto& marc : marcaciones) {
            archivo.write((char*)&marc, sizeof(Marcacion));
        }
    }
};

// Se crea una clase Reporte para manejar los reportes generados por el sistema
class Reporte {
public:
    // Se definen los atributos de la clase Reporte
    char tipo[30];           
    char fechaGeneracion[20];
    char descripcion[200];   

    // Constructor por defecto que inicializa los atributos a cero
    Reporte() { memset(this, 0, sizeof(Reporte)); }

    // Método estático para cargar reportes desde un archivo binario
    static vector<Reporte> cargarReportes() {
        vector<Reporte> reportes;
        ifstream archivo("reportes.dat", ios::binary);
        Reporte rep;
        while (archivo.read((char*)&rep, sizeof(Reporte))) {
            reportes.push_back(rep);
        }
        return reportes;
    }

    // Método estático para guardar reportes en un archivo binario
    static void guardarReportes(const vector<Reporte>& reportes) {
        ofstream archivo("reportes.dat", ios::binary | ios::trunc);
        for (const auto& rep : reportes) {
            archivo.write((char*)&rep, sizeof(Reporte));
        }
    }
};

// Se crea una clase de tipo publica de SistemaGestion para manejar la lógica del sistema de gestión de asistencia
class SistemaGestion {
public:
    // Se definen los vectores para almacenar empleados y marcaciones
    vector<Empleado> empleados;
    vector<Marcacion> marcaciones;
    vector<Reporte> reportes;

    // Constructor que carga los empleados y marcaciones desde los archivos al iniciar el sistema
    SistemaGestion() {
        empleados = Empleado::cargarEmpleados();
        marcaciones = Marcacion::cargarMarcaciones();
        reportes = Reporte::cargarReportes();
    }

    // Método para guardar los datos de empleados y marcaciones al finalizar el sistema
    void guardarDatos() {
        Empleado::guardarEmpleados(empleados);
        Marcacion::guardarMarcaciones(marcaciones);
        Reporte::guardarReportes(reportes);
    }

    // Métodos para agregar, editar, desactivar y listar empleados
    void agregarEmpleado() {
        Empleado nuevo;
        cout << "\n--- NUEVO EMPLEADO ---\n";
        cout << "Código: "; cin >> nuevo.codigo;
        cin.ignore();
        cout << "Nombre completo: "; cin.getline(nuevo.nombre, 50);
        cout << "DUI: "; cin >> nuevo.dui; cin.ignore();
        cout << "Departamento: "; cin.getline(nuevo.departamento, 30);
        cout << "Cargo: "; cin.getline(nuevo.cargo, 30);
        cout << "Estado (1=activo, 0=inactivo): "; cin >> nuevo.estado; cin.ignore();

        // Validación de datos
        for (const auto& emp : empleados) {
            if (strcmp(emp.codigo, nuevo.codigo) == 0) {
                cout << "El código de empleado ya existe.\n";
                return;
            }
            if (strcmp(emp.dui, nuevo.dui) == 0) {
                cout << "El DUI ya existe.\n";
                return;
            }
        }
        empleados.push_back(nuevo);
        Empleado::guardarEmpleados(empleados);
        cout << "Empleado registrado con éxito!.\n";
    }

    // Método para editar un empleado existente
    void editarEmpleado() {
        cout << "\n--- EDITAR EMPLEADO ---\n";
        char codigo[10];
        cout << "Ingrese el código del empleado a editar: ";
        cin >> codigo;
        bool encontrado = false;

        //Ciclo for para búsqueda del empleado por código
        for (auto& emp : empleados) {
            if (strcmp(emp.codigo, codigo) == 0 && emp.estado) {
                cout << "Nuevo nombre: "; cin.ignore(); cin.getline(emp.nombre, 50);
                cout << "Nuevo DUI: "; cin >> emp.dui; cin.ignore();
                cout << "Nuevo departamento: "; cin.getline(emp.departamento, 30);
                cout << "Nuevo cargo: "; cin.getline(emp.cargo, 30);
                encontrado = true;
                break;
            }
        }
        // Si se encuentra el empleado, se actualizan los datos y se guarda
        if (encontrado) {
            Empleado::guardarEmpleados(empleados);
            cout << "Empleado actualizado.\n";
        } else {
            cout << "Empleado no encontrado o inactivo.\n";
        }
    }

    // Método para desactivar un empleado (por medio de eliminación lógica)
    void desactivarEmpleado() {
        cout << "\n--- DESACTIVAR EMPLEADO ---\n";
        char codigo[10];
        cout << "Ingrese el código del empleado a desactivar: ";
        cin >> codigo;
        bool encontrado = false;
        for (auto& emp : empleados) {
            if (strcmp(emp.codigo, codigo) == 0 && emp.estado) {
                emp.estado = false;
                encontrado = true;
                break;
            }
        }
        // Si se encuentra el empleado, se cambia su estado a inactivo y se guarda
        if (encontrado) {
            Empleado::guardarEmpleados(empleados);
            cout << "Empleado desactivado (eliminación lógica).\n";
        } else {
            cout << "Empleado no encontrado o ya inactivo.\n";
        }
    }

    // Método para listar todos los empleados activos e inactivos
    void listarEmpleados() {
        cout << "\n--- LISTA DE EMPLEADOS ---\n";
        cout << setfill('-') << setw(140) << "-" << setfill(' ') << endl;
        cout << left << setw(12) << "Código"
             << setw(40) << "Nombre"
             << setw(16) << "DUI"
             << setw(22) << "Depto."
             << setw(32) << "Cargo"
             << setw(12) << "Estado" << endl;
        cout << setfill('-') << setw(140) << "-" << setfill(' ') << endl;

        // Ciclo for para recorrer el vector de empleados
        for (const auto& emp : empleados) {
            cout << left << setw(12) << emp.codigo
                 << setw(40) << emp.nombre
                 << setw(16) << emp.dui
                 << setw(22) << emp.departamento
                 << setw(32) << emp.cargo
                 << setw(12) << (emp.estado ? "Activo" : "Inactivo") << endl;
        }
        cout << setfill('-') << setw(140) << "-" << setfill(' ') << endl;
    }

    // Métodos para registrar, editar y listar marcaciones
    void registrarMarcacion() {
        Marcacion nueva;
        cout << "\n--- NUEVA MARCACIÓN ---\n";
        cout << "Código de empleado: "; cin >> nueva.codigoEmpleado;
        bool existe = false;

        //Ciclo for para verificar si el empleado existe y está activo
        for (const auto& emp : empleados) {
            if (strcmp(emp.codigo, nueva.codigoEmpleado) == 0 && emp.estado) {
                existe = true;
                break;
            }
        }
        if (!existe) {
            cout << "El empleado no existe o está inactivo.\n";
            return;
        }
        cout << "Fecha (DD/MM/AAAA): "; cin >> nueva.fecha;

        //Ciclo for para verificar si ya existe una marcación para el empleado en esa fecha
        for (const auto& marc : marcaciones) {
            if (strcmp(marc.codigoEmpleado, nueva.codigoEmpleado) == 0 && strcmp(marc.fecha, nueva.fecha) == 0) {
                cout << "Ya existe una marcación para este empleado en esa fecha.\n";
                return;
            }
        }
        // Validación del formato de fecha y hora
        if (strlen(nueva.fecha) != 10 || nueva.fecha[2] != '/' || nueva.fecha[5] != '/') {
            cout << "Formato de fecha incorrecto. Debe ser DD/MM/AAAA.\n";
            return;
        }
        cout << "Hora de entrada (HH:MM): "; cin >> nueva.horaEntrada;
        if (strlen(nueva.horaEntrada) != 5 || nueva.horaEntrada[2] != ':') {
            cout << "Formato de hora incorrecto. Debe ser HH:MM.\n";
            return;
        }
        cout << "Hora de salida (HH:MM): "; cin >> nueva.horaSalida;
        if (strlen(nueva.horaSalida) != 5 || nueva.horaSalida[2] != ':') {
            cout << "Formato de hora incorrecto. Debe ser HH:MM.\n";
            return;
        }
        if (strcmp(nueva.horaEntrada, nueva.horaSalida) >= 0) {
            cout << "La hora de entrada debe ser menor que la hora de salida.\n";
            return;
        }
        cout << "Horas extra realizadas: "; cin >> nueva.horasExtra;
        cout << "Permiso (1=si, 0=no): "; cin >> nueva.permiso; cin.ignore();
        if (nueva.permiso) {
            cout << "Motivo del permiso: "; cin.getline(nueva.motivoPermiso, 50);
        } else {
            strcpy(nueva.motivoPermiso, "N/A");
        }
        // Se solicita una observación opcional
        cout << "Observaciones: "; cin.getline(nueva.observaciones, 100);
        marcaciones.push_back(nueva);
        Marcacion::guardarMarcaciones(marcaciones);
        cout << "Marcación registrada!\n";
    }

    // Método para editar una marcación existente
    void editarMarcacion() {
        cout << "\n--- EDITAR MARCACIÓN ---\n";
        char codigoEmpleado[10], fecha[11];
        cout << "Código del empleado: "; cin >> codigoEmpleado;
        cout << "Fecha de la marcación (DD/MM/AAAA): "; cin >> fecha;
        bool encontrada = false;

        // Ciclo for para buscar la marcación por código de empleado y fecha
        for (auto& marc : marcaciones) {
            if (strcmp(marc.codigoEmpleado, codigoEmpleado) == 0 && strcmp(marc.fecha, fecha) == 0) {
                cout << "Nueva hora de entrada (HH:MM): "; cin >> marc.horaEntrada;
                cout << "Nueva hora de salida (HH:MM): "; cin >> marc.horaSalida;
                cout << "Horas extra: "; cin >> marc.horasExtra;
                cout << "Permiso (1=si, 0=no): "; cin >> marc.permiso; cin.ignore();
                if (marc.permiso) {
                    cout << "Motivo del permiso: "; cin.getline(marc.motivoPermiso, 50);
                } else {
                    strcpy(marc.motivoPermiso, "N/A");
                }
                cout << "Observaciones: "; cin.getline(marc.observaciones, 100);
                encontrada = true;
                break;
            }
        }
        // Si se encuentra la marcación, se actualizan los datos y se guarda
        if (encontrada) {
            Marcacion::guardarMarcaciones(marcaciones);
            cout << "Marcación actualizada con éxito!.\n";
        } else {
            cout << "Marcación no encontrada.\n";
        }
    }

    // Método para listar todas las marcaciones registradas
    void listarMarcaciones() {
        cout << "\n--- LISTADO DE MARCACIONES ---\n";
        cout << setfill('-') << setw(140) << "-" << setfill(' ') << endl;
        cout << left << setw(10) << "Empleado" << setw(14) << "Fecha" << setw(10) << "Entrada"
             << setw(10) << "Salida" << setw(10) << "Extra" << setw(10) << "Permiso"
             << setw(35) << "Motivo" << setw(25) << "Observaciones" << endl;
        cout << setfill('-') << setw(140) << "-" << setfill(' ') << endl;
        for (const auto& marc : marcaciones) {
            cout << left << setw(10) << marc.codigoEmpleado << setw(14) << marc.fecha
                 << setw(10) << marc.horaEntrada << setw(10) << marc.horaSalida
                 << setw(10) << marc.horasExtra << setw(10) << (marc.permiso ? "Si" : "No")
                 << setw(35) << marc.motivoPermiso << setw(25) << marc.observaciones << endl;
        }
        cout << setfill('-') << setw(140) << "-" << setfill(' ') << endl;
    }

    // Método para generar reportes de asistencia, horas trabajadas, ausencias, permisos y horas extra
    void generarReporteAsistencia() {
        // Genera un reporte de asistencia por rango de fechas
        cout << "\n--- REPORTE DE ASISTENCIA ---\n";
        vector<Marcacion> marcaciones;
        vector<Empleado> empleados;
        marcaciones = Marcacion::cargarMarcaciones();
        empleados = Empleado::cargarEmpleados();
        string fechaInicio, fechaFin;
        cout << "Ingrese el rango de fechas:\n";
        cout << "Fecha inicial (DD/MM/AAAA): "; cin >> fechaInicio;
        cout << "Fecha final (DD/MM/AAAA): "; cin >> fechaFin;
        cout << "\n--- REPORTE DE ASISTENCIA ---\n";
        cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;
        cout << left << setw(14) << "Código"
            << setw(40) << "Nombre"
            << setw(20) << "Fecha"
            << setw(18) << "Entrada"
            << setw(18) << "Salida" << endl;
        cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;

        // Ciclo for para recorrer las marcaciones y filtrar por fecha
        for (const auto& marc : marcaciones) {
            if (string(marc.fecha) >= fechaInicio && string(marc.fecha) <= fechaFin) {
                // Buscar el nombre del empleado
                string nombre = "";
                for (const auto& emp : empleados) {
                    if (strcmp(emp.codigo, marc.codigoEmpleado) == 0) {
                        nombre = emp.nombre;
                        break;
                    }
                }
                cout << left << setw(14) << marc.codigoEmpleado
                    << setw(40) << nombre
                    << setw(20) << marc.fecha
                    << setw(18) << marc.horaEntrada
                    << setw(18) << marc.horaSalida << endl;
            }
        }
        cout << setfill('-') << setw(110) << "-" << setfill(' ') << endl;
    }

    // Genera un reporte de horas trabajadas por empleado
    void generarReporteHorasTrabajadas() {
        cout << "\n--- REPORTE DE HORAS TRABAJADAS ---\n";
        vector<Marcacion> marcaciones = Marcacion::cargarMarcaciones();
        vector<Empleado> empleados = Empleado::cargarEmpleados();
        vector<string> codigos;
        string codigo;
        char opcion;
        // Solicita los códigos de los empleados para generar el reporte
        do {
            cout << "Ingrese el código del empleado: ";
            cin >> codigo;
            codigos.push_back(codigo);
            cout << "¿Desea ingresar otro código? (s/n): ";
            cin >> opcion;
        } while (opcion == 's' || opcion == 'S');

        cout << "\n--- REPORTE DE HORAS TRABAJADAS ---\n";
        cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
        cout << left << setw(18) << "Código"
            << setw(35) << "Nombre"
            << setw(15) << "Total"
            << setw(16) << "Normales"
            << setw(16) << "Extras" << endl;
        cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;

        // Ciclo for para recorrer los códigos ingresados
        for (const auto& cod : codigos) {
            double totalNormales = 0, totalExtras = 0;
            string nombre = "";

            // Buscar el nombre del empleado por código
            for (const auto& emp : empleados) {
                if (cod == emp.codigo) {
                    nombre = emp.nombre;
                    break;
                }
            }
            // Ciclo for para Calcular las horas normales y extras
            for (const auto& marc : marcaciones) {
                if (cod == marc.codigoEmpleado) {
                    totalNormales += 8;
                    totalExtras += marc.horasExtra;
                }
            }
            double total = totalNormales + totalExtras;

            cout << left << setw(18) << cod
                << setw(35) << nombre
                << setw(15) << total
                << setw(16) << totalNormales
                << setw(16) << totalExtras << endl;
        }
        cout << setfill('-') << setw(100) << "-" << setfill(' ') << endl;
    }

    // Genera un reporte de ausencias
    void generarReporteAusencias() {
        // Solicita la fecha a consultar
        cout << "\n--- REPORTE DE AUSENCIAS ---\n";
        // Carga los empleados y marcaciones desde el archivo
        vector<Empleado> empleados = Empleado::cargarEmpleados();
        vector<Marcacion> marcaciones = Marcacion::cargarMarcaciones();
        string fecha;
        cout << "Fecha a consultar (DD/MM/AAAA): "; cin >> fecha;
        cout << "\n--- LISTADO DE EMPLEADOS CON AUSENCIAS ---\n";

        // Cabecera de la tabla
        cout << setfill('-') << setw(160) << "-" << setfill(' ') << endl;
        cout << left << setw(16) << "Código"
            << setw(35) << "Nombre"
            << setw(28) << "Departamento"
            << setw(35) << "Cargo"
            << setw(16) << "Fecha"
            << setw(30) << "Motivo" << endl;
        cout << setfill('-') << setw(160) << "-" << setfill(' ') << endl;

        // Ciclo for para recorrer el vector de empleados
        for (const auto& emp : empleados) {
            if (!emp.estado) continue;
            bool asistio = false;
            string motivo = "Ausencia";
            for (const auto& marc : marcaciones) {
                if (string(marc.codigoEmpleado) == emp.codigo && string(marc.fecha) == fecha) {
                    asistio = true;
                    if (marc.permiso) {
                        motivo = marc.motivoPermiso;
                    } else {
                        motivo = "Asistió";
                    }
                    break;
                }
            }
            if (!asistio) {
                motivo = "Ausencia";
            }
            if (!asistio || motivo != "Asistió") {
                cout << left << setw(16) << emp.codigo
                    << setw(35) << emp.nombre
                    << setw(28) << emp.departamento
                    << setw(35) << emp.cargo
                    << setw(16) << fecha
                    << setw(30) << motivo << endl;
            }
        }
        cout << setfill('-') << setw(160) << "-" << setfill(' ') << endl;
    }

    // Genera un reporte de permisos solicitados
    void generarReportePermisos() {
        // Solicita la fecha a consultar
        cout << "\n--- REPORTE DE PERMISOS ---\n";
        vector<Marcacion> marcaciones = Marcacion::cargarMarcaciones();
        vector<Empleado> empleados = Empleado::cargarEmpleados();

        // Cabecera de la tabla
        cout << "\n--- LISTADO DE PERMISOS SOLICITADOS ---\n";
        cout << setfill('-') << setw(150) << "-" << setfill(' ') << endl;
        cout << left << setw(14) << "Código"
            << setw(32) << "Nombre"
            << setw(28) << "Departamento"
            << setw(28) << "Cargo"
            << setw(32) << "Motivo"
            << setw(16) << "Fecha" << endl;
        cout << setfill('-') << setw(150) << "-" << setfill(' ') << endl;

        for (const auto& marc : marcaciones) {
            if (marc.permiso) {

                // Buscar el nombre, departamento y cargo del empleado
                string nombre = "", departamento = "", cargo = "";
                for (const auto& emp : empleados) {
                    if (strcmp(emp.codigo, marc.codigoEmpleado) == 0) {
                        nombre = emp.nombre;
                        departamento = emp.departamento;
                        cargo = emp.cargo;
                        break;
                    }
                }
                cout << left << setw(14) << marc.codigoEmpleado
                    << setw(32) << nombre
                    << setw(28) << departamento
                    << setw(28) << cargo
                    << setw(32) << marc.motivoPermiso
                    << setw(16) << marc.fecha << endl;
            }
        }
        cout << setfill('-') << setw(150) << "-" << setfill(' ') << endl;
    }

    // Genera un reporte de horas extra
    void generarReporteHorasExtra() {
        cout << "\n--- REPORTE DE HORAS EXTRA ---\n";
        vector<Marcacion> marcaciones = Marcacion::cargarMarcaciones();
        vector<Empleado> empleados = Empleado::cargarEmpleados();
        string fechaInicio, fechaFin;
        cout << "Ingrese el rango de fechas:\n";
        cout << "Fecha inicial (DD/MM/AAAA): "; cin >> fechaInicio;
        cout << "Fecha final (DD/MM/AAAA): "; cin >> fechaFin;
        cout << setfill('-') << setw(140) << "-" << setfill(' ') << endl;
        cout << "\n--- REPORTE DE HORAS EXTRA ---\n";
        cout << setfill('-') << setw(140) << "-" << setfill(' ') << endl;
        cout << left << setw(14) << "Código"
            << setw(32) << "Nombre"
            << setw(28) << "Departamento"
            << setw(28) << "Cargo"
            << setw(18) << "Fecha"
            << setw(16) << "Horas Extra" << endl;
        cout << setfill('-') << setw(140) << "-" << setfill(' ') << endl;

        // Ciclo for para recorrer las marcaciones y filtrar por fecha y horas extra
        for (const auto& marc : marcaciones) {
            if (string(marc.fecha) >= fechaInicio && string(marc.fecha) <= fechaFin && marc.horasExtra > 0) {
                string nombre = "", departamento = "", cargo = "";
                for (const auto& emp : empleados) {
                    if (strcmp(emp.codigo, marc.codigoEmpleado) == 0) {
                        nombre = emp.nombre;
                        departamento = emp.departamento;
                        cargo = emp.cargo;
                        break;
                    }
                }
                cout << left << setw(14) << marc.codigoEmpleado
                    << setw(32) << nombre
                    << setw(28) << departamento
                    << setw(28) << cargo
                    << setw(18) << marc.fecha
                    << setw(16) << marc.horasExtra << endl;
            }
        }
        cout << setfill('-') << setw(140) << "-" << setfill(' ') << endl;
    }
    // Menús para gestionar empleados, marcaciones y reportes
    void menuGestionEmpleados() {
        int opcion;
        do {
            cout << "\n--- GESTIÓN DE EMPLEADOS ---\n";
            cout << "1. Agregar Empleado\n";
            cout << "2. Editar Empleado\n";
            cout << "3. Desactivar Empleado\n";
            cout << "4. Listar Empleados\n";
            cout << "5. Volver al menu principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;

            // Ciclo switch para manejar las opciones del menú
            switch(opcion) {
                case 1: agregarEmpleado(); break;
                case 2: editarEmpleado(); break;
                case 3: desactivarEmpleado(); break;
                case 4: listarEmpleados(); break;
                case 5: break;
                default: cout << "Opción no válida!\n";
            }
        } while(opcion != 5);
    }

    // Método para mostrar el menú de marcaciones
    void menuMarcaciones() {
        int opcion;
        do {
            cout << "\n--- REGISTRO DE MARCACIONES ---\n";
            cout << "1. Registrar Marcacion\n";
            cout << "2. Editar Marcacion\n";
            cout << "3. Listar Marcaciones\n";
            cout << "4. Volver al menu principal\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;
            switch(opcion) {
                case 1: registrarMarcacion(); break;
                case 2: editarMarcacion(); break;
                case 3: listarMarcaciones(); break;
                case 4: break;
                default: cout << "Opción no válida!\n";
            }
        } while(opcion != 4);
    }

    // Método para mostrar el menú de reportes
    void menuReportes() {
    int opcion;
    // Ciclo do-while para mostrar el menú hasta que el usuario seleccione salir
    do {
        cout << "\n--- REPORTES ---\n";
        cout << "1. Asistencia por rango de fechas\n";
        cout << "2. Horas trabajadas por empleado\n";
        cout << "3. Empleados con ausencias\n";
        cout << "4. Listado de permisos solicitados\n";
        cout << "5. Resumen de horas extra\n";
        cout << "6. Volver al menú principal\n";
        cout << "Seleccione una opción: ";
        cin >> opcion;

        // Ciclo switch para manejar las opciones del menú
        switch(opcion) {
            case 1: generarReporteAsistencia(); break;
            case 2: generarReporteHorasTrabajadas(); break;
            case 3: generarReporteAusencias(); break;
            case 4: generarReportePermisos(); break;
            case 5: generarReporteHorasExtra(); break;
            case 6: break;
            default: cout << "Opción no válida!\n";
        }
    } while(opcion != 6);
 }
};
    // Función principal que inicia el sistema de gestión
    int main() {
        SetConsoleOutputCP(CP_UTF8); 
        SistemaGestion sistema; 
        int opcion;

        // Ciclo do-while para mostrar el menú principal hasta que el usuario seleccione salir
        do {
            cout << "\n--- SISTEMA DE GESTIÓN DE ASISTENCIA DE EMPLEADOS (SIGESAT) ---\n";
            cout << "1. Gestión de Empleados\n";
            cout << "2. Registro de Marcaciones\n";
            cout << "3. Reportes\n";
            cout << "4. Salir\n";
            cout << "Seleccione una opción: ";
            cin >> opcion;
            switch(opcion) {
                case 1: sistema.menuGestionEmpleados(); break;
                case 2: sistema.menuMarcaciones(); break;
                case 3: sistema.menuReportes(); break; 
                case 4: cout << "Saliendo del sistema...\n"; break;
                default: cout << "Opción no válida!\n";
            }
        } while(opcion != 4);
        return 0;   // Fin del programa
}