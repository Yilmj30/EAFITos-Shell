/**
 * @file parser.c
 * @brief Módulo encargado de interpretar la entrada del usuario.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <signal.h>

#include "shell.h"

#define BUFFER_SIZE 1024

extern int num_comandos();
extern Comando tabla_comandos[];

/* ============================= */
/* ====== MANEJO DE SEÑALES ==== */
/* ============================= */

static volatile sig_atomic_t g_interrupted = 0;

static void sigint_handler(int sig) {
    (void)sig;
    g_interrupted = 1;
}

/* ============================= */
/* ====== MODO RAW TERMINAL ==== */
/* ============================= */

static void habilitar_modo_raw(struct termios *original) {
    struct termios raw;
    tcgetattr(STDIN_FILENO, original);
    raw = *original;

    raw.c_lflag &= ~(ICANON | ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

static void restaurar_modo(struct termios *original) {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, original);
}

/* ============================= */
/* ========= AUTOCOMPLETADO ==== */
/* ============================= */

static void autocompletar(char *buffer) {
    int coincidencias = 0;
    char *match = NULL;

    for (int i = 0; i < num_comandos(); i++) {
        if (strncmp(buffer, tabla_comandos[i].es, strlen(buffer)) == 0 ||
            strncmp(buffer, tabla_comandos[i].en, strlen(buffer)) == 0 ||
            strncmp(buffer, tabla_comandos[i].fr, strlen(buffer)) == 0) {
            coincidencias++;
            match = tabla_comandos[i].es; /* completar en español */
        }
    }

    if (coincidencias == 1 && match != NULL) {
        printf("\r\033[1;32mEAFITos>\033[0m %s", match);
        fflush(stdout);
        strcpy(buffer, match);
    } else if (coincidencias > 1) {
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

/* ============================= */
/* ========= LECTURA LINEA ===== */
/* ============================= */

char *leer_linea(void) {
    static char buffer[BUFFER_SIZE];
    int pos = 0;
    struct termios original;

    /* instalar handler SIGINT (Ctrl+C) */
    signal(SIGINT, sigint_handler);
    g_interrupted = 0;

    habilitar_modo_raw(&original);

    while (1) {
        if (g_interrupted) {
            /* Ctrl+C: no mata la shell, solo vuelve al prompt */
            buffer[0] = '\0';
            printf("\n");
            break;
        }

        int ci = getchar();
        if (ci == EOF) {
            buffer[0] = '\0';
            printf("\n");
            break;
        }

        char c = (char)ci;

        if (c == '\n') {
            buffer[pos] = '\0';
            printf("\n");
            break;
        } else if (c == 127 || c == 8) { /* Backspace */
            if (pos > 0) {
                pos--;
                printf("\b \b");
                fflush(stdout);
            }
        } else if (c == 9) { /* TAB */
            buffer[pos] = '\0';
            autocompletar(buffer);
            pos = (int)strlen(buffer);
        } else {
            if (pos < BUFFER_SIZE - 1) {
                buffer[pos++] = c;
                putchar(c);
                fflush(stdout);
            }
        }
    }

    restaurar_modo(&original);

    return strdup(buffer);
}

/* ============================= */
/* ========= PARSEAR LINEA ===== */
/* ============================= */

char **parsear_linea(char *linea) {
    int bufsize = 64;
    int posicion = 0;

    char **tokens = malloc((size_t)bufsize * sizeof(char *));
    if (!tokens) {
        fprintf(stderr, "Error de asignación de memoria\n");
        exit(EXIT_FAILURE);
    }

    char *token = strtok(linea, DELIM);
    while (token != NULL) {
        tokens[posicion++] = token;

        if (posicion >= bufsize) {
            bufsize += 64;
            char **tmp = realloc(tokens, (size_t)bufsize * sizeof(char *));
            if (!tmp) {
                fprintf(stderr, "Error de reasignación de memoria\n");
                exit(EXIT_FAILURE);
            }
            tokens = tmp;
        }

        token = strtok(NULL, DELIM);
    }

    tokens[posicion] = NULL;
    return tokens;
}
