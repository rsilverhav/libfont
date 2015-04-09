#ifdef __cplusplus
extern "C" {
#endif

  typedef struct font_bitmap_data{
    unsigned char * data;
    int width;

  } FontBitmapData;

  FontBitmapData getBitmapWithText(const char * text, const char *fontPath);

#ifdef __cplusplus
}
#endif
