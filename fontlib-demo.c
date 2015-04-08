#include <stdio.h>
#include <stdlib.h>

#include "libfont.h"

int main(int argc, char * argv[])
{
  unsigned char * bitmap = getBitmapWithText();


  int i;
  printf("bitmap contains:\n");
  for(i = 0; i < 10; i++){
    printf("%u, ", bitmap[i]);
  }
  printf("\n");

  free(bitmap);
  return 0;
}
