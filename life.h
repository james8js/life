int **tab;

int **tmp;

int *Xdim1;

int *Ydim1;

int** createLife( int m, int n);

void setAlive(int **tab, int x, int y);

int** copyLife(int **tab, int x, int y);

int checkNeighbour(int **tab_n, int x, int y, int xdim, int ydim);

void newGeneration(int **tab, int **tmp, int xdim, int ydim);

void showLife(int** tab, int xdim, int ydim);

void simulateLife(int **life_tab, int **life_tmp, int x, int y, int nopt, int Nopt, int topt, int s);

struct life
{
	int **tab;
	int xdim;
	int ydim;
};
struct life makeLife();
