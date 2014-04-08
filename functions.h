#define BG_BLACK 40

#define BRIGHT 1
#define RED 31 
#define GREEN 32
#define YELLOW 33 
#define BLUE 34 
#define PINK 35
#define CYAN 36 
#define WHITE 37

void setColor();

void resetColor();

int isNumeric (const char * s);

struct options getOptions(struct options opt, int argc, char **argv);

struct options{
	int nopt;
	int topt;
	int Nopt;
	int s;
	int o;
	char *fopt;
};

