#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

pixel *load_pixels(char *path, unsigned int *w, unsigned int *h) {
  BMP *bmp = bopen(path);

  unsigned int width = get_width(bmp);
  unsigned int height = get_height(bmp);
  *w = width;
  *h = height;

  pixel pixels[width * height];
  unsigned int pxHead = 0;

  for (int x = 0;x < width;x++) {
    for (int y = 0;y < height;y++) {
      unsigned char r, g, b;
      get_pixel_rgb(bmp, x, y, &r, &g, &b);

      pixel p;
      p.red = r;
      p.green = g;
      p.blue = b;

      pixels[pxHead] = p;
      pxHead++;
    }
  }

  bclose(bmp);

  pixel *p = pixels;
  return p;
}

int cequal(pixel p1, pixel p2) {
  if (p1.red == p2.red && p1.green == p2.green && p1.blue == p2.blue && p1.alpha && p2.alpha) {
    return 1;
  }

  return 0;
}

pixel *get_unique(pixel *pixels, unsigned int pxLen, unsigned int *len) {
  pixel *unique = malloc(sizeof(pixel));
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
        unique = realloc(unique, sizeof(pixel) * (uniqLen + 1));
      }

      unique[uniqLen] = pixels[i];
      uniqLen++;
    }
  }

  *len = uniqLen;

  return unique;
}

int get_color_index(pixel *palette, unsigned int paletteLen, pixel p) {
  for (int i = 0;i < paletteLen;i++) {
    if (cequal(p, palette[i])) {
      return i;
    }
  }

  return 0;
}

int *index_pixels(pixel *pixels, unsigned int pxLen, pixel *palette, unsigned int paletteLen) {
  int *indexedBmp = malloc(sizeof(int) * pxLen);

  for (int p = 0;p < pxLen;p++) {
    indexedBmp[p] = get_color_index(palette, paletteLen, pixels[p]);
  }

  return indexedBmp;
}
