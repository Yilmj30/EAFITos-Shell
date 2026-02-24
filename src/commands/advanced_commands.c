#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "commands.h"

#define MAX_HISTORY 100
#define MAX_INPUT 256

static char history[MAX_HISTORY][MAX_INPUT];
static int history_count = 0;

/* =========================
   HISTORIAL
   ========================= */

void guardar_historial(char *linea) {
    if (history_count < MAX_HISTORY) {
        strncpy(history[history_count], linea, MAX_INPUT - 1);
        history[history_count][MAX_INPUT - 1] = '\0';
        history_count++;
    }
}

void cmd_historial(char **args) {
    (void)args; 

    int inicio = history_count - 10;
    if (inicio < 0) inicio = 0;

    for (int i = inicio; i < history_count; i++) {
        printf("%d: %s\n", i + 1, history[i]);
    }
}

/* =========================
   LIMPIAR
   ========================= */

void cmd_limpiar(char **args) {
    (void)args;   // 👈 VA AQUÍ

    printf("\033[H\033[J");
}

/* =========================
   CAMBIAR DIRECTORIO (cd)
   ========================= */

void cmd_cd(char **args) {
    if (args[1] == NULL) {
        fprintf(stderr, "directorio: falta argumento\n");
        return;
    }

    if (chdir(args[1]) != 0) {
        perror("directorio");
    }
}