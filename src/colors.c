#include <stdio.h>
#include <stdlib.h>
#include "colors.h"
#include "../lib/cbmp.h"

void close_compressed(Compressed *c) {
  free(c->palette);
  free(c->indices);
  free(c);
}

pixel **load_pixels(Compressed *c, char *path) {
  BMP *bmp = bopen(path);

  unsigned int width = get_width(bmp);
  unsigned int height = get_height(bmp);
  c->width = width;
  c->height = height;

  pixel **pixels = malloc(sizeof(pixel*) * width * height);
  unsigned int pxHead = 0;

  for (int x = 0;x < width;x++) {
    for (int y = 0;y < height;y++) {
      unsigned char r, g, b;
      get_pixel_rgb(bmp, x, y, &r, &g, &b);

      pixel *p = malloc(sizeof(pixel));
      p->red = r;
      p->green = g;
      p->blue = b;
      p->alpha = 1;

      pixels[pxHead] = p;
      pxHead++;
    }
  }

  bclose(bmp);

  return pixels;
}

int cequal(pixel *p1, pixel *p2) {
  if (p1->red == p2->red && p1->green == p2->green && p1->blue == p2->blue) {
    return 1;
  }

  return 0;
}

void get_unique(Compressed *c, pixel **pixels, unsigned int pxLen) {
  pixel **unique = malloc(0);
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
      uniqLen++;
      unique = realloc(unique, sizeof(pixel*) * uniqLen);
      unique[uniqLen - 1] = pixels[i];
    }
  }

  c->palette = unique;
  c->paletteLen = uniqLen;
}

int get_color_index(Compressed *c, pixel *p) {
  for (int i = 0;i < c->paletteLen;i++) {
    if (cequal(p, c->palette[i])) {
      return i;
    }
  }

  return 0;
}

void index_pixels(Compressed *c, pixel **pixels, unsigned int pxLen) {
  int *indexedBmp = malloc(sizeof(int) * pxLen);

  for (int p = 0;p < pxLen;p++) {
    indexedBmp[p] = get_color_index(c, pixels[p]);
  }

  c->indices = indexedBmp;
}

BMP *decompress_to_bmp(Compressed *c) {
  pixel **pixels = malloc(sizeof(pixel*) * c->width * c->height);
  for (int y = 0;y < c->height;y++) {
    for (int x = 0;x < c->width;x++) {
      int pos = c->height * y + x;
      pixels[pos] = c->palette[c->indices[pos]];
    }
  }

  BMP *bmp = bcreate(c->width, c->height, pixels);
  return bmp;
}
