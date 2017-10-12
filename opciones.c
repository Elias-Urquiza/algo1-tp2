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

	char *choices[3];

	for(i = 0; i < 3; i++)
	{
		choices[i] = (char*)malloc(sizeof(char)*30);
	}

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
					printf("Eligio A\n");
					strcpy(choices[0], argv[i + 1]);
					break;
				}

			case OPCION_2:
				{
					printf("Eligio B\n");
					strcpy(choices[1], argv[i + 1]);
					break;
				}

			case OPCION_3:
				{
					printf("Eligio C\n");
					strcpy(choices[2], argv[i + 1]);
					break;
				}
		}
	}

	for(i = 0; i < 3; i++)
	{
		printf("%s ", choices[i]);
	}
	printf("\n");

	return EXIT_SUCCESS;
}
