#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../lib/cbmp.h"
#include "files.h"

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

void compress_routine(char *path) {
  unsigned int w, h;
  unsigned int *width = &w;
  unsigned int *height = &h;
  pixel *pixels = load_pixels(path, width, height);
  unsigned int pixelLen = (*width) * (*height);

  unsigned int pl;
  unsigned int *paletteLen = &pl;
  pixel *palette = get_unique(pixels, pixelLen, paletteLen);

  int *indices = index_pixels(pixels, pixelLen, palette, *paletteLen);

  write_indexed_file(indices, *width, *height, palette, *paletteLen, path);

  free(palette);
  free(indices);
}

int main(int argc, char **argv) {
  if (argc < 3) {
    printf("%s: Usage: %s <subcommand> <input_file>\n", argv[0], argv[0]);
    return 1;
  }

  char *subcommand = argv[1];
  char *path = argv[2];

  if (strcmp(subcommand, "compress") == 0) {
    compress_routine(path);
  } else {
    printf("%s: Subcommand '%s' not recognised.\n", argv[0], argv[1]);
  }

  return 0;
}
