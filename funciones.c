#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "tipos.h"
#include "funciones.h"

/*crear*/

status_t validar_argumentos_crear(int argc, char* argv[], FILE **file, int numero, char* mode)
{
	if (argv == NULL || file == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if (argc != MAX_ARGC_CREAR)
		return ST_ERROR_CANT_ARGC;
	if ((*file = fopen(argv[numero], mode)) == NULL)
		return ST_ERROR_OPEN_ARCHIVO;

	return ST_OK;
}



t_datos convertir_datos(char** arreglo)
{
	struct tm datetm = {0,0,0,1,0,0,0,0,0}; /* tm_mday puede tomar valores de 1 a 31 por ello elegí poner ese uno.*/
	char datechar[MAX_LENGTH] = "";
	char** datearreglo = NULL;
	t_datos datos;
	size_t l;
	status_t estado;

	datos.id = atoi(arreglo[0]);
	strcpy(datos.nombre, arreglo[1]);
	strcpy(datos.autor, arreglo[2]);
	strcpy(datos.genero, arreglo[3]);

	strcpy(datechar, arreglo[4]);
	datearreglo = split(datechar, '-', &l);
	datetm.tm_year = atoi(datearreglo[0]) - ANIO_PARTIDA;
	datetm.tm_mon = atoi(datearreglo[1]) - 1;
	datetm.tm_mday = atoi(datearreglo[2]);
	if ((datos.date = mktime(&datetm)) == -1)
	{
		estado = ST_ERROR_TIME;
		imprimir_error(estado);
		return; /*hacer que llame a una funcion que retorna una estructura vacía*/
	}

	if (destruir_arreglo_cadenas(datearreglo, l) != ST_OK)
	{
		estado = ST_ERROR_DESTRUIR_ARREGLO;
		imprimir_error(estado);
		return; /*hacer que llame a una funcion que retorna una estructura vacía*/
	}

	datos.puntaje = atoi(arreglo[5]);
	datos.resenas = atoi(arreglo[6]);

	return datos;
}



char* strdup(const char* sc)
{
	size_t l;
	char *s;

	if(sc == NULL)
		return NULL;

	l = strlen(sc) + 1;

	s = (char*)malloc(sizeof(char)*(l));

	if(s != NULL)
		memcpy(s,sc,l);
	return s;
}

status_t destruir_arreglo_cadenas(char** campos, size_t size) /*agregar verificación si saben cual poner*/
{
	size_t i;

	for(i = 0; i < size; i++)
	{
		free(campos[i]);
		campos[i] = NULL;
	}

	free(campos);
	campos = NULL;

	return ST_OK;
}

char** split(const char* cadena, char delimitador, size_t* l)
{
	char** campos;
	size_t n, i;
	char *aux, *q, *linea, delim[2];

	if(!cadena || !l)
		return ST_ERROR_PUNTERO_NULO;

	for(i = 0, n = 1; cadena[i]; i++)
	{
		if(cadena[i] == delimitador)
			n++;
	}

	if((campos = (char**)malloc(sizeof(char*)*n)) == NULL)
	{
		*l = 0;
		return NULL;
	}

	if((linea = strdup(cadena)) == NULL)
	{
		free(campos);
		campos = NULL;
		*l = 0;
		return NULL;
	}

	delim[0] = delimitador;
	delim[1] = '\0';

	for(i = 0, q = linea; (aux = strtok(q, delim)) != NULL; i++, q = NULL)
	{
		if((campos[i] = strdup(aux)) == NULL)
		{
			if((destruir_arreglo_cadenas(campos, i)) != ST_OK)
			{
				puts(MSJ_ERROR_DESTRUIR_ARREGLO);
			}
			campos = NULL;
			*l = 0;
		}
	}
	free(linea);
	*l = i;
	return campos;
}
/* */

/*deco*/

status_t validar_argumentos_deco(int argc, char* argv[], FILE **file, int numero, char* mode)
{
	if (argv == NULL || file == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if (argc != MAX_ARGC_DECO)
		return ST_ERROR_CANT_ARGC;
	if ((*file = fopen(argv[numero], mode)) == NULL)
		return ST_ERROR_OPEN_ARCHIVO;

	return ST_OK;
}


/* */

/*Impresiones*/

imprimir_error(status_t estado)
{
	switch(estado)
	{
		case ST_ERROR_PUNTERO_NULO:
			puts(MSJ_ERROR_PUNTERO_NULO);
			break;

		case ST_ERROR_NOMEM:
			puts(MSJ_ERROR_NOMEM);
			break;

		case ST_ERROR_CANT_ARGC:
			puts(MSJ_ERROR_CANT_ARGC);
			break;

		case ST_ERROR_OPEN_ARCHIVO:
			puts(MSJ_ERROR_OPEN_ARCHIVO);
			break;

		case ST_ERROR_TIME:
			puts(MSJ_ERROR_TIME);
			break;

		case ST_ERROR_DESTRUIR_ARREGLO:
			puts(MSJ_ERROR_DESTRUIR_ARREGLO);
			break;
			
		default:
			puts(MSJ_ERROR);
	}
}
