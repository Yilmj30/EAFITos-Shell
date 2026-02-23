# 🔌 Referencia de API (Developer)

## include/shell.h
- void loop_shell(void);
- char *leer_linea(void);
- char **parsear_linea(char *linea);
- void ejecutar(char **args);
- extern Comando tabla_comandos[];
- int num_comandos(void);

## include/commands.h
Comandos:
- cmd_listar, cmd_leer, cmd_tiempo, cmd_calc, cmd_ayuda, cmd_salir
- cmd_usuario, cmd_directorio

## include/utils.h
- str_eq(a,b)
- print_error(msg)
- print_errorf(fmt, ...)

## Archivos fuente
- src/core/parser.c: lectura raw + TAB + SIGINT
- src/core/shell_loop.c: REPL + tabla multi-idioma + historial
- src/commands/*: implementación de comandos