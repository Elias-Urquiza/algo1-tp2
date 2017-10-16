#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "tipos.h"
#include "funciones.h"

#define OPCION_ORIG "-if"
#define OPCION_REG "-f"
#define OPCION_LOG "-log"
#define CHAR_ORIG 'i'
#define CHAR_REG 'f'
#define CHAR_LOG 'l'
#define CHAR_ALTA 'A'
#define CHAR_BAJA 'B'
#define CHAR_MODIF 'M'

status_t validar_argumentos_gestion(int argc, char* argv[], FILE** pf_original, FILE** pf_registro, FILE** pf_log, gestion_t* accion);
status_t crear_datos(FILE *pf, t_datos **datos[]);
status_t destruir_datos(t_datos **datos[]);
status_t gestion_altas(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, char *argv[]);
status_t gestion_bajas(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, char *argv[]);
status_t gestion_modificacion(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, char *argv[]);





int main(int argc, char* argv[])
{
	status_t estado;
	gestion_t accion;
	FILE *pf_original, *pf_registro, *pf_log;
	t_datos **datos_original = NULL;
	t_datos **datos_registro = NULL;

	if((estado = validar_argumentos_gestion(argc, argv, &pf_original, &pf_registro, &pf_log, &accion)) != ST_OK)
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
		if((estado = gestion_altas(datos_original, datos_registro, pf_original, argv)) != ST_OK)
		{
			imprimir_error(estado, stderr);
			return EXIT_FAILURE;
		}
		break;
	}
	case GESTION_BAJAS:
	{
		if((estado = gestion_bajas(datos_original, datos_registro, pf_original, argv)) != ST_OK)
		{
			imprimir_error(estado, stderr);
			return EXIT_FAILURE;
		}
		break;
	}
	case GESTION_MODIFICACION:
	{
		if((estado = gestion_modificacion(datos_original, datos_registro, pf_original, argv)) != ST_OK)
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

		switch(flag[j][1]) /*segun el caracter principal de cada opcion*/
		{
		case CHAR_ORIG:
		{
			if((*pf_original = fopen(argv[i+1], "rb")) == NULL)
			{
				return ST_ERROR_PUNTERO_NULO;
			}
			break;
		}

		case CHAR_REG:
		{
			if((*pf_registro = fopen(argv[i+1], "rb")) == NULL)
			{
				return ST_ERROR_PUNTERO_NULO;
			}
			break;
		}

		case CHAR_LOG:
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
		*accion = GESTION_BAJAS;
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



status_t crear_datos(FILE *pf, t_datos **datos[])
{
	size_t i, n;

	if (!pf || !datos)
		return ST_ERROR_PUNTERO_NULO;

	fseek(pf, 0, SEEK_END);
	n = ftell(pf)/(sizeof(t_datos)); /*number of datos in the file*/
	fseek(pf, 0, SEEK_SET);

	if ((*datos = (t_datos**)malloc(sizeof(t_datos*)*(n+1))) == NULL)
	{
		return ST_ERROR_NOMEM;
	}

	for(i = 0; i < n; i++)
	{
		if (((*datos)[i] = (t_datos*)malloc(sizeof(t_datos))) == NULL)
		{
			return ST_ERROR_NOMEM;
		}
		fread((*datos)[i], sizeof(t_datos), 1, pf);
	}

	(*datos)[n] = NULL;

	return ST_OK;
}




status_t destruir_datos(t_datos **datos[])
{
	int i;

	if (!datos)
		return ST_ERROR_PUNTERO_NULO;


	for (i = 0; (*datos)[i]; i++)
	{
		free((*datos)[i]);
		(*datos)[i] = NULL;
	}
	free(*datos);
	*datos = NULL;

	return ST_OK;
}


status_t gestion_altas(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, char *argv[])
{
	size_t i = 0, j;

	if (!datos_original[0] || !datos_registro[0] || !pf || !argv[0])
		return ST_ERROR_PUNTERO_NULO;

	while(argv[i][1] != CHAR_ORIG)
	{
		i++;
	}

	if((pf = freopen(argv[i + 1], "wb", pf)) == NULL) /*erase the file*/
	{
		return ST_ERROR_OPEN_ARCHIVO;
	}


	for (i = 0, j =0; datos_original[i] != NULL || datos_registro[j] != NULL; )
	{

		if ((datos_original[i] != NULL) && (datos_registro[j] != NULL))
		{
			if (datos_original[i]->id < datos_registro[j]->id)
			{
				if ((fwrite(datos_original[i], sizeof(t_datos), 1, pf)) != 1)
					return ST_ERROR_WRITE;
				i++;
			}
			else if (datos_original[i]->id > datos_registro[j]->id)
			{
				if ((fwrite(datos_registro[j], sizeof(t_datos), 1, pf)) != 1)
					return ST_ERROR_WRITE;
				j++;
			}
			else
			{
				j++; /*si los ids son iguales, no ecribimos el nuevo datos*/
				/* Aca es un caso de logueo que debemos tratar*/
			}
		}

		else if (datos_original[i] != NULL)
		{
			if ((fwrite(datos_original[i], sizeof(t_datos), 1, pf)) != 1)
				return ST_ERROR_WRITE;
			i++;
		}

		else if (datos_registro[j] != NULL)
		{
			if ((fwrite(datos_registro[j], sizeof(t_datos), 1, pf)) != 1)
				return ST_ERROR_WRITE;
			j++;
		}
	}

	return ST_OK;
}



status_t gestion_bajas(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, char *argv[])
{
	size_t i = 0, j;

	if (!datos_original[0] || !datos_registro[0] || !pf || !argv[0])
		return ST_ERROR_PUNTERO_NULO;

	while(argv[i][1] != CHAR_ORIG)
	{
		i++;
	}

	if((pf = freopen(argv[i + 1], "wb", pf)) == NULL) /*erase the file*/
	{
		return ST_ERROR_OPEN_ARCHIVO;
	}

	for (i = 0, j = 0; datos_original[i]; i++)
	{
		if (datos_registro[j])
		{
			if(datos_original[i]->id == datos_registro[j]->id)
			{
				j++;
			}
			else if(datos_original[i]->id < datos_registro[j]->id)
			{
				if ((fwrite(datos_original[i], sizeof(t_datos), 1, pf)) != 1)
					return ST_ERROR_WRITE;
			}
			else
			{
				j++;
				i--;
				/*aca es un caso de logueo*/
			}
		}
		else
		{
			if ((fwrite(datos_original[i], sizeof(t_datos), 1, pf)) != 1)
				return ST_ERROR_WRITE;
		}
	}

	return ST_OK;
}

status_t gestion_modificacion(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, char *argv[])
{
	size_t i = 0, j;

	if (!datos_original[0] || !datos_registro[0] || !pf || !argv[0])
		return ST_ERROR_PUNTERO_NULO;

	while(argv[i][1] != CHAR_ORIG)
	{
		i++;
	}

	if((pf = freopen(argv[i + 1], "wb", pf)) == NULL) /*erase the file*/
	{
		return ST_ERROR_OPEN_ARCHIVO;
	}

	for (i = 0, j = 0; datos_original[i]; i++)
	{
		if(datos_original[i]->id == datos_registro[j]->id)
		{
			j++;
		}
		else if(datos_original[i]->id < datos_registro[j]->id)
		{
			if ((fwrite(datos_original[i], sizeof(t_datos), 1, pf)) != 1)
				return ST_ERROR_WRITE;
		}
		else
		{
			j++;
			i--;
			/*aca es un caso de logueo*/
		}
	}

	return ST_OK;
}
