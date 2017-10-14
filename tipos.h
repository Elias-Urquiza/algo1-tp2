#ifndef TIPOS__H
#define TIPOS__H

/*constantes*/

#define CHAR_COMMENT '#'
#define MSJ_ERROR_DESTRUIR_ARREGLO "ERROR AL DESTRUIR EL ARREGLO"
#define MSJ_ERROR_TIME "Error con la fecha"
#define MSJ_ERROR "Error"

#define MAX_LENGTH 500
#define MAX_ARGC_CREAR 3
#define MAX_LONG_CAMPOS 50
#define ANIO_PARTIDA 1900

#define MAX_ARGC_DECO 2

/* */

/*enums y structs*/

typedef enum {ST_ERROR_PUNTERO_NULO, ST_ERROR_NOMEM, ST_OK, ST_ERROR_CANT_ARGC, ST_ERROR_OPEN_ARCHIVO} status_t;

typedef struct {
	size_t id;
	char nombre[MAX_LONG_CAMPOS];
	char autor[MAX_LONG_CAMPOS];
	char genero[MAX_LONG_CAMPOS];
	time_t date;
	double puntaje;
	size_t resenas;
}t_datos;

/* */

#endif
