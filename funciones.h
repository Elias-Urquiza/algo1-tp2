#ifndef FUNCIONES__H
#define FUNCIONES__H

/*prototipos*/

/*crear*/

status_t validar_argumentos_crear(int argc, char* argv[], FILE **file, int numero, char* mode);
t_datos convertir_datos(char** arreglo);
char* strdup(const char* sc);
status_t destruir_arreglo_cadenas(char** campos, size_t size);
char** split(const char* cadena, char delimitador, size_t* l, status_t* p_estado);

/* */

/*deco*/

status_t validar_argumentos_deco(int argc, char* argv[], FILE **file, int numero, char* mode);

/* */

/*gestion*/

/* */

/*impresiones*/

imprimir_error(status_t estado, FILE* salida);
imprimir_uso_gestion(void);

/* */
#endif
