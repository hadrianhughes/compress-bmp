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

Color *get_unique(Color *pixels, unsigned int pxLen, unsigned int *len) {
  Color *unique = malloc(sizeof(Color));
  unsigned int uniqLen = 0;

  for (int i = 0;i < pxLen;i++) {
    int duplicate = 0;
    for (int j = 0;j < uniqLen;j++) {
      if (cequal(pixels[i], unique[j])) {
        duplicate = 1;
        break;
      }
    }

    if (!duplicate) {
      if (uniqLen > 0) {
        unique = realloc(unique, sizeof(Color) * (uniqLen + 1));
      }

      unique[uniqLen] = pixels[i];
      uniqLen++;
    }
  }

  *len = uniqLen;

  return unique;
}

int main() {
  unsigned int w, h;
  unsigned int *width = &w;
  unsigned int *height = &h;
  Color *pixels = load_pixels("example.bmp", width, height);

  unsigned int pl;
  unsigned int *paletteLen = &pl;
  Color *palette = get_unique(pixels, *width * *height, paletteLen);

  for (int i = 0;i < *paletteLen;i++) {
    printf("%u %u %u\n", palette[i].r, palette[i].g, palette[i].b);
  }

  free(palette);

  return 0;
}
