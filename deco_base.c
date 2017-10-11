#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_ARGC 2
#define MSJ_ERROR "Error"

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


int main(int argc, char* argv[])
{

	FILE *pf_entrada;
	FILE *pf_salida;
	t_datos datos;
	status_t st;
	struct tm date;

	if ((st = validar_argumentos(argc, argv, &pf_entrada, 1, "r")) != ST_OK)
	{
		printf("%s\n", MSJ_ERROR);
		return EXIT_FAILURE;
	}

	if ((pf_salida = fopen("datos2.csv", "wb")) == NULL)
		return ST_ERROR_OPEN_ARCHIVO;

	while(fread(&datos, sizeof(t_datos), 1, pf_entrada))
	{
		date = *gmtime(&datos.date);
		date.tm_year += 1900;
		date.tm_mon += 1;
		fprintf(pf_salida, "%lu,%s,%s,%s,%i-%i-%i,%.0f,%lu\n", datos.id, datos.nombre, datos.autor, datos.genero, date.tm_year, date.tm_mon, date.tm_mday, datos.puntaje, datos.resenas);
	}


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
