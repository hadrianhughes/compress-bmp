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
  unsigned int pixelLen = *width * *height;

  unsigned int pl;
  unsigned int *paletteLen = &pl;
  Color *palette = get_unique(pixels, pixelLen, paletteLen);

  int *indices = index_pixels(pixels, pixelLen, palette, *paletteLen);

  for (int i = 0;i < pixelLen;i++) {
    printf("%d\n", indices[i]);
  }

  free(palette);
  free(indices);

  return 0;
}
