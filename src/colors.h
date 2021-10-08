#include "../lib/cbmp.h"

typedef struct compressed {
  pixel **palette;
  int *indices;
  unsigned int width, height, paletteLen;
} Compressed;

void close_compressed(Compressed *c);

pixel **load_pixels(Compressed *c, char *path);

int cequal(pixel *p1, pixel *p2);

void get_unique(Compressed *c, pixel **pixels, unsigned int pxLen);

void index_pixels(Compressed *c, pixel **pixels, unsigned int pxLen);

BMP *decompress_to_bmp(Compressed *c);
