# Sistema de Gestión de Marcaciones de Empleados
Este proyecto consiste en un sistema de gestión de asistencia de empleados (SIGESAT) creado en C++. Permite registrar empleados, gestionar sus asistencias (marcaciones), y generar reportes relacionados con la asistencia, ausencias, permisos y horas extra. Utiliza archivos binarios para almacenar la información de empleados, marcaciones y reportes.


## Puntos Importantes
###1. Clases principales
- Empleado: Representa a un empleado con atributos como código, nombre, DUI, departamento, cargo y estado (activo/inactivo). Incluye métodos estáticos para cargar y guardar empleados desde/para un archivo binario (empleados.dat).

- Marcacion: Representa una marcación de asistencia, con atributos como código de empleado, fecha, hora de entrada/salida, horas extra, permiso, motivo y observaciones. También tiene métodos para cargar y guardar marcaciones (marcaciones.dat).

- Reporte: Permite almacenar información de reportes generados, aunque en el código actual solo se usa para guardar/cargar reportes (reportes.dat).

- SistemaGestion: Es la clase principal que gestiona la lógica del sistema. Contiene vectores de empleados, marcaciones y reportes, y métodos para todas las operaciones del sistema (agregar/editar/desactivar/listar empleados, registrar/editar/listar marcaciones, y generar reportes).

###2. Menús
### El sistema tiene menús para:

- Gestión de empleados (agregar, editar, desactivar, listar)
- Registro de marcaciones (registrar, editar, listar)
- Reportes (asistencia, horas trabajadas, ausencias, permisos, horas extra)

3. Persistencia de datos
Toda la información se guarda en archivos binarios (empleados.dat, marcaciones.dat, reportes.dat). Cada vez que se realiza una operación de alta, edición o eliminación lógica, se actualizan los archivos correspondientes.

4. Validaciones
Al agregar empleados, se valida que el código y el DUI no estén repetidos.
Al registrar marcaciones, se valida que el empleado exista y esté activo, que la fecha y hora tengan el formato correcto, y que no exista ya una marcación para ese empleado y fecha.
Al editar o desactivar empleados/marcaciones, se verifica que existan y estén activos.

6. Reportes
El sistema puede generar varios reportes:

- Asistencia por rango de fechas.
- Horas trabajadas por empleado.
- Empleados con ausencias en una fecha.
- Permisos solicitados.
- Horas extra realizadas en un rango de fechas.
  
6. Interfaz
La interfaz es por consola, con menús y tablas formateadas usando iomanip para facilitar la lectura.




8. Compatibilidad
- Incluye windows.h y usa SetConsoleOutputCP(CP_UTF8); para soportar caracteres UTF-8 en la consola de Windows.
