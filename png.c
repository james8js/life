#include "lodepng.h"

#include <stdlib.h>
#include <stdio.h>

#include "png.h"

void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height)
{
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename, image, width, height);

  /*if there's an error, display it*/
  if(error) printf("error %u: %s\n", error, lodepng_error_text(error));
}


void savePNG(const char* filename, int **tab,  int width, int height)
{
  int color;
  unsigned char* image = malloc(width * height * 4);
  unsigned x, y;
  for(y = 0; y < height; y++)
  for(x = 0; x < width; x++)
  {
  //printf("for[%d][%d]->OK  w=%d h=%d\n", x, y, width, height);
		if(tab[y][x]==0)
			color=255;
		else
			color=0;
		
		
    image[4 * width * y + 4 * x + 0] = color;
    image[4 * width * y + 4 * x + 1] = color;
    image[4 * width * y + 4 * x + 2] = color;
    image[4 * width * y + 4 * x + 3] = 255;
  }

  /*run an example*/
  encodeOneStep(filename, image, width, height);

  free(image);

}
