#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OPCION_1 'A'
#define OPCION_2 'B'
#define OPCION_3 'C'
int main(int argc, char* argv[])
{
	const char *opt[] = {"-A", "-B", "-C"};
	int i, j;

	for(i = 1; i < argc; i+=2)
	{
		for(j = 0; j < sizeof(opt)/sizeof(opt[0]); j++)
		{
			if(!(strcmp(argv[i], opt[j]))) /*agregué el ! porque sin el, no sirve. Es porque strcmp devuelve 0 si es verdad, pero if lo lee al reves*/
				break;
		}

		if(j == sizeof(opt)/sizeof(opt[0]))
		{
			puts("error");
		}

		switch(opt[j][1]) /*lee la opcion*/
		{
			case OPCION_1:
				{
					printf("Eligio A: %s\n", argv[i+1]);
					break;
				}

			case OPCION_2:
				{
					printf("Eligio B: %s\n", argv[i+1]);
					break;
				}

			case OPCION_3:
				{
					printf("Eligio C: %s\n", argv[i+1]);
					break;
				}
		}
	}

	return EXIT_SUCCESS;
}
