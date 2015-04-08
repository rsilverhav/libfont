#include <stdio.h>
#include <stdlib.h>
#include "libfont.h"

#define STB_TRUETYPE_IMPLEMENTATION 
#include "stb_truetype.h"

unsigned char * getBitmapWithText(const char * text, const char * fontPath)
{
  /* load font file */
  long size;
  unsigned char* fontBuffer;

  FILE* fontFile = fopen(fontPath, "rb");
  if(fontFile == NULL) {
    printf("File does not exist, I will crash now :/\n");
  }

  fseek(fontFile, 0, SEEK_END);
  size = ftell(fontFile); /* how long is the file ? */
  fseek(fontFile, 0, SEEK_SET); /* reset */

  fontBuffer = malloc(size);

  fread(fontBuffer, size, 1, fontFile);
  fclose(fontFile);

  /* prepare font */
  stbtt_fontinfo info;
  if (!stbtt_InitFont(&info, fontBuffer, 0))
  {
    printf("failed\n");
  }

  int b_w = 512; /* bitmap width */
  int b_h = 512; /* bitmap height */
  int l_h = 256; /* line height */

  /* create a bitmap for the phrase */
  unsigned char* bitmap = malloc(b_w * b_h);

  /* calculate font scaling */
  float scale = stbtt_ScaleForPixelHeight(&info, l_h);

  const char* word = text;

  int x = 0;


  int ascent, descent, lineGap;
  stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);

  ascent *= scale;
  descent *= scale;

  int i;
  for (i = 0; i < strlen(word); ++i)
  {
    /* get bounding box for character (may be offset to account for chars that dip above or below the line */
    int c_x1, c_y1, c_x2, c_y2;
    stbtt_GetCodepointBitmapBox(&info, word[i], scale, scale, &c_x1, &c_y1, &c_x2, &c_y2);

    /* compute y (different characters have different heights */
    int y = ascent + c_y1;

    /* render character (stride and offset is important here) */
    int byteOffset = x + (y  * b_w);
    stbtt_MakeCodepointBitmap(&info, bitmap + byteOffset, c_x2 - c_x1, c_y2 - c_y1, b_w, scale, scale, word[i]);

    /* how wide is this character */
    int ax;
    stbtt_GetCodepointHMetrics(&info, word[i], &ax, 0);
    x += ax * scale;

    /* add kerning */
    int kern;
    kern = stbtt_GetCodepointKernAdvance(&info, word[i], word[i + 1]);
    x += kern * scale;
  }

  free(fontBuffer);

  return bitmap;

}
