#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tipos.h"
#include "funciones.h"


int main (int argc, char *argv[])
{

	FILE *pf_entrada;
	FILE *pf_salida;
	char renglon[MAX_LENGTH] = "";
	size_t l = 1;
	char** arreglo = NULL;
	t_datos datos;
	status_t st;


	if ((st = validar_argumentos_crear(argc, argv, &pf_entrada, 1, "r")) != ST_OK)
	{
		imprimir_error(st, stderr);
		return EXIT_FAILURE;
	}

	if ((st = validar_argumentos_crear(argc, argv, &pf_salida, 2, "w+b")) != ST_OK)
	{
		imprimir_error(st, stderr);
		return EXIT_FAILURE;
	}



	while (fgets(renglon, MAX_LENGTH, pf_entrada) != NULL)
	{
		if(renglon[0] == CHAR_COMMENT) continue; /*salta el renglon si encuentra que el mismo es un comentario*/

		arreglo = split(renglon, ',', &l, &st);

		if(st != ST_OK)
		{
			imprimir_error(st, stderr);
			return EXIT_FAILURE;
		}

		datos = convertir_datos(arreglo);

		if (fwrite(&datos, sizeof(t_datos), 1, pf_salida) != 1)
		{
			st = ST_ERROR_WRITE;
			imprimir_error(st, stderr);
		}

		if ((st = destruir_arreglo_cadenas(&arreglo, l)) != ST_OK)
		{
			imprimir_error(st, stderr);
			return EXIT_FAILURE;
		}
	}

	fclose(pf_entrada);
	fclose(pf_salida);

	return EXIT_SUCCESS;
}
