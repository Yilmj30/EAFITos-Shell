/**
 * @file shell_loop.c
 * @brief Corazón operativo de la shell (Lógica de control).
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "shell.h"
#include "commands.h"

#define MAX_HISTORY 100
#define MAX_INPUT 256

char history[MAX_HISTORY][MAX_INPUT];
int history_count = 0;

/* Tabla multi-idioma */
Comando tabla_comandos[] = {
    {"listar",     "list",       "lister",      &cmd_listar},
    {"leer",       "read",       "lire",        &cmd_leer},
    {"tiempo",     "time",       "temps",       &cmd_tiempo},
    {"calc",       "calc",       "calc",        &cmd_calc},
    {"ayuda",      "help",       "aide",        &cmd_ayuda},
    {"salir",      "exit",       "sortir",      &cmd_salir},

    /* Sistema (avanzados mínimos) */
    {"historial",  "history",    "historique",  NULL}, /* interno */
    {"limpiar",    "clear",      "nettoyer",    NULL}, /* interno */

    /* Extra para más puntos */
    {"usuario",    "user",       "utilisateur", &cmd_usuario},
    {"directorio", "pwd",        "repertoire",  &cmd_directorio}
};

int num_comandos() {
    return (int)(sizeof(tabla_comandos) / sizeof(Comando));
}

/* Historial */
void guardar_historial(char *linea) {
    if (history_count < MAX_HISTORY) {
        strncpy(history[history_count], linea, MAX_INPUT - 1);
        history[history_count][MAX_INPUT - 1] = '\0';
        history_count++;
    }
}

void cmd_historial() {
    int inicio = history_count - 10;
    if (inicio < 0) inicio = 0;

    for (int i = inicio; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

/* Limpiar */
void cmd_limpiar() {
    printf("\033[H\033[J");
}

/* Ejecutar */
void ejecutar(char **args) {
    if (args[0] == NULL) return;

    for (int i = 0; i < num_comandos(); i++) {
        if (strcmp(args[0], tabla_comandos[i].es) == 0 ||
            strcmp(args[0], tabla_comandos[i].en) == 0 ||
            strcmp(args[0], tabla_comandos[i].fr) == 0) {

            if (strcmp(tabla_comandos[i].es, "historial") == 0) {
                cmd_historial();
                return;
            }

            if (strcmp(tabla_comandos[i].es, "limpiar") == 0) {
                cmd_limpiar();
                return;
            }

            if (tabla_comandos[i].func != NULL) {
                (*tabla_comandos[i].func)(args);
                return;
            }
        }
    }

    printf("Comando desconocido: %s\nEscribe 'ayuda' / 'help' / 'aide'\n", args[0]);
}

/* Loop */
void loop_shell() {
    char *linea;
    char **args;
    int status = 1;

    do {
        printf("\033[1;32mEAFITos>\033[0m ");

        linea = leer_linea();

        if (linea != NULL && strlen(linea) > 1) {
            guardar_historial(linea);
        }

        args = parsear_linea(linea);

        ejecutar(args);

        free(linea);
        free(args);

    } while (status);
}
