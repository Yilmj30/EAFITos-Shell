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

/* ============================= */
/* ====== HISTORIAL GLOBAL ===== */
/* ============================= */

char history[MAX_HISTORY][MAX_INPUT];
int history_count = 0;

/* ============================= */
/* ===== TABLA MULTI-IDIOMA ==== */
/* ============================= */

/*
 * Ahora cada comando tiene:
 * Español | Inglés | Francés | Función
 */


Comando tabla_comandos[] = {
    {"listar",    "list",      "lister",     &cmd_listar},
    {"leer",      "read",      "lire",       &cmd_leer},
    {"tiempo",    "time",      "temps",      &cmd_tiempo},
    {"calc",      "calc",      "calc",       &cmd_calc},
    {"ayuda",     "help",      "aide",       &cmd_ayuda},
    {"salir",     "exit",      "sortir",     &cmd_salir},
    {"historial", "history",   "historique", NULL}, // lo manejamos aquí
    {"limpiar",   "clear",     "nettoyer",   NULL}  // lo manejamos aquí
};

int num_comandos() {
    return sizeof(tabla_comandos) / sizeof(Comando);
}

/* ============================= */
/* ========= HISTORIAL ========= */
/* ============================= */

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

/* ============================= */
/* ========= LIMPIAR =========== */
/* ============================= */

void cmd_limpiar() {
    printf("\033[H\033[J");
}

/* ============================= */
/* ========= EJECUTAR ========== */
/* ============================= */

void ejecutar(char **args) {

    if (args[0] == NULL) {
        return;
    }

    for (int i = 0; i < num_comandos(); i++) {

        if (strcmp(args[0], tabla_comandos[i].es) == 0 ||
            strcmp(args[0], tabla_comandos[i].en) == 0 ||
            strcmp(args[0], tabla_comandos[i].fr) == 0) {

            // Comandos manejados internamente
            if (strcmp(tabla_comandos[i].es, "historial") == 0) {
                cmd_historial();
                return;
            }

            if (strcmp(tabla_comandos[i].es, "limpiar") == 0) {
                cmd_limpiar();
                return;
            }

            // Comandos normales
            if (tabla_comandos[i].func != NULL) {
                (*tabla_comandos[i].func)(args);
                return;
            }
        }
    }

    printf("Comando desconocido: %s\nEscribe 'ayuda' / 'help' / 'aide'\n", args[0]);
}

/* ============================= */
/* ========= REPL LOOP ========= */
/* ============================= */

void loop_shell() {

    char *linea;
    char **args;
    int status = 1;

    do {
        printf("\033[1;32mEAFITos>\033[0m ");

        linea = leer_linea();

        // Guardar en historial antes de parsear
        if (linea != NULL && strlen(linea) > 1) {
            guardar_historial(linea);
        }

        args = parsear_linea(linea);

        ejecutar(args);

        free(linea);
        free(args);

    } while (status);
}
