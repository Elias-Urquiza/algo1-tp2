#ifndef TIPOS__H
#define TIPOS__H

/*constantes*/

#define CHAR_COMMENT '#'
#define MSJ_ERROR_NOMEM "Sin Memoria Suficiente."
#define MSJ_ERROR_OPEN_ARCHIVO "No se pudo abrir el archivo."
#define MSJ_ERROR_CANT_ARGC "Cantidad de Argumentos Invalida."
#define MSJ_ERROR_PUNTERO_NULO "No se pudo leer el archivo."
#define MSJ_ERROR_DESTRUIR_ARREGLO "Error al destruir el arreglo."
#define MSJ_ERROR_TIME "Error con la fecha."
#define MSJ_ERROR_FLAGS "No se encuentra ningún flag."
#define MSJ_ERROR_COMANDO "No se puede realizar la acción pedida."
#define MSJ_ERROR_WRITE "No se puede escribir en el archivo"
#define MSJ_ERROR "Error."
#define MSJ_USO_GESTION "USO: ./gestion operacion -if base_datos -f archivo_registro -log archivo_logs"

#define MAX_LENGTH 500
#define MAX_ARGC_CREAR 3
#define MAX_LONG_CAMPOS 50
#define ANIO_PARTIDA 1900

#define MAX_ARGC_DECO 2

#define MAX_ARGC_GESTION 8
#define NUM_FLAGS 3

/* */

/*enums y structs*/

typedef enum {ST_OK, ST_ERROR_PUNTERO_NULO, ST_ERROR_NOMEM, ST_ERROR_CANT_ARGC, ST_ERROR_OPEN_ARCHIVO, ST_ERROR_TIME, ST_ERROR_DESTRUIR_ARREGLO, ST_ERROR_FLAGS, ST_ERROR_COMANDO, ST_ERROR_WRITE} status_t;

typedef enum {GESTION_ALTAS, GESTION_BAJAS, GESTION_MODIFICACION, GESTION_NULA} gestion_t;

typedef struct {
	size_t id;
	char nombre[MAX_LONG_CAMPOS];
	char desarrollador[MAX_LONG_CAMPOS];
	char plataforma[MAX_LONG_CAMPOS];
	time_t date;
	double puntaje;
	size_t resenas;
}t_datos;

/* */

#endif
