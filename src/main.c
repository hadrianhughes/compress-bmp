#include <stdio.h>
#include "../lib/cbmp.h"

int main() {
  BMP *bmp = bopen("example.bmp");

  unsigned int width = get_width(bmp);
  unsigned int height = get_height(bmp);
  unsigned char r, g, b;

  for (int x = 0;x < width;x++) {
    for (int y = 0;y < height;y++) {
      get_pixel_rgb(bmp, x, y, &r, &g, &b);
      printf("%u %u %u\n", r, g, b);
    }
  }

  bclose(bmp);

  return 0;
}
