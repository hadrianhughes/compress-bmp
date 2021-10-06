#include <stdio.h>
#include <stdlib.h>
#include "../lib/cbmp.h"
#include "./colors.c"

Color *load_pixels(char *path, unsigned int *w, unsigned int* h) {
  BMP *bmp = bopen(path);

  unsigned int width = get_width(bmp);
  unsigned int height = get_height(bmp);
  *w = width;
  *h = height;

  Color pixels[width * height];
  unsigned int pxHead = 0;

  for (int x = 0;x < width;x++) {
    for (int y = 0;y < height;y++) {
      unsigned char r, g, b;
      get_pixel_rgb(bmp, x, y, &r, &g, &b);

      Color p;
      p.r = r;
      p.g = g;
      p.b = b;

      pixels[pxHead] = p;
      pxHead++;
    }
  }

  bclose(bmp);

  Color *p = pixels;
  return p;
}

int main() {
  unsigned int w, h;
  unsigned int *width = &w;
  unsigned int *height = &h;
  Color *pixels = load_pixels("example.bmp", width, height);

  unsigned int ul;
  unsigned int *uniqLen = &ul;
  Color *unique = get_unique(pixels, *width * *height, uniqLen);

  free(unique);

  return 0;
}
