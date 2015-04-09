#include <stdio.h>
#include <stdlib.h>
#include "libfont.h"

#define STB_TRUETYPE_IMPLEMENTATION 
#include "stb_truetype.h"

FontBitmapData getBitmapWithText(const char * text, const char *fontPath, int fontSize)
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


  const char* word = text;
  /* calculate font scaling */
  int l_h = fontSize; /* line height */
  float scale = stbtt_ScaleForPixelHeight(&info, l_h);
  int width = 0; /* width of the text */


  int i;
  for(i = 0; i < strlen(word); ++i)
  {
    int ax;
    stbtt_GetCodepointHMetrics(&info, word[i], &ax, 0);
    width += ax * scale;

    /* add kerning */
    int kern;
    kern = stbtt_GetCodepointKernAdvance(&info, word[i], word[i + 1]);
    width += kern * scale;
  }

  width = (int)(((float) width) / 256.0f + 1.0f)*256;

  int b_w = width; /* bitmap width */
  int b_h = l_h; /* bitmap height */

  /* create a bitmap for the phrase */
  unsigned char* bitmap = malloc(b_w * b_h);
  memset(bitmap, 0, b_w*b_h*sizeof(unsigned char));



  int x = 0;


  int ascent, descent, lineGap;
  stbtt_GetFontVMetrics(&info, &ascent, &descent, &lineGap);

  ascent *= scale;
  descent *= scale;

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

  //cleanup
  free(fontBuffer);
  
  FontBitmapData bitmapData;
  bitmapData.data = bitmap;
  bitmapData.width = width;
  bitmapData.textWidth = x;
  bitmapData.height = l_h;

  return bitmapData;

}
