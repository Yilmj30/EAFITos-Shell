/**
 * @file system_commands.c
 * @brief Comandos de utilería del sistema.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pwd.h>
#include <sys/types.h>

#include "commands.h"

/**
 * @brief Comando CALC (Calculadora)
 */
void cmd_calc(char **args) {
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL) {
        printf("Uso: calc <num1> <operador> <num2>\nEjemplo: calc 5 + 3\n");
        return;
    }

    float n1 = (float)atof(args[1]);
    char op = args[2][0];
    float n2 = (float)atof(args[3]);
    float res = 0;

    switch (op) {
        case '+': res = n1 + n2; break;
        case '-': res = n1 - n2; break;
        case '*':
        case 'x': res = n1 * n2; break;
        case '/':
            if (n2 == 0) {
                printf("Error: División por cero no permitida.\n");
                return;
            }
            res = n1 / n2;
            break;
        default:
            printf("Error: Operador '%c' no reconocido. Use +, -, *, /.\n", op);
            return;
    }

    printf("Resultado: %.2f\n", res);
}

/**
 * @brief Comando USUARIO
 * Muestra información básica del usuario actual (POSIX).
 */
void cmd_usuario(char **args) {
    (void)args;

    uid_t uid = getuid();
    struct passwd *pw = getpwuid(uid);

    if (pw) {
        printf("Usuario: %s\nUID: %d\nHome: %s\nShell: %s\n",
               pw->pw_name, (int)uid, pw->pw_dir, pw->pw_shell);
    } else {
        printf("Usuario: (desconocido)\nUID: %d\n", (int)uid);
    }
}

/**
 * @brief Comando DIRECTORIO (pwd)
 * Muestra el directorio actual.
 */
void cmd_directorio(char **args) {
    (void)args;

    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("%s\n", cwd);
    } else {
        perror("getcwd");
    }
}
