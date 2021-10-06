#include <stdio.h>

typedef struct Color {
  unsigned char r, g, b;
} Color;

int cequal(Color col1, Color col2) {
  if (col1.r == col2.r && col1.g == col2.g && col1.b == col2.b) {
    return 1;
  }

  return 0;
}
