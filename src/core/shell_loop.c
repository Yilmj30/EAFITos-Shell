/**
 * @file shell_loop.c
 * @brief Corazón operativo de la shell (Lógica de control).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"
#include "commands.h"

/* Tabla multi-idioma */
Comando tabla_comandos[] = {
    {"listar",     "list",       "lister",      &cmd_listar},
    {"leer",       "read",       "lire",        &cmd_leer},
    {"tiempo",     "time",       "temps",       &cmd_tiempo},
    {"calc",       "calc",       "calc",        &cmd_calc},
    {"ayuda",      "help",       "aide",        &cmd_ayuda},
    {"salir",      "exit",       "sortir",      &cmd_salir},

    /* Sistema */
    {"historial",  "history",    "historique",  &cmd_historial},
    {"limpiar",    "clear",      "nettoyer",    &cmd_limpiar},
    {"cambiar",    "cd",         "changer",     &cmd_cd},

    /* Extra */
    {"usuario",    "user",       "utilisateur", &cmd_usuario},
    {"directorio", "pwd",        "repertoire",  &cmd_directorio}
};

int num_comandos() {
    return (int)(sizeof(tabla_comandos) / sizeof(Comando));
}

/* Ejecutar */
void ejecutar(char **args) {
    if (args[0] == NULL) return;

    for (int i = 0; i < num_comandos(); i++) {

        if (strcmp(args[0], tabla_comandos[i].es) == 0 ||
            strcmp(args[0], tabla_comandos[i].en) == 0 ||
            strcmp(args[0], tabla_comandos[i].fr) == 0) {

            if (tabla_comandos[i].func != NULL) {
                (*tabla_comandos[i].func)(args);
                return;
            }
        }
    }

    printf("Comando desconocido: %s\n", args[0]);
    printf("Escribe 'ayuda' / 'help' / 'aide'\n");
}

/* Loop principal */
void loop_shell() {
    char *linea;
    char **args;

    while (1) {

        printf("\033[1;32mEAFITos>\033[0m ");

        linea = leer_linea();

        if (linea == NULL) {
            continue;
        }

        if (strlen(linea) > 1) {
            guardar_historial(linea);
        }

        args = parsear_linea(linea);

        ejecutar(args);

        free(linea);
        free(args);
    }
}
