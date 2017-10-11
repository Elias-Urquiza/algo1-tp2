#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#define MAX_LENGTH 1000
#define MSJ_ERROR_DESTRUIR_ARREGLO "ERROR AL DESTRUIR EL ARREGLO"
#define MSJ_ERROR_TIME "Error con la fecha"
#define MSJ_ERROR "Error"
#define MAX_ARGC 3

typedef enum {ST_ERROR_PUNTERO_NULO, ST_ERROR_NOMEM, ST_OK, ST_ERROR_CANT_ARGC, ST_ERROR_OPEN_ARCHIVO} status_t;

typedef struct {
	size_t id;
	char nombre[200];
	char autor[200];
	char genero[200];
	time_t date;
	double puntaje;
	size_t resenas;
}t_datos;


status_t validar_argumentos(int argc, char* argv[], FILE **file, int numero, char* mode);
t_datos convertir_datos(char** arreglo);
char* strdup(const char* sc);
status_t destruir_arreglo_cadenas(char** campos, size_t size);
char** split(const char* cadena, char delimitador, size_t* l);


int main (int argc, char *argv[])
{

	FILE *pf_entrada;
	FILE *pf_salida;
	char reglon[MAX_LENGTH] = "";
	size_t l = 1;
	char** arreglo = NULL;
	t_datos datos;
	status_t st;

	if ((st = validar_argumentos(argc, argv, &pf_entrada, 1, "r")) != ST_OK)
	{
		printf("%s\n", MSJ_ERROR);
		return EXIT_FAILURE;
	}

	if ((st = validar_argumentos(argc, argv, &pf_salida, 2, "wr")) != ST_OK)
	{
		printf("%s\n", MSJ_ERROR);
		return EXIT_FAILURE;
	}



	while (fgets(reglon, MAX_LENGTH, pf_entrada) != NULL)
	{
		arreglo = split(reglon, ',', &l);

		datos = convertir_datos(arreglo);

		printf("%s\n", reglon);
		fwrite(&datos, sizeof(t_datos), 1, pf_salida);

		if (destruir_arreglo_cadenas(arreglo, l) != ST_OK)
		{
			printf("%s\n", MSJ_ERROR_DESTRUIR_ARREGLO);
			return EXIT_FAILURE;
		}

	}

	rewind(pf_salida);
	fread(&datos, sizeof(t_datos), 1, pf_salida);
	printf("%lu,%s,%s,%s,%s,%.0f,%lu\n", datos.id, datos.nombre, datos.autor, datos.genero, ctime(&datos.date), datos.puntaje, datos.resenas);
	fclose(pf_entrada);
	fclose(pf_salida);



	return EXIT_SUCCESS;

}



status_t validar_argumentos(int argc, char* argv[], FILE **file, int numero, char* mode)
{
	if (argv == NULL || file == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if (argc != MAX_ARGC)
		return ST_ERROR_CANT_ARGC;
	if ((*file = fopen(argv[numero], mode)) == NULL)
		return ST_ERROR_OPEN_ARCHIVO;

	return ST_OK;
}



t_datos convertir_datos(char** arreglo)
{
	struct tm datetm = {0,0,0,0,0,0,0,0,0};
	char datechar[MAX_LENGTH] = "";
	char** datearreglo = NULL;
	t_datos datos;
	size_t l;

	datos.id = atoi(arreglo[0]);
	strcpy(datos.nombre, arreglo[1]);
	strcpy(datos.autor, arreglo[2]);
	strcpy(datos.genero, arreglo[3]);

	strcpy(datechar, arreglo[4]);
	datearreglo = split(datechar, '-', &l);
	datetm.tm_year = atoi(datearreglo[0]) - 1900;
	datetm.tm_mon = atoi(datearreglo[1]) - 1;
	datetm.tm_mday = atoi(datearreglo[2]);
	if ((datos.date = mktime(&datetm)) == -1)
	{
		fprintf(stderr, "%s\n", MSJ_ERROR_TIME);
	}

	if (destruir_arreglo_cadenas(datearreglo, l) != ST_OK)
	{
		printf("%s\n", MSJ_ERROR_DESTRUIR_ARREGLO);
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

status_t destruir_arreglo_cadenas(char** campos, size_t size)
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
