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
