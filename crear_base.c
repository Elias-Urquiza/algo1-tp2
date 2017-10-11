#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LENGTH 1000
#define MSJ_ERROR_DESTRUIR_ARREGLO "ERROR AL DESTRUIR EL ARREGLO"

typedef enum {ST_ERROR_PUNTERO_NULO, ST_ERROR_NOMEM, ST_OK} status_t;

typedef struct {
	size_t id;
	char nombre[200];
	char autor[200];
	char genero[200];
	/*time_t date;*/
	double puntaje;
	size_t resenas;
}t_datos;

char* strdup(const char* sc);
status_t destruir_arreglo_cadenas(char*** campos, size_t size);
status_t split(const char* cadena, char delimitador, char*** arreglo, size_t* l);


int main (int argc, char *argv[])
{

	FILE *pf_entrada;
	FILE *pf_salida;
	char reglon[MAX_LENGTH] = "";
	size_t l;
	char** arreglo;
	t_datos datos;
	t_datos *pdatos = &datos;

	pf_entrada = fopen(argv[1],"r");
	pf_salida = fopen(argv[2],"wb");

	if (pf_entrada != NULL || pf_salida != NULL)
	{
		while (fgets(reglon, MAX_LENGTH, pf_entrada) != NULL)
		{
			split(reglon, ',', &arreglo, &l);

			datos.id = atoi(arreglo[0]);
			strcpy(datos.nombre, arreglo[1]);
			strcpy(datos.autor, arreglo[2]);
			strcpy(datos.genero, arreglo[3]);
			datos.puntaje = atoi(arreglo[5]);
			datos.resenas = atoi(arreglo[6]);

			fwrite(pdatos, sizeof(t_datos), 1, pf_salida);

		}

		fclose(pf_entrada);
		fclose(pf_salida);
	}


	return EXIT_SUCCESS;

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

status_t destruir_arreglo_cadenas(char*** campos, size_t size)
{
	size_t i;

	for(i = 0; i < size; i++)
	{
		free((*campos)[i]);
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
