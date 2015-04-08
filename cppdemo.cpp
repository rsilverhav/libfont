#include <iostream>
#include <cstdlib>
#include "libfont.h"

int main ()
{
    std::cout << "Hello World! ";

    unsigned char * bitmap = getBitmapWithText();
    free(bitmap);
    
    return 0;

}
