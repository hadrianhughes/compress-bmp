#include <stdio.h>
#include "../lib/cbmp.h"

typedef struct Color {
  unsigned char r, g, b;
} Color;

Color *load_pixels(char *path) {
  BMP *bmp = bopen(path);

  unsigned int width = get_width(bmp);
  unsigned int height = get_height(bmp);
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
  Color *pixels = load_pixels("example.bmp");

  return 0;
}
