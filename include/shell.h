#ifndef SHELL_H
#define SHELL_H

#define MAX_CMD_INPUT 1024
#define DELIM " \t\r\n\a"

void loop_shell();
char *leer_linea(void);
char **parsear_linea(char *linea);
void ejecutar(char **args);

/*
 * Estructura base de un comando (Soporte multi-idioma)
 */
typedef struct {
    char *es;
    char *en;
    char *fr;
    void (*func)(char **);
} Comando;

/*
 * Tabla global de comandos (definida en shell_loop.c)
 */
extern Comando tabla_comandos[];
int num_comandos();

#endif

