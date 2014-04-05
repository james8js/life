#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "life.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#include <process.h>
#include <dir.h>
#endif

#ifdef linux
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#endif

int** loadLife(const char *file, int *x_dim, int *y_dim)
{
	int **tab;
        FILE * fr;
        char * line = NULL;
        size_t len = 0;
		ssize_t read;
        int x=0, y=0, i=0;
        fr = fopen(file, "r");
        if (fr == NULL)
        {
			printf("Nie można otworzyć pliku %s.", file);
			exit(EXIT_FAILURE);
		}
        while ((read = getline(&line, &len, fr)) != -1) {
			x = atoi( strtok (line," ") );
			y = atoi( strtok (NULL," ") );
			if(i==0)
			{
				*x_dim=x;
				*y_dim=y;
				tab = createLife(x, y);
				i++;
			}
			else
				setAlive(tab, y, x);
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
