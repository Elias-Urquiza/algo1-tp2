#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MSJ_ERROR_DESTRUIR_ARREGLO "ERROR AL DESTRUIR EL ARREGLO"

typedef enum {ST_ERROR_PUNTERO_NULO, ST_ERROR_NOMEM, ST_OK} status_t;

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

status_t destruir_arreglo_cadenas(char*** campos, size_t size)
{
	size_t i;

	for(i = 0; i < size; i++)
	{
		free(**campos)[i]);
		campos[i] = NULL;
	}
	free(campos);
	campos = NULL;

	return ST_OK;
}

status_t split(const char* cadena, char delimitador, char*** arreglo, size_t* l)
{
	status_t estado;
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
		*arreglo = NULL;
		*l = 0;
		return ST_ERROR_NOMEM;
	}

	if((linea = strdup(cadena)) == NULL)
	{
		free(campos);
		*arreglo = NULL;
		*l = 0;
		return ST_ERROR_NOMEM;
	}
	
	delim[0] = delimitador;
	delim[1] = '\0';

	for(i = 0, q = linea; (aux = strtok(q, delim)) != NULL; i++, q = NULL)
	{
		if((campos[i] = strdup(aux)) == NULL)
		{
			if((estado = destruir_arreglo_cadenas(&campos, i)) != ST_OK)
			{
				puts(MSJ_ERROR_DESTRUIR_ARREGLO);
			}
			*arreglo = NULL;
			*l = 0;
			return ST_ERROR_NOMEM;
		}
	}

	free(linea);
	*l = i;
	*arreglo = campos;
	return ST_OK;
}

int main(void)
{
	const char cadena = "Elías Urquiza,93984286,20";
	char delimitador = ',';
	char** arreglo;
	size_t l = 3;
	size_t i;
	status_t estado;

	if(estado = split(&cadena, delimitador, &arreglo, &l))
	{
		puts(MSJ_ERROR_SPLIT);
		return EXIT_FAILURE;
	}

	for(i = 0; i < l; i++)
	{
		printf("%s\n", arreglo[i]);
	}

	return EXIT_SUCCESS;
}
