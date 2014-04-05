#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#ifdef _WIN32
#include "wingetopt.h"
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
#include "png.h"
#include "lodepng.h"
#include "functions.h"

int main(int argc, char **argv)
{
	int **life_tab, **life_tmp, x, y;
	opterr = 0;
	setColor();
	struct options opt = {-1,-1,-1,0,NULL};
	opt = getOptions(opt, argc, argv);
	struct life rlife;
	if(opt.fopt==NULL || fileExists(opt.fopt)==0 )
	{
		rlife = makeLife();
		life_tab = rlife.tab;
		x=rlife.xdim;
		y=rlife.ydim;
		printf("Plik nie został podany lub nie istnieje. Losuję stan generacji bazowej.\n");
	}
	else
		life_tab = loadLife(opt.fopt, &x, &y);
	life_tmp = createLife( x, y);
	resetColor();
	simulateLife(life_tab, life_tmp, x, y, opt.nopt, opt.Nopt, opt.topt, opt.s);
	return 0;
}
