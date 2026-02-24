/**
 * @file commands.h
 * @brief Interfaz para los comandos del sistema.
 *
 * Todas siguen la firma void cmd_nombre(char **args).
 */

#ifndef COMMANDS_H
#define COMMANDS_H

/* Básicos (6 obligatorios) */
void cmd_listar(char **args);
void cmd_leer(char **args);
void cmd_tiempo(char **args);
void cmd_calc(char **args);
void cmd_ayuda(char **args);
void cmd_salir(char **args);


/* ADVANCED COMMANDS */

void cmd_historial(char **args);
void cmd_limpiar(char **args);
void cmd_cd(char **args);

void guardar_historial(char *linea);
/* Sistema (avanzados) */
void cmd_usuario(char **args);
void cmd_directorio(char **args);

#endif