#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

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

#include "functions.h"

void setColor()
{
	#ifdef _WIN64
		system("COLOR 4");
	#elif _WIN32
		system("COLOR 4");
	#elif __linux
		printf("%c[%dm",0x1B,RED);
	#endif
	
}

void resetColor()
{
	#ifdef _WIN64
		system("COLOR 7");
	#elif _WIN32
		system("COLOR 7");
	#elif __linux
		printf("%c[%dm",0x1B,0);//przywrocenie naturalnych kolorow konsoli
	#endif
}

int isNumeric (const char * s)
{
    if (s == NULL || *s == '\0' || isspace(*s))
      return 0;
    char * p;
    strtod (s, &p);
    return *p == '\0';
}

struct options getOptions(struct options opt, int argc, char **argv)
{
	int c;
	while ((c = getopt (argc, argv, "f:n:t:N:so")) != -1)
		switch (c)
		{
			case 'f':
				opt.fopt = optarg;
			break;
			case 'n':
				opt.nopt = atoi(optarg);
				if(isNumeric(optarg)==0 || opt.nopt < 0)
				{
					printf("Podane t jest niepoprawne. Używam domyślnej wartości n=5.\n");
					opt.nopt = 5;
				}
			break;
			case 't':
				opt.topt = atoi(optarg);
				if(isNumeric(optarg)==0 || opt.topt < 0 || opt.topt > 30)
				{
					printf("Podane t jest niepoprawne. Używam domyślnej wartości t=1.\n");
					opt.topt = 1;
				}
			break;
			case 'N':
				if(isNumeric(optarg)==0)
				{
					printf("Podane N jest niepoprawne. Używam domyślnej wartości N=1.\n");
					opt.Nopt = 1;
				}
				else
					opt.Nopt = atoi(optarg);
			break;
			case 's':
				opt.s = 1;
			break;
			case 'o':
				opt.o = 1;
			break;
			default:
				abort ();
		}
	if(opt.nopt<0)
	{
		opt.nopt=5;
		printf("'n' nie zostało podane. Używam domyślnej wartości n=5.\n");
	}
	if(opt.topt<0)
	{
		opt.topt=1;
		printf("t nie zostało podane. Używam domyślnej wartości t=1.\n");
	}
	if(opt.Nopt<0 || opt.Nopt>opt.nopt )
	{
		opt.Nopt=1;
		printf("'N' nie zostało podane lub jest niepoprawne (przedział <0,n>). Używam domyślnej wartości N=1.\n");
	}
	return opt;
}
