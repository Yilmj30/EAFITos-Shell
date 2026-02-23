# EAFITos – Shell Educativa en C

*Materia:* Sistemas Operativos  
*Reto 1 – Shell EAFITos*  
*Fecha de entrega:* 23/02/2026  

---

## Integrantes

- *Fabiola Valencia* – 50%  
- *Yilmar J.* – 50%  

---

## Objetivo del Proyecto

Desarrollar una shell educativa en lenguaje C que implemente comandos básicos y avanzados del sistema, siguiendo una arquitectura modular y buenas prácticas de programación.

El proyecto simula el comportamiento de una shell real mediante un ciclo REPL (Read-Eval-Print Loop), permitiendo ejecutar comandos personalizados sin utilizar system().

---

## Arquitectura del Proyecto


eafitos/
├── src/
│   ├── core/
│   │   ├── main.c
│   │   ├── shell_loop.c
│   │   └── parser.c
│   ├── commands/
│   │   ├── basic_commands.c
│   │   ├── file_commands.c
│   │   ├── system_commands.c
│   │   └── advanced_commands.c
│   └── utils/
│       ├── memory_manager.c
│       ├── error_handler.c
│       └── helpers.c
├── include/
│   ├── shell.h
│   ├── commands.h
│   ├── parser.h
│   └── utils.h
├── tests/
│   ├── unit_tests.c
│   ├── integration_tests.c
│   └── test_runner.sh
├── docs/
│   ├── API.md
│   ├── DESIGN.md
│   ├── USER_GUIDE.md
│   └── html/
├── scripts/
│   ├── build.sh
│   └── format.sh
├── Makefile
├── CONTRIBUTION.md
├── CHANGELOG.md
└── LICENSE


Arquitectura modular separando responsabilidades en:
- Núcleo del sistema (core)
- Comandos por categoría
- Utilidades independientes
- Headers organizados
- Pruebas y documentación

---

## Compilación y Ejecución

### Compilar

bash
make


### Ejecutar

bash
make run


O directamente:

bash
./build/sistema_os


### Limpiar archivos compilados

bash
make clean


---

## Funcionamiento del REPL

La shell funciona mediante un ciclo continuo:

1. Mostrar el prompt
2. Leer entrada del usuario
3. Parsear argumentos
4. Ejecutar el comando correspondiente
5. Repetir hasta que el usuario escriba salir

Se utiliza una tabla de comandos con punteros a función, aplicando el patrón Command Pattern.

---

## Comandos Implementados

### Comandos Básicos (6 obligatorios)

- listar – Muestra archivos del directorio actual  
- leer <archivo> – Muestra contenido de archivo  
- tiempo – Fecha y hora actual  
- calc <n1> <op> <n2> – Calculadora básica  
- ayuda – Lista de comandos  
- salir – Termina la shell  

### Comandos Avanzados (Equipo 2 personas)

- historial – Muestra últimos 10 comandos  
- limpiar – Limpia la pantalla  
- usuario – Muestra información del usuario actual  
- directorio – Muestra directorio actual  

Total implementados: *10 comandos*

---

## Soporte Multi-Idioma

Cada comando puede ejecutarse en:

- Español  
- Inglés  
- Francés  

Ejemplo:


listar
list
lister


---

## Features Avanzadas

- Autocompletado con TAB  
- Soporte multi-idioma (ES / EN / FR)  
- Manejo de señales (Ctrl+C no cierra la shell)  
- Prompt personalizado con color  
- Historial interno de comandos  
- Arquitectura modular profesional  
- Documentación automática con Doxygen  

---

## Documentación Técnica

Generar documentación automática con:

bash
doxygen Doxyfile


Abrir en navegador:


docs/html/index.html


---

## Buenas Prácticas Aplicadas

- Separación modular por responsabilidades  
- Uso de punteros a función (Command Pattern)  
- Manejo dinámico de memoria con liberación adecuada  
- Manejo de señales (SIGINT)  
- Makefile estructurado  
- Código documentado con estándar Doxygen  

---

## Pruebas

El proyecto incluye carpeta tests/ preparada para pruebas unitarias e integración.

---

## Estado del Proyecto

- Cumple requisitos para equipo de 2 personas  
- Supera el mínimo de comandos requeridos  
- Arquitectura alineada con la rúbrica  
- Compila sin errores  
- Interfaz interactiva funcional  
- Modularidad y documentación completas  

---

## Licencia

MIT License