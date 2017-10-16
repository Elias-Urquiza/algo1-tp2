#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "tipos.h"
#include "funciones.h"

/*crear*/

status_t validar_argumentos_crear(int argc, char* argv[], FILE **file, int numero, char* mode)
{
	if (argv == NULL || file == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if (argc != MAX_ARGC_CREAR)
		return ST_ERROR_CANT_ARGC;
	if ((*file = fopen(argv[numero], mode)) == NULL)
		return ST_ERROR_OPEN_ARCHIVO;

	return ST_OK;
}



t_datos convertir_datos(char** arreglo)
{
	struct tm datetm = {0,0,0,1,0,0,0,0,0}; /* tm_mday puede tomar valores de 1 a 31 por ello elegí poner ese uno.*/
	char datechar[MAX_LENGTH] = "";
	char** datearreglo = NULL;
	t_datos datos;
	size_t l;
	status_t estado;

	datos.id = atoi(arreglo[0]);
	strcpy(datos.nombre, arreglo[1]);
	strcpy(datos.desarrollador, arreglo[2]);
	strcpy(datos.plataforma, arreglo[3]);

	strcpy(datechar, arreglo[4]);
	datearreglo = split(datechar, '-', &l, &estado);
	if(estado != ST_OK)
	{
		imprimir_error(estado, stderr);
		/*NO SE QUE MAS PONER AQUI*/
	}
	datetm.tm_year = atoi(datearreglo[0]) - ANIO_PARTIDA;
	datetm.tm_mon = atoi(datearreglo[1]) - 1;
	datetm.tm_mday = atoi(datearreglo[2]);
	if ((datos.date = mktime(&datetm)) == -1)
	{
		estado = ST_ERROR_TIME;
		imprimir_error(estado, stderr);
		datos.date = time(NULL); /*comprobar si esto sirve*/
	}

	if (destruir_arreglo_cadenas(&datearreglo, l) != ST_OK)
	{
		estado = ST_ERROR_DESTRUIR_ARREGLO;
		imprimir_error(estado, stderr);
		/*deberiamos hacer algo más aquí?*/
	}

	datos.puntaje = atof(arreglo[5]);
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

status_t destruir_arreglo_cadenas(char ***campos, size_t size) /*agregar verificación si saben cual poner*/
{
	size_t i;

	for(i = 0; i < size; i++)
	{
		free((*campos)[i]);
		(*campos)[i] = NULL;
	}

	free(*campos);
	*campos = NULL;

	return ST_OK;
}

char** split(const char* cadena, char delimitador, size_t* l, status_t* p_estado)
{
	char** campos;
	size_t n, i;
	char *aux, *q, *linea, delim[2];

	if(!cadena || !l)
	{
		*p_estado = ST_ERROR_PUNTERO_NULO;
		return NULL;
	}

	for(i = 0, n = 1; cadena[i]; i++)
	{
		if(cadena[i] == delimitador)
			n++;
	}

	if((campos = (char**)malloc(sizeof(char*)*n)) == NULL)
	{
		*l = 0;
		*p_estado = ST_ERROR_NOMEM;
		return NULL;
	}

	if((linea = strdup(cadena)) == NULL)
	{
		free(campos);
		campos = NULL;
		*l = 0;
		*p_estado = ST_ERROR_NOMEM;
		return NULL;
	}

	delim[0] = delimitador;
	delim[1] = '\0';

	for(i = 0, q = linea; (aux = strtok(q, delim)) != NULL; i++, q = NULL)
	{
		if((campos[i] = strdup(aux)) == NULL)
		{
			if((*p_estado = destruir_arreglo_cadenas(&campos, i)) != ST_OK)
			{
				imprimir_error(*p_estado, stderr);
			}
			campos = NULL;
			*l = 0;
		}
	}
	free(linea);
	*l = i;
	*p_estado = ST_OK;
	return campos;
}
/* */

/*deco*/

status_t validar_argumentos_deco(int argc, char* argv[], FILE **file, int numero, char* mode)
{
	if (argv == NULL || file == NULL)
		return ST_ERROR_PUNTERO_NULO;
	if (argc != MAX_ARGC_DECO)
		return ST_ERROR_CANT_ARGC;
	if ((*file = fopen(argv[numero], mode)) == NULL)
		return ST_ERROR_OPEN_ARCHIVO;

	return ST_OK;
}


/* */

/*modificar_base*/

status_t validar_argumentos_gestion(int argc, char* argv[], FILE** pf_original, FILE** pf_registro, FILE** pf_log, gestion_t* accion, size_t* pos_original)
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

			*pos_original = i + 1;

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
			if((*pf_log = fopen(argv[i+1], "a+b")) == NULL)
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

	return ST_OK;
}



status_t crear_datos(FILE *pf, t_datos **datos[])
{
	size_t i, n;

	if (!pf || !datos)
		return ST_ERROR_PUNTERO_NULO;

	fseek(pf, 0, SEEK_END);
	n = ftell(pf)/(sizeof(t_datos)); /*esto representa el numero de datos en el archivo*/
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


status_t gestion_altas(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, FILE *plog, char *argv[], size_t pos_original)
{
	status_t caso_logueo = ST_LOG_ALTA;
	size_t i, j;
	struct tm date;

	if (!datos_original[0] || !datos_registro[0] || !pf || !argv[0])
		return ST_ERROR_PUNTERO_NULO;

	if((pf = freopen(argv[pos_original], "wb", pf)) == NULL) /*erase the file*/
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

			if (datos_original[i]->id > datos_registro[j]->id)
			{
				if ((fwrite(datos_registro[j], sizeof(t_datos), 1, pf)) != 1)
					return ST_ERROR_WRITE;
				j++;
			}

			else
			{
				/*imprime aviso de logueo y datos decodificados en log*/
				imprimir_error(caso_logueo, p_log);

				date = *gmtime(&datos_registro[j].date);
				date.tm_year += ANIO_PARTIDA;
				date.tm_mon += 1;
				impresion_datos(p_log, datos_registro[j], date);
				j++;
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



status_t gestion_bajas(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, FILE *plog, char *argv[], size_t pos_original)
{
	size_t i, j;
	status_t caso_logueo = ST_LOG_BAJA;
	struct tm date;

	if (!datos_original[0] || !datos_registro[0] || !pf || !argv[0])
		return ST_ERROR_PUNTERO_NULO;

	if((pf = freopen(argv[pos_original], "wb", pf)) == NULL) /*erase the file*/
	{
		return ST_ERROR_OPEN_ARCHIVO;
	}

	for (i = 0, j = 0; datos_original[i]; i++)
	{
		if (datos_registro[j])
		{
			if(datos_original[i]->id == datos_registro[j]->id)
			{
				j++; /* se saltea aquel item que se desea eliminar*/
			}
			else if(datos_original[i]->id < datos_registro[j]->id)
			{
				if ((fwrite(datos_original[i], sizeof(t_datos), 1, pf)) != 1)
					return ST_ERROR_WRITE;
			}
			else
			{
				/*imprime un mensaje de aviso de logueo en log e imprime el item decodificado*/
				imprimir_error(caso_logueo, p_log);

				date = *gmtime(&datos_registro[j].date);
				date.tm_year += ANIO_PARTIDA;
				date.tm_mon += 1;
				impresion_datos(p_log, datos_registro[j], date);
				j++;
				i--;
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


status_t gestion_modificacion(t_datos *datos_original[], t_datos *datos_registro[], FILE *pf, FILE *plog, char *argv[], size_t pos_original)
{
	status_t caso_logueo = ST_LOG_MODIF;
	size_t i, j;
	struct tm date;

	if (!datos_original[0] || !datos_registro[0] || !pf || !argv[0])
		return ST_ERROR_PUNTERO_NULO;

	if((pf = freopen(argv[pos_original], "wb", pf)) == NULL) /*erase the file*/
	{
		return ST_ERROR_OPEN_ARCHIVO;
	}

	for (i = 0, j = 0; datos_original[i]; i++)
	{
		if (datos_registro[j])
		{
			if(datos_original[i]->id == datos_registro[j]->id)
			{
				if ((fwrite(datos_registro[j], sizeof(t_datos), 1, pf)) != 1)
					return ST_ERROR_WRITE;
				j++;

			}
			else if(datos_original[i]->id < datos_registro[j]->id)
			{
				if ((fwrite(datos_original[i], sizeof(t_datos), 1, pf)) != 1)
					return ST_ERROR_WRITE;
			}
			else
			{
				/*imprime mensaje de logueo y los datos decodificados en el log*/
				imprimir_error(caso_logueo, p_log);

				date = *gmtime(&datos_registro[j].date);
				date.tm_year += ANIO_PARTIDA;
				date.tm_mon += 1;
				impresion_datos(p_log, datos_registro[j], date);
				j++;
				i--;
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


/* */
/*Impresiones*/

void imprimir_error(status_t estado, FILE* salida)
{
	switch(estado)
	{
	case ST_ERROR_PUNTERO_NULO:
		fprintf(salida, "%s\n", MSJ_ERROR_PUNTERO_NULO);
		break;

	case ST_ERROR_NOMEM:
		fprintf(salida, "%s\n", MSJ_ERROR_NOMEM);
		break;

	case ST_ERROR_CANT_ARGC:
		fprintf(salida, "%s\n", MSJ_ERROR_CANT_ARGC);
		break;

	case ST_ERROR_OPEN_ARCHIVO:
		fprintf(salida, "%s\n", MSJ_ERROR_OPEN_ARCHIVO);
		break;

	case ST_ERROR_TIME:
		fprintf(salida, "%s\n", MSJ_ERROR_TIME);
		break;

	case ST_ERROR_DESTRUIR_ARREGLO:
		fprintf(salida, "%s\n", MSJ_ERROR_DESTRUIR_ARREGLO);
		break;

	case ST_ERROR_FLAGS:
		fprintf(salida, "%s\n", MSJ_ERROR_FLAGS);
		break;

	case ST_ERROR_COMANDO:
		fprintf(salida, "%s\n", MSJ_ERROR_COMANDO);
		break;

	case ST_ERROR_WRITE:
		fprintf(salida, "%s\n", MSJ_ERROR_WRITE);
		break;

	case ST_LOG_ALTA:
		fprintf(salida, "%s\n", MSJ_LOG_ALTA);
		break;

	case ST_LOG_BAJA:
		fprintf(salida, "%s\n", MSJ_LOG_BAJA);
		break;

	case ST_LOG_MODIF:
		fprintf(salida, "%s\n", MSJ_LOG_MODIF);
		break;

	default:
		fprintf(salida, "%s\n", MSJ_ERROR);
	}

	return;
}

void imprimir_uso_gestion(void)
{
	fprintf(stderr, "%s\n", MSJ_USO_GESTION);
	return;
}

void impresion_datos(FILE* pf_salida, t_datos datos, struct tm date)
{
	fprintf(pf_salida, "%lu,%s,%s,%s,%i-%i-%i,%.0f,%lu\n", datos.id, datos.nombre, datos.desarrollador, datos.plataforma, date.tm_year, date.tm_mon, date.tm_mday, datos.puntaje, datos.resenas);
	return;
}
