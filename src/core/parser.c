/**
 * @file parser.c
 * @brief Módulo encargado de interpretar la entrada del usuario.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include "shell.h"

#define BUFFER_SIZE 1024

/* ===================================== */
/* ==== DECLARACIONES EXTERNAS ========= */
/* ===================================== */

/*
 * Estas vienen desde shell_loop.c
 */
extern int num_comandos();


extern Comando tabla_comandos[];

/* ===================================== */
/* ====== MODO RAW PARA TERMINAL ======= */
/* ===================================== */

void habilitar_modo_raw(struct termios *original) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, original);
    raw = *original;

    raw.c_lflag &= ~(ICANON | ECHO); // Sin modo canónico y sin eco automático

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void restaurar_modo(struct termios *original) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, original);
}

/* ===================================== */
/* ========= AUTOCOMPLETADO ============ */
/* ===================================== */

void autocompletar(char *buffer) {

    int coincidencias = 0;
    char *match = NULL;

    for (int i = 0; i < num_comandos(); i++) {

        if (strncmp(buffer, tabla_comandos[i].es, strlen(buffer)) == 0 ||
            strncmp(buffer, tabla_comandos[i].en, strlen(buffer)) == 0 ||
            strncmp(buffer, tabla_comandos[i].fr, strlen(buffer)) == 0) {

            coincidencias++;
            match = tabla_comandos[i].es; // completamos en español
        }
    }

    if (coincidencias == 1 && match != NULL) {

        printf("\r\033[1;32mEAFITos>\033[0m %s", match);
        fflush(stdout);
        strcpy(buffer, match);
    }
    else if (coincidencias > 1) {

        printf("\n");

        for (int i = 0; i < num_comandos(); i++) {

            if (strncmp(buffer, tabla_comandos[i].es, strlen(buffer)) == 0 ||
                strncmp(buffer, tabla_comandos[i].en, strlen(buffer)) == 0 ||
                strncmp(buffer, tabla_comandos[i].fr, strlen(buffer)) == 0) {

                printf("%s  ", tabla_comandos[i].es);
            }
        }

        printf("\n\033[1;32mEAFITos>\033[0m %s", buffer);
        fflush(stdout);
    }
}

/* ===================================== */
/* ========= LECTURA DE LÍNEA ========= */
/* ===================================== */

char *leer_linea(void) {

    static char buffer[BUFFER_SIZE];
    int pos = 0;
    struct termios original;

    habilitar_modo_raw(&original);

    while (1) {

        char c = getchar();

        if (c == '\n') {

            buffer[pos] = '\0';
            printf("\n");
            break;
        }

        else if (c == 127 || c == 8) { // Backspace

            if (pos > 0) {
                pos--;
                printf("\b \b");
                fflush(stdout);
            }
        }

        else if (c == 9) { // TAB

            buffer[pos] = '\0';
            autocompletar(buffer);
            pos = strlen(buffer);
        }

        else {

            if (pos < BUFFER_SIZE - 1) {
                buffer[pos++] = c;
                putchar(c);
                fflush(stdout);
            }
        }
    }

    restaurar_modo(&original);

    return strdup(buffer); // Importante: malloc interno para que shell_loop pueda hacer free()
}

/* ===================================== */
/* ========= PARSEAR LÍNEA ============= */
/* ===================================== */

char **parsear_linea(char *linea) {

    int bufsize = 64;
    int posicion = 0;

    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "Error de asignación de memoria\n");
        exit(EXIT_FAILURE);
    }

    token = strtok(linea, DELIM);

    while (token != NULL) {

        tokens[posicion++] = token;

        if (posicion >= bufsize) {
            bufsize += 64;
            tokens = realloc(tokens, bufsize * sizeof(char*));

            if (!tokens) {
                fprintf(stderr, "Error de reasignación de memoria\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DELIM);
    }

    tokens[posicion] = NULL;
    return tokens;
}
