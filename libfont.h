#ifdef __cplusplus
extern "C" {
#endif

  typedef struct font_bitmap_data{
    unsigned char * data;
    int width;
    int textWidth;
    int height;
  } FontBitmapData;

  FontBitmapData getBitmapWithText(const char * text, const char *fontPath, int fontSize);

#ifdef __cplusplus
}
#endif
