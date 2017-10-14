#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tipos.h"
#include "funciones.h"


int main(int argc, char* argv[])
{

	FILE *pf_entrada;
	FILE *pf_salida;
	t_datos datos;
	status_t st;
	struct tm date;

	if ((st = validar_argumentos_deco(argc, argv, &pf_entrada, 1, "r")) != ST_OK)
	{
		imprimir_error(st);
		return EXIT_FAILURE;
	}

	if ((pf_salida = fopen("datos2.csv", "wb")) == NULL)
	{
		st = ST_ERROR_OPEN_ARCHIVO;
		imprimir_error(st);
		return EXIT_FAILURE;
	}

	while(fread(&datos, sizeof(t_datos), 1, pf_entrada))
	{
		date = *gmtime(&datos.date);
		date.tm_year += ANIO_PARTIDA;
		date.tm_mon += 1;
		fprintf(pf_salida, "%lu,%s,%s,%s,%i-%i-%i,%.0f,%lu\n", datos.id, datos.nombre, datos.desarrollador, datos.plataforma, date.tm_year, date.tm_mon, date.tm_mday, datos.puntaje, datos.resenas);
	}


	fclose(pf_entrada);
	fclose(pf_salida);
	return EXIT_SUCCESS;
}
