#include <stdio.h>
#include <stdlib.h>

#include "libfont.h"

int main(int argc, char * argv[])
{
  FontBitmapData bitmap = getBitmapWithText("hejsan", "font.ttf", 256);

  free(bitmap.data);
  return 0;
}
