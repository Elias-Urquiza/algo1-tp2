#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tipos.h"
#include "funciones.h"

#define OPCION_ORIG "-if"
#define OPCION_REG "-f"
#define OPCION_LOG "-log"
#define CHAR_ALTA 'A'
#define CHAR_BAJA 'B'
#define CHAR_MODIF 'M'

status_t validar_argumentos_gestion(int argc, char* argv[], FILE** pf_original, FILE** pf_registro, FILE** pf_log, gestion_t* accion);

int main(int argc, char* argv[])
{
	const char *flag[] = {OPCION_ORIG, OPCION_REG, OPCION_LOG};
	status_t estado;
	gestion_t accion;
	FILE *pf_original, *pf_registro, *pf_log;
	int i, j;

	if((estado = validar_argumentos_gestion(argc, argv, &pf_original, &pf_registro, &pf_log, &accion)) != ST_OK)
	{
		imprimir_error(estado, stderr);
		imprimir_uso_gestion();
		return EXIT_FAILURE;
	}

	switch(accion)
	{
		case GESTION_ALTAS:
		{
			/**/
			break;
		}
		case GESTION_BAJA:
		{
			/**/
			break;
		}
		case GESTION_MODIFICACION:
		{
			/**/
			break;
		}
		default:
		{
			estado = ST_ERROR_COMANDO;
			imprimir_error(estado, pf_log); /*imprime en el log*/
			return EXIT_FAILURE;
		}
	}

	return EXIT_SUCCESS;
}


status_t validar_argumentos_gestion(int argc, char* argv[], FILE** pf_original, FILE** pf_registro, FILE** pf_log, gestion_t* accion)
{
	const char *flag[] = {OPCION_ORIG, OPCION_REG, OPCION_LOG};
	int i, j;

	if(argc != MAX_ARGC_GESTION)
	{
		return ST_ERROR_FLAGS;
	}

	for(i = 2; i < argc; i+=2) /* empieza en 2 y aumenta en 2 para leer cada flag*/
	{
		for(j = 0; j < sizeof(flag)/sizeof(flag[0]); j++)
		{
			if(!(strcmp(argv[i], flag[j]))) /*se detiene cuando encuentra un flag*/
				break;
		}

		if(j == sizeof(flag)/sizeof(flag[0]))
		{
			return ST_ERROR_FLAGS;
		}

		switch(flag[j]) /*lee la opcion*/
		{
			case OPCION_ORIG:
				{
					if((*pf_original = fopen(argv[i+1], "rb+")) == NULL)
					{
						return ST_ERROR_PUNTERO_NULO;
					}
					break;
				}

			case OPCION_REG:
				{
					if((*pf_registro = fopen(argv[i+1], "rb")) == NULL)
					{
						return ST_ERROR_PUNTERO_NULO;
					}
					break;
				}

			case OPCION_LOG:
				{
					if((*pf_log = fopen(argv[i+1], "a+")) == NULL)
					{
						return ST_ERROR_PUNTERO_NULO;
					}
					break;
				}
			default:
				{
					return ST_ERROR_FLAGS;
				}
		}
	}

	/**/
	switch(argv[1][0])
	{
		case CHAR_ALTA:
			*accion = GESTION_ALTAS;
			break;

		case CHAR_BAJA:
			*accion = GESTION_BAJA;
			break;

		case CHAR_MODIF:
			*accion = GESTION_MODIFICACION;
			break;

		default:
			*accion = GESTION_NULA;
	}
	/**/

	return ST_OK;
}
