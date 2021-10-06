#include <stdio.h>
#include "../lib/cbmp.h"

typedef struct Pixel {
  unsigned char r, g, b;
} Pixel;

int main() {
  BMP *bmp = bopen("example.bmp");

  unsigned int width = get_width(bmp);
  unsigned int height = get_height(bmp);
  Pixel pixels[width * height];
  unsigned int pxHead = 0;

  for (int x = 0;x < width;x++) {
    for (int y = 0;y < height;y++) {
      unsigned char r, g, b;
      get_pixel_rgb(bmp, x, y, &r, &g, &b);

      Pixel p;
      p.r = r;
      p.g = g;
      p.b = b;

      pixels[pxHead] = p;
      pxHead++;
    }
  }

  bclose(bmp);

  return 0;
}