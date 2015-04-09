#include <stdio.h>
#include <stdlib.h>

#include "libfont.h"

int main(int argc, char * argv[])
{
  FontBitmapData bitmap = getBitmapWithText("hejsan", "font.ttf");

  free(bitmap.data);
  return 0;
}
