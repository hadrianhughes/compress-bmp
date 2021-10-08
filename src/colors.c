#include <stdio.h>
#include <stdlib.h>
#include "colors.h"

void close_compressed(Compressed *c) {
  free(c->palette);
  free(c->indices);
  free(c);
}

pixel *load_pixels(Compressed *c, char *path) {
  BMP *bmp = bopen(path);

  unsigned int width = get_width(bmp);
  unsigned int height = get_height(bmp);
  c->width = width;
  c->height = height;

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

void get_unique(Compressed *c, pixel *pixels, unsigned int pxLen) {
  c->palette = malloc(sizeof(pixel));
  unsigned int uniqLen = 0;

  for (int i = 0;i < pxLen;i++) {
    int duplicate = 0;
    for (int j = 0;j < uniqLen;j++) {
      if (cequal(pixels[i], c->palette[j])) {
        duplicate = 1;
        break;
      }
    }

    if (!duplicate) {
      if (uniqLen > 0) {
        c->palette = realloc(c->palette, sizeof(pixel) * (uniqLen + 1));
      }

      c->palette[uniqLen] = pixels[i];
      uniqLen++;
    }
  }

  c->paletteLen = uniqLen;
}

int get_color_index(Compressed *c, pixel p) {
  for (int i = 0;i < c->paletteLen;i++) {
    if (cequal(p, c->palette[i])) {
      return i;
    }
  }

  return 0;
}

void index_pixels(Compressed *c, pixel *pixels, unsigned int pxLen) {
  int *indexedBmp = malloc(sizeof(int) * pxLen);

  for (int p = 0;p < pxLen;p++) {
    indexedBmp[p] = get_color_index(c, pixels[p]);
  }

  c->indices = indexedBmp;
}
