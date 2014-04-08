#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "life.h"
#include "file.h"
#include "functions.h"

#ifdef linux
	#include <sys/types.h>
	#include <sys/stat.h>
	#include <unistd.h>
#elif defined _WIN32 || defined _WIN64
	#include "wingetopt.h"
	#include <windows.h>
	#include <conio.h>
	#include <process.h>
#endif

int** loadLife(const char *file, int *x_dim, int *y_dim)
{
	int **tab, x=0, y=0, i=0, ln=1, max_x, max_y, lgth;
        FILE *fr;
        char *line = NULL, *tmp_1, *tmp_2;
        size_t len = 0;
		ssize_t read;
        fr = fopen(file, "r");
        if (fr == NULL)
        {
			printf("Nie można otworzyć pliku %s.", file);
			exit(EXIT_FAILURE);
		}
        while ((read = getline(&line, &len, fr)) != -1) {
			tmp_1 = strtok (line," ");
			tmp_2 = strtok (NULL," ");
			lgth = strlen(tmp_2);
			if( tmp_2[lgth-1] == '\n' )
				tmp_2[lgth-1] = 0;
			if(isNumeric(tmp_1)==1 && isNumeric(tmp_2)==1)
			{
				x = atoi( tmp_1 );
				y = atoi( tmp_2 );
			}
			else
			{
				printf("Błąd na linii: %d w pliku %s: ! wartości nie są liczbami.\n", ln, file);
				ln++;
				continue;
			}
			if(i==0)
			{
				if(x>0 && y>0)
				{
					*x_dim=x;
					*y_dim=y;
					tab = createLife(x, y);
					max_x= x;
					max_y= y;
					i++;
				}
				else
				{
					printf("Błąd na linii: %d w pliku %s: wymiary tablicy nie mogą być ujemne.\n", ln, file);
					continue;
				}
			}
			else
			{
				if(x>max_x || y>max_y || x<0 || y<0)
				{
					printf("Błąd na linii %d w pliku %s: współrzędne punktu są nieprawidłowe, muszą być więszke od 0, x<%d i y<%d.\n", ln, file, max_x, max_y);
					ln++;
					continue;
				}
				setAlive(tab, y, x);
			}
			ln++;
        }
        if(i==0)
		{
			printf("Plik %s nie zawiera żadnych poprawnych danych.", file);
			exit(EXIT_FAILURE);
		}	
        if (line)
                free(line);
	fclose(fr);
    return tab;
}

void saveLife(const char *file, int **tab, int xdim, int ydim)
{
	FILE *fw;
	fw = fopen ( file, "ab+" );
	if(fw==NULL)
	{
		printf("Nie można otworzyć pliku %s do zapisu.", file);
		exit(EXIT_FAILURE);
	}
	fprintf(fw, "%d %d", xdim, ydim);
	int i, j;
	for(i=0; i<xdim; i++)
	{
		for(j=0; j<ydim; j++)
		{
			if(tab[j][i]==1)
				fprintf(fw, "\n%d %d", i, j);
				
		}
	}
	fclose(fw);
}

char* fileName()
{
	time_t timer;
	static char dir[20];
    struct tm* tm_info;
	time(&timer);
    tm_info = localtime(&timer);
    strftime(dir, 20, "%Y-%m-%d_%H:%M:%S", tm_info);
	return dir;
}

int fileExists(const char * filename)
{
	FILE * file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return 1;
    }
    return 0;
}
