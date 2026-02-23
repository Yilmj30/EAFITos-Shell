/*
===============================================================================
EAFITos Shell - USER GUIDE (docs/USER_GUIDE.md)
===============================================================================

📖 Guía de Usuario - EAFITos

1) Ejecutar
-----------
Compilar y ejecutar desde la raíz del proyecto:

  make
  make run

(Alternativa)
  ./build/sistema_os


2) Prompt
---------
Al iniciar verás el prompt:

  EAFITos>

Desde ahí puedes escribir comandos y presionar ENTER.


3) Autocompletado con TAB
-------------------------
- Escribe las primeras letras de un comando y presiona TAB.
- Si hay 1 coincidencia: completa automáticamente.
- Si hay varias coincidencias: muestra opciones y vuelve al prompt.

Ejemplo:
  li[TAB]  -> puede completar "listar" (si es la única coincidencia).


4) Comandos (ES / EN / FR)
--------------------------
Puedes ejecutar cada comando en Español / Inglés / Francés según alias.

4.1 Básicos (6)
- listar / list / lister
- leer <archivo> / read <file> / lire <fichier>
- tiempo / time / temps
- calc <n1> <op> <n2> / calc ... / calc ...
- ayuda [comando] / help [command] / aide [commande]
- salir / exit / sortir

4.2 Sistema (avanzados)
- historial / history / historique
- limpiar / clear / nettoyer

4.3 Extra (para más puntaje)
- usuario / user / utilisateur
- directorio / pwd / repertoire


5) Ejemplos rápidos
-------------------
  ayuda
  ayuda calc
  calc 5 + 3
  directorio
  usuario
  historial
  limpiar
  salir


6) Ctrl+C (SIGINT)
------------------
- Presionar Ctrl+C NO cierra la shell.
- Solo cancela la línea actual y regresa al prompt EAFITos>.

===============================================================================
Fin de la guía
===============================================================================
*/
