#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tipos.h"
#include "funciones.h"

int main(int argc, char* argv[])
{
	status_t estado;
	gestion_t accion;
	size_t pos_original;
	FILE *pf_original, *pf_registro, *pf_log;
	t_datos **datos_original = NULL;
	t_datos **datos_registro = NULL;

	if((estado = validar_argumentos_gestion(argc, argv, &pf_original, &pf_registro, &pf_log, &accion, &pos_original)) != ST_OK)
	{
		imprimir_error(estado, stderr);
		imprimir_uso_gestion();
		return EXIT_FAILURE;
	}

	if((estado = crear_datos(pf_original, &datos_original)) != ST_OK)
	{
		imprimir_error(estado, stderr);
		return EXIT_FAILURE;
	}

	if((estado = crear_datos(pf_registro, &datos_registro)) != ST_OK)
	{
		imprimir_error(estado, stderr);
		return EXIT_FAILURE;
	}


	switch(accion)
	{
	case GESTION_ALTAS:
	{
		if((estado = gestion_altas(datos_original, datos_registro, pf_original, pf_log, argv, pos_original)) != ST_OK)
		{
			imprimir_error(estado, stderr);
			return EXIT_FAILURE;
		}
		break;
	}
	case GESTION_BAJAS:
	{
		if((estado = gestion_bajas(datos_original, datos_registro, pf_original, pf_log, argv, pos_original)) != ST_OK)
		{
			imprimir_error(estado, stderr);
			return EXIT_FAILURE;
		}
		break;
	}
	case GESTION_MODIFICACION:
	{
		if((estado = gestion_modificacion(datos_original, datos_registro, pf_original, pf_log, argv, pos_original)) != ST_OK)
		{
			imprimir_error(estado, stderr);
			return EXIT_FAILURE;
		}
		break;
	}
	default:
	{
		estado = ST_ERROR_COMANDO;
		imprimir_error(estado, pf_log);         /*imprime en el log*/
		return EXIT_FAILURE;
	}
	}

	if((estado = destruir_datos(&datos_original)) != ST_OK)
	{
		imprimir_error(estado, stderr);
		return EXIT_FAILURE;
	}

	if((estado = destruir_datos(&datos_registro)) != ST_OK)
	{
		imprimir_error(estado, stderr);
		return EXIT_FAILURE;
	}

	fclose(pf_original);
	fclose(pf_registro);
	fclose(pf_log);

	return EXIT_SUCCESS;
}
