#ifndef FUNCIONES__H
#define FUNCIONES__H

/*prototipos*/

/*crear*/

status_t validar_argumentos_crear(int argc, char* argv[], FILE **file, int numero, char* mode);
t_datos convertir_datos(char** arreglo);
char* strdup(const char* sc);
status_t destruir_arreglo_cadenas(char ***campos, size_t size);
char** split(const char* cadena, char delimitador, size_t* l, status_t* p_estado);

/* */

/*deco*/

status_t validar_argumentos_deco(int argc, char* argv[], FILE **file, int numero, char* mode);

/* */

/*modificar_base*/

status_t validar_argumentos_modificar(int argc, char* argv[], FILE** pf_original, FILE** pf_registro, FILE** pf_log, gestion_t* accion, size_t* pos_original);
status_t crear_datos(FILE *pf, t_datos **datos[]);
status_t destruir_datos(t_datos **datos[]);
status_t gestion_altas(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, FILE *plog, char *argv[], size_t pos_original);
status_t gestion_bajas(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, FILE *plog, char *argv[], size_t pos_original);
status_t gestion_modificacion(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, FILE *plog, char *argv[], size_t pos_original);

/* */

/*impresiones*/

void imprimir_error(status_t estado, FILE* salida);
void imprimir_uso_gestion(void);
void impresion_datos(FILE* pf_salida, t_datos datos, struct tm date);
/* */

#endif
