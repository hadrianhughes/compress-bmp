#include <stdio.h>
#include <stdlib.h>

typedef struct Color {
  unsigned char r, g, b;
} Color;

int cequal(Color col1, Color col2) {
  if (col1.r == col2.r && col1.g == col2.g && col1.b == col2.b) {
    return 1;
  }

  return 0;
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

int get_color_index(Color *palette, unsigned int paletteLen, Color c) {
  for (int i = 0;i < paletteLen;i++) {
    if (cequal(c, palette[i])) {
      return i;
    }
  }

  return 0;
}

int *index_pixels(Color *pixels, unsigned int pxLen, Color *palette, unsigned int paletteLen) {
  int *indexedBmp = malloc(sizeof(int) * pxLen);

  for (int p = 0;p < pxLen;p++) {
    indexedBmp[p] = get_color_index(palette, paletteLen, pixels[p]);
  }

  return indexedBmp;
}
