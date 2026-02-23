/**
 * @file basic_commands.c
 * @brief Implementación de comandos básicos del sistema.
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "commands.h"
#include "shell.h"
#include "utils.h"

typedef struct {
    const char *es;
    const char *uso_es;
    const char *desc_es;

    const char *uso_en;
    const char *desc_en;

    const char *uso_fr;
    const char *desc_fr;
} HelpEntry;

static const HelpEntry HELP[] = {
    {"listar",
     "listar",
     "Muestra el contenido del directorio actual.",
     "list",
     "Lists current directory contents.",
     "lister",
     "Liste le contenu du répertoire courant."},

    {"leer",
     "leer <archivo>",
     "Muestra el contenido de un archivo de texto.",
     "read <file>",
     "Prints the contents of a text file.",
     "lire <fichier>",
     "Affiche le contenu d'un fichier texte."},

    {"tiempo",
     "tiempo",
     "Muestra la fecha y hora actual.",
     "time",
     "Shows current date and time.",
     "temps",
     "Affiche la date et l'heure actuelles."},

    {"calc",
     "calc <num1> <op> <num2>",
     "Calculadora básica (+, -, *, /).",
     "calc <n1> <op> <n2>",
     "Basic calculator (+, -, *, /).",
     "calc <n1> <op> <n2>",
     "Calculatrice basique (+, -, *, /)."},

    {"ayuda",
     "ayuda [comando]",
     "Muestra lista de comandos o ayuda específica.",
     "help [command]",
     "Shows command list or command-specific help.",
     "aide [commande]",
     "Affiche la liste des commandes ou l'aide d'une commande."},

    {"salir",
     "salir",
     "Termina la shell.",
     "exit",
     "Exits the shell.",
     "sortir",
     "Quitte la shell."},

    {"historial",
     "historial",
     "Muestra los últimos 10 comandos ejecutados.",
     "history",
     "Shows last 10 commands.",
     "historique",
     "Affiche les 10 dernières commandes."},

    {"limpiar",
     "limpiar",
     "Limpia la pantalla.",
     "clear",
     "Clears the screen.",
     "nettoyer",
     "Nettoie l'écran."},

    {"usuario",
     "usuario",
     "Muestra información del usuario actual.",
     "user",
     "Shows current user info.",
     "utilisateur",
     "Affiche les infos de l'utilisateur courant."},

    {"directorio",
     "directorio",
     "Muestra el directorio actual.",
     "pwd",
     "Prints current working directory.",
     "repertoire",
     "Affiche le répertoire courant."},
};

static int help_len(void) {
    return (int)(sizeof(HELP) / sizeof(HELP[0]));
}

static const HelpEntry* find_help_by_any_alias(const char *token) {
    if (!token) return NULL;

    for (int i = 0; i < help_len(); i++) {
        const HelpEntry *h = &HELP[i];

        /* Comparar contra aliases ES/EN/FR en la tabla de comandos */
        for (int j = 0; j < num_comandos(); j++) {
            if (str_eq(h->es, tabla_comandos[j].es)) {
                if (str_eq(token, tabla_comandos[j].es) ||
                    str_eq(token, tabla_comandos[j].en) ||
                    str_eq(token, tabla_comandos[j].fr)) {
                    return h;
                }
            }
        }
    }
    return NULL;
}

static void print_help_entry(const HelpEntry *h) {
    if (!h) return;

    printf("=== AYUDA / HELP / AIDE ===\n");
    printf("ES: %s\n    %s\n    Uso: %s\n\n", h->es, h->desc_es, h->uso_es);
    printf("EN: %s\n    %s\n    Usage: %s\n\n", h->es, h->desc_en, h->uso_en);
    printf("FR: %s\n    %s\n    Usage: %s\n", h->es, h->desc_fr, h->uso_fr);
}

/**
 * @brief Comando AYUDA
 * - Sin args: lista comandos disponibles (ES/EN/FR)
 * - Con args: ayuda específica del comando (por alias ES/EN/FR)
 */
void cmd_ayuda(char **args) {
    if (args && args[1]) {
        const HelpEntry *h = find_help_by_any_alias(args[1]);
        if (!h) {
            print_errorf("No existe ayuda para '%s'. Usa 'ayuda' para listar.\n", args[1]);
            return;
        }
        print_help_entry(h);
        return;
    }

    printf("--- Ayuda de Shell Educativa EAFITos ---\n");
    printf("Comandos disponibles (ES / EN / FR):\n");
    for (int i = 0; i < num_comandos(); i++) {
        printf("  - %s / %s / %s\n", tabla_comandos[i].es, tabla_comandos[i].en, tabla_comandos[i].fr);
    }
    printf("\nTip: 'ayuda <comando>' para ver uso y descripción.\n");
}

/**
 * @brief Comando SALIR
 */
void cmd_salir(char **args) {
    (void)args;
    printf("Saliendo de la shell...\n");
    exit(0);
}

/**
 * @brief Comando TIEMPO
 */
void cmd_tiempo(char **args) {
    (void)args;

    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    printf("Fecha y Hora del Sistema: %02d-%02d-%04d %02d:%02d:%02d\n",
           tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
           tm.tm_hour, tm.tm_min, tm.tm_sec);
}
