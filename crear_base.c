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
		imprimir_error(st);
		return EXIT_FAILURE;
	}

	if ((st = validar_argumentos_crear(argc, argv, &pf_salida, 2, "wr")) != ST_OK)
	{
		imprimir_error(st);
		return EXIT_FAILURE;
	}



	while (fgets(renglon, MAX_LENGTH, pf_entrada) != NULL)
	{
		if(renglon[0] == CHAR_COMMENT) continue; /*salta el renglon si encuentra que el mismo es un comentario*/

		arreglo = split(renglon, ',', &l, &st);

		if(st != ST_OK)
		{
			imprimir_error(st);
			return EXIT_FAILURE;
		}

		datos = convertir_datos(arreglo);

		/*printf("%s\n", renglon);*/
		/*CREO QUE ESTO NO SE DEBE INCLUIR*/

		fwrite(&datos, sizeof(t_datos), 1, pf_salida);

		if ((st = destruir_arreglo_cadenas(arreglo, l)) != ST_OK)
		{
			imprimir_error(st);
			return EXIT_FAILURE;
		}

	}

/* Posiblemente Haya que Borrarlo Antes de Entregarlo. Sirve para Testeo.

	rewind(pf_salida);
	fread(&datos, sizeof(t_datos), 1, pf_salida);
	printf("%lu,%s,%s,%s,%s,%.0f,%lu\n", datos.id, datos.nombre, datos.desarrollador, datos.plataforma, ctime(&datos.date), datos.puntaje, datos.resenas);
*/

	fclose(pf_entrada);
	fclose(pf_salida);



	return EXIT_SUCCESS;
}
