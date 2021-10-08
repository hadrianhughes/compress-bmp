#include "../lib/cbmp.h"

pixel *load_pixels(char *path, unsigned int *w, unsigned int *h);

int cequal(pixel p1, pixel p2);

pixel *get_unique(pixel *pixels, unsigned int pxLen, unsigned int *len);

int get_color_index(pixel *palette, unsigned int paletteLen, pixel p);

int *index_pixels(pixel *pixels, unsigned int pxLen, pixel *palette, unsigned int paletteLen);
