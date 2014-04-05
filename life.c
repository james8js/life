#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

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

#include "life.h"
#include "file.h"

int** createLife( int x, int y)
{
	int i,j;
	int **tab;
	tab = malloc(y * sizeof(tab));
	for(i=0; i<y; i++)
		tab[i] = (int*) malloc(sizeof(int) * x);

	for(i=0; i<y; i++)
		for(j=0; j<x; j++)
			tab[i][j]=0;
	return tab;
}

void setAlive(int **tab, int x, int y)
{
	tab[y][x]=1;
}

int** copyLife(int **tab, int x, int y)
{
	int i,j;
	int **tmp;
	tmp = malloc(y * sizeof(tmp));
	for(i=0; i<y; i++)
		tmp[i] = (int*) malloc(sizeof(int) * x);

	for(i=0; i<y; i++)
		for(j=0; j<x; j++)
			tmp[i][j]=tab[i][j];
	return tmp;
}

int checkNeighbour(int **tab_n, int x, int y, int xdim, int ydim)
{
	int i, j;
	int neighbour=0;
	for(j=y-1; j<=y+1; j++)
	{
		if(j<0 || j>=ydim)
		{
			continue;
		}
		for(i=x-1; i<=x+1; i++)
		{
			if(i<0 || i>=xdim || (i==x && j==y))
			{
				continue;
			}
			if(tab_n[j][i]==1)
			{
				neighbour++;
			}
		}
	}
	if(tab_n[y][x]==1 && (neighbour==2 || neighbour==3) )
	{
		return 1;
	}
	if(tab_n[y][x]==0 &&  neighbour==3 )
	{
		return 1;
	}
	return 0;
}

void newGeneration(int **tab, int **tmp, int xdim, int ydim)
{
	tmp=copyLife(tab, xdim, ydim);
	int i,j;
	for(j=0; j<ydim; j++)
	{
		for(i=0; i<xdim; i++)
		{
			tab[j][i] = checkNeighbour(tmp, i, j, xdim, ydim);
		}
	}
}

void showLife(int** tab, int xdim, int ydim)
{
	int i,j;
	for(j=0;j<ydim;j++)
	{
		for(i=0;i<xdim;i++)
		{
			printf("%d", tab[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}


struct life makeLife() //MakeLove!
{
	int i,j;
	int r;
	srand(time(NULL));
	struct life randomlife;
	randomlife.xdim = rand() % (12 - 10 +1 ) + 12;
	randomlife.ydim = rand() % (12 - 10 +1 ) + 12;
	randomlife.tab = createLife(randomlife.xdim, randomlife.ydim);
	for(i=0; i<randomlife.xdim; i++)
		for(j=0 ;j<randomlife.ydim; j++)
		{
			r=rand() % 10;
			if(r<3)
				randomlife.tab[j][i]=1;
		}
	return randomlife;
}

void simulateLife(int **life_tab, int **life_tmp, int x, int y, int nopt, int Nopt, int topt, int s)
{
	int t = time(NULL), i;
    char *dir = fileName();
    char dir_t[40];
    sprintf(dir_t, "%s", dir );
	char name[80];
	#ifdef _WIN32
		mkdir(dir);
	#else
	struct stat st = {0};
	if (stat(dir, &st) == -1) {
		mkdir(dir, 0700);
	}
	#endif
	for(i=1; i<=nopt; i++)
	{
		sprintf(name, "%s/%d",dir, t);
		if(s==1)
			showLife(life_tab, x, y);
		if(Nopt!=0 && i%Nopt==0)
			savePNG(name, life_tab, x, y);
		newGeneration(life_tab, life_tmp, x, y);
		t++;
		if(topt!=0)
			sleep(topt);
	}
	sprintf(name, "%s/generation_%s.txt", dir_t, fileName() );
	saveLife(name, life_tab, x, y);
}
