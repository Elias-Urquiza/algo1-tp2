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
		imprimir_error(st, stderr);
		return EXIT_FAILURE;
	}

	if ((pf_salida = fopen(DOC_DECO, "wb")) == NULL)
	{
		st = ST_ERROR_OPEN_ARCHIVO;
		imprimir_error(st, stderr);
		return EXIT_FAILURE;
	}

	while(fread(&datos, sizeof(t_datos), 1, pf_entrada))
	{
		date = *gmtime(&datos.date);
		date.tm_year += ANIO_PARTIDA;
		date.tm_mon += 1;
		impresion_datos(pf_salida, datos, date); /*imprime en DOC_DECO*/
		impresion_datos(stdout, datos, date); /*imprime por pantalla*/
	}


	fclose(pf_entrada);
	fclose(pf_salida);
	return EXIT_SUCCESS;
}
